//#include "Point.h"
//#include "Segment.h"
#include <iostream>
#include "AVL.h"

using namespace std;

void printSegment(Segment* s);
void generateRandomNodes(int numSegments, avlTree*, double xValue);

//int main(){

	//Segment *s1 = new Segment(1.0,1.0,2.0,2.0);

	//printSegment(s1);
	//system("PAUSE");
	//return 0;

//}
int main()
{
	avlTree avl;

	system("PAUSE");
    return 0;
}


void printSegment(Segment* s){
	cout << "(" << s->leftPoint->x << "," << s->leftPoint->y << ")-(" << s->rightPoint->x << "," << s->rightPoint->x << ")" << endl;
};

void generateRandomNodes(int numSegments, avlTree* currentAVL, double xValue){
	srand(time(NULL));
	for (int i = 0; i < numSegments; i++){
		currentAVL->generateRandomNode(xValue);
	}
}