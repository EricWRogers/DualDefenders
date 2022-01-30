#include "MainGame.hpp"

MainGame::MainGame() : _screenWidth(1280), _screenHeight(720), _time(0), _gameState(GameState::PLAY), _maxFPS(30.0f)
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

    // UI
    _team_and_engine_screen = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/LogoScreen.png");
    _global_game_jam_screen = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/GGJScreen.png");
    _title_screen = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/TitleScreen.png");
    _controls_screen = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Controls.png");
    _game_over_screen = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/GameOver.png");

    _team_and_engine.texture = _team_and_engine_screen;
    _team_and_engine.x = 0.0f;
    _team_and_engine.y = 0.0f;
    _team_and_engine.z = -2.0f;
    _team_and_engine.width = _team_and_engine_screen.width;
    _team_and_engine.height = _team_and_engine_screen.height;

    _global_game_jam.texture = _global_game_jam_screen;
    _global_game_jam.x = 0.0f;
    _global_game_jam.y = 0.0f;
    _global_game_jam.z = -2.0f;
    _global_game_jam.width = _global_game_jam_screen.width;
    _global_game_jam.height = _global_game_jam_screen.height;

    _title.texture = _title_screen;
    _title.x = 0.0f;
    _title.y = 0.0f;
    _title.z = -2.0f;
    _title.width = _title_screen.width;
    _title.height = _title_screen.height;

    _controls.texture = _controls_screen;
    _controls.x = 0.0f;
    _controls.y = 0.0f;
    _controls.z = -2.0f;
    _controls.width = _controls_screen.width;
    _controls.height = _controls_screen.height;

    _game_over.texture = _game_over_screen;
    _game_over.x = 0.0f;
    _game_over.y = 0.0f;
    _game_over.z = -2.0f;
    _game_over.width = _game_over_screen.width;
    _game_over.height = _game_over_screen.height;
    
    // Game Play Textures
    _player_light_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/DefaultShip.png");
    _player_heavy_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/DefaultShip2.png");
    _planet_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Planet.png");
    _planet_health_texture = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Health.png");
    _potato_texture_01 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid1.png");
    _potato_texture_02 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid2.png");
    _potato_texture_03 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid3.png");
    _potato_texture_04 = Canis::ResourceManager::getTexture("assets/textures/DualDefenders/Asteroid4.png");
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

    _player_light_angle = setShipTop(&_player_light, &_planet);

    _player_heavy.texture = _player_heavy_texture;
    _player_heavy.x = (_screenWidth/2.0f)-(_player_heavy_texture.width/2.0f);
    _player_heavy.y = (_screenHeight/2.0f)-(_player_heavy_texture.height/2.0f) + 100.0f;
    _player_heavy.z = 1.0f;
    _player_heavy.width = 32.0f;
    _player_heavy.height = 32.0f;

    _player_heavy_angle = setShipBottom(&_player_heavy, &_planet);

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

    for (int i = 0; i < 8; i++)
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
    while (_gameState != GameState::EXIT)
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
    std::string game_state_message = "";

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

    switch (_gameState)
    {
    case GameState::PLAY:
        game_state_message = "PLAY";
        break;
    case GameState::STUDIO:
        game_state_message = "STUDIO";
        break;
    case GameState::GAMEJAM:
        game_state_message = "GAMEJAM";
        break;
    case GameState::TITLE:
        game_state_message = "TITLE";
        break;
    case GameState::CONTROLS:
        game_state_message = "CONTROLS";
        score = 0;
        _window.setWindowName("Dual Defenders");
        break;
    case GameState::GAME:
        game_state_message = "GAME";
        score++;
        _window.setWindowName("Dual Defenders : (Score : " + std::to_string(score) + ")");
        break;
    case GameState::GAMEOVER:
        game_state_message = "GAMEOVER";
        break;
    case GameState::EXIT:
        game_state_message = "EXIT";
        break;
    }

    /*if (_inputManager.isKeyPressed(SDLK_w))
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
    }*/

    if (_gameState == GameState::GAME)
    {
        if (_inputManager.isKeyPressed(SDLK_RIGHT))
        {
            _player_light_angle = moveShip(&_player_light,&_planet, _player_light_angle, _ship_speed);
            _player_heavy_angle = moveShip(&_player_heavy,&_planet, _player_heavy_angle, _ship_speed);
        }
        else if (_inputManager.isKeyPressed(SDLK_LEFT))
        {
            _player_light_angle = moveShip(&_player_light,&_planet, _player_light_angle, -_ship_speed);
            _player_heavy_angle = moveShip(&_player_heavy,&_planet, _player_heavy_angle, -_ship_speed);
        }
        else if (_inputManager.isKeyPressed(SDLK_a))
        {
            _player_light_angle = moveShip(&_player_light,&_planet, _player_light_angle, -_ship_speed);
            _player_heavy_angle = moveShip(&_player_heavy,&_planet, _player_heavy_angle, -_ship_speed);
        }

        else if (_inputManager.isKeyPressed(SDLK_d))
        {
            _player_light_angle = moveShip(&_player_light,&_planet, _player_light_angle, _ship_speed);
            _player_heavy_angle = moveShip(&_player_heavy,&_planet, _player_heavy_angle, _ship_speed);
        }

        if (_inputManager.isKeyPressed(SDLK_SPACE))
        {
            shooting_wait--;
            if (shooting_wait<=0)
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

                shooting_wait = max_shooting_wait;
            }
        }

        space_was_down = _inputManager.isKeyPressed(SDLK_SPACE);
    }

    if (_inputManager.isKeyPressed(SDLK_RETURN) && !enter_was_down)
    {
        if (_gameState != GameState::GAME)
        {
            change_state = true;
        }
    }

    enter_was_down = _inputManager.isKeyPressed(SDLK_RETURN);

    if (_inputManager.isKeyPressed(SDLK_TAB) && !tab_was_down)
    {
        if (_maxFPS == 30)
        {
            _fpsLimiter.setTargetFPS(10000);
            _maxFPS = 10000;
        }
        else
        {
            _maxFPS = 30;
            _fpsLimiter.setTargetFPS(30);
        }
    }

    tab_was_down = _inputManager.isKeyPressed(SDLK_TAB);
}

