#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

struct Result
{
    char *outputBase64Buffer;
    long int outputBase64BufferSize;
};

typedef struct Result EncodeResult;

#endif
