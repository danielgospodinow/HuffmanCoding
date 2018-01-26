#include "encoder.hpp"

BinaryTree<uint>** Encoder::leafs = nullptr;
char* Encoder::leafChars = nullptr;
uint Encoder::leafsSize = 0;
bool Encoder::printBinary = false;

std::string Encoder::encode(std::string const& str, bool asBinary)
{
    printBinary = asBinary;
    std::map<uchar, uint> charCounts;
    std::vector<BinaryTree<uint>*> binTrees;

    for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        ++charCounts[*it];

    if((leafsSize = charCounts.size()) <= 1)
    {
        std::cerr << "Cannot compress too small files!" << std::endl;
        throw 1;
    }

    leafs = new BinaryTree<uint>*[leafsSize];
    leafChars = new char[leafsSize];

    for(std::map<uchar, uint>::const_iterator it = charCounts.begin(); it != charCounts.end(); ++it)
    {
        uint i = std::distance((std::map<uchar, uint>::const_iterator)charCounts.begin(), it);
        BinaryTree<uint>* currentLeaf = new BinaryTree<uint>(it->second);

        leafs[i] = currentLeaf;
        binTrees.push_back(currentLeaf);
        leafChars[i] = it->first;
    }

    BinaryTree<uint>* root = getRoot(binTrees);
    std::vector<std::tuple<char, std::string>> codingTable;

    if(!root->isLeaf())
        getCodingTable(root, codingTable, "");
    else
        codingTable.push_back(std::tuple<char, std::string>(leafChars[0], "0"));

    std::string encodedString = getEncodedString(codingTable, str);
    std::cout << "Compression %: " << 100 - (int)((float)encodedString.length() / (str.length() * 8) * 100)  << std::endl;

    encodedString = appendHuffTree(convertBinToDec(encodedString), root);

    delete[] leafChars;
    delete[] leafs;
    delete root;
    leafsSize = 0;
    
    return encodedString;
}

void Encoder::getCodingTable(BinaryTree<uint> * const &root, std::vector<std::tuple<char, std::string> > &ret, std::string path)
{
    if(root->isLeaf())
    {
        for(int i=0; i<leafsSize; ++i)
            if(leafs[i] == root)
                ret.push_back(std::tuple<char, std::string> (leafChars[i], path));
    }
    else
    {
        getCodingTable(root->getLeftChild(), ret, path + "0");
        getCodingTable(root->getRightChild(), ret, path + "1");
    }
}

std::string Encoder::getEncodedString(const std::vector<std::tuple<char, std::string> > &codingTable, const std::string &str)
{
    std::string ret = "";

    for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        std::vector<std::tuple<char, std::string> >::const_iterator itemIter = std::find_if(codingTable.begin(), codingTable.end(), [&](const std::tuple<char, std::string>& tup){ return std::get<0>(tup) == *it; });
        ret += std::get<1>(*itemIter);
    }

    return ret;
}

BinaryTree<uint>* Encoder::getRoot(std::vector<BinaryTree<uint>*>& leafs)
{
    while(leafs.size() > 1)
    {
        BinaryTree<uint> *firstSmallest = getSmallest(leafs),
                *secondSmallest = getSmallest(leafs);

        leafs.push_back(new BinaryTree<uint>(firstSmallest->getData() + secondSmallest->getData(), firstSmallest, secondSmallest));
    }

    return *(leafs.begin());
}

BinaryTree<uint>* Encoder::getSmallest(std::vector<BinaryTree<uint>*>& leafs)
{
    BinaryTree<uint>* currSmallest = *(leafs.begin());

    for(std::vector<BinaryTree<uint>*>::const_iterator it = leafs.begin(); it != leafs.end(); ++it)
        if((*it)->getData() <= currSmallest->getData())
            currSmallest = *it;

    leafs.erase(std::find(leafs.begin(), leafs.end(), currSmallest));

    return currSmallest;
}

std::string Encoder::appendHuffTree(const std::string &str, BinaryTree<uint> * const &root)
{
    return serializeHuffTree(root) + "|" + str;
}

std::string Encoder::serializeHuffTree(BinaryTree<uint>* const& root)
{
    if(root->isLeaf())
        return std::string(1, getLeafChar(root));

    return "#{" + serializeHuffTree(root->getLeftChild()) + "," + serializeHuffTree(root->getRightChild()) + "}";
}

uchar Encoder::getLeafChar(BinaryTree<uint>* const& leaf)
{
    for(int i=0; i<leafsSize; ++i)
        if(leafs[i] == leaf)
            return leafChars[i];
}

std::string Encoder::convertBinToDec(const std::string &str)
{
    std::string ret = "";
    std::vector<std::string> strs;

    std::string currentStr = "";
    for(std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        int i = std::distance(str.begin(), it);

        if(i % 8 == 0 && i != 0)
        {
            strs.push_back(currentStr);
            currentStr = "";
            currentStr += *it;
        }
        else
        {
            currentStr += *it;
        }
    }

    if(currentStr.size() > 0) strs.push_back(currentStr);

    for(std::vector<std::string>::const_iterator it = strs.begin(); it != strs.end(); ++it)
    {
        uchar decNum = 0;
        std::string currentBinNum = *it;

        for(int i=currentBinNum.size() - 1; i>=0; --i)
            decNum += ((currentBinNum[i] - '0') * pow(2, (currentBinNum.size() - 1) - i));

        ret += std::string(1, decNum);

        if(printBinary) std::cout << (uint)decNum << " ";
    }
    if(printBinary) std::cout << std::endl;

    ret = std::string(1, (uchar)currentStr.size()) + ret;
    return ret;
}