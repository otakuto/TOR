#pragma once
#include "Option.hpp"
#include "Key.hpp"
#include "Controller.hpp"

class LocalController
:
public Controller
{
	std::shared_ptr<GLFWwindow> window;
	std::shared_ptr<Option const> const option;

public:
	Key key;

	LocalController(std::shared_ptr<GLFWwindow> window, std::shared_ptr<Option const> const option)
	:
	window(window),
	option(option),
	key(Key::None)
	{
	}

	void run()
	{
		key = Key::None;
		for (auto e : {Key::Up, Key::Down, Key::Right, Key::Left, Key::Jump, Key::ActionA, Key::ActionB, Key::ActionC, Key::ActionD})
		{
			if (glfwGetKey(window.get(), option->keyMap.at(e)))
			{
				key = static_cast<Key>(static_cast<int>(key) | static_cast<int>(e));
			}
		}
	}

	void draw() const
	{
	}

	bool at(Key key)
	{
		return static_cast<bool>(static_cast<int>(key) & static_cast<int>(this->key));
	}
};
