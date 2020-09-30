#include <stdio.h>
#include <inttypes.h>

int64_t add(int64_t, int64_t);
int64_t subtract(int64_t, int64_t);

int main(int argc, char** argv) {
    char* addformat = "%d + %d = %d\n";
    char* subtractformat = "%d - %d = %d\n";

    printf(addformat, 24, 98, add(24, 98));
    printf(addformat, -38, 154, add(-38, 154));
    printf(addformat, -980, -2657, add(-980, -2657));

    printf(subtractformat, 389, 1238, subtract(389, 1238));
    printf(subtractformat, 48, -157, subtract(48, -157));
    printf(subtractformat, -374, -47222, subtract(-374, -47222));
}
