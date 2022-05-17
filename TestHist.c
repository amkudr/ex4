#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "TestHist.h"
#include "Hist.h"
#include <stdio.h>
#include <stdlib.h>

static Element clone_int(Element int_elem) {
    if (!int_elem) return NULL;
    int *p = malloc(sizeof(int));//check
    *p = *((int*)int_elem);
    return p;
}
static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return (bool) !strcmp(str_elem_1, str_elem_2);
}

static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem) + 1);//check
    strcpy(p, str_elem);
    return p;
}

static void test_int_hist(int n) {
    Hist hist = HistCreate(clone_int, free, cmp_str);
    for(int i=1; i<n; i++) {
        printf("hh");

        assert(HistSize(hist) == i-1);
        printf("hh");
        HistInc(hist, i);
//        for(int j=i+1; j<n; j++){
//            HistInc(hist, j);
//        }
    }
    for(int i=0; i<n; i++) {
        int *p = HistGetElement(hist,i);
        int c = HistGetCount(hist,p);
        assert(p && *p == i);
        assert(c == i);
        free(p);
    }
    HistDestroy(hist);
    assert(HistSize(hist) == 0);

}
void test_hist(){
    test_int_hist(3);
}



