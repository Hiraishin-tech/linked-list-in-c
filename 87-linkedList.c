#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    char* name;
    int age;
    struct Person *nextPerson;
} Person;

Person *createNewPerson(char* name, const int age) {
   Person *newPerson = NULL;  
   newPerson = malloc(sizeof(Person));
   if (newPerson == NULL) {
       fprintf(stderr, "Allocation failed fro newPerson struct.\n");
       exit(EXIT_FAILURE);
   }
   newPerson->name = name;
   newPerson->age = age;
   newPerson->nextPerson = NULL; // automatically set to NULL, so every newPerson created will point nextPerson to NULL for safety.
   printf("Created new person at %p\n", newPerson);
   return newPerson;
}

void printPerson(Person *person, char *comment) {
    if (person == NULL) {
        fprintf(stderr, "%s is NULL", comment);
    }
    else {
        printf("name: %s, age: %d, address: %p, comment: %s\n", 
                person->name, person->age, person, comment);
    }
}

int main() {
    Person *alice = createNewPerson("Alice", 27); 
    Person *bob = createNewPerson("Bob", 34);
    Person *jonah = createNewPerson("Jonah", 16);
    Person *richard = createNewPerson("Richard", 46);
    Person *lucia = createNewPerson("Lucia", 21);

    alice->nextPerson = bob;
    bob->nextPerson = jonah;
    jonah->nextPerson = richard;
    richard->nextPerson = lucia;
    /* lucia->nextPerson = NULL; // End of list */

    // Traverse and print the list
    Person *temp = alice; // alice is the first Node
    while(temp != NULL) {
        printPerson(temp, "Traversing");
        temp = temp->nextPerson;
    }

    // Free memory
    Person *freeTemp = alice; // from first Node
    while(freeTemp != NULL) {
        Person *nextP = freeTemp->nextPerson;
        free(freeTemp);
        freeTemp = nextP;
    }

    return 0;
}
