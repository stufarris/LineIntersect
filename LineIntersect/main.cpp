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