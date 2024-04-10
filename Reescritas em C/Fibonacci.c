#include <stdio.h>

int main(){
    double num = 1, num_preanterior = 0, num_anterior = 0;
    for (int i=0; i<100; i++){
        printf("%.0lf ", num);
        num_preanterior = num_anterior;
        num_anterior = num;
        num = num_anterior + num_preanterior;

    }

}
