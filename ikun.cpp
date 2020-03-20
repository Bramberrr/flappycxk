//主函数
#include "stdafx.h"
#include "cxk.h"
                                 
int main()
{
    music();//播放音乐

    display_menu();//加载菜单

    _getch();
    closegraph();
	exit (0);
    return 0;
}
