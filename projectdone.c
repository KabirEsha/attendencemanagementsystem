#include <stdio.h>
#include <string.h>

struct student
{
    int roll;
    char name[20];
    char course[5][20];
    int TotalNumberOfClasses[5];
    int AttendedNumberOfClasses[5];
    int AttendancePercent[5];
};

struct students {
    int rolls;
    char names[20];
};

void takeRollCall(struct students* students, int numStudents, char* date) {
    FILE* file = fopen("attendance_records.txt", "a");
    if (file == NULL) {
        printf("Unable to open the attendance records file.\n");
        return;
    }

    fprintf(file, "Date: %s\n", date);

    for (int i = 0; i < numStudents; i++) {
        printf("Is student with roll number %d present? (Y/N): ", students[i].rolls);
        char answer[2];
        scanf("%s", answer);

        if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0) {
            printf("%s is present\n", students[i].names);
            fprintf(file, "%d p\n", students[i].rolls);
        } else {
            printf("%s is absent\n", students[i].names);
            fprintf(file, "%d a\n", students[i].rolls);
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

void addStudent(struct student *s) {
    printf("Enter roll number: ");
    scanf(" %d", &(s->roll));
    printf("Enter name: ");
    scanf("%s", s->name);

    for(int i = 0; i < 5; i++) {
        printf("Enter course %d: ", i+1);
        scanf("%s", s->course[i]);
        printf("Enter total number of classes for course %d: ", i+1);
        scanf("%d", &(s->TotalNumberOfClasses[i]));
        printf("Enter attended number of classes for course %d: ", i+1);
        scanf("%d", &(s->AttendedNumberOfClasses[i]));
        s->AttendancePercent[i] = (s->AttendedNumberOfClasses[i] * 100) / s->TotalNumberOfClasses[i];
    }
}

void displayAttendance(struct student *s) {
    printf("Roll number: %d\n", s->roll);
    printf("Name: %s\n", s->name);

    for(int i = 0; i < 5; i++) {
        printf("Course %d: %s\n", i+1, s->course[i]);
        printf("Total number of classes for course %d: %d\n", i+1, s->TotalNumberOfClasses[i]);
        printf("Attended number of classes for course %d: %d\n", i+1, s->AttendedNumberOfClasses[i]);
        printf("Attendance percentage for course %d: %d%%\n", i+1, s->AttendancePercent[i]);
    }
}

void searchStudentByRoll(int rollNumber) {
    FILE *file = fopen("attendance.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    struct student s;
    int found = 0;

    while (fscanf(file, "%d %s", &(s.roll), s.name) != EOF) {
        if (s.roll == rollNumber) {
            for(int i = 0; i < 5; i++) {
                fscanf(file, "%s %d %d %d", s.course[i], &(s.TotalNumberOfClasses[i]), &(s.AttendedNumberOfClasses[i]), &(s.AttendancePercent[i]));
            }
            displayAttendance(&s);
            found = 1;
            break;
        } else {
            for(int i = 0; i < 5; i++) {
                fscanf(file, "%*s %*d %*d %*d");
            }
        }
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", rollNumber);
    }

    fclose(file);
}

void updateStudentByRoll(int rollNumber) {
    FILE *file = fopen("attendance.txt", "r+");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }

    struct student s;
    int found = 0;

    long int pos = ftell(file);
    while (fscanf(file, "%d %s", &(s.roll), s.name) != EOF) {
        if (s.roll == rollNumber) {
            found = 1;
            break;
        } else {
            for(int i = 0; i < 5; i++) {
                fscanf(file, "%*s %*d %*d %*d");
            }
            pos = ftell(file);
        }
    }

    if (found) {
        fseek(file, pos, SEEK_SET);

        printf("Enter roll number: ");
        scanf("%d", &(s.roll));
        printf("Enter name: ");
        scanf("%s", s.name);

    for(int i = 0; i < 5; i++) {
        printf("Enter course %d: ", i+1);
        scanf("%s", s.course[i]);
        printf("Enter total number of classes for course %d: ", i+1);
        scanf("%d", &(s.TotalNumberOfClasses[i]));
        printf("Enter attended number of classes for course %d: ", i+1);
        scanf("%d", &(s.AttendedNumberOfClasses[i]));
        s.AttendancePercent[i] = (s.AttendedNumberOfClasses[i] * 100) / s.TotalNumberOfClasses[i];
    }
        fprintf(file, "%d %s ", s.roll, s.name);
        for(int i = 0; i < 5; i++) {
            fprintf(file, "%s %d %d %d ", s.course[i], s.TotalNumberOfClasses[i], s.AttendedNumberOfClasses[i], s.AttendancePercent[i]);
        }
        fprintf(file, "\n");

        printf("Student with roll number %d updated successfully.\n", rollNumber);
    } else {
        printf("Student with roll number %d not found.\n", rollNumber);
    }

    fclose(file);
}

int main() {
    int choice;
    int rollNumber;

    int numStudents;


    struct students* students = malloc(numStudents * sizeof(struct students));

    char date[20];

    do {
        printf("\n***** Attendance Management System *****\n");
        printf("1. Add Student\n");
        printf("2. Search Student by Roll Number\n");
        printf("3. Update Student by Roll Number\n");
        printf("4. Take Roll Call\n");
        printf("5. Search Attendance by Date\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                struct student s;
                addStudent(&s);

                FILE *file = fopen("attendance.txt", "a");
                if(file == NULL) {
                    printf("Unable to open the file.\n");
                    return 1;
                }
                fprintf(file, "%d %s ", s.roll, s.name);
                for(int i = 0; i < 5; i++) {
                    fprintf(file, "%s %d %d %d ", s.course[i], s.TotalNumberOfClasses[i], s.AttendedNumberOfClasses[i], s.AttendancePercent[i]);
                }
                fprintf(file, "\n");
                fclose(file);

                printf("Student added successfully.\n");
                break;
            }
            case 2: {
                printf("Enter roll number: ");
                scanf("%d", &rollNumber);
                searchStudentByRoll(rollNumber);
                break;
            }
            case 3: {
                printf("Enter roll number: ");
                scanf("%d", &rollNumber);
                updateStudentByRoll(rollNumber);
                break;
            }
            case 4: {
                printf("\nEnter the date (format: DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Roll call in progress...\n");
                    printf("Enter the number of students: ");
    scanf("%d", &numStudents);
        for (int i = 0; i < numStudents; i++) {
        printf("Enter roll number for student %d: ", i + 1);
        scanf("%d", &students[i].rolls);
        printf("Enter name for student %d: ", i + 1);
        scanf("%s", students[i].names);
    }
                takeRollCall(students, numStudents, date);
                break;
            }
            case 5: {
                printf("\nEnter the date (format: DD-MM-YYYY): ");
                scanf("%s", date);
                printf("Search attendance by date...\n");
                searchAttendanceByDate(date);
                break;
            }
            case 6: {
                printf("Exiting the program.\n");
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    } while(choice != 6);

    return 0;
}