#ifndef FUNCOESTESTES_H_INCLUDED
#define FUNCOESTESTES_H_INCLUDED
#include "estruturas.h"

//Funções de Testes

int procuraPCR(tipoTestesCovid *vdTestesCovid,tipoTestesCovid dadosAux, int totalTestes,int pcr);
tipoTestesCovid lerInfoTeste(void);
tipoTestesCovid *agendarTeste(tipoTestesCovid *vdTestesCovid,int *totalTestes,int *testesAgendados,tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros);
int procuraDesignacao(tipoTestesCovid *vdTestesCovid,int totalTestes,char designacao[MAX_STRING]);
void listarTestesCovid(tipoTestesCovid *vdTestesCovid, int *totalTestes);
void alterarDataAgendada(tipoTestesCovid *vdTestesCovid, int totalTestes);
void apresentarInfoTeste(tipoTestesCovid *vdTestesCovid, int *totalTestes, int *totalMembros,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS]);
void escreverFicheiroLog(tipoTestesCovid *vdTestesCovid, tipoMembrosAcademicos vMembros[MAX_MEMBROS],int *totalMembros,int pos);
int registarResultado(tipoTestesCovid *vdTestesCovid,int totalTestes,int *testesAgendados);
tipoTestesCovid *agendarTesteAposResultado(tipoTestesCovid *vdTestesCovid,int *totalTestes,int *testesAgendados,int pos);
float tempoMedioDuracao(tipoTestesCovid*vdTestesCovid,int testesAgendados,int totalTestes);
void menorQuantTestesRealizados(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS],int totalMembros);
void testeMaisRecente(tipoTestesCovid *vdTestesCovid,int totalTestes,int total);
float percTestesInc(tipoTestesCovid *vdTestesCovid,int totalTestes,int testesInc,int testesAgendados);
void contadorTotalAgendados(tipoTestesCovid *vdTestesCovid,int totalTestes,int *testesAgendados);
int contadorTestesInc(tipoTestesCovid *vdTestesCovid,int totalTestes);

#endif // FUNCOESTESTES_H_INCLUDED
