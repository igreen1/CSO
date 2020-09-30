#include <stdio.h>
#include <string.h>

#include "notes.h"


#define MAX_SUBSTRING 15
#define INVALID -1

//header files
int string_compare(char* a, char*b);
int get_chord_index(char*);
int get_note_index(char*);
void split_string_at_index(char* string, int index, char* left, char* right);
int get_max_chord_suffix_length();
int get_max_note_length();

// ***** IMPLEMENT ME! *****
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


/*
Previously created functions
Technically, I should create header files
Then include them in the path
Then use them through that but not for this assignment yet :)
*/

int string_compare(char* a, char* b)
{
    int i = 0, j = 0;

    if(strlen(a) != strlen(b)) return -1;

    while(a[i] != '\0' && b[j] != '\0'){

        if(a[i] != b[j]){
            return -1;
        }

        i++;j++;
    
    }

    return 1;
}


// ***** IMPLEMENT ME! ***** done
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

// ***** IMPLEMENT ME! ***** done
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

// ***** IMPLEMENT ME! *****
void split_string_at_index(char* string, int index, char* left, char* right) {

    int i = 0; //used in two loops
    for(;i<index;i++)
    {
        left[i] = string[i];
        if(string[i] == '\0')break; //just to be sure of input ;)
    }

    left[i] = '\0';

    while(1)
    {
        right[i-index] = string[i]; 
        if(string[i] == '\0') break; //assumes valid string !!
        i++;
    }

}

// ***** IMPLEMENT ME! *****
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