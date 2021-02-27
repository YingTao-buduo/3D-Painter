#include "Texture.h"
#include <iostream>
#include <math.h>
#include <glut.h>
#include <Windows.h>
#define PI 3.14159

using namespace std;

//��ʼ��
void Init(void);
//��ʾ���
void Display(void);
//����Ҽ��Ӳ˵�
void MyMainMenu(int value);
//ʱ�亯��
void Mytime(int value);
//�ü�
void Reshape(GLsizei w, GLsizei h);
//������꽻��
void MyKeyboard(unsigned char key, int x, int y);
void MyMouse(int button, int state, int x, int y);
void MyMotion(int x, int y);
void MyPM(int x, int y);
//��ʼ����
void Start();
//���Ʊ���
void Background();
//���ƻ���
void Pad();
//���ƻ���
void Pen(int x, int y);
//���ɻ���
void DrawFree(int index);
//����ֱ��
void DrawLine(int index);
//���ƾ���
void DrawRect(int index);
//����ԲȦ
void DrawCircle(int index);
//���������
void DrawPentagon(int index);
//���������
void DrawStar(int index);
//���Ƽ�ͷ
void DrawArrow(int index);
//�������
void DrawString(const char* str);
//��������ͼ��
void Draw();