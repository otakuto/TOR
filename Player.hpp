#pragma once
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <list>
#include <memory>
#include "GameObject.hpp"
#include "Option.hpp"
#include "Key.hpp"
#include "Damage.hpp"

class Player
:
public GameObject
{
private:
	std::shared_ptr<GLFWwindow> window;
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;
	std::shared_ptr<Option const> const option;
	std::array<int, 3> position;
	int hp;
	int level;
	int speed;
	int jumpTime;
	int jumpHight;

public:
	Player(std::shared_ptr<GLFWwindow> window, std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist, std::shared_ptr<Option const> const option)
	:
	window(window),
	gameObjectlist(gameObjectlist),
	option(option),
	position(),
	hp(),
	level(),
	speed(2),
	jumpTime(1),
	jumpHight()
	{
	}

	void run()
	{
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Up)))
		{
			//position[1] += speed;
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Down)))
		{
			//position[1] -= speed;
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Right)))
		{
			position[0] += speed;
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Left)))
		{
			position[0] -= speed;
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Jump)))
		{
		}
		{
			static int time = 0;
			if (time <= 0)
			{
				if (glfwGetKey(window.get(), option->keyMap.at(Key::ActionA)))
				{
				gameObjectlist->emplace_back(std::make_shared<Damage>(position, false));
				time = 100;
				}
			}
			else
			{
				--time;
			}
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::ActionB)))
		{
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::ActionC)))
		{
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::ActionD)))
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

