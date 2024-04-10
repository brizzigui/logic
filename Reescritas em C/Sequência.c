#include <stdio.h>

int main(){
    int n, contExterno = 0, contInterno = 0;
    scanf("%d", &n);

    while (contExterno <= n){
        contExterno++;
        printf("\n%d", contExterno);
        int i = contExterno;

        while (contInterno < contExterno){
            contInterno++;
            printf(" %d", i);
            i--;

        }

        contInterno = 0;
    }
}
