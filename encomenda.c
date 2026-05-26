#include <GL/glut.h> 
#include <stdio.h>

int moveEsq, moveDir; 
float xJogador, yJogador; 
float yChao = -0.60; 
float limitePulo = 0.2; 
int pulando = 0; 
float cameraX = 0; 
int frameAnim = 0; 
int contadorAnim = 0; 
int olhandoDireita = 0; 
int terreno[8][200]; 
float xCorreio = -0.6; 
float yCorreio = -0.60; 
int temCarta = 0; 
int mostrarMensagem = 0; 
int cartasEnviadas = 0; 
float xCasa = 3.0; 
float yCasa = -0.31; 
char texto[100]; 
char texto2[100];

float xInimigo = 1.5; float yInimigo = -0.70;
float velocidade = 0.01;

int personagemParado[18][14] = {
{0,0,0,0,0,1,1,1,1,0,0,0,0,0},
{0,0,0,1,1,5,5,5,5,1,1,0,0,0},
{0,0,1,5,5,5,5,5,5,5,5,1,0,0},
{0,0,1,5,5,5,5,5,5,5,5,1,0,0},
{0,1,5,4,5,5,5,5,5,5,5,5,1,0},
{0,1,4,4,4,4,5,5,5,5,5,4,1,0},
{0,1,4,4,4,4,4,4,4,4,4,4,1,0},
{0,0,1,4,4,1,4,4,1,4,4,1,0,0},
{0,0,0,1,4,1,4,4,1,4,1,0,0,0},
{0,0,1,3,1,4,4,4,4,1,3,1,0,0},
{0,1,4,3,3,1,1,1,1,3,3,4,1,0},
{1,4,4,1,3,3,3,3,3,3,1,4,4,1},
{1,4,4,1,3,3,3,3,3,3,1,4,4,1},
{0,1,1,2,1,1,1,1,1,1,2,1,1,0},
{0,0,1,2,2,2,2,2,2,2,2,1,0,0},
{0,0,1,2,2,2,1,1,2,2,2,1,0,0},
{0,0,1,6,6,6,1,1,6,6,6,1,0,0},
{0,0,0,1,1,1,0,0,1,1,1,0,0,0}
};

int personagemPulando[18][16] = {
{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,1,1,5,5,5,5,1,1,0,0,0,0},
{0,0,0,1,5,5,5,5,5,5,5,5,1,0,0,0},
{0,0,0,1,5,5,5,5,5,5,5,5,1,0,0,0},
{0,0,1,5,4,5,5,5,5,5,5,5,5,1,0,0},
{0,0,1,4,4,4,4,5,5,5,5,5,4,1,0,0},
{0,0,1,4,4,4,4,4,4,4,4,4,4,1,0,0},
{0,0,0,1,4,4,1,4,4,1,4,4,1,0,0,0},
{0,1,1,0,1,4,1,4,4,1,4,1,0,1,1,0},
{1,4,4,1,3,1,4,4,4,4,1,3,1,4,4,1},
{1,4,4,4,3,3,1,1,1,1,3,3,4,4,4,1},
{0,1,4,4,1,3,3,3,3,3,3,1,4,4,1,0},
{0,0,1,4,1,3,3,3,3,3,3,1,4,1,0,0},
{0,0,0,1,2,1,1,1,1,1,1,2,1,0,0,0},
{0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0},
{0,0,0,1,2,2,2,1,1,2,2,2,1,0,0,0},
{0,0,0,1,6,6,6,1,1,6,6,6,1,0,0,0},
{0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0}
};

int personagemMovendo1[16][12] = {
{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 1, 1, 5, 5, 5, 5, 1, 1, 0, 0},
{0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0},
{0, 1, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0},
{1, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 1},
{0, 1, 4, 4, 5, 5, 5, 5, 5, 5, 5, 1},
{0, 1, 4, 1, 4, 5, 5, 4, 5, 5, 5, 1},
{0, 1, 4, 1, 4, 4, 4, 4, 4, 5, 5, 1},
{0, 0, 1, 4, 4, 4, 4, 4, 4, 4, 1, 0},
{0, 0, 1, 1, 4, 4, 4, 4, 1, 1, 0, 0},
{0, 1, 4, 4, 1, 1, 1, 1, 4, 4, 1, 0},
{0, 1, 4, 1, 3, 3, 3, 1, 4, 4, 1, 0},
{0, 1, 1, 3, 3, 3, 3, 3, 1, 1, 0, 0},
{1, 6, 6, 1, 2, 1, 2, 2, 1, 6, 1, 0},
{0, 1, 6, 6, 1, 0, 1, 1, 6, 6, 1, 0},
{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0}
};

