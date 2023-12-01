#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int process(char *p);

int main(int c, char** v) {
    char p[80];
    int n;
    long total = 0;

    printf("Hello advent of code 2023!\n");
    while(scanf("%s", p) != EOF) {
        total += process(p);
    };
    printf("total: %ld\n", total);
    exit(0);
}

int process(char* p) {
    int set = 0;
    char in[3];
    int out = 0;
    if( p == NULL)
        return out;

    while( *p != '\0') {
        if (isdigit(*p)) {
            if (!set) {
                in[0] = *p;
                in[1] = *p;
                set = 1;
            } else {
                in[1] = *p;
            }
        }
        p++;
    }
    in[2] = '\0';
    return atoi(in);
}
