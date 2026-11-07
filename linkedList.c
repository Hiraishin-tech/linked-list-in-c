#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* listFind (hledání podle jména) */
/* personRemove (smazání prvku, tady se hodí ukazatel na ukazatel nebo hlídání předchozího prvku) */

typedef struct Person {
    char* name;
    int age;
    struct Person *nextPerson;
} Person;

void printPerson(Person *person, char *comment) {
    if (person == NULL) {
        fprintf(stderr, "%s is NULL\n", comment);
    }
    else {
        printf("name: %s, age: %d, address: %p, comment: %s\n", 
                person->name, person->age, person, comment);
    }
}

// Will insert nodes to the start of the list. So e.g. calling listInsertFirst on Alice, Jonah, Bob, in this order
// will in the list look like Bob, Jonah, Alice.
Person *listInsertFirst(Person **head, char *name, int age) {
    Person *p = malloc(sizeof(Person));
    if (p == NULL) {
        return NULL;
    }
    p->name = name;
    p->age = age;
    p->nextPerson = *head; // new Node will point to the previous first Node.
    *head = p;
    return p;
}

// Inserts as the last Node.
Person *listInsertLast(Person **head, char *name, int age) {
    Person *p = malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Allocation failed!!");
        exit(EXIT_FAILURE);
    }
    p->name = name;
    p->age = age;

    Person *last = *head;
    if (last == NULL) {
        *head = p;
        last = p;
        return p;
        /* return NULL; */
    }

    while (last->nextPerson) {
        last = last->nextPerson;
    }
    last->nextPerson = p;
    p->nextPerson = NULL;
    return p;
}

Person *listFind(Person *head, char *nameToFind) {
   printf("Wanted person: %s\n", nameToFind);
   Person *curr = head;

   while(curr && strcmp(curr->name, nameToFind)) {
        curr = curr->nextPerson;
   }
   return curr;
}

void printList(Person *head) {
    while(head != NULL) {
        printPerson(head, "Traversing");
        head = head->nextPerson;
    }
}

void personRemove(Person **head, char *nameToRem) {
    Person *curr = *head;
    /* printf(">> %p\n", curr); */

    // When the list is empty:
    if(curr == NULL) {
        fprintf(stderr, "The list is empty.");
        return;
    }

    if(curr && !strcmp(curr->name, nameToRem)) {
        Person *pNext = curr->nextPerson;
        *head = pNext; // must not forget to point the head in main to the next Person.
        free(curr);
        return;
    }

    while(curr->nextPerson && strcmp(curr->nextPerson->name, nameToRem)) {
        curr = curr->nextPerson;
    }

    if (curr->nextPerson == NULL) {
        fprintf(stderr, "Person not found to remove.\n");
        return;
    }

    // found the person behind the one that is trying to remove, now point to the next Person
    Person *tempHead = curr->nextPerson;
    curr->nextPerson = tempHead->nextPerson;
    /* printf(">>To Remove Name: %s, Age: %d\n", tempHead->name, tempHead->age); */
    /* printf(">>Curr Name: %s, Age: %d\n", (curr)->name, (curr)->age); */
    /* printf(">>Head Name: %s, Age: %d\n", (*head)->name, (*head)->age); */
    free(tempHead);
}

void freeList(Person *head) {
    while(head != NULL) {
        Person *nextP = head->nextPerson;
        free(head);
        head = nextP;
    }
}

int main() {
    Person *head = NULL;

    listInsertFirst(&head, "Alice", 27);
    listInsertFirst(&head, "Jonah", 34);
    listInsertFirst(&head, "Bob", 16);
    listInsertFirst(&head, "Richard", 46);
    listInsertFirst(&head, "Lucia", 21);
    listInsertLast(&head, "Mark", 54);
    listInsertLast(&head, "Joseph", 42);

    // Traverse and print the list
    Person *temp = head; // first Node
    printList(temp);

    // Search the Person:
    Person *searchP = listFind(head, "Lucia");
    printPerson(searchP, "Searched Person");

    personRemove(&head, "Lucia");
    puts("");
    // Traverse and print the list
    Person *temp2 = head; // first Node
    printList(temp2);

    // Free memory
    Person *freeTemp = head; // from first Node
    /* printf(">>>>>>>>>>>>Head: %s\n", head->name); */
    freeList(freeTemp);

    return 0;
}
