

## Ian Green

##### https://github.com/lmu-cmsi284-spring2020/oh-say-can-you-c-igreen1

| Category/Feedback | Points |
| --- | ---: |
| **code-point-to-utf8.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 1/1 |
| • _Correct program output?_ All tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ All tests pass. | 1/1 |
| **split-string-at-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 4/4 |
| • _Correct program output?_ All tests pass. | 12/12 |
| • _Correct handling of invalid user input?_ All tests pass. | 4/4 |
| **print-max-note-lengths.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 1/1 |
| • _Correct program output?_ Missing period in the output, but otherwise all tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ No deduction, but ideally, the program prints out some kind of message when arguments are unexpectedly supplied, to inform the user that these aren’t necessary. | 1/1 |
| **get-note-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs.  | 1/1 |
| • _Correct program output?_ Missing period in the output, but otherwise all tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ Missing period in the output, but otherwise all tests pass. | 1/1 |
| **get-chord-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs.  | 1/1 |
| • _Correct program output?_ Missing period in the output, but otherwise all tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ Missing period in the output, but otherwise all tests pass. | 1/1 |
| **split-note-and-chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 6/6 |
| • _Correct program output?_ All tests pass. | 18/18 |
| • _Correct handling of invalid user input?_ The program correctly checks arguments and return values to determine the validity of user input. | 6/6 |
| **print-chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 4/4 |
| • _Correct program output?_ It was better not to copy! `jumps` is hardcoded on the assumption that chords may have a maximum of 3 steps. This does not generalize to arbitrary arrays in _notes.h_. Following `CHORD_STEP_COUNT` and `CHORD_STEPS` without creating `jumps` at all would have led to 100% generality (–3). | 9/12 |
| • _Correct handling of invalid user input?_ Range checking is off-by-one: C-arrays are zero-based, so `NOTE_COUNT` and `CHORD_COUNT` themselves aren’t valid (–1). | 3/4 |
| **chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 2/2 |
| • _Correct program output?_ Because this is a cumulative program from all previous code, we avoid re-deductions of prior errors and will only count new ones.<br><br>Given that consideration, no new issues were found for _chord.c_. | 6/6 |
| • _Correct handling of invalid user input?_ Because this is a cumulative program from all previous code, we avoid re-deductions of prior errors and will only count new ones.<br><br>Given that consideration, no new issues were found for _chord.c_. | 2/2 |
| **Input/output in functions other than `main`** No stray prints found. |  |
| **Failure to write functions as defined** No divergences from function specifications were seen. |  |
| **Hard-to-maintain or error-prone code** For `get_note_index`, I guess you didn’t realize that `NOTE_COUNT` already has the value computed by `size_of_notes`? (analogous note in `get_chord_index`) |  |
| **Hard-to-read code** Not a big deal, but note that opening braces should go on the same line on which you begin the loop or conditional statement (the style you are using is called “Allman braces” and the style I’m suggesting is called “1TBS”—long discussion why 1TBS is preferred over Allman so for now, just passing this along).<br><br>Add spaces after reserved words like `for` and `if`, so that they don’t look like function calls.<br><br>In _print-max-note-lengths.c_, your `if` statements aren’t enclosed in braces. It’s good practice to _always_ use braces, even if a clause consists of a single statement. |  |
| **Version Control** 8 commits; good commit frequency and granularity, and commit messages are descriptive. Good work! |  |
| **Punctuality** First commit on 3/5 10:21am; last commit on 4/5 2:03pm. |  |
| **Total** | **96/100** |
