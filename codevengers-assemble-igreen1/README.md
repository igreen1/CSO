**CMSI 284** Computer System Organization/Systems Programming, Spring 2020

# Assignment 0505: Codevengers Assemble!
OK, this is it—the moment you've all been waiting for (or dreading): no-holds-barred, full-contact, in-your-face assembly language programming. You are seven programs/functions away from finishing up the semester! Suit up.

## Overview
This assignment consists of seven (7) deliverables: a sequence of five (5) programs that build on each other, an assembly language program that calls a C function whose source code you already have (as opposed to a C _library_ function), and an assembly language _function_ that is called by C code. The latter two were chosen so that you already have some familiarity with them.

Given the title of this assignment, you can think of these as analogous to movies that you see in big pop culture franchises…if you have some imagination and stare at it really hard 😂
1. [_convert-and-printf.asm_](#the-indie-movie-gone-hollywood-convert-and-printfasm) is like the little indie movie that got tweaked a little bit by Hollywood to make it more “marketable:” Modify the sample program from the “Understanding Calling Conventions” async video so that it converts a string _provided as a command line argument_ into a number.
2. [_add.asm_](#the-franchise-builder-addasm) is like that franchise-building movie which takes the basic idea of _convert-and-printf.asm_ and does something more with it: Implement an assembly language program that takes two command-line arguments, converts them internally into numbers, then prints their sum.
3. [_sub.asm_](#the-lookalike-sequel-subasm) is a lookalike sequel—almost exactly like _add.asm_ but it subtracts the numbers rather than adds them. 
4. [_addsub.asm_](#the-crossover-addsubasm) is like the ambitious “crossover” show, here smushing addition and subtraction into the same program: Implement an assembly language program that either adds or subtracts based on whether the user supplies `+` or `–` at the command line.
5. [_addsub-func.asm_](#the-reimagining-addsub-funcasm) is like one of those “reimaginings” where it’s pretty much _addsub.asm_ but addition and subtraction are implemented as _functions_ that follow the calling conventions.
6. [_code-point-to-utf8.asm_](#the-nostalgic-remake-code-point-to-utf8asm) is a “nostalgic remake” which takes a “cherished classic” (_code-point-to-utf-8.c_) and updates it to the current course content: Implement an assembly-language version of its `main` function but still call the C version of `emit_utf_8`.
7. Finally, [_is-in-game-bounds.asm_](#the-spinoff-is-in-game-boundsasm) is one of those “spinoffs”—it takes a single function from the venerable _Mine-C-Weeper_ program and has you redo it…in assembly language.

Are you hyped? Let’s get into them in detail.

## Background Reading
Most of the information you need can be found in Dr. Toal’s [NASM Tutorial page](https://cs.lmu.edu/~ray/notes/nasmtutorial/) page. Make sure to also check out the _Async Sessions_ section in Brightspace for “Using a C Library from Assembly Language,” “Understanding Calling Conventions,” and “Command Line Arguments”—they will continue to be of use for this assignment, supplementing the longer sample programs from the [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/).

## For Submission
Write the requested assembly language programs and function. The first five programs build upon each other conceptually, but they should be standalone and independently buildable. The last program and function rely on additional (and familiar) code, re-supplied with the assignment’s repository.

All of these deliverables come with starter versions. You generally have free reign to modify these versions to fit the way you prefer to think and work with _one exception_—when a definition is provided for printed messages or formats, _don’t change the text_. This will ensure that your program’s messages are standardized and fit the specifications shown here.

Except for the last two items, these programs should all be buildable with the standard `nasm` + `gcc` pattern:

    nasm -felf64 <file.asm>
    gcc -no-pie <file.o>

Specific instructions for _code-point-to-utf8.asm_ and _is-in-game-bounds.asm_ are given in their respective detail sections.

As a quick reference, the requested deliverables are:
* [_convert-and-printf.asm_](#the-indie-movie-gone-hollywood-convert-and-printfasm) (the indie movie gone Hollywood)
* [_add.asm_](#the-franchise-builder-addasm) (the franchise-builder)
* [_sub.asm_](#the-lookalike-sequel-subasm) (the lookalike sequel)
* [_addsub.asm_](#the-crossover-addsubasm) (the crossover)
* [_addsub-func.asm_](#the-reimagining-addsub-funcasm) (the reimagining)
* [_code-point-to-utf8.asm_](#the-nostalgic-remake-code-point-to-utf8asm) (the nostalgic remake)
* [_is-in-game-bounds.asm_](#the-spinoff-is-in-game-boundsasm) (the spinoff)

### The Indie Movie Gone Hollywood: _convert-and-printf.asm_
A _convert-and-printf.asm_ program was shown in the “Understanding Calling Conventions” async session (around 20 minutes in) to demonstrate how `atoi` and `printf` can be called from assembly language. Functionally, the sample program converted a hardcoded string into an integer via `atoi`, then printed that integer via `printf`. Overall, it was a nice little “indie movie.”

But we want it to go Hollywood! Who wants a program that performs an operation on a _hardcoded_ string??? Now, with our big studio budget, we can remake this program with…command line arguments! For _your_ version of _convert-and-printf.asm_, make `atoi` convert the string that is given by the user at the command line.

The given starter code provides a version of the original _convert-and-printf.asm_, with some argument count checking to set you in the right direction. Sample program invocation and output are shown below. As with earlier assignments, to make it easier to distinguish the many samples on this document, `a.out` is substituted for the name of the specific program being invoked.

    $ ./convert-and-printf
    One argument is needed for conversion to a number.
    $ ./convert-and-printf 54
    Here it is: 54
    $ ./convert-and-printf -99
    Here it is: -99
    $ ./convert-and-printf 42andchange
    Here it is: 42
    $ ./convert-and-printf not-a-number-but-atoi-is-ok-with-that
    Here it is: 0
    $ ./convert-and-printf 52 12 24 53 56
    One argument is needed for conversion to a number.

Remember to take out the `hardCodedNumber` definition when you’re done—you won’t, and _shouldn’t_, need that in the finished _convert-and-printf.asm_ program.

#### Let `atoi` Be!
One notable observation from this sample output is that we’re letting `atoi` just do its thing. For this _entire_ assignment, we’ll just work with `atoi`’s extremely…_forgiving_…approach to converting strings to numbers. This will just let us focus on the main thread of assembly language logic without getting mired in scanning the strings for legitimate characters.

### The Franchise-Builder: _add.asm_
Turn your indie hit into a franchise by using your newfound ability to convert command-line strings into numbers in assembly language to implement a simple adder. Again, we’ll leave `atoi` to its devices and happily print out the sum of whatever its converted results may be.

Once more, our sample output uses `add` instead of `a.out` to make it clearer that this is the output of a finished version of _add.asm_:

    $ ./add
    Two arguments are needed in order to perform addition.
    $ ./add 35
    Two arguments are needed in order to perform addition.
    $ ./add 23 35 1009
    Two arguments are needed in order to perform addition.
    $ ./add 23 35
    23 + 35 = 58
    $ ./add dog cat
    0 + 0 = 0
    $ ./add level42 90savages
    0 + 90 = 90
    $ ./add 83478 -23758
    83478 + -23758 = 59720
    $ ./add 17583 235998
    17583 + 235998 = 253581

### The Lookalike Sequel: _sub.asm_
Like many a lookalike sequel, _sub.asm_ should be almost entirely a copy of _add.asm_, except that it _subtracts_, rather than adds, the two given command-line arguments. It should differ from _add.asm_ in just a few key lines:

    $ ./sub
    Two arguments are needed in order to perform subtraction.
    $ ./sub 2134
    Two arguments are needed in order to perform subtraction.
    $ ./sub -213 234 5830
    Two arguments are needed in order to perform subtraction.
    $ ./sub 98 -67
    98 - -67 = 165
    $ ./sub coffee tea
    0 - 0 = 0
    $ ./sub 2fast2furious F9
    2 - 0 = 2
    $ ./sub -124 6364
    -124 - 6364 = -6488
    $ ./sub 3859 785
    3859 - 785 = 3074

### The Crossover: _addsub.asm_
Like real-world entertainment crossovers, _addsub.asm_ might perhaps be the toughest program to pull off in this entire set. But note how it directly builds upon the programs that came before it, with the new logic being centered on now expecting an _operator_ between the two numbers. `+` should add the two numbers and `-` should subtract them.

Again, note the `addsub` substitution for `a.out` and how we’re skipping strict number checks and going with whatever `atoi` returns after converting the string:

    $ ./addsub
    To use this program, either enter <number> + <number> or <number> - <number>.
    $ ./addsub 5
    To use this program, either enter <number> + <number> or <number> - <number>.
    $ ./addsub 98 3524
    To use this program, either enter <number> + <number> or <number> - <number>.
    $ ./addsub 98 3524 342
    This program only recognizes + or -.
    $ ./addsub 98 plus 342
    This program only recognizes + or -.
    $ ./addsub 98degrees + 342
    98 + 342 = 440
    $ ./addsub 98 - 342bueller
    98 - 342 = -244
    $ ./addsub banana - 26
    0 - 26 = -26
    $ ./addsub 2048 - 2006
    2048 - 2006 = 42
    $ ./addsub 2042345 + 327498
    2042345 + 327498 = 2369843
    $ ./addsub 2042345 ++++ 327498
    This program only recognizes + or -.
    $ ./addsub 2042345 -+ 327498
    This program only recognizes + or -.

### The Reimagining: _addsub-func.asm_
Like many “reimaginings,” the substance of _addsub-func.asm_ is identical to _addsub.asm_, but _how_ it does it is (slightly) different. For _addsub-func.asm_, implement `add` and `subtract` _assembly language functions_ that adhere to the calling conventions described on the [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/) page and the async video.

Thus, no need to reiterate sample output here because it should be identical to the output of _addsub.asm_. _However_, make sure that _addsub-func.asm_ has the following:
* Two functions, one called `add` and another called `subtract`, whose C-equivalent signatures would be:

        int64_t add(int64_t, int64_t);
        int64_t subtract(int64_t, int64_t);

  Yes, if you want an example, search for `int64_t` in the [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
* _Calls_ to the two functions, at wherever is appropriate in your `main` function:

        call add
        ; etc.
        call subtract

  It goes without saying that registers should be set up properly prior to the `call`s, callee-save registers must be preserved per the calling convention, and the stack must be managed properly so that it is balanced before returning from a function, including `main`.

---

***Note:*** The last two deliverables involve code that has been placed in the _mine-c-weeper-af_ folder of the repository, so make sure to work on those files in there instead of at the top level. As you can tell by the folder name, this is the Mine-C-Weeper code, but with some assembly functions inside (once the assignment is done).

---

### The Nostalgic Remake: _code-point-to-utf8.asm_
At this point in the semester, you might be longing for those bygone, simpler times when you only had to write in one language (C) and there were no such things as registers or express stack management 😬 There were still segmentation faults, but hey nostalgia tends to fade out the bad parts.

In that spirit, we offer up a “nostalgic remake” of the first program from our first C assignment—_code-point-to-utf8_, but now written in assembly language. Here’s the wrinkle: just like that first program, you don’t have to write _all_ of it—we get to keep the C code to the `emit_utf_8` function! Instead, just port the `main` function to assembly and _call_ the C-written `emit_utf_8` function.

No output for this one because it should be identical to the original. However, it will be built differently; assemble _code-point-to-utf8.asm_ first, and then use _gcc_ to put everything together:

    nasm -felf64 code-point-to-utf8.asm
    gcc -no-pie io-utilities.c code-point-to-utf8.o

As you can infer from these commands, we’re re-using our Mine-C-Weeper code base here and thus the `emit_utf_8` C function can be found in _io-utilities.c_.

Once this is done, you should have an executable whose behavior is indistinguishable from the first (it’s a remake after all!) but of course the `main` function is now in cool, slick, badass-embly language.

And note, you _still_ don’t have to fully understand what `sscanf` does—but just make sure to _call it correctly_ in assembly language. The answer yet again lies in fully understanding the calling conventions _and_, in this case, the data types being passed to `sscanf`—_particularly the last one_. The starter code plants some seeds to help you along, but overall if you understand pointers and the calling conventions and have a good understanding of the code in [NASM Tutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/), async videos, and class sessions, it shouldn’t be too hard to figure out.

### The Spinoff: _is-in-game-bounds.asm_
And now, as one entertainment franchise closes on its way to a new one, we wrap up with something that is similar to what happens with those franchises—we spin them off! Here, we “spin off” a frequently-used part of the Mine-C-Weeper code base and do something to it that aligns with something that was done early on with computer games: _write it in assembly language_.

For maximum performance and efficiency, many early computer games were written in 100% assembly language even after other types of applications had switched to other languages. This is no longer a necessity with today’s technology, but we pay homage to that tradition here by rewriting just one Mine-C-Weeper function in assembly language: `is_in_game_bounds`. This new assembly language version should be placed in a file called _is-in-game-bounds.asm_, for which a starter has been provided in the assignment repository. (note our ongoing convention of using underscores in function names but hyphens in file names)

For the rest of the code, _copy_ your Mine-C-Weeper implementation from the previous assignment into this one—that’s pretty much _mine-c-weeper.c_, but _without_ the `is_in_game_bounds` function. Your Mine-C-Weeper implementation doesn’t have to be fully fully functional, but it should at least have some working calls to `is_in_game_bounds`. If not, then feel free to write a test program that calls `is_in_game_bounds` directly.

When correctly written, the C portions of Mine-C-Weeper should successfully call `is_in_game_bounds` _with no changes to the code_. What assures the proper interoperability? Yet again, it’s those _calling conventions_, of course! The `is_in_game_bounds` declaration in _mine-c-weeper.h_ continues to tell the compiler how to use the function, but now the linker does the work of connecting those function calls to the assembly language implementation.

Thus, there is no need to repeat sample output, but you _will_ need to know how to build this new, part-assembly (bionic?) version of Mine-C-Weeper:

    nasm -felf64 is-in-game-bounds.asm
    gcc -no-pie string-plus.c io-utilities.c mine-c-weeper.c is-in-game-bounds.o <file-with-main-function.c>

Note from the _gcc_ command that the last file can be any of the test programs (copied to this repository again for convenience) or the full game itself, _mine-c-weeper-game.c_ (again copied to this repository in full for your convenience).

The third test, _03-test-is-in-game-bounds.c_ probably gets added attention here, but don’t hesitate to try the other tests as well in order to see how amazingly cool it is to be able to write parts of a program in superfast assembly language without the other parts even knowing that this is the case!

#### Notes on the Function Signature
The declaration of `is_in_game_bounds` remains unchanged from the original (after all, the “spinoff” wouldn’t be quite so slick if we had to retcon some original parts, right?):

    bool is_in_game_bounds(mcw_game* game, int x, int y);

As such, there are some slight twists to remember:
* The `int` data type on our platform consists of 32 bits only—thus, for those data types, make sure use the _32-bit synonyms_ of the registers (e.g., `esi`, `edx`, etc.)
* Pointer (`*`) data types continue to be 64 bits, so for those data types, stay with the 64-bit names (e.g., `rdi`)
* Finally, the `bool` data type is ultimately just an integer synonym, so you can use those in assembly language: `1` for `true` and `0` for `false`—if you want to see for yourself, type and run this program:

        #include <stdio.h>

        int main() {
            printf("%d\n", true);
            printf("%d\n", false);
           return 0;
        }

## Implementation/Sequencing/Difficulty Notes
* The first five programs build upon each other: if you feel like you are copying code from a previous program then changing or expanding it in order to achieve the next program, then you’re generally doing it right. The five programs were defined with that cumulative sequence in mind.
* By far, “crossing over” _add.asm_ and _sub.asm_ into _addsub.asm_ will take the most work. Plan accordingly. To compensate for this, going from _addsub.asm_ to _addsub-func.asm_ should then be relatively simple in comparison—as long as you understand how to create a function in assembly language correctly!
* _code-point-to-utf-8.asm_ can potentially be quite difficult, but as noted in the starter code, observe that its overall structure is very similar to _echo.asm_. However, instead of merely echoing each argument via `puts`, you need to adapt the `sscanf` C function call into its corresponding assembly language version, and also call `emit_utf_8` correctly from assembly language. As mentioned in the earlier instructions, you don’t have to understand `sscanf` deeply in order to do this—you just have to look at its arguments and map them to their assembly language equivalents (specifically, put them in the right registers, per the calling conventions).
* After all that, _is-in-game-bounds.asm_ should be a fairly good cooldown. It was likely the easiest Mine-C-Weeper function to write, and the hope is that it will translate to assembly fairly easily. The key here is to follow the calling convention well, because C code will be calling it and _that_ code will definitely be expecting compliance with that convention!

## How to Turn it In
Commit your source code (and _just_ the source code) to this repository, in their designated folders/directories. Note that starter files for most programs have already been supplied, so all you need to do is edit or update them.
* _convert-and-printf.asm_, _add.asm_, _sub.asm_, _addsub.asm_, and _addsub-func.asm_ go at the top of the repository
* _code-point-to-utf8.asm_ and _is-in-game-bounds.asm_ go inside the _mine-c-weeper-af_ folder (“af” for “assembly functions” of course!), because they need additional source files from within that folder.

## Specific Point Allocations
This assignment is scored according to outcomes _2a_ to _2d_, _3a_, _3b_, and _4a_ to _4f_ in the [syllabus](https://dondi.lmu.build/spring2020/cmsi284/cmsi284-spring2020-syllabus.pdf). For this particular assignment, graded categories are as follows:

| Category | Points | Outcomes |
| -------- | -----: | -------- |
| _convert-and-printf.asm_ | 10 points total | |
| • Assembles, links, and runs without unexpected errors | 2 points | _3a_, _4a_, _4d_ |
| • Correct program output | 6 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • Removal of hardcoded number | 1 point | _4b_ |
| • Correct handling of invalid user input | 1 point | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _add.asm_ | 20 points total | |
| • Assembles, links, and runs without unexpected errors | 4 points | _3a_, _4a_, _4d_ |
| • Correct program output | 12 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 4 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _sub.asm_ | 10 points total | |
| • Assembles, links, and runs without unexpected errors | 2 points | _3a_, _4a_, _4d_ |
| • Correct program output | 6 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 2 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _addsub.asm_ | 30 points total | |
| • Assembles, links, and runs without unexpected errors | 5 points | _3a_, _4a_, _4d_ |
| • Correct program output | 10 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • Direct use of `add` and `sub` assembly instructions | 10 points | _2c_, _4a_, _4d_ |
| • Correct handling of invalid user input | 5 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _addsub-func.asm_ | 10 points total | |
| • Assembles, links, and runs without unexpected errors | 2 points | _3a_, _4a_, _4d_ |
| • Correct program output | 2 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • `add` function follows calling conventions | 2 points | _3b_, _4a_, _4d_ |
| • `subtract` function follows calling conventions | 2 points | _3b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 2 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _code-point-to-utf8.asm_ | 40 points total | |
| • Compiles, assembles, links, and runs without unexpected errors | 8 points | _3a_, _4a_, _4d_ |
| • `main` in assembly, `emit_utf_8` in C | 10 points | _3b_, _4a_, _4d_ |
| • Correct program output | 14 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 8 points | _2a_–_2d_, _3b_, _4a_, _4d_ |
| _is-in-game-bounds.asm_ | 30 points total | |
| • Compiles, assembles, links, and runs without unexpected errors | 5 points | _3a_, _4a_, _4d_ |
| • Removal of `is_in_game_bounds` C version | 5 points | _4b_ |
| • Adherence to original `is_in_game_bounds` declaration | 5 points | _4b_ |
| • Correct program output | 10 points | _2b_–_2d_, _3b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 5 points | _2b_–_2d_, _3b_, _4a_, _4d_ |
| Hard-to-maintain or error-prone code | deduction only | _4b_ |
| Hard-to-read code | deduction only | _4c_ |
| Version control | deduction only | _4e_ |
| Punctuality | deduction only | _4f_ |
| **Total** | **150** |

Note that inability to compile, assemble, link, and run to begin with will negatively affect other criteria, because if we can’t build an executable, we can’t evaluate the remaining items completely.
