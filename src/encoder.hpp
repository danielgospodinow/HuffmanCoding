#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <math.h>
#include <stdlib.h>

#include "binarytree.hpp"

typedef unsigned char uchar;
typedef unsigned int uint;

class Encoder
{
public:
    static std::string encode(std::string const& str, bool asBinary = false);

private:
    Encoder() {}
    ~Encoder() {}
    Encoder(Encoder const& other) {}
    Encoder& operator= (Encoder const& other) {}

    static BinaryTree<uint>* getRoot(std::vector<BinaryTree<uint>*>& leafs);
    static BinaryTree<uint>* getSmallest(std::vector<BinaryTree<uint>*>& leafs);
    static void getCodingTable(BinaryTree<uint>* const& root, std::vector<std::tuple<char, std::string>>& ret, std::string path);
    static std::string getEncodedString(std::vector<std::tuple<char, std::string>> const& codingTable, std::string const& str);
    static std::string appendHuffTree(std::string const& str, BinaryTree<uint>* const& root);
    static std::string convertBinToDec(std::string const& str);
    static std::string serializeHuffTree(BinaryTree<uint>* const& root);
    static uchar getLeafChar(BinaryTree<uint>* const& leaf);

    static BinaryTree<uint>** leafs;
    static char* leafChars;
    static uint leafsSize;
    static bool printBinary;
};

#endif
