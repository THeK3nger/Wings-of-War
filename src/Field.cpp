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
    
    LOGMESSAGE_NO_ENDL("Field Loaded!"); OK;
    this->loop();
}

Field::~Field() {
}

void Field::loop() {
    // Definition of useful stuff
    Kicker* kicker = new Kicker(_window);
    float angle=0;
    //float acc=0; // NO NEED OF THIS
    
    float p1pos [3];    // these two arrays will keep track of the displayed position of the planes in the window
    float p2pos [3];
    
    std::vector<Card*> player_choices; // used to store player's choices
    std::vector<Card*> ai_choices; // used to ask to THE BRAIN which cards should be chosen
    
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
        if (this->theClock.GetElapsedTime() < 0.01) //MAX FRAMERATE
            continue;
        
        switch(this->CurrentState){
            case Field::INIT:
                // HERE WE INITIALIZE THINGS
                // planes positions
                this->plane1->getPosition(p1pos);
                this->plane2->getPosition(p2pos);
                
                this->CurrentState = Field::PLAYER_SELECT;
                break;
                
            case Field::PLAYER_SELECT:
                // TODO: HERE THE PLAYER SHOULD CHOOSE HIS/HER MOVE, for now it chooses a predetermined card
                player_choices.clear();
                player_choices.push_back(this->plane1->getCardSet()->cards);
#if DEBUG
                LOGMESSAGE("Player has chosen!");
#endif
                this->CurrentState = Field::BRAIN_SELECT;
                break;
                
            case Field::BRAIN_SELECT:
                ai_choices = theBrain->returnBestCards(1,MAX_THINK_TIME);     // for the moment, this chooses 1 card
#if DEBUG
                LOGMESSAGE("AI has chosen!");
#endif
                this->CurrentState = Field::APPLY_MOVES;
                break;
                
            case Field::APPLY_MOVES:
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
                if( !(animation1->nextStep(p1pos)) && !(animation2->nextStep(p2pos))){
                    delete animation1;
                    delete animation2;
                    this->CurrentState = Field::COMPUTE_DAMAGES;
                }
                
                break;
                
            case Field::COMPUTE_DAMAGES:
                this->CurrentState = Field::ANIM_DAMAGES;
                break;
                
            case Field::ANIM_DAMAGES:
                this->CurrentState = Field::CHECK_FINISH;
                break;
                
            case Field::CHECK_FINISH:
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
                    water->setPos(i*water_size.x,j*water_size.y);
                    _window->Draw(water->getSprite());
                }
        }
        
        // Now draw things...
        _window->Draw(plane1_shadow);
        _window->Draw(plane2_shadow);
        _window->Draw(plane1->plane_sprite);
        _window->Draw(plane2->plane_sprite);
        
        // ...and display them
        _window->SetView(_window->GetDefaultView());
        kicker->display();
        _window->Display();
        
        theClock.Reset();
        
        //INPUT HANDLING
                
//        if (CurrentState == Field::playerSelect) 
//            {
//                
//
//                //Dialog* CardDialog = new Dialog(_window,title,message);
//
//                int tastoPremuto;
//
//                if(this->handleEvents())
//                {
//                    //printf("Tasto premuto %d \n", tastoPremuto); //49 = 1, 50 = 2, 51=3
//
//                    if (tastoPremuto == 49)
//                        plane1->move(&(plane1->getCardSet()->cards[0]));
//
//                    if (tastoPremuto == 50)
//                        plane1->move(&(plane1->getCardSet()->cards[1]));
//
//                    if (tastoPremuto == 51)
//                        plane1->move(&(plane1->getCardSet()->cards[2]));
//
//                    CurrentState = Field::brainSelect;
//                }
//            }
        //END INPUT HANDLING
        
