#include "Field.h"
#include <vector>

Field::Field(sf::RenderWindow *refwindow) {

    _window = refwindow;
    
    //Loading the bgmusic file
    _bgmusic.OpenFromFile("assets/field.ogg");
    //Setting the bgmusic volume
    _bgmusic.SetVolume(100.0f);
    //PLaying the bgmusic
    _bgmusic.SetLoop(true);
    _bgmusic.Play();
            
    CurrentState = Field::init;

    plane1 = new Plane(0, 10, 400, 300, 0);
    plane1->plane_sprite.SetColor(sf::Color(255, 0, 0));


    plane2 = new Plane(1, 10, 50, 50, 0);
    plane2->plane_sprite.SetColor(sf::Color(0, 255, 0));

    field_image.LoadFromFile("assets/field.png");
    field_sprite.SetImage(field_image);


    theWorld = new World(2000, 2000);
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
    
    
    this->loop();
}

Field::~Field() {
}

void Field::loop() {
    CurrentState = Field::playerSelect;
    Kicker* kicker = new Kicker(_window);
    
    float angle=0;
    
    float acc=0;
    
    float p2pos [3];
    plane2->getPosition(p2pos);
    
    Animation * animation = new Animation(p2pos[0], p2pos[1], p2pos[2], 300, 300, 0);
    
    while(this->handleEvents())
    {
        
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
        
        // AI CHOOSES ITS MOVE
        if (CurrentState == Field::brainSelect){
            std::vector<Card*> best_moves = this->theBrain->returnBestCards(20);
            this->theBrain->getAIPlane()->move(best_moves[0]);
        }
        // AI HAS CHOSEN IT'S MOVE
        
        
        if (animation->nextStep(p2pos)){
            plane2->setX(p2pos[0]);
            plane2->setY(p2pos[1]);
            plane2->setT(p2pos[2]);
        }
        
        
        if (acc>=0.01) //MAX FRAMERATE
        {
            
            //Dimensione della sprite del field
            sf::Vector2f field_size=field_sprite.GetSize();
            //Configuro il centro della sprite del field al centro della sprite e non all'angolo in alto a sx
            field_sprite.SetCenter(field_size.x/2,field_size.y/2);
            field_sprite.SetPosition(field_size.x/2,field_size.y/2);
            //Tutto sto casino mi serve per avere un comportamente coerente quando effettuo lo scaling
            //field_sprite.SetScale(_globalscale,_globalscale);

            CurrentState = Field::playerSelect;
            float pos1[3];
            float pos2[3];
            plane1->getPosition(pos1);

            //printf("X: %f Y: %f THETA: %f \n", pos[0], pos[1], pos[2]);

            // TODO: not "this->_window->GetHeight()", but world->height

            //stesso discorso del field
            sf::Vector2f plane1_size = plane1->plane_sprite.GetSize();
            plane1->plane_sprite.SetCenter(plane1_size.x/2,plane1_size.y/2);

            plane1->plane_sprite.SetPosition(pos1[0] + _xdisplacement, this->_window->GetHeight() - pos1[1] + _ydisplacement);

           


            //plane1->plane_sprite.SetRotation(pos1[2]*180 / M_PI - 90);
            
            plane1->plane_sprite.SetRotation(pos1[2]*180/M_PI);
            //plane1->plane_sprite.SetScale(_globalscale,_globalscale);
            //fine aereo 1


            //stesso discorso del field
            sf::Vector2f plane2_size = plane2->plane_sprite.GetSize();
            plane2->plane_sprite.SetCenter(plane2_size.x/2,plane2_size.y/2);

            plane2->getPosition(pos2);
            plane2->plane_sprite.SetPosition(pos2[0] + _xdisplacement, pos2[1] + _ydisplacement);
            plane2->plane_sprite.SetRotation(pos2[2]*180 / M_PI);
            //plane2->plane_sprite.SetScale(_globalscale,_globalscale);
            //fine aereo 2

            _window->Clear(sf::Color(255,255,255));


            

            _window->SetView(camera);
            water->update(0);
            sf::Vector2f waterSize = water->getSprite().GetSize();
            
            //DIRTY TEST
            for(int i=0;i<30;i++)
            {
                for(int j=0;j<30;j++)
                {
                    
                    water->setPos(i*waterSize.x,j*waterSize.y);
                    _window->Draw(water->getSprite());
                }
            }
            
            
             
             //OMBRE
             sf::Sprite planeshadow=plane1->plane_sprite;
             planeshadow.SetColor(sf::Color(0,0,0,128));
                     
             sf::Vector2f shadowpos = plane1->plane_sprite.GetPosition();
             shadowpos.x+=10;
             shadowpos.y+=15;
             planeshadow.SetPosition(shadowpos);
             planeshadow.SetRotation(pos1[2]*180 / M_PI);
             _window->Draw(planeshadow);
             
             shadowpos = plane2->plane_sprite.GetPosition();
             shadowpos.x+=10;
             shadowpos.y+=10;
             planeshadow.SetPosition(shadowpos);
             planeshadow.SetRotation(pos2[2]*180 / M_PI);
             _window->Draw(planeshadow);
             //FINE OMBRE
              
             
             //TEST rotazione
             
             float tx;
             float ty;
             tx=pos1[0];
             ty=pos1[1];
             
             tx=cos(angle)+tx;
             ty=sin(angle)+ty;
             
             angle+=0.01f;
             
             plane1->setX(tx);
             plane1->setY(ty);
             plane1->setT(angle);
             
            _window->Draw(plane1->plane_sprite);
            _window->Draw(plane2->plane_sprite);
            
            //SHADOWS
            
           
            
            
            _window->SetView(_window->GetDefaultView());
            kicker->display();
            _window->Display();

           //accumulator reset
            acc=0;
            
        }
        
        //adding elapsed time to the accumulator
        acc+=theClock.GetElapsedTime();
        //resetting the clock
        theClock.Reset();
        
        
        
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
            _xstart = Event.MouseMove.X;
            _ystart = Event.MouseMove.Y;
            //printf("X: %i,              Y: %i\n", _xdisplacement, _ydisplacement);
        }
        
        
        
       // printf("generic mouse event\n");
    }
  
    return 1;
}


