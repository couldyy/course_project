#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
//#include <cstring>
#include "prototype.h"


void pause() {
	std::cout << "\n\nДля продовження натисніть будь-яку клавішу...\n";
	_getch();
}

int showProjectInfo(void* ptr) {
	
	puts("Проєкт \"Бібліотека\"");
	puts("Розробник Погодін А.І., гр. КІ-233");
	puts("\tДата народження 17.07.2006.");
	puts("\tВаріант 18.\n");
	puts("Корінь: Кафедра");
	puts("\tполя: назва, навантаження в годинах, чи випускаюча");
	puts("1-й рівень: предмет");
	puts("\tполя: назва, викладач, кількість робіт");
	puts("2-й рівень: література");
	puts("\tполя: назва, автор, мова написання, рік створення\n");
	pause();
	return 0;
	
}

void growSubjectArr(Department* pDept) {
	int newSize = pDept->arrSize * 1.5 + 0.5;

	Subject** newArr = new Subject * [newSize];
	memcpy(newArr, pDept->subjectArr, pDept->arrSize * sizeof(Subject*));
	pDept->arrSize = newSize;
	delete[] pDept->subjectArr;
	pDept->subjectArr = newArr;
	newArr = NULL;
	fprintf_s(logfile, "\nArray size increased to %d", newSize);
}

char* getChar(const char* str) {
	int size = 0, i=0;
	while (str[i] != '\0')
	{
		size++;
		i++;
	}
	size++;
	char* newStr = new char[size];
	for (i = 0; i < size-1; i++) {
		newStr[i] = str[i];
	}
	newStr[size-1] = '\0';
	return newStr;
}



int showWholeTree(void* ptr) {
	if (rootExists()) {
		puts("\n   --- Tree Structure ---");
		printf("\nName: %s, load in hours %d, is graduatin: %s", root->name, root->load_in_hours, root->is_graduating == 1 ? "yes" : "no");
		size_t k;
		Literature* litObj;
		if (root->subjectCount > 0) {
			for (size_t i = 0; i < root->subjectCount; i++) {
				printf("\n\tSubject name: %s, lecturer: %s, num of tasks: %d", root->subjectArr[i]->name, root->subjectArr[i]->lecturer, root->subjectArr[i]->num_of_tasks);
				if (root->subjectArr[i]->firstLiterature != NULL) {
					litObj = root->subjectArr[i]->firstLiterature;
					while (litObj != NULL) {
						printf("\n\t\t%s, %s, %s, %d", litObj->name, litObj->author, litObj->creation_language, litObj->creation_year);
						litObj = litObj->nextLiterature;
					}
				}
			
			}
		}
	}
	
	pause();
	return 0;
	
}

int getInt(const char* prompt, int min, int max) {
	int num; 
	do {
		printf("%s(%d..%d): ", prompt, min, max);
		fflush(stdin);
		std::cin >> num;
	} while (num < min || num > max);
	return num;
}

int getInt(const char* prompt) {
	int temp;
	std::cout << prompt;
	std::cin >> temp;
	return temp;
}

char* getStr(const char* prompt) {
	std::cout << prompt;
	std::string s;
	fflush(stdin);
	std::getline(std::cin>>std::ws, s);
	int size = s.length() + 1;
	char* cStr = new char[size];
	strncpy(cStr, s.c_str(), size);
	return cStr;
}

int rootExists() {
	if (root == NULL) {
		
		std::cout << "\nTree does not exist!" << std::endl;
		return 0;
	}
	return root != NULL;
}

int confirm() {
	int input;
	do
	{
		std::cout << "\nAre you sure you want to proceed?(type 1 if yes, otherwise 0): ";
		std::cin >> input;
		fflush(stdin);
	} while (input < 0 || input >1);
	
	return input == 1;
}
int confirm(const char* prompt) {
	int input;
	do
	{
		std::cout << prompt;
		std::cin >> input;
		fflush(stdin);
	} while (input < 0 || input >1);
	return input == 1;
}

int showlogFile(void* ptr) {
	puts("\n\tВиведення файлу протоколу");
	puts("\t  --------------------");
	rewind(logfile);
	char c = fgetc(logfile);
	while (c != EOF) {
		std::cout << c;
		c = fgetc(logfile);
	}
	puts("\n\t  --------------------");
	fseek(logfile, 0, SEEK_END);
	fprintf_s(logfile, "\nLogfile have been shown.");
	return 0;
}

