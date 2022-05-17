#include "Hist.h"
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


#include "Set.h"

static Element clone_int(Element int_elem) {
    if (!int_elem) return NULL;
    int *p = malloc(sizeof(int));//check
    *p = *((int *) int_elem);
    return p;
}


struct Hist {
    void (*free_func)(Element);

    Element (*clone_func)(Element);

    LinkedList listElement;
    LinkedList listCount;

    bool (*cmp_func)(Element, Element);
};

Hist HistCreate(Element (*clone_func)(Element), void (*free_func)(Element),
                bool (*cmp_func)(Element, Element)) {
    Hist hist = calloc(sizeof(struct Hist), 1);
    if (!hist) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist));
        exit(-1);
    }

    hist->listElement = LLCreate(clone_func, free_func);

    if (!hist->listElement) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(LinkedList));
        exit(-1);
    }

    hist->listCount = LLCreate(clone_int, free);
    if (!hist->listCount) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(LinkedList));
        exit(-1);
    }
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
    return hist;
}

void HistDestroy(Hist hist) {
    LLDestroy(hist->listElement);
    LLDestroy(hist->listCount);
    free(hist);
}

unsigned int HistSize(Hist hist) {
    return LLSize(hist->listElement);
}

// Get the count of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element e)
{

    if (LLSize(hist->listElement) == 0) {
        return 0;
    }

    unsigned int length = LLSize(hist->listCount);
    for (int i = 0; i < length; i++) {
        if (hist->cmp_func(HistGetElement(hist, i), e)) {

            int *cnt = LLRemove(hist->listCount, i);
            int *cloneCnt = clone_int(cnt);
            LLAdd(hist->listCount, i, cnt);

            return *cloneCnt;
        }
    }
    return 0;
}

// Increment the count of e by one.
// If e is not in hist, create a new entry with a clone of e and a count of 1.
void HistInc(Hist hist, Element e) {

    if (HistGetCount(hist, e) == 0) // If e is not in hist, create a new entry with a clone of e and a count of 1.
    {
        unsigned int e3 = 1;
        unsigned int length = LLSize(hist->listElement);
        unsigned int length2 = LLSize(hist->listCount);
        Element *e2 = hist->clone_func(e);
        LLAdd(hist->listElement, length, e2);
        LLAdd(hist->listCount, length2, &e3);

    } else { // Increment the count of e by one.

        unsigned int length2 = LLSize(hist->listCount);

        for (unsigned int i = 0; i < length2; i++) {
            if (hist->cmp_func(HistGetElement(hist, i), e)) {

                int count = HistGetCount(hist, e) + 1;
                LLAdd(hist->listCount, i, &count);
            }
        }
    }
}


// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.

Element HistGetElement(Hist hist, unsigned int index) {
    if (index < 0 || index >= LLSize(hist->listElement)) {
        return NULL;
    }
    Element e2 = LLRemove(hist->listElement, index);
    Element e = hist->clone_func(e2);
    LLAdd(hist->listElement, index, e2);
    return e;
}
