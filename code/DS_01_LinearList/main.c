#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define EXAMPLE 8

#if EXAMPLE <= 2		//例题1、2
typedef  char ElemType;
#elif EXAMPLE >=3 && EXAMPLE <= 7	//例题3
typedef int ElemType;
#elif EXAMPLE >= 8	//双向链表
typedef int ElemType;
#endif

typedef struct Node{
	ElemType data;

#if EXAMPLE >= 8
	struct Node* prev; //上一节点
#endif 

	struct Node* next; //定义时为struct node
}Node;


//初始化一个头节点，next为空
Node* initNode(void)
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		return NULL;
	}
#if EXAMPLE <= 2
	p->data = '0';
#elif EXAMPLE >= 3;
	p->data = 0;
#endif

#if EXAMPLE >=8
	p->prev = NULL;  //初始话节点时首个节点的上下均为空
#endif

	p->next = NULL;
	return p;
}

//初始化一个节点，带值
Node* initNodeWithElem(ElemType e)
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		return NULL;
	}

#if EXAMPLE >=8
	p->prev = NULL;
#endif /* end EXAMPLE */
	
	p->data = e;
	p->next = NULL;
	return p;
}

//以头插法插入节点,带值
Node* insertHeaderWithElem(Node* header, ElemType e)
{
	Node* p = header;
	Node* m = (Node*)malloc(sizeof(Node));
	if (m == NULL)
	{
		return NULL;
	}
	m->data = e;

#if EXAMPLE >= 8
	/* 链接prev节点 */
	if (p->next != NULL)
	{
		p->next->prev = m;
	}
	m->prev = header;
#endif

	m->next = p->next;
	p->next = m;
	return p;
}
 
