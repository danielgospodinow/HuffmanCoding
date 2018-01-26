#ifndef DECODER_HPP
#define DECODER_HPP

#include <iostream>
#include <tuple>
#include <stdlib.h>

#include "binarytree.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

class Decoder
{
public:
    static std::string decode(std::string const& str, std::string const& huffTree);

private:
    Decoder();
    ~Decoder() {}
    Decoder(Decoder const& other) {}
    Decoder& operator= (Decoder const& other) {}

    static BinaryTree<uchar>* getBinTreeFromEncoding(std::string const& huffTreeEncoding, std::function<uchar(std::string const&)> toT);
    static void decodeBinTree(std::string const& huffTreeEncoding, std::string& rootNum, std::string& leftHuffTreeEncoding, std::string& rightHuffTreeEncoding);
    static std::string convertToBinary(std::string const& str);
    static std::string convertToBinary(uchar ch, bool last = false, uint lastDigLen = 0);
    static void fillBin(std::string& str, uint fillToLen);
};

#endif
