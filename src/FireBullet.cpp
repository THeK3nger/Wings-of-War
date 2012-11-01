#include "wowcommon.h"
#include "FireBullet.h"

#include "resources/ImageRes.h"
#include "resources/ResourcesManager.h"

FireBullet::FireBullet(float start_x, float start_y, float final_x, float final_y, sf::RenderWindow *refwindow) :
    _xi(start_x), _yi(start_y), _visible(true),
    _xf(final_x), _yf(final_y), _step(0), _bullet_velocity(10)
{
    _bullet_image = GET_SFML_IMAGE_FROM_MANAGER("firebullet");
    _bullet_sprite.SetImage(_bullet_image);
    _angle = atan2(-(_yf - _yi),(_xf - _xi));
    _refwindow = refwindow;
    _current_x = _xi;
    _current_y =_yi;
    _bullet_sprite.SetPosition(_current_x,_current_y);
    _bullet_sprite.SetRotation(radiants2degrees(_angle));
}

FireBullet::~FireBullet() {}

void FireBullet::setBulletVelocity(float v) { _bullet_velocity = v; }

bool FireBullet::isVisible() { return _visible; }

void FireBullet::update() {
    _step += _bullet_velocity;

    _current_x += cos(_angle)*_bullet_velocity;
    _current_y -= sin(_angle)*_bullet_velocity;

    _bullet_sprite.SetPosition(_current_x,_current_y);
    _bullet_sprite.SetRotation(radiants2degrees(_angle));

    // TODO: We need a more accurate check...
    if (abs(_current_x - _xf) < 10 || abs(_current_y -_yf) < 10) _visible = false;
}

void FireBullet::draw() {
    if (_visible) {
        _refwindow->Draw(_bullet_sprite);
    }
}
