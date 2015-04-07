#include <cstdlib>

class Point;

class Segment{
public:
	Point* leftPoint;
	Point* rightPoint;

	Segment(){

	};
	Segment(double x1, double y1, double x2, double y2){
		Point *p1 = new Point(x1,y1,this);
		Point *p2 = new Point(x2,y2,this);
		leftPoint = p1;
		rightPoint = p2;
	}
};