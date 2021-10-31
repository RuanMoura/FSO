#include <stdio.h>
#include <stdlib.h>

int compare(FILE *, FILE *);

int main(int argc, char **argv)
{
    int i, j;

    FILE **files;
    files = malloc((argc - 1) * sizeof(FILE *));

    // open files
    for (i = 1; i < argc; i++)
    {
        files[i - 1] = fopen(argv[i], "r");
    }

    // compare files
    for (i = 1; i < argc; i++)
    {
        for (j = i + 1; j < argc; j++)
        {
            if (compare(files[i - 1], files[j - 1]))
                printf("%s %s iguais\n", argv[i], argv[j]);
            else
                printf("%s %s diferentes\n", argv[i], argv[j]);
        }
    }

    // close files pointer
    for (i = 1; i < argc; i++)
    {
        fclose(files[i - 1]);
    }

    return 0;
}

int compare(FILE *file1, FILE *file2)
{
    // same size ?
    fseek(file1, 0, SEEK_END);
    fseek(file2, 0, SEEK_END);
    if (ftell(file1) != ftell(file2))
        return 0;

    // compare byte to byte
    char byte1 = 'a', byte2 = 'a';
    fseek(file1, 0, SEEK_SET);
    fseek(file2, 0, SEEK_SET);

    while (fread((void *)&byte1, 1, 1, file1))
    {
        fread((void *)&byte2, 1, 1, file2);
        if (byte1 != byte2)
            return 0;
    }
    return 1;
}