int showListOfSubjecs(void* ptr) {
	Department* dept = (Department*)(ptr);
	if (rootExists()) {
		if (root->subjectCount > 0) {
			for (size_t i = 0; i < root->subjectCount; i++) {
				printf("\n\t %d. %s, lecturer: %s, num of tasks: %d",i+1, root->subjectArr[i]->name, root->subjectArr[i]->lecturer, root->subjectArr[i]->num_of_tasks);
			}
		}
		else {
			puts("There is no subjects!");
		}
	}
	return 0;
}

Literature* selectLiterature(Subject* subject) {
	puts("\n    --- Literature selection ---");
	int n = 1;
	Literature* temp = subject->firstLiterature;
	while (temp != NULL) {
		printf("\n %d. %s, %s", n, temp->name, temp->author);
		temp = temp->nextLiterature;
		n++;
	}
	printf("\n %d. Exit", n);

	int choise = getInt("\nSelect literature for further operations", 1, n);
	if (choise == n)
		return NULL;

	temp = subject->firstLiterature;
	for (n = 1; n < choise; n++) {
		temp = temp->nextLiterature;
	}
	return temp;
}

int selectSubject(Department* dept) {
	puts("\n    --- Subject selection ---");
	if (dept->subjectCount > 0) {
		int i;
		for (i = 0; i < dept->subjectCount; i++)
		{
			//printf("\n\t %d. %s, lecturer: %s, num of tasks: %d", i + 1, root->subjectArr[i]->name, root->subjectArr[i]->lecturer, root->subjectArr[i]->num_of_tasks);
			printf("\n %d. %s", i + 1, dept->subjectArr[i]->name);
		}
		printf("\n %d. Exit", i + 1);
		int choise = getInt("\nSelect subject for further operations", 1, i+1);
		if (choise == i + 1) {
			return -1;
		}
		return choise - 1;
	}
	else {
		puts("There are no subjects!");
	}
}
int showListOfLiterature(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	puts("\n    --- List of literature ---");
	if (subject->firstLiterature != NULL) {
		Literature* litObj;
		litObj = subject->firstLiterature;
		int i = 1;
		while (litObj != NULL) {
			printf("\n %d. %s, %s, %s, %d",i, litObj->name, litObj->author, litObj->creation_language, litObj->creation_year);
			litObj = litObj->nextLiterature;
			i++;
		}
	}
	else {
		puts("\nNo literature connected to this subject");
	}
	fprintf_s(logfile, "\nShowed literature list of subject %s", subject->name);
	return 0;
}

int showInfoSpecificSubject(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	puts("\n    --- Subject Info ---");
	printf("\n %s, lecturer: %s, num of tasks: %d",subject->name, subject->lecturer, subject->num_of_tasks);
	if (subject->firstLiterature != NULL) {
		Literature* litObj;
		litObj = subject->firstLiterature;
		while (litObj != NULL) {
			printf("\n\t%s, %s, %s, %d", litObj->name, litObj->author, litObj->creation_language, litObj->creation_year);
			litObj = litObj->nextLiterature;
		}
	}
	fprintf_s(logfile, "\nShowed info about subject %s", subject->name);
	return 0;
}

int showLiteratureInfo(void* ptr) {
	Literature* literature = (Literature*)(ptr);
	puts("\n    --- Literature info ---");
	printf("\n Name - %s", literature->name);
	printf("\n Author - %s", literature->author);
	printf("\n Language - %s", literature->creation_language);
	printf("\n Creation year - %d", literature->creation_year);
	fprintf_s(logfile, "\nShowed info about literature \"%s\"", literature->name);
	return 0;
}

int showDepartmentInfo(void* ptr) {
	Department* dept = (Department*)(ptr);
	puts("\n    --- Department info ---");
	printf("\nName - %s", dept->name);
	printf("\nLoad in hours - %d", dept->load_in_hours);
	printf("\nIs graduating - %s", dept->is_graduating == 1 ? "yes" : "no");
	return 0;
}

int calculateTreeSize(void* ptr) {
	Department* dept = (Department*)(ptr);
	int sizeDept = sizeof(Department), sizeSubjects = 0, sizeLiteratures = 0, sum = 0;
	Literature* literature_temp;

	for (int i = 0; i < dept->subjectCount; i++) {
		sizeSubjects += sizeof(Subject);
		literature_temp = dept->subjectArr[i]->firstLiterature;
		while (literature_temp != NULL) {
			sizeLiteratures += sizeof(Literature);
			literature_temp = literature_temp->nextLiterature;
		}
	}
	sum = sizeDept + sizeSubjects + sizeLiteratures;
	printf("\nTree = %d bytes\nDept = %d bytes\nSubjects = %d bytes\nLiteratures = %d bytes", sum, sizeDept, sizeSubjects, sizeLiteratures);
	fprintf_s(logfile, "\nClaculated and showed size of tree");
	return 0;
}
