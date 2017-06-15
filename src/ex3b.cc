/*----------------------------------------------------------------------------*/
/******************************************************************************
 ** Created by @author Omer Schwartz

               @email 23know.one(2).omer at gm(a)il d.o.t.com

        ## See ID and login on README file attached! ##

   This Program creates a BST from user values taken from cin, and finds the
   minimum depth leaf in that tree using a BFS algorithm.
   This algorithm allows for the program to end sooner than checking for each
   branch's depth since on the average case, we will only go through

   O(2^k) <= O(2^h) = O(n) nodes [where k = min_depth_leaf].
   Worst case: O(n)=O(2^h) [where h = height of tree].

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
typedef struct{

    int _treeSize;
    struct Node* _root;
}Tree;

struct Node {

    Tree* _rootTree;
    int _data ;
    bool _visited;
    struct Node *_left, *_right;
};

typedef struct{

    Node** _nodes;      //array of Node pointers
    int _head_index;
    int _tail_index;
} Queue;
/*------------------------- Function Declaration -----------------------------*/
/*-------------------------- Private  Function -------------------------------*/
/**
 * Create a new node with _data attribute of @param value and tree as _root of
 * newNode.
 * @param value any integer
 * @param the Tree struct pointer representing the root of the tree
 * @return pointer to new Node struct
 */
Node*   createNewNode(Tree* tree, const int value);

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
 * Allocate an empty Tree struct.
 * Note: the Node struct within _root is uninitialized.
 * @return pointer to newly allocated Tree struct
 */
Tree*   treeCreate();

/**
 * Receives input from user and creates a BST with those values.
 * @param tree pointer to an allocated Tree struct
 */
void    getUserValues(Tree* tree);

/**
 * Delete tree struct and all its Node structs.
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
 * Finds the the leaf with the minimum (least) depth in the BST.
 * It uses a Breadth-First Search algorithm to traverse the tree "horizontally",
 * meaning it goes through all the nodes in the same height from the root
 * (starting from 1), going left to right, and if a leaf was not found, advances
 * to traverse all nodes with height of 2 and so on..
 * Using 2 Queues to undo changes to the state of node_visited in each node.
 * Note: we override the const modifier by getting a pointer from the root node
 * to it's Tree parent struct and back to the root without a const modifier.
 * This casting is necessary for the algorithm to work. No modifications are
 * done to any Node and any change is reverted.
 *
 * @param root the first Node of the tree.
 * @return pointer to the Node that is in the minimum depth (first one from any
 * other node, ordered by in-order).
 */
const Node* min_depth_leaf(const Node *root) ;
/*--------------------------- Queue   Function -------------------------------*/

/**
 * Creates an empty Queue struct in size of @param size
 * @param size the size of the desired queue.
 * Note: Queue Should be the size of the tree.
 * @return empty Queue pointer.
 */
Queue * createQueue(int size);

/**
 * Deletes the Queue object
 * @param q to delete
 */
void    deleteQueue(Queue* q);

/**
 * Add @param node to Queue @param queue. (FIFO)
 * @param queue where to enqueue
 * @param node add node to end of the line
 */
void    enqueue(Queue* queue, Node* node);

/**
 * Remove next Node in the @param queue.
 * @param queue to dequeue from
 * @return pointer to the next node in the queue. @returns NULL if queue is
 * empty.
 */
Node*   dequeue(Queue* queue);

/**
 * Checks if the @param queue is empty.
 * @param queue to check.
 * @return true if queue has no items in it, false otherwise.
 */
bool    isEmpty(Queue* queue);

/**
 * Helper Function. Simply checks if @param node is a leaf.
 * @param node to check.
 * @return true if node has no child nodes, meaning it is a leaf.
 * False, otherwise.
 */
bool    isLeaf(const Node* node);

/*----------------------------------------------------------------------------*/
/*------------------------- Function Implementation --------------------------*/
/*----------------------------- Main Section ---------------------------------*/
/**
 * Create am empty tree, and gets the user input and adds them to the tree,
 * creating a BST.
 * Then, finds the minimum node in the tree and prints it's value.
 * Lastly, deleting the tree.
 */
