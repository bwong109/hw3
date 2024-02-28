#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    
    // Set smaller and larger to null if current node is null
    if (head == nullptr) {
        smaller = larger = nullptr;
        return;
    }

    // Recur the rest of the list to split
    Node *nextNode = head->next; 
    llpivot(nextNode, smaller, larger, pivot);

    // If data of current node greater than pivot, move to larger list
    if (head -> val > pivot) {
        head -> next = larger;
        larger = head;
    }
    // Otherwise, move it to smaller list
    else {
        head -> next = smaller;
        smaller = head;
    }

    // Set head to null for original list to be gone
    head = nullptr;

}
