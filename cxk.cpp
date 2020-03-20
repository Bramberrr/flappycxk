#include "stdafx.h"
#include "cxk.h"


IMAGE background, intro, st, bi, help, ex, rankimg, r1, r2, r3;
IMAGE micropic[4];
int rank = 80; //Ĭ���Ѷȵȼ�����
int before = 0 ;    //�������

STAR star[MAXSTAR];

void InitStar(int i)
{
	star[i].x = 0;
	if(i<0.9*MAXSTAR)
	    star[i].y = rand() % 400;//��������ֲ�
	else
        star[i].y =450 + rand() % 50;//��ֹ�ڵ��ʺ���
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// �ƶ�����
void MoveStar(int i)
{
	// ����ԭ��������
	putpixel((int)star[i].x, star[i].y, 0);
    putpixel((int)star[i].x+1, star[i].y, 0);
	putpixel((int)star[i].x, star[i].y+1, 0);
	putpixel((int)star[i].x+1, star[i].y+1, 0);
	// ������λ��
	star[i].x -= star[i].step;
	if (star[i].x < 0)	
        star[i].x +=1000;//�Ƴ���������ұ����¿�ʼ

	// ��������
	putpixel((int)star[i].x, star[i].y, star[i].color);
    putpixel((int)star[i].x+1, star[i].y, star[i].color);
	putpixel((int)star[i].x, star[i].y+1, star[i].color);
	putpixel((int)star[i].x+1, star[i].y+1, star[i].color);
}


void playgame()
{
    
	ikun_state state;
    state.x = 50;//������ʼλ�� 
    state.y = 200;
    state.qy = 200;
    state.four = 0;
    state.frame = 3;//����ֵ 
    state.jump_height = 100;//��Ծ�߶� 
    state.playball = 0;//������״̬ 
    state.rap = 0;//rap״̬ 
    state.jump = 1;//��Ծ״̬ 
    srand((int)time(0));
    initgraph(1000, 500);//���ɴ��� 
    HWND hwnd = GetHWnd();  // ���ô��ڱ�������
    SetWindowText(hwnd, "Flappy ������");

    IMAGE ikunpng[8]; //���������˧������6����
    IMAGE basketball; //����������
    IMAGE daoju[3];//�����ϰ��� 

    //�����ļ���̫��
    loadimage(&daoju[0], _T("../images/basketball.gif"), 50, 50); //��������������
    loadimage(&daoju[1], _T("../images/jntm.gif"), 50, 50);       //���������ļ���̫��
    loadimage(&daoju[2], _T("../images/dm.gif"), 100, 50);        //���������ĵ�Ļ

    //Ϊ������˧������6���ĸ�ֵ
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
    head->x = 1000;//�����ҿ�ʼ������
    head->y = 1;
    head->object = 0;
    pNode tail = head;

	srand((unsigned)time(NULL));
	for(int i = 0; i < MAXSTAR; i++)//������
	{
		InitStar(i);
		star[i].x = rand() % 1000;
	}
   
	while (1)
    {
        tail = obstacle(state.four, daoju, tail);
        // MessageBox(0,TEXT("aa"),TEXT("aa"),0); //������
        start(&state);
		if(state.rap == 1)//rap����
			rap();//��ʼrap
		else
            mciSendString("stop mymusic2 ", NULL, 0, 0);//��rap����Ƶ�ص�
		if(state.zwjs == 1)//���ҽ��ܾ���
		{
			zwjs();//��ʼ���ҽ���
			Sleep(6000);//��������6����������ҽ��ܣ��ڼ���Ϸ��ͣ
		}
		else
            mciSendString("stop mymusic3 ", NULL, 0, 0);//���ҽ��ܹص�

        show(ikunpng, rm++, head, daoju, &state);//��ʾ���� �ϰ����Լ������˶�״̬ 
        for(int i = 0; i < MAXSTAR; i++)
	    MoveStar(i);//�ƶ���������

		objmove(head);//�ƶ�
        
        Pdelete(head);//ɾ��
        judge(&state, head, tail);//�жϺ���

        if (rm == 6)
        {
            rm = 0;
        }
		//�������������ľ��� 
        Sleep(rank);
    }

}

void show(IMAGE img[], int tem, pNode lp, IMAGE dj[], ikun_state *state)
{
    cleardevice();//���� 

    settextstyle(25, 0, _T("����"));//�������� ��С 
    TCHAR str1[10];//�ַ���1 
    TCHAR str2[10];//�ַ���2 
    TCHAR str3[40];//�ַ���3
	TCHAR str4[40];//�ַ���4
	TCHAR str5[40];//�ַ���5
    sprintf(str1, "������%d", state->four);//��ʾʵʱ���� 
    sprintf(str2, "����ֵ��%d", state->frame);//��ʾʵʱ����ֵ 
    sprintf(str3, "����Shift�ɽ�����picture");
	sprintf(str4, "����Ctrl�ɹر� ����̫��");
	sprintf(str5, "����Alt�ɻָ� ����̫��");
	settextcolor(WHITE);//���ð�ɫ��ʾ 
    outtextxy(0, 450, str1);//��ʾλ�� 
    outtextxy(0, 475, str2);//��ʾλ�� 
    outtextxy(690, 0, str3);//��ʾλ��
	outtextxy(690, 40, str4);//��ʾλ��
	outtextxy(690, 80, str5);//��ʾλ��
    //line(0, 400, 1000, 400);
	float H = 0;		// ɫ��
	float S = 1;		// ���Ͷ�
	float L = 0.3f;		// ����
	setlinestyle(PS_SOLID, 2);	
	for(int y = 400; y < 450; y++)
	{
		H += 5;
		setlinecolor( HSLtoRGB(H, S, L) );//�ʺ���Ч��
		line(0, y, 1000, y);
	}
   


    putimage(state->x, state->qy, &img[tem]);//һ֡һ֡������ 

    if (state->playball)//�����ǰ״̬�ڵȽ��� 
    {
        putimage(state->x, state->qy, &img[7]);//ʼ��չʾһ�ŵȴ�����ͼ 
    }

    if (state->rap)//�����ǰ��rap 
    {
        putimage(state->x, state->qy, &img[6]);//ʼ��չʾһ�Ŵ�rap���ݵ�ͼƬ 
    }

    for (pNode i = lp->next; i != NULL; i = i->next)
    {
        putimage(i->x, i->y, &dj[i->object]);//����ͼ���ϰ��� 
    }
}

void judge(ikun_state *state, pNode lp, pNode tail)
{
	if(GetAsyncKeyState(VK_SHIFT) & 0x8000)//shift�ɽ���
		screencut();
	if(GetAsyncKeyState(VK_CONTROL) & 0x8000)//ctrl�ɹر�����
		mciSendString("stop mymusic ", NULL, 0, 0);
	if(GetAsyncKeyState(VK_MENU) & 0x8000)//Alt�ɴ�����
		music();
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc������ѡ���Ѷ�
        {
            selectrank();
        }
	if (state->four %100 ==0 && state->frame != 3 && state->four != before) 
		state->frame ++;                //ÿ��100 ����������һ���������ӵ�3����
    before = state->four;
    if (state->frame <= 0)//�ж�����ֵ�Ƿ���� 
    {
        settextstyle(36, 0, _T("����"));//���������С 
        state->x = 50;
        state->y = 200;
        state->qy = 200;
        state->four = 0;
        state->frame = 3;
        state->jump_height = 100;
        state->playball = 0;
        state->rap = 0;
        state->jump = 1;//��������״̬ 

		FILE *fp;
        fp=fopen(_T("../record.txt"), "w"); //���ļ�д��÷�
        fputs("Your score is",fp); 
        fputc(':', fp); //�������ļ�дð��
        fprintf(fp, "%d\n", before);//�������ļ�д��÷�
        fclose(fp);

        while (1)
        {
            cleardevice();//�����Ļ 
            settextcolor(RED);
            outtextxy(200, 250, _T("�㱻��ʦ�����棬�밴�ո����¿�ʼ��Ϸ"));
			outtextxy(300, 350, _T("��Esc���˳���Ϸ"));
            if (GetAsyncKeyState(VK_SPACE) & 0x8000)
                selectrank();//����ո�����¾����¿�ʼ 
            
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                exit(0);//���Esc�����¾��˳�

            Sleep(20);
        }
    }

    pNode p, q;

    if (lp == NULL)
    {
        return;
    }

    for (p = lp->next, q = lp; p != NULL; p = p->next, q = q->next)//������ 
    {

        if ((state->x + 100 >= p->x + 10) && (state->x + 100 <= p->x + 40) && (state->qy + 160 >= p->y))
        {

            if (p->object == 0)//���������
            {

                if (state->playball)//������ʱ���ڴ�����״̬ 
                {
                    state->four += 5;  //��ס�����5��
                    q->next = p->next;//�ж���һ���ϰ��� 
                    if (p == NULL)
                        break;
                    else
                        free(p);//�ͷű���ס��������ڴ� 
                }
                break;
            }

            if (p->object == 2)//����ǵ�Ļ 
            {

                if (state->rap)//������rap 
                {
                    state->four += 10;  //��ס��Ļ�Ĺ��ˣ�����10��
                    q->next = p->next;
                    if (p == NULL)
                        break;
                    else
                        free(p);//ɾ���÷���ͷ��ڴ� 
                }
                else
                {

                    state->four -= 20;  //û��ס��Ļ����Bվ�����ˣ���������20 
					q->next = p->next;
                    state->frame -= 1; //������Ϊ��ʦ����ȫ�������������������
                    if (p == NULL)
                        break;
                    else
                        free(p);//�ͷŴ��������
                }

                break;
            }

            else
            {

                state->frame -= 1;  //ײ�����ˣ�ʧȥһ����
                q->next = p->next;
                if (p == NULL)
                    break;
                else
                    free(p);//�ͷű������ļ� 
                break;
            }
        }
    }
}

void menustart()
{

    IMAGE memu;
    
    settextstyle(26, 0, _T("����"));//�������� 
    loadimage(&memu, _T("../images/memu.gif"), 1000, 500);//���ر��� 


    while (!kbhit())//�޼�������ʱ������ѭ�� 
    {
        cleardevice();

        putimage(0,0,&memu);
                                     //���޼��̲�������˸
        setcolor(BLUE);                       //����������ɫ
        outtextxy(700, 350, _T("���ո񷵻�")); //��ʾ
        Sleep(100);                         //��ʱ
        setcolor(WHITE);                     //�ñ���ɫ��ȥ�ּ�
        outtextxy(700, 350, _T("���ո񷵻�")); //��ʾ
        Sleep(100);                         //��ʱ
		setcolor(YELLOW);                     //�ñ���ɫ��ȥ�ּ�
        outtextxy(700, 350, _T("���ո񷵻�")); //��ʾ
        Sleep(100);                         //��ʱ
		setcolor(GREEN);                     //�ñ���ɫ��ȥ�ּ�
        outtextxy(700, 350, _T("���ո񷵻�")); //��ʾ
        Sleep(100);                         //��ʱ
    }
}



void Pdelete(pNode head)
{

    pNode p, q;

    if (head == NULL)//��������β���� 
    {
        return;
    }

    for (p = head->next, q = head; p != NULL; p = p->next, q = q->next)
    {
        if (p->x <= 0)//����Ļ����ϰ����ɾ������ʡ�ڴ�ռ� 
        {
            q->next = p->next;
        }
    }
    if (p == NULL)
        return;
    else
        free(p);//�ͷ��ڴ浥Ԫ 
}



void objmove(pNode lp)
{

    for (pNode i = lp->next; i != NULL; i = i->next)//�������е��ϰ��� 
    {
        if (i->object == 0)//����ϰ���������ͻ������������ 

        {
            i->y = rand() % 50 + 300;//�����������С�������𶯣����ֳ����� 
        }

        i->x -= 20;//��ǰ�ƶ� 
    }
}

pNode obstacle(int four, IMAGE img[], pNode tail)
{ //�����ϰ���

    if ((rand() % 5) == 1)
    { //1/5�ĸ���

        int thisx = rand() % 200 + 1200;//�ϰ������ɵ�Ԥ��λ�� 
        if (thisx <= tail->x + 200)//���ǰһ���ϰ��ﻹû�ƶ���Զ�Ͳ������� 
        {

            return tail;
        }
        else
        {
            tail->next = (pNode)malloc(sizeof(Node));//�����������ɵ��ϰ��� 
            tail->next->y = 300;
            tail->next->next = NULL;
            tail->next->x = thisx;
        }

        int tmp;

        if (four > 100)//100�����ϻ���ֵ�Ļ 
        {
            tmp = rand() % 3;

            tail->next->object = tmp;//������һ���ϰ��� 
        }
        else
        {
            tmp = rand() % 2 + 0;

            tail->next->object = tmp;//������һ���ϰ��� 
        }

        return tail->next;
    }
    return tail;
}

void start(ikun_state *state)
{

    if (GetAsyncKeyState(VK_UP) & 0x8000)//����ϼ��Ƿ��� 
    {

        state->qy -= 30;//����rap����� �� ���� 
    }
    else
    {//��������ʱ�������ͻ����µ��� 

        if (state->qy < state->y)
        {
            state->qy += 30;
        }
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)//����Ƿ����¼� 
    {
        state->playball = 1;//������������׼�������� 
    }
    else
    {
        state->playball = 0;//û�а���ʱ������������У��ʽ���� 
    }

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)//����Ƿ����Ҽ� 
    {
        state->zwjs = 1;//���������ͻذѻ���ͣס����ʼ���ҽ��ܣ���ͼ�ɹ��������ע��
    }
    else
    {
        state->zwjs = 0;//û�а������Ͳ�����㻥�� 
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)//����Ƿ����Ҽ� 
    {
        state->rap = 1;//���������ͻῪʼ������rap������ȥʮ�� cooooooooool 
    }
    else
    {
        state->rap = 0;//û�а������Ͳ�����㻥�� 
    }
}

