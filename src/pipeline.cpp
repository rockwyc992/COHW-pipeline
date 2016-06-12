#include <stdio.h>
#include <string.h>

#include "global.h"

int main(int argc, char **argv)
{
    if (argc == 3) {
        input = fopen(argv[1], "r");
        output = fopen(argv[2], "w+");

        if(init()) {
            puts("Pipeline by rockwyc992");
            puts("Usage: pipeline [Input] [Output]");
        }
        while(true) {
            if(!tick()) {
                break;
            }
            show_all();
        }
        show_all();
        fputs("\n", output);
        fclose(input);
        fclose(output);
    } else {
        puts("Pipeline by rockwyc992");
        puts("Usage: pipeline [Input] [Output]");
    }

    return 0;
}

