#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void GerarNomeArquivo(int numArq, char * nomeArquivo)
{
    nomeArquivo[0] = '\0';
    char charNumArq[10];
    itoa(numArq, charNumArq, 10);
    strcat(nomeArquivo,"./trabalho4/rev");
    strcat(nomeArquivo,charNumArq);
    strcat(nomeArquivo,".bin");
}

int LeturaArquivo(FILE * arquivo, char * maiorPalavra, char * menorPalavra, char * maiorPalavraGlobal, char * menorPalavraGlobal)
{
    char caractere = 0, palavraLida[255];
    palavraLida[0]='\0';
    int qntCarac = 0, tamMaiorPalavra = 0, tamMenorPalavra = sizeof(int)*2, qntPalavras = 0;


    while ((caractere = fgetc(arquivo)) != EOF)
    {
        if((caractere >= 'A' && caractere <='Z') || (caractere >='a' && caractere <='z'))
        {
            palavraLida[qntCarac] = caractere;
            qntCarac++;
        }
        if(caractere == 32 || caractere == 46)
        {
            palavraLida[qntCarac] = '\0';
            if(qntCarac > tamMaiorPalavra && qntCarac > 0)
            {
                maiorPalavra[0]='\0';
                tamMaiorPalavra = qntCarac;
                strcpy(maiorPalavra, palavraLida);
            }
            if(qntCarac < tamMenorPalavra && qntCarac > 0)
            {
                menorPalavra[0]='\0';
                tamMenorPalavra = qntCarac;
                strcpy(menorPalavra, palavraLida);
            }
            if(qntCarac > 0)
                qntPalavras++;
            qntCarac = 0;
        }
    }
    return qntPalavras;
}

int contarParagrafos(FILE * arquivo) {
    int count = 0;
    char caracter, caracterAntigo = '\0';

    while ((caracter = fgetc(arquivo)) != EOF) {
        if (caracterAntigo == '\n' && caracter == '\t') {
            count++;
        }
        caracterAntigo = caracter;
    }

    count++;

    return count;
}

int main()
{
    int qntArq = 0;
    double mediaPalavra, mediaParagrafo, qntPalavras = 0, qntParagrafo = 0;
    FILE *arquivo;
    char MenorPalavraGlobal[255], MaiorPalavraGlobal[255];

    do
    {
    qntArq++;
    char nomeArquivo[100], MaiorPalavraLocal[255], MenorPalavraLocal[255];
    GerarNomeArquivo(qntArq, nomeArquivo);
    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL)
        {
            printf("INFO - Foram lidos %d arquvios\n", qntArq - 1);
            break;
        }
    qntPalavras += LeturaArquivo(arquivo, MaiorPalavraLocal, MenorPalavraLocal, MaiorPalavraGlobal, MenorPalavraGlobal);
    qntParagrafo += contarParagrafos(arquivo);
    printf("INFO - Maior palavra do arquivo %d: %s\n", qntArq, MaiorPalavraLocal);
    printf("INFO - Menor palavra do arquivo %d: %s\n\n", qntArq, MenorPalavraLocal);
    }while (1 || qntArq > 1);
    mediaPalavra = qntPalavras/(4);
    mediaParagrafo = qntParagrafo/(4);

    printf("Qnt palavras lidas: %.0lf\n", qntPalavras);
    printf("Qnt paragrafos lidas: %.0lf\n\n", qntParagrafo);

    printf("1) Media do numero de palavras por review: %.1lf\n", mediaPalavra);
    printf("2) Media do numero de paragrafos por review: %.1lf\n", mediaParagrafo);
    printf("3) Maior palavra: %s\n", MaiorPalavraGlobal);
    printf("4) Menor palavra: %s\n", MenorPalavraGlobal);
    return 0;
}
