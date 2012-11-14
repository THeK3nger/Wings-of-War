#include <vector>

#include "resources/ResourcesManager.h"
#include "resources/ImageRes.h"
#include "wowcommon.h"
#include "Field.h"
#include "Game.h"

Field::Field() : _window(Game::getMainWindow()) {
	//Loading the bgmusic file
	_bgmusic.OpenFromFile("assets/field.ogg");
	//Setting the bgmusic volume
	_bgmusic.SetVolume(100.0f);
	//PLaying the bgmusic
	_bgmusic.SetLoop(true);

	_internal_state = Field::INIT;
}

Field::~Field() {
}

void Field::init() {
	_bgmusic.Play();

	this->outcome = 0;

	gameover_image = GET_SFML_IMAGE_FROM_MANAGER("gameover");
	gameover_sprite.SetImage(gameover_image);

	the_winner_is_image = GET_SFML_IMAGE_FROM_MANAGER("the_winner_is");
	the_winner_is_sprite.SetImage(the_winner_is_image);

	LOGMESSAGE("Initialize Plane 1");
	_plane1 = new Plane(0, 10, 400, 300, 0);
	_plane1->plane_sprite.SetColor(sf::Color(255, 0, 0));        // PLANE 1 IS RED

	LOGMESSAGE("Initialize Plane 2");
	_plane2 = new Plane(1, 10, 50, 50, 0);
	_plane2->plane_sprite.SetColor(sf::Color(0, 255, 0));        // PLANE 2 IS GREEN

	LOGMESSAGE("Initialize Preview Planes");
	_preview_plane_a = new Plane(10,10,400,300,0);
	_preview_plane_b = new Plane(11,10,400,300,0);
	sf::Color col = _plane1->plane_sprite.GetColor();
	col.a = 128;
	_preview_plane_a->plane_sprite.SetColor(col);
	_preview_plane_b->plane_sprite.SetColor(col);

	LOGMESSAGE("Init enemy lifebar");
	_enemyLifebar= new LifeBar(0,10,590,10);

	LOGMESSAGE("Init player lifebar");
	_playerLifebar= new LifeBar(1,10,10,10);

	LOGMESSAGE("Init buttons");
	_okButton= new guiButton(0,560,460);
	_okButton->clickableArea=new sf::Rect<int>(_okButton->_button_sprite.GetPosition().x,_okButton->_button_sprite.GetPosition().y,_okButton->_button_sprite.GetSize().x,_okButton->_button_sprite.GetSize().y);
	_cancelButton= new guiButton(1,560,512);
	_cancelButton->clickableArea=new sf::Rect<int>(_cancelButton->_button_sprite.GetPosition().x,_cancelButton->_button_sprite.GetPosition().y,_cancelButton->_button_sprite.GetSize().x,_cancelButton->_button_sprite.GetSize().y);

	LOGMESSAGE("Create Game World");
	_theWorld = new World(800, 600);
	_theWorld->addPlane(_plane1);
	_theWorld->addPlane(_plane2);
	_theBrain = new WoWBrain(_plane2, _theWorld);

	_xstart = 0;
	_ystart = 0;
	_xdisplacement = 0;
	_ydisplacement = 0;

	_mouse_down = false;

	_water = new WaterTile();
	sf::Rect<float> frect= sf::Rect<float>(0,0,800,600);
	_camera.SetFromRect(frect);

	cardCounter=0;
	//pointer to card image, instance to a generic cardImage with id=0
	CardImage* card = new CardImage(0,0,450,&_cardmaster,0);
	//setting the clickable area
	card->clickableArea = new sf::Rect<int>(card->cardSprite.GetPosition().x,card->cardSprite.GetPosition().y,card->cardSprite.GetSize().x,card->cardSprite.GetSize().y);
	//adding the cardImage to the cards vector
	_cards.push_back(card);
	for(int i=1;i<6;i++)
	{
		card = new CardImage(1,91*i,450,&_cardmaster,i);
		card->clickableArea = new sf::Rect<int>(card->cardSprite.GetPosition().x,card->cardSprite.GetPosition().y,card->cardSprite.GetSize().x,card->cardSprite.GetSize().y);
		_cards.push_back(card);
	}

	//store sprites dimentions and centering
	water_size = this->_water->getSprite().GetSize();
	plane1_size = this->_plane1->plane_sprite.GetSize();
	plane2_size = this->_plane2->plane_sprite.GetSize();
	_plane1->plane_sprite.SetCenter(plane1_size.x/2,plane1_size.y/2);
	_plane2->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);
	_preview_plane_a->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);
	_preview_plane_b->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);

	// planes shadows sprites (they could be different)
	plane1_shadow = _plane1->plane_sprite;
	plane1_shadow.SetColor(sf::Color(0,0,0,128));
	plane2_shadow = _plane2->plane_sprite;
	plane2_shadow.SetColor(sf::Color(0,0,0,128));

	LOGMESSAGE_NO_ENDL("Field Loaded!"); OK;
	this->_status = INGAME;
}

