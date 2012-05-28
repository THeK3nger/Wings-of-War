#include <vector>

#include "wowcommon.h"
#include "Field.h"

inline float radiants2degrees(float rads){
    return rads * 180 / M_PI;
}

inline float degrees2radiants(float degs){
    return degs * M_PI / 180;
}

Field::Field(sf::RenderWindow *refwindow) {
    LOGMESSAGE("Loading Field...");
    _window = refwindow;
    
    //Loading the bgmusic file
    _bgmusic.OpenFromFile("assets/field.ogg");
    //Setting the bgmusic volume
    _bgmusic.SetVolume(100.0f);
    //PLaying the bgmusic
    _bgmusic.SetLoop(true);
    _bgmusic.Play();
            
    CurrentState = Field::INIT;

    LOGMESSAGE("Initialize Plane 1");
    plane1 = new Plane(0, 10, 400, 300, 0);
    plane1->plane_sprite.SetColor(sf::Color(255, 0, 0));        // PLANE 1 IS RED

    LOGMESSAGE("Initialize Plane 2");
    plane2 = new Plane(1, 10, 50, 50, 0);
    plane2->plane_sprite.SetColor(sf::Color(0, 255, 0));        // PLANE 2 IS GREEN

    field_image.LoadFromFile("assets/field.png");
    field_sprite.SetImage(field_image);

    LOGMESSAGE("Create Game World");
    theWorld = new World(800, 800);
    theWorld->addPlane(plane1);
    theWorld->addPlane(plane2);
    theBrain = new WoWBrain(plane2, theWorld);


    _xstart = 0;
    _ystart = 0;
    _xdisplacement = 0;
    _ydisplacement = 0;

    _mouse_down = false;
    

    water = new WaterTile(_window);
    sf::Rect<float> frect= sf::Rect<float>(0,0,800,600);
    camera.SetFromRect(frect);
    
    kicker = new Kicker(_window);
    
    //pointer to card image, instance to a generic cardImage with id=0
    CardImage* card = new CardImage(0,420,450);
    //adding the cardImage to the cards vector
    cards.push_back(card);
    //same
    card = new CardImage(1,520,450);
    cards.push_back(card);
    //same
    card = new CardImage(2,620,450);
    cards.push_back(card);
    
    //rect areas to check user inputs (idea: insert the rect class in the cardImage)
    //insert in the clickableAreas vector
    //note: rect(startx, starty, width, height)
    sf::Rect<int>* rect = new sf::Rect<int>(420,450,100,180);
    clickableAreas.push_back(rect);
    //same
    rect = new sf::Rect<int>(520,450,100,180);
    clickableAreas.push_back(rect);
    //same
    rect = new sf::Rect<int>(620,450,200,180);
    clickableAreas.push_back(rect);
    
    
    LOGMESSAGE_NO_ENDL("Field Loaded!"); OK;
    this->loop();
}

Field::~Field() {
}

