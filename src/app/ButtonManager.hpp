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
            /**
             * \brief
             * Default constructor
             */
            ButtonManager();
            /**
             * \brief
             * Registers a new button with the ButtonManager
             *
             * \param button New button to be registered
             */
            void registerButton(Button &button);
            /**
             * \brief
             * Deregistered a button from the ButtonManager
             *
             * \param Button to be deregistered
             * \return True if succeeded to deregister
             */
            bool deregisterButton(Button &button);
            /**
             * \brief
             * Sets selected status of a button to true
             *
             * \param button Button to be set as selected
             * \return True if succeeded to set selected status
             */
            bool setSelected(Button &button);
            /**
             * \brief
             * Deselects all registered buttons
             */
            void deselectAll();
            /**
             * \brief
             * Sets selected status of next (according to time registered) button to true
             */
            void cycleSelectedNext();
            /**
             * \brief
             * Sets selected status of previous (according to time registered) button to true
             */
            void cycleSelectedPrevious();
            /**
             * \brief
             * Returns selected button
             *
             * \return Currently selected button
             */
            const Button& getSelected()
            {
                return *selected_button;
            }
        };
    }
}

#endif
