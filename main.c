/* 
 * File:   main.c
 * Author: igor
 *
 * Created on 25 de Novembro de 2010, 23:54
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa{
    char nome[30];
    char endereco[50];
    char telefone[10];
}Pessoa;

typedef struct No{
    Pessoa conteudo;
    struct No *prox;
    struct No *ant;
}No;

typedef struct Lista{
    No *inicio;
    No *fim;
}Lista;

// prototipo das funcoes
void inserir(Lista**,Pessoa*);
char* apagar(Lista**);
void mostrar(Lista**);
void cadastrar(Pessoa**);
int verifica(Lista**);

int main() {
    Lista *List = NULL;
    char* info=NULL;
    Pessoa *pessoa = NULL;
    int op;
    do{
        puts("\t\t == Lista Duplamente Encadeada ==\n\n");
        printf("(1) - Inserir\n(2) - Remover\n(3) - Imprimir\n(4) - Sair\n-->");
        scanf("%d",&op);
        __fpurge(stdin);
        switch(op){
            case 1:cadastrar(&pessoa);
                   inserir(&List,pessoa);
                   break;
            case 2:if(verifica(&List) == 0)
                        break;
                   mostrar(&List);
                   info = apagar(&List);
                   if(info==NULL)
                       break;
                   else
                       printf("\nRemovido: %s \n",info);
                   break;
            case 3:if(verifica(&List) == 0)
                        break;
                   mostrar(&List);printf("\n");
                   break;
            case 4:puts("\nFechando...");
                   break;
            default:puts("\nCalma, Usuario amigo!");
        }
        getchar();
        system("clear");
    }while(op!=4);
    return (0);
}

void inserir(Lista **lista,Pessoa *nova){
    No *aux;
    No* novo = (No*)malloc(sizeof(No)); //aloca o no a ser inserido na lista
    novo->conteudo = *nova;
    if(*lista == NULL){  // aloca a lista se ainda nao tiver sido criada e atribui o primeiro no
        *lista = (Lista*)malloc(sizeof(Lista));
        (*lista)->inicio=novo;
        (*lista)->inicio->ant = NULL;
        (*lista)->inicio->prox = NULL;
        (*lista)->fim = novo;
    }
    else{
        if( strcmp(novo->conteudo.nome,(*lista)->inicio->conteudo.nome) < 0 ){ //insere antes do primeiro
            novo->ant = NULL;
            (*lista)->inicio->ant = novo;
            novo->prox = (*lista)->inicio;
            (*lista)->inicio=novo;
        }
        else{
            aux=(*lista)->inicio;
            while(aux != NULL){     // insere no meio
                if( strcmp(novo->conteudo.nome,aux->conteudo.nome) < 0 ){
                    novo->prox = aux;
                    novo->ant = aux->ant;
                    aux->ant->prox= novo;
                    aux->ant = novo;
                    return;
                }
                else
                    aux = aux->prox;
            }
            if(aux == NULL){    // insere no fim da lista
                novo->prox = NULL;
                (*lista)->fim->prox = novo;
                novo->ant = (*lista)->fim;
                (*lista)->fim = novo;
            }
        }
    }
}

char* apagar(Lista **lista){
    No* aux = (*lista)->inicio;
    char info[30];
    char retorno[30];  // nome a ser retornado
    printf("\nPessoa a ser removida: ");
    __fpurge(stdin);
    fgets(info,30,stdin);  // pessoa a ser removida da lista
    if( strcmp(info,(*lista)->inicio->conteudo.nome) == 0 ){  //inicio da lista
        strcpy( retorno,(*lista)->inicio->conteudo.nome );  //copia conteudo para retornar
        if( (*lista)->inicio == (*lista)->fim ){  // se for o unico elemento da lista
            free(aux);
            (*lista)->inicio = (*lista)->fim = NULL;
            return retorno;
        }
        (*lista)->inicio = aux->prox;  // atualiza o inicio pro proximo elemento
        (*lista)->inicio->ant = NULL;
        free(aux);  // libera a memoria ocupada pelo ex-primeiro elemento
        return retorno;
    }
    else{
        while(aux != NULL){
            if( aux->prox == NULL && ( strcmp(info,aux->conteudo.nome) == 0 ) ){        // final da lista
                strcpy( retorno,aux->conteudo.nome );
                (*lista)->fim = aux->ant;
                (*lista)->fim->prox = NULL;
                free(aux);
                return retorno;
            }
            if( strcmp(info,aux->conteudo.nome) == 0 ){  //meio da lista
                strcpy( retorno,aux->conteudo.nome );
                aux->prox->ant = aux->ant;
                aux->ant->prox = aux->prox;
                free(aux);
                return retorno;
            }
            aux = aux->prox;
        }
    }
    printf("\nElemento Nao Existe!\n");
    return NULL;
}

void mostrar(Lista **lista){  // imprime toda a lista
    No *aux = (*lista)->inicio;
    while( aux != NULL ){
    printf("Nome: %sTelefone: %s\nEndereco: %s\n",aux->conteudo.nome,aux->conteudo.telefone,aux->conteudo.endereco);
    printf("---------------------------------------------------\n");
    aux = aux->prox;
    }
}

void cadastrar(Pessoa **Nova){  // cadastrar nova pessoa
    if ( *Nova == NULL)
        (*Nova) = (Pessoa*)malloc(sizeof(Pessoa));
    printf("\nNome: ");
    fgets((*Nova)->nome,30,stdin);  __fpurge(stdin);
    printf("\nTelefone [ex: 6384515637]: ");
    fgets((*Nova)->telefone,10,stdin); __fpurge(stdin);
    printf("\nEndereco: ");
    fgets((*Nova)->endereco,50,stdin); __fpurge(stdin);
    puts("\nCadastrado!");
}

int verifica(Lista **lista){  // verifica se a lista esta vazia
    if( (*lista) == NULL  || (*lista)->inicio == NULL ){
        puts("\nLista Vazia !");
        return 0;
    }
    return 1;
}