#include <stdio.h>
#include <stdlib.h>
#include "Result.h"

static char BASE64_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned char NEW_LINE_POSITION = 77;

/**
 * Function sets new line character when position is proper.
 * (after 76 characters of Base64 string)
 */
void addNewLineChar(char *buffer, long int *pointer)
{
    if (((*pointer + 1) % NEW_LINE_POSITION) == 0)
    {
        buffer[*pointer] = 10;
        *pointer = *pointer + 1;
    }
}

/**
 * Function for encoding char buffer to Base64 string format.
 *
 * \param[in] 	inputBuffer input data
 * \param[in] 	inputBufferSize input size
 */
EncodeResult encode(unsigned char *inputBuffer, long int *inputBufferSize)
{
    char *outputBase64Buffer = NULL; /* Pointer for new Base64 string buffer. */

    /**
     * Specifying the size for new Base64 characters buffer.
     */

    long int countedBytes = (*inputBufferSize / 3) * 3;
    long int outputBase64BufferSize = countedBytes + (countedBytes / 3);

    /**
     * Specifying Base64 padding size if needed.
     */

    int paddingSize = 0;
    if (countedBytes != *inputBufferSize)
    {
        int diff = *inputBufferSize - countedBytes;

        paddingSize = 3 - diff;
        printf("Bytes indivisible by 3.\n");
        printf("Padding: %i.\n\n", paddingSize);

        outputBase64BufferSize = outputBase64BufferSize + (diff + 1) + paddingSize;
    }

    /**
     * Specifying how many new-line characters will be set.
     * (update size of Base64 string buffer)
     */

    long int newLinesSize = (outputBase64BufferSize / 76);
    outputBase64BufferSize = outputBase64BufferSize + newLinesSize;

    /**
     * Allocating memory for Base64 string buffer.
     */

    printf("Allocating %ldB memory for Base64 string.\n", outputBase64BufferSize);
    outputBase64Buffer = (char *)malloc((outputBase64BufferSize) * sizeof(char));

    unsigned char last;  /* Cutted part of previous byte. */
    unsigned char newer; /* New base64 byte. */

    int shiftLast, shiftR; /* Variable for bits shifting. */

    /* Arrays with values for sequence of shift. */

    int seqR[3] = {2, 4, 6};
    int seqL[3] = {0, 6, 4};

    /**
     * Indicates which byte from the three-bytes packet is current
     * (possible values are 0, 1 and 2).
     */
    int bytePos;

    long int pointer = 0; /* Indicates current position in new Base64 string. */

    /**
     * Main loop for encoding sequence.
     * (each byte from file)
     */
    for (int i = 0; i < *inputBufferSize; i++)
    {
        addNewLineChar(outputBase64Buffer, &pointer);

        bytePos = i % 3;

        /**
         * Set shift right and last byte shift left values.
         */

        shiftR = seqR[(i) % 3];
        shiftLast = seqL[(i) % 3];

        /**
         * Shift current buffer byte.
         */

        newer = inputBuffer[i] >> shiftR;

        /**
         * When three-bytes packet's current position isn't 0, get part of the last byte
         * and concatenate with current buffer (shifted) byte.
         */
        if (bytePos != 0)
        {
            last = inputBuffer[i - 1] << shiftLast;
            last = last >> 2;
            newer = (newer | last);
        }

        /**
         * We have an encoded byte in 'newer' variable.
         * Write Base64 character to output buffer and
         * then increment pointer.
         */

        outputBase64Buffer[pointer] = BASE64_ALPHABET[newer];
        pointer = pointer + 1;

        /**
         * Little differences in operations when last byte form three-bytes
         * packet is just encoded or when is the last byte from input data buffer.
         */
        if (bytePos == 2 || ((i + 1) == *inputBufferSize))
        {
            addNewLineChar(outputBase64Buffer, &pointer);

            newer = inputBuffer[i];

            if (bytePos == 1)
            {
                newer = newer << 2;
            }
            else if (bytePos == 0)
            {
                newer = newer << 4;
            }

            /**
             * In this case we make our operations only on current byte
             * of buffer so have to set last two bits to 0 value.
             */

            newer = newer &= ~(1 << 7);
            newer = newer &= ~(1 << 6);

            outputBase64Buffer[pointer] = BASE64_ALPHABET[newer];
            pointer = pointer + 1;
        }
    }

    /**
     * Adds padding characters at the end of a buffer.
     */
    for (int i = 0; i < paddingSize; i++)
    {
        outputBase64Buffer[pointer] = '=';
        pointer = pointer + 1;
    }

    EncodeResult result;
    result.outputBase64Buffer = outputBase64Buffer;
    result.outputBase64BufferSize = outputBase64BufferSize;

    return result;
}
