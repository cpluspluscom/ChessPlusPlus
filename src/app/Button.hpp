#ifndef ChessPlusPlus_App_Button_HeaderPlusPlus
#define ChessPlusPlus_App_Button_HeaderPlusPlus

#include "SFML.hpp"

#include <string>
namespace chesspp
{
	namespace app
	{
		class Button : public sf::Drawable
		{
			sf::Text button;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		public:
			Button(const std::string &text, unsigned font_size);

			//Only the same if they are actually the same object
			bool operator==(const Button& other) const
			{
				return this == &other;
			}
			void setPosition(int x, int y)
			{
				button.setPosition(x,y);
			}
			void setPosition(sf::Vector2f &pos)
			{
				button.setPosition(pos);
			}
			void setText(const std::string &text)
			{
				button.setString(text);
			}
			void setColor(const sf::Color &color)
			{
				button.setColor(color);
			}
			void setFont(const sf::Font &font)
			{
				button.setFont(font);
			}
			sf::Vector2f getPosition()
			{
				return button.getPosition();
			}
			//Returns underlying button (sf::Text) representation. Need this since we just inherit from
			//sf::Drawable, and a lot of functionality is delegated down to more specific classes
			//There's probably a better way to do this, but for now it works.
			const sf::Text& getText()
			{
				return button;
			}
			bool contains(int x, int y)
			{
				return button.getGlobalBounds().contains(x,y);
			}

		};
	}
}
#endif
