#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Delete at beginning
void deleteBeginning(struct Node** head) {
    if (*head == NULL) return;
    struct Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) (*head)->prev = NULL;
    free(temp);
}

// Delete at end
void deleteEnd(struct Node** head) {
    if (*head == NULL) return;
    struct Node* temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else
        *head = NULL; // List had only one node

    free(temp);
}

// Delete at position (1-based index)
void deleteAtPosition(struct Node** head, int pos) {
    if (*head == NULL || pos < 1) return;

    struct Node* temp = *head;
    int i;
    for (i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;

    if (temp == NULL) return; // Position out of bounds

    if (*head == temp)
        *head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    free(temp);
}
