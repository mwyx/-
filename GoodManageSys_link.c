//-------------------------------------------------------------------
//˵������Ʒ����ϵͳ������ʵ�ֿ��
//ʱ�䣺2018.11.20
//������1. ����goodinfo.txt�������⣨�洢��Ʒ���ļ����������ģ�
//        MAC�²���UNICODE�޷���ȡ��utf-8�������룬GBK��ASCII��������������д
//        Windows�²���ANSII����洢������
//     2. visualstudio����fopen��һϵ���ļ�������������ȫ��������Ŀ-��
//        ����-��Ԥ������-��Ԥ���������崦����_CRT_SE  CURE_NO_WARNINGS
//����1. ���ƴ���//TO DO YOUR WORK�ĺ���
//     2. ���ݽṹ��ʵ�ַ�ʽ��������ʵ��
//     3. �ļ��Ķ�д�ο�fileIOreferrence����
//     4. ע�⴫����ָ��*L�ʹ�����ָ��ĵ�ַ**L������
//-------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//--------------------------------------------------------------------
//��Ʒ���������
//--------------------------------------------------------------------
#define MAX 100
//--------------------------------------------------------------------
//ȫ�ֱ������洢��ǰ��Ʒ������
//--------------------------------------------------------------------
int CurrentCnt = 0;
//--------------------------------------------------------------------
//��Ʒ��Ϣ�ṹ�Ķ���
//--------------------------------------------------------------------
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30
typedef struct
{
	char 	good_id[MAX_ID_LEN];
	char	good_name[MAX_NAME_LEN];
	int  	good_price;
	double	good_discount;
	int		good_amount;
	int		good_remain;
} GoodInfo;

//--------------------------------------------------------------------
//������Ʒ����Ľ��
//--------------------------------------------------------------------
typedef struct node
{
	GoodInfo data;
	struct node *next;
} GoodList;
bool qs(void)//ѯ���û��Ƿ�ȷ�ϲ��� 
{
	char temp;
	printf("�Ƿ�ȷ�ϸò�������Y/N) \n");
	while(1)
	{
		scanf("%c",&temp);
		if(temp=='Y'||temp=='y')return true;
		if(temp=='N'||temp=='n')return false; 
	}
}
//--------------------------------------------------------------------
//�����Ʒ�ļ��Ƿ���ڻ����Ƿ�Ϊ��
//--------------------------------------------------------------------
bool check_nullfile(void)//�ж�goodinfo.txt�Ƿ���ڣ����������½�һ��goodinfo.txt �������Ƿ����ļ� 
{
	FILE *fp = fopen("goodinfo.txt", "r");
	//file not exist
	if (!fp)
	{
		printf("��Ʒ��Ϣ��ʼ���ļ������ڣ�����Ϊ���½�һ��.\n");
		FILE *fp = fopen("goodinfo.txt", "w");
		fclose(fp);
		return false;
	}
	//file already exist
	else
	{
		int temp;
		//res for try to read file if file null feof() can't determine whether file is null or not
		int res = fscanf(fp, "%d", &temp);
		fclose(fp);
		if (res <= 0)
			return false;
		else
			return true;
	}
}
//-------------------------------------------------------------
//��ӡ������Ʒ����ڵ����Ϣ����ӡ��
//-------------------------------------------------------------
void Goodscanf(GoodList *init_)                              //��� ��Ʒ��׼����
{
	printf("��ƷID: ");
	scanf("%s",(init_->data.good_id));
	printf("��Ʒ����: ");
	scanf("%s",(init_->data.good_name));
	printf("��Ʒ�۸�: ") ;
	scanf("%d",&(init_->data.good_price));
	printf("��Ʒ�ۿ�: ") ;
	scanf("%lf",&(init_->data.good_discount));
	printf("��Ʒ����: ") ;
	scanf("%d",&(init_->data.good_amount));
	printf("��Ʒʣ��: ") ;
	scanf("%d",&(init_->data.good_remain));
}
void FGoodscanf(FILE *fp,GoodList *init_)                              //��� ��Ʒ�ļ�����
{
	fscanf(fp,"%s",(init_->data.good_id));
	fscanf(fp,"%s",(init_->data.good_name));
	fscanf(fp,"%d",&(init_->data.good_price));
	fscanf(fp,"%lf",&(init_->data.good_discount));
	fscanf(fp,"%d",&(init_->data.good_amount));
	fscanf(fp,"%d",&(init_->data.good_remain));
	fgetc(fp);fgetc(fp);
}
void Goodprint(GoodList *L)//                                          ���,��������ָ��λ��
{
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID:%s\t����:%s\t�۸�:%d \t�ۿ�:%.2lf\t����:%d\tʣ��:%d\n",
	       L->data.good_id,L->data.good_name,L->data.good_price,L->data.good_discount,L->data.good_amount,L->data.good_remain);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	/**
	 * 1.��ӡ����������Ʒ������Ϣ
	 */
	//TO DO YOUR WORK

	//    �����ʽ�ο���
	//    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//    printf("ID:%s\t����:%s\t�۸�:%s\t�ۿ�:%s\t����:%d\tʣ��:%d\n",
	//           ����������������);
	//    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
