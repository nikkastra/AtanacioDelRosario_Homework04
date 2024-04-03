#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>

//#include "entity.hpp"

void Entity::Update(float delta_time) {
    current_state->Update(*this, delta_time);
}



void Entity::SetState(EntityState* new_state) {
    current_state = new_state;
    current_state->Enter(*this);
}


void EntityCheckCollision::Enter(Entity& entity){
    
}

void EntityCheckCollision:: Update(Entity& entity, float delta_time){
    
};

//Constructor 
Entity::Entity(Vector2 pos, float radius, float size, float speed, float healthPoints){

};