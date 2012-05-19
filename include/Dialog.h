#ifndef DIALOG_H
#define	DIALOG_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>

class Dialog {
public:
    Dialog(sf::RenderWindow *refwindow, sf::String rTitle, sf::String rMessage);
    virtual ~Dialog();

    int run();



private:

    sf::Image dialog_image;
    sf::Sprite dialog_sprite;

    sf::RenderWindow* _window;
    sf::Font Font;
    sf::String Title;
    sf::String Message;
};

#endif	/* DIALOG_H */

