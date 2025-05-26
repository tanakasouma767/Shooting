#include <GL/glut.h>
#include <GL/gl.h>
#define KEY_ESC 27
#define KEY_ENTER 13

#pragma once

const int width = 500;
const int height = 500;
void StartApp(const char* appName);
extern bool keyStates[256];