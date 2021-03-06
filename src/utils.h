#pragma once

#include <filesystem>
#include <raylib-cpp.hpp>

#include "components.h"
#include "physics.h"

namespace andora {
namespace fs = std::filesystem;

extern raylib::Camera2D main_camera;
extern raylib::Texture2D dirt_txt;

constexpr int kBlockLen = 16;
constexpr int kChunkWidth = 32;
constexpr int kTargetFPS = 60;
constexpr float kScreenWidth = 1280;
constexpr float kScreenHeight = 720;
constexpr const char* kGameName = "andora";
constexpr const char* kGameChunksDir = "chunks";

void InitGame();
void RenderCollisions(Physics& p);
bool IsBlockSurrounded(const Chunk& chunk, const Block& block);

fs::path GetSaveDir();
}  // namespace andora