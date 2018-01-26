#include "decoder.hpp"

std::string Decoder::decode(const std::string &str, const std::string &huffTree)
{
    if(huffTree.length() == 0)
    {
        std::cerr << "Cannot decompress without a Huffman tree" << std::endl;
        throw 1;
    }

    std::string ret = "", 
        encodedStr = convertToBinary(str) + "~";

    BinaryTree<uchar>* root = getBinTreeFromEncoding(huffTree, 
        [](std::string const& str) -> uchar {
            return ((*str.begin()) == '#') 
                ? '#'
                : *str.rbegin(); });
                
    BinaryTree<uchar>* iterRoot = root;

    for(std::string::const_iterator it = encodedStr.begin(); it != encodedStr.end(); ++it)
    {
        if(iterRoot->isLeaf())
        {
            ret += iterRoot->getData();
            iterRoot = root;
        }

        if(*it == '0')
            iterRoot = iterRoot->getLeftChild();
        else if(*it == '1')
            iterRoot = iterRoot->getRightChild();
    }

    delete root;
    return ret;
}

BinaryTree<uchar>* Decoder::getBinTreeFromEncoding(std::string const& huffTreeEncoding, std::function<uchar(std::string const&)> toT)
{
    if(huffTreeEncoding.find("{") == std::string::npos)
        return new BinaryTree<uchar> (toT(huffTreeEncoding));

    std::string rootNum = "", leftHuffTreeEncoding = "", rightHuffTreeEncoding = "";
    decodeBinTree(huffTreeEncoding, rootNum, leftHuffTreeEncoding, rightHuffTreeEncoding);
    
    return new BinaryTree<uchar>(toT(rootNum), getBinTreeFromEncoding(leftHuffTreeEncoding, toT), getBinTreeFromEncoding(rightHuffTreeEncoding, toT));
}

void Decoder::decodeBinTree(std::string const& huffTreeEncoding, std::string& rootNum, std::string& leftHuffTreeEncoding, std::string& rightHuffTreeEncoding)
{
    int openingI = -1, separatorI = -1, closingI = -1, penalty = 0;

    for(std::string::const_iterator it = huffTreeEncoding.begin(); it != huffTreeEncoding.end(); ++it)
    {
        if(*it == '{' && openingI == -1)
        {
            openingI = std::distance(huffTreeEncoding.begin(), it);
            rootNum = huffTreeEncoding.substr(0, openingI);
        }

        else if(*it == '{' && openingI != -1)
        {
            penalty += 1;
        }

        else if((*it == ',' && *(it-1) == '{') || (*it == ',' && *(it+1) == '}'))
        {
            continue;
        }

        else if(*it == ',' && separatorI == -1 && penalty == 0)
        {
            separatorI = std::distance(huffTreeEncoding.begin() + openingI, it);
            leftHuffTreeEncoding = huffTreeEncoding.substr((openingI + 1), separatorI - 1);
        }

        else if(*it == ',' && separatorI == -1 && penalty != 0)
        {
            penalty -= 1;
        }

        else if(*it == '}')
        {
            closingI = std::distance(huffTreeEncoding.begin() + openingI + separatorI, it);
            rightHuffTreeEncoding = huffTreeEncoding.substr((openingI + separatorI + 1), closingI - 1);
        }
    }
}

std::string Decoder::convertToBinary(std::string const& str)
{
    std::string ret = "";

    for(std::string::const_iterator it = str.begin() + 1; it != str.end() - 1; ++it)
        ret += convertToBinary(*it);

    ret += convertToBinary(*(str.end() - 1), true, (uint)(*str.begin()));
    return ret;
}

std::string Decoder::convertToBinary(uchar ch, bool last, uint lastDigLen)
{
    std::string ret = "";
    
    while(ch > 0)
    {
        (ch % 2 == 0) ? (ret = "0" + ret) : (ret = "1" + ret);
        ch /= 2;
    }

    (last) ? fillBin(ret, lastDigLen) : fillBin(ret, 8);

    return ret;
}

void Decoder::fillBin(std::string& str, uint fillToLen)
{
    while(str.length() < fillToLen)
        //Slow, can be optimized
        str = "0" + str;
}