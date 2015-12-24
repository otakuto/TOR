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
#include "Skill.hpp"

class Player
:
public GameObject
{
public:
	int const & time;
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;
	std::shared_ptr<Controller> controller;
	Eigen::Vector3d position;
	int hp;
	int hpMax;
	int level;
	int speed;
	int jumpTime;
	int jumpedTime;
	int jumpVelocity;
	Direction direction;
	Skill skillA;
	Skill skillC;

	GLuint vao;

public:
	Player(int const & time, std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist, std::shared_ptr<Controller> controller)
	:
	time(time),
	gameObjectlist(gameObjectlist),
	controller(controller),
	position(0, 0, 0),
	hp(5),
	hpMax(32),
	level(),
	speed(2),
	jumpTime(1),
	jumpedTime(0),
	jumpVelocity(128),
	direction(Direction::Right),
	skillA(time, 30, [this, gameObjectlist=gameObjectlist]()
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
	}),
	skillC(time, 180, [this]()
	{
		if (direction == Direction::Left)
		{
			position[0] -= 8 * 5;
		}
		else
		{
			position[0] += 8 * 5;
		}
	})
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
			if (position[1] > 0)
			{
				position[1] -= 9.8 * (jumpedTime / 60.0) * (jumpedTime / 60.0);
				++jumpedTime;
			}
			else
			{
				jumpedTime = 0;
			}
		}

		if (controller->at(Key::Jump))
		{
			position[1] += 8;
		}

		if (controller->at(Key::ActionA))
		{
			skillA.run();
		}
		if (controller->at(Key::ActionB))
		{
		}
		if (controller->at(Key::ActionC))
		{
			skillC.run();
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

