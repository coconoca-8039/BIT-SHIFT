#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define NEWLINE printf("\n");

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/
uint16_t original = 0x10;
/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*/

int hexToBinary(uint64_t hex){
    for (int i = 15; i >= 0; i--){
        if ((hex & (1 << i))){  // // 16進数の値と、1を左にiビットシフトした値をAND演算
            printf("1");
        }
        else{
            printf("0");
        }
        if (i % 4 == 0){ // 4ビットごとにスペースを挿入
            printf(" ");
        }
    }
    NEWLINE;
    return 0;
}

uint16_t rightShift(uint64_t value, int shiftAmount){
    return value >> shiftAmount;
}

uint16_t leftShift(uint64_t value, int shiftAmount){
    return value << shiftAmount;
}

/*nビット目を0にする*/
uint16_t clearBit(uint16_t value, uint16_t n){
    // And演算で両方が1の時だけ1にする
    // ビット反転を利用して狙いのビットだけが0の値を作る
    return value & ~(1 << n);
}

/*nビット目を1にする*/
uint16_t setBit(uint16_t value, uint16_t n){
    // Or演算でどちらかに1があれば1にする
    return value | (1 << n);
}

void show_original(){
    printf("オリジナル      : ");
    hexToBinary(original);
}

int main(){
    printf("original 10進数 : %u\n", original);  // llは64ビット整数
    printf("original 16進数 : %X\n", original);  // uは符号なし整数, Xは16進数
    show_original();
    NEWLINE;

    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    uint16_t shifted_right = 0x00;
    shifted_right = rightShift(original, 1);
    printf("右シフト 10進数 : %u\n", shifted_right);
    printf("右シフト 16進数 : %X\n", shifted_right);
    printf("右シフト  2進数 : ");
    hexToBinary(shifted_right);
    NEWLINE;

    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    uint16_t shifted_left = 0x00;
    shifted_left = leftShift(original, 1);
    printf("左シフト 10進数 : %u\n", shifted_left);
    printf("左シフト 16進数 : %X\n", shifted_left);
    printf("左シフト  2進数 : ");
    hexToBinary(shifted_left);
    NEWLINE;

    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    uint16_t clear_value = 0x00;
    clear_value = clearBit(original, 4);
    printf("クリア  10進数  : %u\n", clear_value);
    printf("クリア  16進数  : %X\n", clear_value);
    show_original();
    printf("クリア   2進数  : ");
    hexToBinary(clear_value);
    NEWLINE;

    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
    uint16_t set_value = 0x00;
    set_value = setBit(original, 3);
    set_value = setBit(set_value, 2);
    set_value = setBit(set_value, 1);
    set_value = setBit(set_value, 0);
    printf("セット  10進数  : %u\n", set_value);
    printf("セット  16進数  : %X\n", set_value);
    show_original();
    printf("セット   2進数  : ");
    hexToBinary(set_value);
    NEWLINE;

 
    return 0;
}