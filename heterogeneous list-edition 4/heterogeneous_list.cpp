#include<stdio.h>
#include"heterogeneous_list.h"

int InitHeadNode(SL_List* l_list)
{
	l_list->HeadNode = NULL;
	l_list->NodeCount = 0;
	return 0;
}

int InsertNode(SL_Node* LastNode, SL_Node* ThisNode, SL_List* l_list, FunctionPoint l_UserFuncPoint)
{
	HelpInsert(LastNode, ThisNode, l_list);
	ThisNode->m_UserFuncPoint = l_UserFuncPoint;
	return 0;
}

int DeleteNode(SL_Node* ThisNode, SL_List* l_list)
{
	if(l_list->NodeCount == 1)
	{
		if(l_list->HeadNode == ThisNode)
		{
			ThisNode->m_UserFuncPoint(l_list, ThisNode);
			l_list->HeadNode = NULL;
			l_list->NodeCount--;
		}
		else
		{
			#ifdef _DEBUG
			printf("����ڵ����!\n");
			return -1;
			#else
			return -1;
			#endif
		}
	}
	else
	{
		SL_Node* SL_temppoint = ThisNode;
		SL_temppoint->prev->next = SL_temppoint->next;
		SL_temppoint->next->prev = SL_temppoint->prev;
		SL_temppoint->prev = NULL;
		SL_temppoint->next = NULL;
		ThisNode->m_UserFuncPoint(l_list, ThisNode);
		l_list->NodeCount--;
	}
	return 0;
}

int GetNodeCount(SL_List* l_list)
{
	return l_list->NodeCount;
}

int TraverseList(SL_List* l_list, FunctionPoint l_UserFuncPoint)
{
	int i = 0; 
	if(l_list->NodeCount != 0)
	{
		int TraverseFlag = FLAG_CONTINUE_TRAVERSE;
		SL_Node* SL_temp = l_list->HeadNode->next;
		
		for(i = 0; i < l_list->NodeCount; i++)
		{
			TraverseFlag = l_UserFuncPoint(l_list, SL_temp->prev);
			if(TraverseFlag == FLAG_CONTINUE_TRAVERSE)
			{
				SL_temp = SL_temp->next;
			}
			else
			{
				break;
			}
		}
		
	}
	return 0;
}

int ClearList(SL_List* l_list)
{
	int i = 0;
	char ch = 0;
	if(l_list->HeadNode == NULL)
	{
		#ifdef _DEBUG
		printf("����Ϊ��!\n");
		return -1;
		#else
		return -1;
		#endif
	}
	else
	{
		SL_Node* TempNode1 = l_list->HeadNode;
		SL_Node* TempNode2 = l_list->HeadNode;
		for(i = 0; i < l_list->NodeCount; i++)
		{
			TempNode1 = TempNode2;
			TempNode2 = TempNode2->next;
			TempNode1->m_UserFuncPoint(l_list, TempNode1);
		}
	}
	l_list->HeadNode = NULL;
	l_list->NodeCount = 0;
	return 0;
}

SL_Node* InsertElement(SL_Node* LastNode, void* pElement, SL_List* l_list)
{
	SL_Node* TempNode = (SL_Node*)malloc(sizeof(SL_Node));
	TempNode->m_UserFuncPoint = HelpFree;
	HelpInsert(LastNode, TempNode, l_list);
	TempNode->data = pElement;
	return TempNode;
}

int HelpInsert(SL_Node* LastNode, SL_Node* ThisNode, SL_List* l_list)
{
	if(l_list->NodeCount == 0)
	{
		l_list->HeadNode = ThisNode;
		ThisNode->next = ThisNode;
		ThisNode->prev = ThisNode;
		l_list->NodeCount++;
	}
	else
	{
		ThisNode->next = LastNode->next;
		ThisNode->prev = LastNode;
		LastNode->next = ThisNode;
		ThisNode->next->prev = ThisNode;
		l_list->NodeCount++;
	}
	return 0;
}

int HelpFree(SL_List* l_list, SL_Node* ThisNode)
{
	free(ThisNode);
	return 0;
}