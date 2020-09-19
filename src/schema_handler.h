#pragma once

#include <fstream>
#include <iostream>

namespace andora {
template <class T>
class SchemaHandler {
 public:
  T schema_;

  template <class F>
  SchemaHandler(const char* path, F&& get_schema) : path_(path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    data_len_ = file.tellg();
    file.seekg(0, std::ios::beg);
    data_ = new char[data_len_];
    file.read(data_, data_len_);
    file.close();
    schema_ = const_cast<T>(get_schema(data_));
  };

  SchemaHandler(const char* path, T&& schema, char* data)
      : path_(path), schema_(std::move(schema)), data_(std::move(data)) {
    data = nullptr;
  };

  ~SchemaHandler() { delete[] data_; };

 private:
  const char* path_;
  char* data_;
  int data_len_;
};
}  // namespace andora