// Singleton
#ifndef BIRDS_EYE_CAMERA
#define BIRDS_EYE_CAMERA

#include "raylib.h"

class BirdsEyeCamera {
    public:

    private:
        float cameraMoveSpeed;
        Vector3 forward;
        Vector3 backward;
        Vector3 left;
        Vector3 right;
        Vector3 cameraMoveDirection;
        Vector3 delta_pos;
        
        Camera *camera;

    public:
        BirdsEyeCamera(Camera *camera, float cameraMoveSpeed);
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        void update();
};
#endif
