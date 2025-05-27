#include <iostream>
#include <windows.h>
#include "App.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    StartApp("Shooting");
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char* argv[] = { (char*)"" };
    glutInit(&argc, argv);
    StartApp("Shooting");
    return 0;
}