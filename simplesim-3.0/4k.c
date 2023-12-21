#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 7; i++) {
        int bsize = 1 << (3 + i);
        int nsets = 4096 / bsize;
        char commend[512];

        snprintf(commend, sizeof(commend), "./sim-cache -redir:sim 4k_%d_%d.txt -max:inst 1000000 -cache:il1 il1:%d:%d:1:l -cache:il2 il2:4096:1024:1:r ../benchmark/gcc/gcc00.peak.ev6 ../benchmark/gcc/cp-decl.i", nsets, bsize, nsets, bsize);

        system(commend);
    }

    return 0;
}

