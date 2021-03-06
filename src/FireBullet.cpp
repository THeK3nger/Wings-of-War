#include "wowcommon.h"
#include "FireBullet.h"
#include "Game.h"

#include "resources/ImageRes.h"
#include "resources/ResourcesManager.h"

FireBullet::FireBullet(float start_x, float start_y, float final_x, float final_y) :
    _xi(start_x), _yi(start_y), _visible(true), _finished(false),
    _xf(final_x), _yf(final_y), _step(0), _bullet_velocity(10),
    _refwindow(Game::getMainWindow())
{
    _bullet_image = GET_SFML_IMAGE_FROM_MANAGER("firebullet");
    _bullet_sprite.SetImage(_bullet_image);
    _angle = atan2(-(_yf - _yi),(_xf - _xi));
    _current_x = _xi;
    _current_y =_yi;
    _bullet_sprite.SetPosition(_current_x,_current_y);
    _bullet_sprite.SetRotation(radiants2degrees(_angle));
    sf::Vector2f sprite_size = this->_bullet_sprite.GetSize();
    this->_bullet_sprite.SetCenter(sprite_size.x/2, sprite_size.y/2);
}

FireBullet::~FireBullet() {}

void FireBullet::setBulletVelocity(float v) { _bullet_velocity = v; }

bool FireBullet::isVisible() { return _visible; }

bool FireBullet::hasArrived() { return _finished; }

void FireBullet::setVisible(bool value){
	_visible=value;
}

void FireBullet::update() {

	if (!_visible){
		_finished = true;
		return;
	}

    _step += _bullet_velocity;

    _current_x += cos(_angle)*_bullet_velocity;
    _current_y -= sin(_angle)*_bullet_velocity;

    _bullet_sprite.SetPosition(_current_x,_current_y);
    _bullet_sprite.SetRotation(radiants2degrees(_angle));

    // TODO: We need a more accurate check...
    if (abs(_current_x - _xf) < 10 && abs(_current_y -_yf) < 10) _finished = true;
}

void FireBullet::draw() {
    if (_visible) {
        _refwindow.Draw(_bullet_sprite);
    }
}
