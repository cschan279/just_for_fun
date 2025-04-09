#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <ctype.h>


#define SLEEP_DELAY 20000

void printrloop(const char* leading, int ascii) {
    for (int i = 0; i < 255; i++) {
        if (!isprint(i)) 
            continue;
        printf("%s%c\r", leading, (char)i);
        fflush(stdout);
        usleep(SLEEP_DELAY);
        
        if (i == ascii)
            break;
    }
}

void printsloop(const char* s) {
    int len = strlen(s);
    char leading[len];
    
    for (int i = 0; i < len; i++) {
        strncpy(leading, s, i);
        leading[i] = '\0';
        printrloop(leading, (int)s[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printsloop(argv[argc - 1]);
    return 0;
}
