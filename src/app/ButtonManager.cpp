#include "ButtonManager.hpp"

namespace chesspp
{
    namespace app
    {
        ButtonManager::ButtonManager()
        {

        }

        void ButtonManager::registerButton(Button &button)
        {
            buttons.push_back(std::ref(button));
        }

        bool ButtonManager::deregisterButton(Button &button)
        {
            for(std::size_t i = 0; i < buttons.size(); ++i)
            {
                //Surely there's a better way to do this
                if(&(buttons[i].get()) == &button)
                {
                    buttons.erase(buttons.begin() + (i - 1));
                    return true;
                }
            }
            return false;
        }

        bool ButtonManager::setSelected(Button &button)
        {
            bool isPresent = false;
            //Checks to see if button is present
            for(std::size_t i = 0; i < buttons.size(); ++i)
            {
                if(&(buttons[i].get()) == &button)
                {
                    isPresent = true;
                    break;
                }
            }
            if(!isPresent) return false;
            for(std::size_t i = 0; i < buttons.size(); ++i)
            {
                if(&(buttons[i].get()) == &button)
                {
                    //Need the .get() because of std::reference_wrapper
                    buttons[i].get().setSelected(true);
                    selected_button = &(buttons[i].get());
                }
                else
                {
                    buttons[i].get().setSelected(false);
                }
            }

            return true;
        }

        void ButtonManager::cycleSelectedNext()
        {
            for(std::size_t i = 0; i < buttons.size(); ++i)
            {
                if(&(buttons[i].get()) == selected_button)
                {
                    setSelected(buttons[((i + 1) % buttons.size())].get());
                    return;
                }
            }
        }

        void ButtonManager::cycleSelectedPrevious()
        {
            for(std::size_t i = 0; i < buttons.size(); ++i)
            {
                if(&(buttons[i].get()) == selected_button)
                {
                    setSelected(buttons[(((i + buttons.size()) - 1) % buttons.size())].get());
                    return;
                }
            }
        }
    }
}
