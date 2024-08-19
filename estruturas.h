#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
#include "constantes.h"

typedef struct
{
    int segundos, minutos, horas;

} tipoHoras;

typedef struct
{
    int dia, mes, ano;

} tipoData;

typedef struct
{
    int numeroUtente;
    char nome[MAX_STRING];
    int tipoMembro;         //1- Estudante/2- Docente/3- Tecnico
    tipoData dataNascimento;
    int estadoConfinamento;    //1 - Não Confinado/ 2 - Quarentena/ 3 - Isolamento profilático
    tipoData dataConfinamento;
    int duracaoConfinamento;
    int estadoVacinacao;
    tipoData ultimaVacina;
    int testesRealizados;   //Guarda o total de testesRealizados pelo membro
    int testesPos;          //Guarda o total de testesPositivos do membro

} tipoMembrosAcademicos;

typedef struct
{
    char designacao[MAX_STRING];
    int tipoTeste;              //1-PCR ou 2-Antigenio
    tipoData dataTeste;
    int numeroUtente;
    int resultado;              //1-Positivo/2-Negativo/3-Inconclusivo
    tipoHoras horaColheita;     //Horas a que foi realizada a colheita
    int tempoDuracao;           //Tempo de duracao da colheita
    int estado;                 //Realizado ou Agendado

} tipoTestesCovid;



#endif // ESTRUTURAS_H_INCLUDED
