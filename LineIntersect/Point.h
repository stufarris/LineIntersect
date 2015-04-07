#include <cstdlib>
class Segment;

class Point{
public:
	enum PointType
	{
		END_POINT,
		INTERSECTION
	};
	
	PointType type;	
	double x;
	double y;
	Segment* parentSegment;
	Segment* intersectingSegment1;
	Segment* intersectingSegment2;

	Point(double xInit, double yInit, Segment* parent){
		x = xInit;
		y = yInit;

		type = END_POINT;
		parentSegment = parent;
	}
};