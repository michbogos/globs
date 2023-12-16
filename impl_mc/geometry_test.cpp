#define RL_CULL_DISTANCE_NEAR              0.01    // Default projection matrix near cull distance
#define RL_CULL_DISTANCE_FAR             1000.0    // Default projection matrix far cull distance
#include <raylib.h>
#include "rcamera.h"
#include "marching_cubes.h"
#include<raymath.h>
#include<math.h>
#include<assert.h>
#include<stdio.h>
#include<vector>
#include<GL/gl.h>
#include<algorithm>
#include<cmath>

double clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}

float Lerp(double a, double b, double t){
    return t*a+(1.0-t)*b;
}


float opSmoothUnion( float d1, float d2, float k )
{
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return Lerp( d2, d1, h ) - k*h*(1.0-h);
}


Mesh GenMesh(){
    std::vector<TRIANGLE> tris;
    int count = 0;
    for(double x = -2.0; x < 2.0; x+=0.1){
        for(double y = -2.0; y < 2.0; y+=0.1){
            for(double z = -2.0; z < 2.0; z+=0.1){
                GRIDCELL cell;
                int id = 0;
                for(int dx = 0; dx <= 1; dx++){
                    for(int dy = 0; dy <= 1; dy++){
                        for(int dz = 0; dz <= 1; dz++){
                            cell.p[id] = (XYZ){x+0.1*dx, y+0.1*dy, z+0.1*dz};
                            Vector3 p = (Vector3){x+0.1*dx, y+0.1*dy, z+0.1*dz};
                            cell.val[id] = opSmoothUnion(Vector3Length(p)-1.0, Vector3Length(Vector3Subtract(p, (Vector3){0.5, 0.5, 0.5}))-1.0, 0.1);
                            id++;
                        }
                    }
                }
                std::swap(cell.p[2], cell.p[3]);
                std::swap(cell.p[6], cell.p[7]);
                std::swap(cell.val[2], cell.val[3]);
                std::swap(cell.val[6], cell.val[7]);
                std::vector<TRIANGLE> res = Polygonise(cell, 0.0);
                for(int i = 0; i < res.size(); i++){
                    tris.push_back(res[i]);
                }
            }
        }
    }
    Mesh mesh = {0};
    mesh.triangleCount = tris.size();
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)malloc(mesh.vertexCount*3*sizeof(float));
    for(int i = 0; i < tris.size(); i++){
        mesh.vertices[i*9+0] = tris[i].p[0].x;
        mesh.vertices[i*9+1] = tris[i].p[0].y;
        mesh.vertices[i*9+2] = tris[i].p[0].z;

        mesh.vertices[i*9+3] = tris[i].p[1].x;
        mesh.vertices[i*9+4] = tris[i].p[1].y;
        mesh.vertices[i*9+5] = tris[i].p[1].z;

        mesh.vertices[i*9+6] = tris[i].p[2].x;
        mesh.vertices[i*9+7] = tris[i].p[2].y;
        mesh.vertices[i*9+8] = tris[i].p[2].z;
    }

     UploadMesh(&mesh, false);

     return mesh;
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    float cx = 0.0f;
    float cy = 10.0f;
    float cz = 10.0f;

    Camera3D camera = { 0 };
    camera.position = (Vector3){ cx,cy,cz };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera mode type

    Vector3 cubepos = {0.0f,1.0f,0.0f};

    SetTargetFPS(60);

    Model model = LoadModelFromMesh(GenMesh());

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        glDisable(GL_CULL_FACE);
        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawGrid(10, 10);
                DrawModel(model, (Vector3){0, 0, 0}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}