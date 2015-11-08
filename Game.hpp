#pragma once
#include <list>
#include <memory>
#include "GameObject.hpp"
#include "Player.hpp"
#include "Damage.hpp"
#include "Option.hpp"
#include "Enemy.hpp"
#include <iostream>

class Game
{
private:
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;

public:
	Game(std::shared_ptr<GLFWwindow> window)
	:
	gameObjectlist(std::make_shared<std::list<std::shared_ptr<GameObject>>>())
	{
		gameObjectlist->emplace_back(std::make_shared<Player>(window, gameObjectlist, std::make_shared<Option>()));
		gameObjectlist->emplace_back(std::make_shared<Enemy>(gameObjectlist, [](boost::coroutines::symmetric_coroutine<void>::yield_type & yield, Enemy & enemy)
		{
			while(true)
			{
				for (int i = 0; i < 100; ++i)
				{
					yield();
				}
				enemy.gameObjectlist->emplace_back(std::make_shared<Damage>(enemy.position, true));
			}
		}));
	}

	void run()
	{
		for (auto e = gameObjectlist->begin(); e != gameObjectlist->end();)
		{
			if ((*e)->enable)
			{
				(*e)->run();
				++e;
			}
			else
			{
				e = gameObjectlist->erase(e);
			}
		}
	}

	void draw()
	{
		for (auto && e : *gameObjectlist)
		{
			e->draw();
		}
	}
};
