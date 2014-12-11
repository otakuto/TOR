#pragma once
#include "GameObject.hpp"

class Bullet
:
public GameObject
{
private:
	GLdouble position[3];
public:
	Bullet()
	:
	position()
	{
	}

	void run()
	{
		++position[0];
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
		static GLubyte const color[3] = {0xFF, 0xFF, 0xFF};

		glPushMatrix();
		glTranslated(position[0], position[1], position[2]);
		glColor3ubv(color);
		glBegin(GL_QUADS);
		for (auto && e : vertex)
		{
			glVertex3dv(e);
		}
		glEnd();
		glPopMatrix();
	}
};

