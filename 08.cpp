#include <iostream>
// linked lists hee hee ha fucking kill me
// SOURCE: https://www.geeksforgeeks.org/linked-list-set-1-introduction/
// modified a bit

class Node {
public:
    // int data and pointer to class node?
    int data;
    Node* next; // pointer to the next node
                // example: second->data=2; second->next = third;
};

// function for printing out the linked list

void printl(Node* n) { // Node* n == the pointer to the next node within the list.. probably...
    while (n != NULL) {
        std::cout<< n->data << std::endl; // print the value of data
        n = n -> next; // update the value of n?
    }
}


int main() {

    // init maybe? idk these fuckers dont explain
    Node* head = NULL;
    Node* second = NULL;
    Node* third = NULL;

    // allocate 3 new nodes in the heap
    head = new Node();
    second = new Node();
    third = new Node();

    /* Three blocks have been allocated dynamically.
    We have pointers to these three blocks as head,
    second and third
    head         second         third
        |             |             |
        |             |             |
    +---+-----+     +----+----+     +----+----+
    | # | # |     | # | # |     | # | # |
    +---+-----+     +----+----+     +----+----+
    represents any random value.
    Data is random because we haven’t assigned
    anything yet */

    head -> data = 1; // assign data in first node
    head -> next = second; // Link first node with
    // the second node
    second -> data = 2; // int data, the value of data in this node :)
    second -> next = third; // link the next node, which is third

    third -> data = 3;
    third -> next = NULL;

    printl(head);

    return 0;
}
