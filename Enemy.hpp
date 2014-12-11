#pragma once
#include "GameObject.hpp"

class Enemy
:
public GameObject
{
private:
	GLdouble position[3];
	//ヘリウムポテチ
	int hp;

public:
	Enemy()
	:
	position(),
	hp()
	{
	}

	void run()
	{
	}

	void draw() const
	{
	}
};

