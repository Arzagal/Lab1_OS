//
// Created by louis on 12/6/23.
//
#include <stdio.h>
#include <malloc.h>
#include "exo3.h"



int length(chainedlist *start){ // Question 2 :
    chainedlist *act = start;
    int res = 1;
    if(start == NULL){ // We simply run through the entire list and count the iteration
        return 0;
    }
    while(act->next != NULL){
        res++;
        act = act->next;
    }
    return res;
}

int lengthdouble(chainedlistdouble *start){ // Question 2, double chained list version
    // Note : we dont use the circular and double chained characteristics, the function is essentially the same as before
    if(start == NULL){
        return 0;
    }
    chainedlistdouble *act = start;
    int res = 1;
    while(act->next != start){ //Because the list is circular, we never reach the NULL pointer, but we reach the start again
        res++;
        act = act->next;
    }
    return res;
}

void printList(chainedlist *start){ // question 3
    chainedlist *act = start;
    printf("This is the content of the list, with format <pointer value> value  \n");
    while(act != NULL){ // We simply run through the list and print each element,t
        printf(" <%p> %d \n", act, act->value);
        act = act->next;
    }
}

void printListdouble(chainedlistdouble *start){ // question 3
    chainedlistdouble *act = start;
    printf("This is the content of the list, with format <pointer value> value  \n");
    printf(" <%p> %d \n", act, act->value); //We print the first value
    act = act->next;
    while(act - start != 0){ // We adapt the condition here for a circular list
        printf(" <%p> %d \n", act, act->value);
        act = act->next;
    }
}

chainedlist* removeFirst(chainedlist *start){
    if(start == NULL || start->next == NULL){ //We check that there is at list 2 element in the list
        return start;
    }
    chainedlist* res = start->next; //We return the second element as the new start of the list
    free(start); //We free the deleted element
    // Note : we choosed to return a new start pointer, but we could have done it in place and change the given start pointer
    return res;
}

chainedlistdouble* removeFirstdouble(chainedlistdouble *start){ //Works the same as for the simple chained list
    if(start == NULL || start->next == start){
        return start;
    }
    chainedlistdouble* res = start->next;
    res->previous = start->previous;
    free(start);
    return res;
}

void removeLast(chainedlist *start){
    if(start == NULL || start->next == NULL){
        return ;
    }
    chainedlist* inter1 = start; // I choosed to stock 2 element, just for clarity
    chainedlist* inter2 = start->next;
    while(inter2->next != NULL){ // We go through the whole list to reach the last element
        inter1 = inter1->next;
        inter2 = inter2->next;;
    }
    inter1->next = NULL; // We erase the last element
    free(inter2); // We free the deleted element
}

void removeLastdouble(chainedlistdouble *start){ //here we can take advantage of the circular cracteristic
    if(start == NULL || start->next == start){
        return ;
    }
    chainedlistdouble *inter = start->previous; // We take the last element of the list
    start->previous->previous->next = start; // We remove the last element : the before last element point to the start now
    start->previous = start->previous->previous; // the start point to the before last element
    free(inter); // As before
}

chainedlist* AddFirst(chainedlist* start, int value){ // Same thing as for the remove first : we return the new start,
    // but we could have changed the start in place
    // Note2 : We take as argument the value we want to have, but we could take the new node :
    // this would allow more modality of this code
    chainedlist* temp = malloc(sizeof(chainedlist)); //We create a new element
    temp->value = value; // we assign the wanted value
    temp->next = start; // We but the new node at the beginning of the list
    return temp;
}

chainedlistdouble* AddFirstdouble(chainedlistdouble* start, int value){ // Works the same way, but they are more pointers to change
    chainedlistdouble* temp = malloc(sizeof(chainedlistdouble));
    temp->value = value;
    temp->next = start;
    start->previous->next = temp; // We take care that the list remind circular
    temp->previous = start->previous;
    start->previous = temp;
    return temp;
}

void AddLast(chainedlist* start, int value){
    chainedlist* temp = malloc(sizeof(chainedlist));
    temp->value = value;
    temp->next = NULL;
    chainedlist* act = start;
    while(act->next != NULL){ //as for the remove, we go to the end
        act = act->next;
    }
    act->next = temp;
}

void AddLastdouble(chainedlistdouble* start, int value){
    chainedlistdouble* temp = malloc(sizeof(chainedlistdouble));
    temp->value = value;
    temp->next = start;
    start->previous->next = temp;
    start->previous = temp;
}

chainedlist* NfirstInt(int n){ //Question 1, creation of a list containing the n first natural int
    struct chainedlist *start = malloc(sizeof(chainedlist)); // we create the first element
    // note : its a choice, the list we return is never empty
    start->value = 0;
    start->next = NULL;
    struct chainedlist *act = start; // We create a pointer to go through the list ( we need to keep the start)
    for(int i =0; i<n; i++){ // we iterate with the value we want
        chainedlist *inter = malloc(sizeof(chainedlist));
        inter->value = i + 1;
        inter->next = NULL;
        act->next = inter; // We create a new element and put it at the end
        act = inter;
    }
    return start;
}

