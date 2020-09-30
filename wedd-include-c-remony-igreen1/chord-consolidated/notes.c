#include <stdbool.h>
#include <stdio.h>
#include <string.h>  // In case your implementation needs it. It does not have to.

#include "string-plus.h"
#include "notes.h"

char *NOTES[] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
int NOTE_COUNT = sizeof(NOTES) / sizeof(char*);

// C has more sophisticated ways to express these structures, but at our level we
// stay with multiple arrays that have coordinated index values (i.e., the same
// index on these arrays corresopnds to the same type of chord).
char *CHORD_SUFFIXES[] = {
    "",     // major
    "m",    // minor
    "7",    // dominant 7th
    "M7",   // major 7th
    "m7",   // minor 7th
    "dim7"  // diminished 7th
};

int CHORD_COUNT = sizeof(CHORD_SUFFIXES) / sizeof(char*);

// C needs to know the maximum size of the inner array, but not the outer one 🤷🏽‍♂️
int CHORD_STEPS[][3] = {
    {4, 3},     // major
    {3, 4},     // minor
    {4, 3, 3},  // dominant 7th
    {4, 3, 4},  // major 7th
    {3, 4, 3},  // minor 7th
    {3, 3, 3}   // diminished 7th
};

// Yes, there are ways of computing this dynamically but for now we choose to list
// them explicitly to show how these arrays correspond to each other.
int CHORD_STEP_COUNT[] = {
    2,  // major
    2,  // minor
    3,  // dominant 7th
    3,  // major 7th
    3,  // minor 7th
    3   // diminished 7th
};

// ***** MOVE YOUR IMPLEMENTATIONS HERE! *****
int get_max_note_length() {
    //again, I didn't notice this in notes. I could replace it easily, but i'm choosing not to 
    //  think of it as a lil inside joke for whoever reads this :)
    // int end_of_out_array = NOTES_COUNT :)
    int end_of_out_array = sizeof(NOTES)/sizeof(char*); //size of NOTES outer data structure

    int max_size = -1; //flag if doesn't work
    int temp_size; //size of the current note in the array 
        //(techinically I could just use j but I like better naming conventions and seperating iterators)

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

        if(temp_size > max_size)    max_size = temp_size;

    }

    return max_size;
}

int get_max_chord_suffix_length() {
    int end_of_out_array = (sizeof(CHORD_SUFFIXES) / sizeof(char*) ); //size of chord_suffix data structure

    //variables used in checking size
    int max_size = -1;
    int temp_size;

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

int get_chord_index(char* string) {
    int index = -1; //aka index = INVALID

    //create size of notes
    //I found out later this is already in notes.h
    //so take this instead as a monument to my knowledge of c? 
    // you could also say size_of_chord = CHORD_COUNT
    //  but no reason to change it in my opinion, its a very small flex in these trying times ;)
    int size_of_chord = sizeof(CHORD_SUFFIXES)/sizeof(char*);

    for(int i = 0; i < size_of_chord; i++)
    {
        //if our chord is equal to a chord in chord_suffixies
        if(string_compare(string, CHORD_SUFFIXES[i]) == 1){

            //it is our answer and return
            index = i;
            return index;   
        }
    } 

    //no equal input, return -1 as a flag
    return index;

}

int split_note_and_chord(char* string, char* note, char* chord) {
     //okay so there is probably a more elegant solution bbbuuuuttt
    //just see if any valid substring (starting from lagest possible size of note) is a note
    //and same for chords

    //PROBLEMATIC EDGE CASE: end of a note corresponds to beginning of chord suffix (does this happen?)

    int output = -1;

    int max_note = get_max_note_length();
    int max_chord_suffix = get_max_chord_suffix_length();

    //start with note, is there any valid substring of note within the bounds of max note present in the string

    const int MAX_SUBSTRING = 10; //larger than the largest NOTE+CHORD COMBO (previously efined but not in this file. 
                                    //deally, this would be calculated by dynamic memory is annoying)
    char left[MAX_SUBSTRING];
    char right[MAX_SUBSTRING];

    for(int i = max_note; i > 0; i--)
    {
        split_string_at_index(string, i, left, right); //this will return a POSSIBLE combination of note, chord in left, right repsectively

        //if right is larger than a max chord, this is an invalid posible combination, don't consider it. ditto to notes (though I think redundant)
        if( sizeof(right)/ sizeof(char*) > max_chord_suffix || sizeof(left)/sizeof(char*) > max_note)
        {
            continue; 
        }
        else
        {
            //if this is an actually possible combination (ie, it creates a chorda and note combo),
            if( get_note_index(left) >= 0 && get_chord_index(right) >= 0 )
            {
                //mini-debugging because my ide is acting up
                //printf("%d: %s found at : %d and %s found at %d\n",i, left, get_note_index(left), right,get_chord_index(right));

                output = 0;
                strcpy(note, left); //copy 'left' into note output
                strcpy(chord, right); //copy 'right' into chord output
                //chord = right;
                return output; //why not just constants? in case I want to return differently in the future ?
            }
        }
        

    }

    return output;
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
