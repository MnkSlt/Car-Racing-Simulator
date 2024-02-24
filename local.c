/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   local -Wall
 * .c
 * Author: andre
 *
 * Created on April 26, 2020, 4:19 PM
 */

#include "local.h"

vetorLocais *initLocal()
{
    //reservar um bloco de memoria
    vetorLocais *vl = malloc(sizeof(vetorLocais));
    //inicializar os restantes parametros
    vl->locais = NULL;
    vl->tamanho_utilizado = vl->tamanho_reservado = 0;

    printf("\n\t### VetorLocais inicializado ###\n\n");
    return vl;
}

void infoFicheiro(char *nome, vetorLocais *vl)
{
    FILE *file = fopen(nome, "rb");
    if (!file)
    {
        printf("Erro na abertura\n");
        ////relatorio("Erro na abertura\n");
        return;
    }
    ////relatorio("\n### infoFicheiro  ###\n");
    //printf("\n### infoFicheiro  ###\n");
    local p; //= malloc(sizeof(local));
    int i = 0;
    int linhas = linhasFicheiroBin(nome);

    vl->locais = malloc(sizeof(local) * linhas);

    vl->tamanho_reservado = INITIAL_RESERVE;
    vl->tamanho_utilizado += linhas;
    while (fread(&p, sizeof(local), 1, file))
    {
        vl->locais[i].id = p.id;
        vl->locais[i].capacidade = p.capacidade;
        vl->locais[i].liga[0] = p.liga[0];
        vl->locais[i].liga[1] = p.liga[1];
        vl->locais[i].liga[2] = p.liga[2];
        vl->locais[i].count = 0;

        i++;
    }
    fclose(file);

    //int aux = verificaLocais(vl);
    //se for 1 foi bem sucedido
    // -1 id negativo
    //-2 ids iguais
    //-3 id, nas ligacoes, negativos e dif de -1
    //-4 ligacoes nao correspondem corretamente
    /*    if (aux == -1)
        printf("\n[Debug] Ficheiros nao carregados\n"); */
}

int verificaLocais(vetorLocais *vl)
{
    int aux = 0;
    int j, k;
    //verifica se o id e negativo ou igual
    for (j = 0; j < vl->tamanho_utilizado; j++)
        if (vl->locais[j].id < 1)
        {
            //relatorio("\n[Debug] Ficheiro de locais nao carregado devido a id negativo\n");
            aux = -1;
        }
    // verifica se o id e igual
    for (j = 0; j < vl->tamanho_utilizado; j++)
    {
        for (k = 0; k < vl->tamanho_utilizado; k++)
        {
            if (k != j)
                if (vl->locais[j].id == vl->locais[k].id)
                {

                    //printf("\nvl->locais[j].id %d %d", vl->locais[j].id, vl->locais[k].id);
                    aux = -1;
                    //relatorio("\n[Debug] Ficheiro de locais nao carregado devido a ids iguais\n");
                }
        }
    }

    int l, m, flag, aux1, aux2;
    //verfica se o id sas ligacoes sao <=0 e != -1(pois -1 e pq nao tem ligacao)
    for (l = 0; l < vl->tamanho_utilizado; l++)
    {
        for (m = 0; m < LIGA_SIZE; m++)
        {
            if (vl->locais[l].liga[m] <= 0)
                if (vl->locais[l].liga[m] != -1)
                {
                    aux = -1;
                    //relatorio("\n[Debug] Ficheiro de locais nao carregado devido a id, nas ligacoes, negativos e dif de -1\n");
                }
        }
    }

    //verifica ligacoes entre ids, se corresponde uns aos outros
    for (int i = 0; i < vl->tamanho_utilizado; i++)
    {
        for (int j = 0; j < LIGA_SIZE; j++)
        {
            if (vl->locais[i].liga[j] != -1)
            {
                aux1 = vl->locais[i].liga[j];
                aux2 = vl->locais[i].id;
                //                flag = verificaIdLigacoes(vl, aux1, aux2);
                if (flag != 1)
                {
                    //relatorio("\n[Debug] Ficheiro de locais nao carregado devido a ligacoes nao correspondem corretamente \n");
                    aux = -1;
                }
            }
        }
    }
    if (aux < 0 && aux >= -4)
        return aux;
    else
    {
        //relatorio("\n[Debug] Ficheiro de locais carregado com sucesso\n");
        aux = 1;
    }
    return aux;
}

int verificaIdLigacoes(vetorLocais *v, int id_destino, int id_origem)
{
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        if (v->locais[id_destino].liga[i] != id_origem)
            flag = -1;
        else
            flag = 1;
    }
    return flag;
}

