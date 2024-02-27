#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include "prototype.h"
#include "structs.h"

FILE* logfile;
Department* root;

int main() {
	int k;
	for (k = 0; k !=10; k++);
	std::cout << k << std::endl;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	logfile = fopen("logfile", "wt+");

	showProjectInfo(NULL);

	root = createDefaultTree();
	showWholeTree(NULL);
	//root = createDepartment(getChar("somename"), 15, true);
	//std::cout << root->arrSize;
	//growSubjectArr(root);
	//std::cout << root->arrSize;

	mainMenu(NULL);
	showlogFile(NULL);
	fclose(logfile);

	return 0;
}