#pragma once

class GameObject
{
public:
	bool enable;
	virtual void run() = 0;
	virtual void draw() const = 0;

	GameObject()
	:
	enable(true)
	{
	}
};

