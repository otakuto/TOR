#pragma once
#include "Option.hpp"
#include "Key.hpp"
#include "GameObject.hpp"

class Controller
:
public GameObject
{
public:
	virtual void run() = 0;
	virtual void draw() const = 0;
	virtual bool at(Key key) = 0;
};
