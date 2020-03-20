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

#define MAXSTAR 1000	// 星星总数

struct STAR            //背景中闪烁的星星
{
	double	x;
	int		y;
	double	step;
	int		color;
};




struct ikun_state //坤坤的状态
{
    int x; //坤坤的x轴
    int y; //坤坤的y轴
    int qy;
    int jump_height; //坤坤的跳跃高度
    int jump;        //跳跃标记
    int frame;       //还有几条命
    int playball;    //打球标记
    int four;        //分数
    int rap;         //rap标记
	int zwjs;        //自我介绍标记
};

typedef struct node
{
    int x;
    int y;
    IMAGE img;
    int object; //物体标记1是篮球，2是鸡，3是弹幕
    struct node *next;

} Node, *pNode;

void show(IMAGE img[], int tem, pNode lp, IMAGE dj[], ikun_state *state); //显示函数
pNode obstacle(int four, IMAGE img[], pNode tail);                        //判断函数
void objmove(pNode lp);                                                   //物体移动函数
void start(ikun_state *state);                                            //键盘监听
void Pdelete(pNode lp);                                                   //链表删除
void judge(ikun_state *state, pNode lp, pNode tail);                      //判断函数s
void menustart();                                                         //菜单函数
void music();                                       //背景音乐
void rap();                                         //rap音乐
void zwjs();                                    //坤坤的自我介绍
void playgame();                           //开始游戏
int display_menu();                           //起始菜单
void GRAPHIC_Initimage();                     //图形初始化函数
void GRAPHIC_Index();
void InitStar(int i);                    //星星初始化
void MoveStar(int i);                       //移动星星
void selectrank();                          //选择游戏难度
void screencut();


#endif