/*
 * C++ program to Implement AVL Tree
 */
#include "Point.h"
#include "Segment.h"
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#define pow2(n) (1 << (n))
using namespace std;
 
/*
 * Node Declaration
 */
struct avl_node
{
	Segment* s;
    double data;
    struct avl_node *left;
    struct avl_node *right;
}*root;
 
/*
 * Class Declaration
 */
class avlTree
{
    public:
        int height(avl_node *);
        int diff(avl_node *);
        avl_node *rr_rotation(avl_node *);
        avl_node *ll_rotation(avl_node *);
        avl_node *lr_rotation(avl_node *);
        avl_node *rl_rotation(avl_node *);
        avl_node* balance(avl_node *);
        avl_node* insert(avl_node *, Segment*, double);
		bool compare(Segment*, Segment*, double);
		avl_node* findSegment(avl_node*, Segment*, double);
		void deleteSegment(Segment*, double);
		void deleteSegmentInternal(avl_node*, bool, double xValue);
		void generateRandomNode(double);
        void display(avl_node *, int);
        void inorder(avl_node *);
        void preorder(avl_node *);
        void postorder(avl_node *);
        avlTree()
        {
            root = NULL;
        }
};
 
 
/*
 * Height of AVL Tree
 */
int avlTree::height(avl_node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
/*
 * Height Difference 
 */
int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
/*
 * Right- Right Rotation
 */
avl_node *avlTree::rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}
/*
 * Left- Left Rotation
 */
avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 
/*
 * Left - Right Rotation
 */
avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
/*
 * Right- Left Rotation
 */
avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
/*
 * Balancing AVL Tree
 */
avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}
 
/*
 * Insert Element into the tree
 */
avl_node *avlTree::insert(avl_node *root, Segment* seg, double xValue)
{
	double value = seg->leftPoint->y;
	//s = seg;
    if (root == NULL)
    {
        root = new avl_node;
		root->s = seg;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (compare(seg,root->s,xValue))
    {
        root->left = insert(root->left, seg,xValue);
        root = balance (root);
    }
    else if (!compare(seg,root->s,xValue))
    {
        root->right = insert(root->right, seg,xValue);
        root = balance (root);
    }
    return root;
}
 
/*
 * Display AVL Tree
 */
void avlTree::display(avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        //cout<<ptr->s->;
		cout << "(" << ptr->s->leftPoint->x << "," << ptr->s->leftPoint->y << ")-(" << ptr->s->rightPoint->x << "," << ptr->s->rightPoint->y << ")" << endl;
        display(ptr->left, level + 1);
    }
}

/*
 * Inorder Traversal of AVL Tree
 */
void avlTree::inorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data<<"  ";
    inorder (tree->right);
}
/*
 * Preorder Traversal of AVL Tree
 */
void avlTree::preorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    preorder (tree->left);
    preorder (tree->right);
 
}
 
/*
 * Postorder Traversal of AVL Tree
 */
void avlTree::postorder(avl_node *tree)
{
    if (tree == NULL)
        return;
    postorder ( tree ->left );
    postorder ( tree ->right );
    cout<<tree->data<<"  ";
}

bool avlTree::compare(Segment* s1, Segment* s2, double xValue){
	double yValue1 = (s1->rightPoint->y - s1->leftPoint->y)/(s1->rightPoint->x - s1->leftPoint->x)*xValue + s1->leftPoint->y - (s1->rightPoint->y - s1->leftPoint->y)/(s1->rightPoint->x - s1->leftPoint->x)*s1->leftPoint->x;
	double yValue2 = (s2->rightPoint->y - s2->leftPoint->y)/(s2->rightPoint->x - s2->leftPoint->x)*xValue + s2->leftPoint->y - (s2->rightPoint->y - s2->leftPoint->y)/(s2->rightPoint->x - s2->leftPoint->x)*s2->leftPoint->x;
	//cout << yValue1 << endl;
	//cout << yValue2 << endl;
	if(yValue1 >= yValue2){
		return 0;
	}
	else{
		return 1;
	}
}

