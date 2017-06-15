/*----------------------------------------------------------------------------*/
/******************************************************************************
 ** Created by @author Omer Schwartz

               @email 23know.one(2).omer at gm(a)il d.o.t.com

        ## See ID and login on README file attached! ##

   This Program takes a series of integers and creates a BST tree. Using the
   tree created, prints the minimum value from all the user input, and prints
   the tree's leaf nodes.

 ******************************************************************************/
/*--------------------------- Include Section --------------------------------*/
#include <iostream>
#ifndef EXIT_FAILURE
#include <cstdlib>  //For exit status
#endif
/*--------------------------- Using Section ----------------------------------*/
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
/*--------------------------- Type Definition --------------------------------*/
struct Node {
    int _data ;
    struct Node *_left, *_right ;
};

//Tree object contains the single Node root
typedef struct{
    struct Node* _root;

}Tree;

/*------------------------- Function Declaration -----------------------------*/
/*-------------------------- Private  Function -------------------------------*/
/**
 * Create a new node with _data attribute of @param value
 * @param value non-zero integer
 * @return pointer to new Node struct
 */
Node*   createNewNode(const int value);

/**
 * Add @param toAdd into the (sub)tree with root of @param node.
 * Recursively try to find the new node's correct location as a left or right
 * child of node.
 * @param node the root of the (sub)tree that will contain the new toAdd node.
 * @param toAdd the new node to add into the tree
 */
void    nodeAdd(Node* node, Node* const toAdd);

/**
 * Delete the Node struct.
 * @param node to delete
 */
void    nodeDelete(Node* node);

/*--------------------------- Public  Function -------------------------------*/
/**
 * Receives input from user and creates a BST with those values.
 * @param tree pointer to an allocated Tree struct
 */
void    getUserValues(Tree* tree);

/**
 * Allocate an empty Tree struct.
 * Note: the Node struct within _root is uninitialized.
 * @return pointer to newly allocated Tree struct
 */
Tree*   treeCreate();

/**
 * Delete tree struct and all its Node structs.
 * @param tree to delete
 */
void    treeDelete(Tree* tree);

/**
 * Add a value into the Tree.
 * @param tree the Tree struct to add a value to.
 * @param value a non zero integer
 */
void    treeAdd(Tree* tree, const int value);

/**
 * Print the Tree struct leaves.
 * @param root the root Node of the (sub)tree to print it's leaves.
 */
void    printTreeLeaves(const Node* root);

/**
 * print the minimum value of the Tree (leftmost leaf)
 * @param tree to find it's minimum value
 */
void    printMinimumTreeValue(const Tree *const tree);

/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 * Creates an empty tree, adds values to it from user, and prints the required
 * output: the tree's minimum value and all the tree's leaves.
 * @return EXIT_SUCCESS
 */
int main() {
    Tree *t = treeCreate();         //Create an empty tree
    getUserValues(t);               //Receive user input and insert into tree
    printMinimumTreeValue(t);       //Print the Tree's minimum value
    printTreeLeaves(t->_root);      //Print the Tree's leaves
    cout << endl;                   //print a newline at end of output
    treeDelete(t);                  //Cleanup
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
     Tree* t;
    if ((t = new(std::nothrow) Tree) == NULL){
        //TODO: add alloc checks
    }
    return t;
}
/*----------------------------------------------------------------------------*/
void    treeDelete(Tree* tree){

    //Delete all Nodes
    if (tree != NULL && tree->_root != NULL){
        nodeDelete(tree->_root);
    }
    delete(tree);
}
/*----------------------------------------------------------------------------*/
void    nodeDelete(Node* node){

    if (node->_left == NULL && node->_right == NULL){
        delete(node);
    }
        //Delete all nodes "post-order"
    else{
        if (node->_left != NULL){
            nodeDelete(node->_left);
        }
        if (node->_right != NULL){
            nodeDelete(node->_right);
        }
        delete(node);
    }
}
/*----------------------------------------------------------------------------*/
void    getUserValues(Tree* tree){

    int userInput = 0;
    cin >> userInput;
    while (userInput != 0){

        //Add user value to tree:
        treeAdd(tree, userInput);

        //Get next user value:
        cin >> userInput;
    }
}
/*----------------------------------------------------------------------------*/
void    treeAdd(Tree* tree, const int value){

    Node* currentNode, * newNode = createNewNode(value);
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{

        //Tree is not empty, add newNode to tree:
        currentNode = tree->_root;
        nodeAdd(currentNode, newNode);
    }

}
/*----------------------------------------------------------------------------*/
void    nodeAdd(Node* node, Node* const toAdd){
    if (node->_data < toAdd->_data){
        if (node->_right == NULL){
            //Insert new node to right subtree
            node->_right = toAdd;
        }
        else{
            //Find the correct location for new node in right subtree
            nodeAdd(node->_right, toAdd);
        }
    }
    else {
        if (node->_left == NULL) {
            //Insert new node to the left subtree
            node->_left = toAdd;
        }
        else {
            //Find the correct location for new node in left subtree
            nodeAdd(node->_left, toAdd);
        }
    }
}
/*----------------------------------------------------------------------------*/
Node*   createNewNode(const int value){
    Node* newNode;
    if ((newNode = new(std::nothrow) Node) == NULL) {
        //TODO: add alloc checks
    }
    newNode->_data = value;
    return newNode;
}
/*----------------------------------------------------------------------------*/
void    printTreeLeaves(const Node* const root){

    if (root == NULL){
        return;
    }

    //Print tree with "in-order" scheme, resulting in sorted array
    if (root->_left != NULL){
        printTreeLeaves(root->_left);
    }
    if (root->_left == NULL && root->_right == NULL) {
        cout << root->_data << " ";
    }
    if (root->_right != NULL){
        printTreeLeaves(root->_right);
    }
}
/*----------------------------------------------------------------------------*/
void    printMinimumTreeValue(const Tree *const tree){

    Node* node = tree->_root;
    if (node == NULL){
        return;
    }
    else {

        //Go to leftmost node
        while (node->_left != NULL) {
            node = node->_left;
        }
        cout << node->_data << endl;
    }
}
/*----------------------------------------------------------------------------*/