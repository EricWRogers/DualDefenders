#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
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
    void drawGame();

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
    std::vector<Entity> _field_of_potatos = {};
};