int personagemMovendo2[16][12] = {
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,1,1,5,5,5,5,1,1,0,0},
{0,1,5,5,5,5,5,5,5,5,1,0},
{0,1,5,5,5,5,5,5,5,5,1,0},
{1,5,4,5,5,5,5,5,5,5,5,1},
{0,1,4,4,5,5,5,5,5,5,5,1},
{0,1,4,1,4,5,5,4,5,5,5,1},
{0,1,4,1,4,4,4,4,4,5,5,1},
{0,0,1,4,4,4,4,4,4,4,1,0},
{0,0,1,1,4,4,4,4,1,1,0,0},
{0,1,4,4,1,1,1,1,1,4,1,0},
{0,1,4,4,1,3,3,3,1,4,1,0},
{0,1,1,1,3,3,3,3,1,1,0,0},
{1,6,6,1,2,1,2,2,1,6,1,0},
{0,1,6,6,1,0,1,1,6,6,1,0},
{0,0,1,1,0,0,0,0,1,1,0,0}
};

int personagemMovendo3[17][12] = {
{0,0,0,0,1,1,1,1,0,0,0,0},
{0,0,1,1,5,5,5,5,1,1,0,0},
{0,1,5,5,5,5,5,5,5,5,1,0},
{0,1,5,5,5,5,5,5,5,5,1,0},
{1,5,4,5,5,5,5,5,5,5,5,1},
{0,1,4,4,5,5,5,5,5,5,5,1},
{0,1,4,1,4,5,5,4,5,5,5,1},
{0,1,4,1,4,4,4,4,4,5,5,1},
{0,0,1,4,4,4,4,4,4,4,1,0},
{0,0,0,1,4,4,4,4,4,1,0,0},
{0,0,0,0,1,1,1,1,1,0,0,0},
{0,0,0,1,3,1,1,3,3,1,0,0},
{0,0,0,1,1,4,4,1,3,1,0,0},
{0,0,0,0,1,4,4,1,3,1,0,0},
{0,0,0,1,2,1,1,2,1,0,0,0},
{0,0,0,1,6,6,6,6,1,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0,0}
};

void gerarMapa(){
    for(int l = 0; l < 6; l++){
        for(int c = 0; c < 200; c++){
            terreno[l][c] = (l < 2) ? 1 : 0;
        }
    }
}

void renderizarTerreno(){
    for(int l = 0; l < 6; l++){

        for(int c = 0; c < 200; c++){

            if(terreno[l][c] == 1)
                glColor3ub(95, 159, 53);

            if(terreno[l][c] == 0)
                glColor3ub(134, 96, 67);

            float x = c * 0.050 - cameraX - 1.0;
            float y = -l * 0.050 - 0.80;

            glBegin(GL_QUADS);

            glVertex2f(x - 0.050, y - 0.050);
            glVertex2f(x + 0.050, y - 0.050);
            glVertex2f(x + 0.050, y + 0.050);
            glVertex2f(x - 0.050, y + 0.050);

            glEnd();
        }
    }
}

void desenharMatriz(int rows, int cols, int matriz[rows][cols]){
    for(int l = 0; l < rows; l++){

        for(int c = 0; c < cols; c++){

            if(matriz[l][c] != 0){

                if(matriz[l][c] == 1)
                    glColor3ub(0, 0, 0);

                if(matriz[l][c] == 2)
                    glColor3ub(17, 164, 224);

                if(matriz[l][c] == 3)
                    glColor3ub(224, 33, 16);

                if(matriz[l][c] == 4)
                    glColor3ub(254, 232, 214);

                if(matriz[l][c] == 5)
                    glColor3ub(186, 120, 81);

                if(matriz[l][c] == 6)
                    glColor3ub(118, 49, 11);

                float x = c * 0.0090;
                float y = -l * 0.0090;

                glBegin(GL_QUADS);

                glVertex2f(x, y + yJogador);
                glVertex2f(x + 0.0090, y + yJogador);
                glVertex2f(x + 0.0090, y + 0.0090 + yJogador);
                glVertex2f(x, y + 0.0090 + yJogador);

                glEnd();
            }
        }
    }
}

void desenharPersonagem(){
    if(pulando){
        desenharMatriz(18, 16, personagemPulando);
        return;
    }

    if(!moveEsq && !moveDir){
        desenharMatriz(18, 14, personagemParado);
        return;
    }

    contadorAnim++;

    if(contadorAnim >= 10){
        contadorAnim = 0;
        frameAnim = (frameAnim + 1) % 4;
    }

    glPushMatrix();

    if(olhandoDireita){
        glTranslated(12 * 0.0090, 0, 0); // VER DEPOIS
        glScaled(-1.0, 1.0, 1.0);
    }

    if(frameAnim == 0)
        desenharMatriz(16, 12, personagemMovendo1);

    if(frameAnim == 1)
        desenharMatriz(17, 12, personagemMovendo3);

    if(frameAnim == 2)
        desenharMatriz(16, 12, personagemMovendo2);

    if(frameAnim == 3)
        desenharMatriz(17, 12, personagemMovendo3);

    glPopMatrix();
}

