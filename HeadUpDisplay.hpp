#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class HeadUpDisplay
:
public GameObject
{
private:
	std::shared_ptr<Player> player;
	int width;
	int height;
	int barLength;
	int barHeight;

public:
	HeadUpDisplay(std::shared_ptr<GLFWwindow> window, std::shared_ptr<Player> player)
	:
	player(player),
	width(),
	height(),
	barLength(256),
	barHeight(8)
	{
		 glfwGetWindowSize(window.get(), &width, &height);
	}

	void run()
	{
	}

	void draw() const
	{
		static GLubyte const color_fg[3] = {0xF1, 0x35, 0x35};
		static GLubyte const color_bg[3] = {0x60, 0x60, 0x60};

		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glTranslated((width - barLength) / 2, (height * 3) / 4, 0);

		glBegin(GL_QUADS);
		glColor3ubv(color_fg);
		glVertex2d(0, 0);
		glVertex2d(barLength * (static_cast<double>(player->hp) / static_cast<double>(player->hpMax)), 0);
		glVertex2d(barLength * (static_cast<double>(player->hp) / static_cast<double>(player->hpMax)), barHeight);
		glVertex2d(0, barHeight);
		glColor3ubv(color_bg);
		glVertex2d(0, 0);
		glVertex2d(barLength, 0);
		glVertex2d(barLength, barHeight);
		glVertex2d(0, barHeight);
		glEnd();
		glPopMatrix();
	}
};
