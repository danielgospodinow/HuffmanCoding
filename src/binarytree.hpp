#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <string>
#include <functional>

template <class T>
class BinaryTree
{
public:
    BinaryTree(T data, BinaryTree<T>* leftChild = nullptr, BinaryTree<T>* rightChild = nullptr);
    ~BinaryTree();
    BinaryTree* getLeftChild();
    BinaryTree* getRightChild();
    bool isLeaf();
    T getData();

private:
    T _data;
    BinaryTree *_leftChild, *_rightChild;
};

#include "binarytree.cpp"

#endif
