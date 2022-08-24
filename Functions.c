//Coded by Chen Bello

#include "Header.h"


/* Function definitions */
void freeCoursesL(course ** head)
{
	course* currC = NULL, * freeC = NULL;
	student* currS = NULL, * freeS = NULL;
	if (*head)
	{
		currC = *head;
		while (currC)
		{
			if (currC->Stud)
			{
				currS = currC->Stud;
				while (currS)
				{
					freeS = currS;
					currS = currS->next;
					free(freeS);
					freeS = NULL;
				}
			}
			freeC = currC;
			currC = currC->next;
			free(freeC);
			freeC = NULL;
		}

	}
}
void freeStudentsL(S_data** head)
{
	S_data* currS = NULL, * freeS = NULL;
	if (*head)
	{
		while (currS)
		{
			freeS = currS;
			currS = currS->nextS;
			free(freeS);
			freeS = NULL;
		}
	}
}


int sum(course* C)
{
	int  i = 0, result = 0;
	student* S = NULL;
	if (C->Stud)
	{
		S = C->Stud;
		while (S)
		{

			if (strlen(S->grade) == 3) result += 100;
			else
			{
				for (i = 0; i < strlen(S->grade); i++)
				{
					if (strlen(S->grade) == 2 && i == 0)result += (S->grade[i] - '0') * 10;
					else result += (S->grade[i] - '0');

				}
			}
			S = S->next;
		}
	}
	else result = 0;
	return result;
}

double averageGrade(course* C)
{
	int  i = 0;
	double result = 0;
	student* S = NULL;
	if (C->Stud)
	{
		S = C->Stud;
		while (S)
		{
			if (strlen(S->grade) == 3) result += 100;
			else
			{
				for (i = 0; i < strlen(S->grade); i++)
				{
					if (strlen(S->grade) == 2 && i == 0)result += (S->grade[i] - '0') * 10;
					else result += (S->grade[i] - '0');

				}
			}
			S = S->next;
		}
	}
	else result = 0;
	return result / C->numofstudents;
}

int maximalGrade(course* C)
{
	int  i = 0, cmpr = 0, max = 0;
	student* S = NULL;
	if (C->Stud)
	{
		S = C->Stud;
		while (S)
		{
			if (strlen(S->grade) == 3) cmpr = 100;
			else
			{
				for (i = 0; i < strlen(S->grade); i++)
				{
					if (strlen(S->grade) == 2 && i == 0)cmpr += (S->grade[i] - '0') * 10;
					else cmpr += (S->grade[i] - '0');


				}
			}
			max = (max < cmpr ? cmpr : max);
			if (max == 100) break;
			S = S->next;
		}
	}
	else max = 0;
	return max;
}


int minimalGrade(course* C)
{
	int i = 0, cmpr = 0, min = 100;
	student* S = NULL;
	if (C->Stud)
	{

		S = C->Stud;
		while (S)
		{
			if (strlen(S->grade) == 3) cmpr = 100;
			else
			{
				for (i = 0; i < strlen(S->grade); i++)
				{
					if (strlen(S->grade) == 2 && i == 0)cmpr += (S->grade[i] - '0') * 10;
					else cmpr += (S->grade[i] - '0');


				}
			}
			min = (min > cmpr ? cmpr : min);
			if (min == 0) break;
			S = S->next;
		}
	}
	else min = 0;
	return min;
}


int insertS_data(S_data** S, S_data* newStudent)//?
{
	int flag = 1;
	S_data* freePlace = NULL;
	
		if (!*S)
		{
			*S = newStudent;
			
		}
		else if (*S && !(*S)->nextS)
		{
			if (strcmp((*S)->studName, newStudent) != 0)(*S)->nextS = newStudent;
			else
			{
				//(*S)->amountOfCourses++;
				flag = 0;
			}
		}
		else
		{
			freePlace = *S;
			if (freePlace)
			{
				while (freePlace && strcmp(freePlace->studName, newStudent) != 0)
				{
					freePlace = freePlace->nextS;
				}
				if (freePlace && strcmp(freePlace->studName, newStudent) == 0)
				{
					freePlace->amountOfCourses++;
					flag = 0;
				}
				else if (!freePlace && flag)
				{
					freePlace = *S;
					while (freePlace->nextS)
					{
						freePlace = freePlace->nextS;
					}
					if (!freePlace->nextS)
					{
						freePlace->nextS = newStudent;
					}
				}
			}
		}
		return flag;
	
}
S_data* createS_data(char* studentName)
{
	S_data* newS_data = NULL;
	newS_data = (S_data*)calloc(1, sizeof(S_data));
	if (newS_data && studentName)
	{
		Strcpy(newS_data->studName, studentName);
		newS_data->nextS = NULL;
		newS_data->amountOfCourses = 1;
	}
	return newS_data;
}

