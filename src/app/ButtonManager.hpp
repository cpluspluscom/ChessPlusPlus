#ifndef ChessPlusPlus_App_ButtonManager_HeaderPlusPlus
#define ChessPlusPlus_App_ButtonManager_HeaderPlusPlus

#include "Button.hpp"
#include "SFML.hpp"

#include <vector>
#include <functional>

/**
 * ButtonManager is a class which handles button selection of menus
 * Inspiration for this comes from ButtonGroups in Java's Swing
 * To use, just create your Buttons inside your menu class, then register
 * via registerButton(Button &button). Setting a button as selected will automatically
 * 'deselect' all other buttons. User can then call getSelected() to get the 
 * currently selected button.
 *
 * Should this class handle placement also?
 * This should be renamed to ButtonGroup or something similar
 */
namespace chesspp
{
	namespace app
	{
		class ButtonManager
		{
			//std::map be any better maybe?
			using Buttons_t = std::vector<std::reference_wrapper<Button>>;
			Buttons_t buttons;
			Button *selected_button;

			//Noncopyable
			ButtonManager(const ButtonManager&) = delete;
			ButtonManager& operator=(const ButtonManager&) = delete;

		public:
			ButtonManager();
			void registerButton(Button &button);
			bool deregisterButton(Button &button);
			bool setSelected(Button &button);
			void deselectAll();
			void cycleSelectedUp();
			void cycleSelectedDown();
			const Button& getSelected()
			{
				return *selected_button;
			}
		};
	}
}

#endif
