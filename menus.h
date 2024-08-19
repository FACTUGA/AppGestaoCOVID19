#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "estruturas.h"


char menu(int *totalMembros, int *testesAgendados, int *totalVacinados, int *totalTestes);
char subMenuMembros(void);
void opcaosubMenuMembros(char opcaoMembro, tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros, int *totalVacinados,tipoTestesCovid *vetorDinamicoTestesCovid,int totalTestes);
char subMenuTestes(void);
tipoTestesCovid *opcaosubMenuTestes(char opcaoTeste,tipoTestesCovid *vetorDinamicoTestesCovid,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros, int *totalTestes, int *testesAgendados,int *testesInc);
char subMenuFicheiros(void);
tipoTestesCovid *opcaosubMenuFicheiros(char opcaoFicheiro,tipoMembrosAcademicos vetorMembros[MAX_MEMBROS], int *totalMembros,tipoTestesCovid *vetorDinamicoTestesCovid, int *totalTestes,int *testesAgendados);
void subMenuDadosEstatisticos(tipoMembrosAcademicos vMembros[MAX_MEMBROS],int totalMembros,int *estudantes,int *docentes,int *tecnicos,tipoTestesCovid *vdTestesCovid,int totalTestes, int testesAgendados,int testesInc);

#endif // MENUS_H_INCLUDED