void freeStaticLineAndGrade(char* line, char *grade)
{
	int i = 0;

	while ( line[i] != '\0')
	{
		line[i] = '\n';
		i++;
	}
	if (line[i] == '\0') line[i] = '\n';
	
	i = 0;

	while (grade[i] == '\0')
	{
		
		grade[i] = '\n';
		i++;
	}
	if (line[i] == '\0') grade[i] = '\n';

}


int ExistingCourseNum(course* head, course** theOne, char* courseNum)
{
	int flag = 1;
	course* check = NULL;
	if (!head) return 0;
	else if (head && !(head)->next)
	{
		if (strcmp((head)->Cnum, courseNum) == 0)
		{
			*theOne = head;

		}
		else flag = 0;
	}
	else
	{
		check = head;
		while (check && strcmp(check->Cnum, courseNum) != 0)
		{
			check = check->next;
		}
		if (check && strcmp(check->Cnum, courseNum) == 0)
		{
			*theOne = check;
		}
		else if (!check) flag = 0;
	}
	return flag;

}

int ExistingStudentInCourse(courses C, student** theOne, char* courseNum, char* studentName)
{
	//flag = 0 if Student needs to be inserted && flag = 1 if the grade of Student in curr course needs to be changed (in main) 
	int flag = 1;
	course* currC = NULL;
	student* currS = NULL;
	if (C.course_head)
	{
		if (!C.course_head->next)
		{
			if (strcmp(C.course_head->Cnum, courseNum) == 0)
			{
				if (!C.course_head->Stud)
				{
					*theOne = C.course_head->Stud;
					flag = 0;
					//printf("Student needs to be inserted\n");//לשנות


				}
				else if (strcmp(C.course_head->Stud->name, studentName) == 0)
				{

					*theOne = C.course_head->Stud;


				}
				else
				{
					currS = C.course_head->Stud;
					while (currS && strcmp(currS->name, studentName) != 0)
					{
						currS = currS->next;
					}
					if (currS && strcmp(currS->name, studentName) == 0)
					{
						*theOne = currS;
					}
					else if (!currS)
					{
						//printf("Student wasn't found\n");//לשנות
						flag = 0;
					}
				}
			}
		}
		else
		{
			currC = C.course_head;
			if (currC)
			{
				while (currC && strcmp(currC->Cnum, courseNum) != 0)
				{
					currC = currC->next;
				}

				if (currC && strcmp(currC->Cnum, courseNum) == 0)
				{
					if (!currC->Stud)
					{
						*theOne = currC->Stud;
						flag = 0;
					}
					else
					{
						currS = currC->Stud;
						while (currS && strcmp(currS->name, studentName) != 0)
						{
							currS = currS->next;
						}
						if (currS && strcmp(currS->name, studentName) == 0)
						{
							*theOne = currS;
						}
						else if (!currS)
						{
							//printf("Student wasn't found\n");
							flag = 0;
						}
					}
				}
				else if (!currC)flag = 0;//printf("course %c%s%c doesn't exist\n", 34, courseNum, 34);//לשנות

			}

		}
	}
	else
	{
		flag = 0;
	//	printf("course list is empty.\n");//לשנות
	}
	return flag;

}
/* ------------------- */
void Strcpy(char* s1, char* s2)
{
	int x, len;
	len = strlen(s2);
	for (x = 0; x <= len; x++)
		s1[x] = s2[x];
}

int findCurrS_data(students S, S_data** currS, char* studentName)
{
	int flag = 1;
	S_data* currS_data = NULL;
	if (S.student_head)
	{
		currS_data = S.student_head;
		while (currS_data && strcmp(currS_data->studName, studentName) != 0)
		{
			currS_data = currS_data->nextS;
		}
		if (currS_data && strcmp(currS_data->studName, studentName) == 0)
		{
			*currS = currS_data;
		}
		else if (!currS_data)
		{
			//printf("Student wasn't found\n");
			flag = 0;
		}
	}
	else flag = 0;
	return flag;

}
student* createStud(char* studentName, char* courseNum, char* grade)
{
	student* newStud = NULL;
	newStud = (student*)calloc(1, sizeof(student));
	if (newStud)
	{
		Strcpy(newStud->name, studentName);
		Strcpy(newStud->grade, grade);
		newStud->next = NULL;

	}
	return newStud;
	
}

