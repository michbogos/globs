
#include<iostream>
#include <fstream>
#include <string>
#include <raylib.h>
#include<vector>
#include<sstream>
#define RAYGUI_IMPLEMENTATION
#include"raygui.h"

const int screenWidth = 800;
const int screenHeight = 450;
float ires[2] = {800.0f, 450.0f};
float aspect_ratio = (float)screenWidth/(float)screenHeight;
float iCamPos[3] = {0.5f, 0.5f, -3.0f};
float t = 0.0f;
std::vector<float> displacements;

float randf(){
    return (float)rand()/(float)RAND_MAX;
}

void replace_first(
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, toReplace.length(), replaceWith);
}

int main(void)
{
    std::ifstream ifs("base.fs");
    std::string baseString((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Shader baseShader = LoadShader(0, "base.fs");
    int iresLoc        = GetShaderLocation(baseShader, "resolution");
    int iCamPosLoc = GetShaderLocation(baseShader, "camPos");
    int iAspectRatioLoc = GetShaderLocation(baseShader, "aspectRatio");
    int iTimeLoc = GetShaderLocation(baseShader, "time");
    int iDisplacementLoc = GetShaderLocation(baseShader, "displacement");
    int iLengthLoc = GetShaderLocation(baseShader, "LENGTH");
    int id = 0;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE)){
            UnloadShader(baseShader);
            std::ostringstream stream;
            displacements.push_back(randf());
            displacements.push_back(randf());
            displacements.push_back(randf());
            stream << "res=opSmoothUnion(res, sphere(p-displacements["<< id <<"], 1.0), 0.1);\n//<**>";
            replace_first(baseString, "//<**>", stream.str());
            baseShader = LoadShaderFromMemory(0, baseString.c_str());
            iresLoc        = GetShaderLocation(baseShader, "resolution");
            iCamPosLoc = GetShaderLocation(baseShader, "camPos");
            iAspectRatioLoc = GetShaderLocation(baseShader, "aspectRatio");
            iTimeLoc = GetShaderLocation(baseShader, "time");
            iDisplacementLoc = GetShaderLocation(baseShader, "displacements");
            iLengthLoc = GetShaderLocation(baseShader, "LENGTH");

            while(!IsShaderReady(baseShader)){
                ;
            }
            id++;

        }
        if (IsKeyPressed(KEY_UP)){
            iCamPos[2]-= 1.0f*GetFrameTime();
        }
        if (IsKeyPressed(KEY_DOWN)){
            iCamPos[2]+= 1.0f*GetFrameTime();
        }
        if (IsKeyPressed(KEY_LEFT)){
            iCamPos[0]-= 1.0f*GetFrameTime();
        }
        if (IsKeyPressed(KEY_RIGHT)){
            iCamPos[0]+= 1.0f*GetFrameTime();
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))){
        int display = GetCurrentMonitor();
            if (IsWindowFullscreen())
            {
                SetWindowSize(screenWidth, screenHeight);
                aspect_ratio = (float)screenWidth/(float)screenHeight;

            }
            else
            {
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
                aspect_ratio = ires[0]/ires[1];
            }
            ToggleFullscreen();
        }
        t = (float)GetTime();
        SetShaderValue(baseShader, iresLoc, ires, SHADER_UNIFORM_VEC2);
        SetShaderValue(baseShader, iCamPosLoc, iCamPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(baseShader, iAspectRatioLoc, &aspect_ratio, SHADER_UNIFORM_FLOAT);
        SetShaderValue(baseShader, iTimeLoc, &t, SHADER_UNIFORM_FLOAT);
        SetShaderValueV(baseShader, iDisplacementLoc, displacements.data(), SHADER_UNIFORM_VEC3, displacements.size());
        SetShaderValue(baseShader, iLengthLoc, (int*)(displacements.size()), SHADER_UNIFORM_INT);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(baseShader);
                DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadShader(baseShader);
    CloseWindow();

    return 0;
}