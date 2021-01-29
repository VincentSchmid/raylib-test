/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"           // raylib OpenGL abstraction layer to OpenGL 1.1, 2.1, 3.3+ or ES2

#define RLIGHTS_IMPLEMENTATION
#include "rlight.h"

#include "BirdsEyeCamera.hpp"
#include "hotCorners.hpp"
#include "ControlHandler.hpp"


template <size_t rows, size_t cols, size_t len>
void DrawTerrain(int (&terrain)[rows][cols], int tileSize, Model (&models)[len]) 
{
    for (int y=0; y < rows; y++) 
    {
        float posy = (y - rows / 2.0) * tileSize;

        for (int x=0; x < cols; x++) 
        {
            float posx = (x - cols / 2.0) * tileSize;

            // Draw Terrain Patch where there are other assets
            if (terrain[y][x] != 0) {
                // DrawModel(models[0], (Vector3){posx, 0, posy}, 1.0f, WHITE);
            }

            DrawModel(models[terrain[y][x]], (Vector3){posx, 0, posy}, 1.0f, WHITE);
        }
    }
}

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    // Load model5
    const int modelCount = 3;
    Model terrainModels [modelCount]= {};

    //grass
    terrainModels[0] = LoadModel("assets/terrain/Plate_Grass_01.glb");
    //tree
    terrainModels[1] = LoadModel("assets/terrain/Large_Oak_Fall_01.glb");
    //tree2
    terrainModels[2] = LoadModel("assets/terrain/Tree_01.glb");
    

    // Create Terrain
    const int tileSize = 3;
    const int terrainSize = 10;
    int terrain [terrainSize][terrainSize] = {{}};
    terrain[3][4] = 1;
    terrain[5][6] = 2;

    // Camera Params
    Camera camera = { 0 };
    camera.position = (Vector3){ -10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;

    const int hotCornerSize = 100;
    const float cameraMoveSpeed = 20;

    SetCameraMode(camera, CAMERA_CUSTOM);
    BirdsEyeCamera birdsEyeCamera(&camera, cameraMoveSpeed);

    // Load shader and set up some uniforms
    Shader shader = LoadShader("data/base_lighting.vs", "data/lighting.fs");
    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, UNIFORM_VEC4);

    // Using just 1 point lights
    CreateLight(LIGHT_POINT, (Vector3){ 0, 2, 6 }, Vector3Zero(), WHITE, shader);

    ControlHandler inputManager(&birdsEyeCamera);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        checkCorners(screenWidth, screenHeight, hotCornerSize, &inputManager);
        // Update
        //----------------------------------------------------------------------------------
        birdsEyeCamera.update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // Update the light shader with the camera view position
            SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &camera.position.x, UNIFORM_VEC3);

            BeginMode3D(camera);

                DrawTerrain(terrain, tileSize, terrainModels);

            EndMode3D();

            DrawText(TextFormat("%f", camera.position.x), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("%f", camera.position.y), 10, 60, 20, DARKGRAY);
            DrawText(TextFormat("%f", camera.position.z), 10, 80, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (int i = 0; i < modelCount; i++)
    {
        UnloadModel(terrainModels[i]);
    }

    UnloadShader(shader);
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
