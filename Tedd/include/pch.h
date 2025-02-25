#ifndef PCH_H
#define PCH_H

// Standard Library
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <filesystem>
#include <type_traits>
#include <typeindex>
#include <utility>

// SFML
#include "SFML/Graphics.hpp"

// JSON
#include "json.hpp"
#include "tinyfiledialogs.h"

// LUA
#define SOL_ALL_SAFETIES_ON 1 // Don't bother comprehend this
#include "config.hpp"
#include "forward.hpp"

// ImGUi
#ifdef USING_EDITOR
#include "imgui-SFML.h"
#include "imgui.h"
#endif 

// Windows
#ifdef _WIN32
#pragma comment (lib, "Dwmapi")
#include <windows.h>
#include <dwmapi.h>
#endif // _WIN32


// Add more...


#endif // !PCH_H