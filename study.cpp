// study.cpp: implementation of the study class.
//
//////////////////////////////////////////////////////////////////////

#include"study.h"

using namespace std;

//ѧϰ�๹�캯��
study::study(int year,int month,int day,string name,int digit)
{
	this->year=year;
	this->month=month;
	this->day=day;
	this->name=name;
	this->digit=digit;
}

//�����๹�캯��
variable::variable()
{
	memset(StudyKind,0,sizeof(StudyKind));
    ContentLimit=NULL;
    ReviewTime=NULL;
    MaxKind=0;
}

//�����๹�캯��
List::List()
{
	last=NULL;
	next=NULL;
	other=NULL;
	date=0;
}

//hash�����๹�캯��
Hash::Hash()
{
	memset(HashTable,0,sizeof(HashTable));
	memset(tail,0,sizeof(tail));
}

variable vary;
File file;
Hash hash;

//�������
void Hash::clear()
{
	List *p=NULL;
	for(int i=0;i<499;i++)
	{
		if(hash.tail[i])
		{
			//�����ͻ����
			p=hash.HashTable[i];
			p=p->other;
			while(p)
			{
				delete p;
				p=p->next;
			}

			//�������������
			p=hash.HashTable[i];
			p=p->next;
			while(p)
			{
				delete p;
				p=p->next;
			}
		}
	}
}

//���뺯�� 
void Hash::input(char c[],int count,int year,int month,int day)
{
	//��������
	int i=0,sum=0;
	int InvertDate=vary.invert(year,month,day);
	int index=hash.HashValue(InvertDate);
	string str=c; 
	
	//Ѱ�������ѧϰ���Ͷ�Ӧ��ţ��Ա��ҳ����� 
	while(strcmp(c,vary.StudyKind[i])!=0)
	{
		i++;
	}

	//�ж�hash���Ƿ�Ϊ��
	if(hash.tail[index]!=0)
	{
		List *p=new List;
		p=hash.HashTable[index];

		//ͳ�ƴ���ѧϰ���͵����ѧϰ��
		while(p)
		{
			if(p->stu.name==str)
			{
				sum+=p->stu.digit;
				p=p->next;
			}
			else if(p->other->stu.name==str)
			{
				sum+=p->other->stu.digit;
				p=p->other->next;
			}
			else
			{
				p=p->other;
			}
		}
		
		//�ж��Ƿ�������
		if(vary.ContentLimit[i]>=0)
		{
			//�ж��Ƿ�������� 
			if((sum+count)>vary.ContentLimit[i])
			{
				cout<<"���棺����ѧϰ������!"<<endl;
				
				//����ѧϰʱ��Ľ���
				int HashIndex=hash.HashValue(++InvertDate);
				while(hash.tail[HashIndex])
				{
					if(hash.tail[HashIndex]->date==InvertDate)
					{
						List *q=new List;
						q->date=InvertDate;
						q->stu.name=str;
						q->stu.digit=count;
						q->last=hash.tail[HashIndex];
						hash.tail[HashIndex]=q;
						break;
					}
					else
					{
						HashIndex=hash.HashValue(++InvertDate);
					}
				}
				if(hash.tail[HashIndex]==0)
				{
					List *q=new List;
					q->date=InvertDate;
					q->stu.name=str;
					q->stu.digit=count;
					q->last=hash.HashTable[HashIndex];
					hash.HashTable[HashIndex]=q;
					hash.tail[HashIndex]=q;
				}
				fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
				cout<<"������"<<InvertDate<<"��ѧϰ������"<<endl;
			}

			//���������޵����
			else
			{
				p=hash.HashTable[index];
				while(p)
				{
					if(p->date==InvertDate)
					{
						List *q=new List;
						q->date=InvertDate;
						q->stu.name=str;
						q->stu.digit=count;
						q->last=hash.tail[index];
						hash.tail[index]=q;
						break;
					}
					else if(p->other->date==InvertDate)
					{
						p=p->other;
						while(p->next){};
						List *q=new List;
						q->date=InvertDate;
						q->stu.name=str;
						q->stu.digit=count;
						q->last=p;
						p->next=q;
					}
					else
					{
						p=p->other;
					}
				}
				fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
			}
		}

		//�����޵����
		else
		{
			p=hash.HashTable[index];
			while(p)
			{
				if(p->date==InvertDate)
				{
					List *q=new List;
					q->date=InvertDate;
					q->stu.name=str;
					q->stu.digit=count;
					q->last=hash.tail[index];
					hash.tail[index]=q;
					break;
				}
				else if(p->other->date==InvertDate)
				{
					p=p->other;
					while(p->next){};
					List *q=new List;
					q->date=InvertDate;
					q->stu.name=str;
					q->stu.digit=count;
					q->last=p;
					p->next=q;
				}
				else
				{
					p=p->other;
				}
			}
			fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
		}
	}

	//hash��Ϊ��
	else
	{
		List *q=new List;
		q->date=InvertDate;
		q->stu.name=str;
		q->stu.digit=count;
		hash.HashTable[index]=q;
		q->last=hash.HashTable[index];
		hash.tail[index]=q;
		fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
	}
}

