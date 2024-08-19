#ifndef FUNCOESMEMBROS_H_INCLUDED
#define FUNCOESMEMBROS_H_INCLUDED
#include "estruturas.h"

//Funções de Membros

int procuraMembro(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros, int numMembro);
tipoMembrosAcademicos lerInfoMembro(void);
void registarMembro(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int *totalMembros,int *totalVacinados);
void listarMembros(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros,tipoTestesCovid *vdTestesCovid, int totalTestes);
void registarAtualizarEstadoVacinacao(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros, int *totalVacinados);
void registarAtualizarEstadoConfinamento(tipoMembrosAcademicos vMembros[MAX_MEMBROS], int totalMembros);
void listarCasosConfinamento(tipoMembrosAcademicos vetorMembros[MAX_MEMBROS],int totalMembros);
void contadorTipoMembro(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *estudantes,int *docentes, int *tecnicos);
int procuraNumUtente(tipoTestesCovid *vdTestesCovid,int numUtente,int totalTestes);
void contadorVacinados(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *totalVacinados);

#endif // FUNCOESMEMBROS_H_INCLUDED
