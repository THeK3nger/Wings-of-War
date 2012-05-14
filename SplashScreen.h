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
    /*!
     * _window: Used to store the address of the main render window
     */
    
    sf::RenderWindow* _window;
    
    
    /*!
     * Image files, needed for the sprites
     */
    
    sf::Image image1;
    sf::Image image2;
    
    
    /*!
     * Sprites 
     */
    sf::Sprite _background;
    sf::Sprite _fighter;
    
    /*!
     * BG Music
     */
    sf::Music _bgmusic;
    
    /*!
     * Sound
     */
    sf::Sound _menuSound;
    
    /*!
     * The buffer needed bu the sound
     */
    sf::SoundBuffer _buffer;
    
    /*!
     * Describes the state of the fighter (the pointer on the splashscreen)
     */
    enum FighterPosition { StartGame, Option};
    
    /*!
     * The fighter position on the splashscreen
     */
    FighterPosition FighterState;
    
    bool handleEvents();

};

#endif	/* SPLASHSCREEN_H */

