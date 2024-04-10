//Calcular o valor anual e total de um financiamento bancário de 20 anos, no qual o valor
//da prestação inicial é de 700,00 e com reajuste da prestação em 0.85% ao mês

#include <stdio.h>

int main(){
    int cont = 1, ano = 1;
    float prestacao = 700, valorAnual = 0, valorFinal = 0;

    while (ano <= 20){
        while (cont <= 12){
            prestacao = prestacao * 1.0085;
            valorAnual = valorAnual + prestacao;
            cont++;
        }

        cont = 0;
        printf("O valor anual no ano %d foi de %.2f\n", ano, valorAnual);
        ano++;
        valorFinal = valorFinal + valorAnual;
    }

    printf("\n\n\nO valor final foi de %f\n\n", valorFinal);
}
