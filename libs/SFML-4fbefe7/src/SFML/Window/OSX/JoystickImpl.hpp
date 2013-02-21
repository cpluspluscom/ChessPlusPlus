////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2012 Marco Antognini (antognini.marco@gmail.com), 
//                         Laurent Gomila (laurent.gom@gmail.com),
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_JOYSTICKIMPLOSX_HPP
#define SFML_JOYSTICKIMPLOSX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/JoystickImpl.hpp>
#include <IOKit/hid/IOHIDDevice.h>
#include <map>
#include <vector>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Mac OS X implementation of joysticks
///
////////////////////////////////////////////////////////////
class JoystickImpl
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Check if a joystick is currently connected
    ///
    /// \param index Index of the joystick to check
    ///
    /// \return True if the joystick is connected, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool isConnected(unsigned int index);

    ////////////////////////////////////////////////////////////
    /// \brief Open the joystick
    ///
    /// \param index Index assigned to the joystick
    ///
    /// \return True on success, false on failure
    ///
    ////////////////////////////////////////////////////////////
    bool open(unsigned int index);

    ////////////////////////////////////////////////////////////
    /// \brief Close the joystick
    ///
    ////////////////////////////////////////////////////////////
    void close();

    ////////////////////////////////////////////////////////////
    /// \brief Get the joystick capabilities
    ///
    /// \return Joystick capabilities
    ///
    ////////////////////////////////////////////////////////////
    JoystickCaps getCapabilities() const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the joystick and get its new state
    ///
    /// \return Joystick state
    ///
    ////////////////////////////////////////////////////////////
    JoystickState update();

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    typedef long                                          Location;
    typedef std::map<sf::Joystick::Axis, IOHIDElementRef> AxisMap;
    typedef std::vector<IOHIDElementRef>                  ButtonsVector;
    
    AxisMap       m_axis;    ///< Axis (IOHIDElementRef) connected to the joystick
    ButtonsVector m_buttons; ///< Buttons (IOHIDElementRef) connected to the joystick
    unsigned int  m_index;   ///< SFML index
    
    static Location m_locationIDs[sf::Joystick::Count]; ///< Global Joystick register
    /// For a corresponding SFML index, m_locationIDs is either some usb 
    /// location or 0 if there isn't currently a connected joystick device
};

} // namespace priv

} // namespace sf


#endif // SFML_JOYSTICKIMPLOSX_HPP
