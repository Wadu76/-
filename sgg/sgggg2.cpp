//Linear Table On Linked Storage Structure
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

//����Ԥ����
//״ֵ̬����󳤶ȵĺ궨��
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
#define FILENAME_LENGTH 30

//����״̬����ֵ���ͺ�����Ԫ������
typedef int status;
typedef int ElemType;

//��������ڵ�����
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node,*Linklist;

//��������Ա��ͷָ�빹�ɵ�����ڵ�����
typedef struct HeadNodePointer
{
	Linklist head;
	struct HeadNodePointer *next;
}HeadNodePointer,*HeadNodeList;//ָ��ÿһ������ 

//��������
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
	if(p->data!=e) return FALSE;		//���ýڵ�����Ԫ�ز�����e������FALSE
	else return OK;
}

int main(void)
{
	ElemType e;
	int i=0,op=1,condition=0;			//op=1��ѭ����ڣ�condition���շ��صĻ�ȡ״̬
	int n=0;
	Linklist L=NULL;					//L:������������ͷָ��

	HeadNodeList Head_L=NULL;			//Head_L:�����Ա��ͷָ�빹�ɵ�����
	Head_L=(HeadNodeList)malloc(sizeof(HeadNodePointer));	//Ϊ��ͷ�ڵ�����ڴ�ռ�
	Head_L->head=NULL;					//��ͷ�ڵ��������ÿ�
	Head_L->next=NULL;					//��ͷ�ڵ�ָ�����ÿ�

	while(op)							//case 0:op=0��ѭ�����ڣ�
	{
		//��ʾ�˵�����
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
		printf("    ��ѡ����Ĳ���[0~20]:");
		if(scanf("%d",&op)!=1) {fflush(stdin);op=18;}//����������֮����ַ�����ձ�׼������������ݣ�����op��Ϊdefault
		switch(op)
		{
		   case 1:
			 if(InitList(&L,Head_L)==OK) printf("���Ա����ɹ���\n");
			 else printf("���Ա���ʧ�ܣ�\n");
			 getchar();getchar();
			 //system("pause");
			 break;

		   case 2:
			 if(DestroyList(&L,Head_L)==OK) printf("�������Ա�ɹ���\n");
			 else printf("���Ա����ڣ������Ƿ���\n�������Ա�ʧ�ܣ�\n");
			 getchar();getchar();
			 break;

		   case 3:
			 if(ClearList(L)==OK) printf("������Ա�ɹ���\n");
			 getchar();getchar();
			 break;

		   case 4:
			 condition=ListEmpty(L);
			 if(condition==TRUE) printf("�����Ա��ǿձ�\n");
			 else if(condition==FALSE) printf("�����Ա��ǿձ�\n");
			 getchar();getchar();
			 break;

		   case 5:
			 condition=ListLength(L);
			 if(condition!=INFEASIBLE) printf("���Ա�ĳ�����: %d \n",condition);
			 getchar();getchar();
			 break;

		   case 6:
			 printf("����i����ȡ���Ա��е�i��1��i��%d��������Ԫ�ص�ֵ��",ListLength(L));
			 scanf("%d",&i);
			 condition=GetElem(L,i,&e);	
			 if(condition==ERROR) printf("����ʧ�ܣ������i�������㷶Χ 1��i��%d ��\n",ListLength(L));
			 else if(condition==OK) printf("���ҳɹ������Ա��е� %d ������Ԫ�ص�ֵ�� %d ��\n",i,e);
			 getchar();getchar();
			 break;

		   case 7:
			 printf("����e����ȡ����Ԫ��e�����Ա��е�λ�ã�") ;
			 scanf("%d",&e);
			 condition=LocateElem(L,e);
			 if(condition==0) printf("��ȡʧ�ܣ����Ա��в���������Ԫ�� %d ��\n",e);
			 else if(condition>=1) printf("��ȡ�ɹ�������Ԫ�� %d �����Ա��е�λ��Ϊ %d ��\n",e,condition);
			 getchar();getchar();
			 break;

		   case 8:
			 printf("����e����ȡ����Ԫ��e�����Ա��е�ǰ������Ԫ�أ�");
			 scanf("%d",&e);
			 condition=PriorElem(L,e,i);
			 if(condition==ERROR) printf("����ʧ�ܣ�����Ԫ�� %d ��ǰ���޶���\n",e);
			 else if(condition==OK) printf("�����ɹ�������Ԫ�� %d ��ǰ������Ԫ��Ϊ %d ��\n",e,i);
			 getchar();getchar();
			 break;

		   case 9:
			 printf("����e����ȡ����Ԫ��e�����Ա��еĺ������Ԫ�أ�");
			 scanf("%d",&e);
			 condition=NextElem(L,e,&i);
			 if(condition==ERROR) printf("����ʧ�ܣ�����Ԫ�� %d �ĺ���޶���\n",e);
			 else if(condition==OK) printf("�����ɹ�������Ԫ�� %d �ĺ������Ԫ��Ϊ %d ��\n",e,i);
			 getchar();getchar();
			 break;

		   case 10:
			 printf("�ֱ�����i��e���ڵ�i��1��i��%d����λ��֮ǰ�����µ�����Ԫ��e��",ListLength(L)+1);
			 scanf("%d%d",&i,&e);
			 condition=ListInsert(L,i,e);
			 if(condition==ERROR) printf("����ʧ�ܣ������i�������� 1��i��%d \n",ListLength(L)+1);
			 else if(condition==OK) printf("����ɹ���\n");
			 getchar();getchar();
			 break;

		   case 11:
			 printf("����i��ɾ����i��1��i��%d����λ�õ�����Ԫ�أ�",ListLength(L));
			 scanf("%d",&i);
			 condition=ListDelete(L,i,&e);
			 if(condition==ERROR)
				 printf("ɾ��ʧ�ܣ������ i �������� 1��i��%d ��\n",ListLength(L));
			 else if(condition==OK) printf("ɾ�����Ա�� %d ��λ�õ�����Ԫ�� %d �ɹ���\n",i,e);
			 getchar();getchar();
			 break;

		   case 12:
			 if(ListTraverse(L,visit)==ERROR) printf("���Ա��ǿձ�\n");
			 getchar();getchar();
			 break;

		   case 13:
			 condition=CreatList(L);
			 if(condition==OK) {printf("�������Ա�ɹ���\n");ListTraverse(L,visit);}
			 else printf("�������Ա�ʧ�ܣ�\n");
			 getchar();getchar();
			 break;

		   case 14:
			 condition=SaveList(L);
			 if(condition==OK) printf("���Ա���ɹ���\n");
			 else if(condition==ERROR) printf("���Ա���ʧ�ܣ�\n");
			 getchar();getchar();
			 break;

		   case 15:
			 condition=LoadList(&L,Head_L);
			 if(condition==OK) {printf("��ȡ�����أ����Ա�ɹ���\n");ListTraverse(L,visit);}
			 else printf("��ȡ�����أ����Ա�ʧ�ܣ�\n");
			 getchar();getchar();
			 break;

		   case 16:
		   					//����תreverseList(L)
				condition=reverseList(L,L->next);
				if(condition==INFEASIBLE)printf("���Ա���δ����");
				else printf("�����ѳɹ���ת");
				
				getchar();getchar();
				break;


		   case 17:
				//ɾ������ĵ�����n����� RemoveNthFromEnd(L,n)
				printf("��������Ҫɾ���ĵ�����n��Ԫ����\n");
				scanf("%d", &n);
				
				condition=DeleteNthFromEnd(L,n);
				if(condition==INFEASIBLE)printf("���Ա���δ������ɾ��ʧ�ܣ�");
				else printf("ɾ���ɹ���");		   	
		   		
				

			
			case 18:
				//�������򣺺���������sortList(L)��С����
				condition=ListSort(L);
				if(condition==INFEASIBLE)printf("���Ա����δ������");
				else printf("��С��������ɹ���");
				getchar();getchar();
				break;

			
			case 19:
				condition=CreatAnotherList (&L,Head_L);
				if(condition==OK) printf("�������Ա�ɹ���\n");
				else printf("�������Ա�ʧ�ܣ�\n");
				getchar();getchar();
				break;
			
			
			case 20:
				condition=ChooseList(&L,Head_L);
				if(condition==OK) printf("ѡ�����Ա�ɹ���\n");
				else printf("ѡ�����Ա�ʧ�ܣ�\n");
				getchar();getchar();
				break;
				
				
			case 21://test
				ListTraversetest(L);	
				getchar();getchar();
		   case 0:
			 break;

		   default:
			 printf("������Ч���˵�����ѡ��ʧ�ܣ�\n");
			 system("pause");
			 break;

		}//end of switch

	}//end of while

	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");

	return 0;
}//end of main()

