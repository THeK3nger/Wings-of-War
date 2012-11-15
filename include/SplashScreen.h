#ifndef SPLASHSCREEN_H
#define	SPLASHSCREEN_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Field.h"

class SplashScreen {
public:
    /*!
     * \brief SplashScreen constructor
     * \param refwindow Reference to the original windows.
     */
    SplashScreen();

    virtual ~SplashScreen();

    /*!
     * \brief Draw routine for SplashScreen.
     */
    void draw();

    /*!
     * \brief Update routine for SplashScreen.
     */
    void update();

    /*!
     * \brief Handle user input.
     * \return return false on error or exit key.
     */
    bool handleEvents();

    /*!
     * \brief isExiting check for splashcreen exit.
     * \return True if SplashScreen is Exiting. False otherwise.
     */
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
     * Image files, needed for the sprites
     */
    sf::Image _image1;
    sf::Image _image2;

    /*!
     * Sprites for background and fighter
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
    enum FighterPosition {
        StartGame, Option
    };

    /*!
     * The fighter position on the splashscreen
     */
    FighterPosition FighterState;

    /*!
     * \brief field is a pointer to a Field object. In Field object we play the real game.
     */
    Field* _field;

    /*!
     * \brief tells whether _field->init() has already been called
     * this is used to decide if it is the case of calling init() or reset() on ENTER KEY PRESSED
     */
    bool _field_initiated;

    /*!
     * \brief Initialize SplashScreen class.
     */
    void init();
};

#endif	/* SPLASHSCREEN_H */

