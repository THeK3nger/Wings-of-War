

#ifndef LIFEBAR_H_
#define LIFEBAR_H_

#include "wowcommon.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


#define ENEMYBAR 	0
#define PLAYERBAR 	1

class LifeBar {
public:

    LifeBar(int type, int hp, int posx, int posy);
	virtual ~LifeBar();
	void setLife(int hp);
	void draw();


private:

	int _posx;
	int _posy;
	int _life;
	int _maxlife;
	sf::RenderWindow& _window;
	sf::Image _hud;
	sf::Image _bar;
	sf::Sprite _hud_sprite;
    sf::Sprite _bar_sprite;

};

#endif /* LIFEBAR_H_ */
