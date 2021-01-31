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
        float tileSize;

        map<int, Model> *terrainModels;
        map<int, Model> *vegetationModels;

        vector<vector<int>> terrain;
        vector<vector<int>> vegetation;

    public:
        GameMap(int rows, int cols, map<int, Model> *terrainModels, map<int, Model> *vegetationModels, float tileSize);
        void drawMap();

    private:
        void drawArray(vector<vector<int>> mapArray, map<int, Model> *models, int tileSize);
};

GameMap::GameMap(int rows, int cols, map<int, Model> *terrainModels, map<int, Model> *vegetationModels, float tileSize) {
    this->rows = rows;
    this->cols = cols;
    this->tileSize = tileSize;
    this->terrainModels = terrainModels;
    this->vegetationModels = vegetationModels;

    terrain.resize(rows, vector<int>(cols, 1));
    vegetation.resize(rows, vector<int>(cols, 0));
}

void GameMap::drawArray(vector<vector<int>> mapArray, map<int, Model> *models, int tileSize) {
    for (int y=0; y < rows; y++) {
        float posy = (y - rows / 2.0) * tileSize;

        for (int x=0; x < cols; x++)  {
            float posx = (x - cols / 2.0) * tileSize;
            if (mapArray[y][x] != 0) {
                DrawModel((*models)[mapArray[y][x]-1], (Vector3){posx, 0, posy}, 1.0f, WHITE);
            }
        }
    }
}

void GameMap::drawMap() {
    drawArray(terrain, terrainModels, tileSize);
    drawArray(vegetation, vegetationModels, tileSize);
}
