#include <cstdlib>
class Point;


struct compare
{
	bool operator()(const Point* p1, const Point* p2)
	{
		//return l > r;
		return p1->x > p2->x;
	}
};