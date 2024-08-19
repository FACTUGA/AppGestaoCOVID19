#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcoesMembros.h"
#include "estruturas.h"
#include "constantes.h"
#include "funcoesAuxiliares.h"


tipoTestesCovid lerInfoTeste(void)
{
    tipoTestesCovid vdTestesCovid;

    printf("\tNumero de utente (1 - 9999) : \t");
    vdTestesCovid.numeroUtente = lerInteiro(1,9999);
    printf("\tDesignacao: ");
    lerString(vdTestesCovid.designacao,MAX_STRING);
    printf("\tTipo de teste (1-PCR/2-Antigenio): ");
    vdTestesCovid.tipoTeste = lerInteiro(1,2);
    printf("\tData de agendamento pretendida (yyyy-mm-dd): ");
    vdTestesCovid.dataTeste = lerData();
    vdTestesCovid.estado = 1;

    return vdTestesCovid;
}

int procuraDesignacao(tipoTestesCovid *vdTestesCovid,int totalTestes,char designacao[MAX_STRING])//procura se a designacao do teste existe
{
    int i, pos;
    pos = -1;
    for(i=0; i < totalTestes; i++)
    {
        if(strcmp(vdTestesCovid[i].designacao,designacao) == 0)
        {
            pos = i;
            i = totalTestes;
        }
    }
    return pos;
}

int procuraPCR(tipoTestesCovid *vdTestesCovid,tipoTestesCovid dadosAux, int totalTestes,int pcr)          //Procura o dia e conta o n de pcrs associados
{
    int i;
    for(i=0; i < totalTestes; i++)
    {
        if(vdTestesCovid[i].dataTeste.ano == dadosAux.dataTeste.ano && vdTestesCovid[i].dataTeste.dia == dadosAux.dataTeste.dia && vdTestesCovid[i].dataTeste.mes == dadosAux.dataTeste.mes)
        {
            pcr++;
        }
    }

    return pcr;
}

tipoTestesCovid *agendarTeste(tipoTestesCovid *vdTestesCovid,int *totalTestes,int *testesAgendados,tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros)
{
    tipoTestesCovid dadosAux;
    int pcr,pos;

    pcr = 1;   //pcr e inicializado a 1 porque a data do teste nao e inserida no vdTestesCovid, logo ao procurar a primeira vez nao vai incrementar a variavel pcr
    pos = 0;
    vdTestesCovid = realloc(vdTestesCovid,(*totalTestes+1)*sizeof(tipoTestesCovid));
    if(vdTestesCovid == NULL)
    {
        printf("Memoria insuficiente.\n");
    }
    else
    {
        dadosAux = lerInfoTeste();
        pos = procuraMembro(vMembros,totalMembros,dadosAux.numeroUtente);

        if(pos == -1)
        {
            printf("\n\tErro: Membro nao existente.\n");
        }
        else
        {
            pos = 0;        //Reset na variavel pos pois vai ser utilizada outra vez

            pos = procuraDesignacao(vdTestesCovid,*totalTestes,dadosAux.designacao);
            if(pos != -1)
            {
                printf("\n\tErro: Teste ja existe.\n");
            }
            else
            {
                if(dadosAux.tipoTeste == 1)
                {
                    pcr = procuraPCR(vdTestesCovid,dadosAux,*totalTestes,pcr);

                    if(pcr<=MAX_PCR)
                    {
                        printf("\n\tTeste PCR agendado.\n");
                        vdTestesCovid[*totalTestes] = dadosAux;
                        (*totalTestes)++;
                        (*testesAgendados)++;
                    }
                    else
                    {
                        printf("\n\tErro: Cota diaria de testes PCR excedida.\n");
                    }

                }
                else
                {
                    printf("\n\tTeste antigenio agendado.\n");
                    vdTestesCovid[*totalTestes] = dadosAux;
                    (*totalTestes)++;
                    (*testesAgendados)++;

                }

            }

        }
    }
    return vdTestesCovid;
}

