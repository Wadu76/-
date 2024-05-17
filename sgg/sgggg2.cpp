//Linear Table On Linked Storage Structure
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//编译预处理
//状态值和最大长度的宏定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
#define FILENAME_LENGTH 30

//定义状态返回值类型和数据元素类型
typedef int status;
typedef int ElemType;

//定义链表节点类型
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node,*Linklist;

//定义多线性表表头指针构成的链表节点类型
typedef struct HeadNodePointer
{
	Linklist head;
	struct HeadNodePointer *next;
}HeadNodePointer,*HeadNodeList;//指向每一条链表 

//函数声明
status InitList(Linklist *L,HeadNodeList Head_L);
status DestroyList(Linklist *L,HeadNodeList Head_L);
status ClearList(Linklist L);
status ListEmpty(Linklist L);
int ListLength(Linklist L);
status GetElem(Linklist L,int i,ElemType *e);
status LocateElem(Linklist L,ElemType e);
//status LocateElem(Linklist L,ElemType e,status (*compare)(Node *,ElemType));
status PriorElem(Linklist L,ElemType e,ElemType &pre);
status NextElem(Linklist L,ElemType cur,ElemType *next_e);
status ListInsert(Linklist L,int i,ElemType e);
status ListDelete(Linklist L,int i,ElemType *e);
status ListTraverse(Linklist L,status (*visit)(Node *));
status CreatList(Linklist L);
status SaveList(Linklist L);
status LoadList(Linklist *L,HeadNodeList Head_L);
status CreatAnotherList(Linklist *L,HeadNodeList Head_L);
status ChooseList(Linklist *L,HeadNodeList Head_L);
status reverseList(Linklist L,struct Node* head);
status DeleteNthFromEnd(Linklist L, int n);
status ListSort(Linklist L);
status ListTraversetest(Linklist L);
status visit(Node *p)
{
	printf("%d ",p->data);
	if(p->next!=NULL) return OK;
	else return INFEASIBLE;
}

status compare(Node *p,ElemType e)
{
	if(p->data!=e) return FALSE;		//若该节点数据元素不等于e，返回FALSE
	else return OK;
}

