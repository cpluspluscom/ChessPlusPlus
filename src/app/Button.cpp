#include "Button.hpp"

namespace chesspp
{
    namespace app
    {
        Button::Button(const std::string &text, unsigned font_size)
        {
            button.setCharacterSize(font_size);
            button.setString(text);
            button.setStyle(sf::Text::Bold);
            button.setColor(sf::Color::Black);
            recenter();
        }

        void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(button, states);
        }
    }
}
