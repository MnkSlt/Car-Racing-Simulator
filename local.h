/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   local.h
 * Author: andre
 *
 * Created on April 26, 2020, 4:20 PM
 */

#ifndef LOCAL_H
#define LOCAL_H

#define MAX_NAME_SIZE 101
#define INITIAL_RESERVE 4     //ESPACO INICIALMENTE RESERVADO PA AGENDA, ou seja, vai ter smp espaco pa 2 contactos
#define RESERVE_INCREMENT 100 //qnd precisamos de realocar quantos espacos a mais vamos alocar, ou seja, se precisarmos de mais espaco, ou seja, adicionar um 3o elem, alocamos mais 100 espacos
#define LIGA_SIZE 3

typedef struct pessoa no, *pno;
typedef struct loca local;

#include "pessoa.h"
#include "simulacao.h"
struct loca
{
    int id;         // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3];    // id das ligações (-1 nos casos não usados)
    int count;
    pno pessoa;
};

/*  VETOR DINAMICO DE ESTRUTURAS PARA OS LOCAIS  */
typedef struct locais vetorLocais;
struct locais
{
    int tamanho_utilizado; //espaco utilizado
    int tamanho_reservado; //espaco reservado
    local *locais;         //ponteiro para array
};

vetorLocais *initLocal();


void infoFicheiro(char *nome, vetorLocais *vl);
void lerFicheiroBin(char *nome);
int linhasFicheiroBin(char *nome);
int verificaLocais(vetorLocais *vl);
void printLocais(vetorLocais *vl);
void printLocal(local *l);

void addLocalFromUser(vetorLocais *vl);
local *readLocal(vetorLocais *vl);
local *searchLocal(int id, vetorLocais *vl);
void addLocal(local *l, vetorLocais *vl);

int getId(int id, vetorLocais *vl);

#endif /* LOCAL */