int main(void)
{
	ElemType e;
	int i=0,op=1,condition=0;			//op=1：循环入口；condition接收返回的获取状态
	int n=0;
	Linklist L=NULL;					//L:链表名、链表头指针

	HeadNodeList Head_L=NULL;			//Head_L:多线性表表头指针构成的链表
	Head_L=(HeadNodeList)malloc(sizeof(HeadNodePointer));	//为表头节点分配内存空间
	Head_L->head=NULL;					//表头节点数据域置空
	Head_L->next=NULL;					//表头节点指针域置空

	while(op)							//case 0:op=0（循环出口）
	{
		//显示菜单界面
		system("cls");
		printf("\n\n");
		printf("   Menu for Linear Table On Linked Storage Structure   \n");
		printf("--------------------------------------------------------------\n");
		printf("    	  0. Exit\n");
		printf("    	  1. InitList       	2. DestroyList\n");
		printf("    	  3. ClearList       	4. ListEmpty\n");
		printf("    	  5. ListLength      	6. GetElem\n");
		printf("    	  7. LocateElem      	8. PriorElem\n");
		printf("    	  9. NextElem       	10. ListInsert\n");
		printf("    	 11. ListDelete     	12. ListTrabverse\n");
		printf("    	 13. CreatList      	14. SaveList\n");
		printf("    	 15. LoadList       	16.ReverseList \n");//ReverseList RemoveFromEnd
		printf("    	 17. RemoveFromEnd	18.SortList\n");//
		printf("    	 19.CreateAnotherList 	20.ChooseList\n");//ChooseList CreateAnotherList
		printf("--------------------------------------------------------------\n");
		printf("    请选择你的操作[0~20]:");
		if(scanf("%d",&op)!=1) {fflush(stdin);op=18;}//若输入数字之外的字符，清空标准输入流里的数据，并将op置为default
		switch(op)
		{
		   case 1:
			 if(InitList(&L,Head_L)==OK) printf("线性表创建成功！\n");
			 else printf("线性表创建失败！\n");
			 getchar();getchar();
			 //system("pause");
			 break;

		   case 2:
			 if(DestroyList(&L,Head_L)==OK) printf("销毁线性表成功！\n");
			 else printf("线性表不存在，操作非法！\n销毁线性表失败！\n");
			 getchar();getchar();
			 break;

		   case 3:
			 if(ClearList(L)==OK) printf("清空线性表成功！\n");
			 getchar();getchar();
			 break;

		   case 4:
			 condition=ListEmpty(L);
			 if(condition==TRUE) printf("该线性表是空表！\n");
			 else if(condition==FALSE) printf("该线性表不是空表！\n");
			 getchar();getchar();
			 break;

		   case 5:
			 condition=ListLength(L);
			 if(condition!=INFEASIBLE) printf("线性表的长度是: %d \n",condition);
			 getchar();getchar();
			 break;

		   case 6:
			 printf("输入i，获取线性表中第i（1≤i≤%d）个数据元素的值：",ListLength(L));
			 scanf("%d",&i);
			 condition=GetElem(L,i,&e);	
			 if(condition==ERROR) printf("操作失败，输入的i必须满足范围 1≤i≤%d ！\n",ListLength(L));
			 else if(condition==OK) printf("查找成功！线性表中第 %d 个数据元素的值是 %d ！\n",i,e);
			 getchar();getchar();
			 break;

		   case 7:
			 printf("输入e，获取数据元素e在线性表中的位置：") ;
			 scanf("%d",&e);
			 condition=LocateElem(L,e);
			 if(condition==0) printf("获取失败，线性表中不存在数据元素 %d ！\n",e);
			 else if(condition>=1) printf("获取成功，数据元素 %d 在线性表中的位置为 %d ！\n",e,condition);
			 getchar();getchar();
			 break;

		   case 8:
			 printf("输入e，获取数据元素e在线性表中的前驱数据元素：");
			 scanf("%d",&e);
			 condition=PriorElem(L,e,i);
			 if(condition==ERROR) printf("操作失败，数据元素 %d 的前驱无定义\n",e);
			 else if(condition==OK) printf("操作成功，数据元素 %d 的前驱数据元素为 %d ！\n",e,i);
			 getchar();getchar();
			 break;

		   case 9:
			 printf("输入e，获取数据元素e在线性表中的后继数据元素：");
			 scanf("%d",&e);
			 condition=NextElem(L,e,&i);
			 if(condition==ERROR) printf("操作失败，数据元素 %d 的后继无定义\n",e);
			 else if(condition==OK) printf("操作成功，数据元素 %d 的后继数据元素为 %d ！\n",e,i);
			 getchar();getchar();
			 break;

		   case 10:
			 printf("分别输入i、e，在第i（1≤i≤%d）个位置之前插入新的数据元素e：",ListLength(L)+1);
			 scanf("%d%d",&i,&e);
			 condition=ListInsert(L,i,e);
			 if(condition==ERROR) printf("插入失败，输入的i必须满足 1≤i≤%d \n",ListLength(L)+1);
			 else if(condition==OK) printf("插入成功！\n");
			 getchar();getchar();
			 break;

		   case 11:
			 printf("输入i，删除第i（1≤i≤%d）个位置的数据元素：",ListLength(L));
			 scanf("%d",&i);
			 condition=ListDelete(L,i,&e);
			 if(condition==ERROR)
				 printf("删除失败，输入的 i 必须满足 1≤i≤%d ！\n",ListLength(L));
			 else if(condition==OK) printf("删除线性表第 %d 个位置的数据元素 %d 成功！\n",i,e);
			 getchar();getchar();
			 break;

		   case 12:
			 if(ListTraverse(L,visit)==ERROR) printf("线性表是空表！\n");
			 getchar();getchar();
			 break;

		   case 13:
			 condition=CreatList(L);
			 if(condition==OK) {printf("创建线性表成功！\n");ListTraverse(L,visit);}
			 else printf("创建线性表失败！\n");
			 getchar();getchar();
			 break;

		   case 14:
			 condition=SaveList(L);
			 if(condition==OK) printf("线性表保存成功！\n");
			 else if(condition==ERROR) printf("线性表保存失败！\n");
			 getchar();getchar();
			 break;

		   case 15:
			 condition=LoadList(&L,Head_L);
			 if(condition==OK) {printf("读取（加载）线性表成功！\n");ListTraverse(L,visit);}
			 else printf("读取（加载）线性表失败！\n");
			 getchar();getchar();
			 break;

		   case 16:
		   					//链表翻转reverseList(L)
				condition=reverseList(L,L->next);
				if(condition==INFEASIBLE)printf("线性表尚未创建");
				else printf("链表已成功翻转");
				
				getchar();getchar();
				break;


		   case 17:
				//删除链表的倒数第n个结点 RemoveNthFromEnd(L,n)
				printf("请输入你要删除的倒数第n个元素数\n");
				scanf("%d", &n);
				
				condition=DeleteNthFromEnd(L,n);
				if(condition==INFEASIBLE)printf("线性表尚未创建，删除失败！");
				else printf("删除成功！");		   	
		   		
				

			
			case 18:
				//链表排序：函数名称是sortList(L)从小到大
				condition=ListSort(L);
				if(condition==INFEASIBLE)printf("线性表可尚未创建！");
				else printf("从小到大排序成功！");
				getchar();getchar();
				break;

			
			case 19:
				condition=CreatAnotherList (&L,Head_L);
				if(condition==OK) printf("创建线性表成功！\n");
				else printf("创建线性表失败！\n");
				getchar();getchar();
				break;
			
			
			case 20:
				condition=ChooseList(&L,Head_L);
				if(condition==OK) printf("选择线性表成功！\n");
				else printf("选择线性表失败！\n");
				getchar();getchar();
				break;
				
				
			case 21://test
				ListTraversetest(L);	
				getchar();getchar();
		   case 0:
			 break;

		   default:
			 printf("输入无效！菜单功能选择失败！\n");
			 system("pause");
			 break;

		}//end of switch

	}//end of while

	printf("欢迎下次再使用本系统！\n");

	return 0;
}//end of main()

