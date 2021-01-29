#include <iostream>

// linked lists part 2, the big boy sequel rated R
// finding the middle of a linked list
// SOURCE: https://www.geeksforgeeks.org/write-a-c-function-to-print-the-middle-of-the-linked-list/
// geeksforgeeks carrying my ass

/*-------------------------------------------------------------------------------------------------

Traverse linked list using two pointers. Move one pointer by one and the other pointers by two.
When the fast pointer reaches the end slow pointer will reach the middle of the linked list.

--------------------------------------------------------------------------------------------------*/

struct Node{
    int data;
    struct Node* next;
};

void Middle(struct Node* head) {
    // slow and fast pointer???
    // i sure wish theyd explain these things
    struct Node* slow_ptr = head;
    struct Node* fast_ptr = head;

    if (head != NULL) { // if there is still another node
        while(fast_ptr != NULL && fast_ptr -> next != NULL) { // if ptr is not null
                                                              // if reference to next is not null either
            fast_ptr = fast_ptr->next->next; // uhh, fast = fast reference to next ref to next??
            slow_ptr = slow_ptr->next; // no clue what this is for, good code bad explanations
        }
        std::cout<<"Middle Value: "<< slow_ptr->data << std::endl; // ok waht, so slowptr is middle?
    }
}

void Push(struct Node** head_ref, int new_data) { // fucking showoffs EXPLAIN PLEASE
    // allocate new node on the heap, so within dynamic memory
    struct Node* new_node = new Node;
    // toss in some data to data
    new_node -> data = new_data;
    // link old list
    new_node->next = (*head_ref); // man idk this either || is there any need for () over the pointer?
    // move the head to point to another node
    (*head_ref) = new_node;
}

void printl(struct Node* ptr){ // same function as last time, print everything inside of the linked list
    while(ptr!=NULL) { // ptr is the pointer to the next value in linked list?
        std::cout<<  ptr->data << " -> ";
        ptr = ptr -> next; // ptr is updated to the next node within the linked list
    }
    std::cout<<"NULL\n";
}

int main() {
    // empty list
    struct Node* head = NULL;
    for (int i = 5; i>0; i--) {
        Push(&head, i); // Push a reference to head linked list and an integer 5-1?
        printl(head);   // print out all values within head
        Middle(head);   // print out middle value of head
    }
    return 0;
}
// holy fucking shit this is the coolest thing ive ever seen
// besides ascii ray tracing but feck off yea?
