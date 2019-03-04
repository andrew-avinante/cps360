#include <stdio.h>

//Takes perms file
//This function runs using the input file
void printFile(FILE *f)
{
    char buffer[1000];                      //size of line buffer
    while(fgets(buffer, 1000, f) != NULL)   //while getting input, output line to screen
    {
        printf("%s", buffer);
    }
}

int main(int argc, char **argv)
{
    //Exit with code 0 if no args are given
    if(argc < 1) return 0;
    FILE *f;
    for(int i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "r");
         //If file doesn't exist then print error
        if (f == NULL)
        {
            printf("my-cat: cannot open file\n");
            return 1;
        }
        printFile(f);
        fclose(f);
    }
    return 0;
}