// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"
#include "string-plus.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {

    //correct number of arguments?
    if(argc != 3)
    {
        printf("This program requires exactly two command line arguments:\n");
        printf("The NOTES index and the CHORD_SUFFIXES index of the note and chord suffix to print, respectively.\n");
        return -1;
    }

    //check if input is valid (is a non-negative numeral)
    if(!is_non_negative_numeral(argv[2]) || !is_non_negative_numeral(argv[1]) )
    {
        //improper input
        printf("Either %s or %s is not a valid index.\n", argv[1], argv[2]);
        return -1;
    }

    //okay, then we can convert :)
    int note_index = atoi(argv[1]);
    int chord_index = atoi(argv[2]);

    //numerical input, yes, but within our bounds?
    //technically don't need the below 0s but ehh, double check haha (since we know they are /positive/)
    //  consider them correcting in case someone messes up 'is non negative' in a later version
    if(note_index > NOTE_COUNT || note_index < 0 || chord_index > CHORD_COUNT || chord_index <0)
    {
        //printf("Either %s or %s is out of range.\n", argv[1], argv[2]);
        //TRICK: the 04 --> 4 which means ATOI was dont it, so print the integers
        printf("Either %d or %d is out of range.\n", note_index, chord_index);
        return -1;
    }

    print_chord(note_index, chord_index);
}