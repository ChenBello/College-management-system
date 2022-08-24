//Coded by Chen Bello

#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct student
{
	char grade[4];
	char name[21];
	struct student* next;
}student;

typedef struct Course
{
	int numofstudents;
	//double average, min, max, overall;
	char Cnum[6];
	char Cname[31];
	struct Course* next;
	student* Stud;


}course;
typedef struct Courses
{
	//double average, min, max, overall;
	int amountOfCourses;
	course* course_head;
}courses;

typedef struct Student_data
{
	char studName[21];
	int amountOfCourses;
	struct Student_data* nextS;
}S_data;


typedef struct Students
{
	int amountOfStudents;
	S_data* student_head;
}students;


typedef struct hit//אפשר לוותר כי לא כל כך נעשה בו שימוש, אבל בכל זאת: מחזיק את הכתובות של 2 הרשימות המקושרות
{
	courses* courses;
	students* students;

}hit;



/* Function declarations */

/*for Ex1*/
void freeCoursesL(course** head);
void freeStudentsL(S_data** head);


/*for Ex2*/
int checkLineEx2(char* line);
void InsertCourse(course** courseHead, course* newCourse);
course* createCourse(char* _name, char* _courseNum);//לכל קורס יש מספר קורס ושם קורס
int ExistingCourseNum(course* head, course** theOne, char* courseNum);



/*for Ex3*/
int checkLineEx3(char* line, int* repeats);
char* newLineEx3(char* line, int size);
student* createStud(char* studentName, char* courseNum, char* grade);
int insertS_data(S_data** S, S_data* newStudent);
S_data* createS_data(char* studentName);


/*for Ex4*/
int checkLineEx4(char* line, int* repeats);//מסדר גם את השורה לשורה ללא רווחים במידה ותקינה
char* newLineEx4(char* line, int size);
void DeleteStudent(course** head, char* studentName, char* courseNum);
void notDeleteStudent(course* head, char* studentName, char* courseNum);
int checkIfBelongsToAllClassesEx4(courses C, students S, /*course** Course, */char* line, int repeats/*, char** strStudentName*/);//mainלקרוא מה //////////////////



/*for Ex5*/
void printStudentsinCurrC(course* C);
void printS_data(students S);
int checkLineEx5(char* line);//מסדר גם את השורה לשורה ללא רווחים במידה ותקינה



/*for Ex6*/
double averageGrade(course* C);
int maximalGrade(course* C);
int minimalGrade(course* C);
int sum(course* C);



/*פונקציות עזר נוספות*/
char* makeStudNameStr(char* newL, int* startPoint);
char* makeCourseNumStr(char* newL, int* startPoint);
int findCurrCourse(courses C, course** currC, char* courseNum);
int findCurrStudent(course* C, student** currS, char* studentName);
void Strcpy(char* s1, char* s2);
int ExistingStudentInCourse(courses C, student** theOne, char* courseNum, char* studentName);
void printCoursesAndStudents(courses C);
int findCurrS_data(students S, S_data** currS, char* studentName);
void freeStaticLineAndGrade(char* line, char* grade);






