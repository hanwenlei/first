#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include"function.h"

extern char up,down,left,right;

int select(){
	int hang=0;
	int flag=0;
	char ch=1;
	system("color f1");
	
	while(ch!=13){
		gotoxy(22,8);
		printf("����");
		
		gotoxy(22,11);
		printf("��");
		
		gotoxy(22,14);
		printf("�е�");
		
		gotoxy(22,17);
		printf("����");
		
		gotoxy(22,20);
		printf("����");
		
		gotoxy(22,23);
		printf("����");
		
		gotoxy(20,hang+8);
		printf("%c%c",16,16);
		
		ch=getch();
		
		if(ch==down){
			hang+=3;
			if(hang>15){
				hang=15;
			}
			
			gotoxy(20,hang+5);
			printf("  ");
			
			gotoxy(20,hang+8);
			printf("%c%c",16,16);
		} 
		
		else if(ch==up){
			hang-=3;
			if(hang<0){
				hang=0;
			}
			
			gotoxy(20,hang+11);
			printf("  ");
			
			gotoxy(20,hang+8);
			printf("%c%c",16,16);
		}
	}
	if(hang==15){
		flag=-1;
	}
	else{
		gotoxy(22,26);
		printf("��ѡ����Ѷ��ǣ�"); 
		switch(hang){
			case 0:printf("����");break;
			case 3:printf("��"); break;
			case 6:printf("�е�");break;
			case 9:printf("����");break;
			case 12:printf("����");break;
		}
		gotoxy(22,28);
		printf("�밴�����������Ϸ");
		
		getchar();
		map1();
	}
	return flag;
}