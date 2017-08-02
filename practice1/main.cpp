#include"study.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	//�������� 
	bool flag=true;
	char InputOrder[20];
	char StudyClass[20];
	int StartTime=0,EndTime=0;
	int count=0,y=0,m=0,d=0;
	
	//�����ļ�
	flag=file.OpenDisposition();
	if(flag)
	{
		//��ȡ�ļ�
		flag=file.OpenStore();
		if(flag)
		{
			//�û�����ָ�� 
			while(1)
			{
				cout<<"��������ִ�еĲ���:"<<endl; 
				cin>>InputOrder;
				
				//������� 
				if(strcmp(InputOrder,"-TaskInput")==0)
				{
					cin>>StudyClass>>count>>y>>m>>d;
					hash.input(StudyClass,count,y,m,d);
					hash.review(StudyClass,count,y,m,d);
				}
				
				//��ѯ���� 
				else if(strcmp(InputOrder,"-TaskQuery")==0)
				{
					cin>>StartTime;
					hash.query(StartTime);
				}
				
				//ͳ�Ʋ��� 
				else if(strcmp(InputOrder,"-TaskCollect")==0)
				{
					cin>>StartTime>>EndTime;
					hash.collect(StartTime,EndTime);
				}
				
				//�˳����� 
				else if(strcmp(InputOrder,"-Quit")==0)
				{
					break;
				}
				
				//�쳣ָ�� 
				else
				{
					cout<<InputOrder<<"������Ч��ָ��"<<endl; 
				}
			}
		}
	}
	
	//�������
	hash.clear();
		
	//�رն�д�ļ� 
	if(file.fp)
	{
		fclose(file.fp);
	}
	
	return 0;
}