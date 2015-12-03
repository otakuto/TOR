#pragma once
#include "Option.hpp"
#include "Key.hpp"
#include "Controller.hpp"

class NetworkController
:
public Controller
{
public:
	Key key;

	NetworkController()
	:
	key(Key::None)
	{
	}

	void run()
	{
	}

	void draw() const
	{
	}

	bool at(Key key)
	{
		return static_cast<bool>(static_cast<int>(key) & static_cast<int>(this->key));
	}
};