void GRAPHIC_Initimage()
{
    
	loadimage(&background, "../images/background.jpg", 1000, 500);//���ز˵�����
    loadimage(&intro, "../images/intro.jpg", 1000, 500);//���������Ϸ����Ʊ���
    loadimage(&st, "../images/start_game.png", 240, 70);//���ؿ�ʼ��ť
    loadimage(&bi, "../images/bi.png", 240, 70);//������Ʊ������ܰ�ť
    loadimage(&help, "../images/help.png", 240, 70);//���ذ�����ť
    loadimage(&ex, "../images/exit.png", 240, 70);//�����˳���ť
}

void GRAPHIC_Index()
{
	putimage(0,0,&background);//���ò˵�����
	putimage(680,30,&st);//���ÿ�ʼ��ť
	putimage(680,130,&bi);//������Ʊ������ܰ�ť
	putimage(680,230,&help);//���ð�����ť
	putimage(680,330,&ex);//�����˳���ť
}


int display_menu()
{
    int  logOut = 1;//���õǳ����

	GRAPHIC_Initimage();//����ͼƬ

	while(logOut == 1){//û�еǳ�
		MOUSEMSG mouse;//���׼��
		int op;//ѡ��
		initgraph(1000, 500); //��ʼ��һ������
		HWND hwnd = GetHWnd();  // ���ô��ڱ�������
        SetWindowText(hwnd, "Flappy ������");//���Ϻ�������Ϸ��
		op = 0;//��ѡ�ֵ
		GRAPHIC_Index();//����Ŀ¼
		while(TRUE){
			FlushMouseMsgBuffer();
			mouse = GetMouseMsg();//֪̽���λ��
			if(mouse.x>=680&&mouse.y>=30&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=100){
				op = 1;
				break;//˵�����˿�ʼ��Ϸ
			}
			else if(mouse.x>=680&&mouse.y>=130&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=200){
				op = 2;
				break;//˵�����˱�������
			}
			else if(mouse.x>=680&&mouse.y>=230&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=300){
				op = 3;
				break;//˵�����˰���
			}
			else if(mouse.x>=680&&mouse.y>=330&&mouse.mkLButton==1&&mouse.x<=920&&mouse.y<=400){
				op = 4;
				break;//˵�������˳�
			}
		}
		switch(op){
		case 1:
			selectrank();//������Ϸ�ȼ�ѡ�����
			_getch();
			break;
		case 2:
		    putimage(0,0,&intro);//�������
            _getch();
			break;
		case 3:
		    menustart();//�����������
			_getch();
			break;
		case 4:
			mciSendString("stop mymusic", NULL, 0, 0);//����ͣ��
			closegraph();//ͼ�ιص�
			logOut = 0;
			exit(0);//�ټ���
			break;
		}
	}
	return 0;
}

