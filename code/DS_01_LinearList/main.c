#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define EXAMPLE 3

#if EXAMPLE <= 2 //����1��2
typedef  char ElemType;
#elif EXAMPLE == 3
typedef int ElemType;
#endif

typedef struct Node{
	ElemType data;
	struct Node* next; //����ʱΪstruct node
}Node;

//��ʼ��һ��ͷ�ڵ㣬nextΪ��
Node* initNode(void)
{
	Node* p = (Node*)malloc(sizeof(Node));
#if EXAMPLE <= 2
	p->data = '0';
#elif EXAMPLE == 3;
	p->data = 0;
#endif
	p->next = NULL;
	return p;
}

//��ʼ��һ���ڵ㣬��ֵ
Node* initNodeWithElem(ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = NULL;
	return p;
}

//��ͷ�巨����ڵ�,��ֵ
Node* insertHeaderWithElem(Node* header, ElemType e)
{
	Node* p = header;
	Node* m = (Node*)malloc(sizeof(Node));
	m->data = e;
	m->next = p->next;
	p->next = m;
	return p;
}

//��β�巨����ڵ�,��ֵ
Node* insertTailWithElem(Node* header, ElemType e)
{
	Node* p = header;
	while (p->next != NULL)
	{
		p = p->next;
	}

	Node* m = (Node*)malloc(sizeof(Node));
	m->data = e;
	m->next = NULL;
	p->next = m;
	return m;
}

//��������λ��,��ֵ
int insertNodeWithElem(Node* header, int pos, ElemType e)
{
	Node* p = header;
	
	int i = 0;
	for (i = 0; i < pos - 1; i++)
	{
		if (p->next == NULL)
		{
			return 0;
		}
		p = p->next;
	}

	Node* m = (Node*)malloc(sizeof(Node));
	m->data = e;
	m->next = p->next;
	p->next = m;
	return 1;
}

//�������������ֵ
void printfList(Node* L)
{
	Node* p = L;
	while (p->next != NULL)
	{
		p = p->next;
#if EXAMPLE <= 2
		printf("%c", p->data);
#elif EXAMPLE == 3
		printf("%d ", p->data);
#endif
	}
	printf("\n");
}

//ɾ��ָ��λ�õĽڵ�
Node* deleteNode(Node* L, int pos)
{
	Node* p = L;
	int i = 0;
	for (i = 0; i < pos - 1; i++)
	{
		if (p->next == NULL)
		{
			return NULL;
		}
		p = p->next;
	}

	Node* q = p->next;
	p->next = q->next;
	free(q);
	return L;
}

//�ͷ�����
Node* deleteList(Node* L)
{
	Node* p = L;

	while (p->next != NULL)
	{
		Node* m = p->next;
		free(p);
		p = m;
	}
	return p;
}

