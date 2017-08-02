#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

typedef struct score{
	int id;
	char name[50];
	float chinese;
	float math;
	float english;
}score;

typedef struct stuscore{
	score s;
	float sum;
	float ave;
}stuscore;

bool cmp(const stuscore &a,const stuscore &b){
	return a.sum<b.sum;
}

const int length=100;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	//���ļ� 
	char filename[]="stuScores.txt";
	FILE *fp=fopen(filename,"r");
	if(fp==0){
		exit(0);
	}
	
	//��̬�����ڴ� 
	score *sc=new score[length];
	stuscore ss[length];
	stuscore *p=ss;
	int i=0,j=0,count=0,n=0,choice=0,number=0;
	float allsum=0.0;
	int duan[10]={0};
	
	//���ļ��ж�ȡ���� 
	while(!feof(fp)){
		fscanf(fp,"%d%s%f%f%f",&sc[i].id,sc[i].name,&sc[i].chinese,&sc[i].math,&sc[i].english);
		i++;
	}
	for(j=0;j<i;j++){
		ss[j].s=sc[j];
		ss[j].sum=sc[j].chinese+sc[j].math+sc[j].english;
		ss[j].ave=ss[j].sum/3;
	}
	n=i;
	sort(p,p+n,cmp);
	i=0;
	
	//ͳ�Ʋ�������� 
	printf("������ѧ��������");
	while(ss[i].ave<60){
		printf("%s\t",ss[i].s.name);
		count++;
		i++;
	}
	printf("\n������ѧ��������%d\n",count);
	count=0;
	for(i=0;i<n;i++){
		allsum+=ss[i].sum;
	}
	
	//ͳ��ƽ���� 
	printf("ȫ��ƽ���֣�%f\n",allsum/(3*n));
	printf("����ȫ��ƽ����ѧ��������");
	while(j>1){
		if(ss[j-1].ave>allsum/(3*n)){
			printf("%s\t",ss[j-1].s.name);
			count++;
		}
		j--;
	}
	printf("\n����ȫ��ƽ����ѧ��������%d\n",count);
	
	//ͳ�Ƹ������� 
	for(i=0;i<n;i++){
		choice=(int)(ss[i].ave/10);
		switch(choice){
			case 0:duan[0]++;break;
			case 1:duan[1]++;break;
			case 2:duan[2]++;break;
			case 3:duan[3]++;break;
			case 4:duan[4]++;break;
			case 5:duan[5]++;break;
			case 6:duan[6]++;break;
			case 7:duan[7]++;break;
			case 8:duan[8]++;break;
			case 9:duan[9]++;break;
		}
	}
	for(i=0;i<10;i++){
		printf("%d�����ε�������%d��ռ����İٷֱȣ�%lf\n",i*10,duan[i],(double)duan[i]/n);
	}
	
	//��ӡ���α� 
	printf("%8s%12s%8s%8s%8s%10s\n","ѧ�����","����","��ѧ","Ӣ��","�ܷ�","ƽ����"); 
	for(i=n-1;i>=0;i--){
		printf("%d\t\t%.1f\t%.1f\t%.1f\t%.1f\t%.2f\n",ss[i].s.id,ss[i].s.chinese,ss[i].s.math,ss[i].s.english,ss[i].sum,ss[i].ave);
	}
	
	//��ѯ����ͬѧ�ɼ� 
	printf("�����������ѯ��ѧ��ѧ�ţ�");
	scanf("%d",&number);
	for(i=0;i<n;i++){
		if(number==ss[i].s.id){
			printf("������%d\t���ģ�%.1f\t��ѧ��%.1f\tӢ�%.1f\n",n-i,ss[i].s.chinese,ss[i].s.math,ss[i].s.english);
			break;
		}
	}
	
	//�ͷ��ڴ�ռ䣬�ر��ļ� 
	delete []sc;
	if(fp){
		fclose(fp);
	}
	
	return 0;
}
