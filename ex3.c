//
// Created by louis on 12/6/23.
//
#include <stdio.h>
#include <malloc.h>

typedef struct chainedlist{
    int value;
    struct chainedlist *next;
} chainedlist;

typedef struct chainedlistdouble{
    int value;
    struct chainedlistdouble * next;
    struct chainedlistdouble * previous;
} chainedlistdouble;

int length(chainedlist *start){ // Question 2
    chainedlist *act = start;
    int res = 1;
    if(start == NULL){
        return 0;
    }
    while(act->next != NULL){
        res++;
        act = act->next;
    }
    return res;
}

int lengthdouble(chainedlistdouble *start){ // Question 2
    if(start == NULL){
        return 0;
    }
    chainedlistdouble *act = start;
    int res = 1;
    while(act->next != start){
        res++;
        act = act->next;
    }
    return res;
}

void printList(chainedlist *start){ // question 3
    chainedlist *act = start;
    printf("This is the content of the list, with format <pointer value> value  \n");
    while(act != NULL){
        printf(" <%p> %d \n", act, act->value);
        act = act->next;
    }
}

void printListdouble(chainedlistdouble *start){ // question 3
    chainedlistdouble *act = start;
    printf("This is the content of the list, with format <pointer value> value  \n");
    printf(" <%p> %d \n", act, act->value);
    act = act->next;
    while(act - start != 0){
        printf(" <%p> %d \n", act, act->value);
        act = act->next;
    }
}

chainedlist* removeFirst(chainedlist *start){
    if(start == NULL || start->next == NULL){
        return start;
    }
    chainedlist* res = start->next;
    free(start);
    return res;
}

chainedlistdouble* removeFirstdouble(chainedlistdouble *start){
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
    chainedlist* inter1 = start;
    chainedlist* inter2 = start->next;
    while(inter2->next != NULL){
        inter1 = inter1->next;
        inter2 = inter2->next;;
    }
    inter1->next = NULL;
    free(inter2);
}

void removeLastdouble(chainedlistdouble *start){
    if(start == NULL || start->next == start){
        return ;
    }
    chainedlistdouble *inter = start->previous;
    start->previous->previous->next = start;
    start->previous = start->previous->previous;
    free(inter);
}

chainedlist* AddFirst(chainedlist* start, int value){
    chainedlist* temp = malloc(sizeof(chainedlist));
    temp->value = value;
    temp->next = start;
    return temp;
}

chainedlistdouble* AddFirstdouble(chainedlistdouble* start, int value){
    chainedlistdouble* temp = malloc(sizeof(chainedlistdouble));
    temp->value = value;
    temp->next = start;
    start->previous->next = temp;
    temp->previous = start->previous;
    start->previous = temp;
    return temp;
}

void AddLast(chainedlist* start, int value){
    chainedlist* temp = malloc(sizeof(chainedlist));
    temp->value = value;
    temp->next = NULL;
    chainedlist* act = start;
    while(act->next != NULL){
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

chainedlist* NfirstInt(int n){
    struct chainedlist *start = malloc(sizeof(chainedlist));
    start->value = 0;
    start->next = NULL;
    struct chainedlist *act = start;
    for(int i =0; i<n; i++){ // On cree une liste contenant les n premeirs entiers naturels
        chainedlist *inter = malloc(sizeof(chainedlist));
        inter->value = i + 1;
        inter->next = NULL;
        act->next = inter;
        act = inter;
    }
    return start;
}

chainedlistdouble* NfirstIntdouble(int n){
    struct chainedlistdouble *start = malloc(sizeof(chainedlistdouble));
    start->value = 0;
    start->next = start;
    start->previous = start;
    struct chainedlistdouble *act = start;
    for(int i =0; i<n; i++){ // On cree une liste contenant les n premeirs entiers naturels
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

void concatene2(chainedlist* start1, chainedlist* start2){
    chainedlist* temp = start1;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = start2;
}

void concatene2double(chainedlistdouble * start1, chainedlistdouble* start2){
    chainedlistdouble* temp = start1->previous;
    start1->previous->next = start2;
    start2->previous->next = start1;
    start1->previous = start2->previous;
    start2->previous = temp;

}


chainedlist* functionOnElem(chainedlist* start, int (*func)()){
    chainedlist *start2 = malloc(sizeof(chainedlist));
    if(start != NULL){
        start2->value = func(start->value);
        start2->next = NULL;
    }
    chainedlist *temp = start;
    chainedlist *temp2 = start2;
    while(temp->next != NULL){
        temp = temp->next;
        chainedlist *inter = malloc(sizeof(chainedlist));
        inter->value = func(temp->value);
        inter->next = NULL;
        temp2->next = inter;
        temp2 = inter;
    }
    return start2;
}

chainedlistdouble* functionOnElemdouble(chainedlistdouble* start, int (*func)()){
    chainedlistdouble *start2 = malloc(sizeof(chainedlistdouble));
    if(start != NULL){
        start2->value = func(start->value);
        start2->next = start2;
        start2->previous = start2;
    }
    chainedlistdouble *temp = start;
    chainedlistdouble *temp2 = start2;
    while(temp->next - start != 0){
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

int square(int a){
    return a*a;
}

int exo3(){
    int n = 10;
    chainedlist *start = NfirstInt(n);
    int res = length(start);
    printf("length de la liste %d\n", res);
    printList(start);
    start = removeFirst(start);
    removeLast(start);
    printList(start);
    AddLast(start, 12);
    start = AddFirst(start, 13);
    printList(start);
    chainedlist *debut2 = NfirstInt(3);
    concatene2(start, debut2);
    printList(start);
    chainedlist *newdebut = functionOnElem(start, square);
    printList(newdebut);

    //Question 10 et 11
    int ndouble = 10;
    chainedlistdouble *debutdouble = NfirstIntdouble(ndouble);
    int resdouble = lengthdouble(debutdouble);
    printf("length de la liste %d\n", resdouble);
    printListdouble(debutdouble);
    debutdouble = removeFirstdouble(debutdouble);
    removeLastdouble(debutdouble);
    printListdouble(debutdouble);
    AddLastdouble(debutdouble, 12);
    debutdouble = AddFirstdouble(debutdouble, 13);
    printListdouble(debutdouble);
    chainedlistdouble *debut2double = NfirstIntdouble(3);
    concatene2double(debutdouble, debut2double);
    printListdouble(debutdouble);
    chainedlistdouble *newdebutdouble = functionOnElemdouble(debutdouble, square);
    printListdouble(newdebutdouble);
}
