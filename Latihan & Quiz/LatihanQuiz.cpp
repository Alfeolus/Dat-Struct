#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node{
    char Address[100];
    char id[100];
    char type[30];
    Node *next;
}