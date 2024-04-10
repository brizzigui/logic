#include <stdio.h>

int main(){
    int num = 1, max, adicao = 1;
    scanf("%d", &max);

    while (num <= max && num >= 1){
        printf("%d ", num);
        num = num + adicao;

        if (num == max){
            adicao = -1;
        }
    }
}
