// gcc aptadmat.c tadmatriz.c tadlista.c -o main.bin -Wall && ./main.bin 

/* Alunos: Eduardo Pitanga Loureiro e Theo Mischiatti Gomes */

#include "tadlista.h"
#include "tadmatriz.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// função para pegar o nome do arquivo a partir da linha do matops.txt
char* get_arq(char* letra) {
    char *nome = (char*) malloc(20 * sizeof(char));
    strcpy(nome, "./");
    strcat(nome, letra);
    strcat(nome, ".txt");
    return nome;
}

// função para gerar o nome de saída do arquivo com a operação realizada
char* get_saida(char* sinal1, char* letra1, char* sinal2, char* letra2, char* op) {
    char *nome_saida = (char*) malloc(30 * sizeof(char));
    strcpy(nome_saida, "./");
    if (strcmp(sinal1, "@")) {
        if (!strcmp(&sinal1[0], "-"))
            strcat(nome_saida, "menos");
        else if (!strcmp(sinal1, "T"))
            strcat(nome_saida, "transp");
    }
    strcat(nome_saida, letra1);
    if (!strcmp(op,"+"))
        strcat(nome_saida, "mais");
    else if (!strcmp(op,"-"))
        strcat(nome_saida, "menos");
    else if (!strcmp(op,"x"))
        strcat(nome_saida, "vezes");
    
    if (strcmp(sinal2, "@")) {
        if (!strcmp(sinal2, "-"))
            strcat(nome_saida, "menos");
        else if (!strcmp(sinal2, "T"))
            strcat(nome_saida, "transp");
    }
    strcat(nome_saida, letra2);
    strcat(nome_saida, ".txt");

    return nome_saida;
}

// função para verificar se a matriz deve ser negativa ou transposta
tadmat verifica_sinal(tadmat mat, char* sinal) {
    if (!strcmp(sinal, "-")) {
        mat = neg_mat(mat);
    }
    else if (!strcmp(sinal, "T")) {
        mat = transp_mat(mat);
    }
    return mat;
}

// função para verificar se é possível realizar tal operação com as matrizes dadas
int valido(tadmat res) {
    if (res == NULL) {
        puts("Essa operação é inválida com as matrizes informadas");
        return 0;
    }
    return 1;
}

int main() {

    FILE *arq;
    char linha[32];
    char *token;
    const char s[2] = " ";
    char nome[20];
    char sinal1[3] = "@"; // sinal "@" significa que a matriz não é transposta nem negativa
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

        /* carregando as matrizes */

        // matriz 1
        if (strlen(dadoLista(lista_linha, 0)) == 1) {
            strcpy(letra1, dadoLista(lista_linha, 0));
            strcpy(nome, get_arq(letra1));
            mat1 = carrega_mat(nome);
        }
        else {
            strcpy(letra1,dadoLista(lista_linha, 0));
            letra1[0] = letra1[1];
            letra1[1] = '\0';
            strcpy(sinal1, dadoLista(lista_linha, 0));
            sinal1[1] = '\0';

            strcpy(nome, get_arq(letra1));
            mat1 = carrega_mat(nome);

            mat1 = verifica_sinal(mat1, sinal1);
        }

        // matriz 2
        if (strlen(dadoLista(lista_linha, 2)) == 1) {
            strcpy(letra2, dadoLista(lista_linha, 2));
            strcpy(nome, get_arq(letra2));
            mat2 = carrega_mat(nome);
        }
        else {
            strcpy(letra2,dadoLista(lista_linha, 2));
            letra2[0] = letra2[1];
            letra2[1] = '\0';
            strcpy(sinal2, dadoLista(lista_linha, 2));
            sinal2[1] = '\0';

            strcpy(nome, get_arq(letra2));
            mat2 = carrega_mat(nome);

            mat2 = verifica_sinal(mat2, sinal2);
        }

        /* realizando as operações */

        // soma
        if (!strcmp(dadoLista(lista_linha, 1), "+")) {
            res = soma_mat(mat1, mat2);
            if (valido(res)) {
                strcpy(nome_saida, get_saida(sinal1, letra1, sinal2, letra2, "+"));
                salva_mat(res, nome_saida);
            }
        }
        //subtração
        else if (!strcmp(dadoLista(lista_linha, 1), "-")) {
            res = soma_mat(mat1, neg_mat(mat2));
            if (valido(res)) {
                strcpy(nome_saida, get_saida(sinal1, letra1, sinal2, letra2, "-"));
                salva_mat(res, nome_saida);
            }
        }
        // multiplicação
        else if (!strcmp(dadoLista(lista_linha, 1), "x")){
            res = multi_mat(mat1, mat2);
            if (valido(res)) {
                strcpy(nome_saida, get_saida(sinal1, letra1, sinal2, letra2, "x"));
                salva_mat(res, nome_saida);
            }
        }
        /////////////////////remover depois/////////////////////////////////
        if (valido(res)) {
            puts(nome_saida);
            printa_mat(res);
            printf("\n");
        }
        ////////////////////////////////////////////////////////////////////
    }
    fclose(arq);
    puts("PROGRAMA RODADO COM SUCESSO!!!!\n");
    return 0;
}