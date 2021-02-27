#include "mine.h"

#define N 10000

int ww = 1000, hh = 1000;
int point[N][3], p = 0;
int f[N];
int flag_p = 1;
int line[N][5], l = 0;
int rect[N][5], r = 0;
int circle[N][4], o = 0;
int pentagon[N][4], u = 0;
int star[N][4], s = 0;
int arrow[N][5], a = 0;

int flag = 1;
int color = 3;
bool ex = true;
bool start = true;

int px, py;
double cx = 0, cy = 0, cz = -1500;
double ax = 0, ay = 0, az = 0;

int main() {
	char* argv[] = { "hello ", " " };
	int argc = 2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //设置显示模式；（缓冲，颜色类型）
	glutInitWindowSize(ww, hh);
	glutInitWindowPosition(1024 / 2 - 250, 768 / 2 - 250);
	glutCreateWindow("Sketch PAD");
	glutReshapeFunc(Reshape);
	Init();
	glutDisplayFunc(Display);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);    //注册鼠标按钮回调函数
	glutMotionFunc(MyMotion);  //注册鼠标移动回调函数
	glutPassiveMotionFunc(MyPM);
	int menuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("RED", 1);
	glutAddMenuEntry("BLUE", 2);
	glutAddMenuEntry("BLACK", 3);
	glutAddMenuEntry("CLEAN", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc(15, Mytime, 10);
	glutMainLoop();
	return 0;
}

void Display(void) {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cx, cy, cz, ax, ay, az, 0, 1, 0);
	glRasterPos3f(-20, 5, -110);
	DrawString("1801010019  郑文道");
	if(start)
		Start();
	Background();
	Pad();
	Pen(px, py);
	glRasterPos3f(-50, 5, 100);
	DrawString("1、草图  2、直线  3、矩形  4、圆形  5、五边形  6、星形  7、箭头");
	switch (color) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	if (flag == 1 && ex) {
		DrawFree(p);
	}
	else if (flag == 2 && ex) {
		DrawLine(l);
	}
	else if (flag == 3 && ex) {
		DrawRect(r);
	}
	else if (flag == 4 && ex) {
		DrawCircle(o);
	}
	else if (flag == 5 && ex) {
		DrawPentagon(u);
	}
	else if (flag == 6 && ex) {
		DrawStar(s);
	}
	else if (flag == 7 && ex) {
		DrawArrow(a);
	}
	Draw();
	
	glutSwapBuffers();
}

void Mytime(int value) {
	glutPostRedisplay();
	glutTimerFunc(15, Mytime, 10);
}

void MyKeyboard(unsigned char key, int x, int y) {
	ex = false;
	switch (key) {
	case '1': flag = 1;   //草图
		break;
	case '2': flag = 2;   //直线段
		break;
	case '3': flag = 3;   //矩形
		break;
	case '4': flag = 4;   //三角形
		break;
	case '5': flag = 5;   //五边形
		break;
	case '6': flag = 6;   //五角星
		break;
	case '7': flag = 7;   //箭头
		break;
	case 13:
		start = false;
		cx = 0, cy = 120, cz = 50;
		ax = 0, ay = -200, az = -20;
		break;
	default:
		break;
	}
}

