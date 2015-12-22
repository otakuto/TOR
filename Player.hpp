#pragma once
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <eigen3/Eigen/Core>
#include <list>
#include <memory>
#include "GameObject.hpp"
#include "Option.hpp"
#include "Key.hpp"
#include "Damage.hpp"
#include "Direction.hpp"
#include "Controller.hpp"

class Player
:
public GameObject
{
public:
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;
	std::shared_ptr<Controller> controller;
	Eigen::Vector3d position;
	int hp;
	int hpMax;
	int level;
	int speed;
	int jumpTime;
	int jumpVelocity;
	Direction direction;

	GLuint vao;

public:
	Player(std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist, std::shared_ptr<Controller> controller)
	:
	gameObjectlist(gameObjectlist),
	controller(controller),
	position(0, 0, 0),
	hp(27),
	hpMax(32),
	level(),
	speed(2),
	jumpTime(1),
	jumpVelocity(256),
	direction(Direction::Right)
	{
	}

	void run()
	{
		if (controller->at(Key::Up))
		{
			position[1] += speed;
		}
		if (controller->at(Key::Down))
		{
			position[1] -= speed;
		}
		if (controller->at(Key::Right))
		{
			position[0] += speed;
			direction = Direction::Right;
		}
		if (controller->at(Key::Left))
		{
			position[0] -= speed;
			direction = Direction::Left;
		}
		{
			static int time = 0;
			if (position[1] > 0)
			{
				position[1] -= 9.8 * (time / 30.0) * (time / 30.0);
				++time;
			}
			else
			{
				time = 0;
			}
		}

		if (controller->at(Key::Jump))
		{
			position[1] += 8;
		}
		else
		{
		}

		{
			static int time = 0;
			if (time <= 0)
			{
				if (controller->at(Key::ActionA))
				{
					gameObjectlist->emplace_back(std::make_shared<Damage>(position + Eigen::Vector3d(0, 4, 0), std::array<int, 2>{{4, 4}}, false, [direction=direction](auto & yield, Damage & damage)
					{
						int amount = (direction == Direction::Right) ? 4 : -4;
						for (int time = 0; time < 100; ++time)
						{
							damage.position[0] += amount;
							yield();
						}
						damage.enable = false;
					}));
					time = 60;
				}
			}
			else
			{
				--time;
			}
		}
		if (controller->at(Key::ActionB))
		{
		}
		if (controller->at(Key::ActionC))
		{
		}
		if (controller->at(Key::ActionD))
		{
		}
	}

	void draw() const
	{
		static GLdouble const vertex[][3] =
		{
			{0, 0, 0},
			{8, 0, 0},
			{8, 8, 0},
			{0, 8, 0}
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

