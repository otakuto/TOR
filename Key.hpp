#pragma once

enum class Key : int
{
	None = 0,
	Up = 1 << 0,
	Down = 1 << 1,
	Right = 1 << 2,
	Left = 1 << 3,
	Jump = 1 << 4,
	ActionA = 1 << 5,
	ActionB = 1 << 6,
	ActionC = 1 << 7,
	ActionD = 1 << 8
};

