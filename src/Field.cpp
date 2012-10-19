#include <vector>

#include "wowcommon.h"
#include "Field.h"

Field::Field(sf::RenderWindow *refwindow) {
    _window = refwindow;
    
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

    LOGMESSAGE("Initialize Plane 1");
    _plane1 = new Plane(0, 10, 400, 300, 0);
    _plane1->plane_sprite.SetColor(sf::Color(255, 0, 0));        // PLANE 1 IS RED

    LOGMESSAGE("Initialize Plane 2");
    _plane2 = new Plane(1, 10, 50, 50, 0);
    _plane2->plane_sprite.SetColor(sf::Color(0, 255, 0));        // PLANE 2 IS GREEN

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

    _water = new WaterTile(_window);
    sf::Rect<float> frect= sf::Rect<float>(0,0,800,600);
    _camera.SetFromRect(frect);

    _kicker = new Kicker(_window);

    cardCounter=0;
    //pointer to card image, instance to a generic cardImage with id=0
    CardImage* card = new CardImage(0,420,450,_window,&_cardmaster);
    //setting the clickable area
    card->clickableArea = new sf::Rect<int>(420,450,100,180);
    //adding the cardImage to the cards vector
    _cards.push_back(card);

    //same
    card = new CardImage(1,520,450,_window,&_cardmaster);
    card->clickableArea = new sf::Rect<int>(520,450,100,180);
    _cards.push_back(card);

    //same
    card = new CardImage(2,620,450,_window,&_cardmaster);
    card->clickableArea = new sf::Rect<int>(620,450,200,180);
    _cards.push_back(card);

    //store sprites dimentions and centering
    water_size = this->_water->getSprite().GetSize();
    plane1_size = this->_plane1->plane_sprite.GetSize();
    plane2_size = this->_plane2->plane_sprite.GetSize();
    _plane1->plane_sprite.SetCenter(plane1_size.x/2,plane1_size.y/2);
    _plane2->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);

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

    //==========
    // Game Turns Switch
    switch(this->_internal_state){
    case Field::INIT:
        // HERE WE INITIALIZE THINGS
        // set kicker message
        this->_kicker->setMessage("Initializing stuff");
        this->_kicker->setDetails("enhancing funnyness...");

        // planes positions
        this->_plane1->getPosition(p1pos);
        this->_plane2->getPosition(p2pos);

        this->_internal_state = Field::PLAYER_SELECT;
        break;

    case Field::PLAYER_SELECT:
        display_cards = true;

        // set kicker message
        if (kicker_was_changed){ // this is to avoid continuously replacing it
            this->_kicker->setMessage("Choose your moves (use ARROWS):");
            this->_kicker->setDetails("[left] LEFT - [up] FORWARD - [right] RIGHT");
            kicker_was_changed = false;
        }

        // WARNING: EVENT HANDLING CANNOT BE DONE HERE!!
        if(player_choices.size() >= CHOICES_PER_TURN){
            kicker_was_changed = true;
            display_cards = false;
            this->_internal_state = Field::PREVIEW_MOVES;
#if DEBUG
            LOGMESSAGE("Player has chosen!");
#endif
        }
        break;

    case Field::BRAIN_SELECT:
        // set kicker message
        this->_kicker->setMessage("AI is choosing...");
        this->_kicker->setDetails("it's so clever!");

        ai_choices = _theBrain->returnBestCards(CHOICES_PER_TURN,MAX_THINK_TIME);     // for the moment, this chooses 1 card
#if DEBUG
        LOGMESSAGE("AI has chosen!");
#endif
        this->_internal_state = Field::APPLY_MOVES;
        break;

    case Field::APPLY_MOVES:
        // set kicker message
        this->_kicker->setMessage("WOOSH!");
        this->_kicker->setDetails("");

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

        if(!something_moved)
            this->_internal_state = Field::COMPUTE_DAMAGES;

        break;

    case Field::COMPUTE_DAMAGES:
        // set kicker message
        this->_kicker->setMessage("BUM BUM BUM!");
        this->_kicker->setDetails("");

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
        }
        if ((!plane2_out) && _plane2->canShootTo(_plane1)){
            _plane1->inflictDamage(this->_theBrain->expectedDamage());
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
#if DEBUG
                LOGMESSAGE("both planes out of bounds!");
#endif
                _kicker->setDetails("DRAW, they all got lost somewhere...");
            }
            else{ // ONLY OPPONENT is out of bounds
#if DEBUG
                LOGMESSAGE("PLAYER out of bounds!");
#endif
                _kicker->setDetails("PLAYER got lost...");
            }
        }
        else if (plane2_out){   // ONLY AI plane out of bounds
            game_finished = true;
#if DEBUG
            LOGMESSAGE("AI PLANE out of bounds!");
#endif
            _kicker->setDetails("AI got lost...");
        }

        if (!game_finished){    // check other finish conditions
            if (_plane1->remainingHealth() <= 0){ // PLAYER DIED
                game_finished = true;
                if (_plane2->remainingHealth() <= 0){ // AI DIED TOO
#if DEBUG
                    LOGMESSAGE("BOTH PLANES destroyed!");
#endif
                    _kicker->setDetails("Both planes down: DRAW!");
                }
                else{
#if DEBUG
                    LOGMESSAGE("OPPONENT destroyed!");
#endif
                    _kicker->setDetails("Plane1 destroyed: YOU LOST!");
                }
            }
            else if(_plane2->remainingHealth() <= 0){ // ONLY AI DIED
                game_finished = true;
#if DEBUG
                LOGMESSAGE("AI plane destroyed!");
#endif
                _kicker->setDetails("Plane2 destroyed: YOU WIN!");
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

            _kicker->setMessage("GAME FINISHED");
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
    _plane1->plane_sprite.SetRotation(radiants2degrees(p1pos[2]));
    _plane2->plane_sprite.SetPosition(p2pos[0] + _xdisplacement, p2pos[1] + _ydisplacement);
    _plane2->plane_sprite.SetRotation(radiants2degrees(p2pos[2]));

    // compute and set shadows positions
    shadow1_pos = this->_plane1->plane_sprite.GetPosition();
    shadow1_pos.x+=10;
    shadow1_pos.y+=15;
    plane1_shadow.SetPosition(shadow1_pos);
    plane1_shadow.SetRotation(radiants2degrees(p1pos[2]));
    shadow2_pos = this->_plane2->plane_sprite.GetPosition();
    shadow2_pos.x+=10;
    shadow2_pos.y+=15;
    plane2_shadow.SetPosition(shadow2_pos);
    plane2_shadow.SetRotation(radiants2degrees(p2pos[2]));

    // update the water tile(waves effect)
    this->_water->update();
}

void Field::draw() {
    // TODO: adjust this, it is just for testing
    for(int i=0;i<=(int)(_theWorld->getWidth()/(2*water_size.x));i++){
        for(int j=0;j<=(int)(_theWorld->getHeight()/(2*water_size.y));j++)
        {
            _water->setPos(i*water_size.x*2+_xdisplacement,j*water_size.y*2+_ydisplacement);
            _window->Draw(_water->getSprite());
        }
    }

    // Set the camera according to the zoom
    _window->SetView(this->_camera);

    // Now draw things that must be affected by the zoom...
    _window->Draw(plane1_shadow);
    _window->Draw(plane2_shadow);
    _window->Draw(_plane1->plane_sprite);
    _window->Draw(_plane2->plane_sprite);

    // Now draw things of fixed size
    _window->SetView(_window->GetDefaultView());

    // KICKER
    _kicker->draw();

    if(display_cards){
        //CARDS TEST --------------
        _cards[0]->draw();
        _cards[1]->draw();
        _cards[2]->draw();
    }
}

/************ EVENT HANDLER **********/
void Field::zoom(float z)
{
    this->_camera.Zoom(z);
}

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
    LOGMESSAGE("L PRESSED");
    this->_mouse_down = true;
    this->_xstart = x;
    this->_ystart = y;
}

