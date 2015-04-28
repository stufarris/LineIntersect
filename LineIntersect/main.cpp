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

const int NUM_SEGMENTS = 10;
void printSegment(Segment* s);
void generateRandomSegments(priority_queue<Point*, vector<Point*>, struct compare>&);
void generateSegments(priority_queue<Point*, vector<Point*>, struct compare>&);
void printQueue(priority_queue<Point*, vector<Point*>, struct compare>);
void checkIntersect(Segment*, Segment*, priority_queue<Point*, vector<Point*>, struct compare>&, priority_queue<Point*, vector<Point*>, struct compare>&, bool**);
void findIntersections();
void testTree();

//void printQueue(priority_queue<Point*, vector<Point*>, struct compare>);

int main(){
	findIntersections();
	//testTree();
	//generateRandomSegments(10, pointQueue);
	//printQueue(pointQueue);

	system("PAUSE");
    return 0;
}

void printSegment(Segment* s){
	//cout << "(" << s->leftPoint->x << "," << s->leftPoint->y << ")-(" << s->rightPoint->x << "," << s->rightPoint->y << ")" << endl;
	printf("(%.2lf, %.2lf)-(%.2lf, %.2lf)", s->leftPoint->x, s->leftPoint->y, s->rightPoint->x, s->rightPoint->y);
	//cout << endl;
}

void printQueue(priority_queue<Point*, vector<Point*>, struct compare> priorityQ){
	Point* temp;
	int size = priorityQ.size();
	for (int i = 0; i < size; i++){
		temp = priorityQ.top();
		cout << "(" << temp->x << ", " << temp->y << ")" << endl;
		priorityQ.pop();
	}
	return;
}

void generateRandomSegments(priority_queue<Point*, vector<Point*>, struct compare>& priorityQ){
	srand(time(NULL));
	Segment *temp;
	int intersectionCheckArrayIndex = 0;
	double x1, x2, y1, y2;
	for (int i = 0; i < NUM_SEGMENTS; i++){
		x1 = (double)rand() / (double)RAND_MAX * 100.0;
		x2 = (double)rand() / (double)RAND_MAX * 100.0;
		y1 = (double)rand() / (double)RAND_MAX * 100.0;
		y2 = (double)rand() / (double)RAND_MAX * 100.0;
		if (x1 < x2){
			temp = new Segment(x1, y1, x2, y2, intersectionCheckArrayIndex);
		}
		else{
			temp = new Segment(x2, y1, x1, y2, intersectionCheckArrayIndex);
		}
		intersectionCheckArrayIndex++;
		priorityQ.push(temp->leftPoint);
		priorityQ.push(temp->rightPoint);
		printSegment(temp);
		cout << endl;
	}
	return;
}

void generateSegments(priority_queue<Point*, vector<Point*>, struct compare>& priorityQ){
	Segment* s0 = new Segment(0.0, 7.0, 3.0, 0.0, 0);
	Segment* s1 = new Segment(8.0, 3.0, 9.0, 6.0, 1);
	Segment* s2 = new Segment(1.0, 1.0, 10.0, 5.0, 2);
	Segment* s3 = new Segment(5.0, 5.0, 7.0, 0.0, 3);
	Segment* s4 = new Segment(0.0, 5.0, 11.0, 3.0, 4);
	priorityQ.push(s0->leftPoint);
	priorityQ.push(s0->rightPoint);
	priorityQ.push(s1->leftPoint);
	priorityQ.push(s1->rightPoint);
	priorityQ.push(s2->leftPoint);
	priorityQ.push(s2->rightPoint);
	priorityQ.push(s3->leftPoint);
	priorityQ.push(s3->rightPoint);
	priorityQ.push(s4->leftPoint);
	priorityQ.push(s4->rightPoint);

	//printQueue(priorityQ);
	//cout << endl;
	
	//Segment* s5 = new Segment(0.0, 5.0, 5.0, 5.0);
	//Segment* s6 = new Segment(0.0, 6.0, 5.0, 6.0);
	//Segment* s7 = new Segment(0.0, 7.0, 5.0, 7.0);
	//Segment* s8 = new Segment(0.0, 8.0, 5.0, 8.0);
	//Segment* s9 = new Segment(0.0, 9.0, 5.0, 9.0);
	//Segment* s10 = new Segment(0.0, 10.0, 5.0, 10.0);
}

