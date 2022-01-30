#include "MainGame.hpp"

MainGame::MainGame() : _screenWidth(800), _screenHeight(600), _time(0), _gameState(GameState::PLAY), _maxFPS(30.0f)
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

    _planet.texture = _planet_texture;
    _planet.x = (_screenWidth/2.0f)-(_planet_texture.width/2.0f);
    _planet.y = (_screenHeight/2.0f)-(_planet_texture.height/2.0f);
    _planet.z = 4.0f;
    _planet.width = 128.0f;
    _planet.height = 128.0f;

    _player_light.texture = _player_light_texture;
    _player_light.x = (_screenWidth/2.0f)-(_player_light_texture.width/2.0f);
    _player_light.y = (_screenHeight/2.0f)-(_player_light_texture.height/2.0f) + 100.0f;
    _player_light.z = 1.0f;
    _player_light.width = 32.0f;
    _player_light.height = 32.0f;

    _player_light_index = setShipTop(&_player_light, &_planet);

    _player_heavy.texture = _player_heavy_texture;
    _player_heavy.x = (_screenWidth/2.0f)-(_player_heavy_texture.width/2.0f);
    _player_heavy.y = (_screenHeight/2.0f)-(_player_heavy_texture.height/2.0f) + 100.0f;
    _player_heavy.z = 1.0f;
    _player_heavy.width = 32.0f;
    _player_heavy.height = 32.0f;

    _player_heavy_index = setShipBottom(&_player_heavy, &_planet);

    for (int i = 0; i < _max_health; i++)
    {
        _planet_health.push_back(
            Entity(
                4.0f + ((64.0f + 4.0f) * i),
                _screenHeight - 64.0f - 4.0f,
                0.0f,
                64.0f,
                64.0f,
                _planet_health_texture
            )
        );
    }

    for (int i = 0; i < 2; i++)
    {
        int randomNumber = rand() % 4;

        switch(randomNumber)
        {
            case 0:
                _field_of_potatoes.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        3.0f,
                        32.0f,
                        32.0f,
                        _potato_texture_01
                    )
                );
                break;
            case 1:
                _field_of_potatoes.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        3.0f,
                        32.0f,
                        32.0f,
                        _potato_texture_02
                    )
                );
                break;
            case 2:
                _field_of_potatoes.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        3.0f,
                        32.0f,
                        32.0f,
                        _potato_texture_03
                    )
                );
                break;
            case 3:
                _field_of_potatoes.push_back(
                    Entity(
                        1 + rand() % _screenWidth,
                        1 + rand() % _screenHeight,
                        3.0f,
                        32.0f,
                        32.0f,
                        _potato_texture_04
                    )
                );
                break;
        }
    }

    for (int i = 0; i < _field_of_potatoes.size(); i++)
    {
        _field_of_potatoes[i].velocity = 5.0f;//((50 + rand() % 50) / 100) *  50.0f;

        resetPotato(&_field_of_potatoes[i],&_planet);

        /*_field_of_potatoes[i].direction = glm::normalize(
            (glm::vec2(_planet.x, _planet.y) + glm::vec2(_planet.width/2,_planet.height/2))
            - (glm::vec2(_field_of_potatoes[i].x, _field_of_potatoes[i].y) + glm::vec2(_field_of_potatoes[i].width/2,_field_of_potatoes[i].height/2))
        );*/
    }

    // load Bullets
    for (int i = 0; i < 1000; i++)
    {
        _bullets.push_back(
            Entity(
                -20.0f,
                -20.0f,
                1.0f,
                4.0f,
                4.0f,
                _bullet_texture
            )
        );
    }

    gameLoop();
}