void printS_data(students S)
{
	S_data* currS = NULL;
	int i = 1;
	printf("Total amount of students: %d\n", S.amountOfStudents);
	if (S.student_head)
	{
		currS = S.student_head;
		while (currS)
		{
			printf("%d) %s, Amount of courses this student has: %d.\n", i,currS->studName, currS->amountOfCourses);
			i++;
			currS = currS->nextS;
		}
		printf("\n");

	}
	else printf("There are no students yet.\n");
}

int findCurrCourse(courses C, course** currC, char* courseNum)
{

	int flag = 1;

	if (C.course_head)
	{
		if (strcmp(C.course_head->Cnum, courseNum) == 0)
		{
			//printf("This Course is the first in list.\n"); 
			*currC = C.course_head;
			flag = 2;
		}
		else
		{
			*currC = C.course_head;
			while (*currC && strcmp((*currC)->Cname, courseNum) != 0)
			{
				*currC = (*currC)->next;
			}
			if (*currC && strcmp((*currC)->Cname, courseNum) == 0)
			{
				//*currC = currC;
			}
			else if (!*currC)
			{
				flag = 0;

				printf("Course wasn't found\n");
			}

		}
	}
	else
	{
		//printf("Courses list is empty.\n");
		flag = 0;
	}
	return flag;
}



int findCurrStudent(course* C, student** currS, char* studentName)
{
	student* findS = NULL;
	int flag = 1;
	if (C->Stud)
	{
		if (strcmp(C->Stud->name, studentName) == 0)
		{
			*currS = C->Stud;
			flag = 2;
		
		}

		else
		{
			findS = C->Stud;
			while (findS && strcmp(findS->name, studentName) != 0)
			{
				findS = findS->next;
			}
			if (findS && strcmp(findS->name, studentName) == 0)
			{
				*currS = findS;
			}
			else if (!findS)
			{
				//printf("Student wasn't found\n");
				flag = 0;
			}
		}
	}
	else flag = 0;//printf("The list of students is empty!\n");

	return flag;

}

int checkIfBelongsToAllClassesEx4(courses C, students S, /*course** Course, */char* line, int repeats)//mainלקרוא מה //////////////////
{
	S_data* currS_data = NULL;
	student* currS = NULL;
	course* currC = NULL;

	int flag = 1, counter = 0, startPoint = 0;
	char* courseNum = NULL, * StudentName = NULL;
	StudentName = makeStudNameStr(line, &startPoint);
	if (StudentName && findCurrS_data(S, &currS_data, StudentName) && currS_data)
	{
		while (line[startPoint] != '\0')
		{
			currS = NULL, currC = NULL;
			courseNum = makeCourseNumStr(line, &startPoint);
			if (courseNum)
			{
				if ((!ExistingCourseNum(C.course_head, &currC, courseNum) && !currC))
				{
					flag = 0;
					break;
				}
				free(courseNum);
				courseNum = NULL;
			}
		}

		free(StudentName);
		StudentName = NULL;
	}
	else
	{
		flag = 0;
	}
	return flag;
}

char* newLineEx5(char* line, int lineCounter)
{
	int i = 0, startPoint = 0;
	char* newL = NULL;
	while (line[startPoint] == 32)
	{
		startPoint++;
	}
	while (line[startPoint] != '\0')
	{
		if (line[startPoint] >= '0' && line[startPoint] <= '9')
		{
			i++;
		}
		startPoint++;
	}
	newL = (char*)calloc(i + 1, sizeof(char));
	if (newL)
	{
		startPoint = i = 0;
		while (line[startPoint] == 32)
		{
			startPoint++;
		}
		while (line[startPoint] != '\0')
		{
			if (line[startPoint] >= '0' && line[startPoint] <= '9')
			{
				newL[i] = line[startPoint];
				i++;
			}
			startPoint++;
		}
		newL[i] = '\0';
	}
	return newL;

}

