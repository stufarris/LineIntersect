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
	cout << "test" << endl;

	avlTree avl;
	avlTree *currentAVL = &avl;
	generateRandomNodes(10, currentAVL, 2.0);

	cout << "Balanced AVL Tree:" << endl;
	avl.display(root, 1);

    //while (1)
    //{
    //    cout<<"\n---------------------"<<endl;
    //    cout<<"AVL Tree Implementation"<<endl;
    //    cout<<"\n---------------------"<<endl;
    //    cout<<"1.Insert Element into the tree"<<endl;
    //    cout<<"2.Display Balanced AVL Tree"<<endl;
    //    cout<<"3.InOrder traversal"<<endl;
    //    cout<<"4.PreOrder traversal"<<endl;
    //    cout<<"5.PostOrder traversal"<<endl;
    //    cout<<"6.Exit"<<endl;
    //    cout<<"Enter your Choice: ";
    //    cin>>choice;
    //    switch(choice)
    //    {
    //    /*case 1:
    //        cout<<"Enter value to be inserted: ";
    //        cin>>item;
    //        root = avl.insert(root, item);
    //        break;*/
    //    case 2:
    //        if (root == NULL)
    //        {
    //            cout<<"Tree is Empty"<<endl;
    //            continue;
    //        }
    //        cout<<"Balanced AVL Tree:"<<endl;
    //        avl.display(root, 1);
    //        break;
    //    case 3:
    //        cout<<"Inorder Traversal:"<<endl;
    //        avl.inorder(root);
    //        cout<<endl;
    //        break;
    //    case 4:
    //        cout<<"Preorder Traversal:"<<endl;
    //        avl.preorder(root);
    //        cout<<endl;
    //        break;
    //    case 5:
    //        cout<<"Postorder Traversal:"<<endl;
    //        avl.postorder(root);    
    //        cout<<endl;
    //        break;
    //    case 6:
    //        exit(1);    
    //        break;
    //    default:
    //        cout<<"Wrong Choice"<<endl;
    //    }
    //}

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