void MainGame::initSystem()
{
    Canis::Init();

    _window.create("Dual Defenders", _screenWidth, _screenHeight, 0);

    _last_update = SDL_GetTicks();

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
        update();
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
        //_player_light.y++;
    }

    if (_inputManager.isKeyPressed(SDLK_DOWN))
    {
        //_player_light.y--;
    }

    if (_inputManager.isKeyPressed(SDLK_RIGHT))
    {
        _player_light_index = moveShip(&_player_light,&_planet, _player_light_index, 1);
        _player_heavy_index = moveShip(&_player_heavy,&_planet, _player_heavy_index, 1);
    }
    else if (_inputManager.isKeyPressed(SDLK_LEFT))
    {
        _player_light_index = moveShip(&_player_light,&_planet, _player_light_index, -1);
        _player_heavy_index = moveShip(&_player_heavy,&_planet, _player_heavy_index, -1);
    }

    if (_inputManager.isKeyPressed(SDLK_SPACE))
    {
        shootBullet(
            glm::vec2(_player_light.x,_player_light.y),
            5,
            -_player_light.direction,
            glm::vec2(4,4)
        );
        shootBullet(
            glm::vec2(_player_heavy.x,_player_heavy.y),
            5,
            -_player_heavy.direction,
            glm::vec2(8,8)
        );
    }
}

void MainGame::update()
{
    float current_ticks = SDL_GetTicks();
    _dt = current_ticks - _last_update;
    _last_update = current_ticks;

    // Move Potatoes
    for(int i = 0; i < _field_of_potatoes.size(); i++)
    {
        float x = 0;
        float y = 0;

        x = _field_of_potatoes[i].x;
        y = _field_of_potatoes[i].y;

        _field_of_potatoes[i].MoveWithDirection(_dt);
    }

    // Check for colition with planet
    for(int i = 0; i < _field_of_potatoes.size(); i++)
    {
        float kill_zone = _planet.width/2.0f;
        float distance = sqrtf(powf(((_planet.x+(_planet.width/2))-(_field_of_potatoes[i].x+(_field_of_potatoes[i].width/2))),2)
        +powf(((_planet.y+(_planet.height/2))-(_field_of_potatoes[i].y+(_field_of_potatoes[i].height/2))),2));

        if (kill_zone > distance)
        {
            // reset potato
            resetPotato(&_field_of_potatoes[i],&_planet);
            // damage planet
            if(_current_health > 0)
            {
                _current_health--;
                if (_current_health < 1)
                {
                    // Game Over Screen

                }
            }
        }
    }

    // Bullet
    for (int i = 0; i < _bullets.size(); i++)
    {
        _bullets[i].MoveWithDirection(_dt);
    }

    // Check Bullet collition
    checkBulletCollision();
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

    _spriteBatch.begin(Canis::GlyphSortType::FRONT_TO_BACK);
    // Planet
    _spriteBatch.draw(pos + glm::vec4(_planet.x, _planet.y, _planet.width, _planet.height), uv, _planet.texture, _planet.z, color);
    // Player
    _player_light.direction = glm::normalize(
        (glm::vec2(_planet.x, _planet.y) + glm::vec2(_planet.width/2,_planet.height/2))
        - (glm::vec2(_player_light.x, _player_light.y) + glm::vec2(_player_light.width/2,_player_light.height/2)));
    
    _spriteBatch.draw(pos + glm::vec4(_player_light.x, _player_light.y, 32, 32), uv, _player_light.texture, _player_light.z, color, _player_light.direction);

    _player_heavy.direction = glm::normalize(
        (glm::vec2(_planet.x, _planet.y) + glm::vec2(_planet.width/2,_planet.height/2))
        - (glm::vec2(_player_heavy.x, _player_heavy.y) + glm::vec2(_player_heavy.width/2,_player_heavy.height/2)));
    
    _spriteBatch.draw(pos + glm::vec4(_player_heavy.x, _player_heavy.y, 32, 32), uv, _player_heavy.texture, _player_heavy.z, color, _player_heavy.direction);
    // Health
    if (_current_health > 0)
    {
        for (int i = 0; i < _current_health; i++)
        {
            _spriteBatch.draw(
                glm::vec4(_planet_health[i].x,_planet_health[i].y,_planet_health[i].width,_planet_health[i].height),
                uv,
                _planet_health[i].texture,
                _planet_health[i].z,
                color
            );
        }
    }
    // Potatos
    for (int i = 0; i < _field_of_potatoes.size(); i++)
    {
        _spriteBatch.draw(
            glm::vec4(_field_of_potatoes[i].x,_field_of_potatoes[i].y,_field_of_potatoes[i].width,_field_of_potatoes[i].height),
            uv,
            _field_of_potatoes[i].texture,
            _field_of_potatoes[i].z,
            color
        );
    }
    // Bullet
    for (int i = 0; i < _bullets.size(); i++)
    {
        _spriteBatch.draw(
            glm::vec4(_bullets[i].x,_bullets[i].y,_bullets[i].width,_bullets[i].height),
            uv,
            _bullets[i].texture,
            _bullets[i].z,
            color
        );
    }

    _spriteBatch.end();
    _spriteBatch.renderBatch();

    _colorProgram.unUse();

    _window.swapBuffer();
}

