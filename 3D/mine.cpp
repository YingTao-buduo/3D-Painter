#include "mine.h"

GLuint textures[4];

void Init() {
	BuildTexture("bg.jpg", textures[0]);
	BuildTexture("wood.jpg", textures[1]);
	BuildTexture("start.jpg", textures[2]);

	GLfloat light_position[] = { -20, 1, 40, 0 };
	GLfloat light_ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat lmodel_ambient[] = { 0.8,0.2,0.2,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearColor(0, 0, 0, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_DEPTH_TEST);
}

void Reshape(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, w / h, 10, 500);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

void Start() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-500, -500, -1040);
	glTexCoord2f(0, 1);
	glVertex3f(-500, 500, -1040);
	glTexCoord2f(1, 1);
	glVertex3f(500, 500, -1040);
	glTexCoord2f(1, 0);
	glVertex3f(500, -500, -1040);
	glEnd();
}

void Pad() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-120, -12, -120);
	glTexCoord2f(0, 1);
	glVertex3f(-120, -12, 120);
	glTexCoord2f(1, 1);
	glVertex3f(120, -12, 120);
	glTexCoord2f(1, 0);
	glVertex3f(120, -12, -120);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(200.0f / 255, 200.0f / 255, 200.0f / 255);
	glBegin(GL_POLYGON);
	glVertex3f(-100,-10,-100);
	glVertex3f(-100, -10,100);
	glVertex3f(100, -10,100);
	glVertex3f(100, -10,-100);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-102, -11, -104);
	glVertex3f(-102, -11, 100);
	glVertex3f(102, -11, 100);
	glVertex3f(102, -11, -104);
	glEnd();
}

void Pen(int x, int y) {
	GLfloat mat_specular1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess1[] = { 80.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	glPushMatrix();
	glTranslatef(x, 0, y);
	
	glRotatef(105, 1, 0, 0);
	glRotatef(-10, 0, 1, 0);
	glTranslatef(0, 0, -15);

	glColor3f(139.0f/255, 115.0f /255, 85.0f /255);
	glutSolidCone(5, 15, 30, 30);

	glTranslatef(0, 0, -20);
	glColor3f(0, 0, 1);
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 5, 5, 20, 6, 32);
	
	glColor3f(1, 0, 0);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();

}

void Background() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(-250, -50, 250);
	
	glTexCoord2f(0, 1);
	glVertex3f(250, -50, 250);

	glTexCoord2f(0, 0);
	glVertex3f(250, -50, -250);

	glTexCoord2f(1, 0);
	glVertex3f(-250, -50, -250);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	len = 0;
	for (i = 0; str[i] != '\0'; ++i) {
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	if (wstring) {
		wstring[len] = L'\0';
		for (i = 0; i < len; ++i) {
			wglUseFontBitmapsW(hDC, wstring[i], 1, list);
			glCallList(list);
		}
	}

	free(wstring);
	glDeleteLists(list, 1);
}