//����1: ���ҵ�����x���ڵ�����
Node* findNode(Node * header, int pos)
{
	if (header == NULL) return NULL;
	
	//ʹ�ÿ���ָ������Ч��
	Node* fast = header->next;

	int i = 0;
	//��ָ������ǰ�ƶ�k���ڵ�
	for (i = 0; i < pos - 1; i++)
	{
		if (fast->next == NULL)
		{
			printf("error: length of list less than %d.\n", pos);
			return NULL;
		}
		fast = fast->next;
	}

	//��ʼ�����ڵ㣬��ͬ���޸�
	Node* slow = header->next;
	while (fast->next != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	printf("success: the data is %c.\n", slow->data);
	return slow;
}


//����2: �ϲ�������������being ��ending 
int vergeListWithChar(Node* list1, Node* list2)
{
	//��������Ϊ��
	if (list1 == NULL || list2 == NULL)
	{
		return 0;
	}

	int list1_len = 0;
	int list2_len = 0;
	
	//��������1�ĳ���
	Node* fast = list1;
	while (fast != NULL)
	{
		fast = fast->next;
		list1_len++;
	}

	//��������2�ĳ���
	fast = list2;
	while (fast != NULL)
	{
		fast = fast->next;
		list2_len++;
	}

	//���������ȣ����趨����ָ��ֵ
	Node* slow = fast;
	int gap = 0;
	if (list1_len > list2_len)
	{
		fast = list1;
		slow = list2;
		gap = list1_len - list2_len;
	}
	else
	{
		fast = list2;
		slow = list1;
		gap = list2_len - list1_len;
	}

	//�ƶ���ָ��
	for (int i = 0; i < gap; i++)
	{
		fast = fast->next;
	}

	//�����ҵ������е���ͬ����
	Node* p = slow;
	while (fast->data != slow->data)
	{
		p = slow;//������ͬ��ֵ����һ�ڵ�
		fast = fast->next;
		slow = slow->next;
	}
	//��������ֵͬ
	p->next = fast; 
	
	//�ͷ�ʣ��ڵ�
	while (slow != NULL)
	{
		p = slow;
		slow = slow->next;
		free(p);
	}

	return 1;
}

//����3��ɾ����������ֵ����ֵ��ͬ�Ľڵ�,��֪������n
int deleteRepeatNode(Node* header, int len)
{
	Node* p = header;

	if (p == NULL) return 0;

	//����һ�������鳤������Ŀռ���Ϊ�ж�����
	int* judgeArray = (int*)malloc(sizeof(int) * (len + 1));
	for (int i = 0; i < len + 1; i++)
	{
		judgeArray[i] = 0;
	}

	//����ֵ
	p = header->next;
	Node* last_node = NULL; // ������һ�ڵ�

	while (p != NULL)
	{
		//����ֵ�״γ��֣�����
		if (judgeArray[abs(p->data)] == 0)
		{
			judgeArray[abs(p->data)] = 1;
			last_node = p; //������һ���ڵ�
			p = p->next;
		}
		else //�����ظ��ڵ㣬���ͷŸýڵ�
		{
			last_node->next = p->next;  //���ظ�ֵ��ǰ�ƽڵ������ظ��ڵ�ĺ�һ���ڵ�
			Node* tmp = p;		// ���ͷŵ��ظ��ڵ�
			p = p->next;		//����p�ڵ㣬��������һ���ڵ�q
			free(tmp); //�ͷŵ�ǰ�ڵ�
		}
	}
	free(judgeArray);
	return 1;
}

int main(void)
{
	Node* header = initNode();

#if EXAMPLE <= 2
	insertTailWithElem(header, 'n');
	insertTailWithElem(header, 'd');
	insertTailWithElem(header, 'i');
	insertTailWithElem(header, 'n');
	insertTailWithElem(header, 'g');
	insertHeaderWithElem(header, 'e');
#elif EXAMPLE == 3
	insertTailWithElem(header, 1);
	insertTailWithElem(header, -2);
	insertTailWithElem(header, 2);
	insertTailWithElem(header, 5);
	insertTailWithElem(header, 4);
#endif

	printfList(header);
	deleteNode(header, 4);
	insertNodeWithElem(header, 4, 2);
	printfList(header);

#if EXAMPLE == 1
	Node* p = NULL;
	//����1--Ѱ�ҵ�����n���ַ�
	int pos = 10;
	p = findNode(header,pos);		

	pos = 3;
	p = findNode(header,pos);
#endif

#if EXAMPLE == 2
	//����2--�ϲ���ͬ��׺�ĵ���
	Node* string1 = initNode();
	insertTailWithElem(string1, 'b');
	insertTailWithElem(string1, 'e');
	insertTailWithElem(string1, 'i');
	insertTailWithElem(string1, 'n');
	insertTailWithElem(string1, 'g');
	printfList(header);
	printfList(string1);
	
	vergeListWithChar(header, string1);
	printfList(header);
	printfList(string1);
#endif

#if EXAMPLE == 3
	//����3��ɾ����ͬ�ڵ�
	deleteRepeatNode(header,5);
	printfList(header);
#endif


	deleteList(header);

	return 0;
}