void listarTestesCovid(tipoTestesCovid *vdTestesCovid, int *totalTestes)
{
    if(vdTestesCovid == NULL)
    {
        printf("Nao existem testes para listar.\n");
    }
    else
    {
        for(int i=0; i<*totalTestes; i++)
        {

            printf("\n\tDesignacao: %s\n",vdTestesCovid[i].designacao);
            printf("\tN utente: %d\n",vdTestesCovid[i].numeroUtente);
            if(vdTestesCovid[i].tipoTeste == 1)
            {
                printf("\tTipo do teste: PCR\n");
            }
            else
            {
                printf("\tTipo do teste: Antigenio\n");
            }
            if(vdTestesCovid[i].estado == 1)
            {
                printf("\tEstado do teste: Agendado\n");
                printf("\tData de agendamento do teste: %02d-%02d-%02d\n",vdTestesCovid[i].dataTeste.dia,vdTestesCovid[i].dataTeste.mes,vdTestesCovid[i].dataTeste.ano);
            }
            else
            {
                printf("\tEstado do teste: Realizado\n");
                printf("\tData da realizacao do teste: %02d-%02d-%02d\n",vdTestesCovid[i].dataTeste.dia,vdTestesCovid[i].dataTeste.mes,vdTestesCovid[i].dataTeste.ano);
                printf("\tHora da realizacao do teste: %02d:%02d:%02d\n", vdTestesCovid[i].horaColheita.horas, vdTestesCovid[i].horaColheita.minutos, vdTestesCovid[i].horaColheita.segundos);
                printf("\tDuracao da colheita: %d minutos\n",vdTestesCovid[i].tempoDuracao);
            }
            if(vdTestesCovid[i].resultado == 1 && vdTestesCovid[i].estado == 2)
            {
                printf("\tResultado: Positivo\n");
            }
            else if(vdTestesCovid[i].resultado == 2 && vdTestesCovid[i].estado == 2)
            {
                printf("\tResultado: Negativo\n");
            }
            else if(vdTestesCovid[i].resultado == 3 && vdTestesCovid[i].estado == 2)
            {
                printf("\tResultado: Inconclusivo\n");
            }


        }
    }
}

int procuraData(tipoTestesCovid *vdTestesCovid,tipoTestesCovid dadosAux, int totalTestes)          //Procura o dia e conta o n de pcrs associados
{
    int i, pos = -1;

    for(i=0; i < totalTestes; i++)
    {
        if(vdTestesCovid[i].dataTeste.ano == dadosAux.dataTeste.ano && vdTestesCovid[i].dataTeste.dia == dadosAux.dataTeste.dia && vdTestesCovid[i].dataTeste.mes == dadosAux.dataTeste.mes)
        {
            pos = i;
            i = totalTestes;
        }
    }
    return pos;
}

void alterarDataAgendada(tipoTestesCovid *vdTestesCovid, int totalTestes)
{
    int pos,pcr;
    tipoTestesCovid dadosAux;


    pcr = 1;
    printf("\n\tDesignacao: ");
    lerString(dadosAux.designacao,MAX_STRING);

    pos = procuraDesignacao(vdTestesCovid,totalTestes,dadosAux.designacao);

    if(pos == -1)
    {
        printf("Nao existe essa designacao!!\n");
    }
    else
    {
        printf("\tInsira a nova data (yyyy-mm-dd): \t");
        dadosAux.dataTeste = lerData();

        if(vdTestesCovid[pos].dataTeste.ano == dadosAux.dataTeste.ano && vdTestesCovid[pos].dataTeste.mes == dadosAux.dataTeste.mes && vdTestesCovid[pos].dataTeste.dia == dadosAux.dataTeste.dia)
        {
            printf("Nao pode ser a mesma Data!\nInsira outra data (yyyy-mm-dd): \t");

            dadosAux.dataTeste = lerData();
        }
        pcr = procuraPCR(vdTestesCovid,dadosAux,totalTestes,pcr);

        if (pcr<=MAX_PCR)   //Faz a verificacao se ja existe 15 testes PCR no mesmo dia
        {
            vdTestesCovid[pos].dataTeste = dadosAux.dataTeste;
            printf("\n\tData alterada com sucesso.\n");
        }
        else
        {
            printf("\n\tErro: Cota diaria de testes PCR excedida.\n");

        }

    }

}