void lerFicheiroBin(char *nome)
{
    //relatorio("\t### le linhas ficheiro binario ###\n\n");
    printf("\t### le linhas ficheiro binario %s ###\n\n", nome);
    FILE *file = fopen(nome, "rb");
    if (!file)
    {
        printf("Erro na abertura\n");
        return;
    }
    local p;

    int i = 0;
    while (fread(&p, sizeof(local), 1, file))
        i++;

    fclose(file);
}

int linhasFicheiroBin(char *nome)
{

    printf("\t### Ficheiro binario %s ###\n\n", nome);
    FILE *file = fopen(nome, "rb");
    if (!file)
    {
        printf("Erro na abertura\n");
        return 0;
    }

    local p;
    int i = 0;
    while (fread(&p, sizeof(local), 1, file))
        i++;

    fclose(file);
    return i;
}

void addLocalFromUser(vetorLocais *vl)
{
    local *l = readLocal(vl);
    addLocal(l, vl); //malloc
    free(l);
}

//preenche local com input

local *readLocal(vetorLocais *vl)
{
    //alocal memoria
    local *l = malloc(sizeof(local));

    //verificar se o id nao e duplicado
    while (1)
    {
        printf("id >>> ");
        scanf("%d", &l->id);
        getchar();
        local *resultado = searchLocal(l->id, vl);
        if (resultado != NULL)
            printf("Ja existe um local com o id: %d\n", l->id);
        else
            break;
    }
    printf("capacidade >>> ");
    scanf("%d", &l->capacidade);

    getchar();
    int i = 0;

    return l;
}

//verifica sem ja exite um local com o mesmo id, caso nao envia null, senao envia o local com o id igual

local *searchLocal(int id, vetorLocais *vl)
{
    local *l = NULL;
    int i;
    for (i = 0; i < vl->tamanho_utilizado; i++)
    {
        if (id == vl->locais[i].id)
        {
            l = &vl->locais[i];
            break;
        }
    }
    return l;
}

void addLocal(local *l, vetorLocais *vl)
{
    if (!l || !vl)
        return;
    if (vl->locais == NULL)
    {
        //relatorio("\t[addContacto] malloc inicial, limite =\n\n");
        printf("\t[addContacto] malloc inicial, limite = %d\n\n", INITIAL_RESERVE);
        vl->locais = malloc(sizeof(local) * INITIAL_RESERVE);
        vl->tamanho_reservado = INITIAL_RESERVE;
        vl->tamanho_utilizado = 1;
        vl->locais[0] = *l;
    }
    else if (vl->tamanho_utilizado < vl->tamanho_reservado)
    {
        //relatorio("\t[addLocal] adiciona sem malloc e realloc\n\n");
        printf("\t[addLocal] adiciona sem malloc e realloc %d\n\n", INITIAL_RESERVE);
        vl->locais[vl->tamanho_utilizado] = *l;
        vl->tamanho_utilizado++; //se o cout for 10, os indices vao de 0 a 9
    }
    else
    {
        //relatorio("\t[addContacto] realloc, limite atual = %d, novo limite \n\n");
        printf("\t[addContacto] realloc, limite atual = %d, novo limite = %d\n\n", vl->tamanho_reservado, vl->tamanho_reservado + RESERVE_INCREMENT);
        vl->locais = realloc(vl->locais, sizeof(local) * (vl->tamanho_reservado + RESERVE_INCREMENT));
        vl->tamanho_reservado += RESERVE_INCREMENT;
        vl->tamanho_utilizado++;
    }
}

void printLocais(vetorLocais *a)
{
    /* 
    printf("\t### Vetor Locais ###\n\n");
    printf("Reserved = %d\n", a->tamanho_reservado); */
    if (!a->tamanho_utilizado)
    {
        printf("Sem locais\n");
        //relatorio("Sem locais\n");
    }
    else
    {
        for (int i = 0; i < a->tamanho_utilizado; i++)
            printLocal(&a->locais[i]);
    }
}
void printLocal(local *p)
{
    pno aux = p->pessoa;
    //relatorio("\n[printLocal]\n");
    printf("\n\n\nLocal => Id: %d, capacidade: %d, liga[0]: %d, liga[1]: %d, liga[2]: %d, Numero de pessoas: %d\n",
           p->id, p->capacidade, p->liga[0], p->liga[1], p->liga[2], p->count);
    while (aux->prox != NULL)
    {
        printf("\n  -> Nome: %s \n\t- Idade:  %d\n\t- Estado: %c\n\t- Dias %d\n", p->pessoa->nome, p->pessoa->idade, p->pessoa->estado[0], p->pessoa->dias);
        aux = aux->prox;
    }
    /* printf("\nsaudaveis: %.2f", mostrarPercentagemSaudaveis(aux));
    printf("\ninfetados: %.2f", mostrarPercentagemInfetados(aux));
    printf("\nimunes:    %.2f", mostrarPercentagemImunes(aux)); */
}
