// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

#define MAX_SUBSTRING 15
int main(int argc, char** argv) {

    //correct number of args
    if(argc != 2)
    {
        printf("This program requires exactly one command line argument.\n");
        return -1;
    }
    
    //variables to use later :)
    char *to_split = argv[1]; //unnecessary renaming of argv[1] to make it clearer imo
    char note[MAX_SUBSTRING];   //the note output
    char chord[MAX_SUBSTRING];  //the chord output

    int flag = split_note_and_chord(to_split, note, chord);

    //if valid input, with valid output
    if(flag == 0)
    {
        printf("[%s] [%s]\n", note, chord);
    }
    else
    {
        printf("%s is not a valid chord\n", argv[1]);
    }
    
    return 0;
}