int main() {
    Tree *t = treeCreate();
    getUserValues(t);
    const Node *node;

    //Not an empty tree:
    if (t->_treeSize != 0) {
        node = min_depth_leaf(t->_root);
        if (node != NULL) {
            cout << node->_data;
        }
    }
    treeDelete(t);
    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
Node*   createNewNode(Tree* tree, const int value){
    Node* newNode;
    if ((newNode = new(std::nothrow) Node) == NULL){
        cerr << "Failed to allocate memory in createNewNode()";
        exit(EXIT_FAILURE);
    }
    newNode->_data = value;
    newNode->_rootTree = tree;
    newNode->_visited = false;      //Visited used in BFS
    return newNode;
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
void    nodeDelete(Node* node){

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
Tree*   treeCreate(){
    Tree * t;
    if ((t = new(std::nothrow) Tree) == NULL){
        cerr << "Failed to allocate memory in treeCreate()";
        exit(EXIT_FAILURE);
    }
    t->_treeSize = 0;
    return t;
}
/*----------------------------------------------------------------------------*/
void    getUserValues(Tree* tree){

    int userInput = 0;
    cin >> userInput;
    while (!cin.eof()){

        //Add values to tree
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

    Node* newNode = createNewNode(tree, value);
    Node* currentNode;

    //If empty tree
    if (tree->_root == NULL){
        tree->_root = newNode;
    }
    else{
        currentNode = tree->_root;

        //Find the correct location for newNode
        nodeAdd(currentNode, newNode);
    }
    ++tree->_treeSize;      //Keep the size of tree
}
/*----------------------------------------------------------------------------*/
const Node* min_depth_leaf(const Node *root){

    //queue is used for the algorithm, secondary to revert changes to nodes
    Queue* queue = createQueue(root->_rootTree->_treeSize);
    Queue* secondary = createQueue(root->_rootTree->_treeSize);

    Node* node = root->_rootTree->_root;  //"Casting" a const Node to Node

    //Start with root
    enqueue(queue, node);
    enqueue(secondary, node);

    //Mark as visited so we do not enqueue it again, otherwise it will cause
    //an infinite loop
    node->_visited = true;

    while(!isEmpty(queue)){

        //Check if node is a leaf
        node = dequeue(queue);
        if (isLeaf(node)){
            break;  //stop if true
        }

        /*
            enqueue left and right children of node, making them next in line
            to be checked. If we are deeper then an unchecked node that is higher
            then in the queue they will appear only after that node.
        */
        if(node->_left != NULL && !node->_left->_visited){
            node->_left->_visited = true;
            enqueue(queue, node->_left);

            //enqueue to secondary to be reverted later.
            enqueue(secondary, node->_left);
        }
        if(node->_right != NULL && !node->_right->_visited){
            node->_right->_visited = true;
            enqueue(queue, node->_right);
            enqueue(secondary, node->_right);
        }
    }

    //Perform afterwards - revert all visited from true to false.
    while (!isEmpty(secondary)) {
        dequeue(secondary)->_visited = false;
    }
    deleteQueue(secondary); //Cleanup
    deleteQueue(queue);
    return node;            //minimum depth leaf
}
/*----------------------------------------------------------------------------*/
Queue * createQueue(int size){

    Queue* queue;
    if ((queue = new (std::nothrow) Queue) == NULL
        || ((queue->_nodes = new(std::nothrow) Node* [size]) == NULL)){
        cerr << "Failed to allocate memory in createQueue()";
        exit(EXIT_FAILURE);
    }
    queue->_head_index = 0;     //Simple array implementation of a queue with
    queue->_tail_index = -1;    //head and tail indices
    return queue;
}
/*----------------------------------------------------------------------------*/
void    deleteQueue(Queue* q){
    delete[](q->_nodes);
    delete(q);
}
/*----------------------------------------------------------------------------*/
void    enqueue(Queue* queue, Node* node){

    //Put node in the next available space.
    //Assume queue is in the size of tree, so no overflow will occur
    queue->_nodes[++queue->_tail_index] = node;
}
/*----------------------------------------------------------------------------*/
Node*   dequeue(Queue* queue){

    //if queue not empty, extract the next node in line
    //Return NULL if queue is empty
    if (!isEmpty(queue)){
        return queue->_nodes[queue->_head_index++];
    } else return NULL;
}
/*----------------------------------------------------------------------------*/
bool    isEmpty(Queue* queue){

    //Empty queue is determined if the next to dequeue index is higher than
    //the enqueue index. Meaning check if we didn't extract more items than
    //items put.
    return queue->_tail_index < queue->_head_index;
}
/*----------------------------------------------------------------------------*/
bool    isLeaf(const Node* node){
    return (node != NULL && node->_left == NULL && node->_right == NULL);
}
/*----------------------------------------------------------------------------*/
