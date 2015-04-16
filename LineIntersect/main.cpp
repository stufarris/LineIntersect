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


int main()
{
	avlTree activeSegments;
	priority_queue<Point*, vector<Point*>, compare> pointQueue;
	priority_queue<Point*, vector<Point*>, compare>* pointQueuePointer = &pointQueue;
	double sweepLine;

	Segment *p0 = new Segment(0.0, 0.0, 5.0, 0.0);
	Segment *p1 = new Segment(0.0, 1.0, 5.0, 1.0);
	Segment *p2 = new Segment(0.0, 2.0, 5.0, 2.0);
	/*Segment *p3 = new Segment(0.0, 3.0, 5.0, 3.0);
	Segment *p4 = new Segment(0.0, 4.0, 5.0, 4.0);
	Segment *p5 = new Segment(0.0, 5.0, 5.0, 5.0);
	Segment *p6 = new Segment(0.0, 6.0, 5.0, 6.0);
	Segment *p7 = new Segment(0.0, 7.0, 5.0, 7.0);
	Segment *p8 = new Segment(0.0, 8.0, 5.0, 8.0);
	Segment *p9 = new Segment(0.0, 9.0, 5.0, 9.0);*/

	root = activeSegments.insert(root, p0, 2.0);
	root = activeSegments.insert(root, p1, 2.0);
	root = activeSegments.insert(root, p2, 2.0);
	/*root = activeSegments.insert(root, p3, 2.0);
	root = activeSegments.insert(root, p4, 2.0);
	root = activeSegments.insert(root, p5, 2.0);
	root = activeSegments.insert(root, p6, 2.0);
	root = activeSegments.insert(root, p7, 2.0);
	root = activeSegments.insert(root, p8, 2.0);
	root = activeSegments.insert(root, p9, 2.0);*/

	activeSegments.display(root, 1);

	activeSegments.deleteSegment(p0, 2.0);
	activeSegments.display(root, 1);
	activeSegments.deleteSegment(p1, 2.0);
	activeSegments.display(root, 1);


	//generateRandomSegments(10, pointQueue);
	//printQueue(pointQueue);

	system("PAUSE");
    return 0;
}

void printSegment(Segment* s){
	cout << "(" << s->leftPoint->x << "," << s->leftPoint->y << ")-(" << s->rightPoint->x << "," << s->rightPoint->y << ")" << endl;
};

void printQueue(priority_queue<Point*, vector<Point*>, struct compare>& priorityQ){
	while (!priorityQ.empty()){
		cout << "(" << priorityQ.top()->x << "," << priorityQ.top()->y << ") -->Segment ";
		printSegment(priorityQ.top()->parentSegment);
		priorityQ.pop();
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