#include "Kicker.h"

Kicker::Kicker(sf::RenderWindow *refwindow) {
    _window = refwindow;
    
    iCats.LoadFromFile("assets/cats.png");
    sCats.SetImage(iCats);
    
    sCats.SetPosition(5,430);
}

int Kicker::run() {
    sf::Event Event;


    sf::String message;
    sf::String detail;
    message.SetText("Scegli la mossas:");
    detail.SetText("[]1 LEFT - [2] FORWARD - [3] RIGHT");

    sf::Font Font;
    Font.LoadFromFile("assets/pixelmix.ttf");

    message.SetFont(Font);
    detail.SetFont(Font);

    message.SetPosition(10, 550);
    detail.SetPosition(10, 570);
    message.SetSize(20);
    detail.SetSize(20);

    sf::Shape Rect = sf::Shape::Rectangle(0, 500, 800, 600, sf::Color(0, 0, 0, 120));

    _window->Draw(Rect);
    _window->Draw(sCats);
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
    detail.SetText("[1] LEFT - [2] FORWARD - [3] RIGHT");

    sf::Font Font;
    Font.LoadFromFile("assets/pixelmix.ttf");

    message.SetFont(Font);
    detail.SetFont(Font);

    message.SetPosition(170, 550);
    detail.SetPosition(170, 570);
    message.SetSize(20);
    detail.SetSize(20);

    sf::Shape Rect = sf::Shape::Rectangle(0, 500, 800, 600, sf::Color(0, 0, 0, 120));

    _window->Draw(Rect);
    
    sf::Sprite sCatsShadow = sCats;
    sCatsShadow.SetColor(sf::Color(0,0,0,128));
    sCatsShadow.SetPosition(sCats.GetPosition().x+7,sCats.GetPosition().y+7);
    _window->Draw(sCatsShadow);
    _window->Draw(sCats);
    _window->Draw(message);
    _window->Draw(detail);

    _window->Display();


}

Kicker::~Kicker() {
}
