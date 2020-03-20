#include "stdafx.h"
#include "cxk.h"


IMAGE background, intro, st, bi, help, ex, rankimg, r1, r2, r3;
IMAGE micropic[4];
int rank = 80; //默认难度等级常规
int before = 0 ;    //保存分数

STAR star[MAXSTAR];

void InitStar(int i)
{
	star[i].x = 0;
	if(i<0.9*MAXSTAR)
	    star[i].y = rand() % 400;//星星随机分布
	else
        star[i].y =450 + rand() % 50;//防止遮挡彩虹桥
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i)
{
	// 擦掉原来的星星
	putpixel((int)star[i].x, star[i].y, 0);
    putpixel((int)star[i].x+1, star[i].y, 0);
	putpixel((int)star[i].x, star[i].y+1, 0);
	putpixel((int)star[i].x+1, star[i].y+1, 0);
	// 计算新位置
	star[i].x -= star[i].step;
	if (star[i].x < 0)	
        star[i].x +=1000;//移出画面则从右边重新开始

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
    putpixel((int)star[i].x+1, star[i].y, star[i].color);
	putpixel((int)star[i].x, star[i].y+1, star[i].color);
	putpixel((int)star[i].x+1, star[i].y+1, star[i].color);
}


void playgame()
{
    
	ikun_state state;
    state.x = 50;//坤坤初始位置 
    state.y = 200;
    state.qy = 200;
    state.four = 0;
    state.frame = 3;//生命值 
    state.jump_height = 100;//跳跃高度 
    state.playball = 0;//打篮球状态 
    state.rap = 0;//rap状态 
    state.jump = 1;//跳跃状态 
    srand((int)time(0));
    initgraph(1000, 500);//生成窗口 
    HWND hwnd = GetHWnd();  // 设置窗口标题文字
    SetWindowText(hwnd, "Flappy 蔡徐坤");

    IMAGE ikunpng[8]; //存放坤坤的帅气篮球6连拍
    IMAGE basketball; //坤坤的篮球
    IMAGE daoju[3];//三种障碍物 

    //坤坤的鸡你太美
    loadimage(&daoju[0], _T("../images/basketball.gif"), 50, 50); //加载坤坤的篮球
    loadimage(&daoju[1], _T("../images/jntm.gif"), 50, 50);       //加载坤坤的鸡你太美
    loadimage(&daoju[2], _T("../images/dm.gif"), 100, 50);        //加载坤坤的弹幕

    //为坤坤的帅气篮球6连拍赋值
    loadimage(&ikunpng[0], _T("../images/ikun_one.gif"), 200, 200);
    loadimage(&ikunpng[1], _T("../images/ikun_two.gif"), 200, 200);
    loadimage(&ikunpng[2], _T("../images/ikun_three.gif"), 200, 200);
    loadimage(&ikunpng[3], _T("../images/ikun_four.gif"), 200, 200);
    loadimage(&ikunpng[4], _T("../images/ikun_five.gif"), 200, 200);
    loadimage(&ikunpng[5], _T("../images/ikun_six.gif"), 200, 200);

    loadimage(&ikunpng[6], _T("../images/ikun_rap.gif"), 200, 200);
    loadimage(&ikunpng[7], _T("../images/ikun_playball.gif"), 200, 200);


    
    int rm = 0;
    pNode head = (pNode)malloc(sizeof(node));
    head->next = NULL;
    head->x = 1000;//从最右开始建链表
    head->y = 1;
    head->object = 0;
    pNode tail = head;

	srand((unsigned)time(NULL));
	for(int i = 0; i < MAXSTAR; i++)//画星星
	{
		InitStar(i);
		star[i].x = rand() % 1000;
	}
   
	while (1)
    {
        tail = obstacle(state.four, daoju, tail);
        // MessageBox(0,TEXT("aa"),TEXT("aa"),0); //调试用
        start(&state);
		if(state.rap == 1)//rap警告
			rap();//开始rap
		else
            mciSendString("stop mymusic2 ", NULL, 0, 0);//把rap的音频关掉
		if(state.zwjs == 1)//自我介绍警告
		{
			zwjs();//开始自我介绍
			Sleep(6000);//给坤坤续6秒来完成自我介绍，期间游戏暂停
		}
		else
            mciSendString("stop mymusic3 ", NULL, 0, 0);//自我介绍关掉

        show(ikunpng, rm++, head, daoju, &state);//显示坤坤 障碍物以及它们运动状态 
        for(int i = 0; i < MAXSTAR; i++)
	    MoveStar(i);//移动所有星星

		objmove(head);//移动
        
        Pdelete(head);//删除
        judge(&state, head, tail);//判断函数

        if (rm == 6)
        {
            rm = 0;
        }
		//让坤坤动起来的精髓 
        Sleep(rank);
    }

}

