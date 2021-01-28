#include "ControlHandler.hpp"
#include "BirdsEyeCamera.hpp"


ControlHandler::ControlHandler(BirdsEyeCamera *birdsEyeCamera) {
    this->birdsEyeCamera = birdsEyeCamera;
}

void ControlHandler::moveCameraForward() {
    birdsEyeCamera->moveForward();
}

void ControlHandler::moveCameraBackward() {
    birdsEyeCamera->moveBackward();
}

void ControlHandler::moveCameraLeft() {
    birdsEyeCamera->moveLeft();
}

void ControlHandler::moveCameraRight() {
    birdsEyeCamera->moveRight();
}