void MainGame::update()
{
    float current_ticks = SDL_GetTicks();
    _dt = current_ticks - _last_update;
    _last_update = current_ticks;

    switch (_gameState)
    {
    case GameState::PLAY:
        _gameState = GameState::STUDIO;
        change_state = false;
        break;
    case GameState::STUDIO:
        if (change_state)
        {
            _gameState = GameState::GAMEJAM;
            change_state = false;
        }
        break;
    case GameState::GAMEJAM:
        if (change_state)
        {
            _gameState = GameState::TITLE;
            change_state = false;
        }
        break;
    case GameState::TITLE:
        if (change_state)
        {
            _gameState = GameState::CONTROLS;
            change_state = false;

            _current_health = _max_health;

            for (int i = 0; i < _field_of_potatoes.size(); i++)
            {
                resetPotato(&_field_of_potatoes[i],&_planet);
            }

            for (int i = 0; i < _bullets.size(); i++)
            {
                _bullets[i].x = -20.0f;
                _bullets[i].y = -20.0f;
                _bullets[i].direction = glm::vec2(0.0f,0.0f);
            }
        }
        break;
    case GameState::CONTROLS:
        if (change_state)
        {
            _gameState = GameState::GAME;
            change_state = false;
        }
        break;
    case GameState::GAME:
        if (change_state)
        {
            _gameState = GameState::GAMEOVER;
            change_state = false;
        }
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
                        _gameState = GameState::GAMEOVER;
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
        break;
    case GameState::GAMEOVER:
        if (change_state)
        {
            _gameState = GameState::TITLE;
            change_state = false;
        }
        break;
    case GameState::EXIT:
        break;
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

    _spriteBatch.begin(Canis::GlyphSortType::FRONT_TO_BACK);

    switch (_gameState)
    {
    case GameState::PLAY:
        break;
    case GameState::STUDIO:
        _spriteBatch.draw(pos + glm::vec4(_team_and_engine.x, _team_and_engine.y, _team_and_engine.width, _team_and_engine.height), uv, _team_and_engine.texture, _team_and_engine.z, color);
        break;
    case GameState::GAMEJAM:
        _spriteBatch.draw(pos + glm::vec4(_global_game_jam.x, _global_game_jam.y, _global_game_jam.width, _global_game_jam.height), uv, _global_game_jam.texture, _global_game_jam.z, color);
        break;
    case GameState::TITLE:
        _spriteBatch.draw(pos + glm::vec4(_title.x, _title.y, _title.width, _title.height), uv, _title.texture, _title.z, color);
        break;
    case GameState::CONTROLS:
        _spriteBatch.draw(pos + glm::vec4(_controls.x, _controls.y, _controls.width, _controls.height), uv, _controls.texture, _controls.z, color);
        break;
    case GameState::GAME:
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
        break;
    case GameState::GAMEOVER:
        _spriteBatch.draw(pos + glm::vec4(_game_over.x, _game_over.y, _game_over.width, _game_over.height), uv, _game_over.texture, _game_over.z, color);
        break;
    case GameState::EXIT:
        break;
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

float MainGame::setShipTop(Entity *ship, Entity *planet)
{

    return moveShip(ship,planet,90,0);
}

float MainGame::setShipBottom(Entity *ship, Entity *planet)
{
    return moveShip(ship,planet,270,0);
}

float MainGame::moveShip(Entity *ship, Entity *planet, float angle, float direction)
{

    if (direction < 0 && angle <= 0.0f)
    {
        angle = 360.0f;
    }
    else
    {
        angle += direction;

        if (angle >= 360.0f)
            angle = 0.0f;
    }

    float radius = (planet->width/2) + 64;

    float pi = 3.14159265359;

    float rad = (angle * (pi / 180));

    glm::vec2 new_position(
        radius * cosf(rad),
        radius * sinf(rad)
    );

    ship->x = new_position.x + (planet->x + (planet->width/2) - (ship->width/2));
    ship->y = new_position.y + (planet->y + (planet->width/2) - (ship->width/2));

    

    return angle;
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
                resetPotato(&_field_of_potatoes[p],&_planet);
                score+=50;
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
