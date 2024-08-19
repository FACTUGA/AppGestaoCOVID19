#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constantes.h"
#include "funcoesAuxiliares.h"
#include "estruturas.h"

void limpaBufferStdin(void)
{
    char lixo;
    do
    {
        lixo = getchar();
    }
    while (lixo != '\n' && lixo != EOF);
}

int lerInteiro(int min, int max)
{
    int numero, controlo;
    do
    {
        controlo = scanf("%d", &numero);
        limpaBufferStdin();
        if (numero > max || numero < min)
        {
            printf("\n\tErro: Valor fora do limite.\n\tInsira outro numero:");
        }
        else
        {
            if(controlo == 0)
            {
                printf("\n\tErro: Nao escreveu um numero.\n\tInsira um numero:");
            }
        }
    }
    while (numero<min || numero>max || controlo == 0);
    return numero;
}

void lerString(char vetor[MAX_STRING],int max)
{
    int tamanhoString;

    do  		// Repete leitura caso sejam obtidas strings vazias
    {
        fgets(vetor,max,stdin);

        tamanhoString = strlen(vetor);

        if (tamanhoString == 1)
        {
            printf("\n\tNao foram introduzidos caracteres!!! . Apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);

    if(vetor[tamanhoString-1] != '\n')   // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetor[tamanhoString-1] ='\0';          //substitui \n da string armazenada em vetor por \0 (evitar problemas com listagens)
    }
}

tipoData lerData(void)
{
    tipoData data;
    int maxDiasMes;
    printf("\n\tAno:  ");
    data.ano = lerInteiro(1900, 2050);
    printf("\tMes:  ");
    data.mes = lerInteiro(1,12);

    switch (data.mes)
    {
    case 2:
        if((data.ano % 400 == 0) || (data.ano % 4 == 0 && data.ano % 100 != 0))
        {
            maxDiasMes = 29; //Caso seja ano bisexto.
        }
        else
        {
            maxDiasMes = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiasMes = 30;
        break;
    default:
        maxDiasMes = 31;
    }
    printf("\tDia:  ");
    data.dia = lerInteiro(1, maxDiasMes);   //Leitura do dia e realizada no fim da funcao
    //porque o dia depende do mes associado.
    return data;
}

tipoHoras lerHoras(void)             //Le horas apenas aplicavel na hora de colheita e o tempo de duracao  [TO DO] - Verificacoes/Mensagens de erro
{
    tipoHoras horas;
    printf("\n\tHoras (0 - 23): ");
    horas.horas = lerInteiro(MIN_HORAS,MAX_HORAS);
    printf("\tMinutos (0 - 59): ");
    horas.minutos = lerInteiro(MIN_TEMPO,MAX_TEMPO);
    printf("\tSegundos (0 - 59): ");
    horas.segundos = lerInteiro(MIN_TEMPO,MAX_TEMPO);

    return horas;
}
