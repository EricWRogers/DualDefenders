#include "MainGame.hpp"

MainGame::MainGame() : _screenWidth(800), _screenHeight(600), _time(0), _gameState(GameState::PLAY), _maxFPS(60.0f)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
    initSystem();

    // Init Sprites
    /*_sprites.push_back(new Canis::Sprite());
    _sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0, "assets/textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

    _sprites.push_back(new Canis::Sprite());
    _sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0, "assets/textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");*/
        
    _player_light_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/DefaultShip.png");
    _player_heavy_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/DefaultShip2.png");
    _planet_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Planet.png");
    _planet_health_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Health.png");
    _potato_texture_01 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid1.png");
    _potato_texture_02 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid2.png");
    _potato_texture_03 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid3.png");
    _potato_texture_04 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteriod4.png");
    _bullet_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Bullet.png");

    _player_light.texture = _player_light_texture;
    _player_light.x = (_screenWidth/2.0f)-(_player_light_texture.width/2.0f);
    _player_light.y = (_screenHeight/2.0f)-(_player_light_texture.height/2.0f) + 100.0f;
    _player_light.width = 32.0f;
    _player_light.height = 32.0f;

    _planet.texture = _planet_texture;
    _planet.x = (_screenWidth/2.0f)-(_planet_texture.width/2.0f);
    _planet.y = (_screenHeight/2.0f)-(_planet_texture.height/2.0f);
    _planet.width = 128.0f;
    _planet.height = 128.0f;

    for (int i = 0; i < _max_health; i++)
    {
        _planet_health.push_back(
            Entity(
                4.0f + ((64.0f + 4.0f) * i),
                _screenHeight - 64.0f - 4.0f,
                64.0f,
                64.0f,
                _planet_health_texture
            )
        );
    }

    for (int i = 0; i < 40; i++)
    {
        int randomNumber = rand() % 4;

        switch(randomNumber)
        {
            case 0:
                _field_of_potatos.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        32.0f,
                        32.0f,
                        _potato_texture_01
                    )
                );
                break;
            case 1:
                _field_of_potatos.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        32.0f,
                        32.0f,
                        _potato_texture_02
                    )
                );
                break;
            case 2:
                _field_of_potatos.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        32.0f,
                        32.0f,
                        _potato_texture_03
                    )
                );
                break;
            case 3:
                _field_of_potatos.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        32.0f,
                        32.0f,
                        _potato_texture_04
                    )
                );
                break;
        }
    }

    gameLoop();
}

void MainGame::initSystem()
{
    Canis::Init();

    _window.create("Dual Defenders", _screenWidth, _screenHeight, 0);

    _camera.init(_screenWidth, _screenHeight);

    _gameState = GameState::PLAY;

    srand(time(NULL));

    initShaders();

    _spriteBatch.init();
    _fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("assets/shaders/DefaultShader.vert", "assets/shaders/DefaultShader.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY)
    {
        _fpsLimiter.begin();

        processInput();
        _camera.update();
        _time += 0.01f;
        drawGame();

        _fps = _fpsLimiter.end();

        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 1000)
        {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}

void MainGame::processInput()
{
    const float CAMERA_SPEED = 1.0f;
    const float SCALE_SPEED = 0.01f;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
        case SDL_MOUSEMOTION:
            break;
        case SDL_KEYUP:
            _inputManager.releasedKey(event.key.keysym.sym);
            break;
        case SDL_KEYDOWN:
            _inputManager.pressKey(event.key.keysym.sym);
            break;
        }
    }

    if (_inputManager.isKeyPressed(SDLK_ESCAPE))
    {
        _gameState = GameState::EXIT;
    }

    if (_inputManager.isKeyPressed(SDLK_w))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }

    if (_inputManager.isKeyPressed(SDLK_s))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }

    if (_inputManager.isKeyPressed(SDLK_a))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }

    if (_inputManager.isKeyPressed(SDLK_d))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }

    if (_inputManager.isKeyPressed(SDLK_q))
    {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }

    if (_inputManager.isKeyPressed(SDLK_e))
    {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }

    if (_inputManager.isKeyPressed(SDLK_UP))
    {
        _player_light.y++;
    }

    if (_inputManager.isKeyPressed(SDLK_DOWN))
    {
        _player_light.y--;
    }

    if (_inputManager.isKeyPressed(SDLK_RIGHT))
    {
        _player_light.x++;
    }

    if (_inputManager.isKeyPressed(SDLK_LEFT))
    {
        _player_light.x--;
    }
}

void MainGame::drawGame()
{

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();
    //glActiveTexture(GL_TEXTURE0);

    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    //GLuint timeLocation = _colorProgram.getUniformLocation("time");
    //glUniform1f(timeLocation, _time);

    // Set the camera matrix
    GLuint pLocation = _colorProgram.getUniformLocation("P");

    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));    

    glm::vec4 pos(0.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

    Canis::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    // Planet
    _spriteBatch.begin(Canis::GlyphSortType::FRONT_TO_BACK);
    // Planet
    _spriteBatch.draw(pos + glm::vec4(_planet.x, _planet.y, _planet.width, _planet.height), uv, _planet.texture, 4.0f, color);
    // Player
    _spriteBatch.draw(pos + glm::vec4(_player_light.x, _player_light.y, 32, 32), uv, _player_light.texture, 1.0f, color, glm::normalize(
        (glm::vec2(_planet.x, _planet.y) + glm::vec2(_planet.width/2,_planet.height/2))
        - (glm::vec2(_player_light.x, _player_light.y) + glm::vec2(_player_light.width/2,_player_light.height/2)))
    );
    // Health
    for (int i = 0; i < _current_health; i++)
    {
        _spriteBatch.draw(
            glm::vec4(_planet_health[i].x,_planet_health[i].y,_planet_health[i].width,_planet_health[i].height),
            uv,
            _planet_health[i].texture,
            0.0f,
            color
        );
    }
    // Potatos
    for (int i = 0; i < _field_of_potatos.size(); i++)
    {
        _spriteBatch.draw(
            glm::vec4(_field_of_potatos[i].x,_field_of_potatos[i].y,_field_of_potatos[i].width,_field_of_potatos[i].height),
            uv,
            _field_of_potatos[i].texture,
            3.0f,
            color
        );
    }
    // Bullet
    //_spriteBatch.draw(pos + glm::vec4(_player_pos.x + 8, _player_pos.y + 30, 4, 4), uv, _bullet_texture, 1.0f, color, glm::normalize(
    //    (_planet_pos + glm::vec2(64,64)) - (_player_pos + glm::vec2(16,16)))
    //);
    _spriteBatch.end();
    _spriteBatch.renderBatch();

    float x = 0.0f;
    float y = 0.0f;

    /*_spriteBatch.begin();

    for (int i = 0; i < 100; i++)
    {
        x = 1 + rand() % 800;
        y = 1 + rand() % 600;
        _spriteBatch.draw(pos + glm::vec4(x, y, 32.0f, 32.0f), uv, _potato_texture, 0.0f, color);
    }

    _spriteBatch.end();*/

    _spriteBatch.renderBatch();

    //glBindTexture(GL_TEXTURE_2D, 0);

    _colorProgram.unUse();

    _window.swapBuffer();
}

