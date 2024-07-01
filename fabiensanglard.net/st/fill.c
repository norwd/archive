#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void fill(uint8_t* addr, size_t amount, char value) {
    for (size_t i = 0; i < amount; i++) {
        *(addr + i) = value;
    }
}

int main(int argc, char **argv) {
    size_t s = 1<<30;
    uint8_t* buffer = (uint8_t*)malloc(s);
    fill(buffer, s, atoi(argv[0]));
    return EXIT_SUCCESS;
}