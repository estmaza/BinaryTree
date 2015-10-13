#include <stdlib.h>

#define	SUCCESS_OPER		0x0
#define	NOT_SUCCESS_OPER	0x1

using namespace std;

typedef int data;

/*
//template<template IDType, typename ElemType> SomeClass
template<int IDType, typename ElemType> SomeClass
{
public:
virtual SomeClass& operator()(IDType &ID, ElemType &Inf) = 0;
};
*/


template <class TreeElem> class List
{
	struct ListElem
	{
		TreeElem treeElem;
		ListElem *Next;
	};

	ListElem *Head, *Tail, *CurPos;

public:

	List()
	{
		CurPos = Tail = Head = nullptr;
	}

	bool AddListElem(TreeElem &treeElem)
	{
		ListElem *Cur = new ListElem;
		Cur->treeElem = treeElem;
		Cur->Next = nullptr;
		if (Head)						//	Head != nullptr
			Tail->Next = Cur;
		else
			CurPos = Head = Cur;
		Tail = Cur;
		return SUCCESS_OPER;
	}

	void SetStart()
	{
		CurPos = Head;
	}

	bool CurLevelExist()
	{
		if (CurPos)					// CurPos != null
		{
			return true;
		}
		return false;
	}

	bool GetCurInf(TreeElem &Elem)					//	какой то он странный. Ох и да))
	{
		if (CurPos)
		{
			Elem = CurPos->treeElem;
			return true;
		}
		return false;
	}

	bool RewriteCurInf(TreeElem &Elem)				//	тут можно заменить & на *	???
	{
		CurPos->treeElem = Elem;
		return SUCCESS_OPER;
	}

	void DeleteLastListElem()
	{
		SetStart();
		while (CurPos->Next != Tail)
		{
			CurPos = CurPos->Next;
		}

		delete Tail;
		Tail = CurPos;
		Tail->Next = nullptr;
	}

	List<TreeElem>& operator++()
	{
		if (CurPos)
			CurPos = CurPos->Next;
		return *this;
	}

	void DeleteAllListElem()
	{
		ListElem *Cur = Head;
		while (Cur != nullptr)
		{
			Cur = Cur->Next;
			delete Cur;
		}
		Head = Tail = CurPos = nullptr;
	}
};

class BinaryTree 
{
	struct TreeElem
	{
		int ID;
		data Data;
		TreeElem *Left, *Right, *Next, *Prev;
	};

	TreeElem* Root;											// указатель на корень дерева 
	List<TreeElem*> list;
	
public:

	BinaryTree()
	{
		Root = nullptr;	
	}

	BinaryTree(int id, data data)
	{
		AddNewElem(id, data);
	}

	~BinaryTree()
	{
		delete this;	
	}

	// добавить элемент
	bool AddNewElem(int id, data Data)
	{
		TreeElem *Parent = nullptr, *TElem = nullptr;

		if (Root)										//	!= nullptr - findpos
		{
			if (FindPos(id, Parent) == nullptr)
			{
				TElem = new TreeElem;
				Parent->ID > id ? Parent->Left = TElem : Parent->Right = TElem;		//	прикрепляем к родителю

				if (list.CurLevelExist())				//	уровень существует
				{
					//	наш элемент не первый. линкер
					TreeElem *ListElemInf, *Prev = NULL;
					list.GetCurInf(ListElemInf);
					
					while (ListElemInf && id > ListElemInf->ID)	//	(!)
					{
						Prev = ListElemInf;
						ListElemInf = ListElemInf->Next;
					}

					if (ListElemInf)
					{
						TElem->Next = ListElemInf;
						Prev ? Prev->Next = TElem : list.RewriteCurInf(TElem);
						ListElemInf->Prev = TElem;
					}
					else
					{
						//	последний
						Prev->Next = TElem;
						TElem->Next = nullptr;	//	(!)
					}
					TElem->Prev = Prev;
					
//-----------------------------------------------------------------------
					/*
					if (ListElemInf->ID < id)
					{
						//	не первый
						//	находим позицию
						TreeElem *Pos = nullptr;
						list.GetCurInf(Pos);

						while (Pos->Next != nullptr && Pos->Next->ID < id)
						{
							Pos = Pos->Next;
						}

						if (Pos->Next != nullptr)
						{
							TElem->Next = Pos->Next;
							TElem->Prev = Pos;

							Pos->Next->Prev = TElem;
							Pos->Next = TElem;
						}
						else
						{
							TElem->Next = nullptr;
							TElem->Prev = Pos;

							Pos->Next = TElem;
						}
					}
					else
					{
						//	первый
						ListElemInf->Prev = TElem;		

						TElem->Next = ListElemInf;
						TElem->Prev = nullptr;

						list.RewriteCurInf(TElem);
					}
					*/
				}
				else									//	уровень не существует
				{
					//	наш элемент первый. добавить эл. Лист и в голову впихнуть наш ТриЭлем
					TElem->Prev = TElem->Next = nullptr;

					list.AddListElem(TElem);
				}				 
			}
			else										//	позиция не найдена (занята)
			{
				return NOT_SUCCESS_OPER;
			}
		}
		else											//	добавляем первый элемент
		{
			Root = TElem = new TreeElem;
			
			TElem->Prev = TElem->Next = nullptr;

			list.AddListElem(TElem);
		}

		TElem->ID = id;
		TElem->Data = Data;
		TElem->Left = nullptr;
		TElem->Right = nullptr;
		
		
		return SUCCESS_OPER;
	}

//------------------------------------------------------------------------
//														   Поиск в глубину
//------------------------------------------------------------------------

