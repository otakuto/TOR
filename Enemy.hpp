#pragma once
#include <boost/coroutine/all.hpp>
#include <eigen3/Eigen/Core>
#include "GameObject.hpp"
#include "Damage.hpp"

class Enemy
:
public GameObject
{
public:
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;

	Eigen::Vector3d position;
	int hp;

	boost::coroutines::symmetric_coroutine<void>::call_type coroutine;

	Enemy(std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist, Eigen::Vector3d position, std::function<void(boost::coroutines::symmetric_coroutine<void>::yield_type & yield, Enemy & enemy)> coroutine)
	:
	gameObjectlist(gameObjectlist),
	position(position),
	hp(),
	coroutine([&,coroutine=coroutine](auto & yield){coroutine(yield, *this);})
	{
	}

	void run()
	{
		coroutine();
	}

	void draw() const
	{
		constexpr std::array<std::array<GLdouble, 3>, 4> vertex
		{{
			{{0, 0, 0}},
			{{32, 0, 0}},
			{{32, 32, 0}},
			{{0, 32, 0}}
		}};
		constexpr std::array<GLubyte, 3> color = {{0x80, 0x70, 0x60}};

		glPushMatrix();
		glTranslated(position[0], position[1], position[2]);
		glColor3ubv(color.data());
		glBegin(GL_QUADS);
		for (auto && e : vertex)
		{
			glVertex3dv(e.data());
		}
		glEnd();
		glPopMatrix();
	}
};

