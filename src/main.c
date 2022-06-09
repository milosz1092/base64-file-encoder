#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "encode.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Bad arguments!\n");
        return 1;
    }

    /**
     * Opening file, getting size and validating.
     */

    FILE *fp;

    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Error: Can't open file!\n");
        return 1;
    }

    printf("Opening file: %s.\n", argv[1]);

    fseek(fp, 0, SEEK_END);
    long int inputFileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (inputFileSize == 0)
    {
        fprintf(stderr, "Error: File is empty!\n");
        return 1;
    }

    unsigned char *inputBuffer = NULL; /* Buffer pointer for input data. */

    /**
     * Saving file data to memory.
     */

    inputBuffer = (unsigned char *)malloc((inputFileSize) * sizeof(unsigned char));

    printf("Saving to memory: %ldB.\n", inputFileSize);
    fread(inputBuffer, inputFileSize, 1, fp);
    fclose(fp);

    printf("Encoding data.\n");
    EncodeResult result = encode(inputBuffer, &inputFileSize);

    char *outputFilename = concatenateString(outputFilename, argv[1], (char *)".b64");

    /**
     * Saving encoded string to file and clearing the memory.
     */
    saveBufferToFile(outputFilename, result.outputBase64Buffer, &result.outputBase64BufferSize);

    free(inputBuffer);
    free(outputFilename);
    free(result.outputBase64Buffer);

    return 0;
}
