#include <stdio.h>
#include <stdlib.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

#define BUFFER_SIZE 1024
#define MAX_PROBABILITY 100

#define OPEN_CHAR '.'
#define WEEPER_CHAR 'W'

// ***** IMPLEMENT ME! *****
/**
 * Allocates the memory required for a game with the given dimensions, and sets those dimensions
 * in the resulting game structures `width` and `height` fields.
 *
 * In particular, sufficient memory should be allocated for:
 * - The `mcw_game` structure
 * - The two-dimensional `field` array of square contents (`open` or `weeper`)
 * - The two-dimensional `status` array reflecting the player’s progress
 *   (squares start out `hidden` then are either `revealed` or `flagged` as the game progresses)
 *
 * This function is given enough information to allocate memory _precisely_—no more and no less
 * than required. The implementation must reflect this precision.
 *
 * This function is only supposed to _allocate_ memory for the game, not initialize its squares.
 * Aside from memory, the only other values that this function should set are the `width` and
 * `height` of the game, as indicated by the function arguments.
 *
 * Excessively large hard-coded memory allocations will incur large deductions even if they
 * produce a functional game.
 *
 * You can use the given `initialize_random_game` and `initialize_file_game` functions as
 * references for how a correctly-allocated game structure and arrays will be used.
 */
mcw_game* alloc_game(int width, int height) {

    //malloc and done
    mcw_game* game = (mcw_game *) malloc(sizeof(mcw_game *));
    game->field = malloc(sizeof(mcw_square *) * height);
    for(int i =0; i < height; ++i)
    {
        game->field[i] = malloc(sizeof(mcw_square **) * width);

    }
    game->status = malloc(sizeof(mcw_status*) * height);
    for(int i =0; i < height; ++i)
    {
        game->status[i] = malloc(sizeof(mcw_status**) * width);

    }

    game->width = width;
    game->height = height;

    return game;
}

// ***** IMPLEMENT ME! *****
void free_game(mcw_game* game) {
    for(int i = 0; i < game->height; ++i)
    {
        free(game->field[i]);
    }
    free(game->field);
    for(int i = 0; i < game->height; ++i)
    {
        free(game->status[i]);
    }
    free(game->status);
    free(game);
    return;
}

// ***** IMPLEMENT ME! *****
void show_all(mcw_game* game) {
    //iterate through a 2D array
    for(int r = 0; r < game->height; r++)        //row iterator
    {
        for(int c = 0; c < game->width; c++)    //column iterator
        {
            game->status[r][c] = 1;
        }
    }
}

// ***** IMPLEMENT ME! *****
// This isn’t a “public” function but is used by the initialize functions.
// If you can implement `show_all`, then `hide_all` won’t be that far behind.
// You can even write a helper function (hint hint) that would make these functions
// one-liners.
void hide_all(mcw_game* game) {
    //iterate through a 2D array
    //this is so trivial to copy helper function seems a waste haha
    for(int r = 0; r < game->height; r++)        //row iterator
    {
        for(int c = 0; c < game->width; c++)    //column iterator
        {
            game->status[r][c] = 0;
        }
    }
}

// The initialization functions have been written for you, but note they will not work
// until `alloc_game` has been implemented.
mcw_game* initialize_random_game(int width, int height, int probability) {
    mcw_game* game = alloc_game(width, height);
    if (game == NULL) {
        return NULL;
    }

    int threshold = probability > MAX_PROBABILITY ? MAX_PROBABILITY : probability;

    int x, y;
    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            int mine_roll = random() % MAX_PROBABILITY;
            game->field[y][x] = mine_roll < threshold ? weeper : open;
        }
    }
    hide_all(game);
    return game;
}

