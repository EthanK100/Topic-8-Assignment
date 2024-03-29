#include "BinarySearchTree.h"
using namespace std;

/** @file PrecondViolatedExcept.cpp */

PrecondViolatedExcept::PrecondViolatedExcept(const string & message)
    : logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor


/** @file BinaryNode.cpp*/

//constructors
template < class ItemType>
BinaryNode<ItemType>::BinaryNode()
{

}

template < class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
{

}

template < class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem, shared_ptr<BinaryNode<ItemType>> leftPtr, shared_ptr<BinaryNode<ItemType>> rightPtr)
{

}


template < class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}

template < class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
    return item;
}

template < class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
    bool leaf = false;
    if ((leftChildPtr == nullptr) || (rightChildPtr == nullptr))
    {
        leaf = true;
    }
    
    return leaf;
}

template < class ItemType>
auto BinaryNode<ItemType>::getLeftChildPtr() const
{
    return leftChildPtr;
}

template < class ItemType>
auto BinaryNode<ItemType>::getRightChildPtr() const
{
    return rightChildPtr;
}

template < class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr)
{
    leftChildPtr = leftPtr;
}

template < class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr)
{
    rightChildPtr = rightPtr;
}

   
/** @file BinaryNodeTree.cpp*/

// constructors
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::
BinaryNodeTree(const ItemType& rootItem)
    : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::
BinaryNodeTree(const ItemType& rootItem, const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr) 
    : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr)))
{}// end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::
BinaryNodeTree(const shared_ptr<BinaryNodeTree<ItemType>>& tree)
{

}

template<class ItemType>
auto BinaryNodeTree<ItemType>::balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr,
    shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
    if (subTreePtr->getItem() >= newNodePtr->getItem() )
    {
        if (subTreePtr->isleaf())
        {
            subTreePtr->setRightChildPtr(newNodePtr);
        }
        else 
        {
           subTreePtr->setRightChildPtr( balancedAdd(subTreePtr->getRightChildPtr(), subTreePtr));
        }
    }
    else
    {
        if (subTreePtr->isleaf())
        {
            subTreePtr->setLeftChildPtr(newNodePtr);
           
        }
        else
        {
           subTreePtr->setLeftChildPtr( balancedAdd(subTreePtr->getLeftChildPtr(), subTreePtr));
        }
        
    }
    return subTreePtr;

}


template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{

    auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
    //rootPtr = placeNode(rootPtr, newNodePtr);

    if (rootPtr == nullptr)
    {
        rootPtr = newNodePtr;
    }
    else 
    {
        rootPtr = balancedAdd(rootPtr, newNodePtr);
    }
    

    return true;

}