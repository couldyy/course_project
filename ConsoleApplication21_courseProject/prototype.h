#pragma once

#include "structs.h"
#include <stdio.h>
#include <iostream>
//#include <cstring> //std::getline isn't working with that lib
#include <string>

typedef int MenuFunc(void*);


extern FILE *logfile;
extern Department* root;
enum deptFields;
enum subjectFields;
enum literatureFields;




void runMenu(MenuUnit* menu, const char* title, void* ptr);

int mainMenu(void* ptr);
int departmenMenu(void* ptr);

int subjectMenu(void* ptr);
int selectSubject(Department* dept);
Literature* selectLiterature(Subject* subject);

int literatureMenu(void* ptr);
int treeOperationMenu(void* ptr);
int queryOperationsMenu(void* ptr);

void pause();
int showProjectInfo(void* ptr);

void growSubjectArr(Department* pDept);

inline int cmpSubjectName(Subject* obj1, Subject* obj2);
inline int cmpLiteratureAuthor(Literature* obj1, Literature* obj2);

void addSubject(Department* pDept, Subject* pSubj);
void addLiterature(Subject* pSubj, Literature* pLiterature);

int createRootMenu(void* ptr);
int createDefaultTreeMenu(void* ptr);

Department* createDefaultTree();
Department* createDepartment(char* name, int load_in_hours,
	bool is_graduating);

Subject* CreateSubject(char* name, char* lecturer,
	int num_of_tasks);

Literature* CreateLiterature(char* name, char* author,
	char* creation_language, int creation_year);
int addSubjectMenu(void* deptPtr);
int addLiteratureMenu(void* ptr);

int showWholeTree(void* ptr);
int showInfoSpecificSubject(void* ptr);
int showListOfLiterature(void* ptr);
int showLiteratureInfo(void* ptr);
int showDepartmentInfo(void* ptr);

void deleteAllLiterature(Department* dept);
void deleteAllSubjects(Department* dept);
int deleteAllSubjectsMenu(void* ptr);

int deleteSpecificSubjectMenu(void* ptr);
void deleteSpecificSubject(Subject* subject);

void deleteDepartment(Department* dept);
int deleteDepartmentMenu(void* ptr);
void deleteLiteratureFromSubject(Subject* subject);
int deleteLiteratureFromSubjectMenu(void* ptr);
void deleteLiterature(Literature* literature);
int deleteLiteratureMenu(void* ptr);

int editDepartmentMenu(void* deptPtr);
void editDepartmentInfo(Department* dept, deptFields field);
int editSubjectMenu(void* ptr);
void editSubject(Subject* subject, subjectFields field);
int editLiteratureInfoMenu(void* ptr);
void editLiteratureInfo(Literature* literature, literatureFields field);


char* getStr(const char* prompt);
int getInt(const char* prompt);
int getInt(const char* prompt, int min, int max);
char* getChar(const char* str);
int rootExists();
int confirm();
int confirm(const char* prompt);
int showlogFile(void* ptr);

int showListOfSubjecs(void* dept);
int printAllHoursSubject(void* dept);
int printOldestLiterature(void* dept);
int printLiteratureCreatedLaterEntered(void* dept);
int printSubjectsTasksGreaterEntered(void* dept);

int storeTreeToFileMenu(void* ptr);
void storeTreeToFile(FILE* file, Department* dept);
void storeTextToFile(char* text, FILE* file);
int showTreeFromFile(void* ptr);
char* readTextFromFile(FILE* file);
Literature* restoreLiterature(FILE* file, Subject* parent);
void restoreTreeFromFile(FILE* file);
int restoreTreeFromFileMenu(void* ptr);

int calculateTreeSize(void* ptr);

