// Binary tree abstract base class

 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() 
	{
		destroyTree(rootPtr);
	}
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void breadthFirst(void visit(ItemType&)) const { _breadthFirst(visit, rootPtr); }
	void displayIndented(void visit(ItemType &)) const { _displayIndented(visit, rootPtr, 0); }
	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _displayIndented(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int height) const;
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
    
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		if (nodePtr->getLeftPtr())
			destroyTree(nodePtr->getLeftPtr());
		if (nodePtr->getRightPtr())
			destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}  


template<class ItemType>
void BinaryTree<ItemType>::_breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Queue<BinaryNode<ItemType>*> q;
	if (nodePtr)
	{
		q.enqueue(nodePtr);
		visit(nodePtr->getItem());
	}
	while (!q.isEmpty())
	{
		BinaryNode<ItemType>* tempNodePtr;
		q.dequeue(tempNodePtr);
		if (tempNodePtr->getLeftPtr())
		{
			q.enqueue(tempNodePtr->getLeftPtr());
			visit((tempNodePtr->getLeftPtr())->getItem());
		}
		if (tempNodePtr->getRightPtr())
		{
			q.enqueue(tempNodePtr->getRightPtr());
			visit((tempNodePtr->getRightPtr())->getItem());
		}
	}
	

}

template<class ItemType>
void BinaryTree<ItemType>::_displayIndented(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int space) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		space += count;
		_displayIndented(visit, nodePtr->getRightPtr(),space+1);
		cout << " \n ";
		for (int i = count; i < space; i++)
			cout << "\t\t\t";
		cout << space + 1 << ". ";
		visit(item);
		cout << endl;
		//level++;
		_displayIndented(visit, nodePtr->getLeftPtr(),space+1);
	}
}
template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}  


#endif