void Field::update() {
	this->handleEvents();

	// Game Turns Switch
	switch(this->_internal_state){
	case Field::INIT:
		// HERE WE INITIALIZE THINGS
		// planes positions
		this->_plane1->getPosition(p1pos);
		this->_plane2->getPosition(p2pos);

		this->_internal_state = Field::PLAYER_SELECT;
		break;

	case Field::PLAYER_SELECT:
		display_cards = true;

		// WARNING: EVENT HANDLING CANNOT BE DONE HERE!!
		if(player_choices.size() >= CHOICES_PER_TURN){

			display_cards = false;

			// create preview planes
			float initpos[3];
			_plane1->getPosition(initpos);
			_preview_plane_a->setX(initpos[0]);
			_preview_plane_a->setY(initpos[1]);
			_preview_plane_a->setT(initpos[2]);
			_preview_plane_b->setX(initpos[0]);
			_preview_plane_b->setY(initpos[1]);
			_preview_plane_b->setT(initpos[2]);
			_preview_plane_a->move(player_choices[0]);
			_preview_plane_b->move(player_choices[0]);
			_preview_plane_b->move(player_choices[1]);

			// change state
			this->_internal_state = Field::PREVIEW_MOVES;
#if DEBUG
			LOGMESSAGE("Player has chosen!");
#endif
		}
		break;
	case Field::BRAIN_SELECT:
//		ai_choices = _theBrain->returnBestCards(CHOICES_PER_TURN,MAX_THINK_TIME);     // for the moment, this chooses 1 card
		ai_choices = this->_theBrain->returnBestCards();
#if DEBUG
		LOGMESSAGE("AI has chosen!");
#endif
		this->_internal_state = Field::APPLY_MOVES;
		break;

	case Field::APPLY_MOVES:

		// store positions before moving
		this->_plane1->getPosition(plane1_prev_pos);
		this->_plane2->getPosition(plane2_prev_pos);

		// logically move the planes
		_plane1->move(player_choices[moves_counter]);
		_plane2->move(ai_choices[moves_counter]);

		// get position after move
		_plane1->getPosition(plane1_final_pos);
		_plane2->getPosition(plane2_final_pos);

		// construct the animations
		animation1 = new Animation(plane1_prev_pos[0], plane1_prev_pos[1], plane1_prev_pos[2], plane1_final_pos[0], plane1_final_pos[1], plane1_final_pos[2]);
		animation2 = new Animation(plane2_prev_pos[0], plane2_prev_pos[1], plane2_prev_pos[2], plane2_final_pos[0], plane2_final_pos[1], plane2_final_pos[2]);

		this->_internal_state = Field::ANIM_MOVES;
		break;

	case Field::ANIM_MOVES:
		something_moved = false;

		if (animation1->nextStep(p1pos))
			something_moved = true;
		if (animation2->nextStep(p2pos))
			something_moved = true;

		if(!something_moved){
			this->_plane1->getPosition(p1pos);
			this->_plane2->getPosition(p2pos);
			this->_internal_state = Field::BULLET_ANIM;
			this->_bullet1 = new FireBullet(p1pos[0],p1pos[1],p2pos[0],p2pos[1]);
			this->_bullet2 = new FireBullet(p2pos[0],p2pos[1],p1pos[0],p1pos[1]);
			if(!_plane1->canShootTo(_plane2)){
				_bullet1->setVisible(false);
			}
			if(!_plane2->canShootTo(_plane1)){
				_bullet2->setVisible(false);
			}
		}

		break;

	case Field::BULLET_ANIM:
		this->_bullet1->update();
		this->_bullet2->update();
		if (_bullet1->hasArrived() && _bullet2->hasArrived()) {
			this->_internal_state = Field::COMPUTE_DAMAGES;
			delete _bullet1;
			delete _bullet2;
		}
		break;

	case Field::COMPUTE_DAMAGES:


		// if some plane is out of bounds, destroy it
		if (!this->_theWorld->isInside(_plane1)){
			plane1_out = true;
			_plane1->inflictDamage(_plane1->remainingHealth());
		}
		if (!this->_theWorld->isInside(_plane2)){
			plane2_out = true;
			_plane2->inflictDamage(_plane2->remainingHealth());
		}
		if ((!plane1_out) && _plane1->canShootTo(_plane2)){
#if DEBUG
			LOGMESSAGE("PLANE1 SHOT TO PLANE2");
#endif
			_plane2->inflictDamage(this->_theBrain->expectedDamage());
			_playerLifebar->setLife(this->_theBrain->expectedDamage());
		}
		if ((!plane2_out) && _plane2->canShootTo(_plane1)){
			_plane1->inflictDamage(this->_theBrain->expectedDamage());
			_enemyLifebar->setLife(this->_theBrain->expectedDamage());
#if DEBUG
			LOGMESSAGE("PLANE2 SHOT TO PLANE1");
#endif
		}

#if DEBUG
		std::cout << "remaining health -- PLANE1: " << _plane1->remainingHealth() << ", Plane2: " << _plane2->remainingHealth() << '\n';
#endif

		this->_internal_state = Field::ANIM_DAMAGES;
		break;

	case Field::ANIM_DAMAGES:
		// TODO: add some animation to represent shooting actions

		this->_internal_state = Field::CHECK_FINISH;
		break;

	case Field::CHECK_FINISH: // this will also destroy things and clear stuff

		// CHECK WIN/LOSE CONDITIONS
		if (plane1_out){ // opponent plane is out of bounds
			game_finished = true;
			if (plane2_out){ // BOTH planes out of bounds
				this->outcome = 0;
#if DEBUG
				LOGMESSAGE("both planes out of bounds!");
#endif

			}
			else{ // ONLY OPPONENT is out of bounds
				this->outcome = 1;
#if DEBUG
				LOGMESSAGE("PLAYER out of bounds!");
#endif

			}
		}
		else if (plane2_out){   // ONLY AI plane out of bounds
			game_finished = true;
			this->outcome = -1;
#if DEBUG
			LOGMESSAGE("AI PLANE out of bounds!");
#endif

		}

		if (!game_finished){    // check other finish conditions
			if (_plane1->remainingHealth() <= 0){ // PLAYER DIED
				game_finished = true;
				if (_plane2->remainingHealth() <= 0){ // AI DIED TOO
					this->outcome = 0;
#if DEBUG
					LOGMESSAGE("BOTH PLANES destroyed!");
#endif

				}
				else{
					this->outcome = 1;
#if DEBUG
					LOGMESSAGE("OPPONENT destroyed!");
#endif

				}
			}
			else if(_plane2->remainingHealth() <= 0){ // ONLY AI DIED
				game_finished = true;
				this->outcome = -1;
#if DEBUG
				LOGMESSAGE("AI plane destroyed!");
#endif

			}
		}

		if(!game_finished){     // if the game is not over
			moves_counter++;

			if(moves_counter < CHOICES_PER_TURN){
				this->_internal_state = Field::APPLY_MOVES;
			}
			else{
				moves_counter = 0;
				delete animation1;
				delete animation2;
				player_choices.clear();

				this->_internal_state = Field::PLAYER_SELECT;
			}
		}
		else{   // if the game is over
			delete animation1;
			delete animation2;
			player_choices.clear();


			this->_internal_state = Field::SHOW_INFOS;
		}
		break;

	case Field::SHOW_INFOS:     // we can add something here that shows infos at the end of the game, such as moves performed and damages received by planes
		break;

	default:
		break;
	}
	//----------

	// set planes positionsma
	_plane1->plane_sprite.SetPosition(p1pos[0] + _xdisplacement, p1pos[1] + _ydisplacement);
	_plane1->plane_sprite.SetRotation(radiants2degrees(-p1pos[2]));
	_plane2->plane_sprite.SetPosition(p2pos[0] + _xdisplacement, p2pos[1] + _ydisplacement);
	_plane2->plane_sprite.SetRotation(radiants2degrees(-p2pos[2]));

	// compute and set shadows positions
	shadow1_pos = this->_plane1->plane_sprite.GetPosition();
	shadow1_pos.x+=10;
	shadow1_pos.y+=15;
	plane1_shadow.SetPosition(shadow1_pos);
	plane1_shadow.SetRotation(-radiants2degrees(p1pos[2]));
	shadow2_pos = this->_plane2->plane_sprite.GetPosition();
	shadow2_pos.x+=10;
	shadow2_pos.y+=15;
	plane2_shadow.SetPosition(shadow2_pos);
	plane2_shadow.SetRotation(-radiants2degrees(p2pos[2]));

	// update the water tile(waves effect)
	this->_water->update();
}