	bool FindElByKey(int id)								//	по ключу 
	{	

		TreeElem *Pos = Root;

		while (Pos != nullptr)												//	тут кто то ксть? пока тут не посто
		{
			if (Pos->ID == id)
				return Pos;
			Pos = Pos->ID > id ? Pos->Left : Pos->Right;
		}
		return Pos != NULL;

		/*
		if (Root)
			return false;
		
		TreeElem *Cur = Root;
		while (Cur->ID != id)
		{
			//(Cur->ID < id) ? Cur = Cur->Right : Cur = Cur->Left;
			if (Cur->ID < id)
			{
				if (Cur->Right == nullptr)
				{
					return false;
				}
				Cur = Cur->Right;
			}
			else
			{
				if (Cur->Left == nullptr)
				{
					return false;
				}
				Cur = Cur->Left;
			}
		}
		return true;
		*/
	}

	bool FindElByData(data data)							//	поиск по инфе в глубину.
	{		
		TreeElem *Cur = Root;
		return FindElByDataRec(data, Cur);		
	}
//------------------------------------------------------------------------
//															Поиск в ширину
//------------------------------------------------------------------------

	bool FindElByDataBreadth(data data)
	{
		TreeElem *CurTreeElem = nullptr;
		list.SetStart();
		

		while (list.CurLevelExist() == true)
		{
			list.GetCurInf(CurTreeElem);
			while (CurTreeElem != nullptr)
			{
				if (CurTreeElem->Data == data)
				{
					return true;
				}
				else
				{
					CurTreeElem = CurTreeElem->Next;
				}
			}
			++list;
		}
		return false;
	}

//------------------------------------------------------------------------
//																Удаление
//------------------------------------------------------------------------

