/*********************************************************************
//
// TRABALHO: TABULEIRO DE DAMAS
// Por: Guilherme Brizzi
// Pode ser usado para simular as movimentações das peças em uma
// maneira similar ao jogo de damas, limitando o usuário às jogadas
// que seriam possíveis nesse jogo.
// As peças podem ser movimentadas fazendo uso do teclado
// como também do mouse.
//
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "auxiliar.h"

#define ANCORA_X 50
#define ANCORA_Y 50
#define LADO_CELULA 60
#define RAIO_PECA 20

#define LARG_TELA 1000
#define ALT_TELA 800

#define CODE_BRANCO 1
#define CODE_PRETO 0

#define PECA_ALIADA 1
#define PECA_OPONENTE 0

#define LARG_BOTAO 125
#define ALT_BOTAO 60

#define AZUL_ESCURO 0.0, 0.05, 0.25

//variaveis globais
int posQuadradoX = 100;
int posQuadradoY = 100;

bool click = -2;

int screenWidth = LARG_TELA, screenHeight = ALT_TELA; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().
int tam_tab = 10;
int turno = 0;
bool menu_open = false;

void marca_peca();

int botao(float x0, float y0, char* text)
{
    int x1 = x0+LARG_BOTAO;
    int y1 = y0+ALT_BOTAO;

    CV::color(0.58, 0.93, 1);
    CV::rectFill(x0, y0, x1, y1);
    CV::color(0, 0, 0);
    CV::text(x0+LARG_BOTAO/3, y0+ALT_BOTAO/2, text);

    if(mouseX > x0 && mouseX < x1 && mouseY > y0 && mouseY < y1 && click == 0)
    {
        click = -2;
        return true;
    }

    return false;
}

struct celula
{
    float x, y;
    bool ocupada;
    int peca;
    int cor;
    bool selecionando;
    bool selecionada_origem;
    bool selecionada_destino;

};

struct celula *matriz;

void muda_turno()
{
    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            (matriz + tam_tab*i + j)->selecionando = false;
        }
    }

    if(turno%2 == PECA_ALIADA)
    {
        matriz->selecionando = true;
    }

    else
    {
        (matriz + tam_tab*(tam_tab-1))->selecionando = true;
    }

    turno++;
}

void cria_matriz()
{
    matriz = (struct celula *) malloc(tam_tab*tam_tab*sizeof(celula));

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            (matriz + tam_tab*i + j)->x = ANCORA_X + LADO_CELULA*j;
            (matriz + tam_tab*i + j)->y = ANCORA_Y + LADO_CELULA*i;
            (matriz + tam_tab*i + j)->selecionando = false;
            (matriz + tam_tab*i + j)->selecionada_origem = false;

            if((i+j) % 2 == 0)
            {
                (matriz + tam_tab*i + j)->cor = CODE_BRANCO;
                (matriz + tam_tab*i + j)->ocupada = false;
            }

            else
            {
                (matriz + tam_tab*i + j)->cor = CODE_PRETO;
                (matriz + tam_tab*i + j)->ocupada = false;

                if(i <= 2)
                {
                    (matriz + tam_tab*i + j)->ocupada = true;
                    (matriz + tam_tab*i + j)->peca = PECA_OPONENTE;
                }

                else if (i >= tam_tab-3)
                {
                    (matriz + tam_tab*i + j)->ocupada = true;
                    (matriz + tam_tab*i + j)->peca = PECA_ALIADA;
                }

            }

        }
    }

    muda_turno();
}

void destroi_matriz()
{
    free(matriz);
}

void desenha_marcador(float x0, float y0)
{
    //cria retangulo mais visivel para a marcacao
    CV::rectFill(x0, y0, x0+5, y0+LADO_CELULA);
    CV::rectFill(x0+LADO_CELULA-5, y0, x0+LADO_CELULA, y0+LADO_CELULA);
    CV::rectFill(x0, y0, x0+LADO_CELULA, y0+5);
    CV::rectFill(x0, y0+LADO_CELULA-5, x0+LADO_CELULA, y0+LADO_CELULA);
}


void desloca_selecao_left()
{
    int i_selec, j_selec;

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            if((matriz + tam_tab*i + j)->selecionando == true)
            {
                i_selec = i;
                j_selec = j;
            }

            (matriz + tam_tab*i + j)->selecionando = false;
        }
    }

    if(j_selec > 0)
        (matriz + tam_tab*i_selec + j_selec-1)->selecionando = true;
    else
        (matriz + tam_tab*i_selec + j_selec)->selecionando = true;

}


void desloca_selecao_up()
{
    int i_selec, j_selec;

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            if((matriz + tam_tab*i + j)->selecionando == true)
            {
                i_selec = i;
                j_selec = j;
            }

            (matriz + tam_tab*i + j)->selecionando = false;

        }
    }

    if(i_selec > 0)
        (matriz + tam_tab*(i_selec-1) + j_selec)->selecionando = true;

    else
        (matriz + tam_tab*i_selec + j_selec)->selecionando = true;
}

void desloca_selecao_right()
{
    int i_selec, j_selec;

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            if((matriz + tam_tab*i + j)->selecionando == true)
            {
                i_selec = i;
                j_selec = j;
            }

            (matriz + tam_tab*i + j)->selecionando = false;

        }
    }

    if(j_selec < tam_tab-1)
        (matriz + tam_tab*i_selec + j_selec+1)->selecionando = true;
    else
        (matriz + tam_tab*i_selec + j_selec)->selecionando = true;
}


void desloca_selecao_down()
{
    int i_selec, j_selec;

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            if((matriz + tam_tab*i + j)->selecionando == true)
            {
                i_selec = i;
                j_selec = j;
            }

            (matriz + tam_tab*i + j)->selecionando = false;

        }
    }

    if(i_selec < tam_tab-1)
        (matriz + tam_tab*(i_selec+1) + j_selec)->selecionando = true;
    else
        (matriz + tam_tab*i_selec + j_selec)->selecionando = true;
}

bool jogada_permitida(int i, int j, int i_origem, int j_origem)
{
    if(turno % 2 == 0)
    {
        if(i == i_origem +1 && (j == j_origem-1 || j == j_origem+1))
            return true;
    }

    else
    {
        if(i == i_origem -1 && (j == j_origem-1 || j == j_origem+1))
            return true;
    }

    return false;
}

void seleciona_com_clique()
{
    if(mouseX >= (matriz)->x && mouseX <= (matriz + tam_tab-1)->x+LADO_CELULA && mouseY >= (matriz)->y && mouseY <= (matriz + tam_tab*(tam_tab-1))->y+LADO_CELULA)
    {
        for(int i = 0; i < tam_tab; i++)
        {
            for(int j = 0; j < tam_tab; j++)
            {
                (matriz + tam_tab*i + j)->selecionando = false;
            }
        }

        for(int i = 0; i < tam_tab; i++)
        {
            for(int j = 0; j < tam_tab; j++)
            {
                if(mouseX >= (matriz + tam_tab*i + j)->x && mouseX <= (matriz + tam_tab*i + j)->x+LADO_CELULA && mouseY >= (matriz + tam_tab*i + j)->y && mouseY <= (matriz + tam_tab*i + j)->y+LADO_CELULA)
                {
                    (matriz + tam_tab*i + j)->selecionando = true;
                    marca_peca();
                }

            }
        }
    }



}

void marca_peca()
{
    bool tem_origem = false;
    int i_origem, j_origem;

    for(int i = 0; i < tam_tab; i++)
    {
        for(int j = 0; j < tam_tab; j++)
        {
            if((matriz + tam_tab*i + j)->selecionada_origem == true)
            {
                i_origem = i;
                j_origem = j;
                tem_origem = true;
            }
        }
    }

    if(!tem_origem)
    {
        for(int i = 0; i < tam_tab; i++)
        {
            for(int j = 0; j < tam_tab; j++)
            {
                if((matriz + tam_tab*i + j)->selecionando == true && (matriz + tam_tab*i + j)->ocupada)
                {
                    if(turno % 2 == (matriz + tam_tab*i + j)->peca)
                    {
                        (matriz + tam_tab*i + j)->selecionada_origem = true;
                    }

                }
            }
        }
    }


    else if(tem_origem)
    {
        for(int i = 0; i < tam_tab; i++)
        {
            for(int j = 0; j < tam_tab; j++)
            {
                if((matriz + tam_tab*i + j)->selecionando == true && jogada_permitida(i, j, i_origem, j_origem))
                {
                    (matriz + tam_tab*i_origem + j_origem)->selecionada_origem = false;
                    (matriz + tam_tab*i_origem + j_origem)->ocupada = false;
                    (matriz + tam_tab*i + j)->ocupada = true;
                    (matriz + tam_tab*i + j)->peca = (matriz + tam_tab*i_origem + j_origem)->peca;
                    muda_turno();
                }
            }
        }
    }


}

void render()
{
    CV::clear(AZUL_ESCURO);

    if(menu_open)
    {
        //menu de instrucoes
        CV::text(50, 50, "COM TECLADO");
        CV::text(50, 100, "-> Para navegar ate uma peca, use as setas do teclado.");
        CV::text(50, 150, "-> Ao chegar na peca desejada, clique espaco.");
        CV::text(50, 200, "-> Agora, a peca estara selecionada.");
        CV::text(50, 250, "-> Navegue ate a posicao desejada.");
        CV::text(50, 300, "-> Clique espaco novamente para confirmar a jogada.");
        CV::text(50, 350, "-> Para abrir ou fechar este menu de instrucoes, clique 'X'.");
        CV::text(50, 400, "COM MOUSE");
        CV::text(50, 450, "-> Clique em uma peca para seleciona-la.");
        CV::text(50, 500, "-> Apos, clique na posicao na qual voce quer leva-la.");
        CV::text(50, 550, "-> Pronto, sua jogada esta confirmada.");
        CV::text(50, 650, "-> Para abrir ou fechar este menu de instrucoes, clique 'X'.");
    }

    //desenha matriz e suas pecas
    else
    {
        for(int i = 0; i < tam_tab; i++)
        {
            for(int j = 0; j < tam_tab; j++)
            {
                if((matriz + tam_tab*i + j)->cor == CODE_BRANCO)
                {
                    CV::color(1, 1, 1);
                }

                else
                {
                    CV::color(0.25, 0.25, 0.25);
                }

                CV::rectFill((matriz + tam_tab*i + j)->x, (matriz + tam_tab*i + j)->y, (matriz + tam_tab*i + j)->x+LADO_CELULA, (matriz + tam_tab*i + j)->y+LADO_CELULA);

                if((matriz + tam_tab*i + j)->ocupada)
                {
                    if((matriz + tam_tab*i + j)->peca == PECA_ALIADA)
                    {
                        CV::color(1, 1, 0);
                    }

                    else
                    {
                        CV::color(0, 0, 0);
                    }

                    CV::circleFill((matriz + tam_tab*i + j)->x+LADO_CELULA/2, (matriz + tam_tab*i + j)->y+LADO_CELULA/2, RAIO_PECA, 20);
                }

                if((matriz + tam_tab*i + j)->selecionando)
                {
                    CV::color(1, 1, 0);
                    desenha_marcador((matriz + tam_tab*i + j)->x, (matriz + tam_tab*i + j)->y);
                }

                if((matriz + tam_tab*i + j)->selecionada_origem)
                {
                    CV::color(1, 0, 0);
                    desenha_marcador((matriz + tam_tab*i + j)->x, (matriz + tam_tab*i + j)->y);
                }
            }
        }

        //botoes para alterar tamanho
        bool mudar_p8 = botao((matriz + tam_tab-1)->x+LARG_BOTAO, ANCORA_Y, "8x8");
        bool mudar_p10 = botao((matriz + tam_tab-1)->x+LARG_BOTAO, ANCORA_Y+ALT_BOTAO*1.5, "10x10");
        bool mudar_p12 = botao((matriz + tam_tab-1)->x+LARG_BOTAO, ANCORA_Y+ALT_BOTAO*3, "12x12");

        //mostra quem joga nesse turno
        char texto[64];
        if(turno % 2 == PECA_ALIADA)
        {
           sprintf(texto, "Vez das AMARELAS");
        }

        else
        {
            sprintf(texto, "Vez das PRETAS");
        }

        CV::color(1,1,1);
        CV::text((matriz + tam_tab-1)->x+100, ANCORA_Y+ALT_BOTAO*5, texto);

        CV::text((matriz + tam_tab-1)->x+100, ANCORA_Y+ALT_BOTAO*7, "Ajuda: clique 'X'");

        if(mudar_p8)
            tam_tab = 8;

        else if(mudar_p10)
            tam_tab = 10;

        else if(mudar_p12)
            tam_tab = 12;

        if(mudar_p8 || mudar_p10 || mudar_p12)
        {
            destroi_matriz();
            cria_matriz();
        }
    }





    Sleep(50);
}


//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
    printf("\nTecla: %d" , key);

    switch(key)
    {
        case 27: //esc
            exit(0);
            break;

        case 32: //espaço
            marca_peca();
            break;

        case 120: //"x"
            menu_open = !menu_open;
            break;

        case 200: //seta para esquerda
            desloca_selecao_left();
            break;

        case 201: //seta para cima
            desloca_selecao_up();
            break;

        case 202: //seta para direita
            desloca_selecao_right();
            break;

        case 203: //seta para a baixo
            desloca_selecao_down();
            break;



   }
}

void keyboardUp(int key)
{
}


void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x;
    mouseY = y;
    click = button + state;

    if(click == 0)
    {
        //caso clicado, chama funcao que verifica se clicou em uma casa valida da matriz
        seleciona_com_clique();
    }
}

int main(void)
{
    CV::init(&screenWidth, &screenHeight, "Tabuleiro de Damas");
    cria_matriz();
    CV::run();
}