//��ѯ���� 
void Hash::query(int InputDate)
{
	int index=hash.HashValue(InputDate);
	bool flag=false;
	List *p=new List;
	p=hash.HashTable[index];
	while(p)
	{
		if(p->date==index)
		{
			while(p)
			{
				cout<<p->stu.name<<" "<<p->stu.digit<<endl;
				p=p->next;
			}
			flag=true;
		}
		else if(p->other->date==InputDate)
		{
			p=p->other;
			while(p)
			{
				cout<<p->stu.name<<" "<<p->stu.digit<<endl;
				p=p->next;
			}
			flag=true;
		}
		else
		{
			p=p->other;
		}
	}
	if(!flag)
	{
		cout<<"��ʱ���޸�ϰ���ݣ������������ݻ��������ʽ"<<endl;
	}
}

//ͳ�ƺ��� 
void Hash::collect(int StartDate,int EndDate)
{
	//��ʱ��ת��Ϊ�����ո�ʽ
	int year1=StartDate/10000;
	StartDate%=10000;
	int month1=StartDate/100;
	StartDate%=100;
	int day1=StartDate;
	List *p=new List;
	int *count=new int[10];
	bool flag=false;
	memset(count,0,sizeof(count));
	//��ѧϰ����ת��Ϊstring
	string *str=new string[10];
	for(int i=0;i<vary.MaxKind;i++)
	{
		str[i]=vary.StudyKind[i];
	}
	
	//ͳ��ÿ�����͵�ѧϰ��
	for(i=StartDate;i<=EndDate;day1++)
	{
		study stu=vary.isover("judge",0,year1,month1,day1);
		i=vary.invert(stu.year,stu.month,stu.day);
		int index=hash.HashValue(i);
		p=hash.HashTable[index];
		if(hash.tail[index])
		{
			while(p)
			{
				if(p->date==i)
				{
					while(p)
					{
						for(int j=0;j<vary.MaxKind;j++)
						{
							if(str[j]==p->stu.name)
							{
								count[j]+=p->stu.digit;
								flag=true;
							}
						}
						p=p->next;
					}
					break;
				}
				else if(p->other->date==i)
				{
					p=p->other;
					while(p)
					{
						for(int j=0;j<vary.MaxKind;j++)
						{
							if(str[j]==p->stu.name)
							{
								count[j]+=p->stu.digit;
								flag=true;
							}
						}
						p=p->next;
					}
					break;
				}
				else
				{
					p=p->other;
				}
			}
		}
	}
	
	//���ÿ�����͵�ѧϰ��
	if(flag){
		for(i=0;i<vary.MaxKind;i++)
		{
			cout<<str[i]<<" "<<count[i]<<endl;
		}
	}
	else
	{
		cout<<"��ʱ����޸�ϰ���ݣ������������ݻ��������ʽ"<<endl;
	}

	//�ͷ��ڴ�ռ�
	delete [] count;
	delete [] str;
}

//���㸴ϰʱ�� 
void Hash::review(char c[],int count,int year,int month,int day)
{
	study s;
	int InvertDate=0,index=0;
	List *p=new List;
	for(int i=0;i<13;i++)
	{
		List *q=new List;
		day+=vary.ReviewTime[i];
		s=vary.isover(c,count,year,month,day);
		InvertDate=vary.invert(s.year,s.month,s.day);
		index=hash.HashValue(InvertDate);

		//����ϰʱ�����hash���� 
		p=hash.HashTable[index];

		//hash��Ϊ��
		if(hash.tail[index])
		{
			while(p)
			{
				if(p->date==InvertDate)
				{
					q->date=InvertDate;
					q->stu.name=s.name;
					q->stu.digit=s.digit;
					q->last=hash.tail[index];
					hash.tail[index]=q;
					break;
				}
				else if(p->other->date==InvertDate)
				{
					p=p->other;
					while(p->next){};
					q->date=InvertDate;
					q->stu.name=s.name;
					q->stu.digit=s.digit;
					q->last=p;
					p->next=q;
				}
				else
				{
					p=p->other;
				}
			}
			fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
		}

		//hash��Ϊ��
		else
		{
			q->date=index;
			q->stu.name=s.name;
			q->stu.digit=s.digit;
			hash.HashTable[index]=q;
			q->last=hash.HashTable[index];
			hash.tail[index]=q;
			fprintf(file.fp,"%d%s%d\n",InvertDate,c,count);
		}
	}
}

//hashģ����
int Hash::HashValue(int DateTime)
{
	return DateTime%499;
}

