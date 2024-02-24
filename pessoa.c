#include "pessoa.h"

pno carregaPessoas(char *nome)
{
    FILE *file = fopen(nome, "r");
    if (!file)
    {
        printf("Erro na abertura\n");
        return NULL;
    }

    pno lista = NULL;
    no aux;
    while (fscanf(file, "%14s %d %c", aux.nome, &aux.idade, &aux.estado) != EOF)
    {
        aux.sala = false;
        if (aux.estado[0] == 'D')
            fscanf(file, " %d", &aux.dias);
        else
            aux.dias = 0;
        pno pessoa = criaCopia(&aux);
        lista = adicionaPessoa(lista, pessoa);

        num_pessoas += 1;
    }
    fclose(file);
    return lista;
}
pno criaLista(pno lista, pno pessoa)
{
    pno temp = malloc(sizeof(no));
    if (temp == NULL)
    {
        printf("[ERRO] Alocacao de memoria.\n");
        return false;
    }

    temp = pessoa;
    temp->prox = NULL;
    lista = temp;
    return lista;
}

pno adicionaPessoa(pno lista, pno pessoa)
{
    if (!lista)
        return pessoa;

    pno ultimo = lista;
    while (ultimo->prox)
        ultimo = ultimo->prox;

    ultimo->prox = pessoa;

    return lista;
}
pno insere_inicio(pno p, pno pessoa)
{
    pno novo;
    if ((novo = malloc(sizeof(no))) == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        //relatorio(tempoAtual(), ": Erro na alocacao de memoria /pno insere_inicio/");
    }
    else
    {
        novo = criaCopia(pessoa);
        printPessoas(novo);
        novo->prox = p;
        p = novo;
        //relatorio(tempoAtual(), ": Doente atribuido a local\n");
    }

    return novo;
}

void eliminaPessoas(pno *lista)
{
    pno aux = *lista;
    pno next;
    while (aux)
    {
        next = aux->prox;
        free(aux);
        aux = next;
    }

    *lista = NULL;
}
void infoDoente(pno pessoa)
{
    printf("Nome");
    char aux[10];
    scanf(" %10s", aux);
    printf("%s", aux);
    strcpy(pessoa->nome, aux);
    printf("Nome");
    scanf("%d", &pessoa->idade);
    scanf("%d", &pessoa->dias);
    strcpy(pessoa->estado, "D");
}
pno criaCopia(pno aCopiar)
{
    pno pessoa = malloc(sizeof(no));
    strcpy(pessoa->nome, aCopiar->nome);
    pessoa->idade = aCopiar->idade;
    strcpy(pessoa->estado, aCopiar->estado);
    pessoa->dias = aCopiar->dias;
    pessoa->sala = aCopiar->sala;
    //pessoa->local = aCopiar->local;
    pessoa->prox = NULL;
    return pessoa;
}

void printPessoa(pno pessoa)
{
    printf("\nNome: %s\n", pessoa->nome);
    printf("Idade: %d\n", pessoa->idade);
    printf("Estado: %c\n", pessoa->estado[0]);
    printf("Dias: %d\n", pessoa->dias);
    //if (pessoa->local->id != 0)
    //printf("ID do local: %d\n\n", pessoa->local->id);

    /*
    printf("Self memory address: %p\n", pessoa);
    printf("Next memory address: %p\n", pessoa->prox);
*/
}

void printPessoas(pno lista)
{
    //relatorio(tempoAtual(), ": Pessoas impressas");
    if (!lista)
    {
        printf("\nLista vazia\n");
        return;
    }
    pno aux = lista;
    while (aux)
    {
        printPessoa(aux);
        aux = aux->prox;
    }
}
