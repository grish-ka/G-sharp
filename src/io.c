#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char* get_file_contents(const char* filepath)
{
    char* buffer = 0;
    long length;

    FILE* f = fopen(filepath, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = calloc(length, length);

        if (buffer)
            fread(buffer, 1, length, f);

        fclose(f);
        return buffer;
    }

    printf("Error reading file %s\n", filepath);
    exit(2);
}

char* addfilecontent(const char* filepath, const char* addcontent)
{
    FILE *ft;
    char ch;
    ft=fopen(filepath,"r+");
    if(ft==NULL)
    {
        printf("can not open target file\n");
        exit(1);
    }

    const char* fullcontent = strcat(addcontent, addcontent);

    fprintf(ft, fullcontent);
    

    fflush(ft);
    fclose(ft);
}