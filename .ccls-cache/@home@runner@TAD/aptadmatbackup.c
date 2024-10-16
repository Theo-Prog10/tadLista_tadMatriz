// gcc aptadmat.c tadmatriz.c tadlista.c -o main.bin -Wall && ./main.bin

#include "tadlista.h"
#include "tadmatriz.h"
#include <stdio.h>
#include <string.h>

int main() {

    FILE *arq;
    char linha[32];
    char *token;
    const char s[2] = " ";
    char nome[20];
    char sinal1[3] = "@";
    char sinal2[3] = "@";
    char letra1[3];
    char letra2[3];
    char nome_saida[30];
    Lista lista_linha;

    tadmat mat1, mat2, res;

    arq = fopen("./matops.txt", "rt");

    while (!feof(arq)) {
        lista_linha = criaLista();
        strcpy(sinal1, "@");
        strcpy(sinal2, "@");
        fgets(linha, 32, arq);
        if (linha[strlen(linha) - 1] == '\n')
            linha[strlen(linha) - 1] = '\0';

        token = strtok(linha, s);

        appendLista(lista_linha, token);
        while (token != NULL) {
            token = strtok(NULL, s);
            appendLista(lista_linha, token);
        }

        // carregando as matrizes

        // matriz 1
        if (strlen(dadoLista(lista_linha, 0)) == 1) {
            strcpy(letra1, dadoLista(lista_linha, 0));
            strcpy(nome, "./");
            strcat(nome, letra1);
            strcat(nome, ".txt");
            mat1 = carrega_mat(nome);
        }
        else {
            strcpy(letra1,dadoLista(lista_linha, 0));
            letra1[0] = letra1[1];
            letra1[1] = '\0';
            strcpy(sinal1, dadoLista(lista_linha, 0));
            sinal1[1] = '\0';

            strcpy(nome, "./");
            strcat(nome, letra1);
            strcat(nome, ".txt");
            if (!strcmp(sinal1, "-")) {
                mat1 = carrega_mat(nome);
                mat1 = neg_mat(mat1);
            }
            else if (!strcmp(sinal1, "T")) {
                mat1 = carrega_mat(nome);
                mat1 = transp_mat(mat1);
            }
        }

        // matriz 2
        if (strlen(dadoLista(lista_linha, 2)) == 1) {
            strcpy(letra2, dadoLista(lista_linha, 2));
            strcpy(nome, "./");
            strcat(nome, letra2);
            strcat(nome, ".txt");
            mat2 = carrega_mat(nome);
        }
        else {

            strcpy(letra2,dadoLista(lista_linha, 2));
            letra2[0] = letra2[1];
            letra2[1] = '\0';
            strcpy(sinal2, dadoLista(lista_linha, 2));
            sinal2[1] = '\0';

            strcpy(nome, "./");
            strcat(nome, letra2);
            strcat(nome, ".txt");

            mat2 = carrega_mat(nome);


            if (!strcmp(sinal2, "-")) {
                mat2 = neg_mat(mat2);
            }
            else if (!strcmp(sinal2, "T")) {
                mat2 = transp_mat(mat2);
            }
        }

        // realizando as operações

        if (!strcmp(dadoLista(lista_linha, 1), "+")) {

            res = soma_mat(mat1, mat2);

            strcpy(nome_saida, "./");
            if (strcmp(sinal1, "@")) {
                if (!strcmp(&sinal1[0], "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal1, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra1);
            strcat(nome_saida, "mais");
            if (strcmp(sinal2, "@")) {
                if (!strcmp(sinal2, "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal2, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra2);
            strcat(nome_saida, ".txt");
            salva_mat(res, nome_saida);
        }

        else if (!strcmp(dadoLista(lista_linha, 1), "-")) {

            res = soma_mat(mat1, neg_mat(mat2));

            strcpy(nome_saida, "./");
            if (strcmp(sinal1, "@")) {
                if (!strcmp(&sinal1[0], "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal1, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra1);
            strcat(nome_saida, "menos");
            if (strcmp(sinal2, "@")) {
                if (!strcmp(sinal2, "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal2, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra2);
            strcat(nome_saida, ".txt");
            salva_mat(res, nome_saida);
        }


        else if (!strcmp(dadoLista(lista_linha, 1), "x")){
            res = multi_mat(mat1, mat2);

            strcpy(nome_saida, "./");
            if (strcmp(sinal1, "@")) {
                if (!strcmp(&sinal1[0], "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal1, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra1);
            strcat(nome_saida, "vezes");
            if (strcmp(sinal2, "@")) {
                if (!strcmp(sinal2, "-"))
                    strcat(nome_saida, "menos");
                else if (!strcmp(sinal2, "T"))
                    strcat(nome_saida, "transp");
            }
            strcat(nome_saida, letra2);
            strcat(nome_saida, ".txt");
            salva_mat(res, nome_saida);
        }
        puts(nome_saida);
        printa_mat(res);
        printf("\n");
    }
    puts("PROGRAMA RODADO COM SUCESSO!!!!\n");
    return 0;
}