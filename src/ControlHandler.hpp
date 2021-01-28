#ifndef CONTROL_HANDLER
#define CONTROL_HANDLER

#include "BirdsEyeCamera.hpp"


class ControlHandler {
    private:
        BirdsEyeCamera *birdsEyeCamera;

    public:
        ControlHandler(BirdsEyeCamera *birdsEyeCamera);

        void moveCameraForward();
        void moveCameraBackward();
        void moveCameraLeft();
        void moveCameraRight();
};
#endif
