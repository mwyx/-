//-------------------------------------------------------------------
//说明：商品管理系统的链表实现框架
//时间：2018.11.20
//其他：1. 关于goodinfo.txt编码问题（存储商品的文件内容有中文）
//        MAC下测试UNICODE无法读取，utf-8中文乱码，GBK和ASCII可以中文正常读写
//        Windows下测试ANSII编码存储的正常
//     2. visualstudio报错fopen等一系列文件操作函数不安全，则在项目-》
//        属性-》预处理器-》预处理器定义处增加_CRT_SE  CURE_NO_WARNINGS
//任务：1. 完善带有//TO DO YOUR WORK的函数
//     2. 数据结构的实现方式采用链表实现
//     3. 文件的读写参考fileIOreferrence函数
//     4. 注意传链表指针*L和传链表指针的地址**L的区别
//-------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//--------------------------------------------------------------------
//商品的最大数量
//--------------------------------------------------------------------
#define MAX 100
//--------------------------------------------------------------------
//全局变量，存储当前商品的数量
//--------------------------------------------------------------------
int CurrentCnt = 0;
//--------------------------------------------------------------------
//商品信息结构的定义
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
//定义商品链表的结点
//--------------------------------------------------------------------
typedef struct node
{
	GoodInfo data;
	struct node *next;
} GoodList;
bool qs(void)//询问用户是否确认操作 
{
	char temp;
	printf("是否确认该操作？（Y/N) \n");
	while(1)
	{
		scanf("%c",&temp);
		if(temp=='Y'||temp=='y')return true;
		if(temp=='N'||temp=='n')return false; 
	}
}
//--------------------------------------------------------------------
//检查商品文件是否存在或者是否为空
//--------------------------------------------------------------------
bool check_nullfile(void)//判断goodinfo.txt是否存在，不存在则新建一个goodinfo.txt 返回其是否有文件 
{
	FILE *fp = fopen("goodinfo.txt", "r");
	//file not exist
	if (!fp)
	{
		printf("商品信息初始化文件不存在！程序将为您新建一个.\n");
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
//打印单个商品链表节点的信息（打印）
//-------------------------------------------------------------
void Goodscanf(GoodList *init_)                              //完成 商品标准输入
{
	printf("商品ID: ");
	scanf("%s",(init_->data.good_id));
	printf("商品名称: ");
	scanf("%s",(init_->data.good_name));
	printf("商品价格: ") ;
	scanf("%d",&(init_->data.good_price));
	printf("商品折扣: ") ;
	scanf("%lf",&(init_->data.good_discount));
	printf("商品数量: ") ;
	scanf("%d",&(init_->data.good_amount));
	printf("商品剩余: ") ;
	scanf("%d",&(init_->data.good_remain));
}
void FGoodscanf(FILE *fp,GoodList *init_)                              //完成 商品文件输入
{
	fscanf(fp,"%s",(init_->data.good_id));
	fscanf(fp,"%s",(init_->data.good_name));
	fscanf(fp,"%d",&(init_->data.good_price));
	fscanf(fp,"%lf",&(init_->data.good_discount));
	fscanf(fp,"%d",&(init_->data.good_amount));
	fscanf(fp,"%d",&(init_->data.good_remain));
	fgetc(fp);fgetc(fp);
}
void Goodprint(GoodList *L)//                                          完成,传入链表指针位置
{
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID:%s\t名称:%s\t价格:%d \t折扣:%.2lf\t数量:%d\t剩余:%d\n",
	       L->data.good_id,L->data.good_name,L->data.good_price,L->data.good_discount,L->data.good_amount,L->data.good_remain);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	/**
	 * 1.打印单个链表商品结点的信息
	 */
	//TO DO YOUR WORK

	//    输出格式参考：
	//    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//    printf("ID:%s\t名称:%s\t价格:%s\t折扣:%s\t数量:%d\t剩余:%d\n",
	//           ……………………);
	//    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
void FGoodprint(FILE *fp,GoodList *L)//                     商品文件输出            完成,传入文件指针与链表指针位置
{
	fprintf(fp,"%s\t%s\t%d\t%.2lf\t%d\t%d\n",
	L->data.good_id,L->data.good_name,L->data.good_price,L->data.good_discount,L->data.good_amount,L->data.good_remain);
}
//--------------------------------------------------------------------
//释放商品链表
//--------------------------------------------------------------------
void DestroyGoods(GoodList *L)                                    // 完成 传入链表头
{
	GoodList *p=L,*temp;
	temp=p;
	p=p->next;
	for(; p!=NULL; temp=p,p=p->next)free(temp);
	free(temp);
	/**
	 * 1.使用free函数依次free掉L的所有节点
	 */
}
//--------------------------------------------------------------------
//删除商品文件以及商品链表中的所有信息
//--------------------------------------------------------------------
void DelAll(GoodList **L)                                            //完成  传入链表头
{
	DestroyGoods(*L);//清空商品链表，销毁已有的节点，并新建一个空链表头
	*L=malloc(sizeof(GoodList));
	(*L)->next=NULL;
	FILE *fp;
	fp = fopen("goodinfo.txt", "w");//清空存储商品内容的文件 
	fclose(fp);
}

//--------------------------------------------------------------------
//读取商品文件goodinfo.txt的内容,并建立链表L
//--------------------------------------------------------------------
void info_init(GoodList **L)                                      //完成 传入链表头 
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
		printf("商品的链表文件已建立，有%d个商品记录\n", cnt);
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	else 
	{
		printf("\n当前商品列表为空\n");
	}
	/**
	* 1.判断goodinfo.txt是否存在，不存在则新建一个goodinfo.txt
	* 2.在未达到文件尾的情况下，从文件中读取商品信息
	* 3.然后新建链表
	* 文件信息的读写可参照fileIOreferrence函数
	*/
}

//--------------------------------------------------------------------
//将当前商品链表中的内容存入商品文件goodinfo.txt，存盘后销毁链表L
//--------------------------------------------------------------------
void info_flush(GoodList **L)//                                  完成，传入链表头地址 
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
	 * 1.将链表内容写入到goodinfo.txt
	 * 2.销毁链表
	 * 3.商品数量置0
	 * 文件信息的读写可参照fileIOreferrence函数
	 */
	//TO DO YOUR WORK

	//    输出内容参考：
	//    if .... printf("提示：%d个商品信息存入Goodinfo.txt文件\n", savecount);
	//    else printf("提示：未写入任何商品信息到Goodinfo.txt文件\n");
}
//--------------------------------------------------------------------
//在屏幕上输出所有商品信息
//--------------------------------------------------------------------
void OutputAll(GoodList *L)//                                         完成,传入链表头
{
	int cnt=0;
	for(L=L->next;L!=NULL; L=L->next)
	{
		Goodprint(L);
		cnt++;
	}
	printf("一共有%d个商品\n",cnt);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	/**
	* 1.对所有链表内容进行读取，然后输出商品信息
	*/
	//    输出格式参考：
	//    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//    printf("ID:%s\t名称:%s\t价格:%s\t折扣:%s\t数量:%d\t剩余:%d\n",
	//           ……………………);
	//    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
bool IDsearch(char ID[],GoodList *L)//                               完成 传入商品id与链表头 
{
	for(;L!=NULL;L=L->next)
		if(!strcmp(L->data.good_id,ID))return true;
	return false;
}
//--------------------------------------------------------------------
//添加一条商品记录
//--------------------------------------------------------------------
void info_insert(GoodList **L)//                                    完成  传入链表头
{
	GoodList *temp,*p,*new_p=malloc(sizeof(GoodList));
	int local_,flag=0;
	printf("输入你要插入的商品信息(在商品id输入-1退出)\n");
	Goodscanf(new_p);
	if(!strcmp(new_p->data.good_id,"-1"))return;
	while(IDsearch(new_p->data.good_id,*L))
	{
		printf("输入的商品ID重复，请重新输入商品ID：");
		scanf("%s",(new_p->data.good_id));
	}
	printf("输入数字表明你要插入的商品位置：\n");
	printf("0.商品链表尾部	1.商品链表头部	i.商品链表中间第i号位置\n"); 
	scanf("%d",&local_);//插入位置 
	int cnt=0;
	new_p->next=NULL; 
	if(local_==1)//                                               头插入 
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
		printf("输入的商品位置不存在，退出商品插入\n");
		free(new_p);
	}
	/**
	 * 1.接收输入的某一条商品的信息，包括ID、名称、价格、折扣、数量、剩余
	 * 注：首先通过scanf()函数读入待插入的商品信息的每项数据以换行符来区分信息中的每个条目
	 *    分配大小商品信息结构体的内存空间，然后将读入的数据分别拷贝到已分配得到的内存中，
	 *    其中字符串的拷贝调用系统函数strcpy。
	 *    另外：可以使用前面自定义的read_line函数进行行数据读取
	 * 2.分别实现头插法、尾插法，中间位置插入三种，
	 * 3.然后根据用户输入的插入方式进行相应的节点位置插入
	 * 4.【选作】ID号在插入的时候需要进行查重，如果已经有该ID号了，提示重复
	 */ 
}

