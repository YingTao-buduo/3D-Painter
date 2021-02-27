#include "Texture.h"
#include <iostream>
#include <math.h>
#include <glut.h>
#include <Windows.h>
#define PI 3.14159

using namespace std;

//初始化
void Init(void);
//显示输出
void Display(void);
//鼠标右键子菜单
void MyMainMenu(int value);
//时间函数
void Mytime(int value);
//裁剪
void Reshape(GLsizei w, GLsizei h);
//键盘鼠标交互
void MyKeyboard(unsigned char key, int x, int y);
void MyMouse(int button, int state, int x, int y);
void MyMotion(int x, int y);
void MyPM(int x, int y);
//开始界面
void Start();
//绘制背景
void Background();
//绘制画板
void Pad();
//绘制画笔
void Pen(int x, int y);
//自由绘制
void DrawFree(int index);
//绘制直线
void DrawLine(int index);
//绘制矩形
void DrawRect(int index);
//绘制圆圈
void DrawCircle(int index);
//绘制五边形
void DrawPentagon(int index);
//绘制五角星
void DrawStar(int index);
//绘制箭头
void DrawArrow(int index);
//汉字输出
void DrawString(const char* str);
//绘制所有图案
void Draw();