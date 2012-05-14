/* 
 * File:   SplashScreen.cpp
 * Author: malcom
 * 
 * Created on May 14, 2012, 1:10 PM
 */

#include "SplashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow  *refwindow) {
    _window=refwindow;
    
    
    
    image1.LoadFromFile("assets/splashscreen.png");
    image2.LoadFromFile("assets/fighter.png");
    _background.SetImage(image1);
    _fighter.SetImage(image2);
    
    _fighter.SetPosition(250,380);
    _fighter.SetRotation(-90.f);
    
    _bgmusic.OpenFromFile("assets/bgmusic.ogg");
    _bgmusic.Play();
    
}

void SplashScreen::loop()
{
    while(this->handleEvents()==1)
    {
       
       _window->Draw(_background);
       _window->Draw(_fighter);
       _window->Display();
       
    }
}

bool SplashScreen::handleEvents()
{
    sf::Event Event;
    if (_window->GetEvent(Event))
    {
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
       {
         
        return 1; 
       }
        
         if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
       {
        
        return 1;
       }
        
        
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
       {
          printf("return 0\n");
         return 0;
       }
    }
    
    return 1;
}

SplashScreen::~SplashScreen() {
    
}