int checkLineEx5(char* line)//מסדר גם את השורה לשורה ללא רווחים במידה ותקינה
{
	int startPoint = 0, lineCounter = 0, flag = 1, courseNumCounter = 0;
	char* newL = NULL;
	if (line)
	{
		startPoint = 0;
		while (line[startPoint] == 32)
		{
			startPoint++;
		}
		while (line[startPoint] != '\0')
		{
			if (line[startPoint] >= '0' && line[startPoint] <= '9')
			{
				courseNumCounter++;
				lineCounter++;
				startPoint++;
			}
			else
			{
				flag = 0;
				break;
			}
		}
		if (line[startPoint] == '\0')
		{
			if (courseNumCounter != 5) flag = 0;
		}
		if (flag)
		{
			newL = newLineEx5(line, lineCounter);
			if (newL)
			{
				Strcpy(line, newL);
				free(newL);
				newL = NULL;
			}

		}

	}
	return flag;
}

int checkLineEx4(char* line, int* repeats)//בודק האם עומד בתנאים מבחינת המבנה, מסדר גם את השורה לשורה ללא רווחים במידה ותקינה
{
	int startPoint = 0, lineCounter = 0, flag = 1, courseNumCounter = 0, studentNameCounter = 0;
	char* newL = NULL;
	if (line)
	{
		startPoint = 0;
		while (line[startPoint] == 32)
		{
			startPoint++;
		}
		while (line[startPoint] != ':')
		{
			if ((line[startPoint] >= 'a' && line[startPoint] <= 'z') || (line[startPoint] >= 'A' && line[startPoint] <= 'Z') || line[startPoint] == ' ')
			{
				studentNameCounter++;
				lineCounter++;
				startPoint++;
			}
			else
			{
				flag = 0;
				break;
			}
		}

		if (flag && line[startPoint] == ':' && (studentNameCounter >= 1 && studentNameCounter <= 20))
		{
			lineCounter++;
			startPoint++;
		}
		else flag = 0;
		if (flag)
		{
			do
			{
				courseNumCounter = 0;

				while (line[startPoint] == 32)
				{
					startPoint++;
				}
				while (line[startPoint] != ',')
				{
					if (line[startPoint] >= '0' && line[startPoint] <= '9')
					{
						courseNumCounter++;
						lineCounter++;

					}
					else
					{
						flag = 0;
						break;
					}
					startPoint++;
				}
				if (line[startPoint] == ',')
				{
					lineCounter++;
					startPoint++;//לעבור אחרי הפסיק
				}
				if (courseNumCounter != 5) flag = 0;
				else if (courseNumCounter == 5 && flag) (*repeats)++;
			} while (flag && line[startPoint] != '\0');


			if (flag)
			{
				newL = newLineEx4(line, lineCounter);
				if (newL)
				{
					Strcpy(line, newL);
					free(newL);
					newL = NULL;
				}
			}
		}

	}
	else flag = 0;
	return flag;
}

