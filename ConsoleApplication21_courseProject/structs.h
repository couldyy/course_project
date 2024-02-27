#pragma once
typedef int MenuFunc(void*);

struct Subject;
struct Department;
struct Literature;

struct MenuUnit;

struct MenuUnit {
	const char* text;
	MenuFunc* func;
};

struct Department {
public:
	char* name;
	int load_in_hours;
	int is_graduating;  //might cause problems(changed bool to int)
	Subject** subjectArr;
	int arrSize;
	int subjectCount;
};

struct Subject {
	char* name;
	char* lecturer;
	int num_of_tasks;

	Literature* firstLiterature;
	Department* parent;
};

struct Literature {
	char* name;
	char* author;
	char* creation_language;
	int creation_year;

	Literature* nextLiterature;
	Subject* parent;
};