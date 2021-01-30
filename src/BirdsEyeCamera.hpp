#ifndef BIRDS_EYE_CAMERA
#define BIRDS_EYE_CAMERA

#include "raylib.h"


class BirdsEyeCamera {
    public:
        Camera camera;

    private:
        float cameraMoveSpeed;
        Vector3 forward;
        Vector3 backward;
        Vector3 left;
        Vector3 right;
        Vector3 cameraMoveDirection;
        Vector3 delta_pos;

    public:
        BirdsEyeCamera(Vector3 camPos, Vector3 camTarget, Vector3 up, float camFovy, int camType, float camSpeed);
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void update();

    private:
        void setOrientation();
};
#endif
