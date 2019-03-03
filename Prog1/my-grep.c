#include <stdio.h>
#include <string.h>

//Takes perms file, string to find, and file size
//This function runs using the input file
void printFile(FILE *f, char *s, size_t size)
{
    char *buffer;                               //buffer for `getline`
    while(getline(&buffer, &size, f) != -1)     //loop until end of file
    {
        if(strstr(buffer, s) != NULL)
        {
            printf("%s", buffer);
        }  
    }
}

//Takes perms string to find
//This function runs if the user fails to input a file to read
//This function reads from stdio
void printLine(char *s)
{
    char buffer[10000];
    size_t size = 10000;
    while(fgets(buffer, size, stdin))
    {
        if(strstr(buffer, s) != NULL)
        {
            printf("%s", buffer);
        }  
    }
}

int main(int argc, char **argv)
{
    //Tests if grep is passed 0 arguments
    if(argc < 2)
    {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }
    FILE *f;        //input file
    size_t size;    //file size

    //Tests if file is passed a file to read
    if(argc > 2)
    {
        //Loops over files
        for(int i = 2; i < argc; i++)
        {
            f = fopen(argv[i], "r");
            //If file doesn't exist then print error
            if (f == NULL)
            {
                printf("my-grep: cannot open file\n");
                return 1;
            }
            size = ftell(f);      //set file size
            printFile(f, argv[1], size);
            fclose(f);
        }
    }
    else
    {
        printLine(argv[1]);
    }
    return 0;
}