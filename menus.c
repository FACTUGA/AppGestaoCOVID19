#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menus.h"
#include "funcoesMembros.h"
#include "funcoesAuxiliares.h"
#include "funcoesFicheiros.h"
#include "funcoesTestes.h"



char menu(int *totalMembros, int *testesAgendados, int *totalVacinados, int *totalTestes)
{
    char opcao;

    int testesRealizados = 0;

    testesRealizados = *totalTestes - *testesAgendados;         //Calcula o total de testes realizados
    do
    {
        printf("=================================================[Menu Principal]======================================================\n\n");      // 16 » em cada
        printf("Membros: [%d]\t\t\t\t\t\t\t\t\tTestes Agendados: [%d]\n",*totalMembros,*testesAgendados);                                                                         //TO DO totalMembros|totalTestesAgendados
        printf("Membros Vacinados: [%d]\t\t\t\t\t\t\t\tTestes Realizados: [%d]\n\n\n",*totalVacinados,testesRealizados);                                                            //TO DO totalMembrosVacinados|totalTestesRealizados
        printf("\tM - Mostrar opcoes dos membros\n");
        printf("\tT - Mostrar opcoes dos testes\n");
        printf("\tD - Apresentar dados estatisticos\n");
        printf("\tF - Mostrar opcoes de ficheiros\n");
        printf("\tS - Sair\n\n\tOpcao---> ");
        scanf("%c", &opcao);
        printf("\n\n\n");
        opcao = toupper(opcao);
        limpaBufferStdin();

    }
    while(opcao != 'M' && opcao != 'T' && opcao != 'D' && opcao != 'F' && opcao != 'S');

    return opcao;
}

char subMenuMembros(void)
{
    char opcao;

    do
    {
        printf("=================================================[Menu Membro]==========================================================\n\n");
        printf("\tA - Adicionar membro\n");
        printf("\tM - Mostrar membros\n");
        printf("\tV - Registar/Actualizar estado de vacinacao\n");
        printf("\tC - Registar/Actualizar estado de confinamento\n");
        printf("\tL - Apresentar casos de confinamento\n");
        printf("\tS - Sair\n\n\tOpcao---> ");
        scanf("%c", &opcao);
        opcao = toupper(opcao);
        limpaBufferStdin();

    }
    while(opcao != 'A' && opcao != 'M' && opcao != 'V' && opcao != 'C' && opcao != 'S' && opcao != 'L');

    return opcao;
}

void opcaosubMenuMembros(char opcaoMembro, tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros, int *totalVacinados,tipoTestesCovid *vetorDinamicoTestesCovid,int totalTestes)
{
    do
    {
        switch(opcaoMembro)
        {
        case 'A':
            registarMembro(vetorMembros,totalMembros,totalVacinados);
            printf("\n");
            break;
        case 'M':
            listarMembros(vetorMembros,totalMembros,vetorDinamicoTestesCovid,totalTestes);
            printf("\n");
            break;
        case 'V':
            registarAtualizarEstadoVacinacao(vetorMembros,*totalMembros,totalVacinados);
            printf("\n");
            break;
        case 'C':
            registarAtualizarEstadoConfinamento(vetorMembros,*totalMembros);
            printf("\n");
            break;
        case 'L':
            listarCasosConfinamento(vetorMembros,*totalMembros);
            printf("\n");
            break;
        }
    }
    while (opcaoMembro != 'S' && opcaoMembro != 'A' && opcaoMembro != 'M' && opcaoMembro != 'V' && opcaoMembro != 'C' && opcaoMembro != 'L');

}

char subMenuTestes(void)
{
    char opcao;

    do
    {
        printf("=================================================[Menu Testes Covid]====================================================\n\n");
        printf("\tA - Agendar teste\n");
        printf("\tR - Registar resultado do teste\n");
        printf("\tL - Listar testes\n");
        printf("\tD - Alterar data de teste agendado\n");
        printf("\tX - Apresentar informacao de teste\n");
        printf("\tS - Sair\n\n\tOpcao---> ");
        scanf("%c", &opcao);
        opcao = toupper(opcao);
        limpaBufferStdin();
    }
    while(opcao != 'A' && opcao != 'L' && opcao != 'D' && opcao != 'R' && opcao != 'S'  && opcao !='X');

    return opcao;
}

