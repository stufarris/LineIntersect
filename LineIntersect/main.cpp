//#include "Point.h"
//#include "Segment.h"
#include <iostream>
#include <queue>  
#include "AVL.h"

using namespace std;

void printSegment(Segment* s);
void generateRandomNodes(int numSegments, avlTree*, double xValue);
void printQueue(priority_queue<Point*, vector<Point*>, compare>&);

struct compare
{
	bool operator()(const Point* p1, const Point* p2)
	{
		//return l > r;
		return p1->x > p2->x;
	}
};

//int main(){

	//Segment *s1 = new Segment(1.0,1.0,2.0,2.0);

	//printSegment(s1);
	//system("PAUSE");
	//return 0;

//}
int main()
{
	avlTree activeSegments;
	priority_queue<Point*, vector<Point*>, compare> pointQueue;
	

	system("PAUSE");
    return 0;
}


void printSegment(Segment* s){
	cout << "(" << s->leftPoint->x << "," << s->leftPoint->y << ")-(" << s->rightPoint->x << "," << s->rightPoint->x << ")" << endl;
};

void printQueue(priority_queue<Point*, vector<Point*>, compare>& priorityQ){
	while (!priorityQ.empty()){
		cout << "(" << priorityQ.top()->x << "," << priorityQ.top()->y << ")" << endl;
		priorityQ.pop();
	}
}

void generateRandomNodes(int numSegments, avlTree* currentAVL, double xValue){
	srand(time(NULL));
	for (int i = 0; i < numSegments; i++){
		currentAVL->generateRandomNode(xValue);
	}
}