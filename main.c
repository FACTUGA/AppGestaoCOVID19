#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoesMembros.h"
#include "menus.h"
#include "constantes.h"
#include "estruturas.h"
#include "funcoesTestes.h"

int main()
{
    int totalMembros, testesAgendados, totalVacinados, estudantes, docentes, tecnicos, totalTestes, testesInc;
    char opcao, opcaoMembro, opcaoTeste, opcaoFicheiro;
    tipoMembrosAcademicos vetorMembros[MAX_MEMBROS];
    tipoTestesCovid *vetorDinamicoTestesCovid;
    totalMembros = 0;
    testesAgendados = 0;
    totalVacinados = 0;
    estudantes = 0;
    docentes = 0;
    tecnicos = 0;
    totalTestes = 0;
    testesInc = 0;
    vetorDinamicoTestesCovid = NULL;
    do
    {
        contadorVacinados(vetorMembros, totalMembros, &totalVacinados); // Conta o total de vacinados
        opcao = menu(&totalMembros, &testesAgendados, &totalVacinados, &totalTestes);
        switch (opcao)
        {
        case 'M':
            opcaoMembro = subMenuMembros(); // Apresenta o menu das op�oes dos membros e devolve a opcao selecionada pelo utilizador
            opcaosubMenuMembros(opcaoMembro, vetorMembros, &totalMembros, &totalVacinados, vetorDinamicoTestesCovid, totalTestes);
            break;
        case 'T':
            opcaoTeste = subMenuTestes(); // Apresenta o menu das op�oes dos testes e devolve a opcao selecionada pelo utilizador
            vetorDinamicoTestesCovid = opcaosubMenuTestes(opcaoTeste, vetorDinamicoTestesCovid, vetorMembros, &totalMembros, &totalTestes, &testesAgendados, &testesInc);
            break;
        case 'D':
            subMenuDadosEstatisticos(vetorMembros, totalMembros, &estudantes, &docentes, &tecnicos, vetorDinamicoTestesCovid, totalTestes, testesAgendados, testesInc);
            // Apresenta o menu dos dados estatisticos
            break;
        case 'F':
            opcaoFicheiro = subMenuFicheiros(); // Apresenta o menu das op�oes dos ficheiros e devolve a opcao selecionada pelo utilizador
            vetorDinamicoTestesCovid = opcaosubMenuFicheiros(opcaoFicheiro, vetorMembros, &totalMembros, vetorDinamicoTestesCovid, &totalTestes, &testesAgendados);
            contadorTotalAgendados(vetorDinamicoTestesCovid, totalTestes, &testesAgendados); // Conta o N total de testes agendados
            break;
        }
    } while (opcao != 'S');

    free(vetorDinamicoTestesCovid);

    return 0;
}
