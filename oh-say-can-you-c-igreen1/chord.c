#include <stdbool.h> //haha, so I guess I need is_non_neg_numeral
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

#define INVALID -1
#define MAX_SUBSTRING 15


//function headers
int string_compare(char* a, char* b);
int get_chord_index(char* string);
bool is_non_negative_numeral(char* numeral);
int get_note_index(char* string);
void print_chord(int, int);
int split_note_and_chord(char* string, char* note, char* chord);

// ***** Feel free to add more functions if you think they will make it easier to implement this program.
int main(int argc, char** argv) {

    //check basic input
    if(argc != 2)
    {
        printf("This program requires exactly one command line argument.\n");
        return -1;
    }

    //split note and chord iytoyts
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


/*
 *      copied functions below
 *      (i haven't really organized them, sorry. I mean, technically, these should all be linked anyways)
 */


int get_max_note_length() {

    int end_of_out_array = sizeof(NOTES)/sizeof(char*); //size of NOTES outer data structure

    int max_size = -1;
    int temp_size;

    int j;
    for(int i = 0; i < end_of_out_array; i++)
    {
        //now, iterate through the string
        j = 0; //string iterator
        temp_size = 0;

        while(NOTES[i][j] != '\0')
        {
            temp_size++;
            j++;
        }

        if(temp_size > max_size)
            max_size = temp_size;

    }

    return max_size;
}

// ***** IMPLEMENT ME! *****
void split_string_at_index(char* string, int index, char* left, char* right) {

    int i = 0; //used in two loops
    for(;i<index;i++)
    {
        left[i] = string[i];
        if(string[i] == '\0')break; //just to be sure of input ;)
    }

    left[i] = '\0';

    while(true)
    {
        right[i-index] = string[i]; 
        if(string[i] == '\0') break; //assumes valid string !!
        i++;
    }

}
int get_max_chord_suffix_length() {

    int end_of_out_array = (sizeof(CHORD_SUFFIXES) / sizeof(char*) ); //size of chord_suffix data structure

    //variables used in checking size
    int max_size = -1;
    int temp_size;

    //loop variables (putting this in the loop doesn't work with my compiler ever since i installed something for research)
    //  i think the program downgraded my version of C LOL
    //  i'm working on it :)
    int j;
    for(int i = 0;i<end_of_out_array; i++)
    {
        //get size, compare it to max size, :)
        j = 0; //for iterating through string
        temp_size=0;    //the size of the current string
        while(CHORD_SUFFIXES[i][j] != '\0')
        {
            temp_size++;
            j++;
        }

        if(temp_size > max_size)
            max_size = temp_size;
    }

    if(max_size == -1)
        puts("Chord suffix had some error, no length recorded. Is CORD_SUFFIXES defined?");

    return max_size;
}
// ***** Feel free to add more functions if you think they will make it easier to implement split_note_and_chord.
int split_note_and_chord(char* string, char* note, char* chord) {

    //okay so there is probably a more elegant solution bbbuuuuttt
    //just see if any valid substring (starting from lagest possible size of note) is a note
    //and same for chords

    //PROBLEMATIC EDGE CASE: end of a note corresponds to beginning of chord suffix (does this happen?)

    int output = -1;

    int max_note = get_max_note_length();
    int max_chord_suffix = get_max_chord_suffix_length();

    //start with note, is there any valid substring of note within the bounds of max note present in the string

    char left[MAX_SUBSTRING];
    char right[MAX_SUBSTRING];

    for(int i = max_note; i > 0; i--)
    {
        split_string_at_index(string, i, left, right); //this will return a POSSIBLE combination of note, chord in left, right repsectively

        //if right is larger than a max chord, this is an invalid posible combination, don't consider it
        if( sizeof(right)/ sizeof(char*) > max_chord_suffix )
        {
            continue; 
        }
        else
        {
            //if this is an actually possible combination (ie, it creates a chorda and note combo), we're done
            if( get_note_index(left) >= 0 && get_chord_index(right) >= 0 )
            {
                //mini-debugging because my ide is acting up (commented out in prod)
                //printf("%d: %s found at : %d and %s found at %d\n",i, left, get_note_index(left), right,get_chord_index(right));
                output = 0;
                strcpy(note, left);
                strcpy(chord, right);
                chord = right;
                return 0;
            }
        }
        

    }

    return -1;
}

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
