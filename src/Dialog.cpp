#include <string.h>
#include <stdio.h>

#include "Dialog.h"

Dialog::Dialog(sf::RenderWindow *refwindow, sf::String rTitle, sf::String rMessage) :
    _window(refwindow), _title(rTitle), _message(rMessage)
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
    _window->GetEvent(Event);

    while (Event.Type != sf::Event::KeyPressed) {
        _window->Draw(_dialog_sprite);
        _window->Draw(_title);
        _window->Draw(_message);
        _window->Display();
        _window->GetEvent(Event);
    }

    return Event.Key.Code;

}

Dialog::~Dialog() {

}