status ListTraversetest(Linklist L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if (!L)
    {
        return INFEASIBLE;
    }
    else
    {
        Linklist p;
        p=L;
        if(!p->next) printf("�ǿձ�"); 
        while(p->next)
        {
            p=p->next;
            if(p->next) printf("%d ",p->data);
            if(!p->next) printf("%d",p->data);
        }
        return OK;
    }
}

//��ʼ��������ʼ���������Ա�L�Ѵ��ڣ���������ǹ���һ�����б�ͷ�ڵ�Ŀ�����
status InitList(Linklist *L,HeadNodeList Head_L)
{
	HeadNodePointer *p=Head_L;
	if((*L)!=NULL) {printf("���ܶ�γ�ʼ��һ�����Ա�\n");return ERROR;}
	*L=(Linklist)malloc(sizeof(Node));		//Lָ��ָ�����malloc����Ϊ��ͷ�ڵ㶯̬������ڴ�ռ��ַ
	//if(!*L) exit(OVERFLOW);					//if(*L==NULL) exit(OVERFLOW);
	(*L)->data=0;							//��ʼ�������ȣ�ͷָ������������ڴ洢������
	(*L)->next=NULL;						//ͷָ���ָ�����ÿգ�ͷָ���ָ�������ڴ洢������Ԫ�ڵ�ĵ�ַ
	while(p->next!=NULL) p=p->next;			//��������β
	p->next=(HeadNodePointer *)malloc(sizeof(HeadNodePointer));			//Ϊ�ڵ����ռ�
	p->next->head=(*L);						//������¼�����Ա��ͷָ��
	p->next->next=NULL;						//ָ�����ÿ�
	return OK;
}

//����������ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L��
status DestroyList(Linklist *L,HeadNodeList Head_L)
{
	Node *q=(*L),*pre_q=NULL;				//q���ӱ�ͷ�ڵ㿪ʼ��ָ��ǰ�������Ľڵ㣬pre_qָ��ǰ�ڵ�q��ǰһ�����
	HeadNodePointer *p=Head_L,*temp=NULL;
	if(*L==NULL) return ERROR;				//ERROR���������ڣ������Ƿ�
	while(p->next->head!=(*L)) p=p->next;	//�������������Ա��ͷָ��
	temp=p->next;							//��¼�����Ա��ͷָ�����ڵĽڵ�
	p->next=temp->next;						//�����Ա��ͷָ�����ڵĽڵ��������ɾ��
	free(temp);								//�ͷ����Ա��ͷָ�����ڵĽڵ�
	while(q!=NULL)							//�����������ͷų���ͷ�ڵ�֮������нڵ���ռ���ڴ�ռ�
	{
		pre_q=q;							//pre_q��¼�µ�ǰ�ڵ�
		q=q->next;							//qָ��ǰ�ڵ����һ���ڵ�
		free(pre_q);						//�ͷŵ�ǰ�ڵ�
	}
	*L=NULL;								//�������ͷָ�룩
	return OK;
}

