#ifndef GAME_MAP
#define GAME_MAP


#include <vector>

#include "raylib.h"

#include "GameSettings.hpp"

using namespace std;

class GameMap {
    private:
        int rows;
        int cols;
        GameSettings *settings;

        int modelCount;
        map<int, Model> terrainModels;
        vector<vector<int>> terrain;

    public:
        GameMap(int rows, int cols);
        void drawMap();

    private:
        void drawTerrain();
        void drawVegetation();
        void unloadMap();
};

GameMap::GameMap(int rows, int cols) {
    settings = GameSettings::getInstance();

    modelCount = 3;
    terrainModels = {};
    //grass
    terrainModels[0] = LoadModel("assets/terrain/Plate_Grass_Dirt_01.glb");
    //tree
    terrainModels[1] = LoadModel("assets/terrain/Large_Oak_Fall_01.glb");
    //tree2
    terrainModels[2] = LoadModel("assets/terrain/Tree_01.glb");

    this->rows = rows;
    this->cols = cols;
    terrain.resize(rows, std::vector<int>(cols, 0));
}

void GameMap::drawTerrain() {
    for (int y=0; y < rows; y++) 
    {
        float posy = (y - rows / 2.0) * settings->tileSize;

        for (int x=0; x < cols; x++)  {
            float posx = (x - cols / 2.0) * settings->tileSize;
            DrawModel(terrainModels[0], (Vector3){posx, 0, posy}, 1.0f, WHITE);
        }
    }
}

void GameMap::drawVegetation() {

}

void GameMap::drawMap() {
    drawTerrain();
    drawVegetation();
}

void GameMap::unloadMap() {
    for (int i = 0; i < modelCount; i++)
    {
        UnloadModel(terrainModels[i]);
    }
}
#endif
