#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int tembomba;
    int estaaberta;
    int vizinhos;
}Celula;

Celula jogo[10][10];
int tam = 10;


void inicio(void){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            jogo[i][j].tembomba = 0;
            jogo[i][j].estaaberta = 0;
            jogo[i][j].vizinhos = 0;
        }
    }
}


void sortear_bombas(void){
    srand(time(NULL));
    for(int i = 0; i < tam; i++){
        int cd1 = rand() % 10;
        int cd2 = rand() % 10;
        if(jogo[cd1][cd2].tembomba == 0){
            jogo[cd1][cd2].tembomba = 1;
        }
        else{i--;}
    }
}


int pos_valida(int i, int j){
    if(i >= 0 && i < tam && j >= 0 && j < tam){
        return 1;
    }
    else{return 0;}
}


int checar_vizinhos(int i, int j){
    int bmb = 0;
    if(pos_valida(i - 1, j)){
        if(jogo[i - 1][j].tembomba){bmb += 1;}
    }
    if(pos_valida(i + 1, j)){
        if(jogo[i + 1][j].tembomba){bmb += 1;}
    }
    if(pos_valida(i, j - 1)){
        if(jogo[i][j - 1].tembomba){bmb += 1;}
    }
    if(pos_valida(i, j + 1)){
        if(jogo[i][j + 1].tembomba){bmb += 1;}
    }
    return bmb;
}


void checar_bomba(){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            jogo[i][j].vizinhos = checar_vizinhos(i, j);
        }
    }
}


void imprimir(){
    printf("\n");
    printf("  ");
    for(int i = 0; i < tam; i++){
        printf("  %d ", i);
    }
    printf("\n  -----------------------------------------\n");
    for(int i = 0; i < tam; i++){ 
        printf("%d | ", i);
        for(int j = 0; j < tam; j++){
            if(jogo[i][j].estaaberta){
                if(jogo[i][j].tembomba){
                    printf("*");
                }
                else{
                    printf("%d", jogo[i][j].vizinhos);
                }
            }
            else{
                printf(" ");
            }
            printf(" | ");
        }
        printf("\n  -----------------------------------------\n");
    }
}


void perdeu(){
    printf("\n");
    for(int i = 0; i < tam; i++){
        printf("  %d ", i);
    }
    printf("\n  -----------------------------------------\n");
    for(int i = 0; i < tam; i++){ 
        printf("%d | ", i);
        for(int j = 0;+j < tam; j++){
            if(jogo[i][j].tembomba){
                printf("*");
            }
            else{
                printf("%d", jogo[i][j].vizinhos);
            }
            printf(" | ");
        }
        printf("\n  -----------------------------------------\n");
    }
    printf("\nVoce perdeu :(\n");
}


void abrir_celula(int coord1, int coord2){
    if(pos_valida(coord1, coord2) == 1 && jogo[coord1][coord2].estaaberta == 0){
        jogo[coord1][coord2].estaaberta = 1;
        if(jogo[coord1][coord2].vizinhos == 0){
            abrir_celula(coord1 - 1, coord2);
            abrir_celula(coord1 + 1, coord2);
            abrir_celula(coord1, coord2 - 1);
            abrir_celula(coord1, coord2 + 1);
        }
    }
}


int ganhou(){
    int contfech = 0;
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(jogo[i][j].estaaberta == 0 && jogo[i][j].tembomba == 0){
                contfech += 1;
            }
        }
    }
    return contfech;
}


void game(){
    int coord1, coord2;
    for(;;){
        printf("\nEscolha uma coordenada: ");
        scanf("%d, %d", &coord1, &coord2);
        if(jogo[coord1][coord2].estaaberta || pos_valida( coord1, coord2) == 0){
            printf("\nInsira uma coordenada valida!\n");
        }
        else if(jogo[coord1][coord2].tembomba){
            perdeu();
            break;
        }
        else{
            abrir_celula(coord1, coord2);
        }
        if(ganhou() == 0){printf("\nVoce venceu :)\n"); break;}
        imprimir();
    }
}


int main(void){
    inicio();
    sortear_bombas();
    checar_bomba();
    imprimir();
    game();
}