void apresentarInfoTeste(tipoTestesCovid *vdTestesCovid,int *totalTestes,int *totalMembros,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS])
{
    int posD,posM;
    char designacao[MAX_STRING];

    if(vdTestesCovid == NULL)
    {
        printf("\n\tErro: Nao existem testes para listar.\n");
        return;
    }
    printf("\tInsira designacao do teste: ");
    lerString(designacao,MAX_STRING);
    posD = procuraDesignacao(vdTestesCovid,*totalTestes,designacao);

    if(posD == -1)
    {
        printf("\tErro: Designacao nao eoncontrada.\n");
    }
    else
    {
        posM = procuraMembro(vetorMembros,*totalMembros,vdTestesCovid[posD].numeroUtente);
        printf("\nMembro: %d\n\n",posM+1);
        printf("\tNome de utente: %s\n",vetorMembros[posM].nome);
        if(vetorMembros[posM].tipoMembro == 1)
        {
            printf("\tTipo de membro: Estudante\n");
        }
        else
        {
            if(vetorMembros[posM].tipoMembro == 2)
            {
                printf("\tTipo de membro: Docente\n");
            }
            else
            {
                printf("\tTipo de membro: Tecnico\n");
            }

        }
        printf("\tTotal de testes positivos: %d\n",vetorMembros[posM].testesPos);
        printf("Testes\n\n");
        printf("\tDesignacao: %s\n",vdTestesCovid[posD].designacao);
        if(vdTestesCovid[posD].tipoTeste == 1)
        {
            printf("\tTipo de teste: PCR\n");
        }
        else
        {
            printf("\tTipo de teste: Antigenio\n");
        }
        printf("\tData do teste: %02d-%02d-%02d\n",vdTestesCovid[posD].dataTeste.dia,vdTestesCovid[posD].dataTeste.mes,vdTestesCovid[posD].dataTeste.ano);

        if(vdTestesCovid[posD].estado == 1)
        {
            printf("\tEstado do teste: Agendado\n");
        }
        else if(vdTestesCovid[posD].estado == 2)
        {
            printf("\tEstado do teste: Realizado\n");

            printf("\tHora da realizacao do teste: %d:%d:%d\n", vdTestesCovid[posD].horaColheita.horas, vdTestesCovid[posD].horaColheita.minutos, vdTestesCovid[posD].horaColheita.segundos);
            printf("\tDuracao da colheita: %d minutos\n",vdTestesCovid[posD].tempoDuracao);

            if(vdTestesCovid[posD].resultado == 1)
            {
                printf("\tResultado: Positivo\n");
            }
            else if(vdTestesCovid[posD].resultado == 2)
            {
                printf("\tResultado: Negativo\n");
            }
            else
            {
                printf("\tResultado: Inconclusivo\n");
            }

        }

    }
}

void escreverFicheiroLog(tipoTestesCovid *vdTestesCovid, tipoMembrosAcademicos vMembros[MAX_MEMBROS],int *totalMembros,int pos)
{
    FILE *ficheiro;
    int erro,posM;

    ficheiro = fopen("TesteRealizadoLog.txt","w");
    if(ficheiro == NULL)
    {
        printf("Erro ao abrir ficheiro!!\n");
    }
    else
    {
        posM = procuraMembro(vMembros,*totalMembros,vdTestesCovid[pos].numeroUtente);
        fprintf(ficheiro,"Numero de Utente: %d\n",vdTestesCovid[pos].numeroUtente);
        fprintf(ficheiro,"Nome: %s\n",vMembros[posM].nome);
        if(vMembros[posM].estadoVacinacao != 0)
        {
            fprintf(ficheiro,"Estado de vacinacao: Dose %d\n\n",vMembros[posM].estadoVacinacao);
        }
        else
        {
            fprintf(ficheiro,"Estado de vacinacao: Nao vacinado\n\n");
        }
        fprintf(ficheiro,"Designacao: %s\n",vdTestesCovid[pos].designacao);
        if(vdTestesCovid[pos].tipoTeste == 1)
        {
            fprintf(ficheiro,"Tipo de teste: PCR\n");
        }
        else
        {
            fprintf(ficheiro,"Tipo de teste: Antigenio\n");
        }
        fprintf(ficheiro,"Estado: Realizado\n");
        fprintf(ficheiro,"Data do teste: %02d-%02d-%02d\n",vdTestesCovid[pos].dataTeste.dia,vdTestesCovid[pos].dataTeste.mes,vdTestesCovid[pos].dataTeste.ano);
        fprintf(ficheiro,"Hora da realizacao do teste: %d:%d:%d\n", vdTestesCovid[pos].horaColheita.horas,vdTestesCovid[pos].horaColheita.minutos,vdTestesCovid[pos].horaColheita.segundos);
        fprintf(ficheiro,"Duracao da colheita: %d minutos\n",vdTestesCovid[pos].tempoDuracao);

        if(vdTestesCovid[pos].resultado == 1)
        {
            fprintf(ficheiro,"Resultado: Positivo\n");
        }
        else if(vdTestesCovid[pos].resultado == 2)
        {
            fprintf(ficheiro,"Resultado: Negativo\n");
        }
        else
        {
            fprintf(ficheiro,"Resultado: Inconclusivo\n");
        }


    }
    erro = fclose(ficheiro);
    if(erro != 0)
    {
        printf("Erro %d no fecho do ficheiro.",erro);
    }
}