//以尾插法插入节点,带值
Node* insertTailWithElem(Node* header, ElemType e)
{
	Node* p = header;
	/* 找到尾节点 */
	while (p->next != NULL)
	{
		p = p->next;
	}

	Node* m = (Node*)malloc(sizeof(Node));
	if (m == NULL)
	{
		return NULL;
	}

#if EXAMPLE >= 8
	m->prev = p;
#endif

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
	if (m == NULL)
	{
		return NULL;
	}

#if EXAMPLE >=8
	if (p->next != NULL)
	{
		p->next->prev = m;
	}
	m->prev = p;
#endif

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
#elif EXAMPLE >=3
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
#if EXAMPLE >= 8 
	q->next->prev = p; /* 将下一节点的prev链接至前一节点 */
#endif
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

//释放循环链表
Node* cutCycleList(Node* cycleStartNode)
{
	Node* p = cycleStartNode;
	while (p->next != cycleStartNode)
	{
		p = p->next;
	}
	p->next = NULL;
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

//例题4：反转链表顺序
// @param: src - 输入初始链表
// @return: 成功返回0，异常返回其他值
int reverseList(Node* src)
{
	//若链表节点数小于2(不含头节点)，则退出
	if (src == NULL || src->next == NULL || src->next->next == NULL)
	{
		return 1;
	}

	Node* first = NULL;
	Node* second = src->next;
	Node* third = src->next->next;

	//third为NULL时，second指向最后一个节点
	while (third != NULL)
	{
		second->next = first;
		first = second;
		second = third;
		third = third->next;
	}

	//连接最后一个节点
	second->next = first;

	//更新头节点
	src->next = second;
	return 0;
}

//例题5：删除链表中间节点
// @param: src - 输入初始链表
// @return: 成功返回0，异常返回其他值
int deleteMiddleNode(Node* src)
{
	if (src == NULL || src->next == NULL)
	{
		return 1;
	}

	//设置快慢指针初始值
	Node* slow = src;
	Node* fast = src->next;

	//快指针移动两个节点，直到其或者其下一个节点为NULL
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	Node* del = slow->next;
	slow->next = slow->next->next;
	free(del);
	return 0;
}

//例题6:重排链表节点交叉相连
// @param: src - 输入初始链表
// @return: 成功返回0，异常返回其他值
int reOrderList(Node* src)
{
	Node* p = src;

	if (p == NULL || p->next == NULL)
	{
		return 1;
	}

	//初始化快慢指针，寻找中间节点
	Node* slow = p;
	Node* fast = p->next;

	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	//断开尾部链表
	Node* tail_list = slow->next;
	slow->next = NULL;

	//重排尾部链表
	Node* first = NULL;
	Node* second = tail_list;
	Node* third = tail_list->next;

	while (third != NULL)
	{
		second->next = first;
		first = second;
		second = third;
		third = third->next;
	}

	second->next = first;
	tail_list = second;

	//两个链表交叉重排
	p = src->next;
	Node* q = tail_list;

	while (p->next != NULL)
	{
		Node* tmp = p->next;
		p->next = q;
		q = q->next;
		p->next->next = tmp;
		p = tmp;
	}
	
	//将剩余的q连接至p的尾部(q剩余部分一定包含NULL
	p->next = q;

	return 0;
}

//例题7:判断是否是循环单链表，并且找到循环入口
// @param: src - 输入初始链表
// @return: 存在环，返回环的长度； 链表异常返回-1；链表无环返回-2
int isCycleList(Node* src)
{
	if (src == NULL || src->next == NULL)
	{
		return -1;//源链表异常
	}

	Node* fast = src;
	Node* slow = src;
	while (fast != NULL && fast->next != NULL)/* fast与slow步进长度不同，当fast与slow有交叉时，证明存在环 */
	{
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)
		{
			int siCycleLenth = 1; /* 计算链表内环的长度 */
			fast = fast->next;
			for (siCycleLenth = 1; fast != slow; siCycleLenth++)
			{
				fast = fast->next;
			}
			return siCycleLenth;
		}
	}

	return -2; //未找到环
}

// @param: src - 输入初始链表
// @return: 正常，返回起始节点地址； 异常，返回NULL
Node* findStartNodeInCycle(Node* src,int cycleLenth)
{
	if (src == NULL || src->next == NULL)
	{
		return 1;//源链表异常
	}

	Node* fast = src;
	Node* slow = src;
	/* fast指针向前便宜环个长度 */
	for (int i = 0; i < cycleLenth && fast != NULL; i++)
	{
		fast = fast->next;
	}

	/* slow与fast同步移动，直到相遇 */
	while (slow != fast && fast != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
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
#elif EXAMPLE >= 3 && EXAMPLE <=7
	insertTailWithElem(header, 1);
	insertTailWithElem(header, 2);
	insertTailWithElem(header, 3);
	insertTailWithElem(header, 4);
	insertTailWithElem(header, 5);
	insertTailWithElem(header, 6);
	//insertTailWithElem(header, 7);
#elif EXAMPLE >= 8
	/* 验证头插法 */
	insertTailWithElem(header, 1);
	insertTailWithElem(header, 2);
	insertTailWithElem(header, 3);
	printf("double list insert tail: ");
	printfList(header);
	deleteList(header);

	/* 验证尾插法 */
	header = initNode();
	insertHeaderWithElem(header, 1);
	insertHeaderWithElem(header, 2);
	insertHeaderWithElem(header, 3);
	printf("double list insert header: ");
	printfList(header);

	/* 任意位置插入/删除*/
	insertNodeWithElem(header, 2,10);
	deleteNode(header, 3);
	printf("delete third node and insert node in pos 2: ");
#endif

	printfList(header);
#if EXAMPLE <= 3
	deleteNode(header, 4);
	insertNodeWithElem(header, 4, 2);
	printfList(header);
#endif //EXAMPLE <= 3
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

#if EXAMPLE == 4
	reverseList(header);
	printfList(header);
#endif

#if EXAMPLE == 5
	deleteMiddleNode(header);
	printfList(header);

	printf("偶数节点数:");
	insertTailWithElem(header, 3);
	insertTailWithElem(header, 10);
	printfList(header);
	deleteMiddleNode(header);
	printfList(header);
#endif

#if EXAMPLE == 6
	reOrderList(header);
	printfList(header);
#endif

#if EXAMPLE == 7
	Node *pstrCycleNode = insertTailWithElem(header, 7);
	insertTailWithElem(header, 8);
	insertTailWithElem(header, 9);
	insertTailWithElem(header, 10);
	Node *pstrEndNode = insertTailWithElem(header, 11);
	pstrEndNode->next = pstrCycleNode;

	int rst = isCycleList(header);
	if (rst > 0)
	{
		pstrEndNode = findStartNodeInCycle(header, rst);
	}
	printf("The start node data in cycle list is: %d\n", pstrEndNode->data);
	cutCycleList(pstrEndNode);	/* 断开循环链表连接环  */
#endif 

	deleteList(header);
	return 0;
}