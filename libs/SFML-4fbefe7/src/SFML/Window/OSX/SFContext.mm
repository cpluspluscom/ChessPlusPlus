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
#include <SFML/Window/OSX/SFContext.hpp>
#include <SFML/Window/OSX/WindowImplCocoa.hpp>
#include <SFML/System/Err.hpp>

#import <SFML/Window/OSX/AutoreleasePoolWrapper.h>

namespace sf
{
namespace priv
{


////////////////////////////////////////////////////////////
SFContext::SFContext(SFContext* shared)
: m_view(0), m_window(0)
{
    // Ask for a pool.
    retainPool();
    
    // Create the context
    createContext(shared,
                  VideoMode::getDesktopMode().bitsPerPixel, 
                  ContextSettings(0, 0, 0));
}

    
////////////////////////////////////////////////////////////
SFContext::SFContext(SFContext* shared, const ContextSettings& settings,
                     const WindowImpl* owner, unsigned int bitsPerPixel)
: m_view(0), m_window(0)
{
    // Ask for a pool.
    retainPool();
    
    // Create the context.
    createContext(shared, bitsPerPixel, settings);
    
    // Apply context.
    WindowImplCocoa const * ownerCocoa = static_cast<WindowImplCocoa const *>(owner);
    ownerCocoa->applyContext(m_context);
}


////////////////////////////////////////////////////////////
SFContext::SFContext(SFContext* shared, const ContextSettings& settings, 
                     unsigned int width, unsigned int height)
: m_view(0), m_window(0)
{
    // Ensure the process is setup in order to create a valid window.
    WindowImplCocoa::setUpProcess();
    
    // Ask for a pool.
    retainPool();
    
    // Create the context.
    createContext(shared, VideoMode::getDesktopMode().bitsPerPixel, settings);
    
    // Create a dummy window/view pair (hidden) and asign it our context.
    m_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, width, height)
                                           styleMask:NSBorderlessWindowMask
                                             backing:NSBackingStoreBuffered
                                               defer:NO]; // Don't defer it!
    m_view = [[NSOpenGLView alloc] initWithFrame:NSMakeRect(0, 0, width, height)];
    [m_window setContentView:m_view];
    [m_view setOpenGLContext:m_context];
    [m_context setView:m_view];
}


////////////////////////////////////////////////////////////
SFContext::~SFContext()
{
    [m_context clearDrawable];
    [m_context release];
    
    [m_view release]; // Might be nil but we don't care.
    [m_window release]; // Idem.
    
    releasePool();
}


////////////////////////////////////////////////////////////
bool SFContext::makeCurrent()
{
    [m_context makeCurrentContext];
    return m_context == [NSOpenGLContext currentContext]; // Should be true.
}


////////////////////////////////////////////////////////////
void SFContext::display()
{
    [m_context flushBuffer];
}


////////////////////////////////////////////////////////////
void SFContext::setVerticalSyncEnabled(bool enabled)
{
    // Make compiler happy
#if MAC_OS_X_VERSION_MAX_ALLOWED < 1060
    typedef int GLint;
#endif
    
    GLint swapInterval = enabled ? 1 : 0;
    
    [m_context setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
}


////////////////////////////////////////////////////////////
void SFContext::createContext(SFContext* shared,
                              unsigned int bitsPerPixel, 
                              const ContextSettings& settings)
{
    // Choose the attributs of OGL context.
    std::vector<NSOpenGLPixelFormatAttribute> attrs;
    attrs.reserve(20); // max attributs (estimation).
    
    // These casts are safe. C++ is much more strict than Obj-C.
    
    attrs.push_back(NSOpenGLPFAClosestPolicy);
    attrs.push_back(NSOpenGLPFADoubleBuffer);
    
    if (bitsPerPixel > 24) {
        attrs.push_back(NSOpenGLPFAAlphaSize);
        attrs.push_back((NSOpenGLPixelFormatAttribute)8);
    }
    
    attrs.push_back(NSOpenGLPFADepthSize);
    attrs.push_back((NSOpenGLPixelFormatAttribute)settings.depthBits);
    
    attrs.push_back(NSOpenGLPFAStencilSize);
    attrs.push_back((NSOpenGLPixelFormatAttribute)settings.stencilBits);
    
    if (settings.antialiasingLevel > 0) {
        /* 
         * Antialiasing techniques are described in the 
         * "OpenGL Programming Guide for Mac OS X" document.
         *
         * According to this document, the specification currently allows 
         * only one multisample buffer.
         *
         * The document also states that software renderers should be avoided
         * because antialisaing techniques are very slow with them.
         */
        
        // Prefer multisampling over supersampling
        attrs.push_back(NSOpenGLPFAMultisample);
        
        // Only one buffer is currently available
        attrs.push_back(NSOpenGLPFASampleBuffers);
        attrs.push_back((NSOpenGLPixelFormatAttribute)1);
        
        // Antialiasing level
        attrs.push_back(NSOpenGLPFASamples);
        attrs.push_back((NSOpenGLPixelFormatAttribute)settings.antialiasingLevel);
        
        // No software renderer - only hardware renderer
        attrs.push_back(NSOpenGLPFAAccelerated);
    }
    
    attrs.push_back((NSOpenGLPixelFormatAttribute)0); // end of array
    
    // Create the pixel pormat.
    NSOpenGLPixelFormat* pixFmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:&attrs[0]];
    
    if (pixFmt == nil) {
        sf::err() << "Error. Unable to find a suitable pixel format." << std::endl;
        return;
    }
    
    // Use the shared context if one is given.
    NSOpenGLContext* sharedContext = shared != NULL ? shared->m_context : nil;
    
    // Create the context.
    m_context = [[NSOpenGLContext alloc] initWithFormat:pixFmt
                                           shareContext:sharedContext];
    
    if (m_context == nil) {
        sf::err() << "Error. Unable to create the context." << std::endl;
    }
    
    // Free up.
    [pixFmt release];
    
    // Save the settings. (OpenGL version is updated elsewhere.)
    m_settings = settings;
}

} // namespace priv

} // namespace sf