avl_node* avlTree::findSegment(avl_node *root, Segment* seg, double xValue){
	
	if (root == NULL){
		cout << "Not found";
		return NULL;
	}
	else if (root->s == seg){
		return root;
	}
	else if (!compare(seg, root->s, xValue)){
		return findSegment(root->right, seg, xValue);
	}
	else if (compare(seg, root->s, xValue)){
		return findSegment(root->left, seg, xValue);
	}

}

void avlTree::deleteSegment(Segment* seg, double xValue){
	avl_node* parentOfDeleteNode = root;
	while (true){
		if (parentOfDeleteNode == NULL){
			cout << "not found" << endl;
			return;
		}
		else if (parentOfDeleteNode == root && parentOfDeleteNode->s == seg){
			delete parentOfDeleteNode;
			parentOfDeleteNode = NULL;
			root = NULL;
			return;
		}
		else if (parentOfDeleteNode->left != NULL && parentOfDeleteNode->left->s == seg){
			deleteSegmentInternal(parentOfDeleteNode, 0, xValue);
			return;
		}
		else if (parentOfDeleteNode->right != NULL && parentOfDeleteNode->right->s == seg){
			deleteSegmentInternal(parentOfDeleteNode, 1, xValue);
			return;
		}
		else if (compare(seg, root->s, xValue)){
			parentOfDeleteNode = parentOfDeleteNode->left;
		}
		else if (!compare(seg, root->s, xValue)){
			parentOfDeleteNode = parentOfDeleteNode->right;
		}
	}
	/*
	avl_node* nodeToDelete = findSegment(root, seg, xValue);
		
	//no children
	if (nodeToDelete->left == NULL && nodeToDelete->right == NULL){
		delete nodeToDelete;
		nodeToDelete = NULL;
	}
	//one child
	else if (nodeToDelete->left != NULL && nodeToDelete->right == NULL){
		avl_node* temp = nodeToDelete;
		nodeToDelete = nodeToDelete->left;
		balance(nodeToDelete);
		delete temp;
		temp = NULL;
	}
	else if (nodeToDelete->right != NULL && nodeToDelete->left == NULL){
		avl_node* temp = nodeToDelete;
		nodeToDelete = nodeToDelete->right;
		balance(nodeToDelete);
		delete temp;
		temp = NULL;
	}	
	//two children
	else if (nodeToDelete->right != NULL && nodeToDelete->left != NULL){
		avl_node* temp = nodeToDelete->right;
		while (temp->left != NULL){
			temp = temp->left;
		}
		nodeToDelete->s = temp->s;
		delete temp;
		temp = NULL;
		balance(nodeToDelete);
	}*/
}

void avlTree::deleteSegmentInternal(avl_node* parent, bool direction, double xValue){
	//0 is left 1 is right
	//left
	if (!direction){
		//no children
		if (parent->left->left == NULL && parent->left->right == NULL){
			delete parent->left;
			parent->left = NULL;
			parent = balance(parent);
		}
		//one child to left
		else if (parent->left->left != NULL && parent->left->right == NULL){
			avl_node* temp = parent->left;
			parent->left = parent->left->left;
			parent = balance(parent);
			delete temp;
			temp = NULL;
		}
		//one child to right
		else if (parent->left->right != NULL && parent->left->left == NULL){
			avl_node* temp = parent->left;
			parent->left = parent->left->right;
			parent = balance(parent);
			delete temp;
			temp = NULL;
		}
	}
	//right
	else if (direction){
		//no children
		if (parent->right->left == NULL && parent->right->right == NULL){
			delete parent->right;
			parent->right = NULL;
			parent = balance(parent);
		}
		//one child to left
		else if (parent->right->left != NULL && parent->right->right == NULL){
			avl_node* temp = parent->right;
			parent->right = parent->right->left;
			parent = balance(parent);
			delete temp;
			temp = NULL;
		}
		//one child to right
		else if (parent->right->right != NULL && parent->right->left == NULL){
			avl_node* temp = parent->right;
			parent->right = parent->right->right;
			parent = balance(parent);
			delete temp;
			temp = NULL;
		}
	}
	return;
}

void avlTree::generateRandomNode(double xValue){
	double r = rand() % 100;
	cout << r << endl;
	root = insert(root, new Segment(0.0, r, 5.0, r) , xValue);
	cout << "inserted" << endl;
}