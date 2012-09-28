#include "SplashScreen.h"

/*!
 * Constructor
 */
SplashScreen::SplashScreen(sf::RenderWindow *refwindow) {
    //Storing the address of the mainwindow to the current window
    _window = refwindow;
    this->init();
}

void SplashScreen::init(){
    //Setting the current state of the fighter on the "STARTGAME" state
    FighterState = SplashScreen::StartGame;

    //Loading the menu sound
    _buffer.LoadFromFile("assets/menu.ogg");

    //Using the buffer
    _menuSound.SetBuffer(_buffer);

    //Setting the menu sound volume
    _menuSound.SetVolume(100.0f);

    //Loading the splashscreen image from file
    image1.LoadFromFile("assets/splashscreen.png");
    //Loading the fighter image from file
    image2.LoadFromFile("assets/fighter.png");
    //Setting the background sprite
    _background.SetImage(image1);
    //Setting the fighter sprite
    _fighter.SetImage(image2);
    fighter_display = true;

    //Setting the fighter position
    _fighter.SetPosition(250, 385);

    //Loading the bgmusic file
    _bgmusic.OpenFromFile("assets/bgmusic.ogg");
    //Setting the bgmusic volume
    _bgmusic.SetVolume(60.0f);
    //PLaying the bgmusic
    _bgmusic.SetLoop(true);
    _bgmusic.Play();
}

/*!
 *  Loop routine for the SplashScreenClass
 * 
 *  The Loop routine renders the sprites on the renderwindow 
 *  while checking for the user activity.
 *  
 *  The ESCAPE key terminates the loop
 * 
 */
void SplashScreen::loop() {
    //drawing the background
    _window->Draw(_background);

    //drawing the fighter
    if (fighter_display) {
        _window->Draw(_fighter);
    }
    //displaying on the window
    _window->Display();
}

/*!
 *  Events handling
 *  returns 0: pressed ESCAPE key
 *  returns 1: pressed any other keys
 * 
 *  Inside the handleEvents() routine is handled the movements
 *  of the fighter on the splashscreen.
 *  The mechanics is handled using the states of the ENUM
 * 
 */
bool SplashScreen::handleEvents() {
    sf::Event Event;
    if (_window->GetEvent(Event)) {
        //PRESSING KEY UP
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up)) {

            if (FighterState == SplashScreen::StartGame) {
                _fighter.SetPosition(250, 385);
                FighterState = SplashScreen::StartGame;
            }

            if (FighterState == SplashScreen::Option) {
                _fighter.SetPosition(250, 385);
                FighterState = SplashScreen::StartGame;
                _menuSound.Play();
            }

            return 1;
        }
        //PRESSING KEY DOWN
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down)) {
            if (FighterState == SplashScreen::StartGame) {
                _fighter.SetPosition(250, 450);
                _menuSound.Play();
                FighterState = SplashScreen::Option;
            };

            if (FighterState == SplashScreen::Option) {
                _fighter.SetPosition(250, 450);
                FighterState = SplashScreen::Option;
            }

            return 1;
        }

        //PRESSING KEY ESCAPE
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)) {
            return 0;
        }

        //PRESSING KEY ENTER
        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Return))
       {
            if(FighterState==SplashScreen::Option)
            {
                sf::String Titolo; Titolo.SetText("Bello le opzioni vero?");
                Titolo.SetPosition(180,180);
                sf::String sottoTitolo; sottoTitolo.SetText("");
                Dialog myDialog(_window,Titolo,sottoTitolo);
                     
                sf::PostFX Effect;
                Effect.LoadFromFile("shaders/blur.sfx");
                Effect.SetTexture("framebuffer", NULL);
                Effect.SetParameter("offset", 0.008f);
                
                _window->Clear();
                _window->Draw(_background);
                _window->Draw(Effect);
                _window->Display();

                myDialog.run();
            }
            if (FighterState == SplashScreen::StartGame) {
                _bgmusic.Stop();
                Field field(_window);
                field.loop();
                _bgmusic.Play();
            }
            return 1;
        }
    }
    return 1;
}

/*!
 *  Destructor
 */
SplashScreen::~SplashScreen() {

}

