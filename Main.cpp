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

int main(){

    //full entity parameter: 
    //Entity(Vector2 pos = {0,0}, float radius = 0.0f, float size = 0.0f, float speed = 0, float healthPoints = 0);
    // note that the equal signs are default values
    Player player({WINDOW_WIDTH/2, WINDOW_HEIGHT/2}, 50.0f, 200.0f, 5); // for player Player(Vector2 pos, float rad, float spd, int hp);
    Enemy enemy1({WINDOW_WIDTH/8, WINDOW_HEIGHT/8}, 100.0f, 100.0f, 2); // for enemy Vector2 pos, float sz, float spd, int hp
    Enemy enemy2({7*WINDOW_WIDTH/8, 7*WINDOW_HEIGHT/8}, 100.0f, 100.0f, 2); 

    Item item1 ({0, 0}, 31,2,1);
    Item item2 ({WINDOW_WIDTH/2 + 400, WINDOW_HEIGHT/9 + 200}, 31,2,1);
    Item item3 ({WINDOW_WIDTH/9 + 150, WINDOW_HEIGHT/2 + 200}, 31,2,1);
    Item item4 ({WINDOW_WIDTH/2 + 1000, WINDOW_HEIGHT + 200}, 31,2,1);
    Item item5 ({WINDOW_WIDTH, WINDOW_HEIGHT}, 31,2,1);


    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "miss ko na siya");
    SetTargetFPS(FPS);

    Camera2D camera_view = {0};
    float EDGE_X[2], EDGE_Y[2];
    camera_view.offset = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    camera_view.zoom = 1.0f;

    Texture joshHutcherson = LoadTexture("josh_hutcherson.png");

    while(!WindowShouldClose()){
        float delta_time = GetFrameTime();

        camera_view.target = player._position;

        player.Update(delta_time);
        if(enemy1._healthPoints > 0){
            player.HandleCollision(&enemy1);
            enemy1.Update(delta_time);
            enemy1.HandleCollision(&player);
            enemy2.HandleEnemyCollision(&enemy1);
        }
        if(enemy2._healthPoints > 0){
            player.HandleCollision(&enemy2);
            enemy2.Update(delta_time);
            enemy2.HandleCollision(&player);
            enemy1.HandleEnemyCollision(&enemy2);
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
        DrawTexture(joshHutcherson, 0, 0, WHITE);
        
        if(enemy1._healthPoints > 0 ) enemy1.Draw();
        if(enemy2._healthPoints  > 0) enemy2.Draw();
        
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
        if(enemy1._healthPoints <= 0 && enemy2._healthPoints <=0)
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