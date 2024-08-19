#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcoesMembros.h"
#include "funcoesTestes.h"
#include "estruturas.h"
#include "constantes.h"
#include "funcoesAuxiliares.h"


tipoTestesCovid *armazenarFicheiroTestesEMembros(tipoTestesCovid *vdTestesCovid, int *totalTestes,tipoMembrosAcademicos vMembros[MAX_MEMBROS], int *totalMembros)
{
    FILE *ficheiro;
    int erro, numEscritosM,numEscritosT;
    vdTestesCovid = realloc(vdTestesCovid,(*totalTestes+1)*sizeof(tipoTestesCovid));
    ficheiro = fopen("MembrosETestes.dat","wb");
    if(ficheiro == NULL)
    {
        printf("\tErro ao abrir ficheiro!!\n");
    }
    else
    {

        numEscritosM = fwrite(&(*totalMembros),sizeof(int),1,ficheiro);
        if (numEscritosM != 1)       //Confirma se foi escrito apenas 1 membro
        {
            printf("Erro ao escrever um membro\n");
        }
        else
        {
            printf("[%d] - Elemento escrito\n", numEscritosM);
        }
        numEscritosM = fwrite(vMembros,sizeof(tipoMembrosAcademicos),*totalMembros,ficheiro);
        if (numEscritosM != *totalMembros)           //Confirma se nao falta nenhum membro
        {
            printf("Erro ao escrever os membros\n");
        }
        else
        {
            printf("[%d] - Elementos escritos\n", numEscritosM);
        }
        numEscritosT = fwrite(&(*totalTestes),sizeof(int),1,ficheiro);
        if (numEscritosT != 1)       //Confirma se foi escrito apenas 1 membro
        {
            printf("Erro ao escrever um teste\n");
        }
        else
        {
            printf("[%d] - Elemento escrito\n", numEscritosT);
        }
        numEscritosT = fwrite(vdTestesCovid,sizeof(tipoTestesCovid),*totalTestes,ficheiro);
        if (numEscritosT != *totalTestes)           //Confirma se nao falta nenhum membro
        {
            printf("Erro ao escrever os membros\n");
        }
        else
        {
            printf("[%d] - Elementos escritos\n", numEscritosT);
        }

        erro = fclose(ficheiro);
        if(erro != 0)
        {
            printf("Erro %d no fecho do ficheiro\n",erro);
        }

    }
    return vdTestesCovid;
}

tipoTestesCovid *lerFicheiroTestesEMembros(tipoTestesCovid *vdTestesCovid, int *totalTestes,tipoMembrosAcademicos vMembros[MAX_MEMBROS], int *totalMembros)
{
    FILE *ficheiro;
    int erro, numEscritosM,numEscritosT;
    ficheiro = fopen("MembrosETestes.dat","rb");
    if(ficheiro == NULL)
    {
        printf("\tErro ao abrir ficheiro!!\n");
    }
    else
    {

        numEscritosM = fread(&(*totalMembros),sizeof(int),1,ficheiro);
        if (numEscritosM != 1)       //Confirma se foi escrito apenas 1 membro
        {
            printf("Erro ao ler um membro\n");
        }
        else
        {
            printf("[%d] - Elemento lido\n", numEscritosM);
        }
        numEscritosM = fread(vMembros,sizeof(tipoMembrosAcademicos),*totalMembros,ficheiro);
        if (numEscritosM != *totalMembros)           //Confirma se nao falta nenhum membro
        {
            printf("Erro ao ler os membros\n");
        }
        else
        {
            printf("[%d] - Elementos lidos\n", numEscritosM);
        }

        numEscritosT = fread(&(*totalTestes),sizeof(int),1,ficheiro);
        vdTestesCovid = realloc(vdTestesCovid,(*totalTestes+1)*sizeof(tipoTestesCovid));
        if (numEscritosT != 1)       //Confirma se foi escrito apenas 1 membro
        {
            printf("Erro ao ler um teste\n");
        }
        else
        {
            printf("[%d] - Elemento lido\n", numEscritosT);
        }
        numEscritosT = fread(vdTestesCovid,sizeof(tipoTestesCovid),*totalTestes,ficheiro);
        if (numEscritosT != *totalTestes)           //Confirma se nao falta nenhum membro
        {
            printf("Erro ao ler os testes\n");
        }
        else
        {
            printf("[%d] - Elementos lidos\n", numEscritosT);
        }
        erro = fclose(ficheiro);
        if(erro != 0)
        {
            printf("Erro %d no fecho do ficheiro\n",erro);
        }
    }

    return vdTestesCovid;
}
