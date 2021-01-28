#include "raylib.h"

#include "hotCorners.hpp"
#include "ControlHandler.hpp"

void checkCorners(int screenWidth, int screenHeight, int hotCornerSize, ControlHandler *controlHandler) {
    if (GetMouseX() <= hotCornerSize) {
        controlHandler->moveCameraLeft();
    }

    if (GetMouseX() >= screenWidth - hotCornerSize) {
        controlHandler->moveCameraRight();
    }

    if (GetMouseY() <= hotCornerSize) {
        controlHandler->moveCameraForward();
    }

    if (GetMouseY() >= screenHeight - hotCornerSize) {
        controlHandler->moveCameraBackward();
    }

};