void FGoodprint(FILE *fp,GoodList *L)//                     ��Ʒ�ļ����            ���,�����ļ�ָ��������ָ��λ��
{
	fprintf(fp,"%s\t%s\t%d\t%.2lf\t%d\t%d\n",
	L->data.good_id,L->data.good_name,L->data.good_price,L->data.good_discount,L->data.good_amount,L->data.good_remain);
}
//--------------------------------------------------------------------
//�ͷ���Ʒ����
//--------------------------------------------------------------------
void DestroyGoods(GoodList *L)                                    // ��� ��������ͷ
{
	GoodList *p=L,*temp;
	temp=p;
	p=p->next;
	for(; p!=NULL; temp=p,p=p->next)free(temp);
	free(temp);
	/**
	 * 1.ʹ��free��������free��L�����нڵ�
	 */
}
//--------------------------------------------------------------------
//ɾ����Ʒ�ļ��Լ���Ʒ�����е�������Ϣ
//--------------------------------------------------------------------
void DelAll(GoodList **L)                                            //���  ��������ͷ
{
	DestroyGoods(*L);//�����Ʒ�����������еĽڵ㣬���½�һ��������ͷ
	*L=malloc(sizeof(GoodList));
	(*L)->next=NULL;
	FILE *fp;
	fp = fopen("goodinfo.txt", "w");//��մ洢��Ʒ���ݵ��ļ� 
	fclose(fp);
}

