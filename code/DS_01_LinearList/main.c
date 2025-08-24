#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define EXAMPLE 3

#if EXAMPLE <= 2 //例题1、2
typedef  char ElemType;
#elif EXAMPLE == 3
typedef int ElemType;
#endif

typedef struct Node{
	ElemType data;
	struct Node* next; //定义时为struct node
}Node;

//初始化一个头节点，next为空
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

//初始化一个节点，带值
Node* initNodeWithElem(ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = NULL;
	return p;
}

//以头插法插入节点,带值
Node* insertHeaderWithElem(Node* header, ElemType e)
{
	Node* p = header;
	Node* m = (Node*)malloc(sizeof(Node));
	m->data = e;
	m->next = p->next;
	p->next = m;
	return p;
}

//以尾插法插入节点,带值
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

//插入任意位置,带值
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

//输出链表内所有值
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

//删除指定位置的节点
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

//释放链表
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

//例题1: 查找倒数第x个节点数据
Node* findNode(Node * header, int pos)
{
	if (header == NULL) return NULL;
	
	//使用快慢指针增加效率
	Node* fast = header->next;

	int i = 0;
	//快指针先向前移动k个节点
	for (i = 0; i < pos - 1; i++)
	{
		if (fast->next == NULL)
		{
			printf("error: length of list less than %d.\n", pos);
			return NULL;
		}
		fast = fast->next;
	}

	//初始化慢节点，并同步修改
	Node* slow = header->next;
	while (fast->next != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	printf("success: the data is %c.\n", slow->data);
	return slow;
}


//例题2: 合并单词链表，例如being 和ending 
int vergeListWithChar(Node* list1, Node* list2)
{
	//输入链表为空
	if (list1 == NULL || list2 == NULL)
	{
		return 0;
	}

	int list1_len = 0;
	int list2_len = 0;
	
	//计算链表1的长度
	Node* fast = list1;
	while (fast != NULL)
	{
		fast = fast->next;
		list1_len++;
	}

	//计算链表2的长度
	fast = list2;
	while (fast != NULL)
	{
		fast = fast->next;
		list2_len++;
	}

	//计算链表长度，并设定快慢指针值
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

	//移动快指针
	for (int i = 0; i < gap; i++)
	{
		fast = fast->next;
	}

	//遍历找到链表中的相同数据
	Node* p = slow;
	while (fast->data != slow->data)
	{
		p = slow;//保存相同数值的上一节点
		fast = fast->next;
		slow = slow->next;
	}
	//连接向相同值
	p->next = fast; 
	
	//释放剩余节点
	while (slow != NULL)
	{
		p = slow;
		slow = slow->next;
		free(p);
	}

	return 1;
}

//例题3：删除链表中数值绝对值相同的节点,已知链表长度n
int deleteRepeatNode(Node* header, int len)
{
	Node* p = header;

	if (p == NULL) return 0;

	//建立一个与数组长度相符的空间作为判断数组
	int* judgeArray = (int*)malloc(sizeof(int) * (len + 1));
	for (int i = 0; i < len + 1; i++)
	{
		judgeArray[i] = 0;
	}

	//查找值
	p = header->next;
	Node* last_node = NULL; // 保存上一节点

	while (p != NULL)
	{
		//绝对值首次出现，则标记
		if (judgeArray[abs(p->data)] == 0)
		{
			judgeArray[abs(p->data)] = 1;
			last_node = p; //保存上一个节点
			p = p->next;
		}
		else //出现重复节点，则释放该节点
		{
			last_node->next = p->next;  //将重复值的前移节点链向重复节点的后一个节点
			Node* tmp = p;		// 待释放的重复节点
			p = p->next;		//更新p节点，不更新上一个节点q
			free(tmp); //释放当前节点
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
	//例题1--寻找倒数第n个字符
	int pos = 10;
	p = findNode(header,pos);		

	pos = 3;
	p = findNode(header,pos);
#endif

#if EXAMPLE == 2
	//例题2--合并相同后缀的单词
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
	//例题3：删除相同节点
	deleteRepeatNode(header,5);
	printfList(header);
#endif


	deleteList(header);

	return 0;
}