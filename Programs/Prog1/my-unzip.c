#include <stdio.h>
#include <string.h>

//Takes perms file and file size
//This function decompresses the file and prints to stdout
void decompress(FILE *f, size_t size) 
{   
    int num, ascii;     //stores the letter count and the ascii value
    while(fread(&num, sizeof(int), 1, f) != 0)  //read int into num
    {
        fread(&ascii, sizeof(char), 1, f);      //read char into ascii
        for(int i = 0; i < num; i++)            //print ascii num amount of times
        {
            printf("%c", ascii);
        }
    }
} 

int main(int argc, char **argv)
{
    //Tests if my-unzip is passed 0 arguments
    if(argc < 2)
    {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }
    FILE *f;        //input file
    size_t size;    //file size
    for(int i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "rb");
        //If file doesn't exist then print error
        if (f == NULL)
        {
            printf("my-cat: cannot open file\n");
            return 1;
        }
        size = ftell (f);   //set file size
        decompress(f, size);
        fclose(f);
    }
    return 0;
}