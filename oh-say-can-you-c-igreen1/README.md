**CMSI 284** Computer System Organization/Systems Programming, Spring 2020

# Assignment 0319
Time to try your hand at some rudimentary C programming. This set provides a look at how UTF-8 encoding works in practice and also has a touch of music theory to keep things from being too “computer-y.”

## Background Reading
Pretty much all of the information you need can be found in Dr. Toal’s [Introduction to C](http://cs.lmu.edu/~ray/notes/c) page, as well as many other C programming sites on the web.

## C Programming Environment Setup
Make sure to refer to [c-setup.md](./c-setup.md) for guidelines on how to set yourself up for C programming.

## C-Game Warmup
Once you’re all set up with your Ubuntu machine (or other C programming environment), read through Dr. Toal’s [Introduction to C](http://cs.lmu.edu/~ray/notes/c), typing and running the sample programs provided there. Experiment with them by making some changes to see what happens. Bring any questions or points of confusion back to class ASAP.

## For Submission: Oh Say Can You C
Write the requested C programs. Note that most of these programs are specified such that:
* You are asked to write a _C function_ that performs a particular task, then
* Write a `main` function that calls this function and displays its results.
_Follow such specifications exactly._ It models a best practice when writing more complex software, and for some of the requested programs, you might find that a function you wrote earlier may be useful in others… (nudge nudge hint hint)
    * The `main` function checks the validity of user input, displaying the specified error message and exiting as appropriate
    * The `main` function then calls the requested function with all user input _already converted and validated_ as appropriate
    * So in summary: `main` checks for user input correctness, and the requested function performs the actual calculation/computation

In many cases, one or more starter files have been provided. Some sections of these files are meant to be edited, while others are given for you to use without modification. Take note of the instructions and comments so that you know which is which.

As a quick reference, the requested programs are:
* [_code-point-to-utf8.c_](#code-point-to-utf8c)
* [_split-string-at-index.c_](#split-string-at-indexc)
* [_print-max-note-lengths.c_](#print-max-note-lengthsc)
* [_get-note-index.c_](#get-note-indexc)
* [_get-chord-index.c_](#get-chord-indexc)
* [_split-note-and-chord.c_](#split-note-and-chordc)
* [_print-chord.c_](#print-chordc)
* [_chord.c_](#chordc)

### _code-point-to-utf8.c_
A complete, working program called _code-point-to-utf8.c_ is part of this repository. That program adapts the pseudocode `to_utf_8` function seen in Dr. Toal’s [Character Encoding](https://cs.lmu.edu/~ray/notes/charenc/) page into an actual function called `emit_utf_8`. The given version of _code-point-to-utf8.c_ takes one code point as a command line argument (in the standard `U+(code point in hex)` notation) and sends its UTF-8 encoded version to standard output.

With most modern terminal applications (definitely Ubuntu’s), emitting UTF-8 directly to standard output should display the corresponding glyphs precisely as you would expect, including emoji. Pretty fun if you consider that these terminals otherwise look quite technical and dry. 🤓😎🕺🏽💃🏼

**Your task:** Extend this program so that it can take _more than one_ `U+(code point in hex)` character from the command line and sends all of them, in sequence, to standard output. Make sure to retain the error messages that it displays when the code point is too large or if the command line argument is incorrectly formatted, _but revise the argument-count error message to show that more than one argument can be accepted_ (see sample output below).

Also, in order to see glyphs for graphemes (in terminals that support them), make sure to emit the encoded characters _without spaces_ in between (because the space counts as a character too! `U+0020` as a matter of fact).

Sample program invocation and output (the exact glyphs that appear may vary depending on the way that your terminal renders UTF-8):

    $ ./code-point-to-utf8 U+0048 U+0045 U+004C U+004C U+004F
    HELLO

    $ ./code-point-to-utf8 U+26F2 U+26F3 U+1F574 weh U+2203 U+2234 U+FFFFFF
    ⛲⛳🕴(weh incorrect format)∃∴(00FFFFFF code point is too large)

    $ ./code-point-to-utf8
    This program requires one or more command line arguments,
    one for each code point to encode as UTF-8.

    $ ./code-point-to-utf8 U+1F469 U+1F3FD U+200D U+2695 U+FE0F
    👩🏽‍⚕️

    $ ./code-point-to-utf8 U+1F1E8 U+1F1FB
    🇨🇻


### _split-string-at-index.c_
Implement the following function:
```c
void split_string_at_index(char* string, int index, char* left, char* right)
```

This function takes the given `string` then copies the substring from `0` to `index - 1` (or `0`, whichever is larger) to `left` and the substring from `index` to the end of `string` to `right`. It is the responsibility of the caller to ensure that `left` and `right` have enough space to safely copy the substrings to them.

_split-string-at-index.c_ should then demonstrate this functionality by accepting a string and an index as command line arguments, calling `split_string_at_index` accordingly, and displaying the results.

To simplify implementation, the `main` function for _split-string-at-index.c_ has been done for you. The implementation also includes a handy `is_non_negative_numeral` function that will check whether a string expresses a numeric value ≥ 0.

As written, the `main` function only has room for substrings of length 15, and checks to make sure that the arguments comply with this limit.

Sample program invocation and output:

    $ ./split-string-at-index
    This program requires exactly two command line arguments:
    The string to split and the index at which to split it.

    $ ./split-string-at-index splitme 5
    [split] [me]

    $ ./split-string-at-index splitme banana
    banana is not a valid index.

    $ ./split-string-at-index splitme -1
    -1 is not a valid index.

    $ ./split-string-at-index splitme 0
    [] [splitme]

    $ ./split-string-at-index splitme 7
    [splitme] []

    $ ./split-string-at-index splitme 8
    The index 8 out of range.

    $ ./split-string-at-index "> 15 characters on the right" 4
    Splitting at 4 will exceed the limit of 15 characters per substring.

<hr>

**Note:** The remaining programs all make use of the _notes.h_ file that is provided with this repository. The starter files for this programs already have `#include "notes.h"` in them—don’t take that out! (and don’t modify _notes.h_ either)

### _print-max-note-lengths.c_

Implement the following functions:
```c
int get_max_note_length()
```
```c
int get_max_chord_suffix_length()
```

These functions should return the length of the longest string in the `NOTES` and `CHORD_SUFFIXES` string arrays respectively. Both arrays are defined in _notes.h_. Both arrays are short so the correct answer should be pretty obvious via eyeballing, but still make sure that these functions determine the length of the longest string without making any assumptions, looking at `NOTES` and `CHORD_SUFFIXES` every time (again respectively).

Place these functions in _print-max-note-lengths.c_ and implement a `main` function that calls them then displays the results. The sample program invocation and output below intentionally contains incorrect answers to emphasize that the functions should genuinely depend on whatever is in the `NOTES` and `CHORD_SUFFIXES` arrays:

    $ ./print-max-note-lengths
    The longest NOTES string is 312325 characters long and the longest CHORD_SUFFIXES string is 7281031 characters long.

Again, _those numbers are intentionally different from what you would get from notes.h_. They are just given to show you what message should be displayed by the program when it is executed.

### _get-note-index.c_

Implement the following function:
```c
int get_note_index(char* string)
```

Given a C string, this function should return the zero-based index of the `NOTES` array in which that string appears. It should return `-1` if said string is _not_ in that array.

Place this function in _get-note-index.c_ and implement a `main` function that takes a single argument for the note string to find. The function should display the messages shown below based on the arguments that are given to it:

    $ ./get-note-index
    This program requires exactly one command line argument.

    $ ./get-note-index C A Db dead beef
    This program requires exactly one command line argument.

    $ ./get-note-index fresh
    fresh is not a valid note.

    $ ./get-note-index F#
    F# is not a valid note.

    $ ./get-note-index C
    C is at NOTES index 3.

    $ ./get-note-index A
    A is at NOTES index 0.

    $ ./get-note-index Ab
    Ab is at NOTES index 11.

This sample output shows the correct answers based on what is given in _notes.h_. For simplicity, all notes are flats, represented by a lowercase `b` (using the real ♭ character will be a little tricky on the command line, for reasons that I hope are pretty clear to everyone at this point). We’re not counting sharps for this assignment, sorry musicians.

### _get-chord-index.c_

Implement the following function:
```c
int get_chord_index(char* string)
```

Given a C string, this function should return the zero-based index of the `CHORD_SUFFIXES` array in which that string appears. It should return `-1` if said string is _not_ in that array.

Place this function in _get-chord-index.c_ and implement a `main` function that takes a single argument for the chord suffix string to find. The function should display the messages shown below based on the arguments that are given to it:

    $ ./get-chord-index
    This program requires exactly one command line argument.

    $ ./get-chord-index m7 M7 cow dim7
    This program requires exactly one command line argument.

    $ ./get-chord-index woot
    woot is not a valid chord.

    $ ./get-chord-index M
    M is not a valid chord.

    $ ./get-chord-index M7
    M7 is at CHORD_SUFFIXES index 3.

    $ ./get-chord-index ""
     is at CHORD_SUFFIXES index 0.

    $ ./get-chord-index dim7
    dim7 is at CHORD_SUFFIXES index 5.

This sample output shows the correct answers based on what is given in _notes.h_.

### _split-note-and-chord.c_

Implement the following function:
```c
int split_note_and_chord(char* string, char* note, char* chord)
```

A little background here first: chords are expressed as a concatenation, without spaces, of a letter note followed by a chord suffix (which may be empty). So `A` represents an A major chord, `Cm` is C minor, `Gb7` is the G♭ dominant 7th chord, etc. You don’t need to know all of these chords—you just need to know that the first part represents a note and the second part represents a suffix, both of which are completely defined in our code in the `NOTES` and `CHORD_SUFFIXES` arrays.

The `split_note_and_chord` function should take the string given as its first argument, identify where the note ends and the chord suffix starts, then copy just the note part into the `note` argument and the chord suffix part into the `chord` argument, returning `0` to indicate a successful split. If the `string` argument does not express a valid chord (e.g., `X7` or `Gblarg`), it should put empty strings in `note` and `chord` then return `-1` as its result.

Place this function in _split-note-and-chord.c_ and implement a `main` function that takes a single argument for the chord string to split up. The function should display the messages shown below based on the arguments that are given to it:

Sample program invocation and output:

    $ ./split-note-and-chord
    This program requires exactly one command line argument.

    $ ./split-note-and-chord Dm Am Gm A7
    This program requires exactly one command line argument.

    $ ./split-note-and-chord Dm
    [D] [m]

    $ ./split-note-and-chord Bbdim7
    [Bb] [dim7]

    $ ./split-note-and-chord G
    [G] []

    $ ./split-note-and-chord X2
    X2 is not a valid chord.

    $ ./split-note-and-chord C99
    C99 is not a valid chord.

    $ ./split-note-and-chord bungie
    bungie is not a valid chord.

This sample output shows the correct answers based on what is given in _notes.h_.

If you’re thinking that this function seems to be very similar to `split_string_at_index` but just needs to know where to split the string based on where the possible note might end, then you would be right. In fact, if we knew at what index the note ends and the chord begins, then we can just call `split_string_at_index` to perform the actual splitting… 🤔

### _print-chord.c_

Implement the following function:
```c
void print_chord(int note_index, int chord_index)
```
This one requires one last music mini-tutorial. Chords are sets of notes that are sounded at the same time, and they are  formed using well-known “formulas” for which notes to use depending on the desired chord. Given a base note, say D♭, different types of chords can be created by counting note steps from that note to the next, then the next, then the next. Thus, the major chord for D♭, simply written “D♭,” consists of D♭, then the note four steps above it (in this case F), then finally the note three steps above _that_ (which is A♭). Thus the major chord D♭ consists of the notes D♭, F, and A♭.

All other chords can be formed in the same way, with just different note counts. A minor 7th chord (suffix `m7`) consists of _four_ notes, with counts of 3, 4, then 3 notes from the starting one. Thus, Gm7 consists of G, B♭, D, and F.

Here’s the good news—you don’t have to memorize these counts for this assignment. You just need to know how to _follow_ the counts. The counts are all given, in _notes.h_, in the `CHORD_STEPS` array. There is one subarray of counts for each known chord type in _notes.h_ (go ahead and look at _notes.h_ right now if you wish). To determine the notes for a chord, start with the base note in the `NOTES` array then count along that array according to the number of steps in the `CHORD_STEPS` array.

When following chord counts for higher notes, you’ll have to _wrap around_ the `NOTES` array in order to keep going. For example, when forming the G7 chord, you will start at G then going up 4 steps you would traverse A♭, a wraparound to A, then B♭, then B. Thus the second note of G7 is B. Then you would count 3 steps to D, then 3 more steps to F, yielding the full chord of G7 as G, B, D, and F.

Given all of that, the `print_chord` function is supposed to do the following:
1. Accept two command line arguments, one for an index in the `NOTES` array and another for an index in the `CHORD_STEPS` array.
2. Given those indices, print (a) the chord that they represent then (b) the notes in that chord.

This sample output shows the correct answers based on what is given in _notes.h_:

    $ ./print-chord
    This program requires exactly two command line arguments:
    The NOTES index and the CHORD_SUFFIXES index of the note and chord suffix to print, respectively.

    $ ./print-chord 5 3
    DM7: D Gb A Db

    $ ./print-chord D M7
    Either D or M7 is not a valid index.

    $ ./print-chord 2 M7
    Either 2 or M7 is not a valid index.

    $ ./print-chord Eb 10
    Either Eb or 10 is not a valid index.

    $ ./print-chord 5 34
    Either 5 or 34 is out of range.

    $ ./print-chord 30 04
    Either 30 or 4 is out of range.

    $ ./print-chord 5 04
    Dm7: D F A C

    $ ./print-chord 03 4
    Cm7: C Eb G Bb

### _chord.c_
**Hint:** _Work on this one last!_

Write a C program, _chord.c_, that takes a command line argument which represents a chord that is listed in _notes.h_ and prints the notes of that chord. The printed output should be identical to the output of _print-chord.c_.

Sample program invocation and output:

    $ ./chord
    This program requires exactly one command line argument.

    $ ./chord Gb
    Gb: Gb Bb Db

    $ ./chord Em7
    Em7: E G B D

    $ ./chord AM7
    AM7: A Db E Ab

    $ ./chord Bdim7
    Bdim7: B D F Ab

    $ ./chord Caug
    Caug is not a valid chord.

    $ ./chord banana
    banana is not a valid chord.

Observe that “valid” in this case means that the given argument does not match any chord defined in _notes.h_. There are many other real chords out there, but for the purposes of _chord.c_, if that chord is not listed in _notes.h_, then it isn’t “valid.” For example, there _is_ such a chord as Caug, but _notes.h_ doesn’t list that so _chord.c_ will consider it to be invalid.

## General Guidelines
* You’ll notice that most of the programs are of the form “write this function, then write a program that uses this function.” _Follow this instruction strictly._ Do _not_ just write a `main` function and perform all of the logic there. As you keep working on the assignment, especially the later programs, I hope you’ll see why this directive was given.
* Do _not_ perform any input/output in the functions that you write. The functions should get their input _exclusively_ via the arguments with which they are called, and they convey their results _exclusively_ via their return value or by data sent through specific arguments (e.g., `left`, `right`, `note`, and `chord` in some of the above functions). Again, the reason for this should emerge as you work on the assignment.
* As with previous assignments, the grading of this assignment will be semi-automated, so it is very important that you adhere strictly to the specified output messages and format.

## How to Turn it In
Commit your source code (and _just_ the source code) to this repository. Note that starter files for each program have already been supplied, so all you need to do is edit them.

## Specific Point Allocations
This assignment is scored according to outcomes _2a_, _2b_, and _4a_ to _4f_ in the [syllabus](https://dondi.lmu.build/spring2020/cmsi284/cmsi284-spring2020-syllabus.pdf). For this particular assignment, graded categories are as follows:

| Category | Points | Outcomes |
| -------- | -----: | -------- |
| _code-point-to-utf8.c_ | 5 points total | |
| • Compiles and runs without unexpected errors | 1 point | _4a_, _4d_ |
| • Correct program output | 3 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 1 point | _2a_, _2b_, _4a_, _4d_ |
| _split-string-at-index.c_ | 20 points total | |
| • Compiles and runs without unexpected errors | 4 points | _4a_, _4d_ |
| • Correct program output | 12 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 4 points | _2a_, _2b_, _4a_, _4d_ |
| _print-max-note-lengths.c_ | 5 points total | |
| • Compiles and runs without unexpected errors | 1 point | _4a_, _4d_ |
| • Correct program output | 3 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 1 point | _2a_, _2b_, _4a_, _4d_ |
| _get-note-index.c_ | 5 points total | |
| • Compiles and runs without unexpected errors | 1 point | _4a_, _4d_ |
| • Correct program output | 3 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 1 point | _2a_, _2b_, _4a_, _4d_ |
| _get-chord-index.c_ | 5 points total | |
| • Compiles and runs without unexpected errors | 1 point | _4a_, _4d_ |
| • Correct program output | 3 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 1 point | _2a_, _2b_, _4a_, _4d_ |
| _split-note-and-chord.c_ | 30 points total | |
| • Compiles and runs without unexpected errors | 6 points | _4a_, _4d_ |
| • Correct program output | 18 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 6 points | _2a_, _2b_, _4a_, _4d_ |
| _print-chord.c_ | 20 points total | |
| • Compiles and runs without unexpected errors | 4 points | _4a_, _4d_ |
| • Correct program output | 12 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 4 points | _2a_, _2b_, _4a_, _4d_ |
| _chord.c_ | 10 points total | |
| • Compiles and runs without unexpected errors | 2 points | _4a_, _4d_ |
| • Correct program output | 6 points | _2a_, _2b_, _4a_, _4d_ |
| • Correct handling of invalid user input | 2 points | _2a_, _2b_, _4a_, _4d_ |
| Input/output in functions other than `main` | deduction only | _4b_ |
| Failure to write functions as defined | deduction only | _4b_ |
| Hard-to-maintain or error-prone code | deduction only | _4b_ |
| Hard-to-read code | deduction only | _4c_ |
| Version control | deduction only | _4e_ |
| Punctuality | deduction only | _4f_ |
| **Total** | **100** |

Note that inability to compile and run to begin with will negatively affect the correctness of program output and proper handling of invalid user input.

You may also be wondering why _chord.c_, the last program to write, appears to have a lower point value than you might expect. There is method to this apparent madness—as you work on the assignment, the hope is that you will realize why.
