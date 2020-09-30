

## Ian Green

##### https://github.com/lmu-cmsi284-spring2020/wedd-include-c-remony-igreen1

| Category/Feedback | Points |
| --- | ---: |
| **Chord Consolidated** | |
| • _Consolidated code compiles and runs as specified?_ All files compile and run successfully.  | 6/6 |
| • _All shared/“public” functions are defined only once across all files?_ No duplicate function definitions found. | 4/4 |
| **Mine-C-Weeper** | |
| • _All programs compile and run without unexpected errors?_ All files compile and run successfully. | 10/10 |
| • _Game memory allocation is precise—no shotgun approach?_ Fails test for repeated game allocation and freeing. For the game itself, space is only allocated for a _pointer_ to an `mcw_game` rather than for an `mcw_game` struct itself. Thus, not enough space is allocated, causing all future tests to fail. (–4) In addition (less important but still noteworthy), allocation for elements of the `game->field` and `game->status` arrays is imprecise. It suffices to allocate space of size `width * sizeof(mcw_square)` and `width * sizeof(mcw_status)` in the for loops, rather than using the size of a _pointer_ to an `mcw_square` or a _pointer_ to an `mcw_status` (or a pointer to a pointer, as your implementation does). (–2) | 14/20 |
| • _Game memory is freed correctly?_ Memory is correctly freed. | 20/20 |
| • _Implemented functions produce correct results and behaviors?_ Fails on all tests due to memory allocation, but once memory allocation errors were manually resolved, fails 1 out of 10 tests (adjacent weeper count); tests for total weeper count fails on custom maps. | 34/40 |
| • _Complete game is playable?_ Game is playable. | 10/10 |
| • _Failure to write functions as defined?_ Private definitions like `EMPTY` should not be included in the `mine-c-weeper.h` header file, but rather should only be included in the specific files where they are needed. The header file should only contain "public" functions that multiple files need to use. (–0.5) | -0.5 |
| **System Call Me Maybe** | |
| The Frank (Serious) One | |
| • _Assembles, links, and runs without unexpected errors?_ Assembles, links, and appears to run successfully.<br><br>Kudos and finding and learning how to use `equ` to great effect! | 2/2 |
| • _Correct system call invocation (`syscall`)?_ System call appears to be invoked correctly. | 3/3 |
| • _Correct program output or result?_ Program appears to work as intended. | 8/8 |
| • _Correct handling of invalid user input or erroneous results?_ Error checking appears to be performed. | 2/2 |
| The Prank (Combo) One | |
| • _Well-described expected behavior?_ Description of expected behavior is provided. | 3/3 |
| • _Assembles, links, and runs without unexpected errors?_ Assembles, links, and appears to run successfully. | 2/2 |
| • _Correct _multiple_ system call invocations (`syscall`)?_ Multiple system calls appear to be invoked correctly. | 5/5 |
| • _Correct program output or result?_ Program appears to work as intended. | 10/10 |
| • _Correct handling of invalid user input or erroneous results?_ Program is hardcoded but based on the nature of the prank, this is acceptable. | 5/5 |
| _Insufficiently-commented instructions?_ Instruction-level comments are provided. |  |
| **Hard-to-maintain or error-prone code** No major error-prone or maintainability issues found. |  |
| **Hard-to-read code** No major readability issues found. |  |
| **Version Control** 9 commits; good commit frequency and granularity, and commit messages are sufficiently descriptive. Good work! |  |
| **Punctuality** First commit on 4/18 5:30pm; last commit on 4/23 6:11pm. |  |
| **Total** | **137.5/150** |