chainedlistdouble* NfirstIntdouble(int n){ // it works the same way, but again there are just a few more pointers to assign
    struct chainedlistdouble *start = malloc(sizeof(chainedlistdouble));
    start->value = 0;
    start->next = start;
    start->previous = start;
    struct chainedlistdouble *act = start;
    for(int i =0; i<n; i++){
        chainedlistdouble *inter = malloc(sizeof(chainedlistdouble));
        inter->value = i + 1;
        inter->next = start;
        inter->previous = act;
        act->next = inter;
        act = inter;
    }
    start->previous = act;
    return start;
}

void concatene2(chainedlist* start1, chainedlist* start2){ // We put the list beginning with start2 at the end of the list starting with start 1
    chainedlist* temp = start1;
    while(temp->next != NULL){ // We need to go to the end of the first list
        temp = temp->next;
    }
    temp->next = start2; // we put the second list at the end of the first one
}

void concatene2double(chainedlistdouble * start1, chainedlistdouble* start2){ // There are 4 connections to make in this case
    chainedlistdouble* temp = start1->previous; // we store the end of the first list, since we are gonna change this pointer at some point
    start1->previous->next = start2; // we connect the start of the first list to the end of the second one
    start2->previous->next = start1; // We connect the start of the second list to the end of the first one
    start1->previous = start2->previous; // We connect the end of the first list to the start of the second one
    start2->previous = temp; // We connect the end of the second list to the start of the first one

}


chainedlist* functionOnElem(chainedlist* start, int (*func)()){ // We want to create a new list containing the value of
    // a given list after we applied the given function to them
    // This function works the same way as Nfirstint, the only change is the value we store and the length of the created list
    chainedlist *start2 = malloc(sizeof(chainedlist)); // We create a new list
    if(start != NULL){
        start2->value = func(start->value);
        start2->next = NULL;
    }
    chainedlist *temp = start;
    chainedlist *temp2 = start2;
    while(temp->next != NULL){ // We go through the entire list
        temp = temp->next;
        chainedlist *inter = malloc(sizeof(chainedlist));
        inter->value = func(temp->value); // we calculate the new value with the function in parameter
        inter->next = NULL;
        temp2->next = inter;
        temp2 = inter;
    }
    return start2;
}

chainedlistdouble* functionOnElemdouble(chainedlistdouble* start, int (*func)()){
    // As for Nfirstintdouble, This function works the same way, with simply more connections to make
    chainedlistdouble *start2 = malloc(sizeof(chainedlistdouble));
    if(start != NULL){
        start2->value = func(start->value);
        start2->next = start2;
        start2->previous = start2;
    }
    chainedlistdouble *temp = start;
    chainedlistdouble *temp2 = start2;
    while(temp->next - start != 0){ // We change the condition since the list is circular
        temp = temp->next;
        chainedlistdouble *inter = malloc(sizeof(chainedlistdouble));
        inter->value = func(temp->value);
        inter->next = start2;
        temp2->next = inter;
        inter->previous = temp2;
        temp2 = inter;
    }
    start2->previous = temp2;
    return start2;
}

int square(int a){ // Simple function for test
    return a*a;
}

void exo3(){
    // this function simply apply all the function we created to show the results
    int n = 10;
    // Question 1
    printf("test of question 1 \n");
    chainedlist *start = NfirstInt(n);

    // Question 2
    printf("test of question 2 \n");
    int res = length(start);
    printf("length de la liste %d\n", res);

    // Question 3
    printf("test of question 3 \n");
    printList(start);

    // Question 4 et 5
    printf("test of question 4 and 5 \n");
    start = removeFirst(start);
    removeLast(start);
    printList(start);

    // Question 6 et 7
    printf("test of question 6 and 7 \n");
    AddLast(start, 12);
    start = AddFirst(start, 13);
    printList(start);

    //Question 8
    printf("test of question 8 \n");
    chainedlist *debut2 = NfirstInt(3);
    concatene2(start, debut2);
    printList(start);

    //Question 9
    printf("test of question 9 \n");
    chainedlist *newdebut = functionOnElem(start, square);
    printList(newdebut);

    //Question 10 et 11 : we use the same
    printf("test of question 1 double chained circular version \n");
    int ndouble = 10;
    chainedlistdouble *debutdouble = NfirstIntdouble(ndouble);
    printf("test of question 2 double chained circular version \n");
    int resdouble = lengthdouble(debutdouble);
    printf("length de la liste %d\n", resdouble);
    printf("test of question 3 double chained circular version \n");
    printListdouble(debutdouble);
    printf("test of question 4 and 5 double chained circular version \n");
    debutdouble = removeFirstdouble(debutdouble);
    removeLastdouble(debutdouble);
    printListdouble(debutdouble);
    printf("test of question 6 and 7 double chained circular version \n");
    AddLastdouble(debutdouble, 12);
    debutdouble = AddFirstdouble(debutdouble, 13);
    printListdouble(debutdouble);
    printf("test of question 8 double chained circular version \n");
    chainedlistdouble *debut2double = NfirstIntdouble(3);
    concatene2double(debutdouble, debut2double);
    printListdouble(debutdouble);
    printf("test of question 9 double chained circular version \n");
    chainedlistdouble *newdebutdouble = functionOnElemdouble(debutdouble, square);
    printListdouble(newdebutdouble);
}
