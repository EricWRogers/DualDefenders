#pragma once

#include "Canis/GLTexture.hpp"

class Entity {
    public:
        float x;
        float y;
        float width;
        float height;
        Canis::GLTexture texture;
        
        Entity();
        Entity(float _x, float _y, float _width, float _height, Canis::GLTexture _texture);
};