void MyMouse(int button, int state, int x, int y) {
	px = x / 5 - 100;
	py = y / 5 - 100;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1) {
		point[p][0] = x / 5 - 100;
		point[p][1] = y / 5 - 100;
		flag_p = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 2) {
		line[l][0] = x / 5 - 100;
		line[l][1] = y / 5 - 100;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 2) {
		line[l][2] = x / 5 - 100;
		line[l][3] = y / 5 - 100;
		line[l][4] = color;
		l++;
		glutPostRedisplay();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 3) {
		rect[r][0] = x / 5 - 100;
		rect[r][1] = y / 5 - 100;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 3) {
		rect[r][2] = x / 5 - 100;
		rect[r][3] = y / 5 - 100;
		rect[r][4] = color;
		r++;
		glutPostRedisplay();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 4) {
		circle[o][0] = x / 5 - 100;
		circle[o][1] = y / 5 - 100;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 4) {
		circle[o][2] = (int)sqrt((x / 5 - 100 - circle[o][0]) * (x / 5 - 100 - circle[o][0]) + (y / 5 - 100 - circle[o][1]) * (y / 5 - 100 - circle[o][1]));
		circle[o][3] = color;
		o++;
		glutPostRedisplay();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 5) {
		pentagon[u][0] = x / 5 - 100;
		pentagon[u][1] = y / 5 - 100;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 5) {
		pentagon[u][2] = (int)sqrt((x / 5 - 100 - pentagon[u][0]) * (x / 5 - 100 - pentagon[u][0]) + (y / 5 - 100 - pentagon[u][1]) * (y / 5 - 100 - pentagon[u][1]));
		pentagon[u][3] = color;
		u++;
		glutPostRedisplay();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 6) {
		star[s][0] = x / 5 - 100;
		star[s][1] = y / 5 - 100;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 6) {
		star[s][2] = (int)sqrt((x / 5 - 100 - star[s][0]) * (x / 5 - 100 - star[s][0]) + (y / 5 - 100 - star[s][1]) * (y / 5 - 100 - star[s][1]));
		star[s][3] = color;
		s++;
		glutPostRedisplay();
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 7) {
		arrow[a][0] = x / 5 - 100;
		arrow[a][1] = y / 5 - 100;

	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && flag == 7) {
		arrow[a][2] = x / 5 - 100;
		arrow[a][3] = y / 5 - 100;
		arrow[a][4] = color;
		a++;
		glutPostRedisplay();
	}
}
void MyMotion(int x, int y) {
	ex = true;
	if (flag == 1 && flag_p == 1) {
		p++;
		point[p][2] = color;
		point[p][0] = x / 5 - 100;
		point[p][1] = y / 5 - 100;
	}
	if (flag == 1 && flag_p == 0) {
		point[p][0] = x / 5 - 100;
		point[p][1] = y / 5 - 100;
		f[p] = 1;
		flag_p = 1;
	}

	line[l][2] = x / 5 - 100;
	line[l][3] = y / 5 - 100;

	rect[r][2] = x / 5 - 100;
	rect[r][3] = y / 5 - 100;

	circle[o][2] = (int)sqrt((x / 5 - 100 - circle[o][0]) * (x / 5 - 100 - circle[o][0]) + (y / 5 - 100 - circle[o][1]) * (y / 5 - 100 - circle[o][1]));

	pentagon[u][2] = (int)sqrt((x / 5 - 100 - pentagon[u][0]) * (x / 5 - 100 - pentagon[u][0]) + (y / 5 - 100 - pentagon[u][1]) * (y / 5 - 100 - pentagon[u][1]));

	star[s][2] = (int)sqrt((x / 5 - 100 - star[s][0]) * (x / 5 - 100 - star[s][0]) + (y / 5 - 100 - star[s][1]) * (y / 5 - 100 - star[s][1]));

	arrow[a][2] = x / 5 - 100;
	arrow[a][3] = y / 5 - 100;

	px = x / 5 - 100;
	py = y / 5 - 100;
	glutPostRedisplay();
}

void MyPM(int x, int y) {
	px = x / 5 - 100;
	py = y / 5 - 100;
}

