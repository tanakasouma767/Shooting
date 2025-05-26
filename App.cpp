#include "App.h"
#include "Scene.h"

bool keyStates[256] = { false }; // 全キーの押下状態

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	g_Scene->Draw();
	glFlush();
}

void Idle() {
	g_Scene->Update();
	glutPostRedisplay();
}

void MyKbd(unsigned char key, int x, int y) {
	keyStates[key] = true;
	if (key == KEY_ESC) {
		exit(0);
	}
}

void MyKbdUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void InitWindow(const char* appName) {
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(appName);

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glutKeyboardFunc(MyKbd);
	glutKeyboardUpFunc(MyKbdUp);
}

void StartApp(const char* appName) {

	// シーン初期化
	g_Scene = new Scene();
	if (!g_Scene->Init())
	{
		return;
	}

	InitWindow(appName);
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutMainLoop();
}