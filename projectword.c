#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[20];
};

void takeRollCall(struct student* students, int numStudents, char* date) {
    FILE* file = fopen("attendance_records.txt", "a");
    if (file == NULL) {
        printf("Unable to open the attendance records file.\n");
        return;
    }

    fprintf(file, "Date: %s\n", date);

    for (int i = 0; i < numStudents; i++) {
        printf("Is student with roll number %d present? (Y/N): ", students[i].roll);
        char answer[2];
        scanf("%s", answer);

        if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0) {
            printf("%s is present\n", students[i].name);
            fprintf(file, "%d p\n", students[i].roll);
        } else {
            printf("%s is absent\n", students[i].name);
            fprintf(file, "%d a\n", students[i].roll);
        }
    }

    fclose(file);
}

void searchAttendanceByDate(char* date) {
    FILE* file = fopen("attendance_records.txt", "r");
    if (file == NULL) {
        printf("Unable to open the attendance records file.\n");
        return;
    }

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, date) != NULL) {
            printf("%s", line); // Print the date line
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Attendance records for the date: %s\n", date);
        while (fgets(line, sizeof(line), file)) {
            if (line[0] != '\n') {
                int roll;
                char status;
                sscanf(line, "%d %c", &roll, &status);
                printf("Roll Number: %d | Status: %c\n", roll, status);
            }
        }
    } else {
        printf("No attendance records found for the date: %s\n", date);
    }

    fclose(file);
}

void displayMenu() {
    printf("\n***** Roll Call System *****\n");
    printf("1. Take Roll Call\n");
    printf("2. Search Attendance by Date\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int numStudents;
;

    struct student* students = malloc(numStudents * sizeof(struct student));



    int choice;
    char date[20];

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the date (format: DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Roll call in progress...\n");
                    printf("Enter the number of students: ");
    scanf("%d", &numStudents);
        for (int i = 0; i < numStudents; i++) {
        printf("Enter roll number for student %d: ", i + 1);
        scanf("%d", &students[i].roll);
        printf("Enter name for student %d: ", i + 1);
        scanf("%s", students[i].name);
    }
                takeRollCall(students, numStudents, date);
                break;
            case 2:
                printf("\nEnter the date (format: DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Search attendance by date...\n");
                searchAttendanceByDate(date);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    free(students);

    return 0;
}