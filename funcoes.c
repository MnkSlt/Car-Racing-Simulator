#include "funcoes.h"
vetorLocais *insereDoenteLocal(int id, vetorLocais *vl)
{
    int flag = 0;
    pno novo = malloc(sizeof(no));
    infoDoente(novo);
    for (int i = 0; i < vl->tamanho_utilizado; i++)
    {
        //pno aux = vl->locais[i].pessoa;
        printf("vl->locais[i].id %d", vl->locais[i].id);
        if (vl->locais[i].id == id && flag == 0)
        {
            vl->locais[i].pessoa = insere_inicio(vl->locais[i].pessoa, novo);
            flag = 1;
        }
        else
            printf("\n ### [Debug] O id inserido nao existe nos locais ###\n");
    }
    return vl;
}

char *tempoAtual()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("Current local time and date: %s", asctime(timeinfo));
    return asctime(timeinfo);
}

void taxaDessiminacao(vetorLocais *vLocais)
{
    //num de pessoas num local
    //aux->local->count
    int randomNumber = 0;
    int numPessoas_a_infetar = 0;
    int id_aux = 0;
    pno pessoas;
    for (int i = 0; i < vLocais->tamanho_utilizado; i++)
    {
        pno aux = vLocais->locais[i].pessoa;
        numPessoas_a_infetar = vLocais->locais[i].count * 0.05; //em 10 infetada 2as
        printf("\npercentagem a infetar: %.2f no local %d\n");
        if (numPessoas_a_infetar > 0)
        {
            while (numPessoas_a_infetar)
            {
                pessoas = aux;
                while (pessoas)
                {
                    printf("/n#[Debug] taxaDessiminacao pessoas->local[i].is == id_aux/n");
                    if (pessoas->estado[0] == 'S')
                    {
                        printf("/n#[Debug] taxaDessiminacao pessoas->estado[0] = %c'D'/n", pessoas->estado[0]);
                        pessoas->estado[0] = 'D';
                    }
                }
                pessoas = pessoas->prox;
            }
            numPessoas_a_infetar--;
        }
    }
}
vetorLocais *atribuiPessoasLocais(pno pessoas, vetorLocais *vl)
{
    pno aux = pessoas;

    if (aux == NULL)
        printf("\nAUX E NULL\n");
    initRandom();
    //funcao que retorna numero de locais
    int numLocais = vl->tamanho_utilizado;

    int numRandom;
    for (int i = 0; i < vl->tamanho_utilizado; i++)
        vl->locais[i].pessoa = NULL;

    while (aux != NULL)
    {
        numRandom = intUniformRnd(0, numLocais - 1);
        if (/* aux->sala != true &&  */ vl->locais[numRandom].capacidade > vl->locais[numRandom].count)
        {
            vl->locais[numRandom].count++;
            vl->locais[numRandom].pessoa = insere_inicio(vl->locais[numRandom].pessoa, aux);
        }
        aux = aux->prox;
    }
    return vl;
}

void mostrarSalas(vetorLocais *vl)
{
    int i;

    //printf("\nidade %d\n", vl->locais[1].pessoa->idade);
    for (i = 0; i < vl->tamanho_utilizado - 1; i++)
    {
        printf("\nLocal ID %d\n", vl->locais[i].id);

        pno aux = vl->locais[i].pessoa;
        printf("\nPessoa %s", aux->nome);
        while (aux)
        {
            printf("\n222222222222222222222222");
            if (aux != NULL)
                printf("\nPessoa %s", aux->nome);

            aux = aux->prox;
        }
    }
    printf("\n\n");
}

void limparEcra()
{
    int i;
    for (i = 0; i < 40; i++)
    {
        printf("\n");
    }
}
void estatisticas(pno pessoas)
{
    printf("\n\n -------> Estatisticas <-------\n");
    pno aux = pessoas;
    printf("\n\tsaudaveis: %.2f", mostrarPercentagemSaudaveis(aux));
    aux = pessoas;
    printf("\n\tinfetados: %.2f", mostrarPercentagemInfetados(aux));
    aux = pessoas;
    printf("\n\timunes:    %.2f\n", mostrarPercentagemImunes(aux));
}
float mostrarPercentagemSaudaveis(pno pessoas)
{
    float percentagemSaudaveis = 0.0;
    float saudaveis = 0.0;
    float total = 0.0;
    while (pessoas)
    {

        if (pessoas->estado[0] == 'S')
            saudaveis++;
        total++;
        pessoas = pessoas->prox;
    }
    //printf("\ntotal %f, saudaveis %f\n", total, saudaveis);

    return percentagemSaudaveis = saudaveis / total;
}
float mostrarPercentagemInfetados(pno pessoas)
{

    float percentagemInfetados = 0.0;
    float infetados = 0.0;
    float total = 0.0;
    while (pessoas)
    {

        if (pessoas->estado[0] == 'D')
            infetados++;

        total++;
        pessoas = pessoas->prox;
    }
    //printf("\ntotal %f, infetados %f\n", total, infetados);

    return percentagemInfetados = infetados / total;
}
float mostrarPercentagemImunes(pno pessoas)
{
    float percentagemImunes = 0.0;
    float imunes = 0.0;
    float total = 0.0;
    while (pessoas)
    {
        if (pessoas->estado[0] == 'I')
            imunes++;
        total++;
        pessoas = pessoas->prox;
    }
    //printf("\ntotal %f, imunes %f\n", total, imunes);
    return percentagemImunes = imunes / total;
}
/* ->taxa de imunidade : quando uma pessoa, deixa de ficar doente, por recuperacao ou 
por terem passado os dia isto gera prob de ficar imune msm que olte a ficar infetado, 
n contrai a doenca taxa de imnuidade = 20 % */
void taxaImunidade(pno pessoas, char *nome)
{
    initRandom();
    int prob = 0;
    prob = intUniformRnd(1, 5);
    while (pessoas)
    {
        if (strcmp(nome, pessoas->nome) == 0)
        {
            if (prob == 4)
            {
                pessoas->estado[0] = 'I';
                printf("\nprob pessoas->imune \n");
            }
            else
                pessoas->estado[0] = 'S';
            break;
        }
        pessoas = pessoas->prox;
    }
}

void setDuracaoInfecao(pno pessoa, char *nome)
{
    while (pessoa)
    {
        if (strcmp(nome, pessoa->nome) == 0)
        {
            int idade = pessoa->idade;
            int diasDezena = idade / 10;
            pessoa->dias = diasDezena + 5;
            //printf("\n#[Debug] - %f, pessoa->idade %d", aux, pessoa->idade);
        }
        pessoa = pessoa->prox;
    }
}

/* ->probabilidade de recuperacao : prob de recuperacao de um doente, 
em cada iteracao prob = 1 / idade */

float probRecuperacao(pno pessoa, char *nome)
{
    float prob, idade;
    while (pessoa)
    {
        if (strcmp(nome, pessoa->nome) == 0)
        {
            idade = pessoa->idade;
            prob = 1 / idade;
            //printf("\n#[Debug] - %f, pessoa->idade %d", aux, pessoa->idade);
        }
        pessoa = pessoa->prox;
    }

    return prob;
}