void checkIntersect(Segment* s1, Segment* s2, priority_queue<Point*, vector<Point*>, struct compare>& priorityQ, priority_queue<Point*, vector<Point*>, struct compare>& intersectionQ, bool** intersectionCheckArray){
	int s1Index = s1->intersectionCheckArrayIndex;
	int s2Index = s2->intersectionCheckArrayIndex;
	if (intersectionCheckArray[s1Index][s2Index] || intersectionCheckArray[s2Index][s1Index]){
		return;
	}
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
		intersectionCheckArray[s1Index][s2Index] = 1;
		intersectionCheckArray[s2Index][s1Index] = 1;
	}
	return;

}

void findIntersections(){
	avlTree activeSegments;
	priority_queue<Point*, vector<Point*>, compare> pointQueue;
	priority_queue<Point*, vector<Point*>, compare> intersectionQueue;
	avl_node* successor;
	avl_node* predecessor;
	bool **intersectionCheckArray;
	intersectionCheckArray = new bool*[NUM_SEGMENTS];
	for (int i = 0; i < 10; ++i) {
		intersectionCheckArray[i] = new bool[NUM_SEGMENTS];
		// each i-th pointer is now pointing to dynamic array (size 10) of actual int values
	}
	for (int i = 0; i < NUM_SEGMENTS; i++){
		for (int j = 0; j < NUM_SEGMENTS; j++){
			intersectionCheckArray[i][j] = false;
		}
	}
	int segmentsFound;
	double sweepLine = 0.0;
	generateRandomSegments(pointQueue);
	//generateSegments(pointQueue);
	Point* currentPoint;
	//printQueue(pointQueue);

	while (!pointQueue.empty()){
		currentPoint = pointQueue.top();
		sweepLine = currentPoint->x;

		//checks
		//cout << endl << "Current x Value: " << sweepLine << endl;
		
		//checks

		//if endpoint
		if (currentPoint->type == Point::END_POINT){
			//if left endpoint add segment to avl
			if (sweepLine == currentPoint->parentSegment->leftPoint->x){
				//insert the segment with the endpoint into the active segment BST
				root = activeSegments.insert(root, currentPoint->parentSegment, sweepLine);
				//check successor and predecessor for intersections
				if (activeSegments.height(root) > 0 && activeSegments.findSuccessor(root, currentPoint->parentSegment, sweepLine) != NULL){
					checkIntersect(currentPoint->parentSegment, activeSegments.findSuccessor(root, currentPoint->parentSegment, sweepLine)->s, pointQueue, intersectionQueue, intersectionCheckArray);
				}
				if (activeSegments.height(root) > 0 && activeSegments.findPred(root, currentPoint->parentSegment, sweepLine) != NULL){
					checkIntersect(currentPoint->parentSegment, activeSegments.findPred(root, currentPoint->parentSegment, sweepLine)->s, pointQueue, intersectionQueue, intersectionCheckArray);
				}
			}
			//if right endpoint remove segment from avl
			else{
				successor = activeSegments.findSuccessor(root, currentPoint->parentSegment, sweepLine);
				predecessor = activeSegments.findPred(root, currentPoint->parentSegment, sweepLine);
				//check new neighbors for intersection
				if (successor != NULL){
					if (predecessor != NULL){
						checkIntersect(successor->s, predecessor->s, pointQueue, intersectionQueue, intersectionCheckArray);
					}
				}		
				activeSegments.deleteSegment(currentPoint->parentSegment, sweepLine);
			}
		}
		//else if intersection
		else{
			//switch segments check new neighbors for intersections
			Segment* intersectingSegment1 = currentPoint->intersectingSegment1;
			Segment* intersectingSegment2 = currentPoint->intersectingSegment2;
			Segment** toCheck = activeSegments.swapSegments(intersectingSegment1, intersectingSegment2, sweepLine);
			Segment* check0 = toCheck[0];
			Segment* check1 = toCheck[1];
			Segment* check2 = toCheck[2];
			Segment* check3 = toCheck[3];
			if (check0 != NULL){
				checkIntersect(check0, check1, pointQueue, intersectionQueue, intersectionCheckArray);
			}
			if (check2 != NULL){
				checkIntersect(check2, check3, pointQueue, intersectionQueue, intersectionCheckArray);
			}			
		}
		//checks
		//cout << endl << "Current x Value: " << sweepLine << endl;
		//printQueue(pointQueue);
		//printQueue(pointQueue);
		//cout << endl;
		//activeSegments.display(root, 1);
		//checks
		pointQueue.pop();
	}
	cout << endl << "Intersections:" << endl;
	printQueue(intersectionQueue);
}

