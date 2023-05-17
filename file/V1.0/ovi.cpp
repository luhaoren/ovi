#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
#ifndef MY_WIN_H
#define MY_WIN_H
namespace win{
	inline void gotoxy(int x,int y){
		//设置光标位置
		HANDLE hout;
		COORD pos;
		pos.X=x,pos.Y=y;
		hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hout,pos);
	}
	
	std::pair<int,int> getPos(){
		//获取光标位置
		HANDLE hStdout;
		CONSOLE_SCREEN_BUFFER_INFO pBuffer; 
		hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
		GetConsoleScreenBufferInfo(hStdout, &pBuffer); 
		return {pBuffer.dwCursorPosition.X,pBuffer.dwCursorPosition.Y};
	}
	
	inline void noSetWindow(){
		//禁止设置窗口大小
		SetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE, GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	}
	inline void SetColor(int fore=7,int back=0){
		//设置颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(back<<4)+fore);
	}
	inline void setTitle(std::string title){
		//设置标题
		SetConsoleTitleA(title.c_str());
	}
	
}

#endif

/*
  ovi 使用指南
  版本：V1.0
  
  支持命令模式和输入模式
  切换方式：按Esc
  
  命令模式：
  s  	 保存
  o 	 打开
  r 	 重命名
  wasd   变换光标位置
  e 	 删除一行
  h	 帮助
  q	 退出
  c	 清屏
  
  在输入模式下，支持Tab、BackSpace、delete、Space、Enter操作。
  请不要在输入模式下键入除以上三键外的其它功能按键，否则会出现乱码。
  暂不支持汉字
  暂不支持保存
  打开文件时，若文件中有汉字，请使用ANSL编码
 */
string nowTitle;
void control();
void insert();
void openFile();
void putHelp();

inline void clearAll(){
	system("cls");
	win::gotoxy(0,0);
}
int main(){
	nowTitle="untitled1.txt";
	putHelp();
	control();
	return 0;
}

inline void control(){
	while(1){
		win::setTitle(nowTitle);
		if(_kbhit()){
			pair<int,int> nowPos=win::getPos();
			char ch=_getch();
			switch(ch){
			case 27:
				insert();
				break;
			case 'h':
				putHelp();
				break;
			case 'w':
				win::gotoxy(nowPos.first,nowPos.second-1);
				break;
			case 's':
				win::gotoxy(nowPos.first,nowPos.second+1);
				break;
			case 'a':
				win::gotoxy(nowPos.first-1,nowPos.second);
				break;
			case 'd':
				win::gotoxy(nowPos.first+1,nowPos.second);
				break;
			case 'e':
				win::gotoxy(0,nowPos.second);
				for(int i=0;i<nowPos.first;i++) cout<<' ';
				break;
			case 'o':
				openFile();
				break;
			case 'c':
				clearAll();
				break;
			case 'q':
				exit(-1);
				break;
			case 'r':
				clearAll();
				cout<<"重命名：";
				cin>>nowTitle;
				clearAll();
				break;
			}
		}
	}
}
inline void putHelp(){
	clearAll();
	ifstream in("help.txt");
	if(!in.good()){
		cout<<"帮助文档加载错误！\n";
		getch();
		exit(-1);
	}
	while(!in.eof()){
		char buf[1010];
		in.getline(buf,1010);
		cout<<buf<<endl;
	}
	getch();
	clearAll();
}
inline void openFile(){
	clearAll();
	cout<<"file name:";
	cin>>nowTitle;
	ifstream in(nowTitle);
	if(!in.good()){
		cout<<"\n打开错误！\n";
		return;
	}
	while(!in.eof()){
		char buf[1010];
		in.getline(buf,1010);
		cout<<buf<<endl;
	}
	in.close();
}
inline void insert(){
	while(1){
		win::setTitle(nowTitle);
		if(_kbhit()){
			pair<int,int> nowPos=win::getPos();
			char ch=_getch();
			switch(ch){
			case 27:
				control();//Esc
				break;
			case 13:
				cout<<'\n';//Enter
				break;
			case 10:
				win::gotoxy(nowPos.first+4,nowPos.second);//Tab
				break;
			case 8:
				win::gotoxy(nowPos.first-1,nowPos.second);//BackSpace
				cout<<" ";
				win::gotoxy(nowPos.first-1,nowPos.second);
				break;
			case 127:
				cout<<" ";//delate
				break;
			default:
				cout<<ch;
				break;
			}
		}	
	}
}
