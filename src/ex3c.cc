/*----------------------------------------------------------------------------*/
/******************************************************************************
 ** Created by @author Omer Schwartz

               @email 23know.one(2).omer at gm(a)il d.o.t.com

        ## See ID and login on README file attached! ##

   This Program

 ******************************************************************************/
/*--------------------------- Include Section --------------------------------*/
#include <iostream>
#ifndef EXIT_FAILURE
#include <cstdlib>
#endif
/*--------------------------- Using Section ----------------------------------*/
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
/*--------------------------- Type Definition --------------------------------*/
struct Tree_node {
    int _data ;
    struct Tree_node *_left, *_right ;
};

struct List_node {
    int _data ;
    struct List_node * _next;
};

typedef struct{

    struct Tree_node* _root;

}Tree;
/*------------------------- Function Declaration -----------------------------*/
/*-------------------------- Private  Function -------------------------------*/
/**
 * Create a new node with _data attribute of @param value
 * @param value any integer
 * @return pointer to new Tree_node struct
 */
Tree_node*   createNewNode(const int value);

/**
 * Add @param toAdd into the (sub)tree with root of @param node.
 * Recursively try to find the new node's correct location as a left or right
 * child of node.
 * @param node the root of the (sub)tree that will contain the new toAdd node.
 * @param toAdd the new node to add into the tree
 */
void    nodeAdd(Tree_node* node, Tree_node* const toAdd);

/**
 * Delete the Tree Node struct.
 * @param node to delete
 */
void    nodeDelete(Tree_node* node);

/*--------------------------- Public  Function -------------------------------*/
/**
 * Receives input from user and creates a BST with those values.
 * @param tree pointer to an allocated Tree struct
 */
void    getUserValues(Tree* tree);

/**
 * Allocate an empty Tree struct.
 * Note: the Tree node struct within _root is uninitialized.
 * @return pointer to newly allocated Tree struct
 */
Tree*   treeCreate();

/**
 * Delete tree struct and all its Tree_node structs.
 * @param tree to delete
 */
void    treeDelete(Tree* tree);

/**
 * Add a value into the Tree.
 * @param tree the Tree struct to add a value to.
 * @param value any integer
 */
void    treeAdd(Tree* tree, const int value);

/**
 * Add an integer @param value to a List @param list as the next link.
 * We assume that @param list is the last link in that list! Used incorrectly
 * will overwrite existing lists.
 * @param list where to insert value. List might be changed if is pointer to
 * an empty list.
 * @param value any integer
 * @return The List Node containing the new link (last link added to list)
 */
List_node*   addListNode(List_node*& list, const int value);

/**
 * Traverse the Tree in order and create a list with the values of the tree
 * arranged in a sorted ascending order.
 * @param list the begining of the list
 * @param current will be used to track the last added link in the list in the
 * recursion. Should start with a different pointer to the same List_node
 * @param node the root of the BST
 */
void    createSortedList(List_node *& list,
                         List_node *& current, const Tree_node* node);
/**
 * Print the List, containing a sorted linked list
 * @param node
 */
void    printSortedList(const List_node* node);

/**
 * Delete the List object and all it's List nodes
 * @param list
 */
void    sortedListDelete(List_node *list);
/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 * Creates a BST with user values received from cin, and stops on EOF.
 * Afterwards, it creates a sorted list from that tree, and prints the sorted
 * list.
 * Lastly, cleans up the tree and list.
 */
int main() {

    List_node* ln = NULL,           //ln will have the start of the list
             * ln_current = NULL;   //ln_current will have the end of list

    Tree *t = treeCreate();         //Create an empty tree
    getUserValues(t);               //Get user values into tree

    //Create sorted list
    createSortedList(ln, ln_current, t->_root);
    printSortedList(ln);            //Print it

    treeDelete(t);                  //Cleanup
    sortedListDelete(ln);
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
Tree_node*   createNewNode(const int value){
    Tree_node* newNode;
    if ((newNode = new(std::nothrow) Tree_node) == NULL){
        cerr << "Failed to allocate memory in createNewNode()";
        exit(EXIT_FAILURE);
    }
    newNode->_data = value;
    return newNode;
}
/*----------------------------------------------------------------------------*/
void    nodeAdd(Tree_node* node, Tree_node* const toAdd){
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
void    nodeDelete(Tree_node* node){

    //Delete nodes recursively using post-order traversal
    if (node->_left == NULL && node->_right == NULL){
        delete(node);
    }
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
List_node*   addListNode(List_node*& list, const int value){

    List_node* list_node;
    if((list_node = new(std::nothrow) List_node) == NULL){
        cerr << "Failed to allocate memory in addListNode()";
        exit(EXIT_FAILURE);
    }

    //if list is empty, update list to the new allocated list
    if (list == NULL){
        list =  list_node;
        list->_data = value;
        return list;
    }
        //Put new list node as the next link in that list
    else {
        list_node->_data = value;
        list->_next = list_node;
        return list->_next;
    }
}
/*----------------------------------------------------------------------------*/
Tree*   treeCreate(){
    Tree * t;
    if ((t = new(std::nothrow) Tree) == NULL){
        cerr << "Failed to allocate memory in treeCreate()";
        exit(EXIT_FAILURE);
    }
    return t;
}
/*----------------------------------------------------------------------------*/
void    getUserValues(Tree* tree){

    int userInput = 0;
    cin >> userInput;
    while (!cin.eof()){
        treeAdd(tree, userInput);
        cin >> userInput;
    }
}
/*----------------------------------------------------------------------------*/
void    treeDelete(Tree* tree){

    if (tree != NULL && tree->_root != NULL){
        nodeDelete(tree->_root);
    }
    delete(tree);
}
/*----------------------------------------------------------------------------*/
void    treeAdd(Tree* tree, const int value){

    Tree_node* newNode = createNewNode(value);
    Tree_node* currentNode;
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{
        currentNode = tree->_root;
        nodeAdd(currentNode, newNode);
    }

}
/*----------------------------------------------------------------------------*/
void    createSortedList(List_node *& list,
                      List_node *& current, const Tree_node* node){

    if (node == NULL){
        return;
    }
    if (node->_left != NULL){
        createSortedList(list, current, node->_left);
    }
    //Called once, when the list is started as an empty list.
    if (list == NULL) {
        current = addListNode(list, node->_data);
    }
    else{
        current = addListNode(current, node->_data);
    }
    if (node->_right != NULL){
        createSortedList(list, current, node->_right);
    }
}
/*----------------------------------------------------------------------------*/
void    printSortedList(const List_node* node){

    const List_node* list_node = node;

    while (list_node != NULL){

        cout << list_node->_data << " ";
        list_node = list_node->_next;
    }
    cout << endl;
}
/*----------------------------------------------------------------------------*/
void    sortedListDelete(List_node *list){

    List_node* node = list, *next_node;
    while (node != NULL){
        next_node = node->_next;
        delete(node);
        node = next_node;
    }
    delete(list);
}
/*----------------------------------------------------------------------------*/