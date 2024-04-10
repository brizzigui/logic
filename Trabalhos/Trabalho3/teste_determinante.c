#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int numero_aleatorio_elemento(){
   int num = rand() % 11;
   int sinal = rand() % 2;

   if (sinal == 1){
      num = num * -1;
   }

   return num;
}

int determinante(int matriz[20][20], int linha, int coluna){

    //implementacao do calculo do determinante de tamanho qualquer

    int submatriz[20][20];
    int l = 0, c = 0;
    int determinante_res = 0;
    int cofator;

    if(linha > 2){
        for(int i = 0; i < linha; i++){
            for(int a = 0; a < linha; a++){
                for(int b = 0; b < coluna; b++){
                    
                    if (a != i && b != 0)
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



            cofator = pow(-1.0, (double)(i+0)) * matriz[i][2] * determinante(submatriz, linha-1, coluna-1);
            determinante_res += cofator;
            l=0;
            c=0;

            
        }


        
    }

    else{
        determinante_res = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }
    
    
    return determinante_res;
}

void preenche_matriz(int matriz[20][20], int linha, int coluna)
{

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            matriz[i][j] = numero_aleatorio_elemento();
        }

    }

    int determinante_final = determinante(matriz, linha, coluna);
    printf("\nDet = %d\n\n", determinante_final);

}

int main(){
    srand(time(NULL));
    int matriz[20][20];
    int linha = 12;
    int coluna = 12;

    preenche_matriz(matriz, linha, coluna);

    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            printf("%4d", matriz[i][j]);
        }
        printf("\n");
    }
}