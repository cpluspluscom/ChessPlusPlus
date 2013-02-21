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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Utf.hpp>

#import <Foundation/Foundation.h>
#import <SFML/Window/OSX/cpp_objc_conversion.h>

////////////////////////////////////////////////////////////
NSString* stringToNSString(std::string const& string)
{
    std::string utf8; utf8.reserve(string.size() + 1);
    sf::Utf8::fromAnsi(string.begin(), string.end(), std::back_inserter(utf8));
    NSString* str = [NSString stringWithCString:utf8.c_str() encoding:NSUTF8StringEncoding];
    
    return str;
}

////////////////////////////////////////////////////////////
NSString* sfStringToNSString(sf::String const& string)
{
    sf::Uint32 length = string.getSize() * sizeof(sf::Uint32);
    const void* data = reinterpret_cast<const void*>(string.getData());

    NSStringEncoding encoding;
    if (NSHostByteOrder() == NS_LittleEndian)
        encoding = NSUTF32LittleEndianStringEncoding;
    else
        encoding = NSUTF32BigEndianStringEncoding;

    NSString* str = [[NSString alloc] initWithBytes:data length:length encoding:encoding];
    return str;
}
