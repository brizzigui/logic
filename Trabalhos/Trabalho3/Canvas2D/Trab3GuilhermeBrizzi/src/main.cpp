/*********************************************************************
// TRABALHO
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gl_canvas2d.h"
#include "auxiliar.h"

//constantes
#define TAM 20
#define ORDEM_INIT 5
#define LARGURA_TELA 1280
#define ALTURA_TELA 720


int screenWidth = LARGURA_TELA, screenHeight = ALTURA_TELA;
int mouseX, mouseY;
int clique;

int linha_A = ORDEM_INIT;
int coluna_A = ORDEM_INIT;
int linha_B = ORDEM_INIT;
int coluna_B = ORDEM_INIT;

int linha_res = linha_A, coluna_res = coluna_B;

int matriz_A[TAM][TAM];
int matriz_B[TAM][TAM];
int matriz_res[TAM][TAM];
int digitos_A[TAM][TAM];
int digitos_B[TAM][TAM];
int digitos_res[TAM][TAM];
int max_digitos_a, max_digitos_b, max_digitos_res;

double determinante_final;
int determinante_calculou;

char operacao;
char operacao_print[2];



int numero_aleatorio_elemento(){
   int num = rand() % 11;
   int sinal = rand() % 2;

   if (sinal == 1){
      num = num * -1;
   }

   return num;
}


int numero_aleatorio_tamanho(){
    int num = rand() % 11;
    return num;
}

int digitos(int num){
    int digitos = 0;

    if (num < 0){
        digitos++;
    }

	while (fabs(num) >= 1){
        num = num / 10;
		digitos++;
	}

	return digitos;


}


int max_digitos(int matriz[TAM][TAM], int linha, int coluna)
{
    int maior = matriz[0][0];
    for(int i = 0; i < linha; i++)
    {
        for(int j = 0; j < coluna; j++)
        {
            if(matriz[i][j] > maior){
                maior = matriz[i][j];
            }
        }
    }

    return maior;
}

double determinante(int matriz[TAM][TAM], int linha, int coluna){

    //implementacao do calculo do determinante de tamanho qualquer

    int submatriz[TAM][TAM];
    int l = 0, c = 0;
    double determinante_res = 0;
    double cofator = 0;

    if(linha > 2){
        for(int i = 0; i < linha; i++){
            for(int a = 0; a < linha; a++){
                for(int b = 0; b < coluna; b++){

                    if (a != i && b != 2)
                    {
                        if (c == coluna-1)
                        {
                            l++;
                            c = 0;
                        }

                        submatriz[l][c] = matriz[a][b];
                        c++;


                    }


                }
            }


            cofator = pow(-1.0, (double)(i+2)) * matriz[i][2] * determinante(submatriz, linha-1, coluna-1);
            determinante_res += cofator;
            l=0;
            c=0;


        }



    }

    else if(linha < 2){
        determinante_res = matriz[0][0];
    }

    else{
        determinante_res = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }

    return determinante_res;
}

void somar(){

    for(int i = 0; i < linha_res; i++)
    {
        for(int j = 0; j < coluna_res; j++)
        {

            matriz_res[i][j] = matriz_A[i][j] + matriz_B[i][j];
            digitos_res[i][j] = digitos(matriz_res[i][j]);

        }
    }
}

void subtrair(){

    for(int i = 0; i < linha_res; i++)
    {
        for(int j = 0; j < coluna_res; j++)
        {

            matriz_res[i][j] = matriz_A[i][j] - matriz_B[i][j];
            digitos_res[i][j] = digitos(matriz_res[i][j]);

        }
    }
}


void multiplicar(){
    int soma = 0;


    for(int i = 0; i < linha_res; i++)
    {
        for(int j = 0; j < coluna_res; j++)
        {
            for(int x = 0; x < coluna_res; x++)
            {
                soma = soma + (matriz_A[i][x] * matriz_B[x][j]);
            }

            matriz_res[i][j] = soma;
            digitos_res[i][j] = digitos(matriz_res[i][j]);

            soma = 0;
        }
    }
}

void preenche_matriz(char operacao)
{
    if(operacao == 'x')
    {
        linha_B = coluna_A;
    }

    for (int i = 0; i < linha_A; i++)
    {
        for (int j = 0; j < coluna_A; j++)
        {
            matriz_A[i][j] = numero_aleatorio_elemento();
            digitos_A[i][j] = digitos(matriz_A[i][j]);
        }

    }

    for (int i = 0; i < linha_B; i++)
    {
        for (int j = 0; j < coluna_B; j++)
        {
            matriz_B[i][j] = numero_aleatorio_elemento();
            digitos_B[i][j] = digitos(matriz_B[i][j]);
        }
    }


    switch(operacao)
    {
        case '+':
            linha_res = linha_A;
            coluna_res = coluna_A;
            somar();
            break;

        case '-':
            linha_res = linha_A;
            coluna_res = coluna_A;
            subtrair();
            break;

        case 'x':
            multiplicar();
            break;

    }


    max_digitos_a = max_digitos(digitos_A, linha_A, coluna_A);
    max_digitos_b = max_digitos(digitos_B, linha_B, coluna_B);
    max_digitos_res = max_digitos(digitos_res, linha_res, coluna_res);

    if (linha_res == coluna_res)
    {
        determinante_final = determinante(matriz_res, linha_res, coluna_res);
        determinante_calculou = 1;
    }

    else
    {
        determinante_calculou = 0;
    }


}

int botao(int x0, int y0, int x1, int y1, char texto[]){

    CV::color(0, 0.36, 0.43);
    CV::rectFill(x0, y0, x1, y1);
    CV::color(0, 0.2, 0.3);
    CV::rectFill(x0+(x1-x0)*0.25, y0+(y1-y0)*0.25, x1, y1);
    CV::color(1, 1, 1);
    CV::text((x0+x1)/2, (y0+y1)/2, texto);

    if(mouseX >= x0 && mouseX <= x1 && mouseY >= y0 && mouseY <= y1 && clique == 0){
        //clicado botao
        clique = -2;
        return 1;
    }

    return 0;
}

void render()
{
    int espaco_x, espaco_y, temp_x, temp_y;

    //permite seleção de operação entre as matrizes
    int operacao_mais = botao(10, 10, 50, 50, "+");
    int operacao_menos = botao(60, 10, 100, 50, "-");
    int operacao_vezes = botao(110, 10, 150, 50, "x");


    if (operacao_mais){
        operacao = '+';
        linha_B = linha_A;
        coluna_B = coluna_A;
        preenche_matriz(operacao);
        operacao_print[0] = operacao;
    }

    else if (operacao_menos){
        operacao = '-';
        linha_B = linha_A;
        coluna_B = coluna_A;
        preenche_matriz(operacao);
        operacao_print[0] = operacao;
    }

    else if (operacao_vezes){
        operacao = 'x';
        preenche_matriz(operacao);
        operacao_print[0] = operacao;
    }


    CV::color(1,1,1);
    CV::text(10,70, "Operacao atual:");
    CV::text(170, 70, operacao_print);

    CV::color(0.53, 0.7, 1);
    CV::text(10, 680, "Matriz A:");

    //imprime matriz A
    for(int i = 0; i < linha_A; i++)
    {
        for(int j = 0; j < coluna_A; j++)
        {

            CV::text(10+((40+5*max_digitos_a))*j, 650-40*i, matriz_A[i][j]);

            espaco_x = 10+((40+5*max_digitos_a))*j + 100;
            espaco_y = 650-40*i;
        }

    }

    //botao para aumentar matriz A
    CV::color(1,1,1);
    CV::text(10, espaco_y-30, "Linhas:");
    CV::text(10+80, espaco_y-30, linha_A);
    int diminue_linha_A = botao(10, espaco_y-80, 40, espaco_y-50, "-");
    int aumenta_linha_A = botao(50, espaco_y-80, 80, espaco_y-50, "+");

    if (aumenta_linha_A == 1 && linha_A < 9){
        linha_A++;
        linha_res = linha_A;
        (operacao == '+' || operacao == '-') ? linha_B++ : linha_B;
        preenche_matriz(operacao);
    }

    else if (diminue_linha_A == 1 && linha_A > 1){
        linha_A--;
        linha_res = linha_A;
        (operacao == '+' || operacao == '-') ? linha_B-- : linha_B;
        preenche_matriz(operacao);
    }

    CV::text(10, espaco_y-100, "Colunas:");
    CV::text(10+80, espaco_y-100, coluna_A);
    int diminue_col_A = botao(10, espaco_y-150, 40, espaco_y-120, "-");
    int aumenta_col_A = botao(50, espaco_y-150, 80, espaco_y-120, "+");

    if (aumenta_col_A == 1 && coluna_A < 9){
        coluna_A++;
        (operacao == 'x') ? linha_B++ : linha_B;
        (operacao == '+' || operacao == '-') ? coluna_B++ : coluna_B;
        preenche_matriz(operacao);
    }

    else if (diminue_col_A == 1 && coluna_A > 1){
        coluna_A--;
        (operacao == 'x') ? linha_B-- : linha_B;
        (operacao == '+' || operacao == '-') ? coluna_B-- : coluna_B;
        preenche_matriz(operacao);
    }

    //imprime matriz B
    CV::color(0.53, 0.7, 1);
    CV::text(espaco_x, 680, "Matriz B:");
    int i, j;
    for(i = 0; i < linha_B; i++)
    {
        for(j = 0; j < coluna_B; j++)
        {

            CV::text(espaco_x+((40+5*max_digitos_b))*j, 650-40*i, matriz_B[i][j]);


        }

    }

    espaco_y = (espaco_y < 650-40*i) ? espaco_y : 650-40*i;

    //botao para aumentar matriz B
    CV::color(1,1,1);
    CV::text(espaco_x, espaco_y, "Linhas:");
    CV::text(espaco_x+80, espaco_y, linha_B);
    int diminue_linha_B = botao(espaco_x, espaco_y-50, espaco_x+30, espaco_y-20, "-");
    int aumenta_linha_B = botao(espaco_x+40, espaco_y-50, espaco_x+70, espaco_y-20, "+");

    if (aumenta_linha_B == 1 && linha_B < 9){
        linha_B++;
        (operacao == 'x') ? coluna_A++ : coluna_A;
        (operacao == '+' || operacao == '-') ? linha_A++ : linha_A;
        preenche_matriz(operacao);
    }

    else if (diminue_linha_B == 1 && linha_B > 1){
        linha_B--;
        (operacao == 'x') ? coluna_A-- : coluna_A;
        (operacao == '+' || operacao == '-') ? linha_A-- : linha_A;
        preenche_matriz(operacao);
    }

    CV::text(espaco_x, espaco_y-70, "Colunas:");
    CV::text(espaco_x+80, espaco_y-70, coluna_B);
    int diminue_col_B = botao(espaco_x, espaco_y-120, espaco_x+30, espaco_y-90, "-");
    int aumenta_col_B = botao(espaco_x+40, espaco_y-120, espaco_x+70, espaco_y-90, "+");

    if (aumenta_col_B == 1 && coluna_B < 9){
        coluna_B++;
        (operacao == '+' || operacao == '-') ? coluna_A++ : coluna_A;
        coluna_res = coluna_B;
        preenche_matriz(operacao);

    }

    else if (diminue_col_B == 1 && coluna_B > 1){
        coluna_B--;
        (operacao == '+' || operacao == '-') ? coluna_A-- : coluna_A;
        coluna_res = coluna_B;
        preenche_matriz(operacao);
    }


    espaco_x = espaco_x + 100 + ((40+5*max_digitos_b))*j;


    //imprime resultados
    CV::color(1, 1, 1);
    CV::text(espaco_x, 680, "Resultado da multiplicacao:");
    for(i = 0; i < linha_res; i++)
    {
        for(int j = 0; j < coluna_res; j++)
        {
            CV::text(espaco_x+((40+5*max_digitos_res))*j, 650-40*i, matriz_res[i][j]);
        }
    }


    espaco_y = (espaco_y < 650-40*i) ? espaco_y : 650-40*i;

    CV::text(espaco_x, espaco_y, "Determinante");

    char txt[400] = "Matriz deve ser quadrada";

    if (determinante_calculou)
    {
        sprintf(txt, "%.0f", determinante_final);
    }


    CV::text(espaco_x+150, espaco_y, txt);

}


//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{

   switch(key)
   {
      case 27: //finaliza programa
	     exit(0);
        break;
   }
}
//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{

}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{

   mouseX = x;
   mouseY = y;
   clique = button + state;

}

int main(void)
{
    srand(time(NULL));
    operacao = 'x';
    operacao_print[0] = operacao;
    preenche_matriz(operacao);
    CV::init(&screenWidth, &screenHeight, "virus.exe");

    CV::run();
}