void Field::draw() {
	if(this->_internal_state == Field::SHOW_INFOS){
		_window.Draw(gameover_sprite);
		if(this->outcome != 0){
			the_winner_is_sprite.SetPosition(250,100);
			_window.Draw(the_winner_is_sprite);
			if(this->outcome > 0){
				this->winner_plane_sprite = &(this->_plane2->plane_sprite);
			}
			else{
				this->winner_plane_sprite = &(this->_plane1->plane_sprite);
			}
			winner_plane_sprite->SetPosition(the_winner_is_sprite.GetPosition().x+the_winner_is_sprite.GetSize().x + winner_plane_sprite->GetSize().x/2 + 30,	the_winner_is_sprite.GetPosition().y + the_winner_is_sprite.GetSize().y/2);
			winner_plane_sprite->SetRotation(0);
			_window.Draw(*winner_plane_sprite);
		}
		return;
	}

    // Set the camera according to the zoom
    _window.SetView(this->_camera);

	// TODO: adjust this, it is just for testing
	for(int i=0;i<=(int)(_theWorld->getWidth()/(2*water_size.x));i++){
		for(int j=0;j<=(int)(_theWorld->getHeight()/(2*water_size.y));j++)
		{
			_water->setPos(i*water_size.x*2+_xdisplacement,j*water_size.y*2+_ydisplacement);
			_window.Draw(_water->getSprite());
		}
	}

	// Now draw things that must be affected by the zoom...
	_window.Draw(plane1_shadow);
	_window.Draw(plane2_shadow);
	_window.Draw(_plane1->plane_sprite);
	_window.Draw(_plane2->plane_sprite);

	if(this->_internal_state == Field::PREVIEW_MOVES){
		_preview_plane_a->getPosition(preview_plane_a_pos);
		_preview_plane_b->getPosition(preview_plane_b_pos);
		_preview_plane_a->plane_sprite.SetPosition(preview_plane_a_pos[0] + _xdisplacement, preview_plane_a_pos[1] + _ydisplacement);
		_preview_plane_a->plane_sprite.SetRotation(-radiants2degrees(preview_plane_a_pos[2]));
		_preview_plane_b->plane_sprite.SetPosition(preview_plane_b_pos[0] + _xdisplacement, preview_plane_b_pos[1] + _ydisplacement);
		_preview_plane_b->plane_sprite.SetRotation(-radiants2degrees(preview_plane_b_pos[2]));
		_window.Draw(_preview_plane_a->plane_sprite);
		_window.Draw(_preview_plane_b->plane_sprite);
	}

	if(_internal_state == Field::BULLET_ANIM) {
		_bullet1->draw();
		_bullet2->draw();
	}

	// Now draw things of fixed size
	_window.SetView(_window.GetDefaultView());

	// KICKER


	//HUD
	_enemyLifebar->draw();
	_playerLifebar->draw();
	if(_internal_state == Field::PREVIEW_MOVES){
		_okButton->draw();
		_cancelButton->draw();
	}

	if(display_cards){
		for(int i=0;i< _cards.size();i++)
			_cards[i]->draw();

	}
}

