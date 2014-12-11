#pragma once
#include <memory>
#include <GL/glfw.h>
#include <GL/glu.h>
#include "GameObject.hpp"
#include "Option.hpp"
#include "Key.hpp"

class Player
:
public GameObject
{
private:
	GLdouble position[3];

	std::shared_ptr<Option const> const option;
public:
	Player(std::shared_ptr<Option const> const option)
	:
	position(),
	option(option)
	{
	}

	void run()
	{
		if (glfwGetKey(option->keyMap.at(Key::Up)))
		{
			++position[1];
		}
		if (glfwGetKey(option->keyMap.at(Key::Down)))
		{
			--position[1];
		}
		if (glfwGetKey(option->keyMap.at(Key::Right)))
		{
			++position[0];
		}
		if (glfwGetKey(option->keyMap.at(Key::Left)))
		{
			--position[0];
		}
		if (glfwGetKey(option->keyMap.at(Key::Jump)))
		{
		}
		if (glfwGetKey(option->keyMap.at(Key::ActionA)))
		{
		}
		if (glfwGetKey(option->keyMap.at(Key::ActionB)))
		{
		}
		if (glfwGetKey(option->keyMap.at(Key::ActionC)))
		{
		}
		if (glfwGetKey(option->keyMap.at(Key::ActionD)))
		{
		}
	}

	void draw() const
	{
		static GLdouble const vertex[][3] =
		{
			{0, 0, 0},
			{8, 0, 0},
			{8, 16, 0},
			{0, 16, 0}
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

