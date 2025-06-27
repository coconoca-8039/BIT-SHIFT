#include <stdio.h>
#include <math.h>

int getDpIndex(float value) {
    if (value >= 1000) {
        return 4;
    } else if (value >= 100) {
        return 3;
    } else if (value >= 10) {
        return 2;
    } else {
        return 0;
    }
}

int main() {
    float value = 112.2;  // 表示したい4桁の整数
    printf("value: %f\n", value);
    int dpIndex = 0;     // 小数点の位置
    int digits[4] = {0, 0, 0, 0};

    dpIndex = getDpIndex(value);
    printf("dpIndex: %d\n", dpIndex);

    long scaledValue = (long)(value * 1000 + 0.5); // ← 四捨五入のために+0.5した方が安全
    printf("scaledValue: %ld\n", scaledValue);

    digits[0] = (scaledValue / 1000) / 1000 % 10; // 千の位
    digits[1] = (scaledValue / 1000) / 100 % 10;  // 百の位
    digits[2] = (scaledValue / 1000) / 10 % 10;   // 十の位
    digits[3] = (scaledValue / 1000) % 10;        // 一の位

    printf("digits[0] (千の位): %d\n", digits[0]);
    printf("digits[1] (百の位): %d\n", digits[1]);
    printf("digits[2] (十の位): %d\n", digits[2]);
    printf("digits[3] (一の位): %d\n", digits[3]);

    long scaledValue_3 = (long)(value * 1000 + 0.5); // ← 四捨五入のために+0.5した方が安全
    printf("\n");
    digits[0] = (scaledValue_3 / 1000) / 100 % 10;
    digits[1] = (scaledValue_3 / 100) / 10 % 10;
    digits[2] = (scaledValue_3 / 10) % 10;
    digits[3] = scaledValue_3 % 10;

    printf("digits[0] (千の位): %d\n", digits[0]);
    printf("digits[1] (百の位): %d\n", digits[1]);
    printf("digits[2] (十の位): %d\n", digits[2]);
    printf("digits[3] (一の位): %d\n", digits[3]);

    long scaledValue_2 = (long)(value * 1000 + 0.5); // ← 四捨五入のために+0.5した方が安全
    printf("\n");
    digits[0] = (scaledValue_2 / 1000) % 10;
    digits[1] = (scaledValue_2 / 100) % 10;
    digits[2] = (scaledValue_2 / 10) / 10 % 10;
    digits[3] = scaledValue_2 % 10;

    printf("digits[0] (千の位): %d\n", digits[0]);
    printf("digits[1] (百の位): %d\n", digits[1]);
    printf("digits[2] (十の位): %d\n", digits[2]);
    printf("digits[3] (一の位): %d\n", digits[3]);

    long scaledValue_4 = (long)(value * 1000 + 0.5); // ← 四捨五入のために+0.5した方が安全
    printf("\n");
    digits[0] = (scaledValue_4 / 1000) % 10;
    digits[1] = (scaledValue_4 / 100) % 10;
    digits[2] = (scaledValue_4 / 10) % 10;
    digits[3] = scaledValue_4 % 10;

    printf("digits[0] (千の位): %d\n", digits[0]);
    printf("digits[1] (百の位): %d\n", digits[1]);
    printf("digits[2] (十の位): %d\n", digits[2]);
    printf("digits[3] (一の位): %d\n", digits[3]);

    return 0;
}
