#include "stdafx.h"
#include "cxk.h"


void music(){

    mciSendString("open ../music/jntm.mp3 alias mymusic", NULL, 0, NULL);
	mciSendString("play mymusic repeat", NULL, 0, NULL);        //循环播放音乐


}

void rap(){

    mciSendString("open ../music/rap.mp3 alias mymusic2", NULL, 0, NULL);
	mciSendString("play mymusic2 repeat", NULL, 0, NULL);        //播放rap
}

void zwjs()
{
    mciSendString("open ../music/zwjs.mp3 alias mymusic3", NULL, 0, NULL);
	mciSendString("play mymusic3 repeat", NULL, 0, NULL);        //播放自我介绍
}

void screencut()
{
    saveimage(_T("../picture/cxk.bmp"));
}