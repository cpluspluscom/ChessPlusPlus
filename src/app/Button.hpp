#ifndef ChessPlusPlus_App_Button_HeaderPlusPlus
#define ChessPlusPlus_App_Button_HeaderPlusPlus

#include "SFML.hpp"

#include <string>
namespace chesspp
{
    namespace app
    {
        /**
         * \brief
         * Simple text-based GUI buttons
         */
        class Button : public sf::Drawable
        {
            sf::Text button;
            /**
             * \brief
             * Overriden sf::Drawable::draw method to provide to custom rendering behavior
             *
             * \param target Render target to draw to
             * \param states Current render states
             */
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        public:
            /**
             * \brief
             * Construct from text and a font size
             *
             * \param text Button text
             * \param font_size Font size of the button text
             */
            Button(const std::string &text, unsigned font_size);

            /**
             * \brief
             * Compares two Buttons for equality
             *
             * \param other Other button to test for comparison
             * \return True if and only if other is this
             */
            bool operator==(const Button& other) const
            {
                return this == &other;
            }
            /**
             * \brief
             * Sets abolute position of button
             *
             * \param x The x coordinate of the new position
             * \param y The y coordinate of the new position
             */
            void setPosition(int x, int y)
            {
                button.setPosition(x,y);
            }
            /**
             * \brief
             * Sets absolute position of button
             *
             * \param pos New position
             */
            void setPosition(sf::Vector2f &pos)
            {
                button.setPosition(pos);
            }
            /**
             * \brief
             * Sets the button's text
             *
             * \param text Button's text
             */
            void setText(const std::string &text)
            {
                button.setString(text);
            }
            /**
             * \brief
             * Sets the button's text color
             *
             * \param color Color of button text
             */
            void setColor(const sf::Color &color)
            {
                button.setColor(color);
            }
            /**
             * \brief
             * Sets button's text font
             *
             * \param font Font of button text
             */
            void setFont(const sf::Font &font)
            {
                button.setFont(font);
            }
            /**
             * \brief
             * Sets the selected status of the button
             *
             * /param selected Selected status
             */
            void setSelected(bool selected)
            {
                if(selected) setColor(sf::Color::Blue);
                else setColor(sf::Color::Black);
            }
            /**
             * \brief
             * Returns position of button
             *
             * \return Button position
             */
            sf::Vector2f getPosition()
            {
                return button.getPosition();
            }
            /**
             * \brief
             * Returns button's text
             *
             * \return Text of button
             */
            const sf::Text& getText()
            {
                return button;
            }
            /**
             * \brief
             * Check if point is within the rectangle area of the text
             *
             * \return True if (x,y) is within text area
             */
            bool contains(int x, int y)
            {
                return button.getGlobalBounds().contains(x,y);
            }

        };
    }
}
#endif