void selectrank()//�Ѷ�ѡ�����
{
	loadimage(&rankimg, "../images/rank.jpg", 1000, 500);//���ر���
    loadimage(&r1, "../images/r1.jpg", 240, 180);//���� ����
    loadimage(&r2, "../images/r2.jpg", 240, 180);//���� ����
    loadimage(&r3, "../images/r3.jpg", 240, 180);//���� ����
	
	MOUSEMSG mouse;//���׼��
	int op;//ѡ��
    initgraph(1000, 500); //��ʼ������
    HWND hwnd = GetHWnd();  // ���ô��ڱ�������
    SetWindowText(hwnd, "Flappy ������");//���Ϻ���������

	putimage(0,0,&rankimg);//���ñ���
    putimage(50,160,&r1);//���ó���
    putimage(350,160,&r2);//���ü���
	putimage(650,160,&r3);//���ó���

    while(TRUE){
			FlushMouseMsgBuffer();
			mouse = GetMouseMsg();//������λ��

			if(mouse.x>=50&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=290&&mouse.y<=340){
				op = 1;//ѡ���ٵ�����
				break;
			}
			else if(mouse.x>=350&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=590&&mouse.y<=340){
				op = 2;//ѡ���������
				break;
			}
			else if(mouse.x>=650&&mouse.y>=160&&mouse.mkLButton==1&&mouse.x<=890&&mouse.y<=340){
				op = 3;//ѡ���������������
				break;
			}
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc���˻ز˵�
		{
            display_menu();
			break;
		}
		}
		switch(op){
		case 1:
			rank = 80;
			playgame();//ֱ�ӿ�ʼ��Ϸ
			_getch();
			break;
		case 2:
		    rank = 60;//�����ӿ�
			playgame();
            _getch();
			break;
		case 3:
			rank = 40;
			playgame();//�����ٿ�
			_getch();
			break;
	}
}