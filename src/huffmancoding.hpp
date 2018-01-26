#ifndef HUFFMANCODING_HPP
#define HUFFMANCODING_HPP

#include <string>
#include <fstream>

#include "encoder.hpp"
#include "decoder.hpp"

class HuffmanCoding
{
public:
    static void encode(std::ifstream& inputFile, std::ofstream& outputFile, bool asBinary = true);
    static void decode(std::ifstream& inputFile, std::ofstream& outputFile);

private:
    HuffmanCoding() {}
    ~HuffmanCoding() {}
    HuffmanCoding(HuffmanCoding const& other) {}
    HuffmanCoding& operator= (HuffmanCoding const& other) {}
};

#endif
