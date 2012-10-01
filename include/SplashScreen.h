#ifndef SPLASHSCREEN_H
#define	SPLASHSCREEN_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stdio.h>
#include "Dialog.h"
#include "Field.h"

class SplashScreen {
public:
    /*!
     * \brief SplashScreen constructor
     * \param refwindow Reference to the original windows.
     */
    SplashScreen(sf::RenderWindow *refwindow);

    virtual ~SplashScreen();
    void loop();
    void draw();
    void update();

    /*!
     * \brief Handle user input.
     * \return return false on error or exit key.
     */
    bool handleEvents();

    bool isExiting();

private:
    /*!
     * Possible states of the game
     */
    enum SplashState {
        OnSplash, InGame, Exit
    };

    /*!
     * Actual state of SplashScreen
     */
    SplashState _splashState;

    /*!
     * The render window
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
     * Have I to display the fighter?
     */
    bool fighter_display;

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
    enum FighterPosition {
        StartGame, Option
    };

    /*!
     * The fighter position on the splashscreen
     */
    FighterPosition FighterState;

    Field* field;

    /*!
     * \brief Initializa SplashScreen class.
     */
    void init();
};

#endif	/* SPLASHSCREEN_H */

