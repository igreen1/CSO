#include <stdbool.h> //haha, so I guess I need is_non_neg_numeral
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

#define INVALID -1

int string_compare(char* a, char* b);
int get_chord_index(char* string);
bool is_non_negative_numeral(char* numeral);
int get_note_index(char* string);



void print_chord(int note_index, int chord_index) {

    //oops, i forgot this! must print the stuff beforehand :)
    printf("%s%s: ",NOTES[note_index], CHORD_SUFFIXES[chord_index] );

    //don't ~need~ to copy this but it makes me feel better (ditto to NumOfJumps)
    int jumps[3];
    for(int i = 0; i < 3; i++)
    {
        jumps[i] = CHORD_STEPS[chord_index][i];
    }

    int number_of_jumps = CHORD_STEP_COUNT[chord_index];

    //print initial note
    printf("%s ", NOTES[note_index]); //!!!!! okay the function returns VOID, so no return to main. BUUUTTT, must print. Therefore, print in this function
                                        //  ALSO!! ~you~ put the "puts("");" at the end, which I'm taking to mean that this CAN print in this function?
                                        //  I'll email to check ? 

    //used ii, jj as a lil matlab joke ;) lil engineering joke
    int ii = 0; //jump iterator
    int jj = note_index; //this is the current note to be added (the iterator through the notes array)
    for(; ii < number_of_jumps; ii++)
    {
        jj += jumps[ii];
        if(jj >= NOTE_COUNT) jj -= NOTE_COUNT; //wraparound

        //print the next note
        printf("%s ", NOTES[jj]);
    }

    //end with an end line
    puts("");
}

// ***** Feel free to add more functions if you think they will make it easier to check argument validity.
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

/*
*       COPIED FUNCTIONS BELOW ~ PRETEND THEY WERE #INCLUDED
*/

bool is_non_negative_numeral(char* numeral) {
    int numeral_length = strlen(numeral);
    for (int i = 0; i < numeral_length; i++) {
        if (numeral[i] < '0' || numeral[i] > '9') {
            
            return false;
        }
    }

    return true;
}

int string_compare(char* a, char* b)
{
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
int get_chord_index(char* string) {
    int index = -1; //aka index = INVALID

    //create size of notes
    int size_of_chord = sizeof(CHORD_SUFFIXES)/sizeof(char*);

    for(int i = 0; i < size_of_chord; i++)
    {
        if(string_compare(string, CHORD_SUFFIXES[i]) == 1){
            index = i;
            return index;   
        }
    } 

    return index;
}

// ***** IMPLEMENT ME! *****
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
