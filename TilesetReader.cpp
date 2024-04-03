#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

const int WINDOW_WIDTH = 624;
const int WINDOW_HEIGHT = 224;
const float FPS = 60;

struct Tile{
    Rectangle locationInSpriteSheet;
    bool has_collision;
};

Tile* allTiles = new Tile[2];
// allTiles[0]; //single plank
// alltiles[1]; //double plank

int main(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "miss ko na siya");
    SetTargetFPS(FPS);

    char tilesetName[20];
    int tileCount;
    int tileIndex = 0;
    int gridSizeX = -1;
    int gridSizeY = -1;
    std::vector<std::vector<int>> grid;

    FILE* configFile = fopen("tileset.txt", "r");
    if (configFile) {
        fscanf(configFile, "IMAGE_NAME %s\n", &tilesetName);
        fscanf(configFile, "TILE_COUNT %i\n", &tileCount);
        int h,w,x,y;
        for(int i = 0; i < tileCount; i++){
            fscanf(configFile, "%i %i %i %i\n", &x, &y, &w, &h);
            allTiles[i].locationInSpriteSheet.x = x;
            allTiles[i].locationInSpriteSheet.y = y;
            allTiles[i].locationInSpriteSheet.width = w;
            allTiles[i].locationInSpriteSheet.height = h;
        }
        fscanf(configFile, "GRID %i %i\n", &gridSizeX, &gridSizeY);
        for(int i = 0; i < gridSizeY; i++){
            std::vector<int> row;
            for(int j = 0; j < gridSizeX; j++){
                int g;
                fscanf(configFile, "%i", &g);
                row.push_back(g);
            }
            grid.push_back(row);
        }
        fclose(configFile);
        std::cout << "Config file SUCCESS\n";
    } else {
    std::cerr << "Error";
    }

    Texture tileMap = LoadTexture(tilesetName);

    while(!WindowShouldClose()){
        float delta_time = GetFrameTime();

        BeginDrawing();
        for(int i = 0; i < grid.size(); i++){
            std::vector<int> row = grid[i];
            for(int j = 0; j < row.size(); j++){
                DrawTexturePro(tileMap, allTiles[row[j]].locationInSpriteSheet, {(float) (16*j), (float) (16*i), 16, 16}, Vector2Zero(), 0, WHITE);
            }
        }
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();

    UnloadTexture(tileMap);

    return 0;
}