/************ EVENT HANDLER **********/
void Field::stop()
{
	this->_status = TERMINATED;
	_bgmusic.Stop();
}

bool Field::isTerminated()
{
	return _status == TERMINATED;
}

void Field::mouseLeftPressed(float x, float y)
{
	this->_mouse_down = true;
	this->_xstart = x;
	this->_ystart = y;
}

void Field::mouseLeftReleased(float x, float y)
{
	this->_mouse_down = false;
	this->_xstart = 0;
	this->_ystart = 0;

	int clicked_card = -1;


	//check for click on cards area
	for(int i=0; i<this->_plane1->getCardSet()->cards_number; i++){
        sf::Rect<int>* clickableArea = _cards[i]->clickableArea;
        if(		x>=clickableArea->Left &&
                y>=clickableArea->Top &&
                x<=clickableArea->Left+_cards[0]->clickableArea->Right &&
                y<=clickableArea->Top +_cards[0]->clickableArea->Bottom)
		{
			clicked_card = i;
			break;
		}
	}

	if(		x>=_okButton->clickableArea->Left &&
			y>=_okButton->clickableArea->Top &&
			x<=_okButton->clickableArea->Left+_okButton->clickableArea->Right &&
			y<=_okButton->clickableArea->Top + _okButton->clickableArea->Bottom)
	{
		if(this->_internal_state == Field::PREVIEW_MOVES){
			this->_internal_state = Field::BRAIN_SELECT;}
		std::cout << "OK clicked"<<std::endl;
	}

	if(		x>=_cancelButton->clickableArea->Left &&
			y>=_cancelButton->clickableArea->Top &&
			x<=_cancelButton->clickableArea->Left+_cancelButton->clickableArea->Right &&
			y<=_cancelButton->clickableArea->Top + _cancelButton->clickableArea->Bottom)
	{
		if(this->_internal_state == Field::PREVIEW_MOVES){
			player_choices.clear();
			this->_internal_state = Field::PLAYER_SELECT;}
		std::cout << "Cancel clicked"<<std::endl;
	}

	if(clicked_card != -1){
		player_choices.push_back(this->_plane1->getCardSet()->cards + clicked_card);
	}

	//check for click in buttons area
}

