#include "huffmancoding.hpp"

void startUI()
{
    std::cout << "Welcome to DIP (Dancho's ZIP)!" << std::endl;

    bool isRunning = true;

    enum ProgramMode {Compress, Decompress};

    ProgramMode currentMode = Compress;
    std::cout << "Current mode: -c[ompress]" << std::endl;
    std::string input;

    std::ifstream inputFile;
    std::ofstream outputFile;

    bool asBinary = false;

    while(isRunning)
    {
        std::getline(std::cin, input);

        if(input == "-c" || input == "-compress")
        {
            currentMode = Compress;
            std::cout << "Current mode: -c[ompress]" << std::endl;
            continue;
        }

        if(input == "-d" || input == "-decompress")
        {
            currentMode = Decompress;
            std::cout << "Current mode: -d[ecompress]" << std::endl;
            continue;
        }

        if(input.substr(0,2) == "-i")
        {
            if(input.length() <= 2)
            {   
                std::cerr << "Bad input!" << std::endl;
                continue;
            }

            if(inputFile.is_open())
                inputFile.close();

            inputFile.open(input.substr(3, input.size() - 3), std::ios::in | std::ios::binary);
            continue;
        }

        if(input.substr(0,2) == "-o")
        {
            if(input.length() <= 2)
            {   
                std::cerr << "Bad input!" << std::endl;
                continue;
            }

            if(outputFile.is_open())
                outputFile.close();

            outputFile.open(input.substr(3, input.size() - 3), std::ios::out | std::ios::binary);
            continue;
        }

        if(input == "-e" || input == "-execute")
        {
            if(!inputFile.is_open() || !outputFile.is_open())
            {
                std::cout << "Streams aren't both initialized!" << std::endl;
                continue;
            }

            if(currentMode == Compress)
                HuffmanCoding::encode(inputFile, outputFile, asBinary);
            else
                HuffmanCoding::decode(inputFile, outputFile);

            inputFile.close();
            outputFile.close();

            continue;
        }

        if(input == "-b" || input == "-binary")
        {
            asBinary = !asBinary;

            std::cout << (asBinary?"Output mode set to: Binary":"Output mode set to: Not binary") << std::endl;
            continue;
        }

        if(input == "-q" || input == "-quit")
        {
            isRunning = !isRunning;

            continue;
        }    

        std::cout << "Unsupported command!" << std::endl;
    }
}

void decodeBinTree(std::string const& huffTreeEncoding, std::string& rootNum, std::string& leftHuffTreeEncoding, std::string& rightHuffTreeEncoding);

int main()
{
    startUI();
    return 0;
}

/* TODO:
 *
 * - Adaptive Huffman Coding
 */
