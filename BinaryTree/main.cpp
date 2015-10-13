#include "BinaryTree.h"
#include <conio.h>


int main()
{
	BinaryTree *myTree = new BinaryTree;

	myTree->AddNewElem(5, 5);
	myTree->AddNewElem(2, 2);
	myTree->AddNewElem(3, 3);	
	myTree->AddNewElem(1, 1);	
	myTree->AddNewElem(8, 8);
	myTree->AddNewElem(6, 6);
	myTree->AddNewElem(7, 7);
	myTree->AddNewElem(9, 9);
	
//	myTree->FindElByKey(1);
//	myTree->FindElByData(1);

//	myTree->FindElByKeyRec(6);

//	myTree->FindElByDataRec(1);
//	myTree->FindElByDataBreadth(3);				//	работает

	myTree->DeleteElByKey(1);

	_getch();
	return 0;
}