void Field::mouseLeftReleased(float x, float y)
{
    LOGMESSAGE("L RELEASED");
    this->_mouse_down = false;
    this->_xstart = 0;
    this->_ystart = 0;

    /* TODO: ClickableAreas method? */
    for(int i=0;i<_cards.size();i++)
    {
        //check if the click is inside for EACH clickableAreas rectangle
        //note: rect has a "contains" methods, unluckily... doesn't works -_-"
        double active_offset = 0;
        if(_cards[i]->activated==1) active_offset = 50;
        if(
                x>=_cards[i]->clickableArea->Left &&
                y>=_cards[i]->clickableArea->Top - active_offset &&
                x<=_cards[i]->clickableArea->Left+_cards[0]->clickableArea->Right &&
                y<=_cards[i]->clickableArea->Top - active_offset + _cards[0]->clickableArea->Bottom)

        {
            //the clicked card isn't active
            if(_cards[i]->activated==0)
            {
                //deactivate each card of the deck
                //for(int j=0;j<clickableAreas.size();j++) cards[j]->deActivateCard();
                //activate the "i" card
                _cardmaster.insert(std::pair<int,int>(i,cardCounter));
                _cards[i]->activateCard();
                cardCounter++;
            }
            //the "i" card is already activated, so deactivate it
            else if(_cards[i]->activated)
            {
                for(int j=0;j<_cards.size();j++)
                {
                    _it=_cardmaster.find(j);
                    if(_it!=_cardmaster.end())
                    {
                        _cardmaster.erase(_it);
                        cardCounter--;
                    }
                    _cards[j]->deActivateCard();

                }
            }
            //note:
            //this basic mechanism will be useful for a selectable sequence of card (i.e card1, card2.... cardN then confim!)
        }
    }
}

