#pragma once

#include <map>

#include "raylib.h"

using namespace std;

class GameSettings
{
    public:
        // Camera Settings
        const Vector3 upAxis = (Vector3){ 0.0f, 1.0f, 0.0f };

        Vector3 camPos = (Vector3){ -10.0f, 10.0f, 10.0f };
        Vector3 camTarget = (Vector3){ 0.0f, 0.0f, 0.0f };
        float camFovy = 60.0f;
        int camType = CAMERA_PERSPECTIVE;
        float camSpeed = 20;

        // Screen Settings
        int screenWidth = 800;
        int screenHeight = 450;

        int hotCornerSize = 100;
        float cameraMoveSpeed = 20;

        // Map Settings
        int mapSize = 10;
        int tileSize = 3;

    private:
        /* Private constructor to prevent instancing. */
        GameSettings() {
            
        };

        /* Here will be the instance stored. */
        static GameSettings* instance;

    public:
        /* Static access method. */
        static GameSettings* getInstance() {
            if (instance == 0)
            {
                instance = new GameSettings();
            }

            return instance;
        };
};

GameSettings* GameSettings::instance = 0;