int registarResultado(tipoTestesCovid *vdTestesCovid,int totalTestes,int *testesAgendados)
{
    int pos = 0;
    char auxDesignacao[MAX_STRING];
    if(vdTestesCovid == NULL)
    {
        printf("\n\tErro: Nao existem testes a ser registados.\n");
    }
    else
    {
        printf("\n\tInsira a desginacao do teste: ");
        lerString(auxDesignacao,MAX_STRING);

        pos = procuraDesignacao(vdTestesCovid,totalTestes,auxDesignacao);
        if(pos == -1)
        {
            printf("\n\tErro: Designacao nao encontrada.\n");
            pos = 0;
        }
        else
        {
            if(vdTestesCovid[pos].estado == 2)
            {
                printf("\n\tErro: Teste ja tem resultado registado.\n");
            }
            else
            {
                printf("\n\tInsira as horas da colheita (hh-mm-ss): ");
                vdTestesCovid[pos].horaColheita = lerHoras();
                printf("\n\tInsira o tempo de duracao da colheita (em minutos): ");
                vdTestesCovid[pos].tempoDuracao = lerInteiro(MIN_HORAS,MAX_HORAS);
                printf("\n\tIndique o resultado do teste (1-Positivo/2-Negativo/3-Inconclusivo): ");
                vdTestesCovid[pos].resultado = lerInteiro(1,3);
                vdTestesCovid[pos].estado = 2;
                (*testesAgendados)--;//Desincrementa os testes agendados apos o registo do resultado

                printf("\n\tResultado registado com sucesso.\n");

                if(vdTestesCovid[pos].resultado == 3)
                {
                    printf("========================================================================================================================\n\n");
                    printf("\n\tO resultado do teste foi inconclusivo. \n\tDevido as normas estabelecidas pela DGS sera necessario marcar um novo teste\n\t e colocar o membro em quarentena.\n\n");
                }
                else if(vdTestesCovid[pos].resultado == 1 && vdTestesCovid[pos].tipoTeste == 2)
                {
                    printf("========================================================================================================================\n\n");
                    printf("\n\tO resultado do teste antigenio foi positivo. \n\tDevido as normas estabelecidas pela DGS sera necessario marcar um novo teste do tipo PCR\n\t e colocar o membro em isolamento.\n\n");
                }
                else if(vdTestesCovid[pos].resultado == 1 && vdTestesCovid[pos].tipoTeste == 1)
                {
                    printf("========================================================================================================================\n\n");
                    printf("\n\tO resultado do teste PCR foi positivo. \n\tDevido as normas estabelecidas pela DGS sera necessario colocar o membro em isolamento.\n\n");

                }

            }


        }
    }

    return pos;
}

