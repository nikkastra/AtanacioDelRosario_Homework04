#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>

#include "Player.hpp"
#include "entity.hpp"

class Entity;

void Player::Update(float delta_time){
    if(_damaged){
        invulnerabilityTimer += delta_time;
        if(invulnerabilityTimer > 2.0f){
            _damaged = false;
            invulnerabilityTimer = 0;
        }
    }

    // for the speed buff
    if(_buffed){
        _buffTimer += delta_time;
        if(_buffTimer  > 5.0f){
            _buffed = false;
            _buffTimer = 0.0f;
            _speedMultiplier = 1.0f;
        }
    }

    current_state->Update(*this, delta_time);
}

void Player::Draw(){
    DrawCircleV(_position, _radius, color);
    if(current_state == &attacking){
        DrawCircleV(hitboxPos, hitboxRad, color);
    }

}

void Player::SetState(PlayerState* new_state){
    current_state = new_state;
    current_state->Enter(*this);
}

void Player::HandleCollision(Entity* entity){
    Vector2 q;

    if(current_state == &attacking){
        if(hitboxPos.x < entity->_position.x){
            q.x = entity->_position.x;
        } else if (hitboxPos.x > entity->_position.x + entity->_size){
            q.x = entity->_position.x + entity->_size;
        } else {
            q.x = hitboxPos.x;
        }

        if(hitboxPos.y < entity->_position.y){
            q.y = entity->_position.y;
        } else if (hitboxPos.y > entity->_position.y + entity->_size){
            q.y = entity->_position.y + entity->_size;
        } else {
            q.y = hitboxPos.y;
        }

        if(Vector2Distance(hitboxPos, q) <= _radius && !entity->_damaged){
            entity->_healthPoints -= 1;
            entity->_damaged = true;
        }
    } else {
        entity->_damaged = false;

        if(_position.x < entity->_position.x){
            q.x = entity->_position.x;
        } else if (_position.x > entity->_position.x + entity->_size/2){
            q.x = entity->_position.x + entity->_size/2;
        } else {
            q.x = _position.x;
        }

        if(_position.y < entity->_position.y){
            q.y = entity->_position.y;
        } else if (_position.y > entity->_position.y + entity->_size/2){
            q.y = entity->_position.y + entity->_size/2;
        } else {
            q.y = _position.y;
        }

        if(Vector2Distance(_position, q) <= _radius && !_damaged){
            if(current_state == &dodging){
                _healthPoints -= 0;
            } else if (current_state == &blocking){
                _healthPoints -= (int) entity->_damage/2;
            } else {
                _healthPoints -= (int) entity->_damage;
            }
            _damaged = true;
        }
    }
}

//Player::Player(Vector2 pos, float rad, float spd, int hp)
Player::Player(Vector2 pos, float rad, float spd, int hp){
    // Entity Based Variables
    _position = pos;
    _radius = rad;
    _speed = spd;
    _buffTimer = 0;
    _speedMultiplier = 1.0f;
    _buffed = false;
    _damaged = false;
    _healthPoints = hp;
    
    // Player Based Variables
    timer = 0;
    invulnerabilityTimer = 0;
    hitboxPos = {_position.x + _radius +25.0f, _position.y};
    hitboxRad = _radius/2;

    SetState(&idle);
    
}


void PlayerIdle::Enter(Player& player){
    player.color = PINK;
}

void PlayerMoving::Enter(Player& player){
    player.color = GREEN;
}

void PlayerDodging::Enter(Player& player){
    player.color = ORANGE;
}

void PlayerAttacking::Enter(Player& player){
    player.color = BROWN;
}

void PlayerBlocking::Enter(Player& player){
    player.color = BLUE;
}

void PlayerIdle::Update(Player& player, float delta_time){
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)){
        player.SetState(&player.moving);
    }
    if(IsMouseButtonDown(0)) {
        player.SetState(&player.attacking);
    }
    if(IsMouseButtonDown(1)) {
        player.SetState(&player.blocking);
    }
}

void PlayerMoving::Update(Player& player, float delta_time){
    player.velocity = Vector2Zero();
    if(IsKeyDown(KEY_W)){
        player.velocity.y =  -1*(player._speed * player._speedMultiplier);
    }
    if(IsKeyDown(KEY_A)){
        player.velocity.x = -1*(player._speed * player._speedMultiplier);
    }
    if(IsKeyDown(KEY_S)){
        player.velocity.y =  (player._speed * player._speedMultiplier);
    }
    if(IsKeyDown(KEY_D)){
        player.velocity.x = (player._speed * player._speedMultiplier);
    }
    if(IsKeyPressed(KEY_SPACE)){
        player.SetState(&player.dodging);
    }
    player._position = Vector2Add(player._position, Vector2Scale(player.velocity, delta_time));

    if(IsMouseButtonDown(0)) {
        player.SetState(&player.attacking);
    }

    if(Vector2Length(player.velocity) == 0) {
        player.SetState(&player.idle);
    } else {
        player.hitboxPos = {player._position.x + player.velocity.x/(player._speed * player._speedMultiplier)*(player._radius + 25.0f), player._position.y + player.velocity.y/player._speed*(player._radius + 25.0f)};
    }
}

void PlayerDodging::Update(Player& player, float delta_time){
    player._position = Vector2Add(player._position, Vector2Scale(Vector2Scale(player.velocity, delta_time), 10.0f));
    player.timer += delta_time;
    if(player.timer > 0.125){
        player.timer = 0;
        player.SetState(&player.idle);
    }
}

void PlayerAttacking::Update(Player& player, float delta_time){
    player.timer += delta_time;
    if(player.timer > 0.25){
        player.timer = 0;
        player.SetState(&player.idle);
    }
}

void PlayerBlocking::Update(Player& player, float delta_time){
    if(IsMouseButtonReleased(1)){
        player.SetState(&player.idle);
    }
}