#include "prototype.h"

int printAllHoursSubject(void* ptr) {
	Department* dept = (Department*)(ptr);
	puts("\n    --- Sum of tasks in all subjects --");
	int sum = 0;
	for (int i = 0; i < dept->subjectCount; i++)
	{
		sum += dept->subjectArr[i]->num_of_tasks;
	}
	printf("\nNumber of tasks in all subjects - %d", sum);
	fprintf_s(logfile, "\nCalled query operation: \"Sum of tasks in all subjects\"");
	return 0;
}

int printOldestLiterature(void* ptr) {
	Department* dept = (Department*)(ptr);
	puts("\n    --- The oldest literature ---");
	Literature* temp, *oldest_literature = dept->subjectArr[0]->firstLiterature;
	for (size_t i = 0; i < dept->subjectCount; i++)
	{
		temp = dept->subjectArr[i]->firstLiterature;
		while (temp != NULL) {
			if (oldest_literature == NULL || temp->creation_year < oldest_literature->creation_year)
				oldest_literature = temp;
			temp = temp->nextLiterature;
		}
	}
	printf("\nThe oldest literature: \n %s,\n author - %s,\n language - %s,\n creation year - %d", oldest_literature->name, oldest_literature->author, oldest_literature->creation_language, oldest_literature->creation_year);
	fprintf_s(logfile, "\nCalled query operation: \"The oldest literature\"");
	return 0;
}

int printLiteratureCreatedLaterEntered(void* ptr) {
	Department* dept = (Department*)(ptr);
	puts("\n    --- List of literature created later entered year ---");
	int choise = getInt("Enter literature creation year: ");
	Literature* temp;
	int items_count = 0;
	for (size_t i = 0; i < dept->subjectCount; i++)
	{
		temp = dept->subjectArr[i]->firstLiterature;
		while (temp != NULL) {
			if (temp->creation_year > choise) {
				printf("\n %d. %s, author - %s, language - %s, creation year - %d",items_count+1, temp->name, temp->author, temp->creation_language, temp->creation_year);
				items_count++;
			}
			temp = temp->nextLiterature;
		}
	}
	if (items_count == 0)
		printf("\n\nNo literature meets the requirement \"Created after %d\"\n", choise);
	fprintf_s(logfile, "\nCalled query operation: \"List of literature created after entered year\"");
	return 0;
}

int printSubjectsTasksGreaterEntered(void* ptr) {
	Department* dept = (Department*)(ptr);
	puts("\n    --- List of subjects with number of tasks greater than entered ---");
	int choise = getInt("Enter subject's number of tasks: ");
	int items_count = 0;
	for (size_t i = 0; i < dept->subjectCount; i++)
	{
		if (dept->subjectArr[i]->num_of_tasks > choise) {
			printf("\n %d. %s, lecturer - %s, number of tasks - %d", items_count + 1, dept->subjectArr[i]->name, dept->subjectArr[i]->lecturer, dept->subjectArr[i]->num_of_tasks);
			items_count++;
		}
	}
	if (items_count == 0)
		printf("\n\nNo subject meets the requirement \"Number of tasks greater than %d\"\n", choise);
	fprintf_s(logfile, "\nCalled query operation: \"List of subjects with number of tasks greater than entered\"");
	return 0;
}