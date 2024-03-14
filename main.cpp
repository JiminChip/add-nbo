#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <arpa/inet.h>

//network file to host unsigned long
uint32_t nfile_to_hul(char *file_name) {
    uint32_t readBuf;
    FILE* fp = fopen(file_name, "rb");


    if (fp == NULL) {
        puts("file rb open error");
        exit(1);
    }

    size_t size = fread(&readBuf, 1, 4, fp);
    if (size < 4) {
        puts("file size error");
        exit(1);
    }

    fclose(fp);

    return ntohl(readBuf);
}


int main(int argc, char* argv[]) {
    uint32_t tmp_val;
    uint32_t result = 0;

    if (argc < 3) {
        puts("parameter error");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        tmp_val = nfile_to_hul(argv[i]);
        printf("%d(0x%x)", tmp_val, tmp_val);
        if (i < argc - 1) {
            printf(" + ");
        }
        result += tmp_val;
    }
    printf(" = %d(0x%x)\n", result, result);

    return 0;
}