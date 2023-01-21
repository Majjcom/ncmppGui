
#include "pkcs7.h"

unsigned int pkcs7::pad_size(const unsigned char* src_, unsigned int len_)
{
    unsigned int padlen = src_[len_ - 1];
    return len_ - padlen;
}

void pkcs7::unpad(const unsigned char* src_, unsigned int len_, unsigned char* tgt_)
{
    unsigned int size = pkcs7::pad_size(src_, len_);
    for (unsigned int i = 0; i < size; i++)
    {
        tgt_[i] = src_[i];
    }
}
