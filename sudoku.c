#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>



typedef struct Node{
   int sudo[9][9];
   int visited;
   struct Node *parent;
}Node;

int is_final(Node* n){
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            int val = n->sudo[i][j];
            if (val == 0) return 0;
        }
    }
    return 1;
}

void show(Node *n, int size) {
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            printf("%d", n->sudo[i][j]);
            if ( (j+1) % 3 == 0 && size == 9 ) putchar ('|');
            else putchar (' ');

        }
        if ((i+1) % 3 == 0) {
            putchar('\n');
            for(int i = 0; i < 18; i++) putchar ('-');
        }
        putchar('\n');
    }
}

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  (*n).visited = 0;
  (*n).parent = NULL;
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int isSubmatrixValid(Node *n, int r, int c) {
    c*=3;
    r*=3;
    
    int nums[10] = {0};
    for(int i = c; i < c+3; i++) {
        for(int j = r; j < r+3; j++) {
            int val = n->sudo[i][j];
            if ( val && nums[val] ) return 0;
            else
                nums[val] = 1;
        }
    }
    return 1;
}

int is_valid(Node* n){
    // para cada fila 
    for(int j = 0; j < 9; j++) {
        int nums[10] = {0};
        for(int i = 0; i<9; i++) {
            int val = n->sudo[j][i];
            if (val && nums[val]) return 0;
            else nums[val] = 1;
        }
    }
    for (int k = 0; k < 2; k++) {
        for(int l = 0; l < 2; l++) {
            if(isSubmatrixValid(n, k, l) == 0) return 0;
        }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    show(n, 9);
    printf("Valid? :");
    printf(is_valid(n) ? "yes":"no");
    printf("Final? :");
    printf(is_final(n) ? "yes":"no");
    putchar('\n');

    List* list=createList();
    if (!is_valid(n)) return list;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
               if (!n->sudo[i][j]) { 
                    for (int k = 1; k < 10; k++) {
                        n->sudo[i][j] = k;
                         if (is_valid(n)) {
                            Node *adj = copy(n);
                            pushBack(list, adj);
                     }
                }
                n->sudo[i][j] = 0;
                return list;
            }
        }
    }
    return NULL;
}



Node* DFS(Node* initial, int* cont){
    Stack * stack = createStack();
    push(stack, initial);
    Node *aux = NULL;
    while (!is_empty(stack)) {
        aux = top(stack);
        pop(stack);
        if (is_final(aux)) {
            printf("Final:\n");
            show(aux, 9);
            putchar('\n');
            return aux;
        }
        List *ady = get_adj_nodes(aux);

        for(Node *i = first(ady); i != NULL; i = next(ady)) {
            push(stack, i);
        }

        (*cont)++;
    }

    printf("iteraciones: %d", *cont);
  return NULL;
}



/*

int main( int argc, char *argv[] )
{

//     Initial test file not valid in submatrix 
    Node* initial= read_file("lol.txt");

    show(initial, 9);

    printf("Is ^ valid?: ");
    printf(is_valid(initial) ? "yes":"no");
    putchar('\n');
    printf("Expected: no..\n");

    for (int k = 0; k < 3; k++) {
        for(int l = 0; l < 2; l++) {
            printf("subm %d %d %d", k, l, isSubmatrixValid(initial, k, l)); 
        }
    putchar('\n');
    }
    putchar('\n');

    assert (is_valid(initial) == 0 );

    int cont=0;
    Node* final = DFS(initial, &cont);
    printf("iterations:%d\n",cont);
    print_node(final);

  return 0;
}
*/
