#ifndef FUNCOESFICHEIROS_H_INCLUDED
#define FUNCOESFICHEIROS_H_INCLUDED
#include "estruturas.h"

//Funções de Ficheiros

tipoTestesCovid *armazenarFicheiroTestesEMembros(tipoTestesCovid *vdTestesCovid, int *totalTestes,tipoMembrosAcademicos vMembros[MAX_MEMBROS], int *totalMembros);
tipoTestesCovid *lerFicheiroTestesEMembros(tipoTestesCovid *vdTestesCovid, int *totalTestes,tipoMembrosAcademicos vMembros[MAX_MEMBROS], int *totalMembros);

#endif // FUNCOESFICHEIROS_H_INCLUDED