//�ж��Ƿ�������
bool variable::isyear(int year)
{
	if((year%4==0&&year%100!=0)||(year%400==0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//����ÿ�µ�������� 
int variable::maxday(int year,int month)
{
	int mday=0;
	if(isyear(year)&&month==2)
	{
		mday=29;
	}
	else
	{
		switch(month)
		{
			case 1:mday=31;break;
			case 2:mday=28;break;
			case 3:mday=31;break;
			case 4:mday=30;break;
			case 5:mday=31;break;
			case 6:mday=30;break;
			case 7:mday=31;break;
			case 8:mday=31;break;
			case 9:mday=30;break;
			case 10:mday=31;break;
			case 11:mday=30;break;
			case 12:mday=31;break;
		}
	}
	return mday;
}

//�ж��Ƿ񳬹�ÿ�µ�������� 
study variable::isover(char c[],int count,int year,int month,int day)
{
	int mday=0;
	string str=c;
	mday=vary.maxday(year,month);
	while(day>mday)
	{
		day-=mday;
		month++;
		if(month>12)
		{
			year++;
			month=1;
		}
		mday=vary.maxday(year,month);
	}
	study stu(year,month,day,str,count);
	return stu;
}

//ת�����ں���
int variable::invert(int year,int month,int day)
{
	int DateDigit=0;
	DateDigit=year*10000+month*100+day;
	return DateDigit;
}

//�����ļ�����
bool File::OpenDisposition()
{
	//��������
	vary.ContentLimit=new int[20];
	vary.ReviewTime=new int[13];
	char *optimition=new char[20];
	const int size=100;
	char line[size];

	//�������ļ� 
	char filename[]="�����ļ�.txt";
	FILE *filep=fopen(filename,"r");
	if(filep==NULL)
	{
		cout<<"open file failed"<<endl;
		return false;
	}
	
	//��ȡ�����ļ�
	while(!feof(filep))
	{
		char c=getc(filep);
		
		//����ע���� 
		if(c=='#')
		{
			fgets(line,size,filep);
		}
		
		//��ȡ��ϰʱ���� 
		else if(c=='!')
		{
			for(int i=0;i<13;i++)
			{
				fscanf(filep,"%d",&vary.ReviewTime[i]);
			}
			getc(filep);
		}
		
		//��ȡѧϰ���ͺ���Ӧѧϰ���� 
		else if(c=='*')
		{
			int i=0;
			fscanf(filep,"%s%d",vary.StudyKind[i],&vary.ContentLimit[i]);
			i++;
			getc(filep);
			while(getc(filep)=='*')
			{
				fscanf(filep,"%s%d",vary.StudyKind[i],&vary.ContentLimit[i]);
				i++;
				getc(filep);	
			}
			vary.MaxKind=i;
			getc(filep);
		}
		
		//��ȡ�Ż����� 
		else
		{
			fscanf(filep,"%s",optimition);
		}
	}

	//�ر������ļ� 
	if(filep)
	{
		fclose(filep);
	}

	//�ͷ��ڴ�ռ�
	delete [] optimition;

	return true;
}

//��ȡ�ļ�����
bool File::OpenStore()
{
	//�򿪶�ȡ�ļ�
	file.fp=fopen("study.txt","a+");
	if(file.fp==NULL)
	{
		cout<<"open file failed"<<endl;
		return false;
	}
	//��̬�����ڴ�
	const int size=100;
	int *amount=new int[size];
	int *StudyTime=new int [size];
	char StudyKind[size];

	//��ȡ����
	if(!feof(file.fp))
	{
		//��������
		int j=0,index=0;
		List *p=new List;

		//��ȡ����
		rewind(file.fp);
		while(!feof(file.fp))
		{
			fscanf(file.fp,"%d%s%d",&StudyTime[j],StudyKind[j],&amount[j]);
			j++;
			if(j>=100)
			{
				break;
			}
		}
		if(StudyTime[0]>0)
		{
			//�����ݼ���hash����
			for(int i=0;i<j;i++)
			{
				List *q=new List;
				index=hash.HashValue(StudyTime[j]);
				p=hash.HashTable[index];

				//hash��Ϊ��
				if(hash.tail[index])
				{
					while(p)
					{
						if(p->date==StudyTime[j])
						{
							q->date=StudyTime[j];
							q->stu.name=StudyKind[j];
							q->stu.digit=amount[j];
							q->last=hash.tail[index];
							hash.tail[index]=q;
							break;
						}
						else if(p->other->date==StudyTime[j])
						{
							p=p->other;
							while(p->next){};
							q->date=StudyTime[j];
							q->stu.name=StudyKind[j];
							q->stu.digit=amount[j];
							q->last=p;
							p->next=q;
						}
						else
						{
							p=p->other;
						}
					}
				}

				//hash��Ϊ��
				else
				{
					q->date=StudyTime[j];
					q->stu.name=StudyKind[j];
					q->stu.digit=amount[j];
					hash.HashTable[index]=q;
					q->last=hash.HashTable[index];
					hash.tail[index]=q;
				}
			}
		}
	}

	//�ͷ��ڴ�ռ�
	delete [] StudyTime;
	delete [] amount;

	return true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////