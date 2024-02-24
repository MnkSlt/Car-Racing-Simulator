#include "simulacao.h"
int aux_x = 0;

void relatorio(char *mensagem1, char *mensagem2)
{
    int i = 0, k = 0;
    printf("%d", aux_x);
    aux_x += 0;
    while (i < 100)
    {
        while (k < 100)
        {
            aux_relatorio[i][k] = '\0';
            k++;
        }
        i++;
    }
    /*  if (aux_relatorio[aux_x][100] = malloc(sizeof(aux_relatorio[aux_x][100]) * 1000))
        printf("DEU"); */
    strcat(mensagem1, mensagem2);
    //memset(aux_relatorio[aux_x], '\0', sizeof(aux_relatorio[100]));
    //printf("%s",mensagem1);
    strcpy(aux_relatorio[aux_x], mensagem1);
    printf("%s", aux_relatorio[aux_x]);
    aux_x += 1;
}
void printRelatorio(char mensagem[100][100])
{
    int i;
    printf("ola");
    for (i = 0; i < aux_x; i++)
        printf("Mensagem %d: %s\n", i, mensagem[i]);
}

void simulacao()
{
    setbuf(stdout, NULL);
    pno pessoas = carregaPessoas("pessoas.txt");
    //printPessoas(pessoas);

    vetorLocais *vl = initLocal();
    infoFicheiro("E1.bin", vl);
    vl = atribuiPessoasLocais(pessoas, vl);
    //printLocais(vl);

    int opcao = 0;

    while (opcao != 5)
    {
        printf("\n<Consola> ");
        scanf("%d", &opcao);
        if (opcao == 6)
        {
            printf("\n1 - Avancar uma iteracao:\n2 - Apresentar Estatisticas:\n3 - Adicionar doente:\n4 - Transferir pessoas:\n5 - Terminar Simulacao:\n6 - Help");
        }
        else if (opcao == 1)
        {
            aux_simulacao += 1;
            limparEcra();
            printf("\t############### Dia numero %d ###############\n\n\n\n\n\n\n", aux_simulacao);
            taxaDessiminacao(vl);
        }
        else if (opcao == 2)
        {
            limparEcra();
            printf("\n\t################# Distribuicao de Pessoas #################\n");
            printLocais(vl);
            estatisticas(pessoas);
        }
        else if (opcao == 3)
        {
            int id = 0;
            printf("\n\t################# Adicionar um doente ao local #################\n");
            //user insere o id do local, e o nome idade e dias da pessoas
            printf("\nID do local: ");
            scanf("%d", &id);
            printf("\n%d", id);
            vl = insereDoenteLocal(id, vl);
        }
        else if (opcao == 4)
        {
            limparEcra();
            printf("\n\t################# Relatorio #################");
            printRelatorio(aux_relatorio);
        }
        else if (opcao == 5)
        {
            limparEcra();
            pno *aux = &pessoas;
            printf("\n\t################# Fim #################");
            eliminaPessoas(aux);
            free(vl);
        }
    }
}