#include <stdio.h>

int main(){

    FILE *fptr;

    // fptr = fopen("newflag00.enc", "rb");
    fptr = fopen("newflag00.enc", "rb");
    fseek(fptr, 0, 2);
    int len = ftell(fptr);
    fseek(fptr, 0, 0);
    unsigned char mystring[len];
    fread(mystring, len, 1, fptr);
    srand(1655780698);
    for(int i = 0; i < len; i++) {
        int rand1 = rand();
        int rand2 = rand();
        rand2 = rand2 & 7;
        mystring[i] = mystring[i] >> rand2 | mystring[i] << 8 - rand2;
        mystring[i] = mystring[i] ^ rand1;
        printf("%x ", mystring[i]);
    }


    fclose(fptr);
    return 0;
}