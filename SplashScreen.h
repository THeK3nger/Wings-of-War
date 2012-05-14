/* 
 * File:   SplashScreen.h
 * Author: malcom
 *
 * Created on May 14, 2012, 1:10 PM
 */

#ifndef SPLASHSCREEN_H
#define	SPLASHSCREEN_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stdio.h>

class SplashScreen {
public:
    SplashScreen(sf::RenderWindow  *refwindow);
    
    virtual ~SplashScreen();
    void loop();
    
private:
    
    sf::RenderWindow* _window;
    
    sf::Image image1;
    sf::Image image2;
    
    sf::Sprite _background;
    sf::Sprite _fighter;
    
    sf::Music _bgmusic;
    sf::Sound _menuSound;
    sf::SoundBuffer _buffer;
    
    enum FighterPosition { StartGame, Option};
    FighterPosition FighterState;
    
    bool handleEvents();

};

#endif	/* SPLASHSCREEN_H */

