#define RLGL_IMPLEMENTATION
#define RL_CULL_DISTANCE_NEAR              0.01    // Default projection matrix near cull distance
#define RL_CULL_DISTANCE_FAR             1000.0    // Default projection matrix far cull distance
#include <raylib.h>
#include "rcamera.h"
#include "marching_cubes.h"
#include<raymath.h>
#include<math.h>
#include<assert.h>

Mesh GenMesh(){
    TRIANGLE tris[10000];
    int count = 0;
    for(float x = -1.0; x < 1.0; x+=0.1){
        for(float y = -1.0; y < 1.0; y+=0.1){
            for(float z = -1.0; z < 1.0; z+=0.1){
                GRIDCELL cell;
                int id = 0;
                for(int dx = 0; dx <= 1; dx++){
                    for(int dy = 0; dy <= 1; dy++){
                        for(int dz = 0; dz <= 1; dz++){
                            cell.p[id] = (XYZ){x+0.1*dx, y+0.1*dy, z+0.1*dz};
                            cell.val[id] = sqrtf((x+0.1*dx)*(x+0.1*dx)+(y+0.1*dy)*(y+0.1*dy)+(z+0.1*dz)*(z+0.1*dz))-1.0f;
                            id++;
                        }
                    }
                }
                TRIANGLE chunk[10];
                int res = Polygonise(cell, 0.0, chunk);
                for(int i = 0; i < res; i++){
                    tris[count+i] = chunk[i];
                }
                count += res;
            }
        }
    }
    Mesh mesh = {0};
    assert(count > 0);
    mesh.triangleCount = count;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float)); 
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));
    for(int i = 0; i < count; i++){
        mesh.vertices[i*9+0] = tris[i].p[0].x;
        mesh.vertices[i*9+1] = tris[i].p[0].y;
        mesh.vertices[i*9+2] = tris[i].p[0].z;

        mesh.vertices[i*9+3] = tris[i].p[1].x;
        mesh.vertices[i*9+4] = tris[i].p[1].y;
        mesh.vertices[i*9+5] = tris[i].p[1].z;

        mesh.vertices[i*9+6] = tris[i].p[2].x;
        mesh.vertices[i*9+7] = tris[i].p[2].y;
        mesh.vertices[i*9+8] = tris[i].p[2].z;

        XYZ normal = Vector3CrossProduct(Vector3Subtract(tris[i].p[1], tris[i].p[0]), Vector3Subtract(tris[i].p[2], tris[i].p[0]));

        mesh.normals[i*9+0] += normal.x;
        mesh.normals[i*9+1] += normal.y;
        mesh.normals[i*9+2] += normal.z;

        mesh.normals[i*9+3] += normal.x;
        mesh.normals[i*9+4] += normal.y;
        mesh.normals[i*9+5] += normal.z;

        mesh.normals[i*9+6] += normal.x;
        mesh.normals[i*9+7] += normal.y;
        mesh.normals[i*9+8] += normal.z;

        mesh.texcoords[i*6+0] = 1.0f;
        mesh.texcoords[i*6+1] = 0.0f;
        mesh.texcoords[i*6+2] = 1.0f;
        mesh.texcoords[i*6+3] = 0.0f;
        mesh.texcoords[i*6+4] = 1.0f;
        mesh.texcoords[i*6+5] = 0.0f;

    }

     UploadMesh(&mesh, false);

     return mesh;
}

static Mesh GenMeshCustom(void)
{
    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
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
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera mode type

    Vector3 cubepos = {0.0f,1.0f,0.0f};

    SetTargetFPS(60);

    Model model = LoadModelFromMesh(GenMesh());

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

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