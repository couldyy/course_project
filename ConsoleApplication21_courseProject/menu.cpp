#include "structs.h"
#include "prototype.h"
#include <iostream>


void runMenu(MenuUnit* menu, const char* title, void* ptr) {
	int cnt;
	while (true)
	{
		printf("\n\n    --- %s ---\n\n", title);
		cnt = 0;
		for (; ; cnt++)
		{
			printf("%d. %s\n", cnt + 1, menu[cnt].text);
			if (menu[cnt].func == NULL)
			{
				break;
			}
		}
		int choise = getInt("Choose option",1,cnt+1);
		if (menu[choise -1].func == NULL) {
			return;
		}
		int result = menu[choise - 1].func(ptr);
		if (result != 0) {
			return;
		}

	}
}

int queryOperationsMenu(void* ptr) {
	if (rootExists()) {
		MenuUnit menu[] = {
		{"Sum of tasks in all subjects", printAllHoursSubject},
		{"The oldest literature", printOldestLiterature},
		{"List of literature created after entered year",printLiteratureCreatedLaterEntered},
		{"List of subjects with number of tasks greater than entered", printSubjectsTasksGreaterEntered},
		{"Show size of tree", calculateTreeSize},
		{"Return to main menu",NULL},
		};
		runMenu(menu, "Query oprations menu", root);
	}
	
	return 0;
}

int treeOperationMenu(void* ptr) {
	MenuUnit menu[] = {
	{"Create root", createRootMenu},
	{"Create default tree",createDefaultTreeMenu },
	{"Show project information", showProjectInfo},
	{"Show tree", showWholeTree},
	{"Show logfile", showlogFile},
	{"SAVE tree to file", storeTreeToFileMenu},
	{"RESTORE tree from file", restoreTreeFromFileMenu},
	{"SHOW tree from file", showTreeFromFile},
	{"Return to main menu",NULL },
	};

	runMenu(menu, "Tree operations menu", root);
	
	return 0;
}

int departmenMenu(void* ptr) {
	if (rootExists()) {
		MenuUnit menu[] = {
		{"Edit Department information", editDepartmentMenu},
		{"Delete Department", deleteDepartmentMenu},
		{"Delete all subjects", deleteAllSubjectsMenu},
		{"Show Department information", showDepartmentInfo},
		{"Show list of subjects", showListOfSubjecs},
		{"Add subject", addSubjectMenu},
		{"Return to main menu", NULL},
		};

		runMenu(menu, "Department menu", root);
	}
	return 0;

}



int subjectMenu(void* ptr) {
	if (rootExists()) {
		if (root->subjectCount > 0) {
			int subject_id = selectSubject(root);
			if (subject_id == -1)
				return 0;
			MenuUnit menu[] = {
				{"Edit Subject information", editSubjectMenu},
				{"Delete subject",deleteSpecificSubjectMenu },
				{"Delete all literature", deleteLiteratureFromSubjectMenu},
				{"Show subject information", showInfoSpecificSubject},
				{"Show list of literature", showListOfLiterature},
				{"Add literature", addLiteratureMenu},
				{"Return to main menu", NULL},
			};
			runMenu(menu, "Subject menu", root->subjectArr[subject_id]);
		}
		else {
			puts("\nSubject list is empty!");
		}
	}
	
	return 0;
}

int literatureMenu(void* ptr) {
	if (rootExists()) {
		if (root->subjectCount > 0) {
			int subject_id = selectSubject(root);
			if (root->subjectArr[subject_id]->firstLiterature != NULL) {

				Literature* literature = selectLiterature(root->subjectArr[subject_id]);

				if (literature == NULL)
					return 0;
				MenuUnit menu[] = {
					{"Edit literature information", editLiteratureInfoMenu},
					{"Delete literature", deleteLiteratureMenu},
					{"Show literature information", showLiteratureInfo},
					{"Return to main menu", NULL},
				};

				runMenu(menu, "Literature menu", literature);
			}
			else {
				puts("\nNo literature connected to this subject!");
			}
		}
		else {
			puts("\nSubject list is empty!");
		}
	}
	
	return 0;
}

int mainMenu(void* ptr) {
	MenuUnit menu[] = {
		{"Department operation", departmenMenu},
		{"Subject operation", subjectMenu},
		{"Literture operation", literatureMenu},
		{"Tree operation", treeOperationMenu},
		{"Query operation", queryOperationsMenu},
		{"Exit from project", NULL},
	};

	runMenu(menu, "Main menu", ptr);

	return 0;
	
}