mcw_game* initialize_file_game(char* filename) {
    FILE* game_file = fopen(filename, "r");
    if (!game_file) {
        return NULL;
    }
    char buffer[BUFFER_SIZE];
    mcw_game* game = NULL;
    int y = 0;
    while (!feof(game_file)) {
        fgets(buffer, BUFFER_SIZE, game_file);
        if (game == NULL) {
            int width;
            int height;
            int successful_scans = sscanf(buffer, "%d %d", &width, &height);
            if (successful_scans < 2) {
                fclose(game_file);
                return NULL;
            } else {
                game = alloc_game(width, height);
                if (game == NULL) {
                    fclose(game_file);
                    return NULL;
                }
            }
        } else {
            
            if (y >= game->height) {
                break;
            }
            
            int x;
            for (x = 0; x < game->width; x++) {
                if (buffer[x] == OPEN_CHAR || buffer[x] == WEEPER_CHAR) {
                    game->field[y][x] = buffer[x] == OPEN_CHAR ? open : weeper;
                } else {
                    fclose(game_file);
                    return NULL;
                }
            }

            y++;
        }
    }

    fclose(game_file);
    hide_all(game);
    return game;
}

// Don’t hesitate to write helper functions for yourself when implementing the “public” functions.
// They will reduce code duplication and, with good names, they will make your code more readable.

// ***** IMPLEMENT ME! *****
void display_game_field(mcw_game* game) {

    //must display a simple 2D array but the output is modulated by status, honestly not bad
    //assume that it's all init'd by now :)


    int row_max = game->height, //number of rows
        col_max = game->width;  //number of columns
    int weep_count;

    printf("  "); //don't label the row numbers as a col
    for(int c = 0; c < col_max; c++)
    {
        printf("%2d", c);   //column labels across top
    }
    puts("");//newline

    //iterate through a 2D array
    for(int r = 0; r < row_max; r++)        //row iterator
    {
        printf("%2d", r);
        for(int c = 0; c < col_max; c++)    //column iterator
        {
            if(game->field[r][c] == 1)  //weeper
            {
                emit_utf_8(WEEPER);
            }
            else                        //open
            {   
                
                weep_count = get_adjacent_weeper_count(game, c,r);
                if(weep_count == 0)
                {
                    printf("  ");//2 spaces for formatting
                }
                else
                {
                
                    printf("%2d", weep_count);
                }
            }
            
        }
        puts("");//next line
    }

}

// ***** IMPLEMENT ME! *****
int get_weeper_count(mcw_game* game) {
    //total weeper count

    int count = 0; //running total

    //iterate through a 2D array
    for(int r = 0; r < game->height; r++)        //row iterator
    {
        for(int c = 0; c < game->width; c++)    //column iterator
        {
            if(game->field[r][c] == 1)
            {
                count++;
            }
        }
    }
}

// ***** IMPLEMENT ME! *****
int get_flag_count(mcw_game* game) {

    int count = 0; //running total

    //iterate through a 2D array
    for(int r = 0; r < game->height; r++)        //row iterator
    {
        for(int c = 0; c < game->width; c++)    //column iterator
        {
            if(game->status[r][c] == 2)
            {
                count++;
            }
        }
    }
    return count;
}

// ***** IMPLEMENT ME! *****
int get_adjacent_weeper_count(mcw_game* game, int x, int y) {
    
    if(! is_in_game_bounds(game, x, y)) return 0;

    int counter = 0; //running total of adjavent weepers (including diagonals, no?)

    //another simple 2d array iterator :) 
    for(int r = y-1; r <= y+1; r++)
    {
        if(r >= game->height || r < 0)continue;  //at edge
        else                                    //within bounds
        {
            for(int c = x-1; c <= x+1; c++)
            {
                if(c >= game->width || c < 0) continue; //at edge
                else                                    //within bounds
                {
                    if(game->field[r][c] == 1)
                    {
                        counter++;
                    }
                }
                
            }
        }
        
    }
    return counter;

}

