#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct Options {
    int array_size;
    int source_size;
    int stack_size;
};

void usage() {
    printf("Usage: bf <options> <file>\n");
    printf("\t-s\tSet size of array\n\t\tDefault: 32kiB\n");
    printf("\t-f\tSet max size of surce file\n\t\tDefault: 16kiB\n");
    printf("\t-k\tSet size of instruction stack\n\t\tDefault: 32B\n");
}

void brainfuck(char *file, struct Options opt) {
    // Open file
    char c;
    FILE *fptr;
    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("Error reading file\n");
        return;
    }
    
    // Read code into memory
    char code[opt.source_size];
    int cptr = 0;
    while ((c = fgetc(fptr)) != EOF) {
        code[cptr++] = c;
    }

    // Create stack
    int stack[opt.stack_size];
    int sptr = 0;

    // Create array
    char array[opt.array_size];
    int aptr = 0;
    for (int i = 0; i < opt.array_size; i++) {
        array[i] = 0;
    }

    // The Interpretor
    for (int i = 0; i < cptr; i++) {
        switch (code[i]) {
            case '>':
                aptr++;
                break;
            case '<':
                aptr--;
                break;
            case '+':
                array[aptr]++;
                break;
            case '-':
                array[aptr]--;
                break;
            case '.':
                printf("%c",array[aptr]);
                break;
            case ',':
                scanf("%c",&array[aptr]);
                break;
            case '[':
                stack[sptr] = i;
                sptr++;
                break;
            case ']':
                if (array[aptr] != 0) {
                    i = stack[sptr-1];
                } else {
                    sptr--;
                }
                break;
        }
    }
}

int main(int argc, char **argv) {
    int option;
    struct Options opt = {
        16384,  32768,  32
    };

    // Get options from agruments
    while ((option = getopt(argc, argv, "hds:")) != -1) {
        switch (option) {
            case 's':
                opt.array_size = optarg[0];
                break;
            case 'f':
                opt.source_size = optarg[0];
                break;
            case 'k':
                opt.stack_size = optarg[0];
                break;
            case 'h':
                usage();
                return EXIT_SUCCESS;
        }
    }

    // Interpret 
    char *file;
    for(; optind < argc; optind++) {
        file = argv[optind];
        brainfuck(file, opt);
    }

    return EXIT_SUCCESS;
}
