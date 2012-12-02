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
#include "WaterTile.h"
#include "Animation.h"
#include "CardImage.h"
#include "LifeBar.h"
#include "guiButton.h"
#include "FireBullet.h"

class Field {
public:
	Field();
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
	 * \brief launches init() the first time it is called, reset() the next times
	 */
	void initialize();

	/* EVENTS HANDLER */
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
	 * \brief Perform events on RightMouse click.
	 * \param x
	 * \param y
	 */
	void mouseRightPressed(float x,float y);

	/*!
	 * \brief Perform events on RightMouse release.
	 * \param x
	 * \param y
	 */
	void mouseRightReleased(float x, float y);

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
	 * \brief Initialize Field Class
	 */
	void init();

	/*!
	 * \brief Reset Much Like init
	 */
	void reset();

	/*!
	 * \brief tells whether the init() method has already been called
	 */
	bool _already_initialized;

	int _outcome;	// outcome will be positive if the AI wins, negative if PLAYER wins, and zero on a DRAW

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
	Plane* _preview_plane_a;	// preview planes, used to show chosen moves
	Plane* _preview_plane_b;

	/*!
	 * \brief brains store a reference to WoW AIs.
	 */
	WoWBrain* _brain1;
	WoWBrain* _brain2;

	/*!
	 * \brief theWorld stores a reference to Game World.
	 */
	World* _theWorld;

	/*!
	 * \brief lifebar stores a lifebar reference
	 */
	LifeBar * _enemyLifebar;
	LifeBar * _playerLifebar;

	guiButton * _okButton;
	guiButton * _cancelButton;

	/*!
	 * \brief _bgmusic BG music.
	 */
	sf::Music _bgmusic;

	/*!
	 * \brief The States enum represent the game internal status.
	 */
	enum States {
		INIT, AI1_SELECT, AI2_SELECT, APPLY_MOVES, ANIM_MOVES, BULLET_ANIM, COMPUTE_DAMAGES, ANIM_DAMAGES, CHECK_FINISH, SHOW_INFOS
	};

	/*!
	 * \brief _internal_state stores the game internal state.
	 */
	States _internal_state;

	/*!
	 * \brief _window stores a reference to main window.
	 */
	sf::RenderWindow& _window;

	/*!
	 * \brief _camera stores the game camera.
	 */
	sf::View _camera;

	/*!
	 * \brief _mouse_left_down is true if and only if mouse left-button is down.
	 */
	bool _mouse_left_down;

	/*!
	 * _mouse_right_down is true if and only if mouse right-button is down.
	 */
	bool _mouse_right_down;

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
	bool _paused;	// used to interrupt the AI vs AI match
	
	float p1pos [3];    // these two arrays will keep track of the displayed position of the planes in the window
	float p2pos [3];    // WARNING: I think that these should stay in Plane class...

	bool plane1_out;    // these two booleans are used to signal that planes have gone out of bounds
	bool plane2_out;

	std::vector<Card*> ai1_choices; // used to store AI1 choices
	std::vector<Card*> ai2_choices; // used to store AI2 choices

	int moves_counter;      // used to understand how many move cards have already been applied
	bool something_moved;       // used to signal animations are over

	Animation * animation1;     // used for animating the first plane
	Animation * animation2;     // used for animating the second plane

	float plane1_prev_pos[3];   // these four arrays will be used to correctly construct the animations
	float plane1_final_pos [3];
	float plane2_prev_pos[3];
	float plane2_final_pos [3];

	//	bool kicker_was_changed; // this is used to avoid continuous replacement of the kicker content
	bool display_cards;

	// these will keep track of planes shadows positions
	sf::Vector2f shadow1_pos;
	sf::Vector2f shadow2_pos;

	sf::Vector2f water_size;
	sf::Vector2f plane1_size;
	sf::Vector2f plane2_size;

	float preview_plane_a_pos [3];	// these are for drawing the preview planes
	float preview_plane_b_pos [3];

	sf::Sprite plane1_shadow;
	sf::Sprite plane2_shadow;

	sf::Sprite * winner_plane_sprite;

	sf::Image gameover_image;
	sf::Sprite gameover_sprite;
	sf::Image the_winner_is_image;
	sf::Sprite the_winner_is_sprite;

	FireBullet* _bullet1;
	FireBullet* _bullet2;
};

#endif	/* FIELD_H */

