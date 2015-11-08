#pragma once
#include <boost/coroutine/all.hpp>
#include "GameObject.hpp"
#include "Damage.hpp"

class Enemy
:
public GameObject
{
public:
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;
	boost::coroutines::symmetric_coroutine<void>::call_type r;

	std::array<int, 3> position;
	int hp;

	Enemy(std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist, std::function<void(boost::coroutines::symmetric_coroutine<void>::yield_type & yield, Enemy & enemy)> r)
	:
	gameObjectlist(gameObjectlist),
	r([&,r=r](auto & y){r(y, *this);}),
	position(),
	hp()
	{
	}

	void run()
	{
		r();
	}

	void draw() const
	{
		static GLdouble const vertex[][3] =
		{
			{0, 0, 0},
			{32, 0, 0},
			{32, 32, 0},
			{0, 32, 0}
		};
		static GLubyte const color[3] = {0x80, 0x70, 0x60};

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