//��ձ���ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
status ClearList(Linklist L)
{
	Node *q=NULL,*pre_q=NULL;				//pre_qָ��ǰ�ڵ�q��ǰһ�����
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return ERROR;}		//ERROR���������ڣ������Ƿ�
	q=L->next;								//q������Ԫ�ڵ��NULL��ʼ��ָ��ǰ�������Ľڵ�
	if(q==NULL) {printf("���Ա��ǿձ��������!\n");return ERROR;}		//ERROR�������ǿձ��������
	while(q!=NULL)							//�����������ͷų���ͷ�ڵ�֮������нڵ���ռ���ڴ�ռ�
	{
		pre_q=q;							//pre_q��¼�µ�ǰ�ڵ�
		q=q->next;							//qָ��ǰ�ڵ����һ���ڵ�
		free(pre_q);						//�ͷŵ�ǰ�ڵ�
	}
	L->data=0;								//ͷָ�������������
	L->next=NULL;							//ͷָ���ָ�����ÿ�
	return OK;
}

//�ж��ձ���ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE��
status ListEmpty(Linklist L)
{
	if(L==NULL) {printf("���Ա����ڡ�\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
	else return (L->next==NULL)?TRUE:FALSE;							//return (!L->data)?TRUE:FALSE;
}

//�������ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ�����
int ListLength(Linklist L)
{
	if(!L)return INFEASIBLE;
	Linklist p=L->next,q=NULL;
	int length=0;//�������Ԫ�س��� 
	
	while(p){
		length++;
		p=p->next;
	}//��¼�� 
	return length;
						//ͷָ������������ڴ洢������
}

//��ȡԪ�أ���ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ��
status GetElem(Linklist L,int i,ElemType *e)
{
	int num=1;
	Node *p=NULL;
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
	p=L->next;								//pָ����Ԫ�ڵ��NULL
	if(i<1||i>L->data) return ERROR;		//ERROR���������������
	while(num<i)							//�������ȡ���������ң�ֱ���ҵ���i������Ԫ��
	{
		p=p->next;							//pָ����һ������Ԫ��
		num++;
	}
	*e=p->data;								//ȡ����i������Ԫ�ص�ֵ
	return OK;
}

//����Ԫ�أ���ʼ���������Ա��Ѵ���
//��������Ƿ���L�е�1����e�����ϵcompare()��ϵ������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0��
/*status LocateElem(Linklist L,ElemType e,status (*compare)(Node *,ElemType))
{
	int num=1,find=FALSE;					//num���ڼ�¼����Ԫ��e��λ��,find���ڼ�¼�Ƿ��ѯ��������Ԫ��
	Node *p=NULL;
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
	p=L->next;								//pָ���ͷ�ڵ��nextָ��ָ��Ľڵ㣨��Ԫ�ڵ����NULL��
	while(p)								//�������ȡ���������ң�ֱ���ҵ�ֵΪ��e������Ԫ��
	{
		if(compare(p,e)==TRUE) {find=TRUE;break;}
		else {p=p->next;num++;}
	}
	return (find==TRUE)?num:0;				//�����ҵ���ͷ���Ҳ���ֵΪ��e������Ԫ�أ�����0
}*/
status LocateElem(Linklist L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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


//���ǰ������ʼ���������Ա�L�Ѵ���
//�����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶��塣
/*status PriorElem(Linklist L,ElemType e,ElemType &pre)
{
	Node *pre_q=NULL,*q=NULL;				//pre_qָ��ǰ�ڵ�q��ǰһ�����
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)�����Ա����ڣ������Ƿ�
	q=L->next;								//q������Ԫ�ڵ��NULL��ʼ��ָ��ǰ�������Ľڵ�
	while(q&&q->data!=e) {pre_q=q;q=q->next;}						//��������ֵΪ��cur������Ԫ��
	//���ҵ���ֵΪ��cur������Ԫ�أ��Ҹ�����Ԫ�ص�ǰ���ж��壬ȡ����ǰ����ֵ
	if(q!=NULL&&pre_q!=NULL) {pre=pre_q->data;return OK;}
	else return ERROR;						//ERROR��������ֵΪ��cur������Ԫ�أ��������Ԫ�ص�ǰ��û�ж���
}*/
status PriorElem(Linklist L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)return INFEASIBLE;
    else{
        Linklist p=L->next,q=L;
        int i=0;
        while(p){
            i++;
            if(p->data==e&&i!=1){//�˴�i��-1��ֹeΪ�׸�Ԫ��
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

//��ú�̣���ʼ���������Ա�L�Ѵ���
//�����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣��������ʧ�ܣ�next_e�޶��塣
status NextElem(Linklist L,ElemType cur,ElemType *next_e)
{
	Node *p=NULL;
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
	p=L->next;								//p������Ԫ�ڵ��NULL��ʼ��ָ��ǰ�������Ľڵ�
	while(p&&p->data!=cur) p=p->next;		//��������
	//���ҵ���ֵΪ��cur������Ԫ�أ��Ҹ�����Ԫ�صĺ���ж��壬ȡ�����̵�ֵ
	if(p!=NULL&&p->next!=NULL) {*next_e=p->next->data;return OK;}
	else return ERROR;						//ERROR��������ֵΪ��cur������Ԫ�أ��������Ԫ�صĺ��û�ж���
}

//����Ԫ�أ���ʼ���������Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1�������������L�ĵ�i��λ��֮ǰ�����µ�����Ԫ��e��
status ListInsert(Linklist L,int i,ElemType e)
{
	int num=1;								//num���ڼ�¼λ��
	Node *p=L,*q=NULL;						//pָ���ͷ�ڵ㣬qΪ�����ɵĽڵ�
	if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
	if(i<1||i>L->data+1) return ERROR;		//ERROR���������������
	while(num<i) {p=p->next;num++;}			//�������ȡ���������ҵ���i��λ�õ�ǰһ���ڵ�
	q=(Node *)malloc(sizeof(Node));			//Ϊ�½ڵ�����ڴ�ռ�
	if(q==NULL) exit(OVERFLOW);
	q->data=e;								//¼������Ԫ������
	q->next=p->next;						//�������
	p->next=q;
	L->data++;								//����Ԫ�صĸ�����һ
	return OK;
}

//ɾ��Ԫ�أ���ʼ���������Ա�L�Ѵ����ҷǿգ�1��i��ListLength(L)�����������ɾ��L�ĵ�i������Ԫ�أ���e������ֵ��
status ListDelete(Linklist L,int i,ElemType *e)
{
	int num=0;								//num���ڼ�¼λ��
	Node *p=L,*q=NULL;						//��pָ���ͷ�ڵ㣬qΪ��ɾ���Ľڵ�
	if(L==NULL||L->next==NULL) {printf("���Ա����ڻ����Ա�Ϊ�գ������Ƿ���\n");return -1;}
	if(i<1||i>L->data||L->data==0) return ERROR;					//ERROR��������ɾ������
	while(num<i-1) {p=p->next;num++;}		//�������ȡ���������ҵ���i���ڵ��ǰһ���ڵ�
	q=p->next;								//ɾ������
	p->next=q->next;
	*e=q->data;								//ȡ����ɾ��������Ԫ�ص�ֵ
	free(q);								//�ͷŽڵ���ռ���ڴ�ռ�
	L->data--;								//����Ԫ�صĸ�����һ
	return OK;
}

//��������ʼ���������Ա�L�Ѵ����ҷǿգ�������������ζ�L��ÿ������Ԫ�ص��ú���visit()��
status ListTraverse(Linklist L,status (visit)(Node *))
{
   Node *p=NULL;
   if(L==NULL) {printf("���Ա����ڣ������Ƿ���\n");return -1;}		//ERROR(-1)���������ڣ������Ƿ�
   if(L->next==NULL) return ERROR;									//ERROR�������ǿձ��������
   p=L->next;								//pָ����Ԫ�ڵ�
   //while(visit(p)!=INFEASTABLE) p=p->next;	//���ÿ���ڵ������Ԫ��
   while(p){
   		printf("%d ", p->data);
   		p=p->next;
   }
   printf("\n");
   return OK;
}

//����������ʼ���������Ա�L�������ѱ���ʼ������������Ǵ���һ�����б�ͷ�ڵ㣬���޳��ȵ�����
status CreatList(Linklist L)
{
	ElemType n;
	Node *p=NULL,*pre_p=L;					//p��ʾ�����ɵĽڵ㣬pre_pָ������һ���ڵ�
	if(L==NULL) {printf("���Ա�δ��ʼ����");return ERROR;}			//ERROR��δ��ʼ��
	printf("�������Ա�������1��ʼ 0Ϊ������ǵ�����Ԫ�أ�");
	scanf("%d", &n);
	if(n==1){
		scanf("%d", &n);
		while(n) 
		{
			
			p=(Node *)malloc(sizeof(Node));		//Ϊ�ڵ����ռ�
			//if(p==NULL) exit(OVERFLOW);			//OVERFLOW
			p->data=n;							//¼������Ԫ������
			pre_p->next=p;						//��������
			pre_p=p;
			L->data++;							//����Ԫ�ظ�����һ
			scanf("%d", &n);
		}
	}
	if(p!=NULL) p->next=NULL;
	return OK;
}

//����������ʼ���������Ա�L�������ѱ���ʼ������������ǽ�������洢��������ļ�·����ȥ��
status SaveList(Linklist L)
{
	char filename[FILENAME_LENGTH]={0};		//filename���ڴ洢������ļ�·��
	FILE *fp=NULL;							//�ļ�ָ��
	Node *p=NULL;
	if(L==NULL) {printf("���Ա�δ��ʼ����\n");return -1;}				//ERROR(-1)��δ��ʼ��
	p=L->next;
	printf("�����ļ�·��(����Ӧ��%d�ַ�����)�������Ա��浽���ļ��У�",FILENAME_LENGTH);
	scanf("%s",filename);
	fp=fopen(filename,"w");					//���ļ�
	if(fp==NULL) {printf("���ļ�����\n");return ERROR;}	//ERROR�����ļ�����
	while(p) {fprintf(fp,"%d ",p->data);p=p->next;}					//д���ļ�
	fclose(fp);								//�ر��ļ� 
	return OK;
}

//��ȡ��װ�أ�������ʼ�����������·���ļ��е�������������ʽ������
//��������ǽ������·���ļ��е�����װ�ص�������ȥ��
status LoadList(Linklist *L,HeadNodeList Head_L)
{
	char filename[FILENAME_LENGTH];			//filename���ڴ洢������ļ�·��
	FILE *fp=NULL;							//�ļ�ָ��
	ElemType n;								//n���ڶ�ȡ�ڵ��������
	Node *p=NULL,*pre_p=NULL;				//p��ʾ�����ɵĽڵ㣬pre_pָ������һ���ڵ�
	printf("�����ļ�·��(����Ӧ��%d�ַ�����)�������Ա��浽���ļ��У�",FILENAME_LENGTH);
	scanf("%s",filename);
	fp=fopen(filename,"r");					//���ļ�
	if(fp==NULL) {printf("���ļ�����\n");return ERROR;}
	(*L)=NULL;								//�������ͷָ���ָ��
	if(InitList(L,Head_L)==ERROR) exit(OVERFLOW);					//��ʼ�����Ա�
	pre_p=*L;
	while(fscanf(fp,"%d ",&n)!=EOF)
	{
		p=(Node *)malloc(sizeof(Node));		//Ϊ�ڵ����ռ�
		if(p==NULL) exit(OVERFLOW);			//OVERFLOW
		p->data=n;							//¼������Ԫ������
		pre_p->next=p;						//��������
		//pre_p����ƶ�����¼��ǰ��������һ���ڵ㣬Ҳ���Ǽ������ɵ��½ڵ��ǰһ�����
		pre_p=p;							
		(*L)->data++;						//����Ԫ�ظ�����һ
	}
	if(p!=NULL) p->next=NULL;				//���һ���ڵ��next��ֵΪNULL
	fclose(fp);								//�ر��ļ�
	return OK;
}

//����һ���µ����Ա���ʼ�������Ѿ���������һ�����Ա�
//��������Ǳ���ԭ�е����Ա��ͬʱ������һ���µ����Ա�
status CreatAnotherList(Linklist *L,HeadNodeList Head_L)
{
	Linklist AnotherList=NULL;
	if((*L)==NULL) {printf("�ȴ�����һ�����Ա��\n");return ERROR;}	
	if(InitList(&AnotherList,Head_L)==OK)
	{
		(*L)=AnotherList;					//��ʼ��ͷָ��
		printf("�µ����Ա����ɹ���\n");
	}
	else {printf("���Ա���ʧ�ܣ�\n");return ERROR;}					//ERROR:��ʼ��ʧ��
	if(CreatList(*L)==OK) return OK;		//�������Ա�
	else return ERROR;						//ERROR:����ʧ��
}

//ѡ�����Ա���ʼ�������Ѿ���������һ�����Ա�
status ChooseList(Linklist *L,HeadNodeList Head_L)
{
	int i=1,n;
	HeadNodePointer *p=Head_L->next;
	if(p==NULL) {printf("û�п�ѡ������Ա�\n");return ERROR;}		//ERROR:û�п�ѡ������Ա�
	while(p!=NULL)							//�������Ա�ͷָ������
	{
		printf("��%d�����Ա�",i);
		if(ListTraverse(p->head,visit)==ERROR) printf("\n");		//������������Ա����и�ʽ����
		p=p->next;
		i++;
	}
	printf("����n��ѡ���n�����Ա���в�����");
	scanf("%d",&n);
	if(n<1||n>=i) {printf("�����ڵ� %d �����Ա�\n",n);return ERROR;}	//ERROR��������󣬲����ڸ����Ա�
	i=1;
	p=Head_L->next;
	while(p!=NULL)							//�������Ա�ͷָ������
	{
		if(i==n) (*L)=p->head;
		p=p->next;
		i++;
	}
	if((*L)==NULL) return ERROR;
	else return OK;
}

//18����ת 
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

//19ɾ��������n��Ԫ��
status DeleteNthFromEnd(Linklist L, int n){
	if(!L)return INFEASIBLE;
	Linklist p=L->next,q=NULL;
	int length=0;//�������Ԫ�س��� 
	
	while(p){
		length++;
		p=p->next;
	}//��¼�� 
	
	p=L->next;
	q=L;
	for(int i=0;i<length-n;i++){
		q=p;
		p=p->next;
	}//��ʱpָ��Ҫɾ��Ԫ�أ�qָ��Ҫɾ��Ԫ�ص�ǰ����
	
	q->next=p->next;
	p->next=NULL;
	free(p);
	return OK;
} 

//20���� bubble
status ListSort(Linklist L){
	if(!L)return INFEASIBLE;
	Linklist p=L->next;
	int length=0;//�������Ԫ�س��� 
	
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
	//������� 
	for(int i=0;i<length-1;i++){
		for(int j=0;j<length-1-i;j++){
			if(a[j]>a[j+1]){
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
	}//ԭ����������ڴ˴�j<length-1-iû-1 
	
/*	int tem;
	for (i = 0; i < length-1;i ++)//size-1����Ϊ�������Լ��Ƚϣ����Աȵ�������һ��
	{
		int count = 0;
		for (j = 0; j < length-1 - i; j++)	//size-1-i����Ϊÿһ�˾ͻ���һ�����Ƚ�   
		{
			if (a[j] > a[j+1])//���������ŷ���ǰһ�����ͺ�һ�����Ƚϣ����ǰ���������һ������λ��
			{
				tem = a[j];
				a[j] = a[j+1];
				a[j+1] = tem;
				count = 1;
				
			}
		}
		if (count == 0)			//���ĳһ��û�н���λ�ã���˵���Ѿ��ź���ֱ���˳�ѭ��
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
