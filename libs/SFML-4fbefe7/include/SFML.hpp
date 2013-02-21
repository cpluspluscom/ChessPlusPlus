#pragma once
#ifndef SFMLFULL_INCLUDED
#define SFMLFULL_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#if defined(_DEBUG) || defined(DEBUG)
    #if defined(SFML_STATIC)
        #pragma comment(lib,"sfml-graphics-s-d.lib")
        #pragma comment(lib,"sfml-audio-s-d.lib")
        #pragma comment(lib,"sfml-network-s-d.lib")
        #pragma comment(lib,"sfml-window-s-d.lib")
        #pragma comment(lib,"sfml-system-s-d.lib")
        #pragma comment(lib,"sfml-main-d.lib")
    #else
        #pragma comment(lib,"sfml-graphics-d.lib")
        #pragma comment(lib,"sfml-audio-d.lib")
        #pragma comment(lib,"sfml-network-d.lib")
        #pragma comment(lib,"sfml-window-d.lib")
        #pragma comment(lib,"sfml-system-d.lib")
        #pragma comment(lib,"sfml-main-d.lib")
    #endif
#else
    #if defined(SFML_STATIC)
        #pragma comment(lib,"sfml-graphics-s.lib")
        #pragma comment(lib,"sfml-audio-s.lib")
        #pragma comment(lib,"sfml-network-s.lib")
        #pragma comment(lib,"sfml-window-s.lib")
        #pragma comment(lib,"sfml-system-s.lib")
        #pragma comment(lib,"sfml-main.lib")
    #else
        #pragma comment(lib,"sfml-graphics.lib")
        #pragma comment(lib,"sfml-audio.lib")
        #pragma comment(lib,"sfml-network.lib")
        #pragma comment(lib,"sfml-window.lib")
        #pragma comment(lib,"sfml-system.lib")
        #pragma comment(lib,"sfml-main.lib")
    #endif
#endif

#endif // SFMLFULL_INCLUDED