void show(IMAGE img[], int tem, pNode lp, IMAGE dj[], ikun_state *state)
{
    cleardevice();//清屏 

    settextstyle(25, 0, _T("楷体"));//设置字体 大小 
    TCHAR str1[10];//字符串1 
    TCHAR str2[10];//字符串2 
    TCHAR str3[40];//字符串3
	TCHAR str4[40];//字符串4
	TCHAR str5[40];//字符串5
    sprintf(str1, "分数：%d", state->four);//显示实时分数 
    sprintf(str2, "生命值：%d", state->frame);//显示实时生命值 
    sprintf(str3, "按下Shift可截屏至picture");
	sprintf(str4, "按下Ctrl可关闭 鸡你太美");
	sprintf(str5, "按下Alt可恢复 鸡你太美");
	settextcolor(WHITE);//都用白色显示 
    outtextxy(0, 450, str1);//显示位置 
    outtextxy(0, 475, str2);//显示位置 
    outtextxy(690, 0, str3);//显示位置
	outtextxy(690, 40, str4);//显示位置
	outtextxy(690, 80, str5);//显示位置
    //line(0, 400, 1000, 400);
	float H = 0;		// 色相
	float S = 1;		// 饱和度
	float L = 0.3f;		// 亮度
	setlinestyle(PS_SOLID, 2);	
	for(int y = 400; y < 450; y++)
	{
		H += 5;
		setlinecolor( HSLtoRGB(H, S, L) );//彩虹桥效果
		line(0, y, 1000, y);
	}
   


    putimage(state->x, state->qy, &img[tem]);//一帧一帧画坤坤 

    if (state->playball)//如果当前状态在等接球 
    {
        putimage(state->x, state->qy, &img[7]);//始终展示一张等待接球图 
    }

    if (state->rap)//如果当前在rap 
    {
        putimage(state->x, state->qy, &img[6]);//始终展示一张带rap气泡的图片 
    }

    for (pNode i = lp->next; i != NULL; i = i->next)
    {
        putimage(i->x, i->y, &dj[i->object]);//用贴图画障碍物 
    }
}

void judge(ikun_state *state, pNode lp, pNode tail)
{
	if(GetAsyncKeyState(VK_SHIFT) & 0x8000)//shift可截屏
		screencut();
	if(GetAsyncKeyState(VK_CONTROL) & 0x8000)//ctrl可关闭音乐
		mciSendString("stop mymusic ", NULL, 0, 0);
	if(GetAsyncKeyState(VK_MENU) & 0x8000)//Alt可打开音乐
		music();
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc可重新选择难度
        {
            selectrank();
        }
	if (state->four %100 ==0 && state->frame != 3 && state->four != before) 
		state->frame ++;                //每到100 的整数倍加一条命，最多加到3条命
    before = state->four;
    if (state->frame <= 0)//判断生命值是否归零 
    {
        settextstyle(36, 0, _T("宋体"));//设置字体大小 
        state->x = 50;
        state->y = 200;
        state->qy = 200;
        state->four = 0;
        state->frame = 3;
        state->jump_height = 100;
        state->playball = 0;
        state->rap = 0;
        state->jump = 1;//重置坤坤状态 

		FILE *fp;
        fp=fopen(_T("../record.txt"), "w"); //打开文件写入得分
        fputs("Your score is",fp); 
        fputc(':', fp); //向所建文件写冒号
        fprintf(fp, "%d\n", before);//向所建文件写入得分
        fclose(fp);

        while (1)
        {
            cleardevice();//清空屏幕 
            settextcolor(RED);
            outtextxy(200, 250, _T("你被律师函警告，请按空格重新开始游戏"));
			outtextxy(300, 350, _T("按Esc可退出游戏"));
            if (GetAsyncKeyState(VK_SPACE) & 0x8000)
                selectrank();//如果空格键按下就重新开始 
            
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                exit(0);//如果Esc键按下就退出

            Sleep(20);
        }
    }

    pNode p, q;

    if (lp == NULL)
    {
        return;
    }

    for (p = lp->next, q = lp; p != NULL; p = p->next, q = q->next)//读链表 
    {

        if ((state->x + 100 >= p->x + 10) && (state->x + 100 <= p->x + 40) && (state->qy + 160 >= p->y))
        {

            if (p->object == 0)//如果是篮球
            {

                if (state->playball)//坤坤此时处于打篮球状态 
                {
                    state->four += 5;  //接住篮球加5分
                    q->next = p->next;//判断下一个障碍物 
                    if (p == NULL)
                        break;
                    else
                        free(p);//释放被接住的篮球的内存 
                }
                break;
            }

            if (p->object == 2)//如果是弹幕 
            {

                if (state->rap)//正好在rap 
                {
                    state->four += 10;  //接住弹幕的梗了，奖励10分
                    q->next = p->next;
                    if (p == NULL)
                        break;
                    else
                        free(p);//删除得分物，释放内存 
                }
                else
                {

                    state->four -= 20;  //没接住弹幕，被B站嘲讽了，分数倒扣20 
					q->next = p->next;
                    state->frame -= 1; //不仅因为律师函被全网嘲讽，还因此少了条命
                    if (p == NULL)
                        break;
                    else
                        free(p);//释放错过的物体
                }

                break;
            }

            else
            {

                state->frame -= 1;  //撞到鸡了，失去一条命
                q->next = p->next;
                if (p == NULL)
                    break;
                else
                    free(p);//释放被碰到的鸡 
                break;
            }
        }
    }
}

