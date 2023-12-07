//
// Created by louis on 12/7/23.
//

#ifndef TP1SYSRES_EXO3_H
#define TP1SYSRES_EXO3_H

#endif //TP1SYSRES_EXO3_H

typedef struct chainedlist{ //First chained list version
    int value;
    struct chainedlist *next;
} chainedlist;

typedef struct chainedlistdouble{ //doubled chained list version (the others function use it as circular chained list)
    int value;
    struct chainedlistdouble * next;
    struct chainedlistdouble * previous;
} chainedlistdouble;

int length(chainedlist *start);
int lengthdouble(chainedlistdouble *start);
void printList(chainedlist *start);
void printListdouble(chainedlistdouble *start);
chainedlist* removeFirst(chainedlist *start);
chainedlistdouble* removeFirstdouble(chainedlistdouble *start);
void removeLast(chainedlist *start);
void removeLastdouble(chainedlistdouble *start);
chainedlist* AddFirst(chainedlist* start, int value);
chainedlistdouble* AddFirstdouble(chainedlistdouble* start, int value);
void AddLast(chainedlist* start, int value);
void AddLastdouble(chainedlistdouble* start, int value);
chainedlist* NfirstInt(int n);
chainedlistdouble* NfirstIntdouble(int n);
void concatene2(chainedlist* start1, chainedlist* start2);
void concatene2double(chainedlistdouble * start1, chainedlistdouble* start2);
chainedlist* functionOnElem(chainedlist* start, int (*func)());
chainedlistdouble* functionOnElemdouble(chainedlistdouble* start, int (*func)());
int square(int a);
void exo3();