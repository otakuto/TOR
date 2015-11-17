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

	GLuint vao;

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
		constexpr std::array<std::array<GLdouble, 3>, 4> vertex =
		{{
			{{0, 0, 0}},
			{{8, 0, 0}},
			{{8, 16, 0}},
			{{0, 16, 0}}
		}};
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		// 頂点バッファオブジェクトを作成する
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex.data(), GL_STATIC_DRAW);

		// 頂点バッファオブジェクトにシェーダ内の変数vertexCoodrinateを結びつける
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(double)*3, 0);

	}

	void run()
	{
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Up)))
		{
			position[1] += speed;
		}
		if (glfwGetKey(window.get(), option->keyMap.at(Key::Down)))
		{
			position[1] -= speed;
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
		//glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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

