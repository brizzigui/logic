#include <stdio.h>

int main(){

	double a, b, numero, erro_aproximacao;
	scanf("%lf", &numero);
	a = numero;

    do{
        b = numero/a;
		a = (a + b)/2;
		erro_aproximacao = b*b - numero;

    } while(erro_aproximacao > 0,000001 && erro_aproximacao > 0 || erro_aproximacao < -0,000001 && erro_aproximacao < 0);

    printf("%lf", a);
}