status ListTraversetest(Linklist L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (!L)
    {
        return INFEASIBLE;
    }
    else
    {
        Linklist p;
        p=L;
        if(!p->next) printf("是空表"); 
        while(p->next)
        {
            p=p->next;
            if(p->next) printf("%d ",p->data);
            if(!p->next) printf("%d",p->data);
        }
        return OK;
    }
}

//初始化链表：初始条件是线性表L已存在；操作结果是构造一个带有表头节点的空链表。
status InitList(Linklist *L,HeadNodeList Head_L)
{
	HeadNodePointer *p=Head_L;
	if((*L)!=NULL) {printf("不能多次初始化一个线性表！\n");return ERROR;}
	*L=(Linklist)malloc(sizeof(Node));		//L指针指向调用malloc函数为表头节点动态分配的内存空间地址
	//if(!*L) exit(OVERFLOW);					//if(*L==NULL) exit(OVERFLOW);
	(*L)->data=0;							//初始化链表长度：头指针的数据域用于存储链表长度
	(*L)->next=NULL;						//头指针的指针域置空：头指针的指针域用于存储链表首元节点的地址
	while(p->next!=NULL) p=p->next;			//遍历至表尾
	p->next=(HeadNodePointer *)malloc(sizeof(HeadNodePointer));			//为节点分配空间
	p->next->head=(*L);						//数据域录入线性表表头指针
	p->next->next=NULL;						//指针域置空
	return OK;
}

