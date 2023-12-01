#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int process(char *p);
char check_num(char val, char *spell, char *in);
char get_num(char *str);

// one, two, three, four, five, six, seven, eight, and nine

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
        register char tmp;
        tmp = get_num(p);
        // found it
        if(tmp != '\0') {
            if (!set) {
                in[0] = tmp;
                in[1] = tmp;
                set = 1;
            } else {
                in[1] = tmp;
            }
        }
        // Next
        p++;
    }
    in[2] = '\0';
    return atoi(in);
}


// Check is a letter
// Returns '\0' if not
// Otherwise the char representing
// the letter
// o - search one
// t - two, three
// f - four, five
// s - six, seven
// e - eight
// n - nine
char get_num(char *str) {
    char out = '\0';
    // Sanity check
    if (*str == out)
        return out;
    if (isdigit(*str)) {
        out = *str;
    } else if(isalpha(*str)) {
        switch(*str) {
        case 'o':
            out = check_num('1', "one", str);
            break;
        case 't':
            out = check_num('2', "two", str);
            if (out == '\0')
                out = check_num('3', "three", str);
            break;
        case 'f':
            out = check_num('4', "four", str);
            if (out == '\0')
                out = check_num('5', "five", str);
            break;
        case 's':
            out = check_num('6', "six", str);
            if (out == '\0')
                out = check_num('7', "seven", str);
            break;
        case 'e':
            out = check_num('8', "eight", str);
            break;
        case 'n':
            out = check_num('9', "nine", str);
            break;
        }
    }
    return out;
}


char check_num(char val, char *spell, char *in) {
    register int len = strlen(spell);
    if(strlen(in) >= len && strncmp(spell, in, len) == 0) {
        return val;
    }
    return '\0';
}
