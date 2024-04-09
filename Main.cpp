#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>
#include <vector>

#include "PlayerStateMachine.cpp"
#include "EnemyStateMachine.cpp"
#include "ItemStateMachine.cpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float FPS = 60;
const int PIXELS = 16;

struct Tile{
    Rectangle locationInSpriteSheet;
    bool has_collision;
};

Tile* allTiles = new Tile[2];

int main(){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "miss ko na siya");
    SetTargetFPS(FPS);

    Camera2D camera_view = {0};
    float EDGE_X[2], EDGE_Y[2];
    camera_view.offset = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    camera_view.zoom = 1.0f;

    // Texture joshHutcherson = LoadTexture("josh_hutcherson.png");

    //--------------DRAW TILESET ALGORITHM----------------//
    char tilesetName[20];
    int tileCount;
    int tileIndex = 0;
    int gridSizeX = -1;
    int gridSizeY = -1;
    Vector2 playerPos;
    Vector2 enemyOne;
    Vector2 enemyTwo;
    Vector2 enemyThree;
    std::vector<std::vector<int>> grid;

    FILE* configFile = fopen("level1.txt", "r");
    if (configFile) {
        fscanf(configFile, "IMAGE_NAME %s\n", &tilesetName);
        int px, py, e1x, e1y, e2x, e2y, e3x, e3y;
        fscanf(configFile, "PLAYER_POS %i %i\n", &px, &py);
        playerPos = {(float) px, (float) py};
        fscanf(configFile, "ENEMY_ONE_POS %i %i\n", &e1x, &e1y);
        enemyOne = {(float) e1x, (float) e1y};
        fscanf(configFile, "ENEMY_TWO_POS %i %i\n", &e2x, &e2y);
        enemyTwo = {(float) e2x, (float) e2y};
        fscanf(configFile, "ENEMY_THREE_POS %i %i\n", &e3x, &e3y);
        enemyThree = {(float) e3x, (float) e3y};
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

    //full entity parameter: 
    //Entity(Vector2 pos = {0,0}, float radius = 0.0f, float size = 0.0f, float speed = 0, float healthPoints = 0);
    // note that the equal signs are default values
    Player player(playerPos, 50.0f, 200.0f, 5); // for player Player(Vector2 pos, float rad, float spd, int hp);
    Enemy enemy1(enemyOne, 100.0f, 100.0f, 2); // for enemy Vector2 pos, float sz, float spd, int hp
    Enemy enemy2(enemyTwo, 100.0f, 100.0f, 2);
    Enemy enemy3(enemyThree, 100.0f, 100.0f, 2);
    std::cout << enemy3._position.x << "|" << enemy3._position.y << std::endl;

    Item item1 ({0, 0}, 31,2,1);
    Item item2 ({WINDOW_WIDTH/2 + 400, WINDOW_HEIGHT/9 + 200}, 31,2,1);
    Item item3 ({WINDOW_WIDTH/9 + 150, WINDOW_HEIGHT/2 + 200}, 31,2,1);
    Item item4 ({WINDOW_WIDTH/2 + 1000, WINDOW_HEIGHT + 200}, 31,2,1);
    Item item5 ({WINDOW_WIDTH, WINDOW_HEIGHT}, 31,2,1);

    Texture tileMap = LoadTexture(tilesetName);

    while(!WindowShouldClose()){
        float delta_time = GetFrameTime();

        camera_view.target = player._position;

        player.Update(delta_time);
        if(enemy1._healthPoints > 0){
            player.HandleCollision(&enemy1);
            enemy1.Update(delta_time);

            enemy1.HandleCollision(&player);
            enemy2.HandleEnemyCollision(&enemy1);
            enemy3.HandleEnemyCollision(&enemy1);
        }
        if(enemy2._healthPoints > 0){
            player.HandleCollision(&enemy2);
            enemy2.Update(delta_time);

            enemy2.HandleCollision(&player);
            enemy1.HandleEnemyCollision(&enemy2);
            enemy3.HandleEnemyCollision(&enemy2);
        }
        if(enemy3._healthPoints > 0){
            player.HandleCollision(&enemy2);
            enemy3.Update(delta_time);

            enemy3.HandleCollision(&player);
            enemy1.HandleEnemyCollision(&enemy3);
            enemy2.HandleEnemyCollision(&enemy3);
        }

        if(item1._healthPoints > 0)
        {
            item1.HandleCollision(&player, delta_time); // detecting collisions with the player
            item1.HandleCollision(&enemy1, delta_time);
            item1.HandleCollision(&enemy2, delta_time);
            item1.Update(delta_time);
        }

        if(item2._healthPoints > 0)
        {
            item2.HandleCollision(&player, delta_time); // detecting collisions with the player
            item2.HandleCollision(&enemy1, delta_time);
            item2.HandleCollision(&enemy2, delta_time);
            item2.Update(delta_time);
        }

        if(item3._healthPoints > 0)
        {
            item3.HandleCollision(&player, delta_time); // detecting collisions with the player
            item3.HandleCollision(&enemy1, delta_time);
            item3.HandleCollision(&enemy2, delta_time);
            item3.Update(delta_time);
        }

        if(item4._healthPoints > 0)
        {
            item4.HandleCollision(&player, delta_time); // detecting collisions with the player
            item4.HandleCollision(&enemy1, delta_time);
            item4.HandleCollision(&enemy2, delta_time);
            item4.Update(delta_time);
        }

        if(item5._healthPoints > 0)
        {
            item5.HandleCollision(&player, delta_time); // detecting collisions with the player
            item5.HandleCollision(&enemy1, delta_time);
            item5.HandleCollision(&enemy2, delta_time);
            item5.Update(delta_time);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera_view);
        for(int i = 0; i < grid.size(); i++){
            std::vector<int> row = grid[i];
            for(int j = 0; j < row.size(); j++){
                DrawTexturePro(tileMap, allTiles[row[j]].locationInSpriteSheet, {(float) (PIXELS*j), (float) (PIXELS*i), PIXELS, PIXELS}, Vector2Zero(), 0, WHITE);
            }
        }
        
        if(enemy1._healthPoints > 0 ) enemy1.Draw();
        if(enemy2._healthPoints  > 0) enemy2.Draw();
        if(enemy3._healthPoints  > 0) enemy3.Draw();
        
        if(item1._healthPoints > 0) item1.Draw();
        if(item2._healthPoints > 0) item2.Draw();
        if(item3._healthPoints > 0) item3.Draw();
        if(item4._healthPoints > 0) item4.Draw();
        if(item5._healthPoints > 0) item5.Draw();

        if(player._healthPoints > 0) player.Draw();

        //lose condition
        EndMode2D();
        char buffer[10];
        sprintf_s(buffer, "%.0i", player._healthPoints);
        DrawText(buffer, 10, 10, 100, BLACK);
        // win condition
        if(enemy1._healthPoints <= 0 && enemy2._healthPoints <=0 && enemy3._healthPoints <=0)
        {
            DrawRectangle(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,GRAY);
            DrawText("You Win!", (WINDOW_WIDTH/2) - 175,(WINDOW_HEIGHT/2) - 50,100,GREEN);
        }

        if(player._healthPoints <= 0)
        {
            DrawRectangle(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,GRAY);
            DrawText("You Lose!", (WINDOW_WIDTH/2) - 175,(WINDOW_HEIGHT/2) - 50,100,RED);
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}