char* newLineEx4(char* line, int size)
{
	int startPoint = 0, i = 0, start = 0;
	char* newL = (char*)calloc(size + 1, sizeof(char));

	if (newL)
	{
		startPoint = 0;
		while (line[startPoint] != ':')
		{
			if ((line[startPoint] >= 'a' && line[startPoint] <= 'z') || (line[startPoint] >= 'A' && line[startPoint] <= 'Z') || line[startPoint] == ' ')
			{
				newL[i] = line[startPoint];
				i++;
			}
			startPoint++;
		}
		if (line[startPoint] == ':')
		{
			newL[i] = line[startPoint];
			i++;
			startPoint++;//לעבור אחרי הנקודותיים
		}
		do
		{
			while (line[startPoint] == 32)
			{
				startPoint++;
			}
			while (line[startPoint] != ',')
			{
				if (line[startPoint] >= '0' && line[startPoint] <= '9')
				{
					newL[i] = line[startPoint];
					i++;
				}
				else break;

				startPoint++;
			}
			if (line[startPoint] == ',')
			{
				newL[i] = line[startPoint];
				i++;
				startPoint++;//לעבור אחרי הפסיק
			}

		} while (line[startPoint] != '\0');

		if (line[startPoint] != '/0')newL[i] = '\0';
	}
	return newL;

}
char* newLineEx3(char* line, int size)//לבדוק אם תקין
{
	int startPoint = 0, i = 0, start = 0;
	char* newL = (char*)calloc(size + 1, sizeof(char));

	if (newL)
	{
		startPoint = 0;


		while (line[startPoint] == 32)
		{
			startPoint++;
		}
		while (line[startPoint] != ':')
		{
			if ((line[startPoint] >= 'a' && line[startPoint] <= 'z') || (line[startPoint] >= 'A' && line[startPoint] <= 'Z') || line[startPoint] == ' ')
			{
				newL[i] = line[startPoint];
				i++;
			}
			startPoint++;
		}
		if (line[startPoint] == ':')
		{
			newL[i] = line[startPoint];
			i++;
			startPoint++;//לעבור אחרי הנקודותיים
		}
		do
		{
			while (line[startPoint] == 32)
			{
				startPoint++;
			}
			while (line[startPoint] != ',')
			{
				if (line[startPoint] >= '0' && line[startPoint] <= '9')
				{
					newL[i] = line[startPoint];
					i++;

				}
				else break;

				startPoint++;
			}
			if (line[startPoint] == ',')
			{
				newL[i] = line[startPoint];
				i++;
				startPoint++;//לעבור אחרי הפסיק
			}

			while (line[startPoint] == 32)
			{
				startPoint++;
			}



			while (line[startPoint] != ';')
			{
				if (line[startPoint] >= '0' && line[startPoint] <= '9')
				{
					newL[i] = line[startPoint];
					i++;

				}
				else break;

				startPoint++;
			}
			while (line[startPoint] == 32)//אם יש רווחים לפני הנקודה פסיק אז שידלג עליהם לבדיקה הבאה
			{
				startPoint++;
			}

			if (line[startPoint] == ';')
			{
				newL[i] = line[startPoint];
				i++;
				startPoint++;//לעבור אחרי הנקודה פסיק

				while (line[startPoint] == 32)//אם יש רווחים אחרי הנקודה פסיק אז שידלג עליהם לבדיקה הבאה
				{
					startPoint++;
				}

			}
			start++;
		} while (line[startPoint] != '\0');

		if (line[startPoint] != '/0')newL[i] = '\0';

	}
	return newL;
}


int checkLineEx3(char* line, int* repeats)
{
	char* newL = NULL;
	int i = 0, startPoint = 0, courseNumCounter = 0, studentNameCounter = 0, courseGradeCounter = 0, lineCounter = 0, Flag = 1, start = 0;
	if (!line) Flag = 0;
	else
	{
		if (!start && Flag)
		{
			while (line[startPoint] == 32)
			{
				startPoint++;
			}
			while (line[startPoint] != ':')
			{
				if ((line[startPoint] >= 'a' && line[startPoint] <= 'z') || (line[startPoint] >= 'A' && line[startPoint] <= 'Z') || line[startPoint] == ' ')
				{
					studentNameCounter++;
					lineCounter++;
				}
				else
				{
					Flag = 0;
					break;
				}

				startPoint++;
			}
			if (Flag && line[startPoint] == ':' && studentNameCounter >= 1 && studentNameCounter <= 20)
			{
				start = 1;
				//Flag = 1;
				startPoint++;//לעבור אחרי הנקודותיים
				lineCounter++;
			}
			else Flag = 0;
			
		}

		if (start && Flag)
		{

			do
			{
				courseNumCounter = courseGradeCounter = 0;

				while (line[startPoint] == 32)
				{
					startPoint++;
				}
				while (line[startPoint] != ',')
				{
					if (line[startPoint] >= '0' && line[startPoint] <= '9')
					{
						courseNumCounter++;
						lineCounter++;

					}
					else 
					{
						Flag = 0;
						break;
					}
					startPoint++;
				}
				if (line[startPoint] == ',')
				{
					//Flag = 1;//
					startPoint++;// לעבור אחרי הפסיק או הנקודה
					lineCounter++;

				}
				else Flag = 0;

				if (Flag)
				{
					while (line[startPoint] == 32)
					{
						startPoint++;
					}
					if (((line[startPoint] > '0' && line[startPoint] <= '9') && (line[startPoint + 1] >= '0' && line[startPoint + 1] <= '9') && line[startPoint + 2] == ';') || (line[startPoint] == '1' && line[startPoint + 1] == '0' && line[startPoint + 2] == '0' && line[startPoint + 3] == ';') || (line[startPoint] == '0' && line[startPoint + 1] == ';')//break; // אם הציון מתחיל ב0 או בתו שאינו ספרה
						|| ((line[startPoint] > '0' && line[startPoint] <= '9') && (line[startPoint + 1] >= '0' && line[startPoint + 1] <= '9') && line[startPoint + 2] == ';') || ((line[startPoint] >= '0' && line[startPoint] <= '9') && line[startPoint + 1] == ';'));
					else Flag = 0;
					if (Flag)
					{
						while (line[startPoint] != ';')
						{
							if (line[startPoint] >= '0' && line[startPoint] <= '9') 
							{
								courseGradeCounter++;
								lineCounter++;

							}
							else 
							{
								Flag = 0;
								break;
							}
							startPoint++;
						}
						if (line[startPoint] == ';')
						{
							(*repeats)++;
							startPoint++;//לעבור אחרי הנקודה פסיק
							lineCounter++;
							while (line[startPoint] == 32)
							{
								startPoint++;
							}
						}
						else Flag = 0;
					}
					if (courseNumCounter != 5 || (courseGradeCounter < 1 || courseGradeCounter > 3))Flag = 0;//break;
				}


			} while (Flag && line[startPoint] != '\0');

		}
	}
	if (Flag && start)//המשך, הקצאות וכו
	{

		newL = newLineEx3(line, lineCounter);
		if (newL)
		{
			
			i = 0;
			startPoint = 0;

			while (newL[i] != '\0')
			{
				line[i] = newL[i];
				i++;
			}
			line[i] = '\0';
			
			free(newL);
			newL = NULL;

		}
	}

	return Flag;

}

