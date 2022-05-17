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

static bool cmp_int(Element int_elem_1, Element int_elem_2) {
    return *((int*)int_elem_1) == *((int*)int_elem_2);
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
    Hist hist = HistCreate(clone_int, free, cmp_int);
    for(int i=1; i<n; i++) {


        assert(HistSize(hist) == i-1);

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
static bool test_str_at_index(Hist hist, int index, const char *ref) {
//    char *cur = HistGetElement(hist, index);
//    if (!cur || strcmp(cur,ref) != 0) return false;
//    free(cur);
    printf("coo");
    return true;
}

static void test_str_hist() {
    Hist hist = HistCreate(clone_str, free, cmp_str);
    assert(HistSize(hist) == 0);
    char * a = "abc";
    HistInc(hist, a); // abc
//    HistInc(hist,"d");   // d abc
//    HistInc(hist,"ef");  // d ef abc
//    HistInc(hist,"ghi"); // d ef abc ghi
//    assert(HistSize(hist) == 4);
//    assert( test_str_at_index(hist, 0, "d") ); // ef abc ghi
//    assert( test_str_at_index(hist, 1, "abc") ); // ef ghi
//    assert( test_str_at_index(hist, 2, "ghi") ); // ef
//    assert( test_str_at_index(hist, 3, "ef") );
    HistDestroy(hist);
}
void test_hist(){
//    test_int_hist(3);
    test_str_hist();

}



