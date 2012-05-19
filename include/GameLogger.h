#ifndef GAMELOGGER_H
#define	GAMELOGGER_H

#include <iostream>
#include <fstream>
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

    void toLog(std::string message);

private:
    bool _onfile;
    std::ofstream _file;

    static std::string currentTime();


};

#endif	/* GAMELOGGER_H */

