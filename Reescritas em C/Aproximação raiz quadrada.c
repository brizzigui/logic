#include <stdio.h>

int main(){
    double Rn, Ro, RnMenosRo, x;
    printf("Insira a raiz que voce quer aproximar: raiz de ");
    scanf("%lf", &x);
    Ro = x;

    do{

        Rn = 0.5 * (Ro + x / Ro);
        RnMenosRo = Rn - Ro;
        Ro = Rn;

    } while (RnMenosRo > 0.000001 && RnMenosRo > 0 || RnMenosRo < -0.000001 && RnMenosRo < Ro);

    printf("%.6lf", Rn);

}
