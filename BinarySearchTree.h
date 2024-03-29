#pragma once
using namespace std;
class BinarySearchTree
{
};

/** @file NotFoundException.h*/

#include <stdexcept>
#include <string>
class NotFoundException : public exception
{
public:
    NotFoundException(const string& message = "")
        : exception("Target not found")
    {
    } // end constructor
}; // end NotFoundException

/** @file PrecondViolatedExcept.h */
#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public logic_error
{
public:
       PrecondViolatedExcept(const string & message = "");
}; // end PrecondViolatedExcept
#endif

/** Interface for the ADT binary tree.
  @file BinaryTreeInterface.h */

#ifndef BINARY_TREE_INTERFACE_
 #define BINARY_TREE_INTERFACE_

 template < class ItemType>
 class BinaryTreeInterface
 {
 public:
        /** Tests whether this binary tree is empty.
          @return  True if the binary tree is empty, or false if not. */
            virtual bool isEmpty() const = 0;
    
            /** Gets the height of this binary tree.
             @return  The height of the binary tree. */
            virtual int getHeight() const = 0;
    
            /** Gets the number of nodes in this binary tree.
              @return  The number of nodes in the binary tree. */
            virtual int getNumberOfNodes() const = 0;
    
            /** Gets the data that is in the root of this binary tree.
             @pre  The binary tree is not empty.
             @post  The root's data has been returned, and the binary tree is unchanged.
             @return  The data in the root of the binary tree. */
            virtual ItemType getRootData() const = 0;
    
            /** Replaces the data in the root of this binary tree with the given data, if the tree is not empty. However, if the tree is empty, inserts a new root node containing the given data into the tree.
             @pre  None.
             @post  The data in the root of the binary tree is as given.
             @param newData  The data for the root. */
            virtual void setRootData(const ItemType & newData) = 0;
    
            /** Adds the given data to this binary tree.
             @param newData  The data to add to the binary tree.
             @post  The binary tree contains the new data.
             @return  True if the addition is successful, or false if not. */
            virtual bool add(const ItemType & newData) = 0;
    
            /** Removes the specified data from this binary tree.
             @param target  The data to remove from the binary tree.
             @return  True if the removal is successful, or false if not. */
            virtual bool remove(const ItemType & target) = 0;
    
            /** Removes all data from this binary tree. */
            virtual void clear() = 0;
    
            /** Retrieves the specified data from this binary tree.
             @post  The desired data has been returned, and the binary tree
                is unchanged. If no such data was found, an exception is thrown.
             @param target  The data to locate.
             @return  The data in the binary tree that matches the given data.*/
            virtual ItemType getEntry(const ItemType & target) const = 0;
    
            /** Tests whether the specified data occurs in this binary tree.
             @post  The binary tree is unchanged.
             @param target  The data to find.
             @return  True if data matching the target occurs in the tree, or false if not. */
            virtual bool contains(const ItemType & target) const = 0;
    
            /** Traverses this binary tree in preorder (inorder, postorder) and
                calls the function visit once for each node.
            @param visit  A client-defined function that performs an operation on
               either each visited node or its data. */
            virtual void preorderTraverse(void visit(ItemType&)) const = 0;
        virtual void inorderTraverse(void visit(ItemType&)) const = 0;
        virtual void postorderTraverse(void visit(ItemType&)) const = 0;
    
            /** Destroys this tree and frees its assigned memory. */
            virtual ~BinaryTreeInterface() {  }
     }; // end BinaryTreeInterface
#endif

 /** A class of nodes for a link-based binary tree.
   @file BinaryNode.h */
 
#ifndef BINARY_NODE_
      #define BINARY_NODE_
      #include <memory>
     
      template < class ItemType>
      class BinaryNode
      {
      private:
             ItemType                              item;          // Data portion
             shared_ptr<BinaryNode<ItemType>> leftChildPtr;  // Pointer to left child
             shared_ptr<BinaryNode<ItemType>> rightChildPtr; // Pointer to right child
         
      public:
             BinaryNode();
             BinaryNode(const ItemType & anItem);
             BinaryNode(const ItemType & anItem,
                            shared_ptr<BinaryNode<ItemType>> leftPtr,
                            shared_ptr<BinaryNode<ItemType>> rightPtr);
         
                 void setItem(const ItemType & anItem);
             ItemType getItem() const;
         
                 bool isLeaf() const;
         
                 auto getLeftChildPtr() const;
             auto getRightChildPtr() const;
         
                 void setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr);
             void setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr);
          }; // end BinaryNode
 
#endif


      /** ADT binary tree: Link-based implementation.
        @file BinaryNodeTree.h */
      
#ifndef BINARY_NODE_TREE_
           #define BINARY_NODE_TREE_

          
           template < class ItemType>
           class BinaryNodeTree : public BinaryTreeInterface < ItemType>
           {
           private:
                  shared_ptr<BinaryNode<ItemType>> rootPtr;
              
           protected:
               //------------------------------------------------------------
                   //      Protected Utility Methods Section:
                   //      Recursive helper methods for the public methods.
                   //------------------------------------------------------------
                      int getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
                  int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
              
                      // Recursively adds a new node to the tree in a left/right fashion to keep tree balanced.
                      auto balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                           shared_ptr<BinaryNode<ItemType>> newNodePtr);
              
                      // Removes the target value from the tree.
                      virtual int/*auto*/ removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& isSuccessful);
              
                      // Copies values up the tree to overwrite value in current node until
                      // a leaf is reached; the leaf is then removed, since its value is stored in the parent.
                      auto moveValuesUpTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);
              
                      // Recursively searches for target value.
                      virtual int/*auto*/ findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType & target, bool& isSuccessful) const;
              
                      // Copies the tree rooted at treePtr and returns a pointer to the root of the copy.
                      auto copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;
              
                      // Recursively deletes all nodes from the tree.
                      void destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);
              
                      // Recursive traversal helper methods:
                      void preorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;
                  void inorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;
                  void postorder(void visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;
              
           public:
               //------------------------------------------------------------
                   //       Constructor and Destructor Section.
                   //------------------------------------------------------------
                      BinaryNodeTree();
                  BinaryNodeTree(const ItemType & rootItem);
                  BinaryNodeTree(const ItemType & rootItem,
                                     const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                                     const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
                  BinaryNodeTree(const shared_ptr<BinaryNodeTree<ItemType>>&tree);
                  virtual ~BinaryNodeTree();
              
                   //------------------------------------------------------------
                   //       Public BinaryTreeInterface Methods Section.
                   //------------------------------------------------------------
                      bool isEmpty() const;
                  int getHeight() const;
                  int getNumberOfNodes() const;
                  ItemType getRootData() const throw(PrecondViolatedExcept);
                  void setRootData(const ItemType & newData);
                  bool add(const ItemType & newData); // Adds an item to the tree
                  bool remove(const ItemType & data); // Removes specified item from the tree
                  void clear();
                  ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
                  bool contains(const ItemType & anEntry) const;
              
                   //------------------------------------------------------------
                   //       Public Traversals Section.
                   //------------------------------------------------------------
                      void preorderTraverse(void visit(ItemType&)) const;
                  void inorderTraverse(void visit(ItemType&)) const;
                  void postorderTraverse(void visit(ItemType&)) const;
              
                   //------------------------------------------------------------
                   //       Overloaded Operator Section.
                   //------------------------------------------------------------
                      BinaryNodeTree & operator=(const BinaryNodeTree & rightHandSide);
               }; // end BinaryNodeTree
#endif