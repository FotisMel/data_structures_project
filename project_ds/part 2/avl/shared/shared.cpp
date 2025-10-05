#include <iostream>
#include <iomanip>

#include "../../basics/basics.hpp"
#include "shared.hpp"

AVLNode * root = nullptr;

// calculate the height of node using recursion to its left and right subtrees

int height (AVLNode * node) {
    if (node == nullptr) return 0;
    int rheight = height (node->r);                             // get height of right subtree
    int lheight = height (node->l);                             // get height of left subtree
    if (rheight >= lheight) node->height = rheight + 1;         // check which one is bigger
    else node->height = lheight + 1;
    return node->height;
}

// update the height of the entire tree by updating the height of root

void update (void) {
    height (root);
}

// calculate the balance of node using the height(AVLNode * node) function

int bal (AVLNode * node) {
    return height (node->r) - height (node->l);                 // return the balance factor of node (height of right subtree - height of left subtree)
}

// perform RR rotation to node and its left child node

void RR (AVLNode * node) {
    if (node == nullptr) return;                                // guard clause - check if node exists
    if (node->l == nullptr) return;                             // guard clause - check if node's left child exists
    AVLNode * child = node->l;
    AVLNode * subtree = child->r;
    if (node == root) {                                         // RR rotation between node == root and its left child
        root = child;
        child->p = nullptr;
    } else {                                                    //  RR rotation between node != root and its left child
        if (node->p->r == node) node->p->r = child;
        else node->p->l = child;
        child->p = node->p;
    }
    node->p = child;
    node->l = subtree;
    child->r = node;
    if (subtree != nullptr) subtree->p = node;
    update();
}

// perform LL rotation to node and its right child node

void LL (AVLNode * node) {
    if (node == nullptr) return;                                // guard clause - check if node exists
    if (node->r == nullptr) return;                             // guard clause - check if node's left child exists
    AVLNode * child = node->r;
    AVLNode * subtree = child->l;
    if (node == root) {                                         // LL rotation between node == root and its right child
        root = child;
        child->p = nullptr;
    } else {                                                    // LL rotation between node != root and its right child
        if (node->p->r == node) node->p->r = child;
        else node->p->l = child;
        child->p = node->p;
    }
    node->p = child;
    node->r = subtree;
    child->l = node;
    if (subtree != nullptr) subtree->p = node;
    update();
}

// check balance of node and child nodes, and perform the correct rotation

bool rotation (AVLNode * node) {
    if (node == nullptr) return false;                          // guard clause - check if node exists
    int nbal = bal (node);                                      // get balance of node
    if (nbal < 1 && nbal > - 1) return false;
    if (nbal > 1) {                                             // right heavy AVL tree
        if (node->r == nullptr) return false;                   // guard clause - check if node's right child exists
        int cbal = bal (node->r);                               // get balance of node's right child
        if (cbal > 0) LL (node);                                // LL rotation - violation at right child's right subtree
        else if (cbal < 0) {                                    // RL rotation - violation at right child's left subtree
            RR (node->r);
            LL (node);
        }
    } else if (nbal < - 1) {                                    // left heavy AVL tree
        if (node->l == nullptr) return false;                   // guard clause - check if node's left child exists
        int cbal = bal (node->l);                               // get balance of node's left child
        if (cbal < 0) RR (node);                                // RR rotation - violation at left child's left subtree
        else if (cbal > 0) {                                    // LR rotation - violation at left child's right subtree
            LL (node->l);
            RR (node);
        }
    }
    return true;												// to get here, the method must have performed the rotations, so it returns true
}

// perform the balance check and function on every node on the path from leaf node to root

void balPath (AVLNode * node) {
    while (node != nullptr) {
        int nbal = bal (node);
        if (nbal > 1 || nbal < - 1) rotation (node);			// while the balance factor of node violates the rules of AVL tree, the method keeps performing rotations at node
        else node = node->p;									// else, the rotations are then performed to its parent, and so on and so forth, until the method reaches the root
    }
}

// search the subtree with root == node for node with key == key using recursion, or return the last leaf node parsed

AVLNode * searchAVLNode (AVLNode * node, int key) {
    AVLNode * ptr;
    if (node == nullptr) ptr = nullptr;                         // guard clause - check if node exists
    else if (node->key == key) ptr = node;                      // node with correct key found
    else if (node->key < key) {                                 // search the right subtree of node
        if (node->r == nullptr) ptr = node;                     // if you can't continue searching right, then return the current leaf node
        else ptr = searchAVLNode (node->r, key);                // if you can continue searching right, do so
    } else if (node->key > key) {                               // search the left subtree of node
        if (node->l == nullptr) ptr = node;                     // if you can't continue searching left, then return the current leaf node
        else ptr = searchAVLNode (node->l, key);				// if you can continue searching left, do so
    }
    return ptr;
}

// wrapper of search(AVLNode * node, int key) function so that it always searches from the root of the AVL tree

AVLNode * search (int key) {
    return searchAVLNode (root, key);
}

// insert a new AVLNode into the AVL tree

AVLNode * create (AVLNode * node, std :: string date, float temp, int key) {
    AVLNode * newNode = new AVLNode;                          	// dynamically allocate memory for new node element
    newNode->date.push_back (date);                         	// enter date value into date vector
    newNode->temp.push_back (temp);                          	// enter temp value into temp vector
    newNode->key = key;											// initialize node's key field
    newNode->p = node;											// initialize node's parent pointer
    if (root == nullptr && node == nullptr) root = newNode;
    else {
        if (node->key < key) node->r = newNode;
        else node->l = newNode;
    }
	return newNode;
}