//programa para calcular fatorial de um número

#include <stdio.h>

int main(){
    int num, cont = 1;
    double res = 1;
    scanf("%d", &num);

    while (cont <= num){
        res = res * cont;
        cont++;
    }
    printf("%lf", res);
}
