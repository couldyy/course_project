#include <stdio.h>
#include <conio.h>
#include "structs.h"
#include "prototype.h"
#include <string.h>


//write functions for structures here

Department* createDefaultTree()
{
	fprintf_s(logfile, "Started creating default tree");
	Department* department = createDepartment(getChar("FEIT"),1200,true);
	Subject* subj1 = CreateSubject(getChar("Algebra"),getChar("Ander"),120);
	Subject* subj2 = CreateSubject(getChar("Programing"),getChar("Gouda"),20);
	addSubject(department, subj1);
	addSubject(department, subj2);
	Literature* lit1 = CreateLiterature(getChar("somename1"), getChar("Arthur"), getChar("English"), 2005);
	Literature* lit2 = CreateLiterature(getChar("somename2"), getChar("Globus"), getChar("Ukrainian"), 1995);
	Literature* lit3 = CreateLiterature(getChar("somename3"), getChar("Aaron"), getChar("English"), 2012);
	Literature* lit4 = CreateLiterature(getChar("somename4"), getChar("Volodymyr"), getChar("Ukrainian"), 2015);
	Literature* lit5 = CreateLiterature(getChar("somename5"), getChar("Zebra"), getChar("Ukrainian"), 2008);

	addLiterature(subj1, lit1);
	addLiterature(subj1, lit2);
	addLiterature(subj1, lit3);
	addLiterature(subj2, lit4);
	addLiterature(subj2, lit5);
	fprintf_s(logfile, "\nDefault tree created");
	//puts("Default tree created");
	return department;
}

int createDefaultTreeMenu(void* ptr) {
	if (root == NULL) {
		root = createDefaultTree();
		puts("Defaul tree created!");
	}
	else {
		puts("Tree already exists!");
	}
	return 0;
}

Department* createDepartment(char* name, int load_in_hours,
	bool is_graduating) {
	Department* temp = new Department;
	temp->name = name;
	temp->load_in_hours = load_in_hours;
	temp->is_graduating = is_graduating;
	temp->arrSize = 2;
	temp->subjectArr = new Subject * [temp->arrSize];
	temp->subjectCount = 0;
	fprintf_s(logfile, "\nCreated department %s", temp->name);
	//printf("\nCreated department %s", temp->name);

	return temp;
}




Subject* CreateSubject(char* name, char* lecturer,
	int num_of_tasks) {
	Subject* temp = new Subject;
	temp->name = name;
	temp->lecturer = lecturer;
	temp->num_of_tasks = num_of_tasks;
	temp->parent = NULL;
	temp->firstLiterature = NULL;
	fprintf_s(logfile, "\nCreated subject %s", temp->name);

	return temp;
}

Literature*CreateLiterature(char* name, char* author,
	char* creation_language, int creation_year) {
	Literature* temp = new Literature();
	temp->name = name;
	temp->creation_language = creation_language;
	temp->author = author;
	temp->creation_year = creation_year;
	temp->nextLiterature = NULL;
	fprintf_s(logfile, "\nCreated literature object %s", temp->name);

	return temp;

}

int cmpSubjectName(Subject* obj1, Subject* obj2) {
	return strcmp(obj1->name, obj2->name);
}

int cmpLiteratureAuthor(Literature* obj1, Literature* obj2) {
	return strcmp(obj1->author, obj2->author);
}

int addSubjectMenu(void* deptPtr) {
	Department* dept = (Department*)(deptPtr);
	char* name = getStr("Enter subject name: ");
	char* lecturer = getStr("Enter lecturer name: "); //problem here
	int num_tasks;
	std::cout << "Enter number of tasks: ";
	std::cin >> num_tasks;
	Subject* tempsubj = CreateSubject(name, lecturer, num_tasks);
	addSubject(dept, tempsubj);
	//fprintf_s(logfile, "Added subject %s", tempsubj->name);
	printf("Added subject %s\n", tempsubj->name);
	puts("Subject list after adding:");
	showListOfSubjecs(dept);
	return 0;
	
}

void addSubject(Department* pDept, Subject* pSubj) {
	pSubj->parent = pDept;
	if (pDept->arrSize == pDept->subjectCount)
		growSubjectArr(pDept);
	int n = pDept->subjectCount;
	while (n > 0 && cmpSubjectName(pDept->subjectArr[n - 1], pSubj)) {
		pDept->subjectArr[n] = pDept->subjectArr[n - 1];
		n--;
	}
	pDept->subjectArr[n] = pSubj;
	pDept->subjectCount++;
	fprintf_s(logfile, "\nAdded subject %s", pSubj->name);
}

void addLiterature(Subject* pSubj, Literature* pLiterature) {
	pLiterature->parent = pSubj;
	if (pSubj->firstLiterature == NULL) {
		pSubj->firstLiterature = pLiterature;
	}
	else if (cmpLiteratureAuthor(pLiterature, pSubj->firstLiterature) < 0) {
		pLiterature->nextLiterature = pSubj->firstLiterature;
		pSubj->firstLiterature = pLiterature;
	}
	else {
		Literature* p = pSubj->firstLiterature;
		while (p->nextLiterature != NULL && cmpLiteratureAuthor(p, pLiterature) >= 0) {
			p = p->nextLiterature;
		}
		pLiterature->nextLiterature = p->nextLiterature;
		p->nextLiterature = pLiterature;
		fprintf_s(logfile, "\nAdded literature %s to subject %s", pLiterature->name, pSubj->name);
	}
}

int createRootMenu(void* ptr) {
	if (root == NULL) {
		char* newName = getStr("Enter department name: ");
		int new_loadInHours = getInt("Enter load in hours", 0, 20000);
		bool new_isGradiating = getInt("Is department graduating?(0-no, 1-yes)", 0, 1);
		root = createDepartment(newName,new_loadInHours,new_isGradiating);
		printf("Created new department %s", newName);
	}
	else {
		puts("Root already exists!");
	}
	pause();
	return 0;
}



int addLiteratureMenu(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	puts("\n    --- Literature adding ---");
	char* name = getStr("Enter literature name: ");
	char* author = getStr("Enter author name: ");
	char* creation_language = getStr("Enter literature language: ");
	int creation_year = getInt("Enter creation year: ");
	Literature* temp = CreateLiterature(name, author, creation_language, creation_year);
	addLiterature(subject, temp);
	fprintf_s(logfile, "\nAdded literature \"%s\" to subject \"%s\"", name, subject->name);
	printf("\nAdded literature \"%s\" to subject \"%s\"", name, subject->name);
	puts("\nList of literature after adding: ");
	showListOfLiterature(subject);
	return 0;

}




