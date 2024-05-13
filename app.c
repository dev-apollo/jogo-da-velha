#include <stdlib.h>
#include <stdio.h>

void criarTabuleiro(int matriz[3][3]){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(matriz[i][j] == 2){
                if(j == 2) printf(" \n");
                else printf(" |");
            }else if(matriz[i][j] == 1){
                if(j == 2) printf("x\n");
                else printf("x|");
            }else if(matriz[i][j] == 3){
                if(j == 2) printf("o\n");
                else printf("o|");
            }
        }
    }
}

int calcularPesos(int matriz[3][3]){
    int pesos[8], maiorValor = 0, maiorEspaco = 0, menorValor = 30, menorEspaco = 0;
    pesos[0] = matriz[0][0]*matriz[0][1]*matriz[0][2];
    pesos[1] = matriz[1][0]*matriz[1][1]*matriz[1][2];
    pesos[2] = matriz[2][0]*matriz[2][1]*matriz[2][2];
    pesos[3] = matriz[0][0]*matriz[1][0]*matriz[2][0];
    pesos[4] = matriz[0][1]*matriz[1][1]*matriz[2][1];
    pesos[5] = matriz[0][2]*matriz[1][2]*matriz[2][2];
    pesos[6] = matriz[0][0]*matriz[1][1]*matriz[2][2];
    pesos[7] = matriz[0][2]*matriz[1][1]*matriz[2][0];
    for (int i = 0; i < 8; i++){
        if(pesos[i] > maiorValor){
            maiorValor = pesos[i];
            maiorEspaco = i;
        }
        if(pesos[i] < menorValor){
            menorValor = pesos[i];
            menorEspaco = i;
        }
    }
    if(maiorValor >= 12 & menorValor > 2) return maiorEspaco;
    else return menorEspaco;
}

void jogadaMaquina(int matriz[3][3]){
    int espaco = calcularPesos(matriz);
    switch (espaco){
    case 0:
        for(int i = 0; i < 3; i++){
            if(matriz[0][i] == 2){
                matriz[0][i] = 1;
                break;
            }
        }
        break;
    case 1:
        for(int i = 0; i < 3; i++){
            if(matriz[1][i] == 2){
                matriz[1][i] = 1;
                break;
            }
        }
        break;
    case 2:
        for(int i = 0; i < 3; i++){
            if(matriz[2][i] == 2){
                matriz[2][i] = 1;
                break;
            }
        }
        break;
    case 3:
        for(int i = 0; i < 3; i++){
            if(matriz[i][0] == 2){
                matriz[i][0] = 1;
                break;
            }
        }
        break;
    case 4:
        for(int i = 0; i < 3; i++){
            if(matriz[1][i] == 2){
                matriz[1][i] = 1;
                break;
            }
        }
        break;
    case 5:
        for(int i = 0; i < 3; i++){
            if(matriz[2][i] == 2){
                matriz[2][i] = 1;
                break;
            }
        }
        break;
    case 6:
        for(int i = 0; i < 3; i++){
            if(matriz[i][i] == 2){
                matriz[i][i] = 1;
                break;
            }
        }
        break;
    case 7:
        for(int i = 0, j = 2; i < 3; i++, j--){
            if(matriz[i][j] == 2){
                matriz[i][j] = 1;
                break;
            }
        }
        break;
    }
}

int verificarVitoria(int matriz[3][3]){
    int pesos[8], empate = 0;
    pesos[0] = matriz[0][0]*matriz[0][1]*matriz[0][2];
    pesos[1] = matriz[1][0]*matriz[1][1]*matriz[1][2];
    pesos[2] = matriz[2][0]*matriz[2][1]*matriz[2][2];
    pesos[3] = matriz[0][0]*matriz[1][0]*matriz[2][0];
    pesos[4] = matriz[0][1]*matriz[1][1]*matriz[2][1];
    pesos[5] = matriz[0][2]*matriz[1][2]*matriz[2][2];
    pesos[6] = matriz[0][0]*matriz[1][1]*matriz[2][2];
    pesos[7] = matriz[0][2]*matriz[1][1]*matriz[2][0];
    for(int i = 0; i < 8; i++){
        if(pesos[i] == 27) return 3;
        else if(pesos[i] == 1) return 1;
    }
    for(int i = 0; i < 3; i++){
        if(matriz[i][0] != 2) empate++;
        if(matriz[i][1] != 2) empate++;
        if(matriz[i][2] != 2) empate++;
    }
    if(empate == 9) return 2;
    else return 0;
}

int main(){
    int continuar = 0;
    while(continuar == 0){
        int vitoria = 0, linha, coluna, matriz[3][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
        do{
            criarTabuleiro(matriz);
            printf("Insira a linha do espa%co que deseja preencher (1, 2, 3):\n", 135);
            scanf("%d", &linha);
            printf("Insira a coluna do espa%co que deseja preencher (1, 2, 3):\n", 135);
            scanf("%d", &coluna);
            if(linha < 4 & linha > 0 & coluna < 4 & coluna > 0){
                if(matriz[linha-1][coluna-1] != 2){
                    printf("Por favor, escolha um espa%co vazio.", 135);
                }else{
                    matriz[linha-1][coluna-1] = 3;
                    jogadaMaquina(matriz);
                    vitoria = verificarVitoria(matriz);
                }
            }else{
                printf("Por favor, insira apenas valores entre 1 e 3.\n");
            }
        }while(vitoria == 0);
        criarTabuleiro(matriz);
        if(vitoria == 3) printf("Parab%cns jogador! Voc%c ganhou.", 130, 136);
        else if(vitoria == 1) printf("Novamente o computador demonstra sua superioridade perante o humano.");
        else printf("Empate, entretanto voc%c, jogador, poderia ter muito bem ganhado.", 136);
        do{
            printf("\nDeseja jogar novamente?\n[0] - Jogar novamente\n[1] - Sair\n");
            scanf("%d", &continuar);
        }while(continuar != 1 && continuar != 0);
    }
}