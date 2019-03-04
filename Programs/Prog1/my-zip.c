#include <stdio.h>
#include <string.h>

//Takes perms file and file size
//This function compresses the fils using RLE
void compress(FILE *f, size_t size) 
{   
    char *buffer;           //Buffer string
    int charCount = 1;      //number of same consecutive chars
    int charBin;            //Converts char to ASCII
    while(getline(&buffer, &size, f) != -1)     
    {
        size_t strLen = strlen(buffer);     //Gets length of string and stores it in strLen 
        for (int i = 0; i < strLen; i++)    //Loops over each line from buffer
        { 
            if(buffer[i] == buffer[i+1])    //If the next letter in buffer is the same letter in current buffer index
            {                               //Then increment the charCount
                charCount++;
            }
            else                            //Else, write the count and char to file
            {
                charBin = buffer[i];
                fwrite(&charCount, sizeof(int), 1, stdout);
                fwrite(&charBin, sizeof(char), 1, stdout);
                charCount = 1;              //Reset counter
            }
        } 
    }
} 

int main(int argc, char **argv)
{
     //Tests if my-zip is passed 0 arguments
    if(argc < 2)
    {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }
    FILE *f;        //input file
    size_t size;    //file size
    for(int i = 1; i < argc; i++)
    {
        f = fopen(argv[i], "r");
        //If file doesn't exist then print error
        if (f == NULL)
        {
            printf("my-cat: cannot open file\n");
            return 1;
        }
        size = ftell (f);   //set file size
        compress(f, size);
        fclose(f);
    }
    return 0;
}