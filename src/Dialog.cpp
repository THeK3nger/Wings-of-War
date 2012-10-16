#include <string.h>
#include <stdio.h>

#include "Dialog.h"

Dialog::Dialog(sf::RenderWindow *refwindow, sf::String rTitle, sf::String rMessage) {
    _window = refwindow;

    dialog_image.LoadFromFile("assets/option.png");
    dialog_sprite.SetImage(dialog_image);
    dialog_sprite.SetPosition(150, 150);


    Font.LoadFromFile("assets/pixelmix.ttf");

    Title = rTitle;
    Message = rMessage;

    Title.SetFont(Font);
    Message.SetFont(Font);
    
}

int Dialog::run() {
    sf::Event Event;
    _window->GetEvent(Event);

    while (Event.Type != sf::Event::KeyPressed) {
        _window->Draw(dialog_sprite);
        _window->Draw(Title);
        _window->Draw(Message);
        _window->Display();
        _window->GetEvent(Event);
    }

    return Event.Key.Code;

}

Dialog::~Dialog() {

}