void Field::loop() {
    // Definition of useful stuff
    float angle=0;
    
    float p1pos [3];    // these two arrays will keep track of the displayed position of the planes in the window
    float p2pos [3];
    
    std::vector<Card*> player_choices; // used to store player's choices
    std::vector<Card*> ai_choices; // used to ask to THE BRAIN which cards should be chosen
    
    bool something_moved; // used to signal animations are over
    
    Animation * animation1;     // used for animating the first plane
    Animation * animation2;     // used for animating the second plane
    
    float plane1_prev_pos[3];   // these four arrays will be used to correctly construct the animations
    float plane1_final_pos [3];
    float plane2_prev_pos[3];
    float plane2_final_pos [3];
    
    //store sprites dimentions and centering
    sf::Vector2f field_size = this->field_sprite.GetSize();
    sf::Vector2f water_size = this->water->getSprite().GetSize();
    sf::Vector2f plane1_size = this->plane1->plane_sprite.GetSize();
    sf::Vector2f plane2_size = this->plane2->plane_sprite.GetSize();
    plane1->plane_sprite.SetCenter(plane1_size.x/2,plane1_size.y/2);
    plane2->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);
    
    // planes shadows sprites (they could be different)
    sf::Sprite plane1_shadow = plane1->plane_sprite;
    plane1_shadow.SetColor(sf::Color(0,0,0,128));
    sf::Sprite plane2_shadow = plane2->plane_sprite;
    plane2_shadow.SetColor(sf::Color(0,0,0,128));
    
    
    // these will keep track of planes shadows positions
    sf::Vector2f shadow1_pos;
    sf::Vector2f shadow2_pos;
    
    // adjust sprites center (needed for dealing nicely with scaling)
    field_sprite.SetCenter(field_size.x/2,field_size.y/2);
    field_sprite.SetPosition(field_size.x/2,field_size.y/2);
    
    while(this->handleEvents())
    {
        if (this->theClock.GetElapsedTime() < 0.05) continue;
        
        switch(this->CurrentState){
            case Field::INIT:
                // HERE WE INITIALIZE THINGS
                // set kicker message
                this->kicker->setMessage("Initializing stuff");
                this->kicker->setDetails("enhancing funnyness...");
                
                // planes positions
                this->plane1->getPosition(p1pos);
                this->plane2->getPosition(p2pos);
                
                this->CurrentState = Field::PLAYER_SELECT;
                break;
                
            case Field::PLAYER_SELECT:
                // set kicker message
                this->kicker->setMessage("Choose your move (use ARROWS):");
                this->kicker->setDetails("[left] LEFT - [up] FORWARD - [right] RIGHT");
                
                if(player_choices.size() < CHOICES_PER_TURN){ // THERE ARE STILL CARDS TO BE CHOSEN
                    if(this->lastEvent.Type == sf::Event::KeyPressed){
                        switch(this->lastEvent.Key.Code){
                            case sf::Key::Right: // TODO: watch out! because of y inversion, "left" becomes "right"
                                player_choices.push_back(this->plane1->getCardSet()->cards);
                                break;
                            case sf::Key::Left:
                                player_choices.push_back(this->plane1->getCardSet()->cards+1);
                                break;
                            case sf::Key::Up:
                                player_choices.push_back(this->plane1->getCardSet()->cards+2);
                                break;
                            default:
                                break;
                        }
                    }
                }
                else{
                    this->CurrentState = Field::BRAIN_SELECT;
#if DEBUG
                LOGMESSAGE("Player has chosen!");
#endif
                }
                break;
                
            case Field::BRAIN_SELECT:
                // set kicker message
                this->kicker->setMessage("AI is choosing...");
                this->kicker->setDetails("it's so clever!");
                
                ai_choices = theBrain->returnBestCards(CHOICES_PER_TURN,MAX_THINK_TIME);     // for the moment, this chooses 1 card
#if DEBUG
                LOGMESSAGE("AI has chosen!");
#endif
                this->CurrentState = Field::APPLY_MOVES;
                break;
                
            case Field::APPLY_MOVES:
                // TODO: add support for moves sequences
                // for the moment, this only takes the first of the chosen cards
                
                // set kicker message
                this->kicker->setMessage("WOOSH!");
                this->kicker->setDetails("");
                
                // store positions before moving
                this->plane1->getPosition(plane1_prev_pos);
                this->plane2->getPosition(plane2_prev_pos);
                
                // logically move the planes
                plane1->move(player_choices[0]);
                plane2->move(ai_choices[0]);
                
                // get position after move
                plane1->getPosition(plane1_final_pos);
                plane2->getPosition(plane2_final_pos);
                
                // construct the animations
                animation1 = new Animation(plane1_prev_pos[0], plane1_prev_pos[1], plane1_prev_pos[2], plane1_final_pos[0], plane1_final_pos[1], plane1_final_pos[2]);
                animation2 = new Animation(plane2_prev_pos[0], plane2_prev_pos[1], plane2_prev_pos[2], plane2_final_pos[0], plane2_final_pos[1], plane2_final_pos[2]);
                
                this->CurrentState = Field::ANIM_MOVES;
                break;
                
            case Field::ANIM_MOVES:
                something_moved = false;
                
                if (animation1->nextStep(p1pos))
                    something_moved = true;
                if (animation2->nextStep(p2pos))
                    something_moved = true;
                
                if(!something_moved)
                    this->CurrentState = Field::COMPUTE_DAMAGES;
                
                break;
                
            case Field::COMPUTE_DAMAGES:
                // set kicker message
                this->kicker->setMessage("BUM BUM BUM!");
                this->kicker->setDetails("");
                
                this->CurrentState = Field::ANIM_DAMAGES;
                break;
                
            case Field::ANIM_DAMAGES:
                this->CurrentState = Field::CHECK_FINISH;
                break;
                
            case Field::CHECK_FINISH: // this will also destroy things and clear stuff
                delete animation1;
                delete animation2;
                player_choices.clear();
                
                // CHECK WIN/LOSE CONDITIONS
                this->CurrentState = Field::PLAYER_SELECT;
                break;
            default:
                break;
        }
        // END OF SWITCH
        
        // set planes positions
        plane1->plane_sprite.SetPosition(p1pos[0] + _xdisplacement, p1pos[1] + _ydisplacement);
        plane1->plane_sprite.SetRotation(radiants2degrees(p1pos[2]));
        plane2->plane_sprite.SetPosition(p2pos[0] + _xdisplacement, p2pos[1] + _ydisplacement);
        plane2->plane_sprite.SetRotation(radiants2degrees(p2pos[2]));
        
        // compute and set shadows positions
        shadow1_pos = this->plane1->plane_sprite.GetPosition();
        shadow1_pos.x+=10;
        shadow1_pos.y+=15;
        plane1_shadow.SetPosition(shadow1_pos);
        plane1_shadow.SetRotation(radiants2degrees(p1pos[2]));
        shadow2_pos = this->plane2->plane_sprite.GetPosition();
        shadow2_pos.x+=10;
        shadow2_pos.y+=15;
        plane2_shadow.SetPosition(shadow2_pos);
        plane2_shadow.SetRotation(radiants2degrees(p2pos[2]));
        
        // update the water tile(waves effect)
        this->water->update(0);
        
        _window->Clear(sf::Color(0,0,0));
        
        _window->SetView(this->camera);
        
        // TODO: adjust this, it is just for testing
        for(int i=0;i<30;i++){
                for(int j=0;j<30;j++)
                {
                    water->setPos(i*water_size.x*2,j*water_size.y*2);
                    _window->Draw(water->getSprite());
                }
        }
        
        // Now draw things...
        _window->Draw(plane1_shadow);
        _window->Draw(plane2_shadow);
        _window->Draw(plane1->plane_sprite);
        _window->Draw(plane2->plane_sprite);
        
        // KICKER
       kicker->draw();
        
        //CARDS TEST --------------
       _window->Draw(cards[0]->cardSprite);
       _window->Draw(cards[1]->cardSprite);
       _window->Draw(cards[2]->cardSprite);
       
        // ...and display them
        _window->SetView(_window->GetDefaultView());
        kicker->display();
        _window->Display();
        
        theClock.Reset();
    }
}

