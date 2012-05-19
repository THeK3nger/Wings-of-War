#include "Kicker.h"

Kicker::Kicker(sf::RenderWindow *refwindow) {
    _window = refwindow;
}

int Kicker::run() {
    sf::Event Event;


    sf::String message;
    sf::String detail;
    message.SetText("Scegli la mossa:");
    detail.SetText("[]1 LEFT - [2] FORWARD - [3] RIGHT");

    sf::Font Font;
    Font.LoadFromFile("assets/pixelmix.ttf");

    message.SetFont(Font);
    detail.SetFont(Font);

    message.SetPosition(10, 550);
    detail.SetPosition(10, 570);
    message.SetSize(20);
    detail.SetSize(20);

    sf::Shape Rect = sf::Shape::Rectangle(0, 540, 800, 600, sf::Color(0, 0, 0, 120));

    _window->Draw(Rect);
    _window->Draw(message);
    _window->Draw(detail);

    _window->Display();


    while (Event.Type != sf::Event::KeyPressed)
        {
        _window->GetEvent(Event);
    }
    return Event.Key.Code;


}

void Kicker::display() {
    sf::Event Event;


    sf::String message;
    sf::String detail;
    message.SetText("Scegli la mossa:");
    detail.SetText("[]1 LEFT - [2] FORWARD - [3] RIGHT");

    sf::Font Font;
    Font.LoadFromFile("assets/pixelmix.ttf");

    message.SetFont(Font);
    detail.SetFont(Font);

    message.SetPosition(10, 550);
    detail.SetPosition(10, 570);
    message.SetSize(20);
    detail.SetSize(20);

    sf::Shape Rect = sf::Shape::Rectangle(0, 540, 800, 600, sf::Color(0, 0, 0, 120));

    _window->Draw(Rect);
    _window->Draw(message);
    _window->Draw(detail);

    _window->Display();


}

Kicker::~Kicker() {
}

