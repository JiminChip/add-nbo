#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

//network file to host unsigned long
uint32_t nfile_to_hul(char *file_name) {
    uint8_t readBuf[4] = {0,};
    FILE* fp = fopen(file_name, "rb");


    if (fp == NULL) {
        perror("file rb open error");
        exit(1);
    }

    size_t size = fread(readBuf, 1, 4, fp);
    if (size < 4) {
        perror("file size error");
        exit(1);
    }

    fclose(fp);

    return (uint32_t)(readBuf[0] << 24) | (uint32_t)(readBuf[1] << 16) | (uint32_t)(readBuf[2] << 8) | (uint32_t)(readBuf[3]);
}


int main(int argc, char* argv[]) {
    uint32_t tmp_val;
    uint32_t result = 0;

    if (argc < 3) {
        perror("parameter error");
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