//销毁链表：初始条件是线性表L已存在；操作结果是销毁线性表L。
status DestroyList(Linklist *L,HeadNodeList Head_L)
{
	Node *q=(*L),*pre_q=NULL;				//q（从表头节点开始）指向当前遍历到的节点，pre_q指向当前节点q的前一个结点
	HeadNodePointer *p=Head_L,*temp=NULL;
	if(*L==NULL) return ERROR;				//ERROR：链表不存在，操作非法
	while(p->next->head!=(*L)) p=p->next;	//遍历：查找线性表表头指针
	temp=p->next;							//记录下线性表表头指针所在的节点
	p->next=temp->next;						//将线性表表头指针所在的节点从链表中删除
	free(temp);								//释放线性表表头指针所在的节点
	while(q!=NULL)							//遍历，依次释放除表头节点之外的所有节点所占的内存空间
	{
		pre_q=q;							//pre_q记录下当前节点
		q=q->next;							//q指向当前节点的下一个节点
		free(pre_q);						//释放当前节点
	}
	*L=NULL;								//清空链表（头指针）
	return OK;
}

//清空表：初始条件是线性表L已存在；操作结果是将L重置为空表。
status ClearList(Linklist L)
{
	Node *q=NULL,*pre_q=NULL;				//pre_q指向当前节点q的前一个结点
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return ERROR;}		//ERROR：链表不存在，操作非法
	q=L->next;								//q（从首元节点或NULL开始）指向当前遍历到的节点
	if(q==NULL) {printf("线性表是空表，无需清空!\n");return ERROR;}		//ERROR：链表是空表，无需清空
	while(q!=NULL)							//遍历，依次释放除表头节点之外的所有节点所占的内存空间
	{
		pre_q=q;							//pre_q记录下当前节点
		q=q->next;							//q指向当前节点的下一个节点
		free(pre_q);						//释放当前节点
	}
	L->data=0;								//头指针的数据域置零
	L->next=NULL;							//头指针的指针域置空
	return OK;
}