void Field::mouseMoved(float x, float y)
{
	if(_mouse_down){
		_xdisplacement += x - _xstart;
		_ydisplacement += y - _ystart;
		_xstart = x;
		_ystart = y;
	}
}

int Field::handleEvents() {
	//note GetEvent ALWAYS in if() or while()
    sf::Event event;
    while(_window.GetEvent(event))
    {

        switch(event.Type){
        case sf::Event::KeyPressed:
            switch(event.Key.Code){
            case sf::Key::Escape:
                stop();
                break;
            case sf::Key::Return:
                if(this->_internal_state == Field::PREVIEW_MOVES){
                    this->_internal_state = Field::BRAIN_SELECT;
                }
                break;
            case sf::Key::Delete:
                if(this->_internal_state == Field::PREVIEW_MOVES){
                    player_choices.clear();
                    this->_internal_state = Field::PLAYER_SELECT;
                }
                break;
            default:
                break;
            } // END OF KEY.CODE SWITCH
            break;

        case sf::Event::MouseMoved:
            mouseMoved(event.MouseMove.X,event.MouseMove.Y);
            break;

        case sf::Event::MouseWheelMoved:
            if(event.MouseWheel.Delta<0) this->_camera.Zoom(1.1f);
            else this->_camera.Zoom(0.9f);
            break;

        case sf::Event::MouseButtonPressed:
            if (event.MouseButton.Button == sf::Mouse::Left){
                mouseLeftPressed(event.MouseButton.X,event.MouseButton.Y);
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(event.MouseButton.Button == sf::Mouse::Left){
                mouseLeftReleased(event.MouseButton.X,event.MouseButton.Y);
            }
            break;
        default:
            break;
        }// END OF LASTEVENT.TYPE SWITCH
    }
    return 1;
}