tipoTestesCovid *agendarTesteAposResultado(tipoTestesCovid *vdTestesCovid,int *totalTestes,int *testesAgendados,int pos)
{
    tipoTestesCovid dadosAux,auxDo;
    int pcr = 1;

    vdTestesCovid = realloc(vdTestesCovid,(*totalTestes+1)*sizeof(tipoTestesCovid));
    if(vdTestesCovid == NULL)
    {
        printf("Memoria insuficiente.\n");
    }
    else
    {

        dadosAux.numeroUtente = vdTestesCovid[pos].numeroUtente;//O n de utente do teste a realizar vai ser igual ao realizado
        printf("\tDesignacao: ");
        lerString(dadosAux.designacao,MAX_STRING);
        strcpy(auxDo.designacao,dadosAux.designacao);
        dadosAux.tipoTeste = 1;//Obrigatorio ser um teste PCR
        printf("\tData de agendamento pretendida (yyyy-mm-dd): ");
        dadosAux.dataTeste = lerData();
        auxDo.dataTeste = dadosAux.dataTeste;
        dadosAux.estado = 1;

        pos = 0;

        pos = procuraDesignacao(vdTestesCovid,*totalTestes,dadosAux.designacao);

        if(pos != -1)
        {
            while(strcmp(dadosAux.designacao,auxDo.designacao) == 0)
            {
                printf("\n\tErro: Teste ja existe.");
                printf("\n\tInsira outra designacao: ");
                lerString(dadosAux.designacao,MAX_STRING);
            }
        }

        pcr = procuraPCR(vdTestesCovid,dadosAux,*totalTestes,pcr);

        if(pcr<=MAX_PCR)
        {
            printf("\n\tTeste agendado.\n");
            vdTestesCovid[*totalTestes] = dadosAux;
            (*totalTestes)++;
            (*testesAgendados)++;
        }
        else
        {
            printf("\n\tErro: Cota diaria de testes PCR excedida.\n");
            while (auxDo.dataTeste.ano == dadosAux.dataTeste.ano && auxDo.dataTeste.mes == dadosAux.dataTeste.mes && auxDo.dataTeste.dia == dadosAux.dataTeste.dia)
            {
                printf("\n\tInsira outra data: ");
                dadosAux.dataTeste = lerData();
            }
            printf("\n\tTeste PCR agendado.\n");
            vdTestesCovid[*totalTestes] = dadosAux;
            (*totalTestes)++;
            (*testesAgendados)++;



        }


    }
    return vdTestesCovid;
}



float tempoMedioDuracao(tipoTestesCovid *vdTestesCovid,int testesAgendados,int totalTestes)
{
    int i;
    int testesRealizados = 0;
    float tempoTotalTestes = 0;
    float mediaDuracao = 0;
    testesRealizados = totalTestes - testesAgendados;


    for(i=0; i<totalTestes; i++)
    {
        if(vdTestesCovid[i].estado == 2)
        {
            tempoTotalTestes += (float)vdTestesCovid[i].tempoDuracao;
        }

    }

    if(testesRealizados == 0 || tempoTotalTestes == 0)//verifica se alguma das duas variaveis e igual a 0 e se for devolve a media a 0
    {
        mediaDuracao = 0;
    }
    else
    {
        mediaDuracao = tempoTotalTestes/testesRealizados;
    }



    return mediaDuracao;

}

void menorQuantTestesRealizados(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS],int totalMembros)
{
    int menorRealizados = 0, pos = 0,contaIguais = 0;

    if(totalMembros == 0)
    {
        printf("\n\tNao existem membros.\n");
    }
    else
    {
        for(int i=0; i<totalMembros; i++)
        {
            menorRealizados = vetorMembros[i].testesRealizados;//Guarda o total de testes realizados pelo primeiro membro
            pos = i;

            if(menorRealizados > vetorMembros[i].testesRealizados)//Compara o total de testes realizados com os restantes
            {
                //Se for maior o menorRealizados toma o seu valor e a var pos fica igual a i que indica a posicao do elemento no vetor
                menorRealizados = vetorMembros[i].testesRealizados;
                pos = i;
            }
            else if(menorRealizados == vetorMembros[i].testesRealizados)//Se for igual incrementa a var contaIguais
            {
                contaIguais++;
            }

        }
        if(contaIguais != 0)//Se for diferente de 0 imprime os elementos com o menor n de testes realizados iguais
        {
            for(int j = 0; j<totalMembros; j++)
            {
                if(vetorMembros[j].testesRealizados == menorRealizados)
                {
                    printf("\tMembro: %d",j+1);
                    printf("\n\tNome: %s",vetorMembros[j].nome);
                    printf("\n\tNumero de utente: %d",vetorMembros[j].numeroUtente);
                    printf("\n\tQuantidade de testes realizados: %d\n\n",vetorMembros[j].testesRealizados);
                }
            }


        }
        else//Se nao existirem elementos iguais com o menor n de testes realizados imprime o membro com menor numero
        {
            printf("\n\tMembro: %d",pos+1);
            printf("\n\tNome: %s",vetorMembros[pos].nome);
            printf("\n\tNumero de utente: %d",vetorMembros[pos].numeroUtente);
            printf("\n\tQuantidade de testes realizados: %d\n",vetorMembros[pos].testesRealizados);

        }
    }
}

