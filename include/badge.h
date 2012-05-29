/* 
 * File:   badge.h
 * Author: malcom
 *
 * Created on May 29, 2012, 4:43 PM
 */

#ifndef BADGE_H
#define	BADGE_H

class badge {
public:
    badge();
    virtual ~badge();
private:
    
    float _xpos;
    float _ypos;
    int _number;
    sf::Color _badgeColor;
    sf::Shape _shape;
    sf::RenderWindow _window;

};

#endif	/* BADGE_H */

