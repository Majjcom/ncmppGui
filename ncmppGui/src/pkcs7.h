#pragma once

namespace pkcs7
{
    unsigned int pad_size(const unsigned char* src_, unsigned int len_);
    void unpad(const unsigned char* src_, unsigned int len_, unsigned char* tgt_);
}
