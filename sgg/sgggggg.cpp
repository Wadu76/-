/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define max(a, b) ((a) > (b) ? (a) : (b))
//#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
#define LIST_INIT_SIZE 100
//static index=0;
#define LISTINCREMENT  10

typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;         //线性表表长 
	int listsize;  //线性表分配空间大小 
}SqList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  SqList L;
      } elem[10];
      int length;
  int listsize; //线性表集合分配的空间 10
 }LISTS;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status InitInput(SqList &L); //  辅助元素  询问初始化后是否需要输入线性表数据 
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); //简化过
status PriorElem(SqList L,ElemType cur,ElemType&pre_e);
status NextElem(SqList L,ElemType cur,ElemType&next_e);
status ListInsert(SqList&L,int i,ElemType e);
status ListDelete(SqList&L,int i,ElemType& e);
status ListTraverse(SqList L);  //简化过
status MaxSubArray(SqList L); 
status SubArrayNum(SqList L,int K);
status sortList(SqList &L);
status  SaveList(SqList L,char FileName[]);
status  LoadList(SqList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
int MaxSubArray(int* nums, int numsSize);
int subarraySum(int* nums, int numsSize, int k);
void bubble_sort(int *a,int n);
/*--------------------------------------------*/
int main() {
	system("cls");
    SqList L;  int op = 1;
    FILE*fp=NULL;
    int buff[255];
    int i, j, ch, e, n, f, v,k18,k19,k;
    ElemType pre, next;
    LISTS Lists;
    Lists.length = 0;
    Lists.listsize = 10;
    char name[30];
    char ListName[50];
    char FileName[50];
    L.elem=NULL;
    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList        11. ListDelete\n");
        printf("    	  2. DestroyList     12. ListTraverse\n");
        printf("    	  3. ClearList       13. SaveList(写入文件)\n");
        printf("    	  4. ListEmpty      14. LoadList\n");
        printf("    	  5. ListLength      15. AddList\n");
        printf("    	  6. GetElem       16.RemoveList\n");
        printf("          7. LocateElem     17.LocateList\n");
        printf("          8. PriorElem     18.MaxSubArray\n");
        printf("          9. NextElem     19.SubarraySum\n");
        printf("          10. ListInsert     20. SortList\n");
        printf("    	  21.MultiList		0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
        		//L.elem=NULL;
				j=InitList(L);
		    	if(j==OK){
					printf("线性表创建成功！\n");
						//InitInput(L);         
						}
				else if(j==ERROR)
					printf("线性表创建失败！\n");                                                
				else if(j==INFEASIBLE)
					printf("线性表已存在，不能进行线性表初始化操作！\n");

            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK)
                printf("\n线性表销毁成功\n");
            else if (DestroyList(L) == INFEASIBLE)
                printf("线性表不存在，不能进行线性表销毁操作！\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK)
                printf("线性表清空成功！\n");
            else
                printf("线性表不存在，不能进行线性表清空操作！\n");
            getchar(); getchar();
            break;
        case 4:
            if (ListEmpty(L) == TRUE)
                printf("线性表为空！\n");
            else if (ListEmpty(L) == FALSE)
                printf("线性表不为空！\n");
            else if (ListEmpty(L) == INFEASIBLE)
                printf("线性表不存在,不能进行线性表判空操作！\n");
            getchar(); getchar();
            break;
        case 5:
            if (ListLength(L) >= 0)
                printf("线性表长度为 %d ！\n", ListLength(L));
            else
                printf("线性表不存在，不能求表长！\n");
            getchar(); getchar();
            break;
        case 6:
            printf("请输入查找元素的位置：\n");
            scanf("%d", &i);
            j = GetElem(L, i, e);
            if (j == OK)
                printf("线性表中第%d位元素是%d\n", i, e);
            else if (j == ERROR)
                printf("所选择的元素位置不合法（可能小于1或大于线性表长度）\n");
            getchar(); getchar();
            break;
        case 7:
            printf("请输入要查找的查找元素：\n");
            scanf("%d", &e);
            j = LocateElem(L, e);
            if (j > 0)
                printf("要查找的元素 %d 在线性表中的第 %d 位！\n", e, j);
            else if (j == ERROR)
                printf("查找元素失败，该元素不在线性表中！\n");
            else if (j == INFEASIBLE)
                printf("线性表不存在，不能进行元素查找！\n");
            getchar(); getchar();
            break;
        case 8:
            printf("请输入待查找元素以获取其前驱元素：\n");
            scanf("%d", &e);
            j = PriorElem(L, e, pre);
            if (j == OK)
                printf("元素 %d 的前驱元素是 %d ！\n", e, pre);
            else if (j == ERROR)
                printf("元素 %d 没有前驱元素（该元素在表头或者该元素不在表中）！\n", e);
            else if (j == INFEASIBLE)
                printf("线性表不存在，不能获取元素！\n");
            getchar(); getchar();
            break;
        case 9:
            printf("请输入要查找元素以获取其后继元素：\n");
            scanf("%d", &e);
            j = NextElem(L, e, next);
            if (j == OK)
                printf("该元素 %d 的后继元素是 %d ！\n", e, next);
            else if (j == ERROR)
                printf("该元素 %d 没有后继元素（该元素在表尾或者该元素不在表中）！\n", e);
            else if (j == INFEASIBLE)
                printf("线性表不存在，不能获取元素！\n");
            getchar(); getchar();
            break;
        case 10:
            printf("请输入待插入元素：\n");
            scanf("%d", &e);
            printf("请输入插入位置后一个元素序号：\n");
            scanf("%d", &i);
            j = ListInsert(L, i, e);
            if (j == OK)
                printf("插入元素成功！\n");
            else if (j == ERROR)
                printf("插入位置不准确;i值不合法！\n");
            else if (j == INFEASIBLE)
                printf("线性表不存在，不能进行插入操作！\n");
            getchar(); getchar();
            break;
        case 11:
            printf("请输入需要删除的元素的位置：\n");
            scanf("%d", &i);
            j = ListDelete(L, i, e);
            if (j == OK)
                printf("删除元素成功，所删除元素为 %d ！\n", e);
            else if (j == ERROR)
                printf("删除位置不正确！\n");
            else if (j == INFEASIBLE)
                printf("线性表不存在，不能进行删除操作！\n");
            getchar(); getchar();
            break;
        case 12:
            j = ListTraverse(L);
            if (j == OK)
                printf("\n线性表遍历成功！\n");
            else if (j == ERROR)
                printf("\n线性表中是空表，无元素！\n");
            else if (j == INFEASIBLE)
                printf("\n线性表不存在！\n");
            if (!j) printf("线性表是空表！\n");
            getchar(); getchar();
            break;
        case 13:
            printf("请输入待操作文件名称：\n");
            scanf("%s", FileName);
            j = SaveList(L, FileName);
            if (j == OK)
                printf("线性表中数据已成功写入指定文件中！\n");
            else if (j == INFEASIBLE)
                printf("线性表不存在！\n");
            getchar(); getchar();
            break;


        

		case 14:
            printf("\t现在将FileName文件的数据读入线性表L中，请输入FileName文件名：");
            scanf("%s", FileName);
            L.elem=NULL;
            if (LoadList(L, FileName) == OK)
                printf("\t文件读入成功！\n");
            else if (LoadList(L, FileName) == INFEASIBLE)
                printf("\t文件读入失败！请检查L是否清空。\n");
            printf("\t按任意键继续.\n");
            getchar();
            getchar();
            break;

        case 15:
            printf(" 请输入n个线性表，n的值为：\n");
            scanf("%d", &n);
            while (n)
            {
                printf(" 请输入线性表名称，和数据元素，以0结尾，不包括0\n");
                scanf("%s", name);
                AddList(Lists, name);
                scanf("%d", &f);
                while (f!=0)
                {
                    ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, f);
                    scanf("%d", &f);
                }
                n--;
            }
            printf("\n\n打印所有线性表，如下：\n ");
            for (n = 0; n < Lists.length; n++)
            {
                printf("          第%d个线性表名字为%s ", n + 1, Lists.elem[n].name);
                ListTraverse(Lists.elem[n].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
        case 16:
            printf("请输入待删除线性表名称 \n");
            scanf("%s", ListName);
            j = RemoveList(Lists, ListName);
            if (j == ERROR)
                printf("删除失败,无该名称的线性表\n");
            else if (j == -1)
                printf("删除失败！该线性表集合为空\n");
            else
                printf("删除成功\n");
            printf("\n\n打印所有线性表，如下：\n ");
            for (n = 0; n < Lists.length; n++)
            {
                printf("          第%d个线性表名字为%s ", n + 1, Lists.elem[n].name);
                ListTraverse(Lists.elem[n].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
        case 17:
            if (Lists.length == 0)
            {
                printf("该线性表为空\n ");
            }
            printf("请输入待查找线性表名称 \n");
            scanf("%s", ListName);
            j = LocateList(Lists, ListName);
            if (!j)
                printf("线性表集合中无该名称的线性表 \n\n");
            else if (j == -1)
                printf("错误 该线性表集合为空\n\n");
            else
            {
                printf("该线性表序号为: %d \n", j);
                printf("          该线性表为名字为%s ", Lists.elem[j - 1].name);
                ListTraverse(Lists.elem[j - 1].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
            
        case 18:
        	if(L.elem==NULL||L.listsize==0)printf("请先初始化一个线性表");
			else{
			
			k18=MaxSubArray(L.elem, L.length);
            printf("最大的子数组之和为：%d\n",k18);
        	}
            getchar();getchar();
            break;
        
        case 19:
        	if(L.elem==NULL||L.listsize==0)printf("请先初始化一个线性表");
        	else{
        		printf("请输入要和为几的子数组：\n");
				scanf("%d", &k); 
        		k19=subarraySum(L.elem, L.length, k);
        		printf("和为%d的子数组有%d个\n",k, k19);
			}
			getchar();getchar();
			break;
		
		case 20:
			if(L.elem==NULL||L.listsize==0)printf("请先初始化一个线性表");
			else{
				bubble_sort(L.elem, L.length);
				printf("线性表已从小到大排序好！\n");
			}
			getchar();getchar();
			break;
		case 21:
                printf("请选择需要的操作：\n");                             //选择操作
                printf("1. 添加线性表   2. 移除线性表   3. 查找线性表   4.输出线性表名字   5.单独操作\n");//选择操作
                scanf("%d",&j);                                             //输入操作
                switch(j){
                    case 1:
                        printf("请输入线性表的名字:\n");                //输入线性表的名字
                        scanf("%s",ListName);                                          //输入线性表的名字
                        if(AddList(Lists,ListName)==OK)                                 //添加线性表
                            printf("添加成功\n");                                       //添加成功
                        else
                            printf("添加失败\n");                                       //添加失败
                        break;
                    case 2:
                        printf("请输入线性表的名字:\n");    //输入线性表的名字
                        scanf("%s",ListName);                               //输入线性表的名字
                        if(RemoveList(Lists,ListName)==OK)                  //移除线性表
                            printf("移除成功\n");                           //移除成功
                        else
                            printf("移除失败\n");                           //移除失败
                        break;
                    case 3:
                        printf("请输入线性表的名字:\n");                    //输入线性表的名字
                        scanf("%s",ListName);                               //输入线性表的名字
                        if(LocateList(Lists,ListName)!=0)                   //查找线性表
                            printf("线性表的位置为%d\n",LocateList(Lists,ListName));//查找线性表
                        else
                            printf("未找到线性表\n");                       //未找到线性表
                        break;                                              //跳出
                    case 4:
                        if(Lists.length==0){                                    //判断线性表数组是否为空
                            printf("线性表数组为空\n");                         //线性表数组为空
                            break;                                              //跳出
                        }else{
                            for(int num=0;num<Lists.length;num++){              //遍历线性表数组
                                printf("%d %s\n",num+1,Lists.elem[num].name);   //输出线性表的名字
                            }
                        }
                        break;                                                  //跳出
                    case 5:
                        printf("请输入线性表的位置\n");
                        scanf("%d",&k);                                     //输入位置
                        if(k<=Lists.length){                                //判断位置是否合理
                            L=Lists.elem[k-1].L;                            //切换到单个线性表
                            printf("切换成功\n");  //切换成功
                        }else
                            printf("切换失败\n");                           //切换失败
                        break;
                }
                printf("按回车继续\n");                                     //提示
                getchar();getchar();                                        //暂停
                break;

        case 0:
            break;
        default:printf("非法字符使用");
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()
status InitList(SqList& L){
    if(L.elem==NULL)
    {//使用malloc函数为顺序表开辟空间，表长为LIST_INIT_SIZE
        L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        if(L.elem==NULL)   return ERROR;
        L.length=0;
        L.listsize=LIST_INIT_SIZE;
		return OK;
    }
    else   
        return INFEASIBLE;	//线性表已存在，不能构造空表
}

status DestroyList(SqList& L)
// 2如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem) {
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else return INFEASIBLE;

    /********** End **********/
}

status ClearList(SqList& L)
// 3.如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem) {
        L.length = 0;
        return OK;
    }
    else return INFEASIBLE;

    /********** End **********/
}

status ListEmpty(SqList L)
// 4.如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    else {
        if (L.length == 0)return TRUE;
        else return FALSE;
    }

    /********** End **********/
}

status ListLength(SqList L)
// 5.如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/

    if (L.elem == NULL) return INFEASIBLE;
    else if (L.length)return L.length;
    /********** End **********/
}

status GetElem(SqList L, int i, ElemType& e)
// 6.如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    else if (i > L.length || i <= 0)return ERROR;
    else {
        e = L.elem[i - 1];
        return OK;
    }


    /********** End **********/
}

int LocateElem(SqList L, ElemType e)
// 7.如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //最后一位查不到 
    if (L.elem == NULL)return INFEASIBLE;
    int i, flag = 0;
    for (i = 1; i < L.length + 1; i++) {
        if (L.elem[i - 1] == e) {
            flag = 1;
            break;
        }
    }
    if (flag)return i;
    else return 0;
    /********** End **********/
}