/*void testTree(){
	avlTree activeSegments;
	priority_queue<Point*, vector<Point*>, struct compare> priorityQ;
	priority_queue<Point*, vector<Point*>, struct compare> intersectionQ;
	Segment* s0 = new Segment(0.0, 7.0, 3.0, 0.0, 0);
	Segment* s1 = new Segment(8.0, 3.0, 9.0, 6.0, 1);
	Segment* s2 = new Segment(1.0, 1.0, 10.0, 5.0, 2);
	Segment* s3 = new Segment(5.0, 5.0, 7.0, 0.0, 3);
	Segment* s4 = new Segment(0.0, 5.0, 11.0, 3.0, 4);
	priorityQ.push(s0->leftPoint);
	priorityQ.push(s0->rightPoint);
	priorityQ.push(s1->leftPoint);
	priorityQ.push(s1->rightPoint);
	priorityQ.push(s2->leftPoint);
	priorityQ.push(s2->rightPoint);
	priorityQ.push(s3->leftPoint);
	priorityQ.push(s3->rightPoint);
	priorityQ.push(s4->leftPoint);
	priorityQ.push(s4->rightPoint);

	cout << "very beginning" << endl;
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "hit s0" << endl;
	root = activeSegments.insert(root, s0, 0.0);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "hit s4" << endl;
	root = activeSegments.insert(root, s4, 0.0);
	checkIntersect(s0, s4, priorityQ, intersectionQ);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "swaps s4 and s0" << endl;
	activeSegments.swapSegments(s0, s4, priorityQ.top()->x);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "hit s2" << endl;
	root = activeSegments.insert(root, s2, 1.0);
	checkIntersect(s2, s0, priorityQ, intersectionQ);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "swap s0 and s2" << endl;
	activeSegments.swapSegments(s0, s2, priorityQ.top()->x);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "delete s0" << endl;
	activeSegments.deleteSegment(s0, s0->rightPoint->x);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "hit s3" << endl;
	root = activeSegments.insert(root, s3, 1.0);
	checkIntersect(s3, s4, priorityQ, intersectionQ);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "swap s3 and s4" << endl;
	Segment** toCheck = activeSegments.swapSegments(s3, s4, priorityQ.top()->x);
	//Segment** toCheck = activeSegments.swapSegments(intersectingSegment1, intersectingSegment2, sweepLine);
	Segment* check0 = toCheck[0];
	Segment* check1 = toCheck[1];
	Segment* check2 = toCheck[2];
	Segment* check3 = toCheck[3];
	if (check0 != NULL){
		checkIntersect(check0, check1, priorityQ, intersectionQ);
	}
	if (check2 != NULL){
		checkIntersect(check2, check3, priorityQ, intersectionQ);
	}
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "swap s2 and s3" << endl;
	toCheck = activeSegments.swapSegments(s2, s3, priorityQ.top()->x);
	//Segment** toCheck = activeSegments.swapSegments(intersectingSegment1, intersectingSegment2, sweepLine);
	check0 = toCheck[0];
	check1 = toCheck[1];
	check2 = toCheck[2];
	check3 = toCheck[3];
	if (check0 != NULL){
		checkIntersect(check0, check1, priorityQ, intersectionQ);
	}
	if (check2 != NULL){
		checkIntersect(check2, check3, priorityQ, intersectionQ);
	}
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "delete s3" << endl;
	activeSegments.deleteSegment(s3, s3->rightPoint->x);
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	cout << "swap s2 and s4" << endl;
	toCheck = activeSegments.swapSegments(s2, s4, priorityQ.top()->x);
	//Segment** toCheck = activeSegments.swapSegments(intersectingSegment1, intersectingSegment2, sweepLine);
	check0 = toCheck[0];
	check1 = toCheck[1];
	check2 = toCheck[2];
	check3 = toCheck[3];
	if (check0 != NULL){
		checkIntersect(check0, check1, priorityQ, intersectionQ);
	}
	if (check2 != NULL){
		checkIntersect(check2, check3, priorityQ, intersectionQ);
	}
	priorityQ.pop();
	printQueue(priorityQ);
	activeSegments.display(root, 1);
	system("PAUSE");

	//avl_node* succesor = tree.findSuccessor(root, s8, 2.0);
	//avl_node* pred = tree.findPred(root, s8, 2.0);
	//cout << "Successor: ";
	//printSegment(succesor->s);
	//cout << "Predecessor: ";
	//printSegment(pred->s);
}*/

/*void printQueue(priority_queue<Point*, vector<Point*>, struct compare>& intersectionQueue){
	Point* temp;
	for (int i = 0; i < intersectionQueue.size(); i++){
		temp = intersectionQueue.top();
		cout << "(" << temp->x << ", " << temp->y << ")" << endl;
		intersectionQueue.pop();
		intersectionQueue.push(temp);
	}
}*/