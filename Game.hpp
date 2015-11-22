#pragma once
#include <list>
#include <memory>
#include <eigen3/Eigen/Core>
#include "GameObject.hpp"
#include "Player.hpp"
#include "Damage.hpp"
#include "Option.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <random>

class Game
{
private:
	std::shared_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectlist;

public:
	Game(std::shared_ptr<GLFWwindow> window)
	:
	gameObjectlist(std::make_shared<std::list<std::shared_ptr<GameObject>>>())
	{
		auto player = std::make_shared<Player>(window, gameObjectlist, std::make_shared<Option>());
		gameObjectlist->emplace_back(player);
		gameObjectlist->emplace_back(std::make_shared<Enemy>(gameObjectlist, Eigen::Vector3d(0, 0, 0), [](auto & yield, Enemy & enemy)
		{
			while (true)
			{
				for (int i = 0; i < 100; ++i)
				{
					yield();
				}
				enemy.gameObjectlist->emplace_back(std::make_shared<Damage>(enemy.position + Eigen::Vector3d(4,0,0.1), std::array<int, 2>{{24, 28}}, true, [](auto & yield, Damage & damage)
				{
					for (int time = 0; time < 100; ++time)
					{
						//damage.position[0] += 3;
						yield();
					}
					damage.enable = false;
				}));
			}
		}));
		gameObjectlist->emplace_back(std::make_shared<Enemy>(gameObjectlist, Eigen::Vector3d(128, 0, 0), [](auto & yield, Enemy & enemy)
		{
			while (true)
			{
				for (int i = 0; i < 100; ++i)
				{
					yield();
				}
				enemy.gameObjectlist->emplace_back(std::make_shared<Damage>(enemy.position + Eigen::Vector3d(32, 0, 0.1), std::array<int, 2>{{80, 8}}, true, [](auto & yield, Damage & damage)
				{
					for (int time = 0; time < 100; ++time)
					{
						//damage.position[0] += 3;
						yield();
					}
					damage.enable = false;
				}));
			}
		}));
		std::mt19937 engine(std::random_device{}());
		std::uniform_int_distribution<int> pos(-256, 256);
		gameObjectlist->emplace_back(std::make_shared<Enemy>(gameObjectlist, Eigen::Vector3d(pos(engine), pos(engine), 0), [player](boost::coroutines::symmetric_coroutine<void>::yield_type & yield, Enemy & enemy)
		{
			while (true)
			{
				for (int i = 0; i < 120; ++i)
				{
					int amount = i / 60 + 1;
					if (player->position[0] < enemy.position[0])
					{
						enemy.position[0] -= amount;
					}
					else
					{
						enemy.position[0] += amount;
					}

					if (player->position[1] < enemy.position[1])
					{
						enemy.position[1] -= amount;
					}
					else
					{
						enemy.position[1] += amount;
					}
					yield();
				}
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
