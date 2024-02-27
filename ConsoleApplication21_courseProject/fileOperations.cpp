#define _CRT_SECURE_NO_WARNINGS
#include "prototype.h"




void storeTextToFile(char* text, FILE* file) {
	int len = strlen(text) + 1;
	fwrite(&len, sizeof(int), 1, file);
	fwrite(text, sizeof(char), len, file);
}

char* readTextFromFile(FILE* file) {
	int len;
	fread(&len, sizeof(int), 1, file);
	char* text = new char[len];
	fread(text, sizeof(char), len, file);
	return text;
}


void storeTreeToFile(FILE* file, Department* dept) {
	fwrite(dept, sizeof(Department), 1, file);
	storeTextToFile(dept->name, file);

	Subject** subjectArray = dept->subjectArr;
	Literature* temp;
	for (size_t i = 0; i < dept->subjectCount; i++)
	{
		fwrite(subjectArray[i], sizeof(Subject), 1, file);
		storeTextToFile(subjectArray[i]->name, file);
		storeTextToFile(subjectArray[i]->lecturer,file);
		temp = subjectArray[i]->firstLiterature;
		while (temp != NULL) {
			fwrite(temp, sizeof(Literature), 1, file);
			storeTextToFile(temp->name, file);
			storeTextToFile(temp->author, file);
			storeTextToFile(temp->creation_language, file);
			temp = temp->nextLiterature;
		}
	}
}

int storeTreeToFileMenu(void* ptr) {
	//Department* dept = (Department*)(ptr);

	puts("\n    --- Store tree to file ---");
	if (!rootExists()) {
		puts("Root does not exists!");
		return 0;
	}
	char* filename = getStr("Enter filename: ");
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		printf("\nSome error happened opening file \"%s\"", filename);
	}
	else {
		storeTreeToFile(file, root); 
		fprintf_s(logfile, "\nTree successfully saved to file \"%s\"", filename);
		printf("\nTree successfully saved to file \"%s\"", filename);
		fclose(file);
	}
	return 0;
}

int showTreeFromFile(void* ptr) {
	char* filename = getStr("Enter filename: ");
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		printf("\nNo such file or directory \"%s\"", filename);
	}
	else {
		Department* tempDept = new Department;
		fread(tempDept, sizeof(Department), 1, file);
		tempDept->name = readTextFromFile(file);
		printf("\n%s, load in hours - %d, is graduating - %s", tempDept->name, tempDept->load_in_hours, tempDept->is_graduating == 1? "yes":"no");
		Subject** subjectTempArr = new Subject * [tempDept->arrSize];
		tempDept->subjectArr = subjectTempArr;
		for (size_t i = 0; i < tempDept->subjectCount; i++)
		{
			subjectTempArr[i] = new Subject;
			fread(subjectTempArr[i], sizeof(Subject), 1, file);
			subjectTempArr[i]->name = readTextFromFile(file);
			subjectTempArr[i]->lecturer = readTextFromFile(file);
			printf("\n\t%s, lecturer - %s, number of tasks - %d", subjectTempArr[i]->name, subjectTempArr[i]->lecturer, subjectTempArr[i]->num_of_tasks);
						
			if (subjectTempArr[i]->firstLiterature) {
				subjectTempArr[i]->firstLiterature = restoreLiterature(file, subjectTempArr[i]);
				Literature* tempLiterature = subjectTempArr[i]->firstLiterature;
				printf("\n\t\t%s, author - %s, language - %s, creation year - %d", tempLiterature->name, tempLiterature->author, tempLiterature->creation_language, 
					tempLiterature->creation_year);
				while (tempLiterature->nextLiterature != NULL) {
					tempLiterature->nextLiterature = restoreLiterature(file, subjectTempArr[i]);
					printf("\n\t\t%s, author - %s, language - %s, creation year - %d", tempLiterature->nextLiterature->name, tempLiterature->nextLiterature->author,
						tempLiterature->nextLiterature->creation_language, tempLiterature->nextLiterature->creation_year);
					tempLiterature = tempLiterature->nextLiterature;

				}
			}
		}
		deleteAllSubjects(tempDept);
		delete[] tempDept->name;
		delete[] tempDept->subjectArr;
		delete tempDept;
		fprintf_s(logfile, "\nShowed tree from file \"%s\"", filename);
	}
	return 0;
}

void restoreTreeFromFile(FILE* file) {
	root = new Department;
	fread(root, sizeof(Department), 1, file);
	root->name = readTextFromFile(file);
	Subject** subjectTempArr = new Subject * [root->arrSize];
	root->subjectArr = subjectTempArr;
	for (size_t i = 0; i < root->subjectCount; i++)
	{
		subjectTempArr[i] = new Subject;
		fread(subjectTempArr[i], sizeof(Subject), 1, file);
		subjectTempArr[i]->name = readTextFromFile(file);
		subjectTempArr[i]->lecturer = readTextFromFile(file);

		if (subjectTempArr[i]->firstLiterature != NULL) {
			subjectTempArr[i]->firstLiterature = restoreLiterature(file, subjectTempArr[i]);
			Literature* tempLiterature = subjectTempArr[i]->firstLiterature;

			while (tempLiterature->nextLiterature != NULL) {
				tempLiterature->nextLiterature = restoreLiterature(file, subjectTempArr[i]);
				tempLiterature = tempLiterature->nextLiterature;
			}
		}
	}
}

int restoreTreeFromFileMenu(void* ptr) {
	puts("\n    --- Restoring tree from file ---\n");
	if (root == NULL) {
		char* filename = getStr("Enter filename: ");
		FILE* file = fopen(filename, "rb");
		if (file == NULL) {
			printf("\n No such file or directory \"%s\"", filename);
		}
		else {
			restoreTreeFromFile(file);
			fclose(file);
			fprintf_s(logfile, "\nRestored tree from file \"%s\"", filename);
			printf("\n Tree successfully resored from file \"%s\"\n", filename);
		}
	}
	else {
		puts("\n Tree alredy exists!");
	}
	return 0;
}

Literature* restoreLiterature(FILE* file, Subject* subj_parent) {
	Literature* temp = new Literature;
	temp->parent = subj_parent;
	fread(temp, sizeof(Literature), 1, file);
	if (temp == NULL)
		return NULL;
	temp->name = readTextFromFile(file);
	temp->author = readTextFromFile(file);
	temp->creation_language = readTextFromFile(file);
	return temp;
}