#ifndef Menu
#define Menu_h
#include"Libraries.h"
using namespace sf;
using namespace std;
class Menu {
private:
    Font font;
    Text text[5];
    int option = 1;
public:

    //add menu attributes here
    Menu() {};
    void InitialMenu() {
        if (!font.loadFromFile("f1.ttf")) {
            cout << "Error Loading File" << endl;
        }
        else {
            text[0].setFont(font);
            text[0].setFillColor(Color::Cyan);
            text[0].setString("Enchanted Labyrinth Explorer");
            text[0].setCharacterSize(80);
            text[0].setPosition(175, 50);

            text[1].setFont(font);
            text[1].setFillColor(Color::Red);
            text[1].setString("Start Game");
            text[1].setCharacterSize(60);
            text[1].setPosition(400, 250);

            text[2].setFont(font);
            text[2].setFillColor(Color::White);
            text[2].setString("High Score");
            text[2].setCharacterSize(60);
            text[2].setPosition(400, 400);

            text[3].setFont(font);
            text[3].setFillColor(Color::White);
            text[3].setString("Help");
            text[3].setCharacterSize(60);
            text[3].setPosition(400, 550);

            text[4].setFont(font);
            text[4].setFillColor(Color::White);
            text[4].setString("Exit");
            text[4].setCharacterSize(60);
            text[4].setPosition(400, 700);
        }

    }

    void up() {
        if (option - 1 != 0) {
            text[option].setFillColor(Color::White);
            option--;
            text[option].setFillColor(Color::Red);
        }
        else {
            text[option].setFillColor(Color::White);
            option = 4;
            text[option].setFillColor(Color::Red);
        }
    }
    void down() {
        if (option + 1 != 5) {
            text[option].setFillColor(Color::White);
            option++;
            text[option].setFillColor(Color::Red);
        }
        else {
            text[option].setFillColor(Color::White);
            option = 1;
            text[option].setFillColor(Color::Red);
        }
    }

    void DisplayMenu(RenderWindow& window) {
        for (int i = 0; i < 5; i++) {
            window.draw(text[i]);
        }
    }

    void display_menu(){
        Sprite background; // Game background sprite
        Texture bg_texture;
        bg_texture.loadFromFile("images\\background.jpg");
        background.setTexture(bg_texture);
        RenderWindow window(VideoMode(1400, 800), "Menu");
        background.setScale(
            static_cast<float>(window.getSize().x) / bg_texture.getSize().x,
            static_cast<float>(window.getSize().y) / bg_texture.getSize().y
        );
        InitialMenu();
        while (window.isOpen()) {
            Event e;
            bool flag = true;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
                if (e.type == Event::KeyReleased) {
                    if (e.key.code == Keyboard::Up) {
                        up();
                    }
                    else if (e.key.code == Keyboard::Down) {
                        down();
                    }
                    else if (e.key.code == Keyboard::Return) {
                        if (option == 1) {
                            window.clear(Color::White);
                            Game g;
                            window.close();
                            g.play();
                        }
                        else if (option == 4) {
                            window.close();
                        }

                    }
                }
            }
            window.clear(Color::Black);
            window.draw(background);
            DisplayMenu(window);
            window.display();
        }
    }
};
#endif //