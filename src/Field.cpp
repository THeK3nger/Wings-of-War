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
    theWorld = new World(800, 600);
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
    
    
    cardCounter=0;
    //pointer to card image, instance to a generic cardImage with id=0
    CardImage* card = new CardImage(0,420,450,_window,&cardmaster);
    //adding the cardImage to the cards vector
    cards.push_back(card);
    
    //same
    card = new CardImage(1,520,450,_window,&cardmaster);
    cards.push_back(card);
    
    //same
    card = new CardImage(2,620,450,_window,&cardmaster);
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
    this->status = INGAME;
    this->loop();
}

Field::~Field() {
}

void Field::loop() {
    // Definition of useful stuff
    bool game_finished = false; // will be TRUE when the game has ended
    
    float angle=0;
    
    float p1pos [3];    // these two arrays will keep track of the displayed position of the planes in the window
    float p2pos [3];
    
    bool plane1_out = false;    // these two booleans are used to signal that planes have gone out of bounds
    bool plane2_out = false;
    
    std::vector<Card*> player_choices; // used to store player's choices
    std::vector<Card*> ai_choices; // used to ask to THE BRAIN which cards should be chosen
    
    int moves_counter = 0;      // used to understand how many move cards have already been applied
    bool something_moved;       // used to signal animations are over
    
    Animation * animation1;     // used for animating the first plane
    Animation * animation2;     // used for animating the second plane
    
    float plane1_prev_pos[3];   // these four arrays will be used to correctly construct the animations
    float plane1_final_pos [3];
    float plane2_prev_pos[3];
    float plane2_final_pos [3];
    
    bool kicker_was_changed = true; // this is used to avoid continuous replacement of the kicker content
    
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
    
    while(this->handleEvents() && this->status != TERMINATED)
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
                if (kicker_was_changed){ // this is to avoid continuously replacing it
                    this->kicker->setMessage("Choose your moves (use ARROWS):");
                    this->kicker->setDetails("[left] LEFT - [up] FORWARD - [right] RIGHT");
                    kicker_was_changed = false;
                }
                
                if(player_choices.size() < CHOICES_PER_TURN){ // THERE ARE STILL CARDS TO BE CHOSEN
                    if(this->lastEvent.Type == sf::Event::KeyPressed){
                        switch(this->lastEvent.Key.Code){
                            case sf::Key::Right: // TODO: watch out! because of y inversion, "left" becomes "right"
                                player_choices.push_back(this->plane1->getCardSet()->cards);
                                #if DEBUG
                                LOGMESSAGE("You have chosen a move");
                                #endif
                                break;
                            case sf::Key::Left:
                                player_choices.push_back(this->plane1->getCardSet()->cards+1);
                                #if DEBUG
                                LOGMESSAGE("You have chosen a move");
                                #endif
                                break;
                            case sf::Key::Up:
                                player_choices.push_back(this->plane1->getCardSet()->cards+2);
                                #if DEBUG
                                LOGMESSAGE("You have chosen a move");
                                #endif
                                break;
                            default:
                                break;
                        }
                    }
                }
                else{
                    kicker_was_changed = true;
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
                // set kicker message
                this->kicker->setMessage("WOOSH!");
                this->kicker->setDetails("");
                
                // store positions before moving
                this->plane1->getPosition(plane1_prev_pos);
                this->plane2->getPosition(plane2_prev_pos);
                
                // logically move the planes
                plane1->move(player_choices[moves_counter]);
                plane2->move(ai_choices[moves_counter]);
                
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
                
                // if some plane is out of bounds, destroy it
                if (!this->theWorld->isInside(plane1)){
                    plane1_out = true;
                    plane1->inflictDamage(plane1->remainingHealth());
                }
                if (!this->theWorld->isInside(plane2)){
                    plane2_out = true;
                    plane2->inflictDamage(plane2->remainingHealth());
                }
                if ((!plane1_out) && plane1->canShootTo(plane2)){
#if DEBUG
                    LOGMESSAGE("PLANE1 SHOT TO PLANE2");
#endif
                    plane2->inflictDamage(this->theBrain->expectedDamage());
                }
                if ((!plane2_out) && plane2->canShootTo(plane1)){
                    plane1->inflictDamage(this->theBrain->expectedDamage());
#if DEBUG
                    LOGMESSAGE("PLANE2 SHOT TO PLANE1");
#endif
                }
                
#if DEBUG
                std::cout << "remaining health -- PLANE1: " << plane1->remainingHealth() << ", Plane2: " << plane2->remainingHealth() << '\n';
#endif
                
                this->CurrentState = Field::ANIM_DAMAGES;
                break;
                
            case Field::ANIM_DAMAGES:
                // TODO: add some animation to represent shooting actions
                
                this->CurrentState = Field::CHECK_FINISH;
                break;
                
            case Field::CHECK_FINISH: // this will also destroy things and clear stuff
                
                // CHECK WIN/LOSE CONDITIONS
                if (plane1_out){ // opponent plane is out of bounds
                    game_finished = true;
                    if (plane2_out){ // BOTH planes out of bounds
#if DEBUG
                        LOGMESSAGE("both planes out of bounds!");
#endif
                        kicker->setDetails("DRAW, they all got lost somewhere...");
                    }
                    else{ // ONLY OPPONENT is out of bounds
#if DEBUG
                        LOGMESSAGE("PLAYER out of bounds!");
#endif
                        kicker->setDetails("PLAYER got lost...");
                    }
                }
                else if (plane2_out){   // ONLY AI plane out of bounds
                    game_finished = true;
#if DEBUG
                    LOGMESSAGE("AI PLANE out of bounds!");
#endif
                    kicker->setDetails("AI got lost...");
                }
                
                if (!game_finished){    // check other finish conditions
                    if (plane1->remainingHealth() <= 0){ // PLAYER DIED
                        game_finished = true;
                        if (plane2->remainingHealth() <= 0){ // AI DIED TOO
#if DEBUG
                        LOGMESSAGE("BOTH PLANES destroyed!");
#endif
                        kicker->setDetails("Both planes down: DRAW!");
                        }
                        else{
#if DEBUG
                            LOGMESSAGE("OPPONENT destroyed!");
#endif
                            kicker->setDetails("Plane1 destroyed: YOU LOST!");
                        }
                    }
                    else if(plane2->remainingHealth() <= 0){ // ONLY AI DIED
                        game_finished = true;
#if DEBUG
                        LOGMESSAGE("AI plane destroyed!");
#endif
                        kicker->setDetails("Plane2 destroyed: YOU WIN!");
                    }
                }
                
                if(!game_finished){     // if the game is not over
                    moves_counter++;

                    if(moves_counter < CHOICES_PER_TURN){
                        this->CurrentState = Field::APPLY_MOVES;
                    }
                    else{
                        moves_counter = 0;
                        delete animation1;
                        delete animation2;
                        player_choices.clear();
                        
                        this->CurrentState = Field::PLAYER_SELECT;
                    }
                }
                else{   // if the game is over
                    delete animation1;
                    delete animation2;
                    player_choices.clear();
                    
                    kicker->setMessage("GAME FINISHED");
                    this->CurrentState = Field::SHOW_INFOS;
                }
                break;
                
            case Field::SHOW_INFOS:     // we can add something here that shows infos at the end of the game, such as moves performed and damages received by planes
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
        
        // Set the camera according to the zoom
        _window->SetView(this->camera);
        
        // TODO: adjust this, it is just for testing
        for(int i=0;i<=(int)(theWorld->getWidth()/(2*water_size.x));i++){
                for(int j=0;j<=(int)(theWorld->getHeight()/(2*water_size.y));j++)
                {
                    water->setPos(i*water_size.x*2+_xdisplacement,j*water_size.y*2+_ydisplacement);
                    _window->Draw(water->getSprite());
                }
        }
        
        // Now draw things that must be affected by the zoom...
        _window->Draw(plane1_shadow);
        _window->Draw(plane2_shadow);
        _window->Draw(plane1->plane_sprite);
        _window->Draw(plane2->plane_sprite);
        
        // Now draw things of fixed size
        _window->SetView(_window->GetDefaultView());
        
        // KICKER
       kicker->draw();
        
        //CARDS TEST --------------
       cards[0]->draw();
       cards[1]->draw();
       cards[2]->draw();
       
        // ...and display everything
//        kicker->display(); // NOT NEEDED! This just calls kicker->_window->Dislay(), hence it's a repetition
        _window->Display();
        
        theClock.Reset();
    }
}

