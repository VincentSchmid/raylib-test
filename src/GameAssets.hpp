#pragma once

#include <map>

#include "raylib.h"

using namespace std;

class GameAssets { 
    public:
        typedef map<int, Model> modelMap;
        modelMap terrainModels;
        modelMap vegetationModels;
        modelMap buildings;
    
    private:
        /* Private constructor to prevent instancing. */
        GameAssets() {
            terrainModels[0] = LoadModel("assets/terrain/Plate_Grass_Dirt_01.glb");

            vegetationModels[0] = LoadModel("assets/terrain/Large_Oak_Fall_01.glb");
            vegetationModels[1] = LoadModel("assets/terrain/Tree_01.glb");

            buildings[0] = LoadModel("assets/buildings/Hut1.glb");
            buildings[1] = LoadModel("assets/buildings/Hut2.glb");
            buildings[2] = LoadModel("assets/buildings/Hut3.glb");
            buildings[3] = LoadModel("assets/buildings/Hut4.glb");
        };

        /* Here will be the instance stored. */
        static GameAssets* instance;

    public:
        void unload() {
            for (int i = 0; i < terrainModels.size(); i++) {
                UnloadModel(terrainModels[i]);
            }

            for (int i = 0; i < vegetationModels.size(); i++) {
                UnloadModel(vegetationModels[i]);
            }

            for (int i = 0; i < buildings.size(); i++) {
                UnloadModel(buildings[i]);
            }
        }
        /* Static access method. */
        static GameAssets* getInstance() {
            if (instance == 0)
            {
                instance = new GameAssets();
            }

            return instance;
        };
};

GameAssets* GameAssets::instance = 0;
