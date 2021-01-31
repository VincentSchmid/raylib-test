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
        map<int, modelMap *> allModels;
    
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

            Texture buildingTexture = LoadTexture("assets/buildings/texture/wood_gradients.png");

            for (int i = 0; i < buildings.size(); i++)
                for (int m = 0; m < buildings[i].materialCount; m++)
                    buildings[i].materials[m].maps[MAP_DIFFUSE].texture = buildingTexture;

            allModels[0] = &terrainModels;
            allModels[1] = &vegetationModels;
            allModels[2] = &buildings;
        };

        /* Here will be the instance stored. */
        static GameAssets* instance;

    public:
        void applyShader(Shader shader);
        void unload();
        /* Static access method. */
        static GameAssets* getInstance() {
            if (instance == 0)
            {
                instance = new GameAssets();
            }

            return instance;
        };
};

void GameAssets::applyShader(Shader shader) {
    // for every modelMap
    for (int i = 0; i < allModels.size(); i++)

        // for every Model in modelMap
        for (int n = 0; n < (* allModels[i]).size(); n++)

            // for every Material in Model
            for (int u = 0; u < (* allModels[i])[n].materialCount; u++)
                (* allModels[i])[n].materials[u].shader = shader;
}

void GameAssets::unload() {
    // for every modelMap
    for (int i = 0; i < allModels.size(); i++)

        // for every Model in modelMap
        for (int n = 0; n < (* allModels[i]).size(); n++)
            UnloadModel((* allModels[i])[n]);
}

GameAssets* GameAssets::instance = 0;
