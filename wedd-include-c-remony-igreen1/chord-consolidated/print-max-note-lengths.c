// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    // ***** Yes, now you get to implement this too. *****
    //ex output
    //The longest NOTES string is 312325 characters long and the longest CHORD_SUFFIXES string is 7281031 characters long.

    //no input from command line. 
    // not checking if they did becaues program can run regardless. They want to put garbage in? I'll still give them beauty out

    //check if an error occured
    int cmax, nmax;
    cmax = get_max_chord_suffix_length();
    nmax = get_max_note_length();

    if(cmax < 0 || nmax < 0)
    {
        printf("ERROR: CHORD OR NOTES DECLARED POORLY");
        return -1;
    }

    printf("The longest NOTES string is %d characters long and the longest CHORD_SUFFIXES string is %d characters long\n", get_max_note_length(), get_max_chord_suffix_length());
    return 0;
}
