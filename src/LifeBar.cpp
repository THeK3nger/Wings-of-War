

#include "LifeBar.h"


LifeBar::LifeBar(int type, int hp, int posx, int posy,sf::RenderWindow *refwindow) {

	_window = refwindow;

	this->_posx=posx;
	this->_posy=posy;
	this->_maxlife=hp;
	this->_life=hp;

	this->_hud.LoadFromFile("assets/life_hud/life_hud.png");

	if(type==ENEMYBAR)
	{
		this->_bar.LoadFromFile("assets/life_hud/life_stick_enemy.png");
	}

	if(type==PLAYERBAR)
	{
		this->_bar.LoadFromFile("assets/life_hud/life_stick_player.png");
	}

	this->_bar_sprite.SetImage(this->_bar);
	this->_hud_sprite.SetImage(this->_hud);

	this->_hud_sprite.SetPosition(this->_posx,this->_posy);
	this->_bar_sprite.SetPosition(this->_posx+9,this->_posy+9);
}

LifeBar::~LifeBar() {
	// TODO Auto-generated destructor stub
}

void LifeBar::draw(){
	_window->Draw(this->_bar_sprite);
	_window->Draw(this->_hud_sprite);
}

void LifeBar::setLife(int hp)
{
	this->_life=this->_life-hp;
	this->_bar_sprite.SetScale( ( (float)this->_life/(float)this->_maxlife),1);

}
