#include "Entity.hpp"

Entity::Entity()
{

}

Entity::Entity(float _x, float _y, float _z, float _width, float _height, Canis::GLTexture _texture)
{
    x = _x;
    y = _y;
    z = _z;
    width = _width;
    height = _height;
    texture = _texture;
}

void Entity::MoveWithDirection(float deltaTime)
{
    x += direction.x * velocity;
    y += direction.y * velocity;
}