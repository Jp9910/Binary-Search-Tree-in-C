#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//EM ORDEM: EPD
//PRE-ORDEM: PED
//POS-ORDEM: EDP

typedef struct no {
    char nome[51];
    char permis[3];
    long int tamanho;
    int indice;
    struct no *E;
    struct no *D;
} no;

FILE* input;
FILE* output;
int cont = -1;

no* adicionarElemento(char* arquivo, char* perm,long int tamanho,no* raiz);
void printPosOrdemEDP(no* node);
void printEmOrdemEPD(no* node);
void printPreOrdemPED(no* node);
//no* search(char* arquivo, no* raiz);

int main (int argc, char *argv[])
{
    int i,qntBuscas;
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    no* RAIZ = NULL;
    char nomme[51];
    char perm[3];
    long int tamanho;

    fscanf(input,"%d",&qntBuscas);


    for(i=0;i<qntBuscas;i++)
    {
        fscanf(input,"%s %s %ld",nomme,perm,&tamanho);
        //printf("%s %s %ld\n",nomme,perm,tamanho);
        RAIZ = adicionarElemento(nomme,perm,tamanho,RAIZ);
    }

//imprimir os elementos na ordem correte. funcao para buscar? pesquisar como implementar a busca em uma arvore
    fprintf(output,"Inorder:\n");
    printEmOrdemEPD(RAIZ);
    fprintf(output,"Preorder:\n");
    printPreOrdemPED(RAIZ);
    fprintf(output,"Postorder:\n");
    printPosOrdemEDP(RAIZ);

    fclose(input);
    fclose(output);
    return 0;
}

no* adicionarElemento(char* arquivo, char* perm,long int tamanho,no* raiz)
{
    cont++;
    no* temp = NULL;
    no* p = NULL;

        temp = (no*)malloc(sizeof(no));
        strcpy (temp->nome, arquivo);
        strcpy (temp->permis,perm);
        temp->tamanho = tamanho;
        temp->indice = cont;
        temp->E = NULL;
        temp->D = NULL;

        if(raiz == NULL)
        {
            raiz = temp;
            raiz->E = NULL;
            raiz->D = NULL;
        }
        else
        {
            p = raiz;
            if(!(strcmp(p->nome, arquivo)))
            {
                if(!(strcmp(p->permis, "rw"))){
                    strcpy (p->permis,perm);
                    p->tamanho = tamanho;
                    p->indice = cont;
                } else {cont--;}
                free(temp);
                return raiz;
            }
            while(p->E != NULL || p->D != NULL)
            {
                if( strcmp(p->nome,arquivo) > 0 )
                {
                    if(p->E != NULL){
                        p=p->E;
                    }
                    else{
                        p->E = temp;
                        p->E->E = NULL;
                        p->E->D = NULL;
                        return raiz;
                    }
                }
                else if ( strcmp(p->nome,arquivo) < 0 )
                {
                    if(p->D != NULL){
                        p=p->D;
                    }
                    else{
                        p->D = temp;
                        p->D->E = NULL;
                        p->D->D = NULL;
                        return raiz;
                    }
                }
                else
                {
                    if(!(strcmp(p->permis, "rw"))){
                        strcpy (p->permis,perm);
                        p->tamanho = tamanho;
                        p->indice = cont;
                    } else {cont--;}
                    free(temp);
                    return raiz;
                }
            }
            if( strcmp(p->nome,arquivo) == 0 )
            {
                if(!(strcmp(p->permis, "rw"))){
                    strcpy (p->permis,perm);
                    p->tamanho = tamanho;
                    p->indice = cont;
                } else {cont--;}
                free(temp);
                return raiz;
            }
            else if ( strcmp(p->nome,arquivo) > 0 )
            {
                p->E = temp;
                p->E->E = NULL;
                p->E->D = NULL;
            }
            else
            {
                p->D = temp;
                p->D->E = NULL;
                p->D->D = NULL;
            }
        }
        return raiz;
}

void printPosOrdemEDP(no* node)
{
     if (node == NULL)
        return;

     // first recur on left subtree
     printPosOrdemEDP(node->E);

     // then recur on right subtree
     printPosOrdemEDP(node->D);

     // now deal with the node
     if(node->tamanho != 1){
        fprintf(output,"%d %s %s %ld bytes\n",node->indice,node->nome,node->permis,node->tamanho);
     }
     else{
        fprintf(output,"%d %s %s %ld byte\n",node->indice,node->nome,node->permis,node->tamanho);
     }
}

void printEmOrdemEPD(no* node)
{
     if (node == NULL)
          return;

     /* first recur on left child */
     printEmOrdemEPD(node->E);

     /* then print the data of node */
     if(node->tamanho != 1){
        fprintf(output,"%d %s %s %ld bytes\n",node->indice,node->nome,node->permis,node->tamanho);
     }
     else{
        fprintf(output,"%d %s %s %ld byte\n",node->indice,node->nome,node->permis,node->tamanho);
     }

     /* now recur on right child */
     printEmOrdemEPD(node->D);
}

void printPreOrdemPED(no* node)
{
     if (node == NULL)
          return;

     /* first print data of node */
     if(node->tamanho != 1){
        fprintf(output,"%d %s %s %ld bytes\n",node->indice,node->nome,node->permis,node->tamanho);
     }
     else{
        fprintf(output,"%d %s %s %ld byte\n",node->indice,node->nome,node->permis,node->tamanho);
     }

     /* then recur on left sutree */
     printPreOrdemPED(node->E);

     /* now recur on right subtree */
     printPreOrdemPED(node->D);
}