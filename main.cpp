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

template <size_t rows, size_t cols>
void DrawTerrain(int (&terrain)[rows][cols], int tileSize, Model grass) 
{
    for (int y=0; y < rows; y++) 
    {
        float posy = (y - rows / 2.0) * tileSize;

        for (int x=0; x < cols; x++) 
        {
            float posx = (x - cols / 2.0) * tileSize;

            switch(terrain[y][x]) 
            {
                case 0:
                    DrawModel(grass, (Vector3){posx, 0, posy}, 1.0f, WHITE);
                    break;
            }
        }
    }
}

void MoveCamera(int screenWidth, int screenHeight, int hotCornerSize, float cameraMoveSpeed, Camera *camera) {

    Vector3 forward = {camera->target.x - camera->position.x, 0, camera->target.z - camera->position.z};
    Vector3 backward = {-forward.x, 0, -forward.z};
    Vector3 right = {forward.x, 0, -forward.z};
    Vector3 left = {-forward.x, 0, forward.z};

    Vector3 cameraMoveDirection = {0};

    if (GetMouseX() <= hotCornerSize) {
        cameraMoveDirection = left;
    }

    if (GetMouseX() >= screenWidth - hotCornerSize) {
        cameraMoveDirection = right;
    }

    if (GetMouseY() <= hotCornerSize) {
        cameraMoveDirection = Vector3Add(cameraMoveDirection, forward);
    }

    if (GetMouseY() >= screenHeight - hotCornerSize) {
        cameraMoveDirection = Vector3Add(cameraMoveDirection, backward);
    }

    // add camera_move_speed * delta_time * normalized_move_direction to camera position and target
    Vector3 delta_pos = Vector3Scale(Vector3Normalize(cameraMoveDirection), cameraMoveSpeed * GetFrameTime());

    camera->position = Vector3Add(camera->position, delta_pos);
    camera->target = Vector3Add(camera->target, delta_pos);
}

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    // Load model
    Model grass = LoadModel("assets/3DNaturePack/Models/Plate_Grass_01.obj");
    // Create Terrain
    const int tileSize = 3;
    const int terrainSize = 10;
    int terrain [terrainSize][terrainSize] = {{}};

    // Camera Params
    Camera camera = { 0 };
    camera.position = (Vector3){ -10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;

    const int hotCornerSize = 100;
    const float cameraMoveSpeed = 20;

    // Load shader and set up some uniforms
    Shader shader = LoadShader("data/base_lighting.vs", "data/lighting.fs");
    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, UNIFORM_VEC4);


    // Using just 1 point lights
    CreateLight(LIGHT_POINT, (Vector3){ 0, 2, 6 }, Vector3Zero(), WHITE, shader);

    SetCameraMode(camera, CAMERA_CUSTOM);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        MoveCamera(screenWidth, screenHeight, hotCornerSize, cameraMoveSpeed, &camera);
        UpdateCamera(&camera);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            // Update the light shader with the camera view position
            SetShaderValue(shader, shader.locs[LOC_VECTOR_VIEW], &camera.position.x, UNIFORM_VEC3);

            BeginMode3D(camera);

                DrawTerrain(terrain, tileSize, grass);

            EndMode3D();

            DrawText(TextFormat("%f", camera.position.x), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("%f", camera.position.y), 10, 60, 20, DARKGRAY);
            DrawText(TextFormat("%f", camera.position.z), 10, 80, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadModel(grass);
    UnloadShader(shader);
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
