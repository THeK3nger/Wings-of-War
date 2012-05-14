/* 
 * File:   Screen.cpp
 * Author: malcom
 * 
 * Created on May 14, 2012, 4:42 PM
 */

#include "Screen.h"

Screen::Screen(sf::RenderWindow  *refwindow) 
{
    
    //Storing the address of the mainwindow to the current window
    _window=refwindow;
}


Screen::~Screen() {
}

