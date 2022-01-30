#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Canis/GLTexture.hpp"

class Entity {
    public:
        float x;
        float y;
        float z;
        float width;
        float height;
        Canis::GLTexture texture;
        glm::vec2 direction = glm::vec2(0.0f,0.0f);
        float velocity;
        
        Entity();
        Entity(float _x, float _y, float _z, float _width, float _height, Canis::GLTexture _texture);

        void MoveWithDirection(float deltaTime);
};