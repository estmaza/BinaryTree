#include "BinaryTree.h"
#include <conio.h>


int main()
{
	BinaryTree *myTree = new BinaryTree;
/*
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
*/
	myTree->AddNewElem(23, 5);
	myTree->AddNewElem(42, 5);
	myTree->AddNewElem(15, 5);
	myTree->AddNewElem(19, 5);
	myTree->AddNewElem(21, 5);
	myTree->AddNewElem(20, 5);
	myTree->AddNewElem(31, 5);
	myTree->AddNewElem(49, 5);
	myTree->AddNewElem(45, 5);
	myTree->AddNewElem(8, 5);
	myTree->AddNewElem(12, 5);
	myTree->AddNewElem(4, 5);
	myTree->AddNewElem(17, 5);
	myTree->AddNewElem(10, 5);
	myTree->AddNewElem(16, 5);
	myTree->AddNewElem(18, 5);
	myTree->AddNewElem(2, 5);
	myTree->AddNewElem(6, 5);
	myTree->AddNewElem(13, 5);
	myTree->AddNewElem(27, 5);
	myTree->AddNewElem(36, 5);
	myTree->AddNewElem(39, 5);
	myTree->AddNewElem(37, 5);
	myTree->AddNewElem(40, 5);
	myTree->AddNewElem(30, 5);
	myTree->AddNewElem(28, 5);
	myTree->AddNewElem(29, 5);
	myTree->AddNewElem(41, 5);
	myTree->AddNewElem(51, 5);
	myTree->AddNewElem(50, 5);

	//myTree->DeleteElByKey(1);

	_getch();
	return 0;
}