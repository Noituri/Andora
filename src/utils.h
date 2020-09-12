#pragma once

#include <raylib-cpp.hpp>

namespace andora {
extern raylib::Camera2D main_camera;

constexpr int kBlockLen = 16;
constexpr int kChunkWidth = 16;
constexpr int kTargetFPS = 60;
constexpr float kScreenWidth = 1280;
constexpr float kScreenHeight = 720;

void InitGame();
}  // namespace andora