char* makeStudNameStr(char* newL, int* startPoint)
{
	char* StudName = NULL;
	int size = 0, startFill = *startPoint;
	while (newL[*startPoint] != ':')
	{
		if ((newL[*startPoint] >= 'a' && newL[*startPoint] <= 'z') || (newL[*startPoint] >= 'A' && newL[*startPoint] <= 'Z') || newL[*startPoint] == ' ')//אפשר להוריד
		{
			size++;
		}
		(*startPoint)++;
	}
	(*startPoint)++;
	StudName = (char*)calloc(size + 1, sizeof(char));

	if (StudName)
	{
		size = 0;
		while (startFill <= *startPoint)
		{
			if ((newL[startFill] >= 'a' && newL[startFill] <= 'z') || (newL[startFill] >= 'A' && newL[startFill] <= 'Z') || newL[startFill] == ' ')//אפשר להוריד
			{
				StudName[size] = newL[startFill];
				size++;
			}
			startFill++;
		}
		StudName[size] = '\0';
	}

	return StudName;
}
char* makeCourseNumStr(char* newL, int* startPoint)
{
	char* courseNum = NULL;

	int size = 5 + 1;// חמש זה מספר הספרות שבמספר הקורס פלוס הפסיק שבסופו
	courseNum = (char*)calloc(size + 1, sizeof(char));

	if (courseNum)
	{
		size = 0;
		while (newL[*startPoint] != ',')
		{
			if (newL[*startPoint] >= '0' && newL[*startPoint] <= '9')//אפשר להוריד
			{
				courseNum[size] = newL[*startPoint];
				size++;
			}
			(*startPoint)++;
		}
		if (newL[*startPoint] == ',')
		{
			courseNum[size] = '\0';
			(*startPoint)++;
		}
	}

	return courseNum;
}


course* createCourse(char* _name, char* _courseNum)//לכל קורס יש מספר קורס ושם קורס
{
	course* C = NULL;
	int i = 0;
	if (_name && _courseNum)
	{
		C = (course*)calloc(1, sizeof(course));
		if (C != NULL)
		{
			Strcpy(C->Cname, _name);
			Strcpy(C->Cnum, _courseNum);
			C->next = NULL;
			C->Stud = NULL;
			C->numofstudents = 0;
		}
		//else printf("Unfortunately, there is no room for more classes.\n"); // mainמופיע ב
	}
	else printf("Invalid input for Course name or num\n");//לשנות

	return C;
}

void InsertCourse(course** courseHead, course* newCourse)
{
	course* findLast = NULL;
	if (!*courseHead)
	{
		*courseHead = newCourse;//createCourse(newCourse->Cname, newCourse->Cnum);//לכל קורס יש מספר קורס ושם קורס
		(*courseHead)->next = NULL;
		(*courseHead)->Stud = NULL;

	}
	else
	{
		findLast = *courseHead;
		while (findLast->next)
		{
			findLast = findLast->next;
		}
		if (findLast && !findLast->next)
		{
			findLast->next = newCourse;
			findLast = findLast->next;
			findLast->next = NULL;
			findLast->Stud = NULL;
		}
	}
}

