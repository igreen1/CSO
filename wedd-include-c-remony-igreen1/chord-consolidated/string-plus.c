#include <stdbool.h>
#include <string.h>  // In case your implementation needs it. It does not have to.

// Helper function for determining if a string validly expresses a non-negative integer.
// Feel free to use where needed (and to study it as an example).
bool is_non_negative_numeral(char* numeral) {
    int numeral_length = strlen(numeral);
    for (int i = 0; i < numeral_length; i++) {
        if (numeral[i] < '0' || numeral[i] > '9') {
            return false;
        }
    }

    return true;
}

// ***** MOVE YOUR IMPLEMENTATION HERE! *****
void split_string_at_index(char* string, int index, char* left, char* right) {

    //Copied from oh-say-can-you-see/split-string-at-index.c (directly)
    int i = 0; //used in two loops to iterate through original string
    for(;i<index;i++)
    {
        left[i] = string[i];
        if(string[i] == '\0')break; //just to be sure of input ;) don't want out of bounds error
    }

    left[i] = '\0'; //terminate that end 

    while(string[i] != '\0')
    {
        right[i-index] = string[i]; 
        i++;
    }

    right[i-index] = '\0';
}

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
