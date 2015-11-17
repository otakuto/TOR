#pragma once
#include "GameObject.hpp"
#include <iostream>
#include <array>

class Damage
:
public GameObject
{
private:
	std::array<int, 3> position;
	unsigned int time;
	int point;
	bool isEnemy;

public:
	Damage(std::array<int, 3> position, bool isEnemy)
	:
	position(position),
	time(100),
	point(),
	isEnemy(isEnemy)
	{
	}

	void run()
	{
		position[0] += 3;
		if (time)
		{
			--time;
		}
		else
		{
			enable = false;
		}
	}

	void draw() const
	{
		static GLdouble const vertex[][3] =
		{
			{0, 0, 0},
			{4, 0, 0},
			{4, 4, 0},
			{0, 4, 0}
		};
		static GLubyte const color[2][3] =
		{
			{0xFF, 0xFF, 0xFF},
			{0xFF, 0x00, 0x00}
		};

		glPushMatrix();
		glTranslated(position[0], position[1], position[2]);
		glColor3ubv(color[isEnemy]);
		glBegin(GL_QUADS);
		for (auto && e : vertex)
		{
			glVertex3dv(e);
		}
		glEnd();
		glPopMatrix();
	}
};

