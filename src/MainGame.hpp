#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <string>
#include <time.h>

#include "Canis/Canis.hpp"
#include "Canis/GLSLProgram.hpp"
#include "Canis/Debug.hpp"
#include "Canis/Window.hpp"
#include "Canis/GLTexture.hpp"
#include "Canis/Window.hpp"
#include "Canis/Camera2D.hpp"
#include "Canis/SpriteBatch.hpp"
#include "Canis/ResourceManager.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Timing.hpp"

#include "Entity.hpp"

enum class GameState
{
    PLAY,
    EXIT
};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystem();
    void initShaders();
    void gameLoop();
    void processInput();
    void update();
    void drawGame();

    void resetPotato(Entity *potato, Entity *planet);
    int setShipTop(Entity *ship, Entity *planet);
    int setShipBottom(Entity *ship, Entity *planet);
    int moveShip(Entity *ship, Entity *planet, int index, int direction);
    void shootBullet(glm::vec2 position, float velocity, glm::vec2 direction, glm::vec2 size);
    void checkBulletCollision();
    bool checkCollision(Entity &one, Entity &two);


    Canis::Window _window;
    int _screenWidth, _screenHeight;
    GameState _gameState;

    Canis::GLSLProgram _colorProgram;

    Canis::SpriteBatch _spriteBatch;

    Canis::Camera2D _camera;

    Canis::GLTexture _player_light_texture;
    Canis::GLTexture _player_heavy_texture;
    Canis::GLTexture _planet_texture;
    Canis::GLTexture _planet_health_texture;
    Canis::GLTexture _potato_texture_01;
    Canis::GLTexture _potato_texture_02;
    Canis::GLTexture _potato_texture_03;
    Canis::GLTexture _potato_texture_04;
    Canis::GLTexture _bullet_texture;

    Canis::InputManager _inputManager;

    Canis::FpsLimiter _fpsLimiter;

    float _fps;
    float _maxFPS;
    float _time;

    int _array_to_sort[20] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};

    bool _is_sorted = false;

    int _current_index = 0;

    int _max_health = 3;
    int _current_health = 3;

    Entity _player_heavy;
    Entity _player_light;
    Entity _planet;
    std::vector<Entity> _planet_health = {};
    std::vector<Entity> _field_of_potatoes = {};
    std::vector<Entity> _bullets = {}; 

    float _last_update;
    float _dt = 0.0f;

    int _player_heavy_index = 0;
    int _player_light_index = 0;
    int _bullet_index = 0;

    std::vector<glm::vec2> _orbits = {
        glm::vec2(-1,0), glm::vec2(-.75,.25), glm::vec2(-0.5,0.5), glm::vec2(-0.25f,0.75f),
        glm::vec2(0,1), glm::vec2(0.25f,0.75f), glm::vec2(0.5f,0.5f), glm::vec2(0.75f,0.25f),
        glm::vec2(1,0), glm::vec2(0.75f, -0.25f), glm::vec2(0.5f,-0.5f), glm::vec2(0.25f,-0.75f),
        glm::vec2(0,-1), glm::vec2(-0.25f, -0.75f), glm::vec2(-0.5f,-0.5f), glm::vec2(-0.75f,-0.25f)
    };
};
