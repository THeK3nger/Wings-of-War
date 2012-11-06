#include "guiButton.h"
#include "Game.h"
#include "resources/ResourcesManager.h"
#include "resources/ImageRes.h"

guiButton::guiButton(int type, int posx, int posy):
    _window(Game::getMainWindow())
{
	this->_posx=posx;
	this->_posy=posy;


		if(type==BUTTON_CONFIRM)
		{
			this->_button.LoadFromFile("assets/go.png");
		}

		if(type==BUTTON_CANCEL)
		{
			this->_button.LoadFromFile("assets/cancel.png");
		}

		this->_button_sprite.SetImage(this->_button);
		this->_button_sprite.SetPosition(this->_posx,this->_posy);
}

guiButton::~guiButton() {

}
void guiButton::draw()
{
_window.Draw(this->_button_sprite);
}