int caixaDeCorreio[32][28] = {
{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,4,4,4,4,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,4,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,4,4,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,1,1,2,2,1,4,4,1,2,2,2,2,2,1,1,3,3,3,3,1,1,0,0,0},
{0,0,1,2,2,2,2,1,4,4,1,2,2,2,2,1,3,3,3,3,3,3,3,3,1,0,0},
{0,1,2,2,2,2,2,1,4,4,1,2,2,2,1,3,3,3,3,3,3,3,3,3,3,1,0},
{0,1,2,2,2,2,1,4,4,4,1,2,2,2,1,3,3,3,3,3,3,3,3,3,3,1,0},
{1,2,2,2,2,2,1,4,4,4,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,1,4,4,4,1,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,2,1,1,1,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,2,2,2,2,2,2,2,2,2,2,2,2,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,2,1,3,3,3,1,0,0,0,0,0,0,0,0,0,0}
};

void desenharCaixaDeCorreio(){
    for(int l = 0; l < 32; l++){
        for(int c = 0; c < 28; c++){

            if(caixaDeCorreio[l][c] != 0){

                if(caixaDeCorreio[l][c] == 1)
                    glColor3ub(0, 0, 0);

                if(caixaDeCorreio[l][c] == 2)
                    glColor3ub(66, 66, 66);

                if(caixaDeCorreio[l][c] == 3)
                    glColor3ub(117, 117, 117);

                if(caixaDeCorreio[l][c] == 4)
                    glColor3ub(189, 189, 189);

                float x = c * 0.005; float y = -l * 0.005;

                glBegin(GL_QUADS);
                    glVertex2f(x + xCorreio - cameraX, y + yCorreio);
                    glVertex2f(x + 0.005 + xCorreio - cameraX, y + yCorreio);
                    glVertex2f(x + 0.005 + xCorreio - cameraX, y + 0.005 + yCorreio);
                    glVertex2f(x + xCorreio - cameraX, y + 0.005 + yCorreio);
                glEnd();
            }
        }
    }
}

int casa[23][27] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 2, 3, 2, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 3, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 2, 1, 3, 3, 3, 1, 2, 1, 3, 3, 1, 2, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 3, 3, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 1, 0, 0, 0},
    {0, 0, 1, 3, 3, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 3, 3, 1, 0, 0},
    {0, 1, 3, 3, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 3, 3, 1, 0},
    {1, 3, 3, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 5, 6, 5, 1, 2, 2, 2, 1, 3, 3, 1},
    {0, 1, 1, 1, 4, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 6, 5, 6, 5, 6, 1, 2, 2, 1, 1, 1, 0},
    {0, 0, 0, 1, 4, 2, 1, 9, 8, 8, 1, 2, 2, 1, 7, 6, 5, 6, 5, 6, 6, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 2, 1, 9, 8, 8, 1, 2, 2, 1, 7, 6, 5, 6, 5, 6, 6, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 1, 5, 5, 5, 5, 5, 1, 2, 1, 5, 5, 5, 5, 5, 5, 5, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 1, 5, 5, 5, 5, 5, 1, 2, 1, 7, 5, 6, 6, 6, 6, 6, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 1, 1, 1, 1, 1, 1, 1, 2, 1, 5, 5, 5, 5, 5, 5, 5, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 7, 6, 5, 6, 5, 6, 6, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1, 7, 6, 5, 6, 5, 6, 6, 1, 2, 1, 0, 0, 0},
    {0, 0, 0, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 7, 6, 5, 6, 5, 6, 6, 1, 4, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
};

void desenharCasa(){
    for(int l = 0; l < 23; l++){
        for(int c = 0; c < 27; c++){

            if(casa[l][c] != 0){

                if(casa[l][c] == 1) glColor3ub(0, 0, 0); if(casa[l][c] == 2) glColor3ub(255, 255, 255); if(casa[l][c] == 3) glColor3ub(255, 0, 0);

                if(casa[l][c] == 4) glColor3ub(181, 205, 202); if(casa[l][c] == 5) glColor3ub(97, 74, 43); if(casa[l][c] == 6) glColor3ub(160, 123, 69);

                if(casa[l][c] == 7) glColor3ub(146, 101, 34); if(casa[l][c] == 8) glColor3ub(255, 255, 0); if(casa[l][c] == 9) glColor3ub(220, 197, 31);

                float x = c * 0.02; float y = -l * 0.02;

                glBegin(GL_QUADS);
                    glVertex2f(x + xCasa - cameraX, y + yCasa);
                    glVertex2f(x + 0.02 + xCasa - cameraX, y + yCasa);
                    glVertex2f(x + 0.02 + xCasa - cameraX, y + 0.02 + yCasa);
                    glVertex2f(x + xCasa - cameraX, y + 0.02 + yCasa);
                glEnd();
            }
        }
    }
}

