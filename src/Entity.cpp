#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(float _x, float _y, float _width, float _height, Canis::GLTexture _texture)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    texture = _texture;
}