#include <stdbool.h> //haha, so I guess I need is_non_neg_numeral
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

//COPIED!
int string_compare(char* a, char* b)
{
    //iterators
    int i = 0, j = 0;

    while(a[i] != '\0' && b[j] != '\0'){

        if(a[i] != b[j]){
            return 0;
        }

        i++;j++;
    
    }
    
    if(a[i] != b[i] ) return 0;
    //off-by-one error since strings may be different lengths but contain equal substrings to a point

    return 1;
}

// ***** IMPLEMENT ME! *****
//same as get_chord_index but CTRL+F chord -> notes
int get_note_index(char* string) {

    int index = -1; //aka index = INVALID

    //create size of notes
    int size_of_notes = sizeof(NOTES)/sizeof(char*);

    for(int i = 0; i < size_of_notes; i++)
    {
        if(string_compare(string, NOTES[i]) == 1){
            index = i;
            return index;   
        }
    } 

    return index;
}



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
