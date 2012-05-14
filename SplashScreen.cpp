/* 
 * File:   SplashScreen.cpp
 * Author: malcom
 * 
 * Created on May 14, 2012, 1:10 PM
 */

#include "SplashScreen.h"

SplashScreen::SplashScreen(sf::RenderWindow  *refwindow) {
    _window=refwindow;
    
    FighterState=SplashScreen::StartGame;
    
    
    _buffer.LoadFromFile("assets/menu.ogg");
    _menuSound.SetBuffer(_buffer);
    _menuSound.SetVolume(10.f);
    
    
    image1.LoadFromFile("assets/splashscreen.png");
    image2.LoadFromFile("assets/fighter.png");
    _background.SetImage(image1);
    _fighter.SetImage(image2);
    
    _fighter.SetPosition(250,385);
    _fighter.SetRotation(-90.f);
    
    _bgmusic.OpenFromFile("assets/bgmusic.ogg");
    _bgmusic.SetVolume(2.0f);
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
        
             if(FighterState==SplashScreen::StartGame)
                {
                        _fighter.SetPosition(250,385);
                        FighterState=SplashScreen::StartGame;
                };
                
             if(FighterState==SplashScreen::Option)
                {
                        _fighter.SetPosition(250,385);
                        FighterState=SplashScreen::StartGame;
                        _menuSound.Play();
                }
             
        return 1; 
       }
        
         if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
       {
             if(FighterState==SplashScreen::StartGame) 
                {
                       _fighter.SetPosition(250,450);
                       _menuSound.Play();
                       FighterState=SplashScreen::Option;
                };
                
             if(FighterState==SplashScreen::Option) 
                {
                        _fighter.SetPosition(250,450);
                        FighterState=SplashScreen::Option;
                }
             
        return 1;
       }
        
        
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
       {
          
         return 0;
       }
        
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
       {
            if(FighterState=SplashScreen::Option)
            {
                //
            }
            if(FighterState=SplashScreen::StartGame)
            {
                //
            }
         return 0;
       }
    }
    
    return 1;
}

SplashScreen::~SplashScreen() {
    
}

