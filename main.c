#include "Header.h"

//Coded by Chen Bello

void main()
{
	hit hit;
	courses C;
	students S;
	char select;
	int all_Fun_in_loop = 1;
	C.course_head = NULL;
	C.amountOfCourses = 0;
	S.student_head = NULL;
	S.amountOfStudents = 0;
	hit.courses = &C;
	hit.students = &S;
	int i = 0, c = 0, flag = 0, repeats = 0, startPoint = 0;
	course* newCourse = NULL, * toChangeC = NULL, * currCourse = NULL, * currC = NULL;
	student* currS = NULL, * newS = NULL, * findEnd_S = NULL, * toChangeS = NULL, * tempS = NULL;;
	char line[201] = { 0 }, grade[4] = { 0 }, * courseNum = NULL, * courseName = NULL, * studentName = NULL;
	S_data* newS_data = NULL, * currS_data = NULL, * findEnd_S_data = NULL;
	printf("Please select an operation : \n\t1. Exit\n\t2. Insert or update a class\n\t3. Insert or update a student\n\t4. Remove a student from classes\n\t5. Print a class\n\t6. Print all classes with their computed scores\n\t7. Print the menu\n");

	do
	{
		i = c = flag = repeats = startPoint = 0;
		newCourse = toChangeC = currCourse = currC = NULL;
		currS = newS = findEnd_S = toChangeS = tempS = NULL;
		courseNum = courseName = studentName = NULL;
		newS_data = currS_data = findEnd_S_data = NULL;
		select = ' ';
		rewind(stdin);
		do
		{
			rewind(stdin);
			scanf_s("%c", &select);
		} while (select == ' ');

		switch (select)
		{

		case '1':
			freeCoursesL(&C.course_head);
			freeStudentsL(&S.student_head);

			
			all_Fun_in_loop = 0; break;
		case '2'://2.	קליטת קורס חדש עם שמו או עדכון שם של קורס קיים
			currCourse = NULL;
			i = 0, c = 0, flag = 0, startPoint = 0;
			newCourse = NULL, toChangeC = NULL;
			courseNum = NULL, courseName = NULL;
			printf("enter Ex2\n");
			rewind(stdin);
			gets_s(line, 201);
			if (checkLineEx2(line))
			{
				courseNum = makeCourseNumStr(line, &startPoint);

				if (courseNum)
				{
					c = startPoint;
					while (line[c] != '\0')
					{
						i++, c++;
					}
					i++;
					courseName = (char*)calloc(i + 1, sizeof(char));
					if (courseName)
					{
						i = c = 0;
						while (line[startPoint] != '\0')
						{
							courseName[c] = line[startPoint];
							c++;
							startPoint++;
						}
						(courseName)[c] = '\0';
						toChangeC = NULL;
						flag = ExistingCourseNum(C.course_head, &toChangeC, courseNum);
						if (!flag && !toChangeC)
						{
							newCourse = createCourse(courseName, courseNum);//לכל קורס יש מספר קורס ושם קורס
							if (newCourse)
							{
								InsertCourse(&C.course_head, newCourse);
								C.amountOfCourses++;
								printf("Class %c%s, %s%c added.\n", 34, newCourse->Cnum, newCourse->Cname, 34);
							}
							else printf("Unfortunately, there is no room for more classes.\n");

						}
						else if (flag && toChangeC)
						{
							while (courseName[i] != '\0')
							{
								toChangeC->Cname[i] = courseName[i];
								i++;
							}
							toChangeC->Cname[i] = '\0';
							printf("Class %c%s, %s%c updated.\n", 34, toChangeC->Cnum, toChangeC->Cname, 34);

						}

					}

				}
				
			}else printf("Error: invalid class number or name.\n");//invalid format of input

			//if (strlen(courseNum) > 1)free(courseName);// ?
			//free(courseNum);
			courseName = courseNum = NULL;
			break;
		case '3'://3.	רישום סטודנט לקורסים עם הציונים שלו או עדכון ציוניו של סטודנט בקורסים.
			currC = NULL;
			currS = NULL;
			currS_data = NULL;
			i = repeats = 0;
			toChangeS = NULL;
			while (line[i] != '\0')
			{
				line[i] = '\n';
				i++;
			}
			line[i] = '\n';
			studentName = courseNum = NULL;
			printf("enter Ex3\n");
			rewind(stdin);
			gets_s(line, 201);

			if(checkLineEx3(line, &repeats))
			{
				//printf("repeats: %d\n\n", repeats);//delete
				startPoint = 0;
				if (C.course_head)
				{
					studentName = NULL;
					studentName = makeStudNameStr(line, &startPoint);
					if (studentName)
					{
						for (i = 0; i < repeats; i++)
						{
							currC = NULL,currS = toChangeS = newS = NULL, newS_data = NULL, courseNum = NULL;
							courseNum = makeCourseNumStr(line, &startPoint);
							if (courseNum && ExistingCourseNum(C.course_head, &currC, courseNum) && currC)
							{
								c = 0;

								while (line[startPoint] != '\0' && line[startPoint] != ';' && c != 3)
								{
									if (line[startPoint] >= '0' && line[startPoint] <= '9')
									{
										grade[c] = line[startPoint];
										c++;
									}
									startPoint++;
								}
								grade[c] = '\0';

								if (!findCurrStudent(currC, &toChangeS, studentName) && !toChangeS)//צריך להוסיף את הסטודנט
								{
									newS = createStud(studentName, courseNum, grade);
									if (newS)
									{
										tempS = NULL;
										flag = 0;
										if (!currC->Stud)
										{
											currC->Stud = newS;
											if (currC->Stud)flag = 1;

										}
										else if (currC->Stud && !currC->Stud->next)
										{


											if (strcmp(currC->Stud->name, newS->name) > 0)//
											{
												tempS = currC->Stud;
												currC->Stud = newS;
												newS->next = tempS;
												newS = newS->next;
												newS->next = NULL;
												tempS = NULL;
												flag = 1;
											}
											else
											{
												currC->Stud->next = newS;
												flag = 1;
											}


										}
										else
										{
											findEnd_S = currC->Stud;

											if (strcmp(findEnd_S->name, newS->name) > 0 || strcmp(findEnd_S->name, newS->name) == 0)
											{
												tempS = currC->Stud;
												currC->Stud = newS;
												newS->next = tempS;
												tempS = NULL;
												flag = 1;

											}

											while (findEnd_S->next)
											{
												if ((strcmp(findEnd_S->name, newS->name) < 0) && ((strcmp(findEnd_S->next->name, newS->name) > 0) || (strcmp(findEnd_S->next->name, newS->name) == 0)))
												{
													newS->next = findEnd_S->next;
													findEnd_S->next = newS;
													flag = 1;
													break;
												}
												else findEnd_S = findEnd_S->next;
											}
											if (!findEnd_S->next && (strcmp(findEnd_S->name, newS->name) < 0) || (strcmp(findEnd_S->name, newS->name) == 0))
											{
												findEnd_S->next = newS;
												flag = 1;
											}
										}

										if (flag)
										{
											currS_data = newS_data = NULL;
											currC->numofstudents++;
										}
										currS_data = findEnd_S_data = NULL;

										if (!findCurrS_data(S, &currS_data, studentName) && !currS_data)
										{
											newS_data = createS_data(studentName);
											if (newS_data && insertS_data(&S.student_head, newS_data))S.amountOfStudents++;
										}
										else if (findCurrS_data(S, &currS_data, studentName) && currS_data)// && !insertS_data(&S.student_head, newS_data))
										{
											currS_data->amountOfCourses++;
										}
												
										printf("Student %c%s%c added to class %c%s %s%c with grade %s.\n", 34, studentName, 34, 34, currC->Cnum, currC->Cname, 34, grade);
										newS = NULL, currC = NULL,newS_data = NULL;
									}

								}

								else if (findCurrStudent(currC, &toChangeS, studentName) && toChangeS)
								{

									Strcpy(toChangeS->grade, grade);
									printf("Student %c%s%c updated on class %c%s %s%c with grade %s.\n", 34, toChangeS->name, 34, 34, currC->Cnum, currC->Cname, 34, toChangeS->grade);

								}
								newS = toChangeS = NULL, currS_data = newS_data = NULL;
								currC = NULL;
								free(courseNum);
								courseNum = NULL;

							}
							else printf("Error: invalid name, class number or grade(Course doesn't exist).\n");//לשנות


						}

					}
						free(studentName);
						//free(courseNum);
						studentName = courseNum = NULL;
				
				}
				else printf("Error: invalid name, class number or grade(Courses list is empty).\n");
			}
			else
			{
				printf("Error: invalid name, class number or grade.\n");
			}
			freeStaticLineAndGrade(line, grade);

			
			

			 break;
		case '4': //4. מחיקת סטודנט קיים מקורסים בהם הוא משתתף
			flag = 0;
			currC = NULL, currS = NULL,currS_data=NULL, courseNum = studentName = NULL, repeats = startPoint = 0;
			printf("enter Ex4\n");
			rewind(stdin);
			gets_s(line, 201);
			if (checkLineEx4(line, &repeats) && S.student_head && C.course_head && repeats)
			{


				currS_data = NULL;
				currS = NULL;
				currC = NULL;
				flag = 1, c = 0, startPoint = 0;
				courseNum = studentName = NULL;
				studentName = makeStudNameStr(line, &startPoint);

				if (studentName && findCurrS_data(S, &currS_data, studentName) && currS_data)
				{
					free(studentName);
					studentName = NULL;

					if (currS_data->amountOfCourses == repeats)printf("Error: student cannot be removed from all classes.\n");
					else
					{
						if (checkIfBelongsToAllClassesEx4(C, S, line, repeats))
						{
							currC = NULL, currS = NULL, startPoint = 0, courseNum = studentName = NULL;
							studentName = makeStudNameStr(line, &startPoint);
							if (studentName)
							{
								for (i = 0; i < repeats; i++)
								{
									courseNum = makeCourseNumStr(line, &startPoint);
									if (courseNum)
									{
										DeleteStudent(&C.course_head, studentName, courseNum);
										currS_data->amountOfCourses--;

										free(courseNum);
										courseNum = NULL;
									}
								}
								free(studentName);
								studentName = NULL;
							}
						}
						else
						{
							currC = NULL, currS = NULL, startPoint = 0, courseNum = studentName = NULL;
							studentName = makeStudNameStr(line, &startPoint);
							if (studentName)
							{
								for (i = 0; i < repeats; i++)
								{
									courseNum = makeCourseNumStr(line, &startPoint);
									if (courseNum)
									{
										notDeleteStudent(C.course_head, studentName, courseNum);

										free(courseNum);
										courseNum = NULL;
									}
								}
								free(studentName);
								studentName = NULL;
							}
						}
					}
				}
				else printf("Error: invalid name or class number.\n");
			}
			else printf("Error: invalid name or class number.\n");
			
			
				
				
			freeStaticLineAndGrade(line, grade);

			break;
		case '5'://5.	הדפסה של קורס יחד עם כל המשתתפים שלו.
			if (C.course_head)
			{
				printf("enter Ex5\n");
				rewind(stdin);
				gets_s(line, 201);

				if (checkLineEx5(line))
				{
					currC = NULL;
					if (ExistingCourseNum(C.course_head, &currC, line) && currC)
					{
						if (currC->Stud)
						{
							printf("Class %c%s %s%c students:\n", 34, currC->Cnum, currC->Cname, 34);
							printStudentsinCurrC(currC);

						}
						else printf("Class %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
					}
					else printf("Error: invalid class number.\n"); //printf("Error: Class doesn't exist.\n");

				printf("\n\nAll classes and students: \n");
			 	printCoursesAndStudents(C);


				printf("\n\nAll of the students in the university so far:\n");
				printS_data(S);
				}
				else printf("Error: invalid class number.\n");

			}
			else printf("Error: there are no classes\n");
			freeStaticLineAndGrade(line, grade);

			break;

		case '6': 

			/*6. הדפסה של כל הקורסים במערכת, כל אחד עם הציון המחושב שלו:
				.a  ציון ממוצע בקורס.
				.b  ציון מקסימלי בקורס.
				.c  ציון מינימלי בקורס.
				.d  סכום הציונים בקורס.
				.e  מספר הסטודנטים בקורס.*/


			if (C.amountOfCourses == 0 || !C.course_head) printf("Error: there are no classes.\n");
			else
			{
				select = ' ';
				all_Fun_in_loop = 1;


				do
				{
					currC = NULL, currS = NULL;
					do {
						select = ' ';
						printf("Please select the aggregation method:\n\ta.Average Grade.\n\tb.Maximal Grade.\n\tc.Minimal Grade.\n\td.Sum.\n\te.Count.\n\t0. Return to the main menu.\n\n");
						rewind(stdin);
						scanf_s("%c", &select);
					} while (select == ' ' || (select < 'a' && select > 'e' && select != '0'));
					switch (select)
					{


					case 'a':



						currC = C.course_head;
						while (currC)
						{
							if (currC->Stud)
							{
								printf("%s, %s: %.2lf\n", currC->Cnum, currC->Cname, averageGrade(currC));//printf("a.Average Grade of class %c%s, %s%c is: %.2lf\n", 34, currC->Cnum, currC->Cname, 34, averageGrade(currC));
							}
							else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
							currC = currC->next;

						}
						printf("\n");

						break;
					case 'b':
						currC = C.course_head;
						while (currC)
						{

							if (currC->Stud)
							{
								printf("%s, %s: %d\n", currC->Cnum, currC->Cname, maximalGrade(currC));

							}
							else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
							currC = currC->next;

						}
						printf("\n");
						break;
					case 'c':
						currC = C.course_head;
						while (currC)
						{

							if (currC->Stud)
							{
								printf("%s, %s: %d\n", currC->Cnum, currC->Cname, minimalGrade(currC));
							}
							else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
							currC = currC->next;
						}
						printf("\n");

						break;
					case 'd':
						currC = C.course_head;
						while (currC)
						{
							if (currC->Stud)
							{
								printf("%s, %s: %d\n", currC->Cnum, currC->Cname, sum(currC));
							}
							else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
							currC = currC->next;

						}
						printf("\n");
						break;
					case 'e':
						currC = C.course_head;
						while (currC)
						{
							if (currC->Stud)
							{
								printf("%s, %s: %d\n", currC->Cnum, currC->Cname, currC->numofstudents);
							}
							else printf("Class  %c%s %s%c has no students.\n", 34, currC->Cnum, currC->Cname, 34);
							currC = currC->next;

						}
						printf("\n");
						break;


					/*case '0': 
						break;*/

					}
				} while (all_Fun_in_loop && select != '0');
			}
			break;

		case '7': printf("Please select an operation : \n\t1. Exit\n\t2. Insert or update a class\n\t3. Insert or update a student\n\t4. Remove a student from classes\n\t5. Print a class\n\t6. Print all classes with their computed scores\n\t7. Print the menu\n");
			break;
		default: printf("Error: unrecognized operation.\n"); break;
		}
		if ((select != '1') && (select != '6') && (select != '7'))printf("\nSelect the next operation(insert 6 for the entire menu) :\n");

	} while (all_Fun_in_loop && select);
}