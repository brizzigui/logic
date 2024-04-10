#include <stdio.h>

int main(){
    int n;
    double soma = 0, denominador = 2, pot = 1;

    scanf("%d", &n);

    while (n >= pot){
        soma = soma + (1/denominador);
        denominador = denominador * 2;
        pot = pot + 1;
    }

    printf("%.20lf", soma);
}
