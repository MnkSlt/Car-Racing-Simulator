/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pessoa.h
 * Author: andre
 *
 * Created on 26 de Maio de 2020, 11:21
 */

#ifndef PESSOA_H
#define PESSOA_H

typedef struct loca local;
typedef struct locais vetorLocais;
typedef struct pessoa no, *pno;

#include "local.h"
#include "utils.h"

struct pessoa
{
    char nome[100];
    int idade, dias;
    char estado[1];
    bool sala;
    //local *local;
    pno prox;
};

int num_pessoas;
void infoDoente(pno pessoa);
void printPessoa(pno pessoa);
void printPessoas(pno lista);
void eliminaPessoas(pno *lista);
pno insere_inicio(pno p, pno pessoa);
pno criaLista(pno lista, pno pessoa);
pno criaCopia(pno aCopiar);
pno carregaPessoas(char *nome);
pno adicionaPessoa(pno lista, pno pessoa);
pno adicionaPessoa2(pno lista, pno pessoa);

#endif /* PESSOA_H */
