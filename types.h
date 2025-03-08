#pragma once

struct int2
{
	int x;
	int y;
};

struct rect
{
	int2 pos;
	int2 size;
};

inline bool Overlaps(rect a, rect b)
{
	if (a.pos.x > (b.pos.x + b.size.x) || ((a.pos.x + a.size.x) < b.pos.x))
	{
		return false;
	}

	if (a.pos.y > (b.pos.y + b.size.y) || ((a.pos.y + a.size.y) < b.pos.y))
	{
		return false;
	}

	return true;
}