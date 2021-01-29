#include "raylib.h"
#include "raymath.h"

#include "BirdsEyeCamera.hpp"


BirdsEyeCamera::BirdsEyeCamera(Vector3 camPos, Vector3 camTarget, Vector3 up, float camFovy, int camType, float camSpeed) {
    camera = { 0 };
    camera.position = camPos;
    camera.target = camTarget;
    camera.up = up;
    camera.fovy = camFovy;
    camera.type = camType;
    SetCameraMode(camera, CAMERA_CUSTOM);

    cameraMoveSpeed = camSpeed;
    cameraMoveDirection = {0};

    forward = {camera.target.x - camera.position.x, 0, camera.target.z - camera.position.z};
    backward = {-forward.x, 0, -forward.z};
    right = {forward.x, 0, -forward.z};
    left = {-forward.x, 0, forward.z};
}

void BirdsEyeCamera::moveForward() {
    cameraMoveDirection = Vector3Add(cameraMoveDirection, forward);
}
void BirdsEyeCamera::moveBackward() {
    cameraMoveDirection = Vector3Add(cameraMoveDirection, backward);
}
void BirdsEyeCamera::moveLeft() {
    cameraMoveDirection = Vector3Add(cameraMoveDirection, left);
}
void BirdsEyeCamera::moveRight() {
    cameraMoveDirection = Vector3Add(cameraMoveDirection, right);
}

void BirdsEyeCamera::update() {
    delta_pos = Vector3Scale(Vector3Normalize(cameraMoveDirection), cameraMoveSpeed * GetFrameTime());
    camera.position = Vector3Add(camera.position, delta_pos);
    camera.target = Vector3Add(camera.target, delta_pos);
    cameraMoveDirection = {0};
    UpdateCamera(&camera);
}
