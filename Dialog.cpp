/* 
 * File:   Dialog.cpp
 * Author: malcom
 * 
 * Created on May 16, 2012, 7:11 PM
 */

#include "Dialog.h"

Dialog::Dialog(sf::RenderWindow  *refwindow) 
{
    _window=refwindow;
    
    dialog_image.LoadFromFile("assets/option.png");
    dialog_sprite.SetImage(dialog_image);
    dialog_sprite.SetPosition(150,150);
    
    Font.LoadFromFile("assets/pixelmix.ttf");
    Text.SetText("Hello, Maverick");
    Text.SetFont(Font);
    Text.SetSize(30);
    Text.SetColor(sf::Color(255, 255, 255));
    Text.SetRotation(0.f);
    Text.Move(250.f, 200.f);
    
    this->run();
}

void Dialog::run()
{
    while(this->handleEvents()==1)
    {
        _window->Draw(dialog_sprite);
        _window->Draw(Text);
        _window->Display();
    }
}

bool Dialog::handleEvents()
{
    sf::Event Event;
    _window->GetEvent(Event);
    
    if (Event.Type == sf::Event::KeyPressed)
    {
        return 0;
    }
    return 1;
}

Dialog::~Dialog() {
    
}

