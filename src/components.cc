#include "components.h"

#include <iostream>

#include "chunk_generated.h"
#include "schema_handler.h"
#include "utils.h"

namespace andora {
Chunk::Chunk(const char* name, int id) : name_(name), id_(id) {
  fs::path chunk_path = GetSaveDir() / kGameChunksDir / name;
  SchemaHandler<schema::Chunk*> chunk_schema(chunk_path.string().c_str(),
                                             schema::GetChunk);

  auto schema_blocks = chunk_schema.scheme_->blocks();
  for (int i = 0; i < schema_blocks->size(); i++) {
    auto block = schema_blocks->Get(i);
    blocks_.emplace_back(
        Block{raylib::Vector2{block->pos().x(), block->pos().y()},
              block->has_collider(), false});
  }

  pos_x_ = chunk_schema.scheme_->pos_x();
}  // namespace andora

void Chunk::Write() {
  assert(!name_.empty());
  flatbuffers::FlatBufferBuilder builder(1024);
  std::vector<schema::Block> blocks;

  for (const auto& block : blocks_) {
    blocks.emplace_back(
        schema::Block{{block.pos.x, block.pos.y}, block.has_collider});
  }
  auto blocks_vec = builder.CreateVectorOfStructs(blocks.data(), blocks.size());
  auto chunk = andora::schema::CreateChunk(builder, pos_x_, blocks_vec);
  builder.Finish(chunk);

  fs::path chunk_path = GetSaveDir() / kGameChunksDir / name_;
  auto chunk_file = std::fstream(chunk_path, std::ios::out | std::ios::binary);
  chunk_file.write(reinterpret_cast<char*>(builder.GetBufferPointer()),
                   builder.GetSize());
  chunk_file.close();
}

std::string Chunk::GetSavePath() {
  assert(!name_.empty());
  fs::path chunk_path = GetSaveDir() / kGameChunksDir / name_;
  return chunk_path.string();
}
}  // namespace andora