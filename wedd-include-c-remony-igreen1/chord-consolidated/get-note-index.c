// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("This program requires exactly 1 command line arguments.\n");
        //printf("The note to be tested\n");
        return 1;
    }

    int output = get_note_index(argv[1]);

    if(output < 0)
    {
        printf("%s is not a valid note\n", argv[1]);
    }
    else
    {
        printf("%s is at NOTES index %d\n", argv[1], output);
    }
}