/* 
 * File:   Dialog.cpp
 * Author: malcom
 * 
 * Created on May 16, 2012, 5:26 PM
 */

#include "Dialog.h"

Dialog::Dialog(sf::RenderWindow  *refwindow)
{
    
    //Storing the address of the mainwindow to the current window
    _window=refwindow;
    
    WOW_Font.LoadFromFile("assets/pixelmix.ttf");
    
    this->Display();
    
}

Dialog::Display()
{
    while(1)
    {
    sf::String Text = "I like donuts";
    Text.SetStyle(sf::String::Regular);
    Text.SetColor(sf::Color(128, 128, 0));
    Text.Move(100.f, 200.f);
    _window.Draw(Text);
    }
}




Dialog::~Dialog() {
    
}

