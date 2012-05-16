/* 
 */

#include "Field.h"

Field::Field(sf::RenderWindow  *refwindow) {
    
    _window=refwindow;
    
    plane1= new Plane(0,10,200,150,30);
    plane1->plane_sprite.SetColor(sf::Color(255,0,0));
    plane2= new Plane(1,10,100,100,45);
    plane2->plane_sprite.SetColor(sf::Color(0,255,0));
    
    field_image.LoadFromFile("assets/field.png");
    field_sprite.SetImage(field_image);

    this->loop();
}


Field::~Field() {
}

void Field::loop()
{
    while(this->handleEvents()==1)
    {
        
        float pos[3];
        
        plane1->getPosition(pos);
        plane1->plane_sprite.SetPosition(pos[0],pos[1]);
        plane1->plane_sprite.SetRotation(pos[3]);
        
        plane2->getPosition(pos);
        plane2->plane_sprite.SetPosition(pos[0],pos[1]);
        plane2->plane_sprite.SetRotation(pos[3]);
        
        _window->Draw(field_sprite);
        _window->Draw(plane1->plane_sprite);
        _window->Draw(plane2->plane_sprite);
        _window->Display();
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


