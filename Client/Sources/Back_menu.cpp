/*
** EPITECH PROJECT, 2024
** ncurses.hpp
** File description:
** ncurses.hpp
*/

#include "../Include/Back.hpp"

int play_game(const std::string& username);
void write_text(sf::RenderWindow& window, const std::string& text, const sf::Color& color, float x, float y, sf::Font font);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-type menu");

    sf::Texture menuTexture, settingsTexture, aideTexture, homeTexture;
    sf::Sprite menuSprite, settingsSprite, aideSprite, homeSprite;

    if (!menuTexture.loadFromFile("Client/sprites/img_menu.jpg") ||
        !settingsTexture.loadFromFile("Client/sprites/setting1.jpg") ||
        !aideTexture.loadFromFile("Client/sprites/help_game.png") ||
        !homeTexture.loadFromFile("Client/sprites/img_menu.jpg")) {
        return -1;
    }

    menuSprite.setTexture(menuTexture);
    settingsSprite.setTexture(settingsTexture);
    settingsSprite.setScale(4.0f, 3.5f);
    aideSprite.setTexture(aideTexture);
    homeSprite.setTexture(homeTexture);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Client/sprites/assets_menu.wav")) {
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();

    sf::Font font, font1;
    if (!font.loadFromFile("Client/sprites/Banana_Summer.otf") ||
        !font1.loadFromFile("Client/sprites/hHare.ttf")) {
        return -1;
    }

    sf::Text detText, playText, settingsText, logT;
    detText.setFont(font);
    detText.setString("Details :");
    detText.setCharacterSize(20);
    detText.setFillColor(sf::Color::Blue);
    detText.setPosition(25, 500);

    playText.setFont(font);
    playText.setString("Press Enter to play game");
    playText.setCharacterSize(20);
    playText.setFillColor(sf::Color::Blue);
    playText.setPosition(25, 550);

    settingsText.setFont(font);
    settingsText.setString("Press P to access settings");
    settingsText.setCharacterSize(20);
    settingsText.setFillColor(sf::Color::Blue);
    settingsText.setPosition(25, 600);

    logT.setFont(font);
    logT.setString("Sign in :)");
    logT.setCharacterSize(20);
    logT.setFillColor(sf::Color::Blue);
    logT.setPosition(25, 675);

    std::string username, password;
    bool usernameFocused = false, passwordFocused = false;

    sf::Text usernamePlaceholder("Username", font, 25);
    sf::Text passwordPlaceholder("Password", font, 25);
    sf::Text usernameText("", font, 25);
    sf::Text passwordText("", font, 25);
    
    usernamePlaceholder.setPosition(25, 700);
    passwordPlaceholder.setPosition(25, 800);
    usernameText.setPosition(55, 755);
    passwordText.setPosition(55, 855);

    usernamePlaceholder.setFillColor(sf::Color::White);
    passwordPlaceholder.setFillColor(sf::Color::White);
    usernameText.setFillColor(sf::Color::White);
    passwordText.setFillColor(sf::Color::White);

    sf::RectangleShape usernameBox(sf::Vector2f(300, 40));
    sf::RectangleShape passwordBox(sf::Vector2f(300, 40));
    usernameBox.setPosition(50, 750);
    passwordBox.setPosition(50, 850);
    usernameBox.setFillColor(sf::Color(50, 50, 50));
    passwordBox.setFillColor(sf::Color(50, 50, 50));

    bool showingMenu = true;
    bool showingAidE = false, showingHome = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (usernameBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    usernameFocused = true;
                    passwordFocused = false;
                } else if (passwordBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    passwordFocused = true;
                    usernameFocused = false;
                } else {
                    usernameFocused = false;
                    passwordFocused = false;
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (usernameFocused && event.text.unicode < 128) {
                    if (event.text.unicode == 8) {
                        if (!username.empty())
                            username.pop_back();
                    } else {
                        username += static_cast<char>(event.text.unicode);
                    }
                } else if (passwordFocused && event.text.unicode < 128) {
                    if (event.text.unicode == 8) {
                        if (!password.empty())
                            password.pop_back();
                    } else {
                        password += static_cast<char>(event.text.unicode);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter)
                    play_game(username);

                if (event.key.code == sf::Keyboard::P)
                    showingMenu = !showingMenu;

                if (event.key.code == sf::Keyboard::S) {
                    if (sound.getStatus() == sf::Sound::Playing) {
                        sound.pause();
                    } else if (sound.getStatus() == sf::Sound::Paused) {
                        sound.play();
                    }
                }

                if (event.key.code == sf::Keyboard::E) {
                    showingAidE = true;
                    showingHome = false;
                }

                if (event.key.code == sf::Keyboard::H) {
                    showingHome = true;
                    showingAidE = false;
                }
            }
        }

        window.clear();
        if (showingMenu) {
            window.draw(menuSprite);
            window.draw(detText);
            window.draw(playText);
            window.draw(settingsText);
            window.draw(logT);
            window.draw(usernameBox);
            window.draw(passwordBox);
            
            if (username.empty() && !usernameFocused)
                window.draw(usernamePlaceholder);
            else
                usernameText.setString(username);

            if (password.empty() && !passwordFocused)
                window.draw(passwordPlaceholder);
            else
                passwordText.setString(std::string(password.length(), '*'));

            window.draw(usernameText);
            window.draw(passwordText);

        } else {
            window.draw(settingsSprite);
            write_text(window, "PRESS C FOR", sf::Color::White, 572, 231, font1);
            write_text(window, "PRESS S FOR", sf::Color::White, 683, 377, font1);
            write_text(window, "PRESS E FOR", sf::Color::White, 681, 511, font1);
            write_text(window, "PRESS R FOR", sf::Color::White, 635, 659, font1);
            write_text(window, "PRESS H FOR", sf::Color::White, 830, 762, font1);

            if (showingAidE) {
                window.draw(aideSprite);
            }
            if (showingHome) {
                window.draw(homeSprite);
            }
        }

        window.display();
    }

    return 0;
}