//判定空表：初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE。
status ListEmpty(Linklist L)
{
	if(L==NULL) {printf("线性表不存在。\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
	else return (L->next==NULL)?TRUE:FALSE;							//return (!L->data)?TRUE:FALSE;
}

//求表长：初始条件是线性表已存在；操作结果是返回L中数据元素的个数。
int ListLength(Linklist L)
{
	if(!L)return INFEASIBLE;
	Linklist p=L->next,q=NULL;
	int length=0;//标记链表元素长度 
	
	while(p){
		length++;
		p=p->next;
	}//记录表长 
	return length;
						//头指针的数据域用于存储链表长度
}

//获取元素：初始条件是线性表已存在，1≤i≤ListLength(L)；操作结果是用e返回L中第i个数据元素的值。
status GetElem(Linklist L,int i,ElemType *e)
{
	int num=1;
	Node *p=NULL;
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
	p=L->next;								//p指向首元节点或NULL
	if(i<1||i>L->data) return ERROR;		//ERROR：不满足查找条件
	while(num<i)							//非随机存取：遍历查找，直至找到第i个数据元素
	{
		p=p->next;							//p指向下一个数据元素
		num++;
	}
	*e=p->data;								//取出第i个数据元素的值
	return OK;
}

//查找元素：初始条件是线性表已存在
//操作结果是返回L中第1个与e满足关系compare()关系的数据元素的位序；若这样的数据元素不存在，则返回值为0。
/*status LocateElem(Linklist L,ElemType e,status (*compare)(Node *,ElemType))
{
	int num=1,find=FALSE;					//num用于记录数据元素e的位序,find用于记录是否查询到该数据元素
	Node *p=NULL;
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
	p=L->next;								//p指向表头节点的next指针指向的节点（首元节点或者NULL）
	while(p)								//非随机存取：遍历查找，直至找到值为的e的数据元素
	{
		if(compare(p,e)==TRUE) {find=TRUE;break;}
		else {p=p->next;num++;}
	}
	return (find==TRUE)?num:0;				//若查找到尽头都找不到值为的e的数据元素，返回0
}*/
status LocateElem(Linklist L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    else{
        Linklist p=L->next;
        int i=0;
        while(p){
            i++;
            if(p->data==e){
                return i;
            }
            p=p->next;
        }
    }
    return ERROR;

    /********** End **********/
}


//获得前驱：初始条件是线性表L已存在
//操作结果是若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
/*status PriorElem(Linklist L,ElemType e,ElemType &pre)
{
	Node *pre_q=NULL,*q=NULL;				//pre_q指向当前节点q的前一个结点
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：线性表不存在，操作非法
	q=L->next;								//q（从首元节点或NULL开始）指向当前遍历到的节点
	while(q&&q->data!=e) {pre_q=q;q=q->next;}						//遍历查找值为的cur的数据元素
	//若找到了值为的cur的数据元素，且该数据元素的前驱有定义，取出其前驱的值
	if(q!=NULL&&pre_q!=NULL) {pre=pre_q->data;return OK;}
	else return ERROR;						//ERROR：不存在值为的cur的数据元素，或该数据元素的前驱没有定义
}*/
status PriorElem(Linklist L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    else{
        Linklist p=L->next,q=L;
        int i=0;
        while(p){
            i++;
            if(p->data==e&&i!=1){//此处i！-1防止e为首个元素
                pre=q->data;
                return OK;
            }
            p=p->next;
            q=q->next;
        }
    }
    return ERROR;

    /********** End **********/
}

//获得后继：初始条件是线性表L已存在
//操作结果是若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义。
status NextElem(Linklist L,ElemType cur,ElemType *next_e)
{
	Node *p=NULL;
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
	p=L->next;								//p（从首元节点或NULL开始）指向当前遍历到的节点
	while(p&&p->data!=cur) p=p->next;		//遍历查找
	//若找到了值为的cur的数据元素，且该数据元素的后继有定义，取出其后继的值
	if(p!=NULL&&p->next!=NULL) {*next_e=p->next->data;return OK;}
	else return ERROR;						//ERROR：不存在值为的cur的数据元素，或该数据元素的后继没有定义
}

//插入元素：初始条件是线性表L已存在，1≤i≤ListLength(L)+1；操作结果是在L的第i个位置之前插入新的数据元素e。
status ListInsert(Linklist L,int i,ElemType e)
{
	int num=1;								//num用于记录位置
	Node *p=L,*q=NULL;						//p指向表头节点，q为新生成的节点
	if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
	if(i<1||i>L->data+1) return ERROR;		//ERROR：不满足插入条件
	while(num<i) {p=p->next;num++;}			//非随机存取：遍历，找到第i个位置的前一个节点
	q=(Node *)malloc(sizeof(Node));			//为新节点分配内存空间
	if(q==NULL) exit(OVERFLOW);
	q->data=e;								//录入数据元素数据
	q->next=p->next;						//插入操作
	p->next=q;
	L->data++;								//数据元素的个数加一
	return OK;
}

//删除元素：初始条件是线性表L已存在且非空，1≤i≤ListLength(L)；操作结果：删除L的第i个数据元素，用e返回其值。
status ListDelete(Linklist L,int i,ElemType *e)
{
	int num=0;								//num用于记录位置
	Node *p=L,*q=NULL;						//将p指向表头节点，q为待删除的节点
	if(L==NULL||L->next==NULL) {printf("线性表不存在或线性表为空，操作非法！\n");return -1;}
	if(i<1||i>L->data||L->data==0) return ERROR;					//ERROR：不满足删除条件
	while(num<i-1) {p=p->next;num++;}		//非随机存取：遍历，找到第i个节点的前一个节点
	q=p->next;								//删除操作
	p->next=q->next;
	*e=q->data;								//取出待删除的数据元素的值
	free(q);								//释放节点所占的内存空间
	L->data--;								//数据元素的个数减一
	return OK;
}

//遍历表：初始条件是线性表L已存在且非空；操作结果是依次对L的每个数据元素调用函数visit()。
status ListTraverse(Linklist L,status (visit)(Node *))
{
   Node *p=NULL;
   if(L==NULL) {printf("线性表不存在，操作非法！\n");return -1;}		//ERROR(-1)：链表不存在，操作非法
   if(L->next==NULL) return ERROR;									//ERROR：链表是空表，无需遍历
   p=L->next;								//p指向首元节点
   //while(visit(p)!=INFEASTABLE) p=p->next;	//输出每个节点的数据元素
   while(p){
   		printf("%d ", p->data);
   		p=p->next;
   }
   printf("\n");
   return OK;
}

//创建链表：初始条件是线性表L存在且已被初始化；操作结果是创建一个带有表头节点，无限长度的链表。
status CreatList(Linklist L)
{
	ElemType n;
	Node *p=NULL,*pre_p=L;					//p表示新生成的节点，pre_p指向其上一个节点
	if(L==NULL) {printf("线性表未初始化！");return ERROR;}			//ERROR：未初始化
	printf("创建线性表，输入以1开始 0为结束标记的数据元素：");
	scanf("%d", &n);
	if(n==1){
		scanf("%d", &n);
		while(n) 
		{
			
			p=(Node *)malloc(sizeof(Node));		//为节点分配空间
			//if(p==NULL) exit(OVERFLOW);			//OVERFLOW
			p->data=n;							//录入数据元素数据
			pre_p->next=p;						//延伸链表
			pre_p=p;
			L->data++;							//数据元素个数加一
			scanf("%d", &n);
		}
	}
	if(p!=NULL) p->next=NULL;
	return OK;
}

//保存链表：初始条件是线性表L存在且已被初始化；操作结果是将该链表存储到输入的文件路径中去。
status SaveList(Linklist L)
{
	char filename[FILENAME_LENGTH]={0};		//filename用于存储输入的文件路径
	FILE *fp=NULL;							//文件指针
	Node *p=NULL;
	if(L==NULL) {printf("线性表未初始化！\n");return -1;}				//ERROR(-1)：未初始化
	p=L->next;
	printf("输入文件路径(长度应在%d字符以内)，将线性表保存到该文件中：",FILENAME_LENGTH);
	scanf("%s",filename);
	fp=fopen(filename,"w");					//打开文件
	if(fp==NULL) {printf("打开文件错误！\n");return ERROR;}	//ERROR：打开文件错误
	while(p) {fprintf(fp,"%d ",p->data);p=p->next;}					//写入文件
	fclose(fp);								//关闭文件 
	return OK;
}

//读取（装载）链表：初始条件是输入的路径文件中的数据是链表形式的数据
//操作结果是将输入的路径文件中的数据装载到链表中去。
status LoadList(Linklist *L,HeadNodeList Head_L)
{
	char filename[FILENAME_LENGTH];			//filename用于存储输入的文件路径
	FILE *fp=NULL;							//文件指针
	ElemType n;								//n用于读取节点的数据域
	Node *p=NULL,*pre_p=NULL;				//p表示新生成的节点，pre_p指向其上一个节点
	printf("输入文件路径(长度应在%d字符以内)，将线性表保存到该文件中：",FILENAME_LENGTH);
	scanf("%s",filename);
	fp=fopen(filename,"r");					//打开文件
	if(fp==NULL) {printf("打开文件错误！\n");return ERROR;}
	(*L)=NULL;								//清空现有头指针的指向
	if(InitList(L,Head_L)==ERROR) exit(OVERFLOW);					//初始化线性表
	pre_p=*L;
	while(fscanf(fp,"%d ",&n)!=EOF)
	{
		p=(Node *)malloc(sizeof(Node));		//为节点分配空间
		if(p==NULL) exit(OVERFLOW);			//OVERFLOW
		p->data=n;							//录入数据元素数据
		pre_p->next=p;						//延伸链表
		//pre_p向后移动，记录当前链表的最后一个节点，也就是即将生成的新节点的前一个结点
		pre_p=p;							
		(*L)->data++;						//数据元素个数加一
	}
	if(p!=NULL) p->next=NULL;				//最后一个节点的next域赋值为NULL
	fclose(fp);								//关闭文件
	return OK;
}

//创建一个新的线性表：初始条件是已经存在至少一个线性表
//操作结果是保留原有的线性表的同时，创建一个新的线性表
status CreatAnotherList(Linklist *L,HeadNodeList Head_L)
{
	Linklist AnotherList=NULL;
	if((*L)==NULL) {printf("先创建第一个线性表吧\n");return ERROR;}	
	if(InitList(&AnotherList,Head_L)==OK)
	{
		(*L)=AnotherList;					//初始化头指针
		printf("新的线性表创建成功！\n");
	}
	else {printf("线性表创建失败！\n");return ERROR;}					//ERROR:初始化失败
	if(CreatList(*L)==OK) return OK;		//创建线性表
	else return ERROR;						//ERROR:创建失败
}

//选择线性表：初始条件是已经存在至少一个线性表
status ChooseList(Linklist *L,HeadNodeList Head_L)
{
	int i=1,n;
	HeadNodePointer *p=Head_L->next;
	if(p==NULL) {printf("没有可选择的线性表！\n");return ERROR;}		//ERROR:没有可选择的线性表
	while(p!=NULL)							//遍历线性表头指针数组
	{
		printf("第%d个线性表：",i);
		if(ListTraverse(p->head,visit)==ERROR) printf("\n");		//遍历输出该线性表并进行格式控制
		p=p->next;
		i++;
	}
	printf("输入n，选择第n个线性表进行操作：");
	scanf("%d",&n);
	if(n<1||n>=i) {printf("不存在第 %d 个线性表！\n",n);return ERROR;}	//ERROR：输入错误，不存在该线性表
	i=1;
	p=Head_L->next;
	while(p!=NULL)							//遍历线性表头指针数组
	{
		if(i==n) (*L)=p->head;
		p=p->next;
		i++;
	}
	if((*L)==NULL) return ERROR;
	else return OK;
}

//18链表翻转 
status reverseList(Linklist L ,struct Node* head) {
	if(head==NULL)return INFEASIBLE;
	
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;

    while (current != NULL) {
    	//printf("%d\n",current->data); test
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    Linklist p=head;
	L->next=head;
    /*while(p){
    	printf("%d ",p->data);
    	p=p->next;
	} test */
    return OK;
}

//19删除倒数第n个元素
status DeleteNthFromEnd(Linklist L, int n){
	if(!L)return INFEASIBLE;
	Linklist p=L->next,q=NULL;
	int length=0;//标记链表元素长度 
	
	while(p){
		length++;
		p=p->next;
	}//记录表长 
	
	p=L->next;
	q=L;
	for(int i=0;i<length-n;i++){
		q=p;
		p=p->next;
	}//此时p指向要删除元素，q指向要删除元素的前驱。
	
	q->next=p->next;
	p->next=NULL;
	free(p);
	return OK;
} 

//20排序 bubble
status ListSort(Linklist L){
	if(!L)return INFEASIBLE;
	Linklist p=L->next;
	int length=0;//标记链表元素长度 
	
	while(p){
		length++;
		p=p->next;
	}
	//printf("%d\n", length);//test
	p=L->next;
	//q=p->next;
	int a[length];
	int i=0,j=0;
	while(p){
		a[i]=p->data;
		p=p->next;
		i++;
	}
	/*for(i=0;i<length;i++){
		printf("%d ", a[i]);
	}//test*/
	printf("\n");
	p=L->next;
	//排序过程 
	for(int i=0;i<length-1;i++){
		for(int j=0;j<length-1-i;j++){
			if(a[j]>a[j+1]){
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
	}//原本问题出现在此处j<length-1-i没-1 
	
/*	int tem;
	for (i = 0; i < length-1;i ++)//size-1是因为不用与自己比较，所以比的数就少一个
	{
		int count = 0;
		for (j = 0; j < length-1 - i; j++)	//size-1-i是因为每一趟就会少一个数比较   
		{
			if (a[j] > a[j+1])//这是升序排法，前一个数和后一个数比较，如果前数大则与后一个数换位置
			{
				tem = a[j];
				a[j] = a[j+1];
				a[j+1] = tem;
				count = 1;
				
			}
		}
		if (count == 0)			//如果某一趟没有交换位置，则说明已经排好序，直接退出循环
				break;	
	}*/
		/*for(i=0;i<length;i++){
		printf("%d\n", a[i]);//test
	}*/
	i=0;
	while(p){
		p->data=a[i];
		p=p->next;
		i++;
	}
	return OK;
} 
