// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {

    //check basic input
    if(argc != 2)
    {
        printf("This program requires exactly one command line argument.\n");
        return -1;
    }

    //split note and chord iytoyts
    const int MAX_SUBSTRING = 10; //should use dynamic mem. butt uhhh, we haven't learned that
    char note[MAX_SUBSTRING];
    char chord[MAX_SUBSTRING];

    int flag = split_note_and_chord(argv[1], note, chord); //if -1, error in split (bad output)

    //check if input was valid on split
    if(flag < 0 )
    {
        printf("%s is not a valid chord.\n", argv[1]);
        return -1;
    }

    //get index of input
    int note_index = get_note_index(note);
    int chord_index = get_chord_index(chord);
    
    //Technically, our input has already been validated by flag above, but nice to always double check
    //if this error comes up, there's a flaw in my /logic/ ://///
    //but it hasn't :)
    if( note_index < 0 || note_index > NOTE_COUNT || chord_index < 0 || chord_index > CHORD_COUNT) 
    {
        printf("Something went wrong in split, the indices are out of bounds.\n");
        return -1;
    }

    print_chord(note_index, chord_index);

}