/*status PriorElem(SqList L, ElemType e, ElemType& pre)
 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    ********* Begin *********
    if (L.elem == NULL)return INFEASIBLE;
    int i, flag = 0;
    for (i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            flag = 1;
            break;
        }
    }
    if (i - 1 >= 0 && flag) {
        pre = L.elem[i - 1];
        return OK;
    }
    else return ERROR;

}
    /********** End **********/

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 8.如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；
//如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASTABLE。
{
    int i;
    if(L.elem)
    {
        for(i=1;i<L.length;i++)
        {//遍历线性表
            if(e==L.elem[i])
            {//查找到对应元素后，返回其前驱元素
                pre=L.elem[i-1];
                return OK;
            }
        }
        return ERROR;	//查找与e元素相同的结点失败
    }
    else
        return INFEASIBLE;	//线性表不存在
}

status NextElem(SqList L, ElemType e, ElemType& next)
// 9.如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    int i, flag = 0;
    for (i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            flag = 1;
            break;
        }
    }
    if (i + 1 <= L.length - 1 && flag) {
        next = L.elem[i + 1];
        return OK;
    }
    else return ERROR;

    /********** End **********/
}

status ListInsert(SqList& L, int i, ElemType e)
// 10.如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //插入i位置 索引为i-1
    if (L.elem == NULL)return INFEASIBLE;//线性表不存在
    else {
        if (i <= 0 || i > L.length + 1) {
            return ERROR;
        }

        if (L.length + 1 > L.listsize) {
            L.elem = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
            L.listsize += LISTINCREMENT;
        }

        int j;
        for (j = L.length + 1; j >= i; j--) {
            L.elem[j] = L.elem[j - 1];
        }
        L.length++;
        L.elem[i - 1] = e;

        return OK;
    }


    /********** End **********/
}

