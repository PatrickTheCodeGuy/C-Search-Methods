// Binary Search Tree ADT

 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"


template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
	BinaryNode<ItemType>* _insertByNumber(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

	//print all nodes matching target string
	bool _printNodes(BinaryNode<ItemType>* treePtr, const string & target) const;
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	bool insertByNumber(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	ItemType findLeftmostNode();
	ItemType findRightmostNode();
	//print all nodes matching target string author: James Martin
	bool printNodes(const string & target) const;
};


///////////////////////// public function definitions ///////////////////////////
//this function will insert a record into the tree sorted by secondary key(artist) 

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
} 

//used for inserting a record into the tree by primary key(record number) 
template<class ItemType>
bool BinarySearchTree<ItemType>::insertByNumber(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insertByNumber(this->rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	bool found = false;
	//BinaryNode<ItemType>* nodePtr = this->rootPtr;
	
	BinaryNode<ItemType>* nodePtr = this->findNode(this->rootPtr, anEntry);
	if (nodePtr != 0)
	{
		returnedItem = nodePtr->getItem();
		found = true;
	}
	
	return found;
}  


template<class ItemType>
bool BinarySearchTree<ItemType>::printNodes(const string & anEntry) const
{
	bool found = false;

	if(this->_printNodes(this->rootPtr, anEntry))
		found = true;

	return found;
}


//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		nodePtr = newNodePtr;
	else if (newNodePtr->getItem()->getBand() <= nodePtr->getItem()->getBand())
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	else
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	return nodePtr;

}  
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insertByNumber(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		nodePtr = newNodePtr;
	else if (newNodePtr->getItem()->getRecNum() <= nodePtr->getItem()->getRecNum())
		nodePtr->setLeftPtr(_insertByNumber(nodePtr->getLeftPtr(), newNodePtr));
	else
		nodePtr->setRightPtr(_insertByNumber(nodePtr->getRightPtr(), newNodePtr));
	return nodePtr;

}
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::findLeftmostNode()
{
	BinaryNode<ItemType>* nodePtr = this->rootPtr;
	while (nodePtr->getLeftPtr() != 0)
		nodePtr = nodePtr->getLeftPtr();
	return nodePtr->getItem();
}
template<class ItemType>
ItemType BinarySearchTree<ItemType>::findRightmostNode()
{
	BinaryNode<ItemType>* nodePtr = this->rootPtr;
	while (nodePtr->getRightPtr() != 0)
		nodePtr = nodePtr->getRightPtr();
	return nodePtr->getItem();
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	//BinaryNode *nodePtr = rootPtr;
	
		 if(nodePtr != 0)
		 {
		 if (nodePtr->getItem() == target)
			 return nodePtr;
		 else if (target < nodePtr->getItem())
			 return findNode(nodePtr->getLeftPtr(),target);
		 else
			 return findNode(nodePtr->getRightPtr(),target);
		 }
	 return nodePtr;
}  
template<class ItemType>
bool BinarySearchTree<ItemType>::_printNodes(BinaryNode<ItemType>* nodePtr,
	const string & target) const
{
	bool found = false;
	if (nodePtr != 0)
	{
		if (nodePtr->getItem()->getBand() == target)
		{
			cout << *(nodePtr->getItem());
			found = true;
		}
			
		//else if (target < nodePtr->getItem()->getBand())
			_printNodes(nodePtr->getLeftPtr(), target);
		//else
			_printNodes(nodePtr->getRightPtr(), target);
	}
	return found;
}

#endif
