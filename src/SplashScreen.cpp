#include "SplashScreen.h"
#include "wowcommon.h"
#include "resources/ResourcesManager.h"
#include "resources/ImageRes.h"
#include "Dialog.h"

/*!
 * Constructor
 */
SplashScreen::SplashScreen(sf::RenderWindow *refwindow) {
    //Storing the address of the mainwindow to the current window
    _window = refwindow;
    _splashState = OnSplash;
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
    _image1 = GET_SFML_IMAGE_FROM_MANAGER("splashscreen");
    //Loading the fighter image from file
    _image2 = GET_SFML_IMAGE_FROM_MANAGER("fighter");
    //Setting the background sprite
    _background.SetImage(_image1);
    //Setting the fighter sprite
    _fighter.SetImage(_image2);

    //Setting the fighter position
    _fighter.SetPosition(250, 385);

    //Loading the bgmusic file
    _bgmusic.OpenFromFile("assets/bgmusic.ogg");
    //Setting the bgmusic volume
    _bgmusic.SetVolume(60.0f);
    //PLaying the bgmusic
    _bgmusic.SetLoop(true);
    _bgmusic.Play();

    // Create an empty Field.
    _field = new Field(_window);
}

/*!
 *  Draw routine for the SplashScreen class
 * 
 *  The Draw routine renders the sprites on the renderwindow.
 */
void SplashScreen::draw() {
    switch (_splashState) {
    case InGame :
        // If InGame propagate draw to field.
        _field->draw();
        break;
    case OnSplash :
        //drawing the background
        _window->Draw(_background);

        //drawing the fighter
        _window->Draw(_fighter);
        break;
    case Exit :
        break;
    }
}

void SplashScreen::update() {
    switch (_splashState) {
    case InGame :
        // If InGame propagate draw to field.
        _field->update();
        // Check for termination.
        // TODO: It is better to use lazy approach.
        if (_field->isTerminated()) {
            _splashState = OnSplash;
            _bgmusic.Play();
        }
        break;
    case OnSplash :
        if (!handleEvents()) {
            LOGMESSAGE("ESC!");
            _splashState = Exit;
        }
        break;
    case Exit :
        break;
    }
}

bool SplashScreen::isExiting() {
    return _splashState == Exit;
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
                ResourcesManager::getSingleton().setScope(1);
                _field->init();
                _splashState = InGame;
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
    delete _field;
}

