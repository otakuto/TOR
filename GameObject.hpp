#pragma once

class GameObject
{
public:
	virtual void run() = 0;
	virtual void draw() const = 0;
};

