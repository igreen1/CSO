#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** IMPLEMENT ME! *****
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

// ***** IMPLEMENT ME! *****
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
