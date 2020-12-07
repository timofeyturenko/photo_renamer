#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "exif.h"



using namespace std;

int rename_jpg(char *name)
{
    printf("File: %s\n", name);


    FILE *fp = fopen(name, "rb");
    if (!fp)
    {
        printf("Can't open file.\n");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize)
    {
        printf("Can't read file.\n");
        delete[] buf;
        return -2;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code)
    {
        printf("Error parsing EXIF: code %d\n", code);
        return -3;
    }


    if (result.DateTimeOriginal.c_str() != NULL)
    {
        printf("Original date/time: %s\n", result.DateTimeOriginal.c_str());
        //printf("Digitize date/time: %s\n", result.DateTimeDigitized.c_str());

        int hh, mm, ss;
        int yy, MM, dd;

        sscanf(result.DateTimeOriginal.c_str(), "%d:%d:%d %d:%d:%d",
               &yy, &MM, &dd, &hh, &mm, &ss);
        char new_name[1024];
        sprintf(new_name, "%04d_%02d_%02d__%02d_%02d_%02d-%s", yy, MM, dd, hh, mm, ss,
                name);

        printf("Renaming %s --> %s\n",
               name, new_name);
        rename(name, new_name);
        int i = strlen(name);
        name[i - 3] = 'N';
        name[i - 2] = 'E';
        name[i - 1] = 'F';
        i = strlen(new_name);
        new_name[i - 3] = 'N';
        new_name[i - 2] = 'E';
        new_name[i - 1] = 'F';
        printf("Renaming %s --> %s\n",
               name, new_name);
        rename(name, new_name);


    }
    else
    {
        printf("DataTimeOriginal is not found in EXIF info, file %s is not renamed\n", name);
    }
    return 0;
}

int main()
{
    DIR * dirp = opendir(".");
    struct dirent * dp;
    char * ext;

    while ((dp = readdir(dirp)) != NULL)
    {
        //printf("%s\n", dp->d_name);
        ext = strrchr(dp->d_name, '.');
        if (ext != NULL)
        {
            if (strcasecmp(ext, ".jpg") == 0)
            {
                rename_jpg(dp->d_name);
            }
        }
    }
    (void)closedir(dirp);
    return 0;
}
