// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

int main(int argc, char** argv) {

    //check basic info on the input
    if (argc != 2) {
        printf("This program requires exactly one command line argument.\n");
        //printf("The chord to be tested\n"); NOT IN DOCUMENTATION
        return 1;
    }

    int output = get_chord_index(argv[1]); //either the index or a negative number flagging that input didn't work


    if(output < 0)
    { 
        printf("%s is not a valid chord\n", argv[1]);
    }
    else //is valid
    {
        printf("%s is at CHORD_SUFFIXES index %d\n", argv[1], output);
    }


}