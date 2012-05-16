/* 
 * File:   Dialog.h
 * Author: malcom
 *
 * Created on May 16, 2012, 5:26 PM
 */

#ifndef DIALOG_H
#define	DIALOG_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <stdio.h>

class Dialog {
public:
    
    Dialog(sf::RenderWindow  *refwindow);
    
    virtual ~Dialog();
    
    sf::RenderWindow* _window;
    
    sf::Image image1;
    sf::Sprite _dialog;
    
    int width,height;
    
    sf::Font WOW_Font;
    
private:

   void Display();
   
   
};

#endif	/* DIALOG_H */