	bool DeleteElByKey(int id)
	{
		if (Root)
		{
			//	найти позицию заменяемого
			TreeElem *DelPos = Root, *DelParent = nullptr;
			TreeElem *ReplasedPos = nullptr, *ReplasedParent = nullptr;		//	просто расширил область их видимости
			list.SetStart();

			while (DelPos && DelPos->ID != id)												//	тут кто то ксть? пока тут не посто
			{
				++list;
				DelParent = DelPos;													//	pos - то самое место, parent - вышестоящий элемент.
				DelPos = DelPos->ID > id ? DelPos->Left : DelPos->Right;
			}
			if (DelPos == nullptr)
				return NOT_SUCCESS_OPER;

				//	сохранить позицию List, иначе если есть потомки мы укатимся ниже
			TreeElem *High_FirstElemOnLevel;
			list.GetCurInf(High_FirstElemOnLevel);
				//	Ох и сохранили))

//	---------------------------------------------------------------------------------------------------------------------------------------
		
			//	найти позицию заменяющего					
			//TreeElem *ReplasedPos = nullptr, *ReplasedParent = nullptr;

			if (DelPos->Left)
			{
				ReplasedParent = DelPos;
				ReplasedPos = DelPos->Left;
				++list;											//	типа надо, мы ж переходим на RemovedPos->Left

				while (ReplasedPos->Right != nullptr)
				{
					++list;
					ReplasedParent = ReplasedPos;
					ReplasedPos = ReplasedPos->Right;
				}
			}
			else if (DelPos->Right)
			{
				ReplasedParent = DelPos;
				ReplasedPos = DelPos->Right;
				++list;											//	типа надо, мы ж переходим на RemovedPos->Left

				while (ReplasedPos->Left != nullptr)
				{
					++list;
					ReplasedParent = ReplasedPos;
					ReplasedPos = ReplasedPos->Left;
				}				
			}

			//	
			TreeElem *Low_FirstElemOnLevel;
			list.GetCurInf(Low_FirstElemOnLevel);

//	---------------------------------------------------------------------------------------------------------------------------------------

/*
			//	1 3 7 9
			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			if (id == FirstElemOnRemovedPosLevel->ID)
				{
					if (DelPos->Next)
					{
						//	перезапись первого элемента на уровне
						DelPos->Next->Prev = nullptr;
						list.RewriteCurInf(DelPos->Next);
					}
					else if (Root->ID == id)
					{
						//	если элемент корневой
						Root = ReplasedPos;
						ReplasedPos->Prev = ReplasedPos->Next = nullptr;
						list.SetStart();
						list.RewriteCurInf(ReplasedPos);
					}
					else
					{
						//	элемент единственный на уровне и надо удалить элемент списка
						list.DeleteLastListElem();
					}
				}
				else
				{
					DelPos->Prev->Next = DelPos->Next;	//	исключения не будет т.к. наличие предыдущего проверили выше
					if (DelPos->Next)
						DelPos->Next->Prev = DelPos->Prev;	//	для 9: Null->Prev - исключение								
				}
			delete DelPos;
			return SUCCESS_OPER;

//	---------------------------------------------------------------------------------------------------------------------------------

			//	5
			if (ReplasedPos)
			{
				//	запомнил листья ReplasedPos, 
				TreeElem *RepPosLeftNode = ReplasedPos->Left, *RepPosRightNode = ReplasedPos->Right;
				//	привязал к ReplasedPos листья DelPos
				ReplasedPos->Left = DelPos->Left;
				ReplasedPos->Right = DelPos->Right;
				//	для RepPos (3)
				TreeElem *FirstElemOnReplasedLevel;
				list.GetCurInf(FirstElemOnReplasedLevel);
				//	переделать по умному
				ReplasedParent->Right = nullptr;

				LevelBinding(ReplasedPos, nullptr, FirstElemOnReplasedLevel, id);
				//	для DelPos (5)
				LevelBinding(DelPos, ReplasedPos, FirstElemOnRemovedPosLevel, id);
			}
			delete DelPos;
			return SUCCESS_OPER;

//	---------------------------------------------------------------------------------------------------------------------------------

			//	1 3 7 9 with LevelBinding()
			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			LevelBinding(DelPos, ReplasedPos, FirstElemOnRemovedPosLevel, id);

//	---------------------------------------------------------------------------------------------------------------------------------

			//	2 
			RemFromLevel(DelPos, High_FirstElemOnLevel);	//	Remove 2
			RemFromLevel(ReplasedPos, Low_FirstElemOnLevel);	//	Remove 1

			InsertIntoLevel(ReplasedPos, High_FirstElemOnLevel);

			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			ReplasedPos->Right = DelPos->Right;		//	для 2
			ReplasedPos->Left = DelPos->Left;		//	для 6
			

			//	1 3 7 9
			RemFromLevel(DelPos, High_FirstElemOnLevel);	
			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;

			//	5	доработать
			RemFromLevel(DelPos, High_FirstElemOnLevel);	//	Remove 6
			RemFromLevel(ReplasedPos, Low_FirstElemOnLevel);	//	Remove 7

			InsertIntoLevel(ReplasedPos, High_FirstElemOnLevel);

			//DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;

			if (DelPos->ID == Root->ID)
			{
			ReplasedPos->Left = DelPos->Left;
			ReplasedPos->Right = DelPos->Right;
			Root = ReplasedPos;
			}

//	------------------------------------------------------------------------------------------------------------------------------------

			if (DelPos->ID != Root->ID)
			{
			if (ReplasedPos)
			{
			//	общий случай
			RemFromLevel(DelPos, High_FirstElemOnLevel);	//	Remove 2
			RemFromLevel(ReplasedPos, Low_FirstElemOnLevel);	//	Remove 1

			InsertIntoLevel(ReplasedPos, High_FirstElemOnLevel);

			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			if(ReplasedPos != DelPos->Right)
			ReplasedPos->Right = DelPos->Right;		//	для 2
			if(ReplasedPos != DelPos->Left)
			ReplasedPos->Left = DelPos->Left;		//	для 6

			//	при удалении 8, 6 продолжает иметь листик 7
			}
			else
			{
			//	лист
			RemFromLevel(DelPos, High_FirstElemOnLevel);
			DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			}
			}
			else
			{
			//	удаляем корень
			}
*/
		
			if (DelPos->ID != Root->ID)
			{
				RemFromLevel(DelPos, High_FirstElemOnLevel);
				if (ReplasedPos)
				{						
					RemFromLevel(ReplasedPos, Low_FirstElemOnLevel);	
					InsertIntoLevel(ReplasedPos, High_FirstElemOnLevel);

					if(ReplasedPos != DelPos->Right)
						ReplasedPos->Right = DelPos->Right;		
					if(ReplasedPos != DelPos->Left)
						ReplasedPos->Left = DelPos->Left;		
				}
				DelParent->ID > id ? DelParent->Left = ReplasedPos : DelParent->Right = ReplasedPos;
			}
			else
			{
				//	удаляем корень

			}
			
			delete DelPos;
			return SUCCESS_OPER;			
		}		
		return NOT_SUCCESS_OPER;
	}

