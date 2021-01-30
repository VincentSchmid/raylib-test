#pragma once

#include <vector>
#include <map>

#include "raylib.h"

#include "GameSettings.hpp"

using namespace std;


class GameMap {
    private:
        int rows;
        int cols;
        GameSettings *settings;

        int terrainModelCount;
        int vegetationModelCount;

        map<int, Model> terrainModels;
        map<int, Model> vegetationModels;

        vector<vector<int>> terrain;
        vector<vector<int>> vegetation;

    public:
        GameMap(int rows, int cols);
        void drawMap();
        void unloadMap();

    private:
        void drawArray(vector<vector<int>> mapArray, map<int, Model> models, int tileSize);
};

GameMap::GameMap(int rows, int cols) {
    settings = GameSettings::getInstance();

    terrainModelCount = 1;
    vegetationModelCount = 2;

    terrainModels = {};
    vegetationModels = {};

    // Populate Terrain Models
    //grass
    terrainModels[0] = LoadModel("assets/terrain/Plate_Grass_Dirt_01.glb");

    // Populate Vegetation Models
    //tree
    vegetationModels[0] = LoadModel("assets/terrain/Large_Oak_Fall_01.glb");
    //tree2
    vegetationModels[1] = LoadModel("assets/terrain/Tree_01.glb");

    this->rows = rows;
    this->cols = cols;
    terrain.resize(rows, std::vector<int>(cols, 0));
}

void GameMap::drawArray(vector<vector<int>> mapArray, map<int, Model> models, int tileSize) {
    for (int y=0; y < rows; y++) {
        float posy = (y - rows / 2.0) * tileSize;

        for (int x=0; x < cols; x++)  {
            float posx = (x - cols / 2.0) * settings->tileSize;
            DrawModel(models[mapArray[y][x]], (Vector3){posx, 0, posy}, 1.0f, WHITE);
        }
    }
}

void GameMap::drawMap() {
    drawArray(terrain, terrainModels, settings->tileSize);
    drawArray(vegetation, vegetationModels, settings->tileSize);
}

void GameMap::unloadMap() {
    for (int i = 0; i < terrainModelCount; i++) {
        UnloadModel(terrainModels[i]);
    }

    for (int i = 0; i < vegetationModelCount; i++) {
        UnloadModel(terrainModels[i]);
    }
}