status ListDelete(SqList& L, int i, ElemType& e)
// 11.如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    else if (i <= 0 || i > L.length)return ERROR;
    else {
        int j;
        e = L.elem[i - 1];
        for (j = i - 1; j < L.length; j++) {
            L.elem[j] = L.elem[j + 1];
        }
        L.length--;
        return OK;
    }
    /********** End **********/
}

status ListTraverse(SqList L)
// 12.如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    else {
        int i;
        for (i = 0; i < L.length - 1; i++) {
            printf("%d ", L.elem[i]);
        }
        if (i > 0)
            printf("%d", L.elem[i]);
        return OK;
    }

    /********** End **********/
}

status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    FILE *fp;
    int i=0;
	if(L.elem)
	{
		fp=fopen(FileName,"wb");
		if(!fp)	//文件打开失败
			return ERROR;
		while(i<L.length)
		{
			fprintf(fp,"%d ",L.elem[i]);	//将线性表中数据写入文件
			i++;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;	//线性表不存在
}

status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	FILE *fp;
    int i=0; 
	if(L.elem)
		return INFEASIBLE;	//线性表已存在，读档会使元素失去
	else
	{
		L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);	//初始化线性表
        L.length=0;
       	L.listsize=LIST_INIT_SIZE;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			while((fscanf(fp,"%d ",&L.elem[i]))!=EOF)	//文件未读取完成
            {
                if(L.length<L.listsize-1)	//线性表未满，直接读入数据
                {
	                L.length++;
	                i++;
				}
				else	//线性表已满，重新分配空间再读入数据
				{
					L.elem=(ElemType *)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
					L.listsize+=LISTINCREMENT;
					L.length++;
					i++;
				}
            } 
		}
		fclose(fp);
		return OK;
	}
} 

