#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function for saving buffer to file.
 *
 * \param[in] 	filename name for new file
 * \param[in] 	buffer buffer data
 * \param[in] 	bufferSize buffer size
 */
void saveBufferToFile(char *filename, char *buffer, long int *bufferSize)
{
    FILE *outputFile;
    if ((outputFile = fopen(filename, "w")) != NULL)
    {
        printf("Saving to file: %s\n", filename);
        fwrite(buffer, 1, *bufferSize, outputFile);
        fclose(outputFile);
    }
}

/**
 * Function for text string concatenation.
 *
 * \param[out] 	output pointer for result
 * \param[in] 	str1 first text string
 * \param[in] 	str2 second text string
 */
char *concatenateString(char *output, char *str1, char *str2)
{
    output = (char *)malloc(1 + strlen(str1) + strlen(str2));
    strcpy(output, str1);
    strcat(output, str2);

    return output;
}