int Field::handleEvents() {
    //note GetEvent ALWAYS in if() or while()
    if(_window->GetEvent(lastEvent))
    {
        switch(lastEvent.Type){
            case sf::Event::KeyPressed:
                switch(lastEvent.Key.Code){
                    case sf::Key::Num1:
                        this->camera.Zoom(1.1f);
                        break;
                    case sf::Key::Num2:
                        this->camera.Zoom(0.9f);
                        break;
                    case sf::Key::Escape:
                        return 0;
                        break;
                    default:
                        break;
                } // END OF KEY.CODE SWITCH
                break;

            case sf::Event::MouseWheelMoved:
                if(lastEvent.MouseWheel.Delta<0) this->camera.Zoom(1.1f);
                else this->camera.Zoom(0.9f);
                break;

            case sf::Event::MouseButtonPressed:
                if (lastEvent.MouseButton.Button == sf::Mouse::Left){
                    _mouse_down = true;
                    _xstart = lastEvent.MouseButton.X;
                    _ystart = lastEvent.MouseButton.Y;

                }
                break;

            case sf::Event::MouseButtonReleased:

                if(lastEvent.MouseButton.Button == sf::Mouse::Left){
                    _mouse_down = false;
                    _xstart = 0;
                    _ystart = 0;
                }

                for(int i=0;i<clickableAreas.size();i++)
                {
                    //check if the click is inside for EACH clickableAreas rectangle 
                    //note: rect has a "contains" methods, unluckly... doesn't works -_-"
                    if(
                    lastEvent.MouseButton.X>=clickableAreas[i]->Left &&
                    lastEvent.MouseButton.Y>=clickableAreas[i]->Top &&
                    lastEvent.MouseButton.X<=clickableAreas[i]->Left+clickableAreas[0]->Right &&
                    lastEvent.MouseButton.Y<=clickableAreas[i]->Top+clickableAreas[0]->Bottom)

                        {
                            //the clicked card isn't active
                            if(cards[i]->activated==0)
                            {    
                                //deactivate each card of the deck
                                for(int j=0;j<clickableAreas.size();j++) cards[j]->deActivateCard();
                                //activate the "i" card
                                cards[i]->activateCard();
                            }
                            //the "i" card is already activated, so deactivate it
                            else if(cards[i]->activated==1)cards[i]->deActivateCard();

                            //note:
                            //this basic mechanism will be useful for a selectable sequence of card (i.e card1, card2.... cardN then confim!)
                        }
                }
                break;

            case sf::Event::MouseMoved:
                if(_mouse_down){
                    _xdisplacement += lastEvent.MouseMove.X - _xstart;
                    _ydisplacement += lastEvent.MouseMove.Y - _ystart;
                    if (_xdisplacement < 0) _xdisplacement = 0;
                    if (_xdisplacement > this->theWorld->getWidth()) _xdisplacement = this->theWorld->getWidth();
                    if (_ydisplacement < 0) _ydisplacement = 0;
                    if (_ydisplacement > this->theWorld->getHeight()) _ydisplacement = this->theWorld->getHeight();
                    _xstart = lastEvent.MouseMove.X;
                    _ystart = lastEvent.MouseMove.Y;
                }
                break;

            default:
                break;
        }// END OF LASTEVENT.TYPE SWITCH

        return 1;
    }
    return 1;
}