status AddList(LISTS& Lists, char ListName[])
// 15.只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //顺序表listsize=10
    static int  j = 0;
    int i;


    for (i = 0; ListName[i]; i++) {
        Lists.elem[j].name[i] = ListName[i];
    }
    Lists.elem[j].name[i] = '\0';
    Lists.length += 1;
    //顺序表的初始化

    //InitList(Lists.elem[j].L.elem);
    //Lists.elem[j].L.listsize=10;

    Lists.elem[j].L.elem = (ElemType*)malloc(10 * sizeof(ElemType));//给顺序表elem分配
    Lists.elem[j].L.length = 0;
    Lists.elem[j].L.listsize = 10;

    j++;
    return OK;
    //多出的空格在于前面遍历线性表题目
    /********** End **********/
}

status RemoveList(LISTS& Lists, char ListName[])
// 16.Lists中删除一个名称为ListName的线性表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j;
    int flag = 1;

    for (i = 0; i < Lists.length; i++) {
        flag = 1;
        for (j = 0; ListName[j]; j++) {
            if (Lists.elem[i].name[j] != ListName[j]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            //printf("%d\n",114514);
            break;
        }//此时i对应的List.elem[i]就是要删除的 ListName[];
    //if(!flag)printf("%d\n",11121);

    }

    if (flag) {
        int k;

        for (k = i; k < Lists.length; k++) {
            Lists.elem[i] = Lists.elem[i + 1];//将要删除的用后一个覆盖掉;
        }
        Lists.length--;//删除后长度-1
        return OK;
    }
    return ERROR;

    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
// 17.在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int i, j;
    int flag = 1;
    for (i = 0; i < Lists.length; i++) {
        flag = 1;
        for (j = 0; ListName[j]; j++) {
            if (ListName[j] != Lists.elem[i].name[j]) {
                flag = 0;
                break;
            }
        }
        if (flag)break;
    }
    if (flag)return i + 1;
    else return 0;

}

//18.找出一个具有最大和的连续子数组（子数组最少包含一个元素），操作结果是其最大和； 
int MaxSubArray(int* nums, int numsSize) {  
    // 检查 nums 是否存在且 numsSize 大于 0  
    if (nums == NULL || numsSize <= 0) {    
        printf("Error: nums is NULL or numsSize is 0\n");  
        return INFEASIBLE;  
    }  
  
    int dp[numsSize];  
    dp[0] = nums[0];   
    for (int i = 1; i < numsSize; i++) {  
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);  
    }  
    int maxSum = dp[0];  
    for (int i = 1; i < numsSize; i++) {  
        maxSum = max(maxSum, dp[i]);  
    }  
    return maxSum;  
} 
//19该数组中和为k的连续子数组的个数
int subarraySum(int* nums, int numsSize, int k){
    int sum=0;
    int key=0;
    for(int i=0;i<numsSize;i++)
    {
        sum=nums[i];
        if(sum==k)
        {
            key++;
        }
        for(int j=i+1;j<numsSize;j++)
        {
            sum+=nums[j];
            if(sum==k)
            {
                key++;
            }
        }
    }
    return key;
}

//20排序
void bubble_sort(int *a,int n)
{
	int i,j,temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
 
		}
	}
}
