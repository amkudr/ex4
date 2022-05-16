#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Hist.h"
#include "LinkedList.h"


static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return (bool)!strcmp(str_elem_1, str_elem_2);
}


static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem)+1);//check
    strcpy(p, str_elem);
    return p;
}
int main(int argc, char **argv) {
//    Hist hist = HistCreate(clone_str, free, cmp_str);
//    char word[] = "b1";
//    char word2[] = "b2";
//    char word3[] = "b3";
//    HistInc(hist, word);
//    HistInc(hist, word2);
//    HistInc(hist, word3);
//    HistInc(hist, word);
//    HistInc(hist, word2);
//    HistInc(hist, word3);
//
//
//    Element  p = HistGetElement(hist, 0);
//    Element p1 = HistGetElement(hist, 1);
//    Element p2=HistGetElement(hist, 2);
//     printf("Address of point %p\n", p);
//
//    printf("What Saar want %s\n", word);
//    printf("What Saar get %s\n", p);
//    printf("What Saar get %s\n", p1);
//    printf("What Saar get %s \n", p2);
//    printf("Size of hist %d \n", HistSize(hist));
//
//    printf("count of b1>%d\n",HistGetCount(hist,p));
//    printf("count of b2>%d\n",HistGetCount(hist,p1));
//    printf("count of b3>%d\n",HistGetCount(hist,p2));
    if(argc > 3){
        fprintf(stderr, "\nUsage: %s <file-path>\n", argv[0]);
        return 1;
    }
    Hist hist = HistCreate(clone_str, free, cmp_str);
    char out[] = "out.txt";
    char *path2 = NULL;
    char *path1 = NULL;
    int flag_argc = 0;
    int flagIsOut = 1; //1=true   0=false
    char *file1name = "";
    char *file2name = "";

    if (argc == 2) {
        char *path1 = argv[1];
        int flag_argc = 2;
    }
    if (argc == 3) {
        path1 = argv[1];
        path2 = argv[2];
        int size = strlen(path1);
        for (int i = size - 2; i > size - 9; i = i - 1) //example:  yesterday_out.txt   <<size-2 is index of the last "t"  size-8 is the index of the letter "o"
        {
            if (out[i] != path1[i]) {
                flagIsOut = 0;
            }
        }
        int i = size - 2;
        while (path1[i] != '/') {
            strcat(file1name, path1[i]);
            i = i - 1;
        }
        int j = strlen(path2) - 2;
        while (path2[i] != '/') {
            strcat(file2name, path2[i]);
            j = j - 1;
        }
        if (flagIsOut == 0) {
            //path2 is the out.txt file  output
        }
        if (flagIsOut == 1) {
            //path1 is the out.txt file  output
        }

    }
    if (flag_argc == 2) {
        char *filename = "";
        path1 = argv[1];
        int size = strlen(argv[1]);
        for (int i = size - 2; i > size - 9; i = i -
                                                 1) //example:  yesterday_out.txt   <<size-2 is index of the last "t"  size-8 is the index of the letter "o"
        {
            if (out[i] != path1[i]) {
                flagIsOut = 0;
            }
        }
        int i = size - 2;
        while (path1[i] != '/') {
            strcat(filename, path1[i]);
            i = i - 1;
        }


        if (flagIsOut == 0) {
            //path1 is the input file
        }
        if (flagIsOut == 1) {
            //path1 is the out.txt file  output
        }

    }


    return 0;
}
