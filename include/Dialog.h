#ifndef DIALOG_H
#define	DIALOG_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Dialog {
public:
    Dialog(sf::RenderWindow *refwindow, sf::String rTitle, sf::String rMessage);
    virtual ~Dialog();

    int run();



private:

    sf::Image _dialog_image;
    sf::Sprite _dialog_sprite;

    sf::RenderWindow* _window;
    sf::Font _font;
    sf::String _title;
    sf::String _message;
};

#endif	/* DIALOG_H */

