#include "huffmancoding.hpp"

void HuffmanCoding::encode(std::ifstream& inputFile, std::ofstream& outputFile, bool asBinary)
{
    std::string inputFileStr = "";
    std::string line = "";

    while (std::getline(inputFile, line))
        inputFileStr += line + "\n";
    inputFileStr.pop_back();

    outputFile << Encoder::encode(inputFileStr, asBinary);
    outputFile.close();
}

void HuffmanCoding::decode(std::ifstream &inputFile, std::ofstream &outputFile)
{
    std::string huffTree = "", encodedStr = "";
    std::string inputFileStr = "", line = "";

    while (std::getline(inputFile, line))
        inputFileStr += line + "\n";
    inputFileStr.pop_back();

    std::size_t separator = inputFileStr.find_first_of("|");
    huffTree = inputFileStr.substr(0, separator), encodedStr = inputFileStr.substr(separator + 1);
    
    outputFile << Decoder::decode(encodedStr, huffTree);
    outputFile.close();
}
