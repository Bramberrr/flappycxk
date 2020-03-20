#ifndef CXK_H
#define CXK_H

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include<mmsystem.h>

#pragma comment(lib,"Winmm.lib")

#define MAXSTAR 1000	// ��������

struct STAR            //��������˸������
{
	double	x;
	int		y;
	double	step;
	int		color;
};




struct ikun_state //������״̬
{
    int x; //������x��
    int y; //������y��
    int qy;
    int jump_height; //��������Ծ�߶�
    int jump;        //��Ծ���
    int frame;       //���м�����
    int playball;    //������
    int four;        //����
    int rap;         //rap���
	int zwjs;        //���ҽ��ܱ��
};

typedef struct node
{
    int x;
    int y;
    IMAGE img;
    int object; //������1������2�Ǽ���3�ǵ�Ļ
    struct node *next;

} Node, *pNode;

void show(IMAGE img[], int tem, pNode lp, IMAGE dj[], ikun_state *state); //��ʾ����
pNode obstacle(int four, IMAGE img[], pNode tail);                        //�жϺ���
void objmove(pNode lp);                                                   //�����ƶ�����
void start(ikun_state *state);                                            //���̼���
void Pdelete(pNode lp);                                                   //����ɾ��
void judge(ikun_state *state, pNode lp, pNode tail);                      //�жϺ���s
void menustart();                                                         //�˵�����
void music();                                       //��������
void rap();                                         //rap����
void zwjs();                                    //���������ҽ���
void playgame();                           //��ʼ��Ϸ
int display_menu();                           //��ʼ�˵�
void GRAPHIC_Initimage();                     //ͼ�γ�ʼ������
void GRAPHIC_Index();
void InitStar(int i);                    //���ǳ�ʼ��
void MoveStar(int i);                       //�ƶ�����
void selectrank();                          //ѡ����Ϸ�Ѷ�
void screencut();


#endif