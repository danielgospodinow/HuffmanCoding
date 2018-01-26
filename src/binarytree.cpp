#include "binarytree.hpp"

#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

template <class T>
BinaryTree<T>::BinaryTree(T data, BinaryTree<T>* leftChild, BinaryTree<T>* rightChild):
    _data(data), _leftChild(leftChild), _rightChild(rightChild)
{
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    delete _leftChild;
    delete _rightChild;
}

template<class T>
BinaryTree<T>* BinaryTree<T>::getLeftChild()
{
    return _leftChild;
}

template<class T>
BinaryTree<T>* BinaryTree<T>::getRightChild()
{
    return _rightChild;
}

template<class T>
T BinaryTree<T>::getData()
{
    return _data;
}

template<class T>
bool BinaryTree<T>::isLeaf()
{
    return (_leftChild == _rightChild && _rightChild == nullptr);
}

#endif
