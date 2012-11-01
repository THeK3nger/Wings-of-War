#ifndef _H_FIREBULLET_
#define _H_FIREBULLET_

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

class FireBullet {
public:
    FireBullet(float start_x, float start_y, float final_x, float final_y, sf::RenderWindow *refwindow);
    ~FireBullet();

    void setBulletVelocity(float t);
    bool isVisible();

    void draw();
    void update();

private:
    float _xi,_yi,_xf,_yf;
    float _current_x, _current_y;
    float _bullet_velocity;
    float _angle;

    float _step;

    sf::Image _bullet_image;
    sf::Sprite _bullet_sprite;

    bool _visible;

    sf::RenderWindow* _refwindow;
};

#endif
