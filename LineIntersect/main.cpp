#include <iostream>
#include <queue>  
#include "AVL.h"
using namespace std;

struct compare
{
	bool operator()(const Point* p1, const Point* p2)
	{
		//return l > r;
		return p1->x > p2->x;
	}
};

void printSegment(Segment* s);
void generateRandomSegments(int numSegments, priority_queue<Point*, vector<Point*>, struct compare>&);
void printQueue(priority_queue<Point*, vector<Point*>, struct compare>&);
void checkIntersect(Segment*, Segment*, priority_queue<Point*, vector<Point*>, struct compare>&, priority_queue<Point*, vector<Point*>, struct compare>&);


int main()
{
	avlTree activeSegments;
	priority_queue<Point*, vector<Point*>, compare> pointQueue;
	priority_queue<Point*, vector<Point*>, compare> intersectionQueue;
	double sweepLine = 0.0;
	generateRandomSegments(10, pointQueue);
	Point* currentPoint;

	while (!pointQueue.empty()){
		currentPoint = pointQueue.top();
		sweepLine = currentPoint->x;
		//if endpoint
		if (currentPoint->type == Point::END_POINT){
			//if left endpoint add segment to avl
			if (sweepLine == currentPoint->parentSegment->leftPoint->x){
				activeSegments.insert(root, currentPoint->parentSegment, sweepLine);
				//check successor and predecessor for intersections
			}
			//if right endpoint remove segment from avl
			else{
				activeSegments.deleteSegment(currentPoint->parentSegment, sweepLine);
				//check new neighbors for intersection
			}
		}
		//else if intersection
		else{
			//switch segments
		}
		pointQueue.pop();
	}

	Segment* s1 = new Segment(0.0, 2.0, 5.0, 2.0);
	Segment* s2 = new Segment(0.0, 20.0, 20.0, 0.0);
	pointQueue.push(s1->leftPoint);
	pointQueue.push(s1->rightPoint);
	pointQueue.push(s2->leftPoint);
	pointQueue.push(s2->rightPoint);

	printQueue(pointQueue);

	cout << endl;
	checkIntersect(s1, s2, pointQueue, intersectionQueue);

	printQueue(pointQueue);
	//generateRandomSegments(10, pointQueue);
	//printQueue(pointQueue);

	system("PAUSE");
    return 0;
}

void printSegment(Segment* s){
	cout << "(" << s->leftPoint->x << "," << s->leftPoint->y << ")-(" << s->rightPoint->x << "," << s->rightPoint->y << ")" << endl;
};

void printQueue(priority_queue<Point*, vector<Point*>, struct compare>& priorityQ){
	if (!priorityQ.empty()){
		Point* temp = priorityQ.top();
		cout << "(" << temp->x << "," << temp->y << ") -->Segment ";
		if (temp->type == Point::END_POINT){
			printSegment(temp->parentSegment);
		}
		else {
			printSegment(temp->intersectingSegment1);
			cout << " and ";
			printSegment(temp->intersectingSegment2);
		}
		priorityQ.pop();
		printQueue(priorityQ);
		priorityQ.push(temp);
	}
	return;
}

void generateRandomSegments(int numSegments, priority_queue<Point*, vector<Point*>, struct compare>& priorityQ){
	srand(time(NULL));
	Segment *temp;
	double x1, x2, y1, y2;
	for (int i = 0; i < numSegments; i++){
		x1 = rand() % 100;
		x2 = rand() % 100;
		y1 = rand() % 100;
		y2 = rand() % 100;
		temp = new Segment(x1, y1, x2, y2);
		priorityQ.push(temp->leftPoint);
		priorityQ.push(temp->rightPoint);
	}
	return;
}

void checkIntersect(Segment* s1, Segment* s2, priority_queue<Point*, vector<Point*>, struct compare>& priorityQ, priority_queue<Point*, vector<Point*>, struct compare>& intersectionQ){
	double x1, y1, x2, y2, x3, y3, x4, y4, ma, mb, xInt, yInt;
	x1 = s1->leftPoint->x;
	y1 = s1->leftPoint->y;
	x2 = s1->rightPoint->x;
	y2 = s1->rightPoint->y;
	x3 = s2->leftPoint->x;
	y3 = s2->leftPoint->y;
	x4 = s2->rightPoint->x;
	y4 = s2->rightPoint->y;
	ma = (y2 - y1) / (x2 - x1);
	mb = (y4 - y3) / (x4 - x3);

	if (ma == mb){
		return;
	}
	
	xInt = (y3 + ma*x1 - y1 - mb*x3) / (ma - mb);

	if (xInt > s1->leftPoint->x && xInt > s2->leftPoint->x && xInt < s1->rightPoint->x && xInt < s2->rightPoint->x){
		yInt = ma*xInt + y1 - (y2 - y1) / (x2 - x1)*x1;
		Point* intersection = new Point(xInt, yInt, s1, s2);
		priorityQ.push(intersection);
		intersectionQ.push(intersection);
	}
	return;

}