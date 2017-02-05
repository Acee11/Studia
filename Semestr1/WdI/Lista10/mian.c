#include <stdio.h>
struct elem
{
    int val;
    struct elem *next;
};
struct elem *utworz(int v)
{
    struct elem *el = malloc(sizeof(struct elem));
    el->val = v;
    el->next = NULL;
    return el;
}
struct ll
{
    struct elem *first;
    struct elem *last;
    int size;
};
void wypiszDod(struct ll *llist) //zad 1
{
    struct elem *el = llist->first;
    if(!el) return;
    for(; el; el = el->next)
        if(el->val > 0) printf("%d ",el->val);
    printf("\n");
}

void dodaj(struct ll *llist, int v) // zad2
{
    struct elem *el = utworz(v);
    if (llist->last == NULL)
    {
        llist -> first = llist -> last = el;
        llist->size = 1;
    }
    else
    {
        llist->last->next = el;
        llist->last = el;
        llist->size++;
    }

}

void usun(struct ll *llist) // zad 3
{
    struct elem *el = llist->first;
    if(!el) return;
    else if(!el->next)
    {
        llist->first = llist->last = NULL;
        free(el);
        return;
    }
    while(el->next->next) el = el->next;
    {
        llist->last = el;
        free(el->next);
        el->next = NULL;
    }
}

void polacz(struct ll *llist1, struct ll *llist2) //zad 4
{
    if(!llist1->last)
    {
        llist1->first = llist1->last = llist2->first;
    }
    else
    {
        llist1->last->next = llist2->first;
        llist1->last = llist2->last;

    }

}

void usunv(struct ll *llist ,int v) //zad 5
{
    struct elem *el = llist->first, *eltmp;
    if(!el) return;

    while(el->val == v)
    {
        eltmp = el;
        llist->first = el->next;
        el = el->next;
        free(eltmp);
        if(!llist->first)
        {
            llist->last = NULL;
            return;
        }
    }
    if(!el->next)
        return;
    while(el->next->next)
    {
        if (el->next->val == v)
        {
            eltmp = el->next;
            el->next = eltmp->next;
            free(eltmp);
        }
        el = el->next;
    }
    if(el->next == v)
    {
        llist->last = el;
        free(el->next);
        el->next = NULL;
    }
}

void wypiszrev(struct ll *llist) //zad 6
{
    struct elem *el = llist->first;
    if(!el) return;

    int i,c = llist->size,tab[c];

    for(i = 0; i < c && el; i++)
    {
        tab[i] = el->val;
        el = el->next;
    }
    for(i = c - 1; i >= 0; i--) printf("%d ",tab[i]);
    printf("\n");
}

void odwroc(struct ll *llist) //zad 7
{
    struct elem *el = llist->first;
    if(!el) return;

    int i, c = llist->size, tab[c];

    for(i = 0; i < c && el; i++)
    {
        tab[i] = el->val;
        el = el->next;
    }
    el = llist->first;
    for(i = c - 1; i >= 0 && el; i--)
    {
        el->val = tab[i];
        el = el->next;
    }
}

void rozdziel(struct ll *llist, struct ll *lpos, struct ll *lneg)
{
    lpos->first = lpos->last = lneg->first = lneg->last = NULL;
    struct elem *el = llist->first;

    while(el)
    {
        if (el->val > 0) dodaj(lpos, el->val);
        else if (el->val < 0) dodaj(lneg, el->val);
        el = el->next;
    }
}


void wyp(struct elem *elem)
{
    if(!elem->next)
    {
        printf("%d",elem->val);
        return;
    }

    wyp(elem->next);
    printf("%d",elem->val);
}

int *tab(struct elem *el, )

void odwroc(struct elem * el)
{

}



struct dll
{
    struct delem *first;
    struct delem *last;
    int size;
};

struct delem
{
    struct delem *next;
    struct delem *prev;
    int val;
};

void dlldodaj(struct dll *dllist, int v)
{
    struct delem *el = malloc(sizeof(struct delem));
    el->val = v;
    if (dllist->last == NULL)
    {
        dllist->first = dllist->last = el;
        el->prev = el->next = NULL;
    }
    else if (dllist->first == dllist->last)
    {
        dllist->last = el;
        dllist->first->next = el;
        el->prev = dllist->first;
        el->next = NULL;
    }
    else
    {
        el->prev = dllist->last;
        dllist->last->next = el;
        dllist->last = el;
        el->next = NULL;
    }
}

void dllusun(struct dll *dllist)
{
    struct delem *el = dllist->first;
    if(!el) return;
    else if (dllist->first = dllist->last)
    {
        free(el);
        dllist->first = dllist->last = NULL;
    }
    else
    {
        dllist->first = el->next;
        dllist->first->prev = NULL;
        free(el);
    }
}


int main()
{
    struct dll dllist;
    dllist.first = dllist.last = NULL;
    dlldodaj(&dllist, 100);
    int i;
    for(i = -10; i < 10; i++)
    {
        dlldodaj(&dllist,i);
    }

    struct delem *el = dllist.first;

    while(el)
    {
        printf("%d ",el->val);
        el = el->next;
    }
    printf("\n");

    el = dllist.last;

    while(el)
    {
        printf("%d ",el->val);
        el = el->prev;
    }

    return 0;
}
