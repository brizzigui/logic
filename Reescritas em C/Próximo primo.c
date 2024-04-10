#include <stdio.h>

int main(){
    int num, divisor = 2, achou = 0;
    scanf("%d", &num);

    while (achou == 0){
        while (num%divisor != 0 && divisor < num){
            divisor++;
            if (divisor == num - 1 && num > 1){
                printf("%d", num);
                achou = 1;
            }
        }
        divisor = 2;
        num++;
    }
}
