#include "Hist.h"
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "string.h"
// #include "LinkedList.c"

#include "Set.h"
static Element clone_int(Element int_elem) {
    if (!int_elem) return NULL;
    int *p = malloc(sizeof(int));//check
    *p = *((int*)int_elem);
    return p;
}
//static bool cmp_str(Element str_elem_1, Element str_elem_2) {
//    return !strcmp(str_elem_1, str_elem_2);
//}

//static Element clone_str(Element str_elem) {
//    if (!str_elem) return NULL;
//    char *p = malloc(strlen(str_elem)+1);//check
//    strcpy(p, str_elem);
//    return p;
//}


struct Hist{
//    int count; ///Was  int * count; //useless
    void (*free_func)(Element);
    Element (*clone_func)(Element);
    LinkedList listElement;
    LinkedList listCount;
    bool(*cmp_func)(Element, Element);
};

Hist HistCreate(Element (*clone_func)(Element),void (*free_func)(Element),
                                               bool (*cmp_func)(Element, Element))
{
    Hist hist = calloc(sizeof(struct Hist), 1);
    if(!hist) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(struct Hist),1);
        exit(-1);
    }

    hist->listElement = LLCreate(clone_func,free_func);

    if(!hist->listElement) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(LinkedList));
        exit(-1);
    }

    hist->listCount = LLCreate(clone_int,free); //clone_func mybe
    if(!hist->listCount) {
        fprintf(stderr, "%s/%u: failed to allocate %lu bytes\n\n",
                __FILE__, __LINE__, sizeof(LinkedList));
        exit(-1);
    }
    hist->clone_func = clone_func;
    hist->free_func = free_func;
    hist->cmp_func = cmp_func;
//    hist->count=0; //useless
    //hist->listCount=listCount;


    return hist;
}

void HistDestroy(Hist hist)
{
    free(hist->listElement);
    free(hist->listCount);
    free(hist);
}

unsigned int HistSize(Hist hist)
{
    return LLSize(hist->listElement);
}
// Get the count of element e. If e is not in hist, returns 0.
int HistGetCount(Hist hist, Element *e)// לבדוק עם מישהו אם זה עובד!!!!
{
//    int count=0;
    Element cnt;
    unsigned int length = LLSize(hist->listCount) ;

    for (int i = 0; i < length; i++) {

       Element *e2=HistGetElement(hist, i); //pointer
//        printf(" %s ", *e);
//        printf(" %s ", *e2);

//
//        if (hist->cmp_func(*e, *e2)){
//            printf(" %s ", *e);
//            printf(" %s ", *e2);
//
//
//            printf(" kek ");
//        } else {
//            printf(" %s ", *e);
//            printf(" %s ", *e2);
//            printf("mek");
//        }

        if (hist->cmp_func(*e2, *e)) {
            printf("Inside");
            printf(" %s ", *e);
            printf(" %s ", *e2);
            cnt = LLRemove(hist->listCount, i); //hist->clone_func
            LLAdd(hist->listCount, i, &cnt);

            return &cnt;//replace//
        }
    }
    return 0;
}


// Increment the count of e by one.
// If e is not in hist, create a new entry with a clone of e and a count of 1.
void HistInc(Hist hist, Element e) {
    //printf("hii");

    if (HistGetCount(hist, &e) == 0) // If e is not in hist, create a new entry with a clone of e and a count of 1.
    {
//        printf("hii");
        unsigned int e3 = 1;
        //Element e3=1;
        unsigned int length = LLSize(hist->listElement);
        unsigned int length2 = LLSize(hist->listCount);
        Element e2 = hist->clone_func(e);
        if (length == 0) {
            LLAdd(hist->listElement, 0, &e2);
            LLAdd(hist->listCount, 0,&e3 );
//            printf("gggggg");
        } else {
            LLAdd(hist->listElement, length, &e2);
            LLAdd(hist->listCount, length2, &e3);
//            printf("ttttt");
        }
    }

}


// Gets (a clone of) the element at given index.
// If index<0 or index >= HistSize(hist) then NULL is returned.
    Element HistGetElement(Hist hist, unsigned int index) {
//        int i=index;
        if (index < 0 || index >= LLSize(hist->listElement))
            return NULL;
        Element e2 = LLRemove(hist->listElement, index);
        //Element e = malloc(sizeof(e2));

//        printf(" %s ", * e2);

        Element e = hist->clone_func(e2);
        // Element e =LLRemove(hist->listElement,index);
        LLAdd(hist->listElement, index, e2);
//        printf("\n %s \n", e);
//        hist->free_func(e2);
        return e;
    }
//    int i=0;
//    Node nodeE,nodeC;
//    nodeC=LLRemove(hist->listCount,0);
//    LLAdd(hist->listCount,0,nodeC);
//    nodeE=LLRemove(hist->listElement,0);
//    LLAdd(hist->listElement,0,nodeE);
//
//    while(nodeE)
//    {
//        if(i==index)
//             {return nodeE;}
//        i++;
//        nodeE= nodeE->next;
//        nodeC=nodeC->next;
//    }
//    return NULL; //if



