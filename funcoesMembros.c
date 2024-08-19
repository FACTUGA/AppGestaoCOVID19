#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcoesMembros.h"
#include "estruturas.h"
#include "constantes.h"
#include "funcoesAuxiliares.h"

tipoMembrosAcademicos lerInfoMembro(void)
{
    tipoMembrosAcademicos vMembros;
    printf("\tN Utente (1 - 9999): ");
    vMembros.numeroUtente = lerInteiro(1,9999);
    printf("\tNome: ");
    lerString(vMembros.nome, MAX_STRING);
    printf("\tTipo de membro (1-Estudante/2-Docente/3-Tecnico) : ");
    vMembros.tipoMembro = lerInteiro(1,3);
    printf("\tData de nascimento (yyyy-mm-dd): \t");
    vMembros.dataNascimento = lerData();
    printf("\tEstado de confinamento (1-Nao confinado/2-Quarentena/3-Isolamento) : ");
    vMembros.estadoConfinamento = lerInteiro(1,3);
    printf("\tEstado de vacinacao (nao vacinado = 0/dose1 = 1/dose2 = 2/dose3 = 3) : \t");
    vMembros.estadoVacinacao = lerInteiro(0,MAX_DOSE);

    if(vMembros.estadoVacinacao != 0)
    {
        printf("\tData da ultima vacina : ");
        vMembros.ultimaVacina = lerData();
    }


    return vMembros;

}

int procuraMembro(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros, int numMembro)           //VetorMembros + total de membros armazenados +  numero de membro a procurar
{
    int i, pos;
    pos = -1;

    for(i=0; i < totalMembros; i++)
    {
        if(vMembros[i].numeroUtente == numMembro)
        {
            pos = i;
            i = totalMembros;

        }
    }
    return pos;                                                                                 //Se encontrar devolve a pos do membro, Senao devolve -1
}

void registarMembro(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros,int *totalVacinados)
{
    int pos;
    tipoMembrosAcademicos dados;

    if(*totalMembros == MAX_MEMBROS)
    {
        printf("\n\tErro: Nao ha espaco para mais membros!.\n");
    }
    else
    {
        dados = lerInfoMembro();
        pos = procuraMembro(vetorMembros,*totalMembros,dados.numeroUtente);
        if ( pos != -1)
        {
            printf("\n\tErro: Membro ja existente!\n");
        }
        else
        {
            vetorMembros[*totalMembros] = dados;
            if(vetorMembros[*totalMembros].estadoVacinacao != 0)
            {
                (*totalVacinados)++;
            }

            (*totalMembros)++;


        }

    }

}

int procuraNumUtente(tipoTestesCovid *vdTestesCovid,int numUtente,int totalTestes)
{
    int i, pos;
    pos = -1;

    for(i=0; i < totalTestes; i++)
    {
        if(vdTestesCovid[i].numeroUtente == numUtente)
        {
            pos = i;
            i = totalTestes;

        }
    }
    return pos;                                                                                 //Se encontrar devolve a pos do membro, Senao devolve -1

}


void listarMembros(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros,tipoTestesCovid *vdTestesCovid, int totalTestes)
{
    int j;
    if(*totalMembros <= 0)
    {
        printf("\n\tErro: Nao existem Membros inseridos na Base de Dados\n");
    }
    else
    {
        for(int i=0; i < *totalMembros; i++)
        {
            printf("\n\tN utente: %d\n",vetorMembros[i].numeroUtente);
            printf("\tNome: %s\n",vetorMembros[i].nome);
            printf("\tData de nascimento do utente: %02d-%02d-%02d\n",vetorMembros[i].dataNascimento.dia, vetorMembros[i].dataNascimento.mes, vetorMembros[i].dataNascimento.ano);
            if(vetorMembros[i].tipoMembro == 1)
            {
                printf("\tTipo de membro: Estudante\n");
            }
            else
            {
                if(vetorMembros[i].tipoMembro == 2)
                {
                    printf("\tTipo de membro: Docente\n");
                }
                else
                {
                    printf("\tTipo de membro: Tecnico\n");
                }
            }

            if(vetorMembros[i].estadoConfinamento == 1)
            {
                printf("\tEstado do confinamento: Nao confinado\n");
            }
            else
            {
                if(vetorMembros[i].estadoConfinamento == 2)
                {
                    printf("\tEstado do confinamento: Quarentena\n");
                }
                else
                {
                    printf("\tEstado do confinamento: Isolamento profilatico\n");
                }
            }
            printf("\tEstado de vacinacao: dose %d\n",vetorMembros[i].estadoVacinacao);
            if (vetorMembros[i].estadoVacinacao == 0)
            {
                printf("\t[Membro nao vacinado, logo nao tem data de ultima vacina]\n");
            }
            else
            {
                printf("\tData da ultima vacina: %02d-%02d-%02d\n",vetorMembros[i].ultimaVacina.dia,vetorMembros[i].ultimaVacina.mes,vetorMembros[i].ultimaVacina.ano);

            }
            printf("\n\tTotal de testes realizados: %d\n",vetorMembros[i].testesRealizados);
            if (vdTestesCovid != NULL)
            {
                j = procuraNumUtente(vdTestesCovid,vetorMembros[i].numeroUtente,totalTestes);

                if(vdTestesCovid[j].estado == 1 && totalTestes > 0)
                {
                    printf("\n\tTeste %d\n",j+1);
                    if(vdTestesCovid[j].tipoTeste == 1)
                    {
                        printf("\tTipo de teste: PCR\n");
                    }
                    else
                    {
                        printf("\tTipo de teste: Antigenio\n");
                    }

                    printf("\tData de agendamento: %02d-%02d-%02d\n",vdTestesCovid[j].dataTeste.dia,vdTestesCovid[j].dataTeste.mes,vdTestesCovid[j].dataTeste.ano);

                }
            }




        }

    }
}