	bool DeleteAllElem()
	{
		DeleteAllElemRec(Root);
	    Root = nullptr;
		list.DeleteAllListElem();	
	}

//------------------------------------------------------------------------
//											 Проверка существования дерева
//------------------------------------------------------------------------
bool operator!()
{
	return (Root != nullptr);
}
/*
//void Action(SomeClass<int, data> *Value)
void Action(BinaryTree *Value)
{
ActionRec(Root, Value);

}
*/	


private:

	TreeElem* FindPos(int id, TreeElem *& Parent)
	{
		TreeElem *Pos = Root;
		Parent = nullptr;
		list.SetStart();

		while (Pos != nullptr)												//	тут кто то ксть? пока тут не посто
		{
			if (Pos->ID == id)												
				return Pos;
			++list;
			Parent = Pos;													//	pos - то самое место, parent - вышестоящий элемент.
			Pos = Pos->ID > id ? Pos->Left : Pos->Right;
		}
		return Pos;
	}

	//	поиск самого левого

	TreeElem * FindLeftPos(int id, TreeElem *& LeftParent, TreeElem *& DeletingElemPos)
	{
		TreeElem *Pos = DeletingElemPos;
		LeftParent = nullptr;
		//	list.SetStart();	//	тут нужно, чтобы List был на уровне с DeletingElemPos, проверь в Debug

		while (Pos->Left != nullptr)
		{			
			LeftParent = Pos;
			Pos = Pos->Left;
		}
		return Pos;
	}

	bool FindElByDataRec(data data, TreeElem* Cur)			//	поиск по инфе в глубину.
	{	
		if (Cur)
		{
			if (Cur->Data == data)
				return true;
			if (FindElByDataRec(data, Cur->Left) == false)
				return FindElByDataRec(data, Cur->Right);
			return true;
		}
		return false;
	}

	void DeleteAllElemRec(TreeElem *Cur)
	{
		if (Cur)
		{
			DeleteAllElemRec(Cur->Left);
			DeleteAllElemRec(Cur->Right);
			delete Cur;
		}
	}
/*
//void ActionRec(TreeElem *Cur, SomeClass<int, data> *Value)
void ActionRec(TreeElem *Cur, BinaryTree *Value)
{
if (Cur)
{
ActionRec(Cur->Left,Value);
(*Value)(Cur);
ActionRec(Cur->Right,Value);

}
}
*/


	bool delleteNode(TreeElem *fPos, TreeElem *Par)
	{
		if ((fPos->Left == nullptr) && (fPos->Right == nullptr))	//	значит у нас лист
		{
			(fPos->ID < Par->ID) ? Par->Left = nullptr : Par->Right = nullptr;	//	обнулили ссылку на элемент у родителя
			if (fPos->Prev == nullptr)
			{
				if (fPos->Next == nullptr)
				{
					//	1
					//delete fPos;
					list.DeleteLastListElem();
				}
				else
				{
					//	2
					fPos->Next->Prev = nullptr;
					list.RewriteCurInf(fPos->Next);
					//delete fPos;
				}
			}
			else
			{
				if (fPos->Next == nullptr)
				{
					//	4
					fPos->Prev->Next = nullptr;
					//delete fPos;
				}
				else
				{
					//	3
					fPos->Prev->Next = fPos->Next;
					fPos->Next->Prev = fPos->Prev;
					
				}
			}
			delete fPos;
			return SUCCESS_OPER;
		}
	}