/************ EVENT HANDLER **********/

void Field::zoom(float z)
{
    this->camera.Zoom(z);
}

void Field::stop()
{
    this->status = TERMINATED;
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

    /* TODO: ClickableAreas method? */
    for(int i=0;i<clickableAreas.size();i++)
    {
        //check if the click is inside for EACH clickableAreas rectangle
        //note: rect has a "contains" methods, unluckly... doesn't works -_-"
        double active_offset = 0;
        if(cards[i]->activated) active_offset = 50;
        if(
        x>=clickableAreas[i]->Left &&
        y>=clickableAreas[i]->Top - active_offset &&
        x<=clickableAreas[i]->Left+clickableAreas[0]->Right &&
        y<=clickableAreas[i]->Top - active_offset + clickableAreas[0]->Bottom)

            {
                //the clicked card isn't active
                if(cards[i]->activated==0)
                {
                    //deactivate each card of the deck
                    //for(int j=0;j<clickableAreas.size();j++) cards[j]->deActivateCard();
                    //activate the "i" card
                    cardmaster.insert(std::pair<int,int>(i,cardCounter));
                    cards[i]->activateCard();
                    cardCounter++;

                }
                //the "i" card is already activated, so deactivate it
                else if(cards[i]->activated==1)
                {
                    for(int j=0;j<cards.size();j++)
                    {
                    it=cardmaster.find(j);
                    if(it!=cardmaster.end())
                    {
                        cardmaster.erase(it);
                        cardCounter--;
                    }
                    cards[j]->deActivateCard();

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
        if (-_xdisplacement > this->theWorld->getWidth()) _xdisplacement = -this->theWorld->getWidth();
        if (_ydisplacement > 0) _ydisplacement = 0;
        if (-_ydisplacement > this->theWorld->getHeight()) _ydisplacement = -this->theWorld->getHeight();
        _xstart = x;
        _ystart = y;
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
                        zoom(1.1f);
                        break;
                    case sf::Key::Num2:
                        zoom(0.9f);
                        break;
                    case sf::Key::Escape:
                        stop();
                        break;
                    default:
                        break;
                } // END OF KEY.CODE SWITCH
                break;

            case sf::Event::MouseWheelMoved:
                if(lastEvent.MouseWheel.Delta<0) zoom(1.1f);
                else zoom(0.9f);
                break;

            case sf::Event::MouseButtonPressed:
                if (lastEvent.MouseButton.Button == sf::Mouse::Left){
                    mouseLeftPressed(lastEvent.MouseButton.X,lastEvent.MouseButton.Y);
                }
                break;

            case sf::Event::MouseButtonReleased:
                if(lastEvent.MouseButton.Button == sf::Mouse::Left){
                    mouseLeftReleased(lastEvent.MouseButton.X,lastEvent.MouseButton.Y);
                }
                break;

            case sf::Event::MouseMoved:
                mouseMoved(lastEvent.MouseMove.X,lastEvent.MouseMove.Y);
                break;

            default:
                break;
        }// END OF LASTEVENT.TYPE SWITCH

        return 1;
    }
    return 1;
}


