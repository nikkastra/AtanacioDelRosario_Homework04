#ifndef PLAYER
#define PLAYER

#include <raylib.h>
#include <raymath.h>

#include "entity.hpp"

class Player;

class PlayerState{
public:
    virtual ~PlayerState(){}
    virtual void Enter(Player& player) = 0;
    virtual void Update(Player& player, float delta_time) = 0;
};

class PlayerIdle : public PlayerState{
public:
    void Enter(Player& player);
    void Update(Player& player, float delta_time);
};

class PlayerMoving : public PlayerState{
public:
    void Enter(Player& player);
    void Update(Player& player, float delta_time);
};

class PlayerDodging : public PlayerState{
public:
    void Enter(Player& player);
    void Update(Player& player, float delta_time);
};

class PlayerAttacking : public PlayerState{
public:
    void Enter(Player& player);
    void Update(Player& player, float delta_time);
};

class PlayerBlocking : public PlayerState{
public:
    void Enter(Player& player);
    void Update(Player& player, float delta_time);
};

class Player : public Entity{
public:
    
    Color color;

    Vector2 hitboxPos;
    float hitboxRad;

    Vector2 velocity;
    float timer;
    float invulnerabilityTimer;
    float powerUpTimer;
    
    PlayerIdle idle;
    PlayerMoving moving;
    PlayerDodging dodging;
    PlayerAttacking attacking;
    PlayerBlocking blocking;

    Player(Vector2 pos, float rad, float spd, int hp);
    Player();

    void Update(float delta_time);
    
    void Draw();

    void SetState(PlayerState* new_state);

    void HandleCollision(Entity* entity);

private:
    PlayerState* current_state;
};

#endif