void DrawFree(int index) {
	switch (point[index][2]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	if (index && flag_p == 1 && f[index] == 0) {
		glBegin(GL_LINES);
		glVertex3f(point[index - 1][0], 0, point[index - 1][1]);
		glVertex3f(point[index][0], 0, point[index][1]);
		glEnd();
	}
}

void DrawLine(int index) {
	switch (line[index][4]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_LINES);
	glVertex3f(line[index][0], 0, line[index][1]);
	glVertex3f(line[index][2], 0, line[index][3]);
	glEnd();
}

void DrawRect(int index) {
	switch (rect[index][4]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_LINES);
	glVertex3f(rect[index][0], 0, rect[index][1]);
	glVertex3f(rect[index][2], 0, rect[index][1]);
	glVertex3f(rect[index][0], 0, rect[index][1]);
	glVertex3f(rect[index][0], 0, rect[index][3]);
	glVertex3f(rect[index][2], 0, rect[index][1]);
	glVertex3f(rect[index][2], 0, rect[index][3]);
	glVertex3f(rect[index][0], 0, rect[index][3]);
	glVertex3f(rect[index][2], 0, rect[index][3]);
	glEnd();

}

void DrawCircle(int index) {
	switch (circle[index][3]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 30; i++) {
		glVertex3f(circle[index][2] * cos(2 * PI / 30 * i) + circle[index][0], 0, circle[index][2] * sin(2 * PI / 30 * i) + circle[index][1]);
	}
	glEnd();
}

void DrawPentagon(int index) {
	switch (pentagon[index][3]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 5; i++) {
		glVertex3f(pentagon[index][2] * cos(2 * PI / 5 * i) + pentagon[index][0], 0, pentagon[index][2] * sin(2 * PI / 5 * i) + pentagon[index][1]);
	}
	glEnd();
}

void DrawStar(int index) {
	switch (star[index][3]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 5; i++) {
		glVertex3f(star[index][2] * cos(2 * PI / 5 * i) + star[index][0], 0, star[index][2] * sin(2 * PI / 5 * i) + star[index][1]);
		glVertex3f(star[index][2] / 2 * cos(2 * PI / 5 * i + PI / 5) + star[index][0], 0, star[index][2] / 2 * sin(2 * PI / 5 * i + PI / 5) + star[index][1]);
	}
	glEnd();
}

void DrawArrow(int index) {
	switch (arrow[index][4]) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 0, 0);
		break;
	}
	glBegin(GL_TRIANGLES);
	glVertex3f(arrow[index][0] - (arrow[index][3] - arrow[index][1]), 0, arrow[index][1] + (arrow[index][2] - arrow[index][0]));
	glVertex3f(arrow[index][0] + (arrow[index][3] - arrow[index][1]), 0, arrow[index][1] - (arrow[index][2] - arrow[index][0]));
	glVertex3f(arrow[index][0] - (arrow[index][2] - arrow[index][0]), 0, arrow[index][1] - (arrow[index][3] - arrow[index][1]));
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(arrow[index][0] - (arrow[index][3] - arrow[index][1]) / 2, 0, arrow[index][1] + (arrow[index][2] - arrow[index][0]) / 2);
	glVertex3f(arrow[index][2] - (arrow[index][3] - arrow[index][1]) / 2, 0, arrow[index][3] + (arrow[index][2] - arrow[index][0]) / 2);
	glVertex3f(arrow[index][2] + (arrow[index][3] - arrow[index][1]) / 2, 0, arrow[index][3] - (arrow[index][2] - arrow[index][0]) / 2);
	glVertex3f(arrow[index][0] + (arrow[index][3] - arrow[index][1]) / 2, 0, arrow[index][1] - (arrow[index][2] - arrow[index][0]) / 2);
	glEnd();
}

void Draw() {
	for (int i = 0; i < p; i++) {
		DrawFree(i);
	}
	for (int i = 0; i < l; i++) {
		DrawLine(i);
	}
	for (int i = 0; i < r; i++) {
		DrawRect(i);
	}
	for (int i = 0; i < o; i++) {
		DrawCircle(i);
	}
	for (int i = 0; i < u; i++) {
		DrawPentagon(i);
	}
	for (int i = 0; i < s; i++) {
		DrawStar(i);
	}
	for (int i = 0; i < a; i++) {
		DrawArrow(i);
	}
}

void MyMainMenu(int value) {
	ex = false;
	switch (value) {
	case 1:
		color = 1;
		break;
	case 2:
		color = 2;
		break;
	case 3:
		color = 3;
		break;
	default:
		memset(point, 0 ,N * 4);
		memset(rect, 0 ,N * 4);
		memset(line, 0 ,N * 4);
		memset(circle, 0 ,N * 4);
		memset(pentagon, 0 ,N * 4);
		memset(star, 0 ,N * 4);
		memset(arrow, 0 ,N * 4);
		p = 0;
		l = 0;
		o = 0;
		r = 0;
		u = 0;
		s = 0;
		a = 0;
		break;
	}
}