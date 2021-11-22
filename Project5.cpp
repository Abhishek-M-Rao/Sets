// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Abhishek Rao
// amr7999
// Slip days used: 1
// Fall 2021
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) { //must be logN
    int high = self -> len - 1;
    int low = 0;
    while(low <= high){
        int middle = (high+low)/2;
        if(self -> elements[middle] < x){
            low = middle + 1;
        }
        if(self -> elements[middle] > x){
            high = middle - 1;
        }
        if(self -> elements[middle] == x){
            return true;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elements[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if (self->len == 0) {
        self->elements = (int*)realloc(self->elements, (sizeof(int))*(self->len+1));
        self->elements[0] = x;
        self->len += 1;
        return;
    }
    if(!isMemberSet(self, x)) {
        int* temp = (int*)malloc(sizeof(int) * (self->len + 1));
        for(int i = 0; i < self->len; i++){
            temp[i] = self->elements[i];
        }
        int i = self->len;
        while ((i > 0) && ((self->elements[i-1] > x))) {
            temp[i] = temp[i-1];
            i--;
        }
        temp[i] = x;
        self->len++;
        self->elements = (int*)realloc(self->elements, (sizeof(int) * (self->len + 1)));
        for(int i = 0; i < self->len; i++){
            self->elements[i] = temp[i];
        }
        free(temp);
    }
}

//    if(!isMemberSet(self, x)) {
//        realloc(self->elements, ((sizeof(int))*(self->len+1))); //makes one more spot on the elements array
//        int saveIndex;
//        int firstTime = 0;
//        for(int i = 0; i < self->len; i++){
//            if((self->elements[i] > x) && (firstTime == 0)){
//                saveIndex = i;
//                firstTime++;
//            }
//            if((i+1 == self->len) && (firstTime == 0)){
//                saveIndex = i+1;
//                firstTime++;
//            }
//        }
//        for(int i = self->len; i > saveIndex; i--) { //if in middle
//            self->elements[i] = self->elements[i-1];
//        }
//        self->elements[saveIndex] = x;
//        self->len++;
//        return;
//    }



/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if((isMemberSet(self, x)) && (self->len != 0)) {
        int saveIndex;
        for(int i = 0; i < self->len; i++){
            if(self->elements[i] == x){
                saveIndex = i;
            }
        }
        for(int i = saveIndex; i < self->len - 1; i++) {
            self->elements[i] = self->elements[i+1];
        }
        self->len--;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if ((self->len == 0) && (other->len == 0)) { //ask about this edge case
        return true;
    }
    if (self->len == other->len) {
        for (int i = 0; i < self->len; i++){
            if(self->elements[i] != other->elements[i]){
                return false; //if two elements are not equal
            }
        }
        return true; //if passes whole for loop
    }
    return false; //if the two set lengths are not equal or negative or something like that
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if ((self->len == 0) && (other->len == 0)) {
        return true;
    }
    if ((self->len == 0) && (other->len !=0)) {
        return true;
    }
    if ((self->len != 0) && (other->len ==0)) { //can't be subset if one or the other length is 0
        return false;
    }
    int X = 0; //index of self; for self to be subset of other, this index must be equal to self->len
    int Y = 0; //index of other
    while(Y < other->len) {
        if (self->elements[X] == other->elements[Y]) { //make sure comparison equal signs have == instead of =
            X++;
            Y++;
        }
        else if (self->elements[X] != other->elements[Y]) {
            Y++;
        }
        if (X == self->len) {
            return true;
        }
    }
        return false;
    }

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int X = 0; //increment first array's counter if second is greater than first
    int Y = 0; //increment second array's counter if first is greater than second
    int Z = 0; //needed for dummy array
    int* temp = (int*)malloc(sizeof(int)*other->len);
    while((X < self->len) && (Y < other->len)) {
        if (self->elements[X] > other->elements[Y]) {
            Y++;
        }
        else if (self->elements[X] == other->elements[Y]) {
            temp[Z] = self->elements[X];
            X++;
            Y++;
            Z++;
        }
        else if (self->elements[X] < other->elements[Y]) {
            X++;
        }
    }
    for(int i = 0; i < Z; i++){
        self->elements[i] = temp[i];
    }
    self->len = Z;
    free(temp);
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    int X = 0; //increment first array's counter if second is greater than first
    int Y = 0; //increment second array's counter if first is greater than second
    int Z = 0; //needed for dummy array
    int* temp = (int*)malloc(sizeof(int)*self->len);
    while((X < self->len) && (Y < other->len)) {
        if (self->elements[X] > other->elements[Y]) {
                Y++;
        }
        else if (self->elements[X] == other->elements[Y]) {
                X++;
                Y++;
        }
        else if (self->elements[X] < other->elements[Y]) {
            temp[Z] = self->elements[X];
            X++;
            Z++;
        }
    }
    while(X < self->len){
        temp[Z] = self->elements[X];
        X++;
        Z++;
    }
    for(int i = 0; i < Z; i++){
        self->elements[i] = temp[i];
    }
    self->len = Z;
    free(temp);
}


/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    int X = 0; //increment first array's counter if second is greater than first
    int Y = 0; //increment second array's counter if first is greater than second
    int Z = 0; //needed for dummy array
    int* temp = (int*)malloc(sizeof(int)*(other->len + self->len));
    self->elements = (int*)realloc(self->elements, sizeof(int) * (other->len + self->len));
    if((self->len > 0) && (other ->len == 0)){ //if others is empty and self has stuff
        free(temp);
        return;
    }
    while((X < self->len) && (Y < other->len)) {
        int track1 = self->elements[X];
        int track2 = other->elements[Y];
        if (self->elements[X] > other->elements[Y]) {
                temp[Z] = other->elements[Y];
                Y++;
                Z++;
            }
        else if (self->elements[X] == other->elements[Y]) {
                temp[Z] = self->elements[X];
                X++;
                Y++;
                Z++;
            }
        else if (self->elements[X] < other->elements[Y]) {
                temp[Z] = self->elements[X];
                X++;
                Z++;
            }
        }
    while(X < self->len){
        temp[Z] = self->elements[X];
        X++;
        Z++;
    }
    while(Y < other->len){
        temp[Z] = other->elements[Y];
        Y++;
        Z++;
    }
    for(int i = 0; i < Z; i++){
        self->elements[i] = temp[i];
    }
    self->len = Z;
    free(temp);
}
