#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "Key.hpp"

class Option
{
public:
	std::unordered_map<Key, int> keyMap;

	Option()
	:
	keyMap()
	{
		keyMap[Key::Up] = GLFW_KEY_UP;
		keyMap[Key::Down] = GLFW_KEY_DOWN;
		keyMap[Key::Right] = GLFW_KEY_RIGHT;
		keyMap[Key::Left] = GLFW_KEY_LEFT;
		keyMap[Key::Jump] = GLFW_KEY_SPACE;
		keyMap[Key::ActionA] = 'Z';
		keyMap[Key::ActionB] = 'X';
		keyMap[Key::ActionC] = 'C';
		keyMap[Key::ActionD] = 'V';
	}
};

