#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"           // raylib OpenGL abstraction layer to OpenGL 1.1, 2.1, 3.3+ or ES2

#define RLIGHTS_IMPLEMENTATION
#include "rlight.h"

#include "GameSettings.hpp"
#include "BirdsEyeCamera.hpp"
#include "hotCorners.hpp"
#include "ControlHandler.hpp"
#include "GameMap.hpp"


int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    // Load Game Parameters
    GameSettings* settings = GameSettings::getInstance();
    InitWindow(settings->screenWidth, settings->screenHeight, "raylib");
    
    // Generate Map
    GameMap gameMap(settings->mapSize, settings->mapSize);

    // Generate Camera
    BirdsEyeCamera birdsEyeCamera(
        settings->camPos, settings->camTarget, settings->upAxis, 
        settings->camFovy, settings->camType, settings->camSpeed);

    // Load GameControls
    ControlHandler inputManager(&birdsEyeCamera);

    // Load shader and set up some uniforms
    Shader shader = LoadShader("data/base_lighting.vs", "data/lighting.fs");
    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, UNIFORM_VEC4);

    // Using just 1 point lights
    CreateLight(LIGHT_POINT, (Vector3){ 0, 2, 6 }, Vector3Zero(), WHITE, shader);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        checkCorners(settings->screenWidth, settings->screenHeight, settings->hotCornerSize, &inputManager);
        // Update
        //----------------------------------------------------------------------------------
        birdsEyeCamera.update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // Update the light shader with the camera view position
            SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &birdsEyeCamera.camera.position.x, UNIFORM_VEC3);

            BeginMode3D(birdsEyeCamera.camera);

                gameMap.drawMap();

            EndMode3D();

            DrawText(TextFormat("%f", birdsEyeCamera.camera.position.x), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("%f", birdsEyeCamera.camera.position.y), 10, 60, 20, DARKGRAY);
            DrawText(TextFormat("%f", birdsEyeCamera.camera.position.z), 10, 80, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }



    UnloadShader(shader);
    gameMap.unloadMap();
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

