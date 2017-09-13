#include"test.h"

int test_InitHeadNode()
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	InitHeadNode(l_list);
	FAIL_TEST(l_list->NodeCount, 0);
	FAIL_TEST(l_list->HeadNode, NULL);
	free(l_list);
	return 0;
}

int test_InsertElement(CopyFunction l_CopyFunction, FreeFunction l_FreeFunction)
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	test_A* l_test_A1 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A2 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A3 = (test_A*)malloc(sizeof(test_A));
	void* lElement1 = malloc(sizeof(test_B));
	void* lElement2 = malloc(sizeof(test_B));
	void* lElement3 = malloc(sizeof(test_B));
	((test_B*)lElement1)->test_struct = l_test_A1;
	((test_B*)lElement2)->test_struct = l_test_A2;
	((test_B*)lElement3)->test_struct = l_test_A3;
	list_node *test1, *test2, *test3;
	
	InitHeadNode(l_list);
	test1 = InsertElement(l_list, NULL, lElement1, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	FAIL_TEST(l_list->HeadNode, &test1->list);
	FAIL_TEST(test1->list.next, &test1->list);
	FAIL_TEST(test1->list.prev, &test1->list);
	test2 = InsertElement(l_list, test1, lElement2, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	test3 = InsertElement(l_list, test2, lElement3, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	FAIL_TEST(test3->list.next, &test1->list);
	
	l_FreeFunction(lElement1);
	l_FreeFunction(lElement2);
	l_FreeFunction(lElement3);
	free(l_list);
	return 0;
}

int test_DeleteNode(CopyFunction l_CopyFunction, FreeFunction l_FreeFunction)
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	test_A* l_test_A1 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A2 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A3 = (test_A*)malloc(sizeof(test_A));
	void* lElement1 = malloc(sizeof(test_B));
	void* lElement2 = malloc(sizeof(test_B));
	void* lElement3 = malloc(sizeof(test_B));
	((test_B*)lElement1)->test_struct = l_test_A1;
	((test_B*)lElement2)->test_struct = l_test_A2;
	((test_B*)lElement3)->test_struct = l_test_A3;
	list_node *test1, *test2, *test3;
	
	InitHeadNode(l_list);
	test1 = InsertElement(l_list, NULL, lElement1, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	DeleteNode(test2, l_list);
	test2 = InsertElement(l_list, test1, lElement2, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	test3 = InsertElement(l_list, test2, lElement3, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	DeleteNode(test2, l_list);
	FAIL_TEST(test1->list.next, test3->list.prev);
	FAIL_TEST(test3->list.prev, test1->list.next);
	
	l_FreeFunction(lElement1);
	l_FreeFunction(lElement2);
	l_FreeFunction(lElement3);
	free(l_list);
	return 0;
}

int test_GetNodeCount(CopyFunction l_CopyFunction, FreeFunction l_FreeFunction)
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	list_node* test[10];
	test_A* l_test_A[10];
	void* lElement[10];
	int i = 0;
	for(i = 0;i < 10;i++)
	{
		l_test_A[i] = (test_A*)malloc(sizeof(test_A));
		lElement[i] = malloc(sizeof(test_B));
		((test_B*)lElement[i])->test_struct = l_test_A[i];
	}
	
	InitHeadNode(l_list);
	test[0] = InsertElement(l_list, NULL, lElement[0], sizeof(test_B), l_CopyFunction, l_FreeFunction);
	FAIL_TEST(l_list->NodeCount, 1);
	
	for(i = 0;i < 9;i++)
	{
		test[i+1] = InsertElement(l_list, test[i], lElement[i+1], sizeof(test_B), l_CopyFunction, l_FreeFunction);
		FAIL_TEST(l_list->NodeCount, i+2);
	} 
	
	for(i = 0;i < 10;i++)
	{
		l_FreeFunction(lElement[i]);
	}
	free(l_list);
	return 0;
}

int test_TraverseList(FunctionPoint l_UserFuncPoint, CopyFunction l_CopyFunction, FreeFunction l_FreeFunction)
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	list_node* test[10];
	test_A* l_test_A[10];
	test_B* lElement[10];
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		l_test_A[i] = (test_A*)malloc(sizeof(test_A));
		lElement[i] = (test_B*)malloc(sizeof(test_B));
		lElement[i]->test_struct = l_test_A[i];
		lElement[i]->number = i;
	}
	
	InitHeadNode(l_list);
	test[0] = InsertElement(l_list, NULL, lElement[0], sizeof(test_B), l_CopyFunction, l_FreeFunction);
	
	for(i = 0; i < 9; i++)
	{
		test[i+1] = InsertElement(l_list, test[i], lElement[i+1], sizeof(test_B), l_CopyFunction, l_FreeFunction);
	}
	TraverseList(l_list, l_UserFuncPoint);
	
	for(i = 0; i < 10; i++)
	{
		l_FreeFunction(lElement[i]);
	}
	free(l_list);
	return 0;
}

int UserFunction(SL_List* l_list, list_node* ThisNode)
{
	list_node* UserNode = (list_node*)malloc(sizeof(list_node));
	int ConductFlag = 0;
	static int count = 1;
	
	#if _DEBUG
	ConductFlag = FLAG_CONTINUE_TRAVERSE;
	FAIL_TEST(((test_B*)(ThisNode->data))->number, count++);
	
/*	#else
	char get_ch = 0;
	getchar();
	printf("��ѡ����������еĲ���(a:�ڴ˲���ڵ�;b:ɾ���˽ڵ�;c:��õ�ǰ����Ľڵ���;d:������������;e:�˳��������)\n");
	printf("(��ע���Сд!)\n");
	get_ch = getchar();
	switch(get_ch)
	{
		case 'a':
			InsertNode(ThisNode, UserNode, l_list);
			ConductFlag = FLAG_CONTINUE_TRAVERSE;
			break;
		case 'b':
			DeleteNode(ThisNode,l_list);
			ConductFlag = FLAG_CONTINUE_TRAVERSE;
			break;
		case 'c':
			GetNodeCount(l_list);
			ConductFlag = FLAG_CONTINUE_TRAVERSE;
			break;
		case 'd':
			ConductFlag = FLAG_CONTINUE_TRAVERSE;
			break; 
		case 'e':ConductFlag = 0;
	}*/
	#endif
	return ConductFlag;
}

int test_ClearList(CopyFunction l_CopyFunction, FreeFunction l_FreeFunction)
{
	SL_List* l_list = (SL_List*)malloc(sizeof(SL_List));
	test_A* l_test_A1 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A2 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A3 = (test_A*)malloc(sizeof(test_A));
	test_A* l_test_A4 = (test_A*)malloc(sizeof(test_A));
	void* lElement1 = malloc(sizeof(test_B));
	void* lElement2 = malloc(sizeof(test_B));
	void* lElement3 = malloc(sizeof(test_B));
	void* lElement4 = malloc(sizeof(test_B));
	((test_B*)lElement1)->test_struct = l_test_A1;
	((test_B*)lElement2)->test_struct = l_test_A2;
	((test_B*)lElement3)->test_struct = l_test_A3;
	((test_B*)lElement4)->test_struct = l_test_A4;
	list_node *test1, *test2, *test3, *test4;
	
	InitHeadNode(l_list);
	ClearList(l_list);
	FAIL_TEST(l_list->HeadNode, NULL);
	FAIL_TEST(l_list->NodeCount, 0);
	
	test4 = InsertElement(l_list, NULL, lElement4, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	ClearList(l_list);
	FAIL_TEST(l_list->HeadNode, NULL);
	FAIL_TEST(l_list->NodeCount, 0);
	
	test1 = InsertElement(l_list, NULL, lElement1, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	test2 = InsertElement(l_list, test1, lElement2, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	test3 = InsertElement(l_list, test2, lElement3, sizeof(test_B), l_CopyFunction, l_FreeFunction);
	ClearList(l_list);
	FAIL_TEST(l_list->HeadNode, NULL);
	FAIL_TEST(l_list->NodeCount, 0);
	
	l_FreeFunction(lElement1);
	l_FreeFunction(lElement2);
	l_FreeFunction(lElement3);
	l_FreeFunction(lElement4);
	free(l_list);
	return 0;
}

void UserCopy(void* Element, void* p)
{
	test_A* l_test_A = (test_A*)malloc(sizeof(test_A));
	((test_B*)p)->test_struct = l_test_A;
	((test_B*)p)->test_struct->number = ((test_B*)Element)->test_struct->number;
	((test_B*)p)->number = ((test_B*)Element)->number;
	//memcpy(p, Element, sizeof(_msize(Element)));
}

void UserFree(void* Element)
{
	free(((test_B*)Element)->test_struct);
}