#include "physics.h"
#include <iostream>
namespace andora {
Physics::Physics(float fps) : dt_(1 / fps) {
  timer_ = Timer();
}


}