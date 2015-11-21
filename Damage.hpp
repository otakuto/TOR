#pragma once
#include "GameObject.hpp"
#include <boost/coroutine/all.hpp>
#include <iostream>
#include <array>

class Damage
:
public GameObject
{
public:
	Eigen::Vector3d position;
	unsigned int time;
	int point;
	bool isEnemy;
	std::array<int, 2> size;

	boost::coroutines::symmetric_coroutine<void>::call_type coroutine;

	std::array<std::array<GLdouble, 3>, 4> vertex;
public:
	Damage(Eigen::Vector3d position, std::array<int, 2> size, bool isEnemy, std::function<void(boost::coroutines::symmetric_coroutine<void>::yield_type & yield, Damage & damage)> coroutine)
	:
	position(position),
	time(100),
	point(),
	isEnemy(isEnemy),
	size(size),
	coroutine([&,coroutine=coroutine](auto & yield){coroutine(yield, *this);}),
	vertex()
	{
		vertex =
		{{
			{{0, 0, 0}},
			{{(GLdouble)size[0], 0, 0}},
			{{(GLdouble)size[0], (GLdouble)size[1], 0}},
			{{0, (GLdouble)size[1], 0}}
		}};
	}

	void run()
	{
		coroutine();
	}

	void draw() const
	{
		/*
		constexpr std::array<std::array<GLdouble, 3>, 4> vertex =
		{{
			{{0, 0, 0}},
			{{4, 0, 0}},
			{{4, 4, 0}},
			{{0, 4, 0}}
		}};
		*/
		constexpr std::array<std::array<GLubyte, 3>, 2> color =
		{{
			{{0xFF, 0xFF, 0xFF}},
			{{0xFF, 0x00, 0x00}}
		}};

		glPushMatrix();
		glTranslated(position[0], position[1], position[2]);
		glColor3ubv(color[isEnemy].data());
		glBegin(GL_QUADS);
		for (auto && e : vertex)
		{
			glVertex3dv(e.data());
		}
		glEnd();
		glPopMatrix();
	}
};

