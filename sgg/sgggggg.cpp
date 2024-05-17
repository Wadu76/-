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
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
//static index=0;
#define LISTINCREMENT  10

typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;         //���Ա�� 
	int listsize;  //���Ա����ռ��С 
}SqList;
typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
     		  SqList L;
      } elem[10];
      int length;
  int listsize; //���Ա��Ϸ���Ŀռ� 10
 }LISTS;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status InitInput(SqList &L); //  ����Ԫ��  ѯ�ʳ�ʼ�����Ƿ���Ҫ�������Ա����� 
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); //�򻯹�
status PriorElem(SqList L,ElemType cur,ElemType&pre_e);
status NextElem(SqList L,ElemType cur,ElemType&next_e);
status ListInsert(SqList&L,int i,ElemType e);
status ListDelete(SqList&L,int i,ElemType& e);
status ListTraverse(SqList L);  //�򻯹�
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
        printf("    	  3. ClearList       13. SaveList(д���ļ�)\n");
        printf("    	  4. ListEmpty      14. LoadList\n");
        printf("    	  5. ListLength      15. AddList\n");
        printf("    	  6. GetElem       16.RemoveList\n");
        printf("          7. LocateElem     17.LocateList\n");
        printf("          8. PriorElem     18.MaxSubArray\n");
        printf("          9. NextElem     19.SubarraySum\n");
        printf("          10. ListInsert     20. SortList\n");
        printf("    	  21.MultiList		0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~21]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
        		//L.elem=NULL;
				j=InitList(L);
		    	if(j==OK){
					printf("���Ա����ɹ���\n");
						//InitInput(L);         
						}
				else if(j==ERROR)
					printf("���Ա���ʧ�ܣ�\n");                                                
				else if(j==INFEASIBLE)
					printf("���Ա��Ѵ��ڣ����ܽ������Ա��ʼ��������\n");

            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK)
                printf("\n���Ա����ٳɹ�\n");
            else if (DestroyList(L) == INFEASIBLE)
                printf("���Ա����ڣ����ܽ������Ա����ٲ�����\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK)
                printf("���Ա���ճɹ���\n");
            else
                printf("���Ա����ڣ����ܽ������Ա���ղ�����\n");
            getchar(); getchar();
            break;
        case 4:
            if (ListEmpty(L) == TRUE)
                printf("���Ա�Ϊ�գ�\n");
            else if (ListEmpty(L) == FALSE)
                printf("���Ա�Ϊ�գ�\n");
            else if (ListEmpty(L) == INFEASIBLE)
                printf("���Ա�����,���ܽ������Ա��пղ�����\n");
            getchar(); getchar();
            break;
        case 5:
            if (ListLength(L) >= 0)
                printf("���Ա���Ϊ %d ��\n", ListLength(L));
            else
                printf("���Ա����ڣ����������\n");
            getchar(); getchar();
            break;
        case 6:
            printf("���������Ԫ�ص�λ�ã�\n");
            scanf("%d", &i);
            j = GetElem(L, i, e);
            if (j == OK)
                printf("���Ա��е�%dλԪ����%d\n", i, e);
            else if (j == ERROR)
                printf("��ѡ���Ԫ��λ�ò��Ϸ�������С��1��������Ա��ȣ�\n");
            getchar(); getchar();
            break;
        case 7:
            printf("������Ҫ���ҵĲ���Ԫ�أ�\n");
            scanf("%d", &e);
            j = LocateElem(L, e);
            if (j > 0)
                printf("Ҫ���ҵ�Ԫ�� %d �����Ա��еĵ� %d λ��\n", e, j);
            else if (j == ERROR)
                printf("����Ԫ��ʧ�ܣ���Ԫ�ز������Ա��У�\n");
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ����ܽ���Ԫ�ز��ң�\n");
            getchar(); getchar();
            break;
        case 8:
            printf("�����������Ԫ���Ի�ȡ��ǰ��Ԫ�أ�\n");
            scanf("%d", &e);
            j = PriorElem(L, e, pre);
            if (j == OK)
                printf("Ԫ�� %d ��ǰ��Ԫ���� %d ��\n", e, pre);
            else if (j == ERROR)
                printf("Ԫ�� %d û��ǰ��Ԫ�أ���Ԫ���ڱ�ͷ���߸�Ԫ�ز��ڱ��У���\n", e);
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");
            getchar(); getchar();
            break;
        case 9:
            printf("������Ҫ����Ԫ���Ի�ȡ����Ԫ�أ�\n");
            scanf("%d", &e);
            j = NextElem(L, e, next);
            if (j == OK)
                printf("��Ԫ�� %d �ĺ��Ԫ���� %d ��\n", e, next);
            else if (j == ERROR)
                printf("��Ԫ�� %d û�к��Ԫ�أ���Ԫ���ڱ�β���߸�Ԫ�ز��ڱ��У���\n", e);
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");
            getchar(); getchar();
            break;
        case 10:
            printf("�����������Ԫ�أ�\n");
            scanf("%d", &e);
            printf("���������λ�ú�һ��Ԫ����ţ�\n");
            scanf("%d", &i);
            j = ListInsert(L, i, e);
            if (j == OK)
                printf("����Ԫ�سɹ���\n");
            else if (j == ERROR)
                printf("����λ�ò�׼ȷ;iֵ���Ϸ���\n");
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ����ܽ��в��������\n");
            getchar(); getchar();
            break;
        case 11:
            printf("��������Ҫɾ����Ԫ�ص�λ�ã�\n");
            scanf("%d", &i);
            j = ListDelete(L, i, e);
            if (j == OK)
                printf("ɾ��Ԫ�سɹ�����ɾ��Ԫ��Ϊ %d ��\n", e);
            else if (j == ERROR)
                printf("ɾ��λ�ò���ȷ��\n");
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ����ܽ���ɾ��������\n");
            getchar(); getchar();
            break;
        case 12:
            j = ListTraverse(L);
            if (j == OK)
                printf("\n���Ա�����ɹ���\n");
            else if (j == ERROR)
                printf("\n���Ա����ǿձ���Ԫ�أ�\n");
            else if (j == INFEASIBLE)
                printf("\n���Ա����ڣ�\n");
            if (!j) printf("���Ա��ǿձ�\n");
            getchar(); getchar();
            break;
        case 13:
            printf("������������ļ����ƣ�\n");
            scanf("%s", FileName);
            j = SaveList(L, FileName);
            if (j == OK)
                printf("���Ա��������ѳɹ�д��ָ���ļ��У�\n");
            else if (j == INFEASIBLE)
                printf("���Ա����ڣ�\n");
            getchar(); getchar();
            break;


        

		case 14:
            printf("\t���ڽ�FileName�ļ������ݶ������Ա�L�У�������FileName�ļ�����");
            scanf("%s", FileName);
            L.elem=NULL;
            if (LoadList(L, FileName) == OK)
                printf("\t�ļ�����ɹ���\n");
            else if (LoadList(L, FileName) == INFEASIBLE)
                printf("\t�ļ�����ʧ�ܣ�����L�Ƿ���ա�\n");
            printf("\t�����������.\n");
            getchar();
            getchar();
            break;

        case 15:
            printf(" ������n�����Ա�n��ֵΪ��\n");
            scanf("%d", &n);
            while (n)
            {
                printf(" ���������Ա����ƣ�������Ԫ�أ���0��β��������0\n");
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
            printf("\n\n��ӡ�������Ա����£�\n ");
            for (n = 0; n < Lists.length; n++)
            {
                printf("          ��%d�����Ա�����Ϊ%s ", n + 1, Lists.elem[n].name);
                ListTraverse(Lists.elem[n].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
        case 16:
            printf("�������ɾ�����Ա����� \n");
            scanf("%s", ListName);
            j = RemoveList(Lists, ListName);
            if (j == ERROR)
                printf("ɾ��ʧ��,�޸����Ƶ����Ա�\n");
            else if (j == -1)
                printf("ɾ��ʧ�ܣ������Ա���Ϊ��\n");
            else
                printf("ɾ���ɹ�\n");
            printf("\n\n��ӡ�������Ա����£�\n ");
            for (n = 0; n < Lists.length; n++)
            {
                printf("          ��%d�����Ա�����Ϊ%s ", n + 1, Lists.elem[n].name);
                ListTraverse(Lists.elem[n].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
        case 17:
            if (Lists.length == 0)
            {
                printf("�����Ա�Ϊ��\n ");
            }
            printf("��������������Ա����� \n");
            scanf("%s", ListName);
            j = LocateList(Lists, ListName);
            if (!j)
                printf("���Ա������޸����Ƶ����Ա� \n\n");
            else if (j == -1)
                printf("���� �����Ա���Ϊ��\n\n");
            else
            {
                printf("�����Ա����Ϊ: %d \n", j);
                printf("          �����Ա�Ϊ����Ϊ%s ", Lists.elem[j - 1].name);
                ListTraverse(Lists.elem[j - 1].L);
                putchar('\n');
            }
            getchar(); getchar();
            break;
            
        case 18:
        	if(L.elem==NULL||L.listsize==0)printf("���ȳ�ʼ��һ�����Ա�");
			else{
			
			k18=MaxSubArray(L.elem, L.length);
            printf("����������֮��Ϊ��%d\n",k18);
        	}
            getchar();getchar();
            break;
        
        case 19:
        	if(L.elem==NULL||L.listsize==0)printf("���ȳ�ʼ��һ�����Ա�");
        	else{
        		printf("������Ҫ��Ϊ���������飺\n");
				scanf("%d", &k); 
        		k19=subarraySum(L.elem, L.length, k);
        		printf("��Ϊ%d����������%d��\n",k, k19);
			}
			getchar();getchar();
			break;
		
		case 20:
			if(L.elem==NULL||L.listsize==0)printf("���ȳ�ʼ��һ�����Ա�");
			else{
				bubble_sort(L.elem, L.length);
				printf("���Ա��Ѵ�С��������ã�\n");
			}
			getchar();getchar();
			break;
		case 21:
                printf("��ѡ����Ҫ�Ĳ�����\n");                             //ѡ�����
                printf("1. ������Ա�   2. �Ƴ����Ա�   3. �������Ա�   4.������Ա�����   5.��������\n");//ѡ�����
                scanf("%d",&j);                                             //�������
                switch(j){
                    case 1:
                        printf("���������Ա������:\n");                //�������Ա������
                        scanf("%s",ListName);                                          //�������Ա������
                        if(AddList(Lists,ListName)==OK)                                 //������Ա�
                            printf("��ӳɹ�\n");                                       //��ӳɹ�
                        else
                            printf("���ʧ��\n");                                       //���ʧ��
                        break;
                    case 2:
                        printf("���������Ա������:\n");    //�������Ա������
                        scanf("%s",ListName);                               //�������Ա������
                        if(RemoveList(Lists,ListName)==OK)                  //�Ƴ����Ա�
                            printf("�Ƴ��ɹ�\n");                           //�Ƴ��ɹ�
                        else
                            printf("�Ƴ�ʧ��\n");                           //�Ƴ�ʧ��
                        break;
                    case 3:
                        printf("���������Ա������:\n");                    //�������Ա������
                        scanf("%s",ListName);                               //�������Ա������
                        if(LocateList(Lists,ListName)!=0)                   //�������Ա�
                            printf("���Ա��λ��Ϊ%d\n",LocateList(Lists,ListName));//�������Ա�
                        else
                            printf("δ�ҵ����Ա�\n");                       //δ�ҵ����Ա�
                        break;                                              //����
                    case 4:
                        if(Lists.length==0){                                    //�ж����Ա������Ƿ�Ϊ��
                            printf("���Ա�����Ϊ��\n");                         //���Ա�����Ϊ��
                            break;                                              //����
                        }else{
                            for(int num=0;num<Lists.length;num++){              //�������Ա�����
                                printf("%d %s\n",num+1,Lists.elem[num].name);   //������Ա������
                            }
                        }
                        break;                                                  //����
                    case 5:
                        printf("���������Ա��λ��\n");
                        scanf("%d",&k);                                     //����λ��
                        if(k<=Lists.length){                                //�ж�λ���Ƿ����
                            L=Lists.elem[k-1].L;                            //�л����������Ա�
                            printf("�л��ɹ�\n");  //�л��ɹ�
                        }else
                            printf("�л�ʧ��\n");                           //�л�ʧ��
                        break;
                }
                printf("���س�����\n");                                     //��ʾ
                getchar();getchar();                                        //��ͣ
                break;

        case 0:
            break;
        default:printf("�Ƿ��ַ�ʹ��");
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()
status InitList(SqList& L){
    if(L.elem==NULL)
    {//ʹ��malloc����Ϊ˳����ٿռ䣬��ΪLIST_INIT_SIZE
        L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        if(L.elem==NULL)   return ERROR;
        L.length=0;
        L.listsize=LIST_INIT_SIZE;
		return OK;
    }
    else   
        return INFEASIBLE;	//���Ա��Ѵ��ڣ����ܹ���ձ�
}

status DestroyList(SqList& L)
// 2������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// 3.������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem) {
        L.length = 0;
        return OK;
    }
    else return INFEASIBLE;

    /********** End **********/
}

status ListEmpty(SqList L)
// 4.������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem == NULL)return INFEASIBLE;
    else {
        if (L.length == 0)return TRUE;
        else return FALSE;
    }

    /********** End **********/
}

status ListLength(SqList L)
// 5.������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/

    if (L.elem == NULL) return INFEASIBLE;
    else if (L.length)return L.length;
    /********** End **********/
}

status GetElem(SqList L, int i, ElemType& e)
// 6.������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// 7.������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //���һλ�鲻�� 
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
 ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// 8.������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK��
//���û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASTABLE��
{
    int i;
    if(L.elem)
    {
        for(i=1;i<L.length;i++)
        {//�������Ա�
            if(e==L.elem[i])
            {//���ҵ���ӦԪ�غ󣬷�����ǰ��Ԫ��
                pre=L.elem[i-1];
                return OK;
            }
        }
        return ERROR;	//������eԪ����ͬ�Ľ��ʧ��
    }
    else
        return INFEASIBLE;	//���Ա�����
}

status NextElem(SqList L, ElemType e, ElemType& next)
// 9.������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// 10.������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //����iλ�� ����Ϊi-1
    if (L.elem == NULL)return INFEASIBLE;//���Ա�����
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
// 11.������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// 12.������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    FILE *fp;
    int i=0;
	if(L.elem)
	{
		fp=fopen(FileName,"wb");
		if(!fp)	//�ļ���ʧ��
			return ERROR;
		while(i<L.length)
		{
			fprintf(fp,"%d ",L.elem[i]);	//�����Ա�������д���ļ�
			i++;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;	//���Ա�����
}

status  LoadList(SqList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	FILE *fp;
    int i=0; 
	if(L.elem)
		return INFEASIBLE;	//���Ա��Ѵ��ڣ�������ʹԪ��ʧȥ
	else
	{
		L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);	//��ʼ�����Ա�
        L.length=0;
       	L.listsize=LIST_INIT_SIZE;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			while((fscanf(fp,"%d ",&L.elem[i]))!=EOF)	//�ļ�δ��ȡ���
            {
                if(L.length<L.listsize-1)	//���Ա�δ����ֱ�Ӷ�������
                {
	                L.length++;
	                i++;
				}
				else	//���Ա����������·���ռ��ٶ�������
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
// 15.ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //˳���listsize=10
    static int  j = 0;
    int i;


    for (i = 0; ListName[i]; i++) {
        Lists.elem[j].name[i] = ListName[i];
    }
    Lists.elem[j].name[i] = '\0';
    Lists.length += 1;
    //˳���ĳ�ʼ��

    //InitList(Lists.elem[j].L.elem);
    //Lists.elem[j].L.listsize=10;

    Lists.elem[j].L.elem = (ElemType*)malloc(10 * sizeof(ElemType));//��˳���elem����
    Lists.elem[j].L.length = 0;
    Lists.elem[j].L.listsize = 10;

    j++;
    return OK;
    //����Ŀո�����ǰ��������Ա���Ŀ
    /********** End **********/
}

status RemoveList(LISTS& Lists, char ListName[])
// 16.Lists��ɾ��һ������ΪListName�����Ա�
{
    // �������ﲹ����룬��ɱ�������
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
        }//��ʱi��Ӧ��List.elem[i]����Ҫɾ���� ListName[];
    //if(!flag)printf("%d\n",11121);

    }

    if (flag) {
        int k;

        for (k = i; k < Lists.length; k++) {
            Lists.elem[i] = Lists.elem[i + 1];//��Ҫɾ�����ú�һ�����ǵ�;
        }
        Lists.length--;//ɾ���󳤶�-1
        return OK;
    }
    return ERROR;

    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
// 17.��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
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

//18.�ҳ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ�����������������ͣ� 
int MaxSubArray(int* nums, int numsSize) {  
    // ��� nums �Ƿ������ numsSize ���� 0  
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
//19�������к�Ϊk������������ĸ���
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

//20����
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
