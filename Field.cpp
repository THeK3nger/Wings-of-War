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
    
    _xstart = 0;
    _ystart = 0;
    _xdisplacement = 0;
    _ydisplacement = 0;
    
    _mouse_down = false;

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
        plane1->plane_sprite.SetPosition(pos[0]+_xdisplacement,pos[1]+_ydisplacement);
        plane1->plane_sprite.SetRotation(pos[3]);
        
        plane2->getPosition(pos);
        plane2->plane_sprite.SetPosition(pos[0]+_xdisplacement,pos[1]+_ydisplacement);
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
    if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Left))
    {
        _mouse_down = true;
        _xstart = Event.MouseButton.X;
        _ystart = Event.MouseButton.Y;
    }
    if ((Event.Type == sf::Event::MouseButtonReleased) && (Event.MouseButton.Button == sf::Mouse::Left))
    {
        _mouse_down = false;
        _xstart = 0;
        _ystart = 0;
    }
    if ((Event.Type == sf::Event::MouseMoved) && _mouse_down) 
    {
        _xdisplacement += Event.MouseMove.X -_xstart;
        _ydisplacement += Event.MouseMove.Y -_ystart;
        _xstart = Event.MouseMove.X;
        _ystart = Event.MouseMove.Y;
        printf("X: %i,              Y: %i\n", _xdisplacement, _ydisplacement);
    }
    return 1;
}


