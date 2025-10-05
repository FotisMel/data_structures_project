#ifndef SHARED
#define SHARED

#include <string>
#include <vector>

// basic AVL tree node used for both date and temperature sorted AVL trees

struct AVLNode {
    std :: vector <std :: string> date;			// store at least one date value
    std :: vector <float> temp;					// store at least one temperature value
	int key;									// store a unique key for each node
	int height;									// store the height of each node
	AVLNode * r = nullptr;						// pointer to right child node - subtree
	AVLNode * l = nullptr;						// pointer to left child node - subtree
	AVLNode * p = nullptr;						// pointer to parent node
};

extern AVLNode * root;

int height (AVLNode *);

void update (void);

int bal (AVLNode *);

void RR (AVLNode *);

void LL (AVLNode *);

bool rotation (AVLNode *);

void balPath (AVLNode *);

AVLNode * searchAVLNode (AVLNode *, int);

AVLNode * search (int);

AVLNode * init (std :: string, float);

AVLNode * create (AVLNode *, std :: string, float, int);

#endif // SHARED