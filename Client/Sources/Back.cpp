/*
** EPITECH PROJECT, 2024
** ncurses.hpp
** File description:
** ncurses.hpp
*/

#include "../Include/Back.hpp"

void write_text(sf::RenderWindow& window, const std::string& text, const sf::Color& color, float x, float y, sf::Font font)
{
    sf::Text detText;
    detText.setFont(font);
    detText.setString(text);
    detText.setCharacterSize(30);
    detText.setFillColor(color);
    detText.setPosition(x, y);
    window.draw(detText);
}

void Bombshells::launch_bombs(float time) {
    bomb.launch_bombs(time);
    sprite_b.move(bomb.x_bombs, 0);
}

void Enemy::make_appear_and_move_opponent(float time) {
    enem.enemy_move_left(time);
    sprite.setPosition(enem.x_ennemie, enem.y_ennemie);
}

int play_game(const std::string& username)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-type parcours");

    const int numImages = 5;
    std::vector<sf::Texture> textures(numImages);
    std::vector<sf::Sprite> sprites(numImages);
    std::vector<std::string> imagePaths = {
        "Client/sprites/start_niveau.png", "Client/sprites/niveau1.png", 
        "Client/sprites/niveau3.png", "Client/sprites/niveau2.png",
        "Client/sprites/Space.png"
    };

    for (int i = 0; i < numImages; ++i)
    {
        if (!textures[i].loadFromFile(imagePaths[i]))
        {
            return -1;
        }
        sprites[i].setTexture(textures[i]);
        sprites[i].setScale(3.1f, 3.1f);
        sprites[i].setPosition(i * textures[i].getSize().x * 1.7f, 0);
    }

    sf::Texture shipTexture;
    if (!shipTexture.loadFromFile("Client/sprites/vaisseau1.png"))
    {
        return -1;
    }
    sf::Sprite shipSprite(shipTexture);
    shipSprite.setScale(0.5f, 0.5f);
    shipSprite.setPosition(100, 540);

    sf::Texture bombTexture;
    if (!bombTexture.loadFromFile("./Client/sprites/rocket.png"))
    {
        return -1;
    }

    sf::Sprite sprite_boss;
    sf::Texture boss_texture;
    if (!boss_texture.loadFromFile("./Client/sprites/scorpio.png")) // Hoda, met le sprite du gros ennemi ici!
    {
        return -1;
    }
    sprite_boss.setTexture(boss_texture);

    sf::SoundBuffer bombBuffer;
    if (!bombBuffer.loadFromFile("Client/sprites/assets_laser.wav"))
    {
        return -1;
    }
    sf::Font font;
    if (!font.loadFromFile("Client/sprites/Banana_Summer.otf")) {
        return -1;
    }
    sf::Sound bombSound;
    bombSound.setBuffer(bombBuffer);

    sf::SoundBuffer backgroundBuffer;
    if (!backgroundBuffer.loadFromFile("Client/sprites/back.wav"))
    {
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(backgroundBuffer);
    sound.setLoop(true);
    sound.play();

    float scrollSpeed = 500.0f;
    float shipSpeed = 200.0f;

    std::vector<Bombshells> bombs;

    sf::Texture enemyTexture1, enemyTexture2;
    if (!enemyTexture1.loadFromFile("./Client/sprites/opponents.png") ||
        !enemyTexture2.loadFromFile("assets/r-typesheet7.gif"))
    {
        return -1;
    }
    std::vector<Enemy> enemies;

    sf::Clock enemyClock;
    float time_pop_enem = 2.0f;

    int score = 0;
    int appearing_ennemy = 0;
    sf::Clock clock;
    Space_Ship ship;
    Manage_bombs bmb;
    Opponent enem;
    const float time_bomb = 1.5f;
    sf::Clock time_is_up;
    std::string tab = ship.read_file_score();
    sf::Vector2f bomb_pos;
    sf::Vector2f enemy_pos;
    sf::FloatRect bomb_size;
    sf::FloatRect enemy_size;
    sf::FloatRect ship_size;
    bool check = false;
    bool fight_boss = false;
    Boss_enemy boss;
    sf::FloatRect boss_size;
    std::string defeat_boss = "";

   

    while (window.isOpen())
    {
        score += 1;
        if (score == 1000) {
            printf("papa\n");
            appearing_ennemy = 1;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                if (score > ship.high_score) {
                    ship.high_score = score;
                    ship.write_file_score();
                }
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ship.move_left(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ship.move_right(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ship.move_up(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ship.move_down(deltaTime);
        shipSprite.setPosition(ship.x_ship, ship.y_ship);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && time_is_up.getElapsedTime().asSeconds() >= time_bomb) {
            bombs.emplace_back(bombTexture, ship.x_ship, ship.y_ship);
            bombSound.play();
        }
        
        for (auto& bomb : bombs)
        {
            bomb.launch_bombs(deltaTime);
        }
        
        if (enemyClock.getElapsedTime().asSeconds() > time_pop_enem)
        {
            enemies.emplace_back(enemyTexture1);
            enemyClock.restart();
        }
        
        ship_size = shipSprite.getGlobalBounds();

        for (auto& enemy : enemies)
        {
            enemy_pos = enemy.sprite.getPosition();
            enemy_size = enemy.sprite.getGlobalBounds();
            enemy.sprite.setScale(0.5f, 0.5f);
            enemy.make_appear_and_move_opponent(deltaTime);
            if (ship.destroy_ship(ship.x_ship + 100, ship.y_ship, ship_size.width, ship_size.height,
                enemy_pos.x, enemy_pos.y, enemy_size.width - 220, enemy_size.height - 120)) {
                    // printf("x: %lf y: %lf", enemy_size.width - 220, enemy_size.height - 100);
                    check = true;
            }

        }

        if (check) {
            check = false;
            std::cout << "Game Over!" << std::endl;
            break;
        }

        for (int i = 0; i < bombs.size(); i++) {
            bomb_pos = bombs[i].sprite_b.getPosition();
            bomb_size = bombs[i].sprite_b.getGlobalBounds();
            for (int j = 0; j < enemies.size(); j++) {
                enemy_pos = enemies[j].sprite.getPosition();
                enemy_size = enemies[j].sprite.getGlobalBounds();
                if (bmb.destroy_opponent(bomb_pos.x, bomb_pos.y, bomb_size.width, bomb_size.height,
                    enemy_pos.x, enemy_pos.y, enemy_size.width - 220, enemy_size.height - 120)) {
                    // printf("x: %lf y: %lf", enemy_size.width - 220, enemy_size.height - 120);
                    bombs.erase(bombs.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    break;
                }
            }
        }

        for (int i = 0; i < numImages; ++i)
        {
            sprites[i].move(-scrollSpeed * deltaTime, 0);
            if (sprites[i].getPosition().x + textures[i].getSize().x * 1.7f < 0)
            {
                int lastSpriteIndex = (i == 0) ? numImages - 1 : i - 1;
                float newPosX = sprites[lastSpriteIndex].getPosition().x + textures[lastSpriteIndex].getSize().x * 1.7f;
                sprites[i].setPosition(newPosX, 0);
            }
        }


        window.clear();
        for (int i = 0; i < numImages; ++i)
        {
            window.draw(sprites[i]);
        }
        window.draw(shipSprite);
        write_text(window, "HIGHER SCORE = ", sf::Color::Blue, 800, 800, font);
        write_text(window, tab, sf::Color::Blue, 1080, 800, font);
        write_text(window, "P1 - 5HP", sf::Color::Blue, 100, 800, font);
        write_text(window, "P2 - 5HP", sf::Color::Blue, 100, 850, font);
        write_text(window, "P3 - Disconnected", sf::Color::Blue, 100, 900, font);
        write_text(window, "P4 - Disconnected", sf::Color::Blue, 100, 950, font);
        write_text(window, "Username: " + username, sf::Color::Blue, 1200, 800, font);

        for (const Bombshells& bomb : bombs)
        {
            window.draw(bomb.sprite_b);
        }

        for (const Enemy& enemy : enemies)
        {
            window.draw(enemy.sprite);
        }

        if (appearing_ennemy == 1) {
                sprite_boss.setPosition(1150, 0);
                boss_size = sprite_boss.getGlobalBounds();
                window.draw(sprite_boss);
                fight_boss = boss.destroy_boss(bomb_pos.x, bomb_pos.y, bomb_size.width, bomb_size.height,
                    1150, 0, boss_size.width, boss_size.height);
                defeat_boss = boss.decrease_pv(fight_boss);
                if (defeat_boss != "") {
                    appearing_ennemy = 0;
                    write_text(window, defeat_boss, sf::Color::Blue, 600, 300, font);
                }
        }

        window.display();
    }
    return (0);
}

// int play_game(const std::string& username)
// {
//     sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-type parcours");

//     const int numImages = 5;
//     std::vector<sf::Texture> textures(numImages);
//     std::vector<sf::Sprite> sprites(numImages);
//     std::vector<std::string> imagePaths = {
//         "Client/sprites/start_niveau.png", "Client/sprites/niveau1.png", 
//         "Client/sprites/niveau3.png", "Client/sprites/niveau2.png", 
//         "Client/sprites/Space.png"
//     };

//     for (int i = 0; i < numImages; ++i)
//     {
//         if (!textures[i].loadFromFile(imagePaths[i]))
//         {
//             return -1;
//         }
//         sprites[i].setTexture(textures[i]);
        
//         sprites[i].setScale(3.1f, 3.1f);
        
//         sprites[i].setPosition(i * textures[i].getSize().x * 1.7f, 0);
//     }

//     sf::Texture shipTexture;
//     if (!shipTexture.loadFromFile("Client/sprites/vaisseau2.png"))
//     {
//         return -1;
//     }
//     sf::Sprite shipSprite(shipTexture);
    
//     shipSprite.setScale(0.5f, 0.5f);
//     shipSprite.setPosition(100, 540);

//     sf::Texture bombTexture;
//     if (!bombTexture.loadFromFile("assets/r-typesheet3.gif"))
//     {
//         return -1;
//     }

//     sf::SoundBuffer bombBuffer;
//     if (!bombBuffer.loadFromFile("Client/sprites/assets_laser.wav"))
//     {
//         return -1;
//     }
//     sf::Font font;
//     if (!font.loadFromFile("Client/sprites/Banana_Summer.otf")) {
//         return -1;
//     }
//     sf::Sound bombSound;
//     bombSound.setBuffer(bombBuffer);

//     sf::SoundBuffer backgroundBuffer;
//     if (!backgroundBuffer.loadFromFile("Client/sprites/back.wav"))
//     {
//         return -1;
//     }

//     sf::Sound sound;
//     sound.setBuffer(backgroundBuffer);
//     sound.setLoop(true);
//     sound.play();

//     float scrollSpeed = 500.0f;
//     float shipSpeed = 200.0f;

//     std::vector<Bombshells> bombs;

//     sf::Clock clock;
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         float deltaTime = clock.restart().asSeconds();

//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//             shipSprite.move(-shipSpeed * deltaTime, 0);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//             shipSprite.move(shipSpeed * deltaTime, 0);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//             shipSprite.move(0, -shipSpeed * deltaTime);
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//             shipSprite.move(0, shipSpeed * deltaTime);

//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
//         {
//             bombs.emplace_back(bombTexture, shipSprite.getPosition().x + shipSprite.getGlobalBounds().width / 2 - 10, shipSprite.getPosition().y);
//             bombSound.play();
//         }

//         for (size_t i = 0; i < bombs.size();)
//         {
//             bombs[i].update(deltaTime);
//             if (bombs[i].isOffScreen())
//             {
//                 bombs.erase(bombs.begin() + i);
//             }
//             else
//             {
//                 ++i;
//             }
//         }

//         for (int i = 0; i < numImages; ++i)
//         {
//             sprites[i].move(-scrollSpeed * deltaTime, 0);
//             if (sprites[i].getPosition().x + textures[i].getSize().x * 1.7f < 0)
//             {
//                 int lastSpriteIndex = (i == 0) ? numImages - 1 : i - 1;
//                 float newPosX = sprites[lastSpriteIndex].getPosition().x + textures[lastSpriteIndex].getSize().x * 1.7f;
//                 sprites[i].setPosition(newPosX, 0);
//             }
//         }

//         window.clear();
//         for (int i = 0; i < numImages; ++i)
//         {
//             window.draw(sprites[i]);
//         }
//         window.draw(shipSprite);
//         write_text(window, "SCORE = 12", sf::Color::Blue, 800, 800, font);
//         write_text(window, "P1 - 5HP", sf::Color::Blue, 100, 800, font);
//         write_text(window, "P2 - 5HP", sf::Color::Blue, 100, 850, font);
//         write_text(window, "P3 - Disconnected", sf::Color::Blue, 100, 900, font);
//         write_text(window, "P4 - Disconnected", sf::Color::Blue, 100, 950, font);
//         write_text(window, "Username: " + username, sf::Color::Blue, 1200, 800, font);
//         for (const Bombshells& bomb : bombs)
//         {
//             window.draw(bomb.sprite_b);
//         }

//         window.display();
//     }

//     return 0;
// }