int checkLineEx2(char* line)
{
	char* courseNum = NULL, * courseName = NULL, * cleanL = NULL;
	int startPoint = 0, c = 0, courseNumCounter = 0, lineCounter = 0, courseNameCounter = 0, Flag = 0, i = 0;
	if (line)
	{
		while (line[startPoint] == 32)
		{
			startPoint++;
		}
		while (line[startPoint] != '\0')
		{
			if (line[startPoint] == 44)//בדיקה ראשונה, האם קיים פסיק
			{
				lineCounter++;
				Flag = 1;
			}
			else
			{
				if (!Flag)
				{
					if (line[startPoint] != 32)
					{
						if (line[startPoint] >= 48 && line[startPoint] <= 57)
						{
							lineCounter++;
							courseNumCounter++;
						}
						else
						{
							Flag = 0;
							break;
						}

					}
					else
					{
						lineCounter++;//חשוב, אחרת יש מצב שלא יעתיק את כל שם הקורס למחרוזת המיועדת
					}

				}
				if (Flag == 1 && line[startPoint] != 32)//הגיע לפסיק, מתחיל מיד אחריו
				{
					if ((line[startPoint] >= 97 && line[startPoint] <= 122) || (line[startPoint] >= 65 && line[startPoint] <= 90) || (line[startPoint] >= 48 && line[startPoint] <= 57))
					{
						Flag = 2;
						lineCounter++;
						courseNameCounter++;
						startPoint++;
					}
					else
					{
						Flag = 0;
						break;
					}

				}
				if (Flag == 2)
				{

					if ((line[startPoint] >= 97 && line[startPoint] <= 122) || (line[startPoint] >= 65 && line[startPoint] <= 90) || (line[startPoint] >= 48 && line[startPoint] <= 57) || line[startPoint] == 32)
					{
						lineCounter++;
						courseNameCounter++;

					}
					else
					{
						if (line[startPoint] != '\0') Flag = 0;
							break;
					}
				}
			}
			startPoint++;
		}
		if (courseNameCounter < 1 || courseNameCounter > 30 || courseNumCounter != 5) Flag = 0;


		if (lineCounter && Flag == 2)
		{

			cleanL = (char*)calloc(lineCounter + 1, sizeof(char));

			if (cleanL)
			{
				startPoint = 0;
				c = 0;
				while (line[startPoint] == 32)
				{
					startPoint++;
				}
				while (line[startPoint] != '\0')
				{
					if (line[startPoint] == 44)//בדיקה ראשונה, האם קיים פסיק
					{
						cleanL[c] = line[startPoint];
						c++;
						Flag = 1;
					}
					else
					{
						if (!Flag)
						{
							if (line[startPoint] != 32)
							{
								if (line[startPoint] >= 48 && line[startPoint] <= 57)
								{
									cleanL[c] = line[startPoint];
									c++;


								}
								else
								{
									Flag = 0;
									break;
								}

							}

						}
						if (Flag == 1 && line[startPoint] != 32)//הגיע לפסיק, מתחיל מיד אחריו
						{
							if ((line[startPoint] >= 97 && line[startPoint] <= 122) || (line[startPoint] >= 65 && line[startPoint] <= 90) || (line[startPoint] >= 48 && line[startPoint] <= 57))
							{
								Flag = 2;
								cleanL[c] = line[startPoint];
								startPoint++;
								c++;

							}
							else
							{
								Flag = 0;
								break;
							}

						}
						if (Flag == 2)
						{

							if ((line[startPoint] >= 97 && line[startPoint] <= 122) || (line[startPoint] >= 65 && line[startPoint] <= 90) || (line[startPoint] >= 48 && line[startPoint] <= 57) || line[startPoint] == 32)
							{
								cleanL[c] = line[startPoint];
								c++;

							}
							else
							{
								Flag = 0;
								break;
							}
						}
					}
					startPoint++;
					//Flag = 1;
				}

				
					//printf("cleanL 'checkLine'_func check: %s\n", cleanL);


					Strcpy(line, cleanL);
					if (strcmp(line, cleanL) == 0)
					{
						free(cleanL);
						cleanL = NULL;
						return 1;
					}
				//	Flag = 1;
				

			}
			else("Free_of_space_line allocation error in func 'checkLine'\n");//לשנות
		}
		//else printf("Error: invalid class number or name.\n");//invalid format of input
	}
	return 0;

}

