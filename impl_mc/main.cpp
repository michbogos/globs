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

#define EPSILON 0.05

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

Vector3 roundv3(Vector3 a){
    return (Vector3){std::roundf(a.x), std::roundf(a.y), std::roundf(a.z)};
}


Mesh GenMesh(){
    std::vector<TRIANGLE> tris;
    int count = 0;
    #pragma omp parallel
    for(double x = -5.0; x < 5.0; x+=EPSILON){
        for(double y = -5.0; y < 5.0; y+=EPSILON){
            for(double z = -5.0; z < 5.0; z+=EPSILON){
                GRIDCELL cell;
                int id = 0;
                for(int dx = 0; dx <= 1; dx++){
                    for(int dy = 0; dy <= 1; dy++){
                        for(int dz = 0; dz <= 1; dz++){
                            cell.p[id] = (XYZ){x+EPSILON*dx, y+EPSILON*dy, z+EPSILON*dz};
                            Vector3 p = (Vector3){x+EPSILON*dx, y+EPSILON*dy, z+EPSILON*dz};
                            Vector3 s = (Vector3){2.5, 2.5, 2.5};
                            //p = Vector3Subtract(p, Vector3Multiply(s, roundv3(Vector3Divide(p, s))));
                            cell.val[id] = sin(p.x*p.y)+sin(p.x*p.z)+cos(p.y*p.z)-1.0;
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
    mesh.normals = (float *)malloc(mesh.vertexCount*3*sizeof(float));
    int* num_vertices = (int *)malloc(mesh.vertexCount*3*sizeof(float));
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

        Vector3 cross = Vector3CrossProduct(Vector3Subtract(tris[i].p[1], tris[i].p[0]), Vector3Subtract(tris[i].p[2], tris[i].p[0]));
        mesh.normals[i*9+0] = cross.x;
        mesh.normals[i*9+1] = cross.y;
        mesh.normals[i*9+2] = cross.z;
        mesh.normals[i*9+3] = cross.x;
        mesh.normals[i*9+4] = cross.y;
        mesh.normals[i*9+5] = cross.z;
        mesh.normals[i*9+6] = cross.x;
        mesh.normals[i*9+7] = cross.y;
        mesh.normals[i*9+8] = cross.z;
    }

     UploadMesh(&mesh, false);

     return mesh;
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Globs");


    float cx = 0.0f;
    float cy = 10.0f;
    float cz = 10.0f;

    Camera3D camera = { 0 };
    camera.position = (Vector3){ cx,cy,cz };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera mode type


    SetTargetFPS(60);

    Model model = LoadModelFromMesh(GenMesh());

    Texture2D matcapTexture = LoadTexture("matcap2.png"); 

    Shader Matcap = LoadShader("shader.vs", "shader.fs");
    model.materials[0].shader = Matcap;
    model.materials[0].maps->texture = matcapTexture;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        glDisable(GL_CULL_FACE);
        BeginDrawing();
        ClearBackground(BLACK);
            DrawFPS(10, 10);
            BeginMode3D(camera);
                DrawGrid(10, 10);
                DrawModel(model, (Vector3){0, 0, 0}, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))){
            int display = GetCurrentMonitor();
            if (IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                SetWindowSize(screenWidth, screenHeight);
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                SetWindowSize(1920, 1080);
            }
            ToggleFullscreen();
        }
    }

    CloseWindow();

    return 0;
}