//--------------------------------------------------------------------
//查找一条商品记录
/**
 * 1.输入商品的名称，如果名称存在则打印商品信息
 * 2.如果商品不存在则提示商品不存在
 */

//--------------------------------------------------------------------
GoodList * info_search(GoodList *L,char name_[])//  完成 传入链表头与查找商品名 返回指向查找结点的指针
{
	for(; L!=NULL; (L=L->next))
	{
		if(strcmp(L->data.good_name,name_)!=0&&strcmp(L->data.good_id,name_)!=0)continue;
		//对链表进行遍历，并比对ID和名称 
		Goodprint(L);
		return L;
	}
	printf("商品不存在\n");
	return NULL;
	// TO DO YOUR WORK
}
//--------------------------------------------------------------------
//删除一条商品记录
/**
 * 1.存在则删除商品信息，即释放对应指针所指向的内存，
 *   并且将该指针赋值为链表的下一个元素，然后打印出删除成功的提示；
 * 2.如果输入的商品名称不存在则输出商品不存在；
 */
//--------------------------------------------------------------------
void info_dele(GoodList **L)//                             完成传入链表头与商品名 
{
	char name_[100];
	printf("输入要删除的商品ID(或名称)(输入-1退出): \n"); 
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
		printf("商品信息删除成功\n");
		return;
	}
	printf("商品不存在\n");
}
//--------------------------------------------------------------------
//修改一条商品记录
//--------------------------------------------------------------------
void info_change(GoodList *L)                              //完成 传入链表头与商品名 
{
	char name_[100];//储存名称或者ID 
	printf("输入要修改的商品ID(或名称)(输入-1退出): ");
	scanf("%s",name_);
	if(!strcmp(name_,"-1"))return;
	printf("当前商品信息为: \n") ;
	GoodList *p=info_search(L,name_);
	if(p==NULL)
	{
		return;
	}
	Goodscanf(p);
	printf("商品信息修改成功，修改后的商品信息为\n");
	Goodprint(p);
	/**
	* 1.输入商品的名称，如果名称存在则打印商品信息
	* 2.然后用户输入新的商品信息
	* 3.如果要修改的商品存在并且信息输入结束后则出现修改成功并且重新打印出软件选择界面
	*/
	// TO DO YOUR WORK
}
//--------------------------------------------------------------------
//冒泡排序实现对链表节点的排序
//--------------------------------------------------------------------
void bubble_sort(GoodList **L)
{
	bool flag=true;//是否执行过冒泡 
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
				//交换两个节点 
				flag=true;
				p=temp;
			}
		}
	}
	/**
	* 1.采用冒泡排序对商品链表进行排序，按照价格从低到高进行排序
	* 2.然后输出排序后的商品链表
	*/
	// TO DO YOUR WORK
}
void menuout(void)
{
	printf("超市商品管理系统" 
	"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
	"1.显示所有商品的信息:\n"
	"2.修改某个商品的信息:\n"
	"3.插入某个商品的信息:\n"
	"4.删除某个商品的信息:\n"
	"5.查找某个商品的信息:\n"
	"6.商品存盘并退出系统:\n"
	"7.对商品价格进行排序:\n"
	"8.(慎用)删除所有内容:\n"
	"其他.不存盘并退出系统:"
	"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
//--------------------------------------------------------------------
//主函数
//--------------------------------------------------------------------
int main()
{
	GoodList *head;
	char ch[100]; 
	char effect=' ';//操作输入
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
				printf("输入你要查找的商品ID（或者名称）:");
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
	* 1.初始化一个链表
	* 2.循环显示商品管理系统的操作选择列表
	* 3.用户选择后调用相应的函数进行处理，处理完成后再度显示系统选择列表
	* 4.如果选择超出列表范围，则默认退出系统不存盘。
	*/
	// TO DO YOUR WORK
	return 0;
}
