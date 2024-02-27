#include <iostream>
#include "prototype.h"

enum deptFields {
	DEPT_NAME,
	IS_GRADUATING,
	LOAD_IN_HOURS
};

enum subjectFields {
	SUBJECT_NAME,
	LECTURER,
	NUM_OF_TASKS,
};

enum literatureFields {
	LITERATURE_NAME,
	AUTHOR,
	CREATION_LANGUAGE,
	CREATION_YEAR,
};

int editDepartmentMenu(void* deptPtr) {
	if (rootExists()) {
		if (confirm("Are you sure you want to change department info?(type 1 if yes, otherwise 0): ")) {
			Department* dept = (Department*)(deptPtr);
			int field;
			deptFields deptField;
			while(true){
				printf("\n1. %s", dept->name);
				printf("\n2. Is graduating: %s", dept->is_graduating == 1 ? "yes" : "no");
				printf("\n3. Loads in hours: %d", dept->load_in_hours);
				printf("\n4. Quit");
				std::cout << "\nEnter field to change: ";
				std::cin >> field;
				deptField = static_cast<deptFields>(field - 1);
				if (field < 1 || field >4) {
					
					puts("Wrong input!");
				}
				else if (field == 4)
					break;
				else {
					editDepartmentInfo(dept, deptField);
				}
			}
		}
	}
	return 0;
}

void editDepartmentInfo(Department* dept, deptFields field) {
	char* newName;
	bool new_is_graduating;
	switch (field) {
	case deptFields::DEPT_NAME:
		newName = getStr("Enter new name: ");
		delete[]dept->name;
		dept->name = newName;
		fprintf_s(logfile, "\nChanged department name to %s", newName);
		
		printf("Changed department name to %s\n", newName);
		break;
	case deptFields::IS_GRADUATING:
		new_is_graduating = getInt("Is department graduating?(1-yes, 0-no) ", 0,1);
		dept->is_graduating = new_is_graduating;
		fprintf_s(logfile, "\nChanged department field \"is_graduating\" to %s", new_is_graduating == 1 ? "yes" : "no");
		
		break;
	case deptFields::LOAD_IN_HOURS:
		int new_loads_hours = getInt("How much load in hours?", 0, 20000);
		dept->load_in_hours = new_loads_hours;
		fprintf_s(logfile, "\nChanged department field \"load_in_hours\" to %d", new_loads_hours);
		
		break;
	}
}

int editSubjectMenu(void* ptr) {
	Subject* subject = (Subject*)(ptr);
	puts("\n    --- Subject info editing ---");
	if (confirm("Are you sure you want to change subject info?(type 1 if yes, otherwise 0): ")) {
		int field;
		subjectFields subjectField;
		while (true){
			printf("\n 1. Subject name - %s", subject->name);
			printf("\n 2. Lecturer - %s", subject->lecturer);
			printf("\n 3. Number of tasks - %d", subject->num_of_tasks);
			printf("\n 4. Quit");
			std::cout << "\nEnter field to change: ";
			std::cin >> field;
			subjectField = static_cast<subjectFields>(field - 1);
			if (field < 1 || field >4) {
				
				puts("Wrong input!");
			}
			else if (field == 4)
				break;
			else {
				editSubject(subject, subjectField);
			}
		}
	}
	return 0;
}

void editSubject(Subject* subject, subjectFields field) {
	char* new_name, * new_lecturer;
	int new_numOfTasks;
	switch (field)
	{
	case SUBJECT_NAME:
		new_name = getStr("Enter new subject name: ");
		delete[] subject->name;
		subject->name = new_name;
		fprintf_s(logfile, "\nChanged name to \"%s\" in subject \"%s\"", new_name, subject->name);
		
		printf("\nChanged name to \"%s\" in subject \"%s\"", new_name, subject->name);
		break;
	case LECTURER:
		new_lecturer = getStr("Enter new lecturer name: ");
		delete[] subject->lecturer;
		subject->lecturer = new_lecturer;
		fprintf_s(logfile, "\nChanged lecturer name to \"%s\" in subject \"%s\"", new_lecturer, subject->name);
		
		printf("\nChanged lecturer name to \"%s\" in subject \"%s\"", new_lecturer, subject->name);
		break;
	case NUM_OF_TASKS:
		new_numOfTasks = getInt("Eneter new number of tasks", 0, 200);
		subject->num_of_tasks = new_numOfTasks;
		fprintf_s(logfile, "\nChanged number of tasks to %d in subject \"%s\"", new_numOfTasks, subject->name);
		
		printf("\nChanged number of tasks to %d in subject \"%s\"", new_numOfTasks, subject->name);
		break;
	default:
		break;
	}
}

int editLiteratureInfoMenu(void* ptr) {
	Literature* literature = (Literature*)(ptr);
	puts("\n    --- Literature info editing ---");
	if (confirm("Are you sure you want to change literature info?(type 1 if yes, otherwise 0): ")) {
		int field;
		literatureFields literatureField;
		while (true) {
			printf("\n 1. Literature name - %s", literature->name);
			printf("\n 2. Author - %s", literature->author);
			printf("\n 3. Language - %s", literature->creation_language);
			printf("\n 4. Creation year - %d", literature->creation_year);
			printf("\n 5. Quit");
			std::cout << "\nEnter field to change: ";
			std::cin >> field;
			literatureField = static_cast<literatureFields>(field - 1);
			if (field < 1 || field >5) {
				
				puts("Wrong input!");
			}
			else if (field == 5)
				break;
			else {
				editLiteratureInfo(literature, literatureField);
			}
		}
	}
	return 0;
}

void editLiteratureInfo(Literature* literature, literatureFields field) {
	char* new_name;
	char* new_author;
	char* new_creation_language;
	switch (field)
	{
	case LITERATURE_NAME:
		delete[] literature->name;
		new_name = getStr("Enter new name: ");
		literature->name = new_name;
		fprintf_s(logfile, "\nChanged name in literature to \"%s\"", new_name);
		
		printf("Changed name in literature to \"%s\"", new_name);
		break;
	case AUTHOR:
		delete[] literature->author;
		new_author = getStr("Enter author name: ");
		literature->author = new_author;
		fprintf_s(logfile, "\nChanged author in literature \"%s\" to \"%s\"", literature->name, new_author);
		
		printf("Changed author in literature \"%s\" to \"%s\"", literature->name, new_author);
		break;
	case CREATION_LANGUAGE:
		delete[] literature->creation_language;
		new_creation_language = getStr("Enter literature language: ");
		literature->creation_language = new_creation_language;
		fprintf_s(logfile, "\nChanged language in literature \"%s\" to \"%s\"", literature->name, new_creation_language);
		
		printf("Changed language in literature \"%s\" to \"%s\"", literature->name, new_creation_language);
		break;
	case CREATION_YEAR:
		int new_creationYear = getInt("Enter literature creation year: ");
		literature->creation_year = new_creationYear;
		fprintf_s(logfile, "\nChanged creation year in literature \"%s\" to %d", literature->name, new_creationYear);
		
		printf("Changed creation year in literature \"%s\" to %d", literature->name, new_creationYear);
		break;
	}
}