void menustart()
{

    IMAGE memu;
    
    settextstyle(26, 0, _T("宋体"));//设置字体 
    loadimage(&memu, _T("../images/memu.gif"), 1000, 500);//加载背景 


    while (!kbhit())//无键盘输入时进入死循环 
    {
        cleardevice();

        putimage(0,0,&memu);
                                     //若无键盘操作，闪烁
        setcolor(BLUE);                       //设置字体颜色
        outtextxy(700, 350, _T("按空格返回")); //显示
        Sleep(100);                         //延时
        setcolor(WHITE);                     //用背景色擦去字迹
        outtextxy(700, 350, _T("按空格返回")); //显示
        Sleep(100);                         //延时
		setcolor(YELLOW);                     //用背景色擦去字迹
        outtextxy(700, 350, _T("按空格返回")); //显示
        Sleep(100);                         //延时
		setcolor(GREEN);                     //用背景色擦去字迹
        outtextxy(700, 350, _T("按空格返回")); //显示
        Sleep(100);                         //延时
    }
}



void Pdelete(pNode head)
{

    pNode p, q;

    if (head == NULL)//读到链表尾跳出 
    {
        return;
    }

    for (p = head->next, q = head; p != NULL; p = p->next, q = q->next)
    {
        if (p->x <= 0)//在屏幕外的障碍物就删除，节省内存空间 
        {
            q->next = p->next;
        }
    }
    if (p == NULL)
        return;
    else
        free(p);//释放内存单元 
}



void objmove(pNode lp)
{

    for (pNode i = lp->next; i != NULL; i = i->next)//读链表中的障碍物 
    {
        if (i->object == 0)//如果障碍物是篮球就会有随机上下震动 

        {
            i->y = rand() % 50 + 300;//利用随机数让小球上下震动，体现出动感 
        }

        i->x -= 20;//向前移动 
    }
}

pNode obstacle(int four, IMAGE img[], pNode tail)
{ //生成障碍物

    if ((rand() % 5) == 1)
    { //1/5的概率

        int thisx = rand() % 200 + 1200;//障碍物生成的预期位置 
        if (thisx <= tail->x + 200)//如果前一个障碍物还没移动过远就不生成了 
        {

            return tail;
        }
        else
        {
            tail->next = (pNode)malloc(sizeof(Node));//用链表储存生成的障碍物 
            tail->next->y = 300;
            tail->next->next = NULL;
            tail->next->x = thisx;
        }

        int tmp;

        if (four > 100)//100分以上会出现弹幕 
        {
            tmp = rand() % 3;

            tail->next->object = tmp;//生成下一个障碍物 
        }
        else
        {
            tmp = rand() % 2 + 0;

            tail->next->object = tmp;//生成下一个障碍物 
        }

        return tail->next;
    }
    return tail;
}

