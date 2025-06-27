#include <stdio.h>
#include <math.h>

int main(){
    double aaaa = 558.50;
    double bbbb = 111.10;
    double cccc = 11.11;
    double dddd = 111.1;
    int digits[4] = {0, 0, 0, 0};

    printf("aaaa: %f\n", aaaa);
    printf("bbbb: %f\n", bbbb);
    printf("cccc: %f\n", cccc);
    printf("dddd: %f\n", dddd);

    // 小数1桁分スケーリング → 712.2 → 7122
    int scaledValue = (int)(aaaa * 10 + 0.5);  // 四捨五入付き

    // 1桁ずつ抽出（上位桁から）
    digits[0] = (scaledValue / 1000) % 10;
    digits[1] = (scaledValue / 100) % 10;
    digits[2] = (scaledValue / 10) % 10;
    digits[3] = scaledValue % 10;

    printf("digits[0] = %d\n", digits[0]);
    printf("digits[1] = %d\n", digits[1]);
    printf("digits[2] = %d\n", digits[2]);
    printf("digits[3] = %d\n", digits[3]);

}