//        // AI CHOOSES ITS MOVE
//        if (CurrentState == Field::brainSelect){
//            std::vector<Card*> best_moves = this->theBrain->returnBestCards(20);
//            this->theBrain->getAIPlane()->move(best_moves[0]);
//        }
//        // AI HAS CHOSEN IT'S MOVE
//        
//        
//        if (acc>=0.01) //MAX FRAMERATE
//        {
//            if (animation->nextStep(p2pos)){
//                plane2->setX(p2pos[0]);
//                plane2->setY(p2pos[1]);
//                plane2->setT(p2pos[2]);
//            }
//            
//            //Dimensione della sprite del field
//            sf::Vector2f field_size=field_sprite.GetSize();
//            //Configuro il centro della sprite del field al centro della sprite e non all'angolo in alto a sx
//            field_sprite.SetCenter(field_size.x/2,field_size.y/2);
//            field_sprite.SetPosition(field_size.x/2,field_size.y/2);
//            //Tutto sto casino mi serve per avere un comportamente coerente quando effettuo lo scaling
//            //field_sprite.SetScale(_globalscale,_globalscale);
//
//            CurrentState = Field::playerSelect;
//            float pos1[3];
//            float pos2[3];
//            plane1->getPosition(pos1);
//
//            //printf("X: %f Y: %f THETA: %f \n", pos[0], pos[1], pos[2]);
//
//            // TODO: not "this->_window->GetHeight()", but world->height
//
//            //stesso discorso del field
//            sf::Vector2f plane1_size = plane1->plane_sprite.GetSize();
//            plane1->plane_sprite.SetCenter(plane1_size.x/2,plane1_size.y/2);
//
//            plane1->plane_sprite.SetPosition(pos1[0] + _xdisplacement, this->_window->GetHeight() - pos1[1] + _ydisplacement);
//
//           
//
//
//            //plane1->plane_sprite.SetRotation(pos1[2]*180 / M_PI - 90);
//            
//            plane1->plane_sprite.SetRotation(pos1[2]*180/M_PI);
//            //plane1->plane_sprite.SetScale(_globalscale,_globalscale);
//            //fine aereo 1
//
//
//            //stesso discorso del field
//            sf::Vector2f plane2_size = plane2->plane_sprite.GetSize();
//            plane2->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);
//
//            plane2->getPosition(pos2);
//            plane2->plane_sprite.SetPosition(pos2[0] + _xdisplacement, pos2[1] + _ydisplacement);
//            plane2->plane_sprite.SetRotation(pos2[2]*180 / M_PI);
//            //plane2->plane_sprite.SetScale(_globalscale,_globalscale);
//            //fine aereo 2
//
//            _window->Clear(sf::Color(255,255,255));
//
//
//            
//
//            _window->SetView(camera);
//            water->update(0);
//            sf::Vector2f waterSize = water->getSprite().GetSize();
//            
//            //DIRTY TEST
//            for(int i=0;i<30;i++)
//            {
//                for(int j=0;j<30;j++)
//                {
//                    
//                    water->setPos(i*waterSize.x,j*waterSize.y);
//                    _window->Draw(water->getSprite());
//                }
//            }
//            
//            
//             
//             //OMBRE
//             sf::Sprite planeshadow=plane1->plane_sprite;
//             planeshadow.SetColor(sf::Color(0,0,0,128));
//                     
//             sf::Vector2f shadowpos = plane1->plane_sprite.GetPosition();
//             shadowpos.x+=10;
//             shadowpos.y+=15;
//             planeshadow.SetPosition(shadowpos);
//             planeshadow.SetRotation(pos1[2]*180 / M_PI);
//             _window->Draw(planeshadow);
//             
//             shadowpos = plane2->plane_sprite.GetPosition();
//             shadowpos.x+=10;
//             shadowpos.y+=10;
//             planeshadow.SetPosition(shadowpos);
//             planeshadow.SetRotation(pos2[2]*180 / M_PI);
//             _window->Draw(planeshadow);
//             //FINE OMBRE
//              
//             
//             //TEST rotazione
//             
//             float tx;
//             float ty;
//             tx=pos1[0];
//             ty=pos1[1];
//             
//             tx=cos(angle)+tx;
//             ty=sin(angle)+ty;
//             
//             angle+=0.01f;
//             
//             plane1->setX(tx);
//             plane1->setY(ty);
//             plane1->setT(angle);
//             
//            _window->Draw(plane1->plane_sprite);
//            _window->Draw(plane2->plane_sprite);
//            
//            //SHADOWS
//            
//           
//            
//            
//            _window->SetView(_window->GetDefaultView());
//            kicker->display();
//            _window->Display();
//
//           //accumulator reset
//            acc=0;
//            
//        }
//        
//        //adding elapsed time to the accumulator
//        acc+=theClock.GetElapsedTime();
//        //resetting the clock
//        theClock.Reset();
        
        
        
    }
}

int Field::handleEvents() {
    sf::Event Event;
    _window->GetEvent(Event);
    
    if(Event.Type == sf::Event::KeyPressed)
    {
        
       if(Event.Key.Code == sf::Key::Num1)
       {
           
           camera.Zoom(1.1f);
       }
       
        if(Event.Key.Code == sf::Key::Num2)
       {
          
          camera.Zoom(0.9f);
       }
        
        if (Event.Key.Code == sf::Key::Escape) {
            return 0;
        }
       
    }
    
    
    if (Event.Type == sf::Event::MouseWheelMoved)
        {
             
            if(Event.MouseWheel.Delta<0) camera.Zoom(1.1f);
            if(Event.MouseWheel.Delta>0) camera.Zoom(0.9f);
        }
    
    
    if(Event.Type == sf::Event::MouseButtonPressed || Event.Type == sf::Event::MouseButtonReleased || Event.Type == sf::Event::MouseMoved)
    {
        if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Left)) {
            _mouse_down = true;
            _xstart = Event.MouseButton.X;
            _ystart = Event.MouseButton.Y;
            
        }
        if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left)) {
            _mouse_down = false;
            _xstart = 0;
            _ystart = 0;
            
        }
        if ((Event.Type == sf::Event::MouseMoved) && _mouse_down) 
        {
            _xdisplacement += Event.MouseMove.X - _xstart;
            _ydisplacement += Event.MouseMove.Y - _ystart;
            if (_xdisplacement < 0) _xdisplacement = 0;
            if (_xdisplacement > this->theWorld->getWidth()) _xdisplacement = this->theWorld->getWidth();
            if (_ydisplacement < 0) _ydisplacement = 0;
            if (_ydisplacement > this->theWorld->getHeight()) _ydisplacement = this->theWorld->getHeight();
            _xstart = Event.MouseMove.X;
            _ystart = Event.MouseMove.Y;
        }
    }
  
    return 1;
}