tipoTestesCovid *opcaosubMenuTestes(char opcaoTeste,tipoTestesCovid *vetorDinamicoTestesCovid,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS],int *totalMembros, int *totalTestes, int *testesAgendados,int *testesInc)
{
    int pos = 0,numUtentePos = 0,posM = 0;

    do
    {
        switch (opcaoTeste)
        {
        case 'A':
            vetorDinamicoTestesCovid = agendarTeste(vetorDinamicoTestesCovid,totalTestes,testesAgendados,vetorMembros,*totalMembros);
            break;
        case 'L':
            listarTestesCovid(vetorDinamicoTestesCovid,totalTestes);
            break;
        case 'D':
            alterarDataAgendada(vetorDinamicoTestesCovid,*totalTestes);
            break;
        case 'R':
            pos = registarResultado(vetorDinamicoTestesCovid,*totalTestes,testesAgendados); //Regista o resultado do teste agendado e devolve a posicao no vetor

            if(vetorDinamicoTestesCovid != NULL)//Feita a verificacao, pois o programa crasha se for selecionada uma opcao com o vetor a NULL
            {
                numUtentePos = vetorDinamicoTestesCovid[pos].numeroUtente;//Guarda o n de utente que registou o teste
                posM = procuraMembro(vetorMembros,*totalMembros,numUtentePos);//Procura o n de utente no vetor dos membros
                vetorMembros[posM].testesRealizados++;//Incrementa a variavel testes realizados do membro do teste registado
                if(pos != 0)
                {
                    escreverFicheiroLog(vetorDinamicoTestesCovid,vetorMembros,totalMembros,pos);//Escreve as informacoes do membro e o teste realizado num ficheiro texto
                }

                if (vetorDinamicoTestesCovid[pos].resultado == 3)//Verifica se o teste e inconclusivo
                {
                    (*testesInc)++;//Incrementa a var testes inconclusivos
                    vetorMembros[posM].estadoConfinamento = 2;//Altera o estado de confinamento do membro com teste inconclusivo
                    vetorMembros[posM].dataConfinamento = vetorDinamicoTestesCovid[pos].dataTeste; //A data de confinamento e igual a data do teste inconclusivo
                    printf("\n\tInsira a duracao do confinamento (em dias): ");
                    vetorMembros[posM].duracaoConfinamento = lerInteiro(1,9999);
                    printf("\n");
                    vetorDinamicoTestesCovid = agendarTesteAposResultado(vetorDinamicoTestesCovid,totalTestes,testesAgendados,pos);//Agenda um teste apos a realizacao de um teste inconclusivo
                }
                else if(vetorDinamicoTestesCovid[pos].resultado == 1 && vetorDinamicoTestesCovid[pos].tipoTeste == 2)//Verifica se o teste e positivo e antigenio
                {
                    vetorDinamicoTestesCovid = agendarTesteAposResultado(vetorDinamicoTestesCovid,totalTestes,testesAgendados,pos);//Agenda um teste PCR
                }
                if(vetorDinamicoTestesCovid[pos].resultado == 1)//Verifica se o teste e positivo
                {
                    vetorMembros[posM].testesPos++;//Incrementa a var testes positivos do membro
                    vetorMembros[posM].estadoConfinamento = 3;//Altera o estado de confinamento para Isolamento
                    vetorMembros[posM].dataConfinamento = vetorDinamicoTestesCovid[pos].dataTeste;
                    printf("\n\tInsira a duracao do confinamento (em dias): ");
                    vetorMembros[posM].duracaoConfinamento = lerInteiro(1,9999);
                }
            }
            break;
        case 'X':
            apresentarInfoTeste(vetorDinamicoTestesCovid,totalTestes,totalMembros,vetorMembros);
            break;

        }

    }
    while(opcaoTeste != 'S' && opcaoTeste !='A' && opcaoTeste != 'L' && opcaoTeste !='D' && opcaoTeste !='R' && opcaoTeste !='B' && opcaoTeste !='X');

    return vetorDinamicoTestesCovid;
}

