#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for separate chaining
struct node {
    char* key;
    char* value;
    struct node* next;
};

// HashMap structure
struct hashMap {
    int capacity;       // Total array size
    struct node** arr;  // Array of linked list heads
};

// Initialize the hash map
void initializeHashMap(struct hashMap* mp, int capacity) {
    mp->capacity = capacity;
    mp->arr = (struct node**) malloc(sizeof(struct node*) * capacity);
    for (int i = 0; i < capacity; i++)
        mp->arr[i] = NULL;
}

// A simple hash function for strings
int hashFunction(struct hashMap* mp, char* key) {
    unsigned long int hashVal = 0;
    int i = 0;
    while (key[i] != '\0') {
        hashVal = (hashVal * 31 + key[i]) % mp->capacity;
        i++;
    }
    return (int)hashVal;
}

// Insert key-value pair into hash map
void insert(struct hashMap* mp, char* key, char* value) {
    int index = hashFunction(mp, key);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = mp->arr[index];
    mp->arr[index] = newNode;
}

// Search value by key in hash map
char* search(struct hashMap* mp, char* key) {
    int index = hashFunction(mp, key);
    struct node* temp = mp->arr[index];
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL;  // Not found
}

// Delete key from hash map
void deleteKey(struct hashMap* mp, char* key) {
    int index = hashFunction(mp, key);
    struct node* temp = mp->arr[index];
    struct node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL)
                mp->arr[index] = temp->next;
            else
                prev->next = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Free all allocated memory
void freeHashMap(struct hashMap* mp) {
    for (int i = 0; i < mp->capacity; i++) {
        struct node* temp = mp->arr[i];
        while (temp != NULL) {
            struct node* next = temp->next;
            free(temp->key);
            free(temp->value);
            free(temp);
            temp = next;
        }
    }
    free(mp->arr);
}

int main() {
    struct hashMap map;
    initializeHashMap(&map, 10);

    insert(&map, "apple", "fruit");
    insert(&map, "carrot", "vegetable");
    insert(&map, "banana", "fruit");
    insert(&map, "cucumber", "vegetable");

    char* value = search(&map, "banana");
    if (value) printf("Value for 'banana': %s\n", value);
    else printf("'banana' not found\n");

    deleteKey(&map, "apple");
    value = search(&map, "apple");
    if (value) printf("Value for 'apple': %s\n", value);
    else printf("'apple' not found\n");

    freeHashMap(&map);
    return 0;
}
