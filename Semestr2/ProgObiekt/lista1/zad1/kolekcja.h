#ifndef KOLEKCJA_H
#define KOLEKCJA_H
#include <stdbool.h>


#define ZBIOR 0
#define TORBA 1

typedef int Elem;

struct Kolekcja
{
    Elem *el;
    unsigned int size,mem;
    bool type;
};
void zbior(struct Kolekcja *k);
void torba(struct Kolekcja *k);
void wstaw(struct Kolekcja *k,Elem e);
int rozmiar(struct Kolekcja *k);
int szukaj(struct Kolekcja *k,Elem e);

#endif