char subMenuFicheiros(void)
{
    char opcao;

    do
    {
        printf("=================================================[Menu Ficheiros]=======================================================\n\n");
        printf("\tA - Armazenar dados de membros e testes agendados\n");
        printf("\tL - Ler dados de membros e testes agendados\n");
        printf("\tS - Sair\n\n\tOpcao---> ");
        scanf("%c", &opcao);
        opcao = toupper(opcao);
        limpaBufferStdin();
    }
    while(opcao != 'A' && opcao != 'L' && opcao != 'S');

    return opcao;
}

tipoTestesCovid *opcaosubMenuFicheiros(char opcaoFicheiro,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros,tipoTestesCovid *vetorDinamicoTestesCovid, int *totalTestes,int *testesAgendados)
{
    int totalRealizados;

    do
    {
        switch (opcaoFicheiro)
        {
        case 'A':
            vetorDinamicoTestesCovid = armazenarFicheiroTestesEMembros(vetorDinamicoTestesCovid,totalTestes,vetorMembros,totalMembros);
            break;
        case 'L':
            vetorDinamicoTestesCovid = lerFicheiroTestesEMembros(vetorDinamicoTestesCovid,totalTestes,vetorMembros,totalMembros);
            break;
        }

    }
    while(opcaoFicheiro != 'S' && opcaoFicheiro != 'A' && opcaoFicheiro != 'L');

}

void subMenuDadosEstatisticos(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *estudantes,int *docentes,int *tecnicos,tipoTestesCovid *vdTestesCovid,int totalTestes, int testesAgendados,int testesInc)
{
    char opcao;
    float tempoMedio = 0;
    float perc = 0;

    do
    {
        printf("=================================================[Dados Estatisticos]===================================================\n\n");
        printf("\t[Quantidade de tipo de membros]\t\t\t\t[%% de testes inconclusivos]\n");
        testesInc = contadorTestesInc(vdTestesCovid,totalTestes);//Conta os testes inconclusivos e devolve o valor
        perc = percTestesInc(vdTestesCovid,totalTestes,testesInc,testesAgendados);//calcula a perc de testes inconclusivos
        contadorTipoMembro(vMembros,totalMembros,estudantes,docentes,tecnicos);//conta os tipos de membros
        printf("\tEstudantes: %d\t\t\t\t\t\t%.2f%% inconclusivos\n",*estudantes,perc);
        tempoMedio = tempoMedioDuracao(vdTestesCovid,testesAgendados,totalTestes);//calcula o tempo medio de deuracao de cada teste realizado
        printf("\tDocentes: %d\n",*docentes);
        printf("\tTecnicos: %d\t\t\t\t\t\t[Tempo medio de duracao de cada teste]",*tecnicos);
        printf("\t\t\t\t\t\t\t\t\t\t%.2f minutos",tempoMedio);
        *estudantes = 0;    //E necessario colocar os contadores a 0, porque se o menu for apresentado outra vez iria incrementar aos valores anteriores
        *docentes = 0;
        *tecnicos = 0;
        printf("\n\t[Membro(s) com menor numero de testes realizados]\n");
        menorQuantTestesRealizados(vMembros,totalMembros);//Escreve o(s) membros com menor n de testes realizados
        printf("\n\t[Teste(s) realizado(s) mais recentemente]\n");
        testeMaisRecente(vdTestesCovid,totalTestes,testesAgendados);//Escreve o(s) membros com o(s) testes mais recentes
        printf("\n\n\tS - Sair\n\n\tOpcao---> ");
        scanf("%c", &opcao);
        opcao = toupper(opcao);
        limpaBufferStdin();

    }
    while(opcao != 'S');

}