void printCoursesAndStudents(courses C)
{
	course* currC = NULL;
	student* currS = NULL;
	if (C.course_head)
	{
		currC = C.course_head;
		while (currC)
		{
			printf("\nClass %c%s %s%c students:\n", 34, currC->Cnum, currC->Cname, 34);
			if (currC->Stud)
			{
				currS = currC->Stud;
				while (currS)
				{
					printf("%s, %s\n", currS->name, currS->grade);
					currS = currS->next;
				}
				printf("\n");
			}
			else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
			currC = currC->next;

		}

	}
	else
	{
		printf("Error: there are no classes\n");
	}
}
void printStudentsinCurrC(course* C)
{
	student* curr = NULL;
	if (C->Stud)
	{
		curr = C->Stud;
		while (curr)
		{
			printf("%s,%s\n", curr->name, curr->grade);
			curr = curr->next;

		}
		printf("\n");
	}
	else
	{
		printf("Class  %c%s %s%c has no students.\n", 34, C->Cnum, C->Cname, 34);
	}
}


void DeleteStudent(course** head, char* studentName, char* courseNum)
{
	S_data* currS_data = NULL;
	course* currC = NULL;
	student* toDelete = NULL, * temp = NULL;
	//int flag = 0;
	if (*head)
	{
		currC = *head;
		while (currC && (strcmp(currC->Cnum, courseNum) != 0))
		{
			currC = currC->next;
		}
		if (currC && (strcmp(currC->Cnum, courseNum) == 0))
		{
			if (currC->Stud)
			{
				if (strcmp(currC->Stud->name, studentName) == 0)
				{
					toDelete = currC->Stud;
					currC->Stud = currC->Stud->next;
					printf("Student %c%s%c removed from class %c%s %s%c.\n", 34, toDelete->name, 34, 34, currC->Cnum, currC->Cname, 34);
					free(toDelete);
					toDelete = NULL;
				}
				else
				{
					toDelete = currC->Stud;

					while (toDelete->next && strcmp(toDelete->next->name, studentName) != 0)
					{
						toDelete = toDelete->next;
					}
					if (toDelete->next && strcmp(toDelete->next->name, studentName) == 0)
					{
						temp = toDelete->next;
						toDelete->next = toDelete->next->next;
						printf("Student %c%s%c removed from class %c%s %s%c.\n", 34, toDelete->name, 34, 34, currC->Cnum, currC->Cname, 34);
						free(temp);
						temp = NULL;

					}
					else printf("Error: student is not a member of class %c%s %s%c.\n", 34, currC->Cnum, currC->Cname, 34);
				}

			}else printf("Error: student is not a member of class %c%s %s%c.\n", 34, currC->Cnum, currC->Cname, 34);

		
		}else printf("Error: invalid name or class number.\n");
		//else printf("class doesn't exist\n");


	}
	else
	{
		printf("Error: invalid name or class number.\n");
		//printf("The list of courses is empty!\n");
	}
}
void notDeleteStudent(course* head, char* studentName, char* courseNum)
{
	S_data* currS_data = NULL;
	course* currC = NULL;
	student* toDelete = NULL, * temp = NULL;
	//int flag = 0;
	if (head)
	{
		currC = head;
		while (currC && (strcmp(currC->Cnum, courseNum) != 0))
		{
			currC = currC->next;
		}
		if (currC && (strcmp(currC->Cnum, courseNum) == 0))
		{
			if (currC->Stud)
			{
				toDelete = currC->Stud;

				while (toDelete->next && strcmp(toDelete->next->name, studentName) != 0)
				{
					toDelete = toDelete->next;
				}
				if (!toDelete->next) printf("Error: student is not a member of class %c%s %s%c.\n", 34, currC->Cnum, currC->Cname, 34);
			}
			else printf("Error: student is not a member of class %c%s %s%c.\n", 34, currC->Cnum, currC->Cname, 34);


		}
		else printf("Error: invalid name or class number.\n");
		//else printf("class doesn't exist\n");


	}
	else
	{
		printf("Error: invalid name or class number.\n");
		//printf("The list of courses is empty!\n");
	}
}

