/*
 * Example of a singleton design pattern.
 * Copyright (C) 2011 Radek Pazdera
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
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