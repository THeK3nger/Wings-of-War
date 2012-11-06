#ifndef GUIBUTTON_H_
#define GUIBUTTON_H_

#include "wowcommon.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#define BUTTON_CONFIRM 	0
#define BUTTON_CANCEL 	1



class guiButton {
public:
	guiButton(int type, int posx, int posy);
	virtual ~guiButton();
	void draw();
	sf::Rect<int>* clickableArea;
	sf::Sprite _button_sprite;
	
private:
	int _posx;
	int _posy;
	sf::RenderWindow& _window;
	sf::Image _button;
	
};


#endif /* GUIBUTTON_H_ */
