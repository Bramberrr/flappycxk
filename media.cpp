#include "stdafx.h"
#include "cxk.h"


void music(){

    mciSendString("open ../music/jntm.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic repeat", NULL, 0, NULL);        //ѭ����������


}

void rap(){

    mciSendString("open ../music/rap.mp3 alias mymusic2", NULL, 0, NULL);
	mciSendString("play mymusic2 repeat", NULL, 0, NULL);        //����rap
}

void zwjs()
{
    mciSendString("open ../music/zwjs.mp3 alias mymusic3", NULL, 0, NULL);
	mciSendString("play mymusic3 repeat", NULL, 0, NULL);        //�������ҽ���
}

void screencut()
{
    saveimage(_T("../picture/cxk.bmp"));
}