void MainGame::resetPotato(Entity *potato, Entity *planet)
{
    // reset position
    int zone = rand() % 4;

    potato->x = 1 + rand() % _screenWidth;
    potato->y = 1 + rand() % _screenHeight;

    switch (zone)
    {
    case 0: // UP
        potato->y += _screenHeight;
        break;
    case 1: // DOWN
        potato->y -= _screenHeight;
        break;
    case 2: // RIGHT
        potato->x += _screenWidth;
        break;
    case 3: // LEFT
        potato->x -= _screenWidth;
        break;
    }

    // get new direction
    potato->direction = glm::normalize(
        (glm::vec2(planet->x, planet->y) + glm::vec2(planet->width/2,planet->height/2))
        - (glm::vec2(potato->x, potato->y) + glm::vec2(potato->width/2,potato->height/2))
    );
}

int MainGame::setShipTop(Entity *ship, Entity *planet)
{

    return moveShip(ship,planet,4,0);
}

int MainGame::setShipBottom(Entity *ship, Entity *planet)
{
    return moveShip(ship,planet,12,0);
}

int MainGame::moveShip(Entity *ship, Entity *planet, int index, int direction)
{
    
    if (direction == -1 && index == 0)
    {
        index = _orbits.size() - 1;
    }
    else
    {
        index += direction;

        if (index >= _orbits.size())
            index = 0;
    }
    
    Canis::Log(std::to_string(index));

    float radius = (planet->width/2) + 64;

    glm::vec2 new_position((_orbits[index]*radius));

    ship->x = new_position.x + (planet->x + (planet->width/2) - (ship->width/2));
    ship->y = new_position.y + (planet->y + (planet->width/2) - (ship->width/2));

    return index;
}

void MainGame::shootBullet(glm::vec2 position, float velocity, glm::vec2 direction, glm::vec2 size)
{
    _bullets[_bullet_index].x = position.x;
    _bullets[_bullet_index].y = position.y;
    _bullets[_bullet_index].width = size.x;
    _bullets[_bullet_index].height = size.y;
    _bullets[_bullet_index].velocity = velocity;
    _bullets[_bullet_index].direction = direction;

    _bullet_index++;

    if (_bullet_index >= _bullets.size())
        _bullet_index = 0;
}

void MainGame::checkBulletCollision()
{
    for (int i = 0; i < _bullets.size(); i++)
    {
        for(int p = 0; p < _field_of_potatoes.size(); p++)
        {
            if(checkCollision(_bullets[i],_field_of_potatoes[p]))
            {
                Canis::Log("HITTTTTTTTTTTTTT");
                resetPotato(&_field_of_potatoes[p],&_planet);
            }
        }
    }
}

bool MainGame::checkCollision(Entity &one, Entity &two)
{
    bool collisionX = one.x + one.width >= two.x &&
        two.x + two.width >= one.x;
    
    bool collisionY = one.y + one.height >= two.y &&
        two.y + two.height >= one.y;
    
    return collisionX && collisionY;
}