void testeMaisRecente(tipoTestesCovid *vdTestesCovid,int totalTestes,int testesAgendados)
{
    int contaIguais = 0;
    int pos = 0;
    int testesRealizados = 0;
    testesRealizados = totalTestes - testesAgendados;
    tipoData dataMaisRecente;
    if (testesRealizados == 0)
    {
        printf("\n\tNao existem testes realizados.\n");
    }
    else
    {
        for(int i=0; i<totalTestes; i++)
        {
            if(vdTestesCovid[i].estado == 2)//Obtem o primeiro teste realizado no vetor
            {
                dataMaisRecente.ano = vdTestesCovid[i].dataTeste.ano;
                dataMaisRecente.mes = vdTestesCovid[i].dataTeste.mes;
                dataMaisRecente.dia = vdTestesCovid[i].dataTeste.dia;
                pos = i;
                i = totalTestes;

            }
        }
        for(int y=pos+1; y<totalTestes; y++)
        {
            if(vdTestesCovid[y].estado == 2)
            {
                if(dataMaisRecente.ano <= vdTestesCovid[y].dataTeste.ano)//Se o ano for menor ou igual passa a proxima "fase"
                {
                    if(dataMaisRecente.mes <= vdTestesCovid[y].dataTeste.mes)//Se o mes for menor ou igual passa a proxima "fase"
                    {
                        if(dataMaisRecente.dia <= vdTestesCovid[y].dataTeste.dia)//Se o dia for menor ou igual guarda os seus valores
                        {
                            dataMaisRecente.ano = vdTestesCovid[y].dataTeste.ano;
                            dataMaisRecente.mes = vdTestesCovid[y].dataTeste.mes;
                            dataMaisRecente.dia = vdTestesCovid[y].dataTeste.dia;
                            pos = y;

                            if(dataMaisRecente.ano == vdTestesCovid[y].dataTeste.ano && dataMaisRecente.mes == vdTestesCovid[y].dataTeste.mes && dataMaisRecente.dia == vdTestesCovid[y].dataTeste.dia)
                            {
                                //Se os 3 elementos forem iguais incrementa a var contaIguais
                                contaIguais++;
                            }
                        }
                    }


                }
            }
        }
        if(contaIguais != 0)//Se for diferente de 0 procura as datas iguais e imprime no ecra
        {
            for(int j=0; j<totalTestes; j++)
            {

                if(vdTestesCovid[j].dataTeste.ano == dataMaisRecente.ano && vdTestesCovid[j].dataTeste.mes == dataMaisRecente.mes && vdTestesCovid[j].dataTeste.dia == dataMaisRecente.dia)
                {
                    printf("\tTeste: %d",j+1);
                    printf("\n\tN utente: %d",vdTestesCovid[j].numeroUtente);
                    printf("\n\tData de realizacao: %02d-%02d-%02d\n\n",vdTestesCovid[j].dataTeste.dia,vdTestesCovid[j].dataTeste.mes,vdTestesCovid[j].dataTeste.ano);
                }
            }
        }
        else//Se for 0 imprime o teste guardado na var pos
        {
            printf("\tTeste: %d",pos+1);
            printf("\n\tN utente: %d",vdTestesCovid[pos].numeroUtente);
            printf("\n\tData de realizacao: %02d-%02d-%02d\n\n",vdTestesCovid[pos].dataTeste.dia,vdTestesCovid[pos].dataTeste.mes,vdTestesCovid[pos].dataTeste.ano);
        }
    }
}


float percTestesInc(tipoTestesCovid *vdTestesCovid,int totalTestes,int testesInc,int testesAgendados)//Calcula a % de testes inconclusivos
{
    float perc,testesRealizados;
    testesRealizados = 0.0;

    testesRealizados = totalTestes - testesAgendados;

    if (testesRealizados != 0)
    {
        perc = ((float)testesInc/testesRealizados)*100;
    }
    else
    {
        perc = 0.0;
    }


    return perc;
}

void contadorTotalAgendados(tipoTestesCovid *vdTestesCovid,int totalTestes,int *testesAgendados)
{
    int totalRealizados = 0;
    *testesAgendados = 0;
    for(int i = 0; i<totalTestes; i++)
    {
        if(vdTestesCovid[i].estado == 1)
        {
            (*testesAgendados)++;
        }
        else
        {
            totalRealizados++;
        }
    }

}

int contadorTestesInc(tipoTestesCovid *vdTestesCovid,int totalTestes)
{
    int testesInc = 0;
    for(int i=0; i<totalTestes; i++)
    {
        if(vdTestesCovid[i].resultado == 3)
        {
            testesInc++;
        }
    }
    return testesInc;
}
