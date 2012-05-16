#ifndef GAMELOGGER_H
#define	GAMELOGGER_H

#include <iostream>
#include <string>

/*!
 * This class provide an useful tools for logging.
 */
class GameLogger {
public:
    GameLogger();
    GameLogger(std::string filename);
    GameLogger(const GameLogger& orig);
    virtual ~GameLogger();
private:
    FILE* _pFile;
    

};

#endif	/* GAMELOGGER_H */