	//	работает со списками при удалении
	bool LevelBinding(TreeElem *DelPos, TreeElem *RepPos, TreeElem *FirstElemOnRemovedPosLevel, int id)
	{
		if (id == FirstElemOnRemovedPosLevel->ID)
		{
			if (DelPos->Next)
			{
				//	перезапись первого элемента на уровне
				DelPos->Next->Prev = nullptr;
				list.RewriteCurInf(DelPos->Next);
			}
			else if (Root->ID == id)
			{
				//	если элемент корневой
				Root = RepPos;
				RepPos->Prev = RepPos->Next = nullptr;
				list.SetStart();
				list.RewriteCurInf(RepPos);
			}
			else
			{
				//	элемент единственный на уровне и надо удалить элемент списка
				list.DeleteLastListElem();
			}
		}
		else
		{
			DelPos->Prev->Next = DelPos->Next;	//	исключения не будет т.к. наличие предыдущего проверили выше
			if (DelPos->Next)
				DelPos->Next->Prev = DelPos->Prev;	//	для 9: Null->Prev - исключение								
		}
		return SUCCESS_OPER;
	}
	
	bool RemFromLevel(TreeElem *& DelPos, TreeElem *& FirstElemOnRemovedPosLevel)
	{
		//	временно
		//DelParent->ID > id ? DelParent->Left = RepPos : DelParent->Right = RepPos;

		if (DelPos->ID == FirstElemOnRemovedPosLevel->ID)
		{
			if (DelPos->Next)
			{
				//	перезапись первого элемента на уровне
				DelPos->Next->Prev = nullptr;

				TreeElem *a;
				list.SetStart();
				list.GetCurInf(a);
				while (a->ID != FirstElemOnRemovedPosLevel->ID)
				{
					++list;
					list.GetCurInf(a);
				}

				list.RewriteCurInf(DelPos->Next);

				//	обновляем значение после удаления первого на уровне
				FirstElemOnRemovedPosLevel = DelPos->Next;
			}
			else
			{
				//	элемент единственный на уровне и надо удалить элемент списка
				list.DeleteLastListElem();
			}
		}
		else
		{
			DelPos->Prev->Next = DelPos->Next;	//	исключения не будет т.к. наличие предыдущего проверили выше
			if (DelPos->Next)
				DelPos->Next->Prev = DelPos->Prev;	//	для 9: Null->Prev - исключение								
		}
		return SUCCESS_OPER;
	}

	bool InsertIntoLevel(TreeElem *& InsElem, TreeElem *& FirstElemOnRemovedPosLevel)
	{
		//	временно
		//InsParent->ID > id ? InsParent->Left = InsElem : InsParent->Right = InsElem;
		//	я не могу прилепить к InsElem листья DelPos без передачи его в метод.
		//	Возможно все действия Parent - Node следует делать в основном методе.

		if (InsElem->ID > FirstElemOnRemovedPosLevel->ID)
		{
			//	не первый, ищем позицию	
			while (FirstElemOnRemovedPosLevel->Next && FirstElemOnRemovedPosLevel->Next->ID < InsElem->ID)
					FirstElemOnRemovedPosLevel = FirstElemOnRemovedPosLevel->Next;
				
			InsElem->Prev = FirstElemOnRemovedPosLevel;
			InsElem->Next = FirstElemOnRemovedPosLevel->Next;

			if (FirstElemOnRemovedPosLevel->Next)
				FirstElemOnRemovedPosLevel->Next->Prev = InsElem;
			FirstElemOnRemovedPosLevel->Next = InsElem;		
		}
		else
		{
			//	первый			
			InsElem->Next = FirstElemOnRemovedPosLevel;
			InsElem->Prev = nullptr;

			FirstElemOnRemovedPosLevel->Prev = InsElem;

			TreeElem *a;
			list.SetStart();
			list.GetCurInf(a);
			while (a->ID != FirstElemOnRemovedPosLevel->ID)
			{
				++list;
				list.GetCurInf(a);
			}
			list.RewriteCurInf(InsElem);

			//	обновляем значение после удаления первого на уровне
			FirstElemOnRemovedPosLevel = InsElem->Next;
		}
		return SUCCESS_OPER;
	}
};