void registarAtualizarEstadoVacinacao(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros,int *totalVacinados)
{
    int numeroUtente, pos, vacinacao, dose;
    printf("\n\tIntroduza N de utente: ");
    numeroUtente = lerInteiro(1,9999);
    pos = procuraMembro(vMembros,totalMembros,numeroUtente);
    if(pos == -1)
    {
        printf("\n\tErro: Membro nao resgistado.\n");
    }
    else
    {
        vacinacao = vMembros[pos].estadoVacinacao;
        printf("\tInsira a dose a ser administrada: ");
        dose = lerInteiro(0,MAX_DOSE);
        if(vacinacao == dose)
        {
            printf("\tErro: Dose identica.\n");

        }
        else
        {
            if(vMembros[pos].estadoVacinacao == 0 && dose != 0)
            {
                (*totalVacinados)++;
            }
            else if(vMembros[pos].estadoVacinacao != 0 && dose == 0)
            {
                (*totalVacinados)--;
            }
            if(dose != 0)
            {
                printf("\t[Data da %d dose] ",dose);
                vMembros[pos].ultimaVacina = lerData();
            }

            printf("\tEstado atualizado!\n");
            vMembros[pos].estadoVacinacao = dose;
        }


    }
}

void registarAtualizarEstadoConfinamento(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros)//Se membro nao esta confinado regista confinamento
{
    tipoMembrosAcademicos estado;
    int numeroUtente, pos;
    printf("\n\tIntroduza N de utente: ");
    numeroUtente = lerInteiro(1,9999);
    pos = procuraMembro(vMembros,totalMembros,numeroUtente);
    if(pos == -1)
    {
        printf("\n\tErro: Membro nao resgistado.\n");
    }
    else
    {
        printf("\tInsira o estado pretendido (1-Nao confinado/2-Quarentena/3-Isolamento): ");
        estado.estadoConfinamento = lerInteiro(1,3);



        if(estado.estadoConfinamento == vMembros[pos].estadoConfinamento)
        {
            printf("\n\tErro: Estado de Confinamento identico.\n");

        }
        else
        {
            if (estado.estadoConfinamento == 2)
            {
                vMembros[pos].estadoConfinamento = estado.estadoConfinamento;
                printf("\tInsira a data de confinamento (yyyy-mm-dd): ");
                vMembros[pos].dataConfinamento = lerData();
                printf("\tDuracao de confinamento (em dias): ");
                vMembros[pos].duracaoConfinamento = lerInteiro(1,9999);
                printf("\tEstado atualizado!\n");

            }
            else
            {
                if(estado.estadoConfinamento == 3)
                {
                    vMembros[pos].estadoConfinamento = estado.estadoConfinamento;
                    vMembros[pos].dataConfinamento = lerData();
                    printf("\tDuracao de confinamento (em dias): ");
                    vMembros[pos].duracaoConfinamento = lerInteiro(1,9999);
                    printf("\tEstado atualizado!\n");

                }
                else
                {
                    if(estado.estadoConfinamento == 1)
                    {
                        vMembros[pos].estadoConfinamento = estado.estadoConfinamento;
                        printf("\n\tEstado atualizado!\n");
                    }
                    else
                    {
                        printf("\n\tErro: Estado invalido!");
                    }
                }
            }



        }


    }
}

void listarCasosConfinamento(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS],int totalMembros)
{
    int varC;//Se = totalmembros os membros existentes no programa  nao estao confinados
    if(totalMembros <= 0)
    {
        printf("\n\tErro: Nao existem Membros inseridos na Base de Dados.\n");
    }
    else
    {

        for(int i=0; i < totalMembros; i++)
        {
            if(vetorMembros[i].estadoConfinamento != 1)
            {
                printf("\n\tNumero de utente: %d\n",vetorMembros[i].numeroUtente);
                if(vetorMembros[i].estadoConfinamento == 2)
                {

                    printf("\tEstado do confinamento: Quarentena\n");
                }
                else
                {
                    if(vetorMembros[i].estadoConfinamento == 3)
                    {
                        printf("\tEstado do confinamento: Isolamento profilatico\n");
                    }

                }
                printf("\tData de confinamento: %02d-%02d-%02d\n",vetorMembros[i].dataConfinamento.dia, vetorMembros[i].dataConfinamento.mes, vetorMembros[i].dataConfinamento.ano);
                printf("\tDuracao de confinamento: %d dias\n",vetorMembros[i].duracaoConfinamento);
            }
            else
            {
                varC++;
            }


        }
        if(varC == totalMembros)
        {
            printf("\n\tNao existem membros confinados.\n");
        }

    }
}

void contadorTipoMembro(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *estudantes,int *docentes, int *tecnicos)//conta o tipo dos membros
{
    for(int i=0; i < totalMembros; i++)
    {
        if(vMembros[i].tipoMembro == 1)
        {
            (*estudantes)++;
        }
        else
        {
            if(vMembros[i].tipoMembro == 2)
            {
                (*docentes)++;
            }
            else
            {
                (*tecnicos)++;
            }
        }
    }
}

void contadorVacinados(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *totalVacinados)//conta o total de vacinados
{
    int i;
    *totalVacinados = 0;
    for(i=0; i<totalMembros; i++)
    {
        if(vMembros[i].estadoVacinacao != 0)
        {
            (*totalVacinados)++;
        }
    }

}
