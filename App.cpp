#include "App.h"
#include "Scene.h"
#include <thread>
#include <chrono>

using namespace std;

bool keyStates[256] = { false }; // 全キーの押下状態

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	g_Scene->Draw();
	//glFlush();
	glutSwapBuffers();
}

void Idle() {
	static auto lastTime = chrono::high_resolution_clock::now();

	g_Scene->Update();
	glutPostRedisplay();

	auto now = chrono::high_resolution_clock::now();
	auto frameTime = chrono::duration_cast<chrono::milliseconds>(now - lastTime).count();

	int targetFrameTime = 1000 / 120; // 120fpsに制限
	if (frameTime < targetFrameTime) {
		this_thread::sleep_for(chrono::milliseconds(targetFrameTime - frameTime));
	}

	lastTime = chrono::high_resolution_clock::now();
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
	//glutInitDisplayMode(GLUT_RGBA);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
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