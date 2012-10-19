#ifndef FIELD_H
#define	FIELD_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Dialog.h"
#include "Plane.h"
#include "WoWBrain.h"
#include "World.h"
#include "math.h"
#include "Kicker.h"
#include "WaterTile.h"
#include "Animation.h"
#include "CardImage.h"
#include "LifeBar.h"

class Field {
public:
	Field(sf::RenderWindow *refwindow);
	~Field();
	int handleEvents();

	/*!
	 * \brief Draw routine for Field class.
	 */
	void draw();

	/*!
	 * \brief Update routine for Field class.
	 */
	void update();

	/*!
	 * \brief Initialize Field Class
	 */
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

	/*!
	 * \brief isTerminated
	 * \return
	 */
	bool isTerminated();


private:
	/*!
	 * \brief The FieldStatus enum represents external global status for Field.
	 */
	enum FieldStates { INGAME, TERMINATED };

	/*!
	 * \brief status stores the current status of the field game.
	 */
	FieldStates _status;

	/*!
	 * \brief Store planes.
	 */
	Plane* _plane1;
	Plane* _plane2;

	/*!
	 * \brief theBrain stores a reference to WoW AI.
	 */
	WoWBrain* _theBrain;

	/*!
	 * \brief theWorld stores a reference to Game World.
	 */
	World* _theWorld;

	/*!
	 * \brief lastEvent stores the last event
	 */
	sf::Event _lastEvent;

	/*!
	 * \brief kicker stores a kicker reference
	 */
	Kicker * _kicker;

	/*!
	 * \brief lifebar stores a lifebar reference
	 */
	LifeBar * _enemyLifebar;
	LifeBar * _playerLifebar;


	/*!
	 * \brief _bgmusic BG music.
	 */
	sf::Music _bgmusic;

	/*!
	 * \brief The States enum represent the game internal status.
	 */
	enum States {
		INIT, PLAYER_SELECT, PREVIEW_MOVES, BRAIN_SELECT, APPLY_MOVES, ANIM_MOVES, COMPUTE_DAMAGES, ANIM_DAMAGES, CHECK_FINISH, SHOW_INFOS
	};

	/*!
	 * \brief _internal_state stores the game internal state.
	 */
	States _internal_state;

	/*!
	 * \brief _window stores a reference to main window.
	 */
	sf::RenderWindow* _window;

	/*!
	 * \brief _camera stores the game camera.
	 */
	sf::View _camera;

	/*!
	 * \brief _mouse_down is true if and only if mouse left-button is down.
	 */
	bool _mouse_down;

	/*!
	 * \brief _cards stores the cards.
	 */
	std::vector<CardImage*> _cards;

	/*!
	 * Store variables for mouse button.
	 */
	int _xstart;
	int _ystart;
	int _xdisplacement;
	int _ydisplacement;

	WaterTile* _water;

	std::map<int,int> _cardmaster;
	std::map<int,int>::iterator _it;
	int cardCounter;

	bool game_finished; // will be TRUE when the game has ended

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

	sf::Vector2f water_size;
	sf::Vector2f plane1_size;
	sf::Vector2f plane2_size;

	sf::Sprite plane1_preview;	// used for showing where the plane will go when the player chooses his moves
	sf::Sprite plane1_shadow;
	sf::Sprite plane2_shadow;
};

#endif	/* FIELD_H */

