#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "Hist.h"
#include "LinkedList.h"
#include "TestHist.h"



static bool cmp_str(Element str_elem_1, Element str_elem_2) {
    return (bool) !strcmp(str_elem_1, str_elem_2);
}

static Element clone_str(Element str_elem) {
    if (!str_elem) return NULL;
    char *p = malloc(strlen(str_elem) + 1);//check
    strcpy(p, str_elem);
    return p;
}


//function get input from file and fill Hist and list
static void in(Hist hist, LinkedList list, char *path1) {
    char *buf = NULL;
    size_t bufsize = 0;
    FILE *file = fopen(path1, "r");
    if (file == NULL) {
        exit(1);
    }
    int i = 0;
    while (getline(&buf, &bufsize, file) != EOF) {
        unsigned long size = strlen(buf);
        char *line = buf;
        line[size - 1] = '\0';
        LLAdd(list, i, line);
        HistInc(hist, line);
        i++;
    }
    free(buf);
    fclose(file);
}

//function get input from user and fill hist and list
static void stdin_func(Hist hist, LinkedList list) {
    char *buf = NULL;
    size_t bufsize = 0;
    int i = 0;
    printf("Enter text, please. Write <end> to stop entering:\n");
    while (1) {
        getline(&buf, &bufsize, stdin);
        if (strcmp(buf, "end\n") == 0) break;
        unsigned long size = strlen(buf);
        char *line = buf;
        line[size - 1] = '\0';
        LLAdd(list, i, buf);
        HistInc(hist, buf);
        i++;
    }
    free(buf);
}

//function print out to file
static void out(Hist hist, LinkedList list, char *path_out) {
    FILE *file = fopen(path_out, "w");
    if (file == NULL) exit(-1);
    while (LLSize(list) != 0) {
        char *line = (char *) LLRemove(list, 0);
        fprintf(file, "%3d %s\n", HistGetCount(hist, line), line);
    }
    fclose(file);
}

//function print out to console
static void stdout_func(Hist hist, LinkedList list) //to the console
{
    while (LLSize(list) != 0) {
        char *line = (char *) LLRemove(list, 0);
        printf("%3d %s\n", HistGetCount(hist, line), line);
    }
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
    test_hist();
    if (argc > 3) {
        fprintf(stderr, "\nUsage: %s <file-path>\n", argv[0]);
        return -1;
    }

    Hist hist = HistCreate(clone_str, free, cmp_str);
    LinkedList list = LLCreate(clone_str, free);

    if (argc == 1) {
        stdin_func(hist, list);
        stdout_func(hist, list);
    }
    if (argc == 2) {

        if (*argv[1] == '-') {
            stdin_func(hist, list);
            stdout_func(hist, list);
        } else {
            in(hist, list, argv[1]);
            stdout_func(hist, list);
        }

    }
    if (argc == 3) {
        char *path_in = argv[1];
        char *path_out = argv[2];
        if (*path_in == '-' && *path_out == '-') {
            stdin_func(hist, list);
            stdout_func(hist, list);
        }
        if (*path_in == '-' && *path_out != '-') {
            stdin_func(hist, list);
            out(hist, list, path_out);
        }
        if (*path_in != '-' && *path_out == '-') {
            in(hist, list, path_in);
            stdout_func(hist, list);
        }
        if (*path_in != '-' && *path_out != '-') {
            in(hist, list, path_in);
            out(hist, list, path_out);
        }
    }

    return 0;
}