void Field::mouseMoved(float x, float y)
{
    if(_mouse_down){
        _xdisplacement += x - _xstart;
        _ydisplacement += y - _ystart;
        if (_xdisplacement > 0) _xdisplacement = 0;
        if (-_xdisplacement > this->_theWorld->getWidth()) _xdisplacement = -this->_theWorld->getWidth();
        if (_ydisplacement > 0) _ydisplacement = 0;
        if (-_ydisplacement > this->_theWorld->getHeight()) _ydisplacement = -this->_theWorld->getHeight();
        _xstart = x;
        _ystart = y;
    }
}


int Field::handleEvents() {
    //note GetEvent ALWAYS in if() or while()
    while(_window->GetEvent(_lastEvent))
    {
        switch(_lastEvent.Type){
        case sf::Event::KeyPressed:
            switch(_lastEvent.Key.Code){
            case sf::Key::Num1:
                zoom(1.1f);
                break;
            case sf::Key::Num2:
                zoom(0.9f);
                break;
            case sf::Key::Escape:
                stop();
                break;
            case sf::Key::Right:
            	if(player_choices.size() < CHOICES_PER_TURN && this->_internal_state == Field::PLAYER_SELECT){
            		player_choices.push_back(this->_plane1->getCardSet()->cards);
					#if DEBUG
            			LOGMESSAGE("You have chosen Right");
					#endif
            	}
            	break;
            case sf::Key::Left:
            	if(player_choices.size() < CHOICES_PER_TURN && this->_internal_state == Field::PLAYER_SELECT){
            	player_choices.push_back(this->_plane1->getCardSet()->cards+1);
					#if DEBUG
						LOGMESSAGE("You have chosen Left");
					#endif
            	}
                break;
            case sf::Key::Up:
            	if(player_choices.size() < CHOICES_PER_TURN && this->_internal_state == Field::PLAYER_SELECT){
            	player_choices.push_back(this->_plane1->getCardSet()->cards+2);
					#if DEBUG
        	    		LOGMESSAGE("You have chosen Up");
        			#endif
            	}
                break;
            case sf::Key::Return:
            	if(this->_internal_state == Field::PREVIEW_MOVES){
            		this->_internal_state = Field::BRAIN_SELECT;
            	}
            	break;
            default:
                break;
            } // END OF KEY.CODE SWITCH
            break;

        case sf::Event::MouseWheelMoved:
            if(_lastEvent.MouseWheel.Delta<0) zoom(1.1f);
            else zoom(0.9f);
            break;

        case sf::Event::MouseButtonPressed:
            if (_lastEvent.MouseButton.Button == sf::Mouse::Left){
                mouseLeftPressed(_lastEvent.MouseButton.X,_lastEvent.MouseButton.Y);
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(_lastEvent.MouseButton.Button == sf::Mouse::Left){
                mouseLeftReleased(_lastEvent.MouseButton.X,_lastEvent.MouseButton.Y);
            }
            break;

        case sf::Event::MouseMoved:
            mouseMoved(_lastEvent.MouseMove.X,_lastEvent.MouseMove.Y);
            break;

        default:
            break;
        }// END OF LASTEVENT.TYPE SWITCH

        return 1;
    }
    return 1;
}