void start(ikun_state *state)
{

    if (GetAsyncKeyState(VK_UP) & 0x8000)//检测上键是否按下 
    {

        state->qy -= 30;//唱跳rap篮球的 跳 功能 
    }
    else
    {//不按键的时候坤坤就会往下掉了 

        if (state->qy < state->y)
        {
            state->qy += 30;
        }
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)//检测是否按下下键 
    {
        state->playball = 1;//按下了坤坤就准备接球了 
    }
    else
    {
        state->playball = 0;//没有按下时坤坤表演美国校队式运球 
    }

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//检测是否按下右键 
    {
        state->zwjs = 1;//按了坤坤就回把画面停住，开始自我介绍，试图成功引起你的注意
    }
    else
    {
        state->zwjs = 0;//没有按坤坤就不会和你互动 
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//检测是否按下右键 
    {
        state->rap = 1;//按了坤坤就会开始无意义rap，看上去十分 cooooooooool 
    }
    else
    {
        state->rap = 0;//没有按坤坤就不会和你互动 
    }
}

void GRAPHIC_Initimage()
{
    
	loadimage(&background, "../images/background.jpg", 1000, 500);//加载菜单背景
    loadimage(&intro, "../images/intro.jpg", 1000, 500);//加载这个游戏的设计背景
    loadimage(&st, "../images/start_game.png", 240, 70);//加载开始按钮
    loadimage(&bi, "../images/bi.png", 240, 70);//加载设计背景介绍按钮
    loadimage(&help, "../images/help.png", 240, 70);//加载帮助按钮
    loadimage(&ex, "../images/exit.png", 240, 70);//加载退出按钮
}

void GRAPHIC_Index()
{
	putimage(0,0,&background);//放置菜单背景
	putimage(680,30,&st);//放置开始按钮
	putimage(680,130,&bi);//放置设计背景介绍按钮
	putimage(680,230,&help);//放置帮助按钮
	putimage(680,330,&ex);//放置退出按钮
}


int display_menu()
{
    int  logOut = 1;//设置登出标记

	GRAPHIC_Initimage();//加载图片

	while(logOut == 1){//没有登出
		MOUSEMSG mouse;//鼠标准备
		int op;//选项
		initgraph(1000, 500); //初始化一个窗口
		HWND hwnd = GetHWnd();  // 设置窗口标题文字
        SetWindowText(hwnd, "Flappy 蔡徐坤");//配上好听的游戏名
		op = 0;//给选项赋值
		GRAPHIC_Index();//放置目录
		while(TRUE){
			FlushMouseMsgBuffer();
			mouse = GetMouseMsg();//探知鼠标位置
			if(mouse.x>=680&&mouse.y>=30&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=100){
				op = 1;
				break;//说明按了开始游戏
			}
			else if(mouse.x>=680&&mouse.y>=130&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=200){
				op = 2;
				break;//说明按了背景介绍
			}
			else if(mouse.x>=680&&mouse.y>=230&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=300){
				op = 3;
				break;//说明按了帮助
			}
			else if(mouse.x>=680&&mouse.y>=330&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=400){
				op = 4;
				break;//说明按了退出
			}
		}
		switch(op){
		case 1:
			selectrank();//进入游戏等级选择界面
			_getch();
			break;
		case 2:
		    putimage(0,0,&intro);//进入介绍
            _getch();
			break;
		case 3:
		    menustart();//进入帮助界面
			_getch();
			break;
		case 4:
			mciSendString("stop mymusic", NULL, 0, 0);//音乐停掉
			closegraph();//图形关掉
			logOut = 0;
			exit(0);//再见！
			break;
		}
	}
	return 0;
}

void selectrank()//难度选择界面
{
	loadimage(&rankimg, "../images/rank.jpg", 1000, 500);//加载背景
    loadimage(&r1, "../images/r1.jpg", 240, 180);//加载 常速
    loadimage(&r2, "../images/r2.jpg", 240, 180);//加载 加速
    loadimage(&r3, "../images/r3.jpg", 240, 180);//加载 超速
	
	MOUSEMSG mouse;//鼠标准备
	int op;//选项
    initgraph(1000, 500); //初始化窗口
    HWND hwnd = GetHWnd();  // 设置窗口标题文字
    SetWindowText(hwnd, "Flappy 蔡徐坤");//配上好听的名字

	putimage(0,0,&rankimg);//放置背景
    putimage(50,160,&r1);//放置常速
    putimage(350,160,&r2);//放置加速
	putimage(650,160,&r3);//放置超速

    while(TRUE){
			FlushMouseMsgBuffer();
			mouse = GetMouseMsg();//获得鼠标位置

			if(mouse.x>=50&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=290&&mouse.y<=340){
				op = 1;//选择常速的坤坤
				break;
			}
			else if(mouse.x>=350&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=590&&mouse.y<=340){
				op = 2;//选择加速坤坤
				break;
			}
			else if(mouse.x>=650&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=890&&mouse.y<=340){
				op = 3;//选择超速能上天的坤坤
				break;
			}
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc可退回菜单
		{
            display_menu();
			break;
		}
		}
		switch(op){
		case 1:
			rank = 80;
			playgame();//直接开始游戏
			_getch();
			break;
		case 2:
		    rank = 60;//坤坤加快
			playgame();
            _getch();
			break;
		case 3:
			rank = 40;
			playgame();//坤坤再快
			_getch();
			break;
	}
}