void quadrado(){
    glBegin(GL_QUADS);
        glVertex2f(-0.05 + xInimigo - cameraX, -0.05 + yInimigo);
        glVertex2f(+0.05 + xInimigo - cameraX, -0.05 + yInimigo);
        glVertex2f(+0.05 + xInimigo - cameraX, 0.05 + yInimigo);
        glVertex2f(-0.05 + xInimigo - cameraX, 0.05 + yInimigo);
    glEnd();
}

void moverQuadrado(int valor){
    xInimigo += velocidade;

    if(xInimigo >= 2.5){
        velocidade = -0.01;
    }
    if(xInimigo <= 0.5){
        velocidade = 0.01;
    }

    glutTimerFunc(20, moverQuadrado, 0);
    glutPostRedisplay();
}

void colisaoInimigo(){
    if(xJogador >= xInimigo - 0.10 && xJogador <= xInimigo + 0.10 && yJogador >= yInimigo - 0.10 && yJogador <= yInimigo + 0.10){
        xJogador = 0.0;
    }
}

void teclaSegurada(unsigned char key, int a, int b){
    if(key == 'a'){
        moveEsq = 1;
        olhandoDireita = 0;
    }

    if(key == 'd'){
        moveDir = 1;
        olhandoDireita = 1;
    }

    if(key == 'w' && yJogador <= yChao)
        pulando = 1;

    if(key == 'e' && xJogador <= xCorreio + 0.10 && xJogador >= xCorreio - 0.10 && temCarta == 0){
        sprintf(texto, "Pegou a carta !");
        mostrarMensagem = 1;
        temCarta = 1;
    }

    else if(key == 'e' && xJogador <= xCorreio + 0.10 && xJogador >= xCorreio - 0.10 && temCarta == 1){
        sprintf(texto, "Limite de cartas atingida !");
        mostrarMensagem = 1;
    }

    else if(key == 'e' && xJogador <= xCasa + 0.29 && xJogador >= xCasa - 0.29 && temCarta == 1){
        sprintf(texto, "Carta entregue !");
        mostrarMensagem = 1;
        temCarta = 0;
        cartasEnviadas++;
    }

    else if(key == 'e' && xJogador <= xCasa + 0.29 && xJogador >= xCasa - 0.29 && temCarta == 0){
        sprintf(texto, "Nao tem cartas para entregar !");
        mostrarMensagem = 1;
    }
}

void teclaSolta(unsigned char key, int a, int b){
    if(key == 'a')
        moveEsq = 0;

    if(key == 'd')
        moveDir = 0;
}

void moverJogador(int valor){
    float velocidadeJogador = 0.0050;

    if(moveEsq)
        xJogador -= velocidadeJogador;

    if(moveDir)
        xJogador += velocidadeJogador;

    if(pulando == 1)
        yJogador += 0.01;

    if(yJogador >= limitePulo)
        pulando = 0;

    if(!pulando)
        yJogador -= 0.01;

    if(yJogador <= yChao)
        yJogador = yChao;

    cameraX = xJogador;

    if(!(xJogador <= xCorreio +0.10 && xJogador >= xCorreio -0.10) && !(xJogador <= xCasa + 0.29 && xJogador >= xCasa - 0.29)){
        mostrarMensagem = 0;
    }

    glutTimerFunc(6, moverJogador, 0);
    glutPostRedisplay();
}

void mostrarTela(){
    if(!mostrarMensagem)
        return;

    glColor3ub(255,255,255);

    glRasterPos2f(-0.25, 0.8);

    for(int i = 0; texto[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto[i]);
    }
}

void placarCartas(){
    glColor3ub(255,255,255);

    glRasterPos2f(-0.95, 0.85);

    sprintf(texto2, "Cartas Enviadas: %d", cartasEnviadas);

    for(int i = 0; texto2[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,texto2[i]);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    renderizarTerreno();

    desenharCaixaDeCorreio();

    desenharCasa();

    desenharPersonagem();

    mostrarTela();

    quadrado();

    placarCartas();
    colisaoInimigo();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(800,600);

    glutCreateWindow("Entregar Cartas");

    glClearColor(0.2,0.2,0.2,1.0);

    gerarMapa();

    glutDisplayFunc(display);

    glutTimerFunc(2,moverJogador,0);

    glutKeyboardFunc(teclaSegurada);

    glutKeyboardUpFunc(teclaSolta);

    glutTimerFunc(6, moverQuadrado, 0);

    glutMainLoop();
}
