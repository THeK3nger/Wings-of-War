/* 
 */

#include "Field.h"

Field::Field(sf::RenderWindow  *refwindow) {
    
    _window=refwindow;
    
    CurrentState = Field::init;
    
    plane1= new Plane(0,10,200,500,0);
    plane1->plane_sprite.SetColor(sf::Color(255,0,0));
    
    
    plane2= new Plane(1,10,100,100,45);
    plane2->plane_sprite.SetColor(sf::Color(0,255,0));
    
    field_image.LoadFromFile("assets/field.png");
    field_sprite.SetImage(field_image);
    
    theWorld = new World(800,600);
    theBrain = new WoWBrain(plane2,theWorld);
    
    this->loop();
}


Field::~Field() {
}

void Field::loop()
{
    CurrentState = Field::playerSelect;
    
    while(1)
    {
         CurrentState = Field::playerSelect;
        float pos[3];
        
        plane1->getPosition(pos);
        printf("X: %f Y: %f THETA: %f \n",pos[0],pos[1],pos[2]);
        
        plane1->plane_sprite.SetPosition(pos[0],pos[1]);
        plane1->plane_sprite.SetRotation(-pos[2]*180/M_PI-90);
        
        plane2->getPosition(pos);
        plane2->plane_sprite.SetPosition(pos[0],pos[1]);
        plane2->plane_sprite.SetRotation(pos[2]);
        
        _window->Draw(field_sprite);
        _window->Draw(plane1->plane_sprite);
        _window->Draw(plane2->plane_sprite);
        _window->Display();
        
        while(CurrentState==Field::playerSelect)
        {
            sf::String title; title.SetText("Choose your destiny");
            sf::String message; message.SetText("[1] Left [2] Forward [3] Right");
            title.SetSize(30.0f);
            message.SetSize(20.0f);
            title.SetPosition(200.0f,200.0f);
            message.SetPosition(200.0f,250.0f);
            
            Dialog* CardDialog = new Dialog(_window,title,message);
            int tastoPremuto;
            tastoPremuto=CardDialog->run();
      
           printf("Tasto premuto %d \n",tastoPremuto); //49 = 1, 50 = 2, 51=3
           if(tastoPremuto==49)
           plane1->move(&(plane1->getCardSet()->cards[0]));
           
           if(tastoPremuto==50)
           plane1->move(&(plane1->getCardSet()->cards[1]));
           
           if(tastoPremuto==51)
           plane1->move(&(plane1->getCardSet()->cards[2]));

            CurrentState=Field::brainSelect;
            
        }
        
    }
}


bool Field::handleEvents()
{
    sf::Event Event;
    _window->GetEvent(Event);
    
    if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)
    {
        return 0;
    }
    return 1;
}


