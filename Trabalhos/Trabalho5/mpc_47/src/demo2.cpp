//==================================================//
// Manipulador básico de texto usando MPC           //
// É capaz de ler entrada do teclado,               //
// mostrá-la para o usuário, invertê-la e           //
// contar caracteres                                //
//==================================================//

//exemplo basico de uso do MPC
//Neste exemplo, vincula-se a posicao do mouse com a posicao do cursor.
//cliques do mouse nao estao sendo tratados
//tambem nao estao sendo tratados teclas especials como as setas direcionais.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpc_c.h"
#include "demo2.h"

#define TAM_CAIXA 20


//variaveis globais que guardam as coordenadas do cursor, que se move segundo o mouse ou setas
int cursorLin = 10, cursorCol = APP_COLUMNS/2-TAM_CAIXA/2;

//mensagem estatica
char msg[] = "Escreva na caixa de texto:";

//matriz global que guarda o texto digitado pelo usuario para ser exibido a cada render
//sem essa matriz, o texto digitado é perdido, pois o MPC nao tem buffer permanente de dados
char texto[21];
char fundo[22];
char qnt_chars[3];

//armazena o id da imagem
int idDaImagem;

//faz as inicializacoes basicas do MPC
void initMpc(void) {
   //mpc configuration
   mpcSetSize(APP_LINES, APP_COLUMNS);

   //mpc callbacks
   mpcSetMouseFunc(cbMouse);
   mpcSetUpdateFunc(cbUpdate);
   mpcSetKeyboardFunc(cbKeyboard);

   mpcSetCursorColor(GREY_2);
   mpcSetCursorVisible(true);

   //inicializa a matriz com espacos, que eh o padrao de "vazio" no MPC
   memset(fundo,' ',21);
   texto[0] = '\0';

   //posição e tamanho da 'janela' onde as IMAGENS poderão aparecer
   mpcSetClippingArea(0, 0, APP_LINES, APP_COLUMNS);

   mpcAbout();
}

//funcao que eh camada a cada frame pela callback cbUpdate() para atualizar a tela
void displayApp(void)
{
    int l = 10;

    mostraTexto(l-1, APP_COLUMNS/2-TAM_CAIXA/2, "Digite aqui:");
    for (int c = 0; c < TAM_CAIXA+1; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l, c+APP_COLUMNS/2-TAM_CAIXA/2, fundo[c], F_STD, WHITE, BLUE_5, 1);

    }

    for (int c = 0; texto[c] != '\0'; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l, c+APP_COLUMNS/2-TAM_CAIXA/2, texto[c], F_STD, WHITE, BLUE_5, 1);

    }

    mostraTexto(l+2, APP_COLUMNS/2-TAM_CAIXA/2, "Seu texto:");
    for (int c = 0; c < TAM_CAIXA+1; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+3, c+APP_COLUMNS/2-TAM_CAIXA/2, fundo[c], F_STD, WHITE, RED_5, 1);

    }

    for (int c = 0; texto[c] != '\0'; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+3, c+APP_COLUMNS/2-TAM_CAIXA/2, texto[c], F_STD, WHITE, RED_5, 1);

    }

    mostraTexto(l+5, APP_COLUMNS/2-TAM_CAIXA/2, "Invertido e maiusculo:");

    char invertido[21];
    strcpy(invertido, texto);
    strrev(invertido);
    strupr(invertido);
    for (int c = 0; c < TAM_CAIXA+1; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+6, c+APP_COLUMNS/2-TAM_CAIXA/2, fundo[c], F_STD, WHITE, GREEN_5, 1);

    }

    for (int c = 0; texto[c] != '\0'; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+6, c+APP_COLUMNS/2-TAM_CAIXA/2, invertido[c], F_STD, WHITE, GREEN_5, 1);

    }


    mostraTexto(l+8, APP_COLUMNS/2-TAM_CAIXA/2, "Quantidade de Caracteres:");
    for (int c = 0; c < TAM_CAIXA/3; c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+9, c+APP_COLUMNS/2-TAM_CAIXA/2, fundo[c], F_STD, WHITE, WHITE, 1);

    }

    sprintf(qnt_chars, "%d", strlen(texto));

    for (int c = 0; c < strlen(qnt_chars); c++)
    {
    //desenha cada caractere da matriz com uma formacao especifica de cor de texto, fundo, transparencia e fonte.
        mpcSetChar(l+9, c+APP_COLUMNS/2-TAM_CAIXA/2, qnt_chars[c], F_STD, BLACK, WHITE, 1);

    }

    mostraTexto(3,APP_COLUMNS/2-TAM_CAIXA/2, msg);

}

//funcao auxiliar para exibir strings na tela.
void mostraTexto(int l, int c, char *msg)
{
   for (int cont = 0; cont < strlen(msg); cont++)
      mpcSetChar(l, c+cont, msg[cont], F_SN, BLACK, WHITE, 1 );
}


//*************************************************************
//callbacks implementation
//*************************************************************
void cbMouse(int lin, int col, int button, int state) {
}

void cbKeyboard(int key, int modifier, bool special, bool up) {
   printf("\nAlguma tecla foi pressionada: %d %d %d %d", key, modifier, special,  up);

   if (special || key == 8 || key == 127)
   {
       int posicao_escrita;
       if( up == false )
       {
            switch(key){
                case 8: //backspace
                    posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;
                    if(posicao_escrita > 0)
                    {
                        cursorCol--;
                        posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;

                        for(int c = posicao_escrita; c < strlen(texto); c++)
                        {
                            texto[c] = texto[c+1];
                        }

                        texto[strlen(texto)] = '\0';
                    }

                    break;

                case 100://seta para esquerda
                    posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;
                    if(posicao_escrita > 0)
                        cursorCol--;
                    break;

                case 102://seta para direita
                    posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;
                    if(posicao_escrita < 20-1)
                        cursorCol++;
                    break;

                case 106://home
                    cursorCol = APP_COLUMNS/2-TAM_CAIXA/2;
                    break;

                case 107://end
                    cursorCol = APP_COLUMNS/2-TAM_CAIXA/2 + TAM_CAIXA;
                    break;

                case 127: //delete

                    posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;
                    for(int c = posicao_escrita; c < strlen(texto); c++)
                    {
                        texto[c] = texto[c+1];
                    }

                    break;
            }
       }

   }
   else
   {
      if(up == false) //soh pega o caractere quando ele for pressionado, ou seja, quando nao eh up.
      {

          int posicao_escrita = cursorCol-APP_COLUMNS/2+TAM_CAIXA/2;

          if(posicao_escrita >= 0 && posicao_escrita < 20 && strlen(texto) < 20)
          {
              for(int c = strlen(texto)+1; c > posicao_escrita; c--)
              {
                  printf("%c %c\n", texto[c], texto[c-1]);
                 texto[c] = texto[c-1];
              }

              texto[posicao_escrita] = key;
              cursorCol++;
          }
      }
   }
   mpcSetCursorPos(cursorLin, cursorCol);
}

void cbUpdate(void) {
   displayApp();
}
