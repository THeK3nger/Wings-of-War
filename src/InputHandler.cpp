#include "InputHandler.h"

InputHandler* InputHandler::_instance = 0;

InputHandler::InputHandler()
{
}

InputHandler* InputHandler::createInputHandler(sf::RenderWindow *window, Game *game)
{
    if (!_instance)
    {
        _instance = new InputHandler();
        _instance->_window = window;
        _instance->_game = game;
        return _instance;
    }
    else
    {
        return 0;
    }
}

InputHandler* InputHandler::getSingleton()
{
    if (_instance)
        return _instance;
    else
        return 0;
}

void InputHandler::handleInput()
{
    if(_window->GetEvent(_lastEvent))
    {
        switch(_lastEvent.Type)
        {
            case sf::Event::KeyPressed:
                switch(_lastEvent.Key.Code)
                {
                    case sf::Key::Num1:
                        _event.type = InputHandler::ZOOMIN;
                        break;
                    case sf::Key::Num2:
                        _event.type = InputHandler::ZOOMOUT;
                        break;
                }
        }
    }
}
