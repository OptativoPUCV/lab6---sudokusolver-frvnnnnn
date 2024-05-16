#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
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

int is_valid(Node* n) {
    int rows[9][10] = {0};
    int cols[9][10] = {0};
    int submatrices[9][10] = {0};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (rows[i][num] == 1) return 0;
                rows[i][num] = 1;
                if (cols[j][num] == 1) return 0;
                cols[j][num] = 1;

                int k = 3 * (i / 3) + (j / 3);
                if (submatrices[k][num] == 1) return 0; 
                submatrices[k][num] = 1; 
            }
        }
    }

    return 1;
}
void copiar(Node * nodo, Node * nodo2){
   for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            nodo->sudo[row][col] = nodo2->sudo[row][col];
        }
    }
}

List* get_adj_nodes(Node* n) {
    List* list = createList();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) { 
                for (int num = 1; num <= 9; num++) {
                    Node* newNode = createNode();
                     copiar(newNode,n);
                    newNode->sudo[i][j] = num; 
                    if (is_valid(newNode)) {
                        pushBack(list, newNode);
                    } else {
                        free(newNode);
                    }
                }
                return list; // Solo se permite una acción por cada casilla vacía
            }
        }
    }
    return list; // No hay nodos adyacentes (tablero resuelto o error en la entrada)
}

int is_final(Node* n){
    for (int i = 0; i < 9; i++)
       for (int k=0;k<9;k++)
          {
             if (n->sudo[i][k] == 0)
                return 0;
          }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack *stack = createStack();
   push(stack, initial);
   while(get_size(stack) != 0)
      {
         Node* aux = top(stack);
         pop(stack);
         if (is_final(aux))
            return aux;
         List* list = get_adj_nodes(aux);
         while (list!=NULL)
            {
               
               Node* aux2 = first(list);
               popFront(list);
               push(stack,aux2);
            }
         free(stack);
       
      }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/