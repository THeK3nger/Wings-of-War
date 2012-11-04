#include <string.h>
#include <stdio.h>

#include "Dialog.h"
#include "Game.h"

Dialog::Dialog(sf::String rTitle, sf::String rMessage) :
    _title(rTitle), _message(rMessage)
{
    _dialog_image.LoadFromFile("assets/option.png");
    _dialog_sprite.SetImage(_dialog_image);
    _dialog_sprite.SetPosition(150, 150);

    _font.LoadFromFile("assets/pixelmix.ttf");

    _title.SetFont(_font);
    _message.SetFont(_font);
    
}

int Dialog::run() {
    sf::Event Event;
    sf::RenderWindow& window = Game::getMainWindow();
    window.GetEvent(Event);

    while (Event.Type != sf::Event::KeyPressed) {
        window.Draw(_dialog_sprite);
        window.Draw(_title);
        window.Draw(_message);
        window.Display();
        window.GetEvent(Event);
    }

    return Event.Key.Code;

}

Dialog::~Dialog() {

}

