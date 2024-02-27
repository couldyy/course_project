//#include <iostream>
//#include <stdio.h>
#include "prototype.h"



void deleteLiteratureFromSubject(Subject* subject) {
	if (subject->firstLiterature != NULL) {
		Literature *temp, *litObj = subject->firstLiterature;
		while (subject->firstLiterature != NULL) {
			temp = subject->firstLiterature;
			delete[] temp->author;
			delete[] temp->creation_language;
			delete[] temp->name;
			litObj = litObj->nextLiterature;
			subject->firstLiterature = litObj;
			delete temp;
		}
	}
}

int deleteLiteratureFromSubjectMenu(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	if (confirm("Are you sure you want to delete all literature from this subject?(0-no, 1-yes)? ")) {
		deleteLiteratureFromSubject(subject);
		fprintf_s(logfile, "\nDeleted all literature from subject %s", subject->name);
		printf("Deleted all literature from subject %s", subject->name);
	}
	return 0;
}


void deleteAllLiterature(Department* dept) {
	
	Literature* litObj, * temp;
	for (size_t i = 0; i < dept->subjectCount; i++) {
		litObj = dept->subjectArr[i]->firstLiterature;
		if (dept->subjectArr[i]->firstLiterature != NULL) {
			while (dept->subjectArr[i]->firstLiterature != NULL) {
				temp = dept->subjectArr[i]->firstLiterature;
				delete[] temp->author;
				delete[] temp->creation_language;
				delete[] temp->name;
				litObj = litObj->nextLiterature;
				dept->subjectArr[i]->firstLiterature = litObj;
				delete temp;
			}
		}
		else {
			continue;
		}
		
	}
	fprintf_s(logfile, "\nDeleted all literature from subject");
	
}

int deleteAllSubjectsMenu(void* ptr) {
	Department* dept = (Department*)(ptr);
	if(confirm()){
		deleteAllSubjects(dept);
		printf("\nSuccessfully deleted all subjects from department %s", dept->name);
	}
	return 0;
}
void deleteAllSubjects(Department* dept) {
	deleteAllLiterature(dept);
	int size = dept->subjectCount;
	for (size_t i = 0; i < size; i++) {
		delete[] dept->subjectArr[i]->name;
		delete[] dept->subjectArr[i]->lecturer;
		delete dept->subjectArr[i];
		dept->subjectCount--;
	}
	//delete[] dept->subjectArr; // probably problem here in future
	fprintf_s(logfile, "\nDeleted all subjects from department %s", dept->name);
}
int deleteSpecificSubjectMenu(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	if (confirm("Are you sure you want do delete this subject?(0-no, 1-yes)")) {
		deleteSpecificSubject(subject);
	}
	return -1;
	
}
void deleteSpecificSubject(Subject* subject) {
	Department* parent = subject->parent;
	deleteLiteratureFromSubject(subject);
	int k;
	for (k = 0; subject != subject->parent->subjectArr[k]; k++); //rewriting menu, probably problem here

	delete[] subject->name;
	delete[] subject->lecturer;
	delete subject;
	for (int i = k; i < parent->subjectCount; i++) {
		parent->subjectArr[i] = parent->subjectArr[i + 1];
	}
	parent->subjectCount--;
	parent = NULL;
	fprintf_s(logfile, "\nDeleted subject from department");
	puts("Subject deleted!");
}



void deleteDepartment(Department* dept) {
	//deleteAllLiterature(dept);
	deleteAllSubjects(dept);
	if (dept->subjectArr != NULL) {
		delete[] dept->subjectArr;
	}
	delete[] dept->name;
	delete dept;
	root = NULL;
	fprintf_s(logfile, "\nDeleted department");
	puts("Department deleted!");
	//dept = NULL;
}

int deleteDepartmentMenu(void* ptr) {
	Department* dept = (Department*)(ptr);
	if (confirm()) {
		deleteDepartment(dept);
	}
	return -1;
}

void deleteLiterature(Literature* literature) { //Problem here (Delete all literature objects) //solved
	Subject* parent = literature->parent;		//problem (cant show all literatures after delting) //solved
	if (parent->firstLiterature == literature)
		parent->firstLiterature = literature->nextLiterature;
	else {
		Literature* temp = parent->firstLiterature;
		while (temp->nextLiterature != literature && temp != NULL) {
			temp = temp->nextLiterature;
		}
		if (temp == NULL)
			return;
		temp->nextLiterature = literature->nextLiterature;
	}
	delete[]literature->name;
	delete[]literature->author;
	delete[]literature->creation_language;
	delete literature;
	fprintf_s(logfile, "\nDeleted literature from subject \"%s\"", parent->name);
}

int deleteLiteratureMenu(void* ptr) {
	Literature* literature = (Literature*)(ptr);
	if (confirm()) {
		deleteLiterature(literature);
		puts("Literature deleted!");
	}
	return 0;
}