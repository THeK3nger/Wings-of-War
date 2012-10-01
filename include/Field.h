#ifndef FIELD_H
#define	FIELD_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string.h>
#include <stdio.h>
#include "Dialog.h"
#include "Plane.h"
#include "WoWBrain.h"
#include "World.h"
#include "math.h"
#include "Kicker.h"
#include <stdlib.h>
#include "WaterTile.h"
#include "Animation.h"
#include "CardImage.h"

class Field {
public:
    Field(sf::RenderWindow *refwindow);
    ~Field();
    void loop();
    int handleEvents();

    void draw();
    void update();
    void init();

    /* EVENTS HANDLER */
    /*!
     * \brief Zoom windows view.
     * \param z Zoom amount!
     */
    void zoom(float z);

    /*!
     * \brief Stop the execution of Field.
     */
    void stop();

    /*!
     * \brief Perform events on LeftMouse click.
     * \param x
     * \param y
     */
    void mouseLeftPressed(float x,float y);

    /*!
     * \brief Perform events on LeftMouse release.
     * \param x
     * \param y
     */
    void mouseLeftReleased(float x, float y);

    /*!
     * \brief Perform events on mouse movement.
     * \param x
     * \param y
     */
    void mouseMoved(float x, float y);


private:
    enum FieldStatus { INGAME, TERMINATED };
    FieldStatus status; //WARING: Difference between status and CurrentState?
    
    Plane* plane1;
    Plane* plane2;

    WoWBrain* theBrain;
    World* theWorld;
    
    sf::Event lastEvent;        // used to store the last event
    
    Kicker * kicker;
    
    sf::Image field_image;
    sf::Sprite field_sprite;
    sf::Clock theClock;
    sf::Music _bgmusic;
    enum States {
        INIT, PLAYER_SELECT, BRAIN_SELECT, APPLY_MOVES, ANIM_MOVES, COMPUTE_DAMAGES, ANIM_DAMAGES, CHECK_FINISH, SHOW_INFOS
    };

    States CurrentState; //WARING: Difference between status and CurrentState?

    sf::RenderWindow* _window;
    sf::View camera;
    
    bool _mouse_down;
    
    std::vector<CardImage*> cards;
    
    int _xstart;
    int _ystart;
    int _xdisplacement;
    int _ydisplacement;
    
    WaterTile* water;
    
    std::map<int,int> cardmaster;
    std::map<int,int>::iterator it;
    int cardCounter;

    bool game_finished; // will be TRUE when the game has ended

    float angle;

    float p1pos [3];    // these two arrays will keep track of the displayed position of the planes in the window
    float p2pos [3];    // WARNING: I think that these should stay in Plane class...

    bool plane1_out;    // these two booleans are used to signal that planes have gone out of bounds
    bool plane2_out;

    std::vector<Card*> player_choices; // used to store player's choices
    std::vector<Card*> ai_choices; // used to ask to THE BRAIN which cards should be chosen

    int moves_counter;      // used to understand how many move cards have already been applied
    bool something_moved;       // used to signal animations are over

    Animation * animation1;     // used for animating the first plane
    Animation * animation2;     // used for animating the second plane

    float plane1_prev_pos[3];   // these four arrays will be used to correctly construct the animations
    float plane1_final_pos [3];
    float plane2_prev_pos[3];
    float plane2_final_pos [3];

    bool kicker_was_changed; // this is used to avoid continuous replacement of the kicker content
    bool display_cards;

    // these will keep track of planes shadows positions
    sf::Vector2f shadow1_pos;
    sf::Vector2f shadow2_pos;

    sf::Vector2f field_size;
    sf::Vector2f water_size;
    sf::Vector2f plane1_size;
    sf::Vector2f plane2_size;

    sf::Sprite plane1_shadow;
    sf::Sprite plane2_shadow;


};

#endif	/* FIELD_H */

