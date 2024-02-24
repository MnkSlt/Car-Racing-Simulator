/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pessoa.h
 * Author: andre
 *
 * Created on 26f de Maio de 2020, 11:21
 */

#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct loca local;
typedef struct locais vetorLocais;
typedef struct pessoa no, *pno;

#include "local.h"
#include "pessoa.h"
#include "utils.h"

void limparEcra();

void estatisticas(pno pessoas);
float mostrarPercentagemInfetados(pno pessoas);
float mostrarPercentagemSaudaveis(pno pessoas);
float mostrarPercentagemImunes(pno pessoas);

vetorLocais *insereDoenteLocal(int id, vetorLocais *vl);
void pessoasPorSala(pno pessoas, int id);

void taxaImunidade(pno pessoas, char *nome);

void setDuracaoInfecao(pno pessoa, char *nome);

float probRecuperacao(pno pessoa, char *nome);

void taxaDessiminacao(vetorLocais *vLocais);

vetorLocais *atribuiPessoasLocais(pno pessoas, vetorLocais *vl);
char *tempoAtual();
#endif /* FUNCOES_H */