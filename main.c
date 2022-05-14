#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Hist.h"

static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return !strcmp(str_elem_1, str_elem_2);
}


static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem)+1);//check
    strcpy(p, str_elem);
    return p;
}
int main() {

    Hist hist = HistCreate(clone_str, free, cmp_str);
    char word[] = "b1";
    char word2[] = "b2";
    char word3[] = "b3";
    HistInc(hist, word);
//    HistInc(hist, word2);
//    HistInc(hist, word3);
    printf("Size of hist %d \n", HistSize(hist));
    Element *p = HistGetElement(hist, 0);
//    Element *p1 = HistGetElement(hist, 2);
    printf("Address of point %p\n", p);
//    printf("What Saar want %s\n", word);
    printf("What Saar get %s\n", *p);
//    printf("What Saar get %s ", *p1);


//    if(cmp_str(word, word2)) printf("hey");
//    else printf("Sad");

//

//    printf("%d", HistGetCount(hist, word));

    return 0;
}
