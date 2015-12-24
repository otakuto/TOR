#pragma once

class Skill
{
public:
	int const & time;
	int usedTime;
	int coolTime;
	std::function<void()> skill;

	Skill(int const & time, int coolTime, std::function<void()> skill)
	:
	time(time),
	usedTime(time),
	coolTime(coolTime),
	skill(skill)
	{
	}

	void run()
	{
		if (usedTime <= time)
		{
			skill();
			usedTime = time + coolTime;
		}
	}
};
