**CMSI 284** Computer System Organization/Systems Programming, Spring 2020

# System Call Me Maybe
For our first cut at assembly language programs, we “borrow” (get it) some functions from our operating system: _system calls_—those built-in operating system-level services invoked by `syscall`.

## Specific Background Reading
In addition to Dr. Toal’s assembly language pages, you’ll want to scan this [list of 64-bit Linux system calls](https://filippo.io/linux-syscall-table/) (or [this one](http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)) in order to pick the one which you’ll invoke for this assignment. When you see a system call that you find interesting, just do a web search for something like “Linux 64-bit system call `system_call_name`” to find more detailed information about that system call.

Dr. Toal’s web pages have `write` and `exit`—there’s lots more you can do!

## Revvin’ your VM
As you will have noticed from the assembly language pages, we will be using a particular assembler called [_nasm_](https://www.nasm.us). Install this on your virtual machine via:

    sudo apt install nasm

Assembling files is analogous to compiling them, but with a specific argument:

    nasm -felf64 <file.asm>

When linking your assembled code into an executable, we will stay with _gcc_, except this time we will use it with the _.o_ files that the assembly process creates, plus we also add a command-line argument:

    gcc -no-pie <file.o>

As when we were starting with C, it will be a good idea to practice first with code that you know will work, from Dr. Toal’s [NASM Tutorial](http://cs.lmu.edu/~ray/notes/nasmtutorial) page.

## What to Do: A Frank One and a Prank One
Examine the aforementioned lists of 64-bit Linux system calls and pick at least two system calls that you find interesting. Implement the following assembly language programs that invoke these system calls using any applicable command-line arguments and displays appropriate message or output. This is pretty much how Linux operating system commands are implemented!

1. A “serious” assembly language program that directly performs a system call, just like an operating system command
2. A “combo” or “prank” assembly language program that uses system calls to do something unexpected (but not harmful!)

Because your combo/prank program may be doing something unexpected, _make sure to provide a clear description_ of what this program is supposed to do in your source file’s comments.

### Combo/Prank Ideas
Some possibilities for the second kind of program:
* A program that doesn’t just copy a file, but makes multiple copies with slight changes in the name
* A program that creates a new folder _and_ puts a file in it
* A program that renames a file but also makes a link to it at the old name
* A program that displays some date/time information then reboots the computer
* A program that copies a file but actually puts the copy in a chain of nested folders

In a sense, the first program is a warmup, and the second one lets you build on what you learned doing the first one.

### Implementation Notes/Tips
* Nearly all system calls require some set of parameters so you will want to link with `gcc` in order to have easy access to `argc` and `argv` as usual, as well as library functions like `atoi`, `puts`, and `printf`. Be cognizant of the system call parameters’ data types (`int`, `char*`, etc.).
* Keep things simple. Some system calls return complex structures—great information and definitely interesting, but likely over your head.
* Choose system calls whose results are easily demonstrable, such as easily verifiable information or concrete, tangible results (like those mentioned in the next item).
* System calls that manipulate files (such as `rename`, `mkdir`, `chmod`, or `unlink`) don’t necessarily have direct output but instead affect the specified file or folder. You can examine the affected file(s) or folder(s) to see if your system call worked.
* Operating system commands tend to be “no news is good news” programs—if everything goes well, they end silently (with the expectation that the user can tell if they worked, such as for file operations named above). You can follow this pattern also, but do display a message if an error is detected or if arguments are not as expected.
* Remember that you are supposed to invoke the system call _directly_, not through C. If your code doesn’t have the `syscall` instruction, then you’re doing it wrong.
* One system call is off-the-table: `chdir`. Calling this in a separate program won’t work as you expect. You’ll see why when you learn about process management in Operating Systems. `write` and `exit` are also off the table for (I hope) obvious reasons. However, you may use these system calls in supporting roles.
* Yes there is a `reboot` system call. It does what it says, so save your work if you want to try invoking it.
* If you decide to use a system call that delivers its results to a block of memory that you supply, it will be easier to just use `resb` in the `.data` section to pre-allocate space rather than to dynamically allocate memory via `malloc`.

## Specific Point Allocations
This portion of the assignment is scored according to outcomes _2c_, _2d_, _3a_, _3b_, _3c_, _4a_, _4c_, and _4d_ in the [syllabus](https://dondi.lmu.build/spring2020/cmsi284/cmsi284-spring2020-syllabus.pdf). For this particular assignment, graded categories are as follows:

| Category | Points | Outcomes |
| -------- | -----: | -------- |
| The Frank (Serious) One | 15 points total | |
| • Assembles, links, and runs without unexpected errors | 2 | _3a_, _4a_, _4d_ |
| • Correct system call invocation (`syscall`) | 3 | _3c_, _4a_, _4d_ |
| • Correct program output or result | 8 | _2c_, _2d_, _3b_, _3c_, _4a_, _4d_ |
| • Correct handling of invalid user input or erroneous results | 2 | _2c_, _2d_, _3b_, _3c_, _4a_, _4d_ |
| The Prank (Combo) One | 25 points total | |
| • Well-described expected behavior | 3 | _3a_, _4a_, _4d_ |
| • Assembles, links, and runs without unexpected errors | 2 | _3a_, _4a_, _4d_ |
| • Correct _multiple_ system call invocations (`syscall`) | 5 | _3c_, _4a_, _4d_ |
| • Correct program output or result | 10 | _2c_, _2d_, _3b_, _3c_, _4a_, _4d_ |
| • Correct handling of invalid user input or erroneous results | 5 | _2c_, _2d_, _3b_, _3c_, _4a_, _4d_ |
| Insufficiently-commented instructions | deduction only | _4c_ |
| **Total** | **40** |

Note that inability to assemble, link, and run to begin with will negatively affect the correctness of program output and proper handling of invalid user input.
