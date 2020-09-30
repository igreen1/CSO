#include <stdio.h>
#include <string.h>

#include "notes.h"

#define INVALID -1


/*
*   Takes two strings as output, returns a fake boolean
*   1 if equal
*   0 if not equal
*/
int string_compare(char* a, char* b)
{
    int i = 0, j = 0;

    if(strlen(a) != strlen(b)) return 0; //not a valid string

    while(a[i] != '\0' && b[j] != '\0'){

        if(a[i] != b[j]){
            return 0;
        }

        i++;j++;
    
    }
    
  
    return 1;
}


// ***** IMPLEMENT ME! *****
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

int main(int argc, char** argv) {

    //check basic info on the input
    if (argc != 2) {
        printf("This program requires exactly one command line argument.\n");
        //printf("The chord to be tested\n"); NOT IN DOCUMENTATION
        return 1;
    }

    int output = get_chord_index(argv[1]); //either the index or a negative number flagging that input didn't work


    if(output < 0)
    { 
        printf("%s is not a valid chord\n", argv[1]);
    }
    else //is valid
    {
        printf("%s is at CHORD_SUFFIXES index %d\n", argv[1], output);
    }


}
