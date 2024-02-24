/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Toolsf | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pessoa.h
 * Author: andre
 *
 * Created on 26 de Maio de 2020, 11:21
 */

#ifndef SIMULACAO_h
#define SIMULACAO_h

typedef struct loca local;
typedef struct locais vetorLocais;
typedef struct pessoa no, *pno;

#include "local.h"

char aux_relatorio[100][100];
int aux_x;
void printRelatorio(char mensagem[100][100]);
int aux_simulacao;
void simulacao();
void relatorio(char *mensagem1, char *mensagem2);

#endif /* SIMULACAO_h */ 