// ***** IMPLEMENT ME! *****
void display_game_state(mcw_game* game) {

    //must display a simple 2D array but the output is modulated by status, honestly not bad
    //assume that it's all init'd by now :)


    int row_max = game->height, //number of rows
        col_max = game->width;  //number of columns
    int weep_count;

    printf("  "); //don't label the row numbers as a col
    for(int c = 0; c < col_max; c++)
    {
        printf("%2d", c);   //column labels across top
    }
    puts("");//newline

    //iterate through a 2D array
    for(int r = 0; r < row_max; r++)        //row iterator
    {
        printf("%2d", r);
        for(int c = 0; c < col_max; c++)    //column iterator
        {
            //find if hidden, revealed, flagged
            if(game->status[r][c] == 0)         //hidden
            {
                emit_utf_8(HIDDEN);
            }
            else if (game->status[r][c] == 1)   //revealed
            {
                if(game->field[r][c] == 1)  //weeper
                {
                    emit_utf_8(WEEPER);
                }
                else                        //open
                {   
                    weep_count = get_adjacent_weeper_count(game, c,r);
                    if(weep_count == 0)
                    {
                        printf("  ");//2 spaces for formatting
                    }
                    else
                    {
                    
                        printf("%2d", weep_count);
                    }
                }
            }
            else                                //flagged
            {
                
                emit_utf_8(MARKER);
            }
            
        }
        puts("");//next line
    }
}

// ***** IMPLEMENT ME! *****
bool is_in_game_bounds(mcw_game* game, int x, int y) {

    if( y < 0 || y >= game->height) return false;

    if( x < 0 || x >= game->width) return false;

    return true;
}

// ***** IMPLEMENT ME! *****
void mark_game_square(mcw_game* game, int x, int y) {
    //put a flag on that square, easy peasy

    if(!is_in_game_bounds(game, x,y)) return;
    if(game->status[y][x] == 0)
        game->status[y][x] = 2; //marked (since this is a 'safe' move, no checking. it'll work out or not for them)
    else if(game->status[y][x] == 2)
        game->status[y][x] = 0;
    //don't do anything if revealed, probably a typo
}

// recursive helper to reveal empty squares adjacent to revealed square
void reveal_game_square_helper(mcw_game* game, int x, int y) {

    if(game->status[y][x] == 1 || game->status[y][x] == 2) return; //it's been handled or is flagged
   
    game->status[y][x] = 1;
    
    //base case
    if(get_adjacent_weeper_count(game,x,y) > 0) return;

    //another zero! insane, recurse away
    else if(get_adjacent_weeper_count(game, x, y) == 0)
    {
        for(int r = y-1; r <= y+1; r++)
        {
            for(int c= x-1; c <= x+1; c++)
            {
                if(is_in_game_bounds(game, c, r)){ 
                    reveal_game_square_helper(game,c,r);
                }
            }
        }
    }
    

}

// ***** IMPLEMENT ME! *****
void reveal_game_square(mcw_game* game, int x, int y) {

    if(!is_in_game_bounds(game, x,y)) return;

    if(game->status[y][x] == 2)     //if position is flagged, return
    {
        return;//probably typo, must remove flagto reveal it
    }

    game->status[y][x] = 1;

    if(game->field[y][x] == 1)
        return; //lost the game :(  - handled in main loop by is_game_over_lost

    if(get_adjacent_weeper_count(game, x, y) == 0)
    {
        for(int r = y-1; r <= y+1; r++)
        {
            for(int c= x-1; c <= x+1; c++)
            {
                if(is_in_game_bounds(game, c, r)){ 
                    reveal_game_square_helper(game,c,r);
                }
            }
        }
    }

puts("");
    

}


// ***** IMPLEMENT ME! *****
bool is_game_over_loss(mcw_game* game) {

    for(int r = 0; r < game->height; r++)
    {
        for(int c = 0; c < game->width; c++)
        {
            if(game->status[r][c] == 1 && game->field[r][c] ==1)
            {
                //a revealed weeper means loss
                return true;
            }
        }
    }

    return false;
}

// ***** IMPLEMENT ME! *****
bool is_game_over_win(mcw_game* game) {
    //to win,
    //every single weeper must be flagged

    for(int r = 0; r < game->height; r++)
    {
        for(int c = 0; c < game->width; c++)
        {
            
            if(game->field[r][c] == 1 && game->status[r][c] !=2 ) //one weeper is not covered in flag
            {
                return false;
            }
            if(game->field[r][c] != 1 && game->status[r][c] == 2) //unnecessary flag
            {
                return false;
            }
        }
    }

    //I could also check if number of flags == number of weepers
    //but that requires /two/ iterations in addition to the above, so I think it's slightly slower
    //also if every weeper is covered by flag and every flag is covering a weeper, they must be the same
    //so, anyways, we now know that they've won :) (or have already returned false)
    
    return true;
}