//--------------------------------------------------------------------
//��ȡ��Ʒ�ļ�goodinfo.txt������,����������L
//--------------------------------------------------------------------
void info_init(GoodList **L)                                      //��� ��������ͷ 
{
	FILE *fp;
	int cnt=0;
	bool flag=check_nullfile();
	GoodList *p,temp;
	if(flag==true)
	{
		fp=fopen("goodinfo.txt","r");
		(*L)->next=malloc(sizeof(GoodList));
		p=*L;
		FGoodscanf(fp,p->next);
		p=p->next;
		p->next=NULL;
		cnt++;
		while (!feof(fp))
		{
			cnt++;
			p->next=malloc(sizeof(GoodList));
			FGoodscanf(fp,p->next);
			p=p->next;
			p->next=NULL;
		}
		fclose(fp);
		printf("��Ʒ�������ļ��ѽ�������%d����Ʒ��¼\n", cnt);
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	else 
	{
		printf("\n��ǰ��Ʒ�б�Ϊ��\n");
	}
	/**
	* 1.�ж�goodinfo.txt�Ƿ���ڣ����������½�һ��goodinfo.txt
	* 2.��δ�ﵽ�ļ�β������£����ļ��ж�ȡ��Ʒ��Ϣ
	* 3.Ȼ���½�����
	* �ļ���Ϣ�Ķ�д�ɲ���fileIOreferrence����
	*/
}

//--------------------------------------------------------------------
//����ǰ��Ʒ�����е����ݴ�����Ʒ�ļ�goodinfo.txt�����̺���������L
//--------------------------------------------------------------------
void info_flush(GoodList **L)//                                  ��ɣ���������ͷ��ַ 
{
	GoodList *p=*L;
	FILE *fp;
	fp=fopen("goodinfo.txt","w");
	p=p->next;
	for(;p!=NULL;p=p->next)
	{
		FGoodprint(fp,p);
	}
	DelAll(L);
	fclose(fp);
	/**
	 * 1.����������д�뵽goodinfo.txt
	 * 2.��������
	 * 3.��Ʒ������0
	 * �ļ���Ϣ�Ķ�д�ɲ���fileIOreferrence����
	 */
	//TO DO YOUR WORK

	//    ������ݲο���
	//    if .... printf("��ʾ��%d����Ʒ��Ϣ����Goodinfo.txt�ļ�\n", savecount);
	//    else printf("��ʾ��δд���κ���Ʒ��Ϣ��Goodinfo.txt�ļ�\n");
}
//--------------------------------------------------------------------
//����Ļ�����������Ʒ��Ϣ
//--------------------------------------------------------------------
void OutputAll(GoodList *L)//                                         ���,��������ͷ
{
	int cnt=0;
	for(L=L->next;L!=NULL; L=L->next)
	{
		Goodprint(L);
		cnt++;
	}
	printf("һ����%d����Ʒ\n",cnt);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	/**
	* 1.�������������ݽ��ж�ȡ��Ȼ�������Ʒ��Ϣ
	*/
	//    �����ʽ�ο���
	//    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//    printf("ID:%s\t����:%s\t�۸�:%s\t�ۿ�:%s\t����:%d\tʣ��:%d\n",
	//           ����������������);
	//    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
bool IDsearch(char ID[],GoodList *L)//                               ��� ������Ʒid������ͷ 
{
	for(;L!=NULL;L=L->next)
		if(!strcmp(L->data.good_id,ID))return true;
	return false;
}
//--------------------------------------------------------------------
//���һ����Ʒ��¼
//--------------------------------------------------------------------
void info_insert(GoodList **L)//                                    ���  ��������ͷ
{
	GoodList *temp,*p,*new_p=malloc(sizeof(GoodList));
	int local_,flag=0;
	printf("������Ҫ�������Ʒ��Ϣ(����Ʒid����-1�˳�)\n");
	Goodscanf(new_p);
	if(!strcmp(new_p->data.good_id,"-1"))return;
	while(IDsearch(new_p->data.good_id,*L))
	{
		printf("�������ƷID�ظ���������������ƷID��");
		scanf("%s",(new_p->data.good_id));
	}
	printf("�������ֱ�����Ҫ�������Ʒλ�ã�\n");
	printf("0.��Ʒ����β��	1.��Ʒ����ͷ��	i.��Ʒ�����м��i��λ��\n"); 
	scanf("%d",&local_);//����λ�� 
	int cnt=0;
	new_p->next=NULL; 
	if(local_==1)//                                               ͷ���� 
	{
		new_p->next=(*L)->next;
		(*L)->next=new_p;
	}
	else if(local_==0)
	{
		p=*L;
		for(;p!=NULL;temp=p,p=p->next);
		temp->next=new_p;
	}
	else 
	{
		p=*L;
		for(;p!=NULL;temp=p,p=p->next)
		{
			cnt++;
			if(cnt==local_)
			{
				new_p->next=p->next;
				p->next=new_p;
				return;
			}
		}
		printf("�������Ʒλ�ò����ڣ��˳���Ʒ����\n");
		free(new_p);
	}
	/**
	 * 1.���������ĳһ����Ʒ����Ϣ������ID�����ơ��۸��ۿۡ�������ʣ��
	 * ע������ͨ��scanf()����������������Ʒ��Ϣ��ÿ�������Ի��з���������Ϣ�е�ÿ����Ŀ
	 *    �����С��Ʒ��Ϣ�ṹ����ڴ�ռ䣬Ȼ�󽫶�������ݷֱ𿽱����ѷ���õ����ڴ��У�
	 *    �����ַ����Ŀ�������ϵͳ����strcpy��
	 *    ���⣺����ʹ��ǰ���Զ����read_line�������������ݶ�ȡ
	 * 2.�ֱ�ʵ��ͷ�巨��β�巨���м�λ�ò������֣�
	 * 3.Ȼ������û�����Ĳ��뷽ʽ������Ӧ�Ľڵ�λ�ò���
	 * 4.��ѡ����ID���ڲ����ʱ����Ҫ���в��أ�����Ѿ��и�ID���ˣ���ʾ�ظ�
	 */ 
}

//--------------------------------------------------------------------
//����һ����Ʒ��¼
/**
 * 1.������Ʒ�����ƣ�������ƴ������ӡ��Ʒ��Ϣ
 * 2.�����Ʒ����������ʾ��Ʒ������
 */

//--------------------------------------------------------------------
GoodList * info_search(GoodList *L,char name_[])//  ��� ��������ͷ�������Ʒ�� ����ָ����ҽ���ָ��
{
	for(; L!=NULL; (L=L->next))
	{
		if(strcmp(L->data.good_name,name_)!=0&&strcmp(L->data.good_id,name_)!=0)continue;
		//��������б��������ȶ�ID������ 
		Goodprint(L);
		return L;
	}
	printf("��Ʒ������\n");
	return NULL;
	// TO DO YOUR WORK
}
//--------------------------------------------------------------------
//ɾ��һ����Ʒ��¼
/**
 * 1.������ɾ����Ʒ��Ϣ�����ͷŶ�Ӧָ����ָ����ڴ棬
 *   ���ҽ���ָ�븳ֵΪ�������һ��Ԫ�أ�Ȼ���ӡ��ɾ���ɹ�����ʾ��
 * 2.����������Ʒ���Ʋ������������Ʒ�����ڣ�
 */
//--------------------------------------------------------------------
void info_dele(GoodList **L)//                             ��ɴ�������ͷ����Ʒ�� 
{
	char name_[100];
	printf("����Ҫɾ������ƷID(������)(����-1�˳�): \n"); 
	scanf("%s",name_);
	if(!strcmp(name_,"-1"))return;
	GoodList *p,*temp;
	p=*L;
	for(; p!=NULL; temp=p,p=p->next)
	{
		if(strcmp(p->data.good_name,name_)!=0&&strcmp(p->data.good_id,name_))continue;
		Goodprint(p);
		if(!qs())return;
		if(temp==*L)(*L)->next=p->next;
		temp->next=p->next;
		free(p);
		printf("��Ʒ��Ϣɾ���ɹ�\n");
		return;
	}
	printf("��Ʒ������\n");
}
//--------------------------------------------------------------------
//�޸�һ����Ʒ��¼
//--------------------------------------------------------------------
void info_change(GoodList *L)                              //��� ��������ͷ����Ʒ�� 
{
	char name_[100];//�������ƻ���ID 
	printf("����Ҫ�޸ĵ���ƷID(������)(����-1�˳�): ");
	scanf("%s",name_);
	if(!strcmp(name_,"-1"))return;
	printf("��ǰ��Ʒ��ϢΪ: \n") ;
	GoodList *p=info_search(L,name_);
	if(p==NULL)
	{
		return;
	}
	Goodscanf(p);
	printf("��Ʒ��Ϣ�޸ĳɹ����޸ĺ����Ʒ��ϢΪ\n");
	Goodprint(p);
	/**
	* 1.������Ʒ�����ƣ�������ƴ������ӡ��Ʒ��Ϣ
	* 2.Ȼ���û������µ���Ʒ��Ϣ
	* 3.���Ҫ�޸ĵ���Ʒ���ڲ�����Ϣ���������������޸ĳɹ��������´�ӡ�����ѡ�����
	*/
	// TO DO YOUR WORK
}
//--------------------------------------------------------------------
//ð������ʵ�ֶ�����ڵ������
//--------------------------------------------------------------------
void bubble_sort(GoodList **L)
{
	bool flag=true;//�Ƿ�ִ�й�ð�� 
	GoodList *p=*L,*temp;
	while(flag==true)
	{
		p=*L;
		flag=false;
		temp=*L;
		p=p->next;
		for(;(p->next)!=NULL;temp=p,p=p->next)
		{
			if((temp->next->data.good_price)>(p->next->data.good_price))
			{
				temp->next=p->next;
				p->next=p->next->next;
				temp->next->next=p;
				//���������ڵ� 
				flag=true;
				p=temp;
			}
		}
	}
	/**
	* 1.����ð���������Ʒ����������򣬰��ռ۸�ӵ͵��߽�������
	* 2.Ȼ�������������Ʒ����
	*/
	// TO DO YOUR WORK
}
void menuout(void)
{
	printf("������Ʒ����ϵͳ" 
	"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
	"1.��ʾ������Ʒ����Ϣ:\n"
	"2.�޸�ĳ����Ʒ����Ϣ:\n"
	"3.����ĳ����Ʒ����Ϣ:\n"
	"4.ɾ��ĳ����Ʒ����Ϣ:\n"
	"5.����ĳ����Ʒ����Ϣ:\n"
	"6.��Ʒ���̲��˳�ϵͳ:\n"
	"7.����Ʒ�۸��������:\n"
	"8.(����)ɾ����������:\n"
	"����.�����̲��˳�ϵͳ:"
	"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
//--------------------------------------------------------------------
//������
//--------------------------------------------------------------------
int main()
{
	GoodList *head;
	char ch[100]; 
	char effect=' ';//��������
	int temp=0;
	head=malloc(sizeof(GoodList)); 
	head->next=NULL; 
	info_init(&head);
	while(1)
	{
		menuout();
		do scanf("%c",&effect);while(effect==' '||effect=='\n');
		temp=effect-'0';
		switch(effect-'0')
		{
			case 1:OutputAll(head);
			system("pause"); 
				break;
			case 2:
				info_change(head);
				break;
			case 3:
				info_insert(&head); 
				break;
			case 4:
				info_dele(&head);
				break;
			case 5:
				printf("������Ҫ���ҵ���ƷID���������ƣ�:");
				scanf("%s",ch);
				info_search(head,ch);
				system("pause");
				break;
			case 6:
				info_flush(&head);
				exit(0);
				break;
			case 7:bubble_sort(&head);
				break;
			case 8:
				DelAll(&head);
				info_flush(&head);
				exit(0); 
				break;
			default:exit(0);
		}
	}
	/**
	* 1.��ʼ��һ������
	* 2.ѭ����ʾ��Ʒ����ϵͳ�Ĳ���ѡ���б�
	* 3.�û�ѡ��������Ӧ�ĺ������д���������ɺ��ٶ���ʾϵͳѡ���б�
	* 4.���ѡ�񳬳��б�Χ����Ĭ���˳�ϵͳ�����̡�
	*/
	// TO DO YOUR WORK
	return 0;
}
