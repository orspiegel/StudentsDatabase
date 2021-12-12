#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ex5.h"
#define MAXGRADE 100
#define MINGRADE 1

void selectNextOpt();
void addClass();
int isValidCalssName(char* className);
int isValidClassNum(char* classNum);
void insertStudent();
void remove_spaces(char* s, char* s_wo);
char* the_token_maker(char* old);
int gradeUpdate(int new_grade, char* name, int k);
int gradeValidation(int grade);
void isID_Exist();
void optCooser_5();
void optCooser_5();
void arithmethic_Iter(char opt);
int average_sum_count(int i, char opt);
int maxOrMin_grade(int i, char op);
int isStuInClass();
int removeStudent(char* fullName, char* course_ID);
int isValidStudentInput(char* input);
int coursesCounter(char* studentName);
int howManyComas(char* str);
void swap(student* a, student* b);
void bubbleSort(student* start, int i);
void printList(student* start);
int isValidFunc1(char* input);
int isTheCourseExist(char* input);
void copy_string(char* old, char* new);
void create_node(char* name_stu, int grade, int i);
int isValidClassorStudidity(char* input);
void opt5_menu();

/*i had to use Global variable to count the cuurent amount of courses on every step of the progrm!
I'm using that counter number a lot on my program, and i need it to keep it value between the functions.*/
int counter = 0;

/*I had to use Global variable here, because  that checkes prevents the program from getting to infinite loop.
eithout that "checker" counter, the menu can get to an situation in which it prints itself non-stop
that checker checks if the menu has already printed*/
int checker = 0;

/******************************************************************************************************************
* Function Name: printMenu
* Input: none
* Output: void
* Function Operation: printd the menu to the board.
******************************************************************************************************************/
void printMenu()
{
	char menu[] = "Please select an operation:\n\t"
		"0. Exit.\n\t1. Insert or update a class.\n\t"
		"2. Insert or update a student.\n\t"
		"3. Remove a student from classes.\n\t"
		"4. Print a class.\n\t5. Print all classes with their computed scores.\n\t"
		"6. Print the menu.\n";
	printf("%s", menu);
	return;
}
/******************************************************************************************************************
* Function Name: operationCooser
* Input: none
* Output: void
* Function Operation: the function scans an input from the user of the operation he chose, and calls to 
*						the corresponding function.
******************************************************************************************************************/
void operationCooser()
{
	
	//string for the input
	char opt[100];
	// ill take an input from the user
	scanf(" %[^\n]", &opt);

	/*if the string is not valid->get out 1*/
	if (strlen(opt) != 1)
	{
		printf("Error: unrecognized operation.\n");
		selectNextOpt();
	}

	/*if he chosed 0*/
	if (strcmp(opt, "0") == 0)
	{
		checker++;
		return;
	}

	/*if he chosed 1*/
	else if (strcmp(opt, "1") == 0)
	{
		addClass();
	}

	/*if he chosed 2*/
	else if (strcmp(opt, "2") == 0)
	{
		insertStudent();
	}

	/*if The user chosed 3*/
	else if (strcmp(opt, "3") == 0)
	{
		isStuInClass();
	}

	/*if he chosed 4*/
	else if (strcmp(opt, "4") == 0)
	{
		isID_Exist();
	}

	/*if he chosed 5*/
	else if (strcmp(opt, "5") == 0)
	{
		opt5_menu();
		if (checker != 0)
		{
			return;
		}
	}
	/*if he chosed 6*/
	else if (strcmp(opt, "6") == 0)
	{
		printMenu();
		checker++;
	}

	/*if he inserted an unvalid char/input*/
	else
	{
		printf("Error: unrecognized operation.\n");
	}

	//print of the minimal menu at the end
	selectNextOpt();
	return;
}

/******************************************************************************************************************
* Function Name: selectNextOpt
* Input: none
* Output: void
* Function Operation: the function asks the user for the nxt option by calling the operationCooser function.
******************************************************************************************************************/
void selectNextOpt()
{
	if (checker == 0)
	{
		printf("Select the next operation (insert 6 for the entire menu):\n");
	}
	else
	{
		checker--;
	}
	/* a cliing to another function, to get the choise of the user*/
	operationCooser();
	return;
}

/******************************************************************************************************************
* Function Name: addClass
* Input: none
* Output: void
* Function Operation: the function checks if the classes array is already full. if it does-
*					the function prints to the user that thhere no more room for more classes.
*					if the classes isnt full- the func asks the user for an input of the class!
*					it cuts the input for his segments: the classes ID, and the class name by strtok func.
*					it checks for every segment if the value is valid, and than, if it valid, it allocates 
*					a place on the memory for that class data. it also rises up the counter of the classes amount.
******************************************************************************************************************/
void addClass()
{
	/*if the counter is more or equal to the maximal valid amount of corses, ill get out*/
	if (counter == 5)
	{
		printf("Unfortunately, there is no room for more classes.\n");
		return;
	}
	//a string for the input
	char temp[200];
	scanf(" %[^\n]", temp);

	//a new string to copy to
	char dest[200];
	
	/*ill duplicate the input so the actions won't ruin him*/
	strcpy(dest, temp);

	//my new string
	char* ornew = dest;

	//ill cut the string by spaces
	char* classNum = strtok(ornew, " ");

	//ill save the last part==the course nanme
	char* className = strtok(NULL, "\0");

	/*if the ID is arleady exist, well be updating.
	ill check if its equal to every one of the IDs of the list*/
	for (int k = 0; k < counter; k++)
	{
		/* if the input ID is equal to another id that already on 
		the classes array, ill put the name on the linked list*/
		if (strcmp(classes[k]->ID, classNum) == 0)
		{
			strcpy(classes[k]->name, className);
			printf("Class \"%s %s\" updated.\n", classNum, className);
			return;
		}
	}

	/*if the string segments are not valid*/
	if (isValidCalssName(className) == 1 || isValidClassNum(classNum) == 1)
	{
		printf("Error: invalid class number or name.\n");
		return;
	}

	/*if theres no space for a new stud, ill get out*/
	class* stud = malloc(sizeof(class));
	if (stud == NULL)
	{
		printf("Error.\n");
		exit;
	}

	/* ill put the new input on the right place at my linkes list*/
	strcpy(stud->name, className);

	/*ill put the new ID that i scanned at the right place at my linked list*/
	strcpy(stud->ID, classNum);
	stud->next = NULL;

	// the classes on place counter (the current amount of classes), will be the stud i initiated
	classes[counter] = stud;

	//increase of the counter of classes
	counter++;
	printf("Class \"% s % s\" added.\n", classNum, className);
	return;
}

/******************************************************************************************************************
* Function Name: isValidClassNum
* Input: char* classNum
* Output: int. valid=0, invalid=1
* Function Operation: the function checks if the class number is valid- if his len is less than 5 chars, and if it
*					contains only decimals.
******************************************************************************************************************/
int isValidClassNum(char* classNum)
{
	/* if the string length isnot equal to the valid length(5), ill return 1. */
	if (strlen(classNum) != 5)
	{
		return 1;
	}

	/*if the class num string contains other than only decimals - ill return 1*/
	for (int i = 0; i < strlen(classNum); i++)
	{
		if (classNum[i] < 48 || classNum[i]>57)
		{
			return 1;
		}
	}

	/*iff all was valid - ill return 0*/
	return 0;
}

/******************************************************************************************************************
* Function Name: isValidClassName
* Input: char* className
* Output: int. valid=0, invalid=1
* Function Operation: the function checks if the class name is valid- if his len is less than 30 chars, and if it
*					contains only aalphabet chars.
******************************************************************************************************************/
int isValidCalssName(char* className)
{
	/*if the class name is empty or the string is too long, ill return 1*/
	if (className == NULL || strlen(className) > 30)
	{
		return 1;
	}

	/*for every char of the classNum string, ill check if it contains
	only an valid characters(only Alphabethical chars or numbers)*/
	for (int i = 0; i < strlen(className); i++)
	{

		/*check if it contains only valid chars. if not - ill return 1
		I had to use those letter (which you can say- MAGIC NUMBERS), because that function 
		figures out if every character of the string is at the valid char domain*/
		if (className[i] <'0' && className[i] != ' ' || (className[i] > '9' && className[i] < 'A') ||
			(className[i] > 'Z' && className[i] < 'a') || className[i]>'z')
		{
			return 1;
		}
	}
	return 0;
}

/******************************************************************************************************************
* Function Name: free_students
* Input: none
* Output: void
* Function Operation: the function freeing from the memory that iv'e been allocated, all the student nodes.
*						to loops: one that runs over the classes array, and an inner one that runs over
*						the linked list, and frees every object (student and his data).
******************************************************************************************************************/
void free_students()
{
	/*initialization of the pointers to NUll before the placemant*/
	class* temp_class = NULL;
	student* head_stu = NULL;
	student* temp_stu = NULL;

	/*for every one of the classes, ill free the first student 
	that holds the pointers to the next student*/
	for (int i = 0; i < counter; i++)
	{
		/*a loop to free the students, i need two loop becuase its different strcts*/
		head_stu = classes[i]->next;

		/*until my dinamic pinter points on null, ill prelude it to be the next one
		and let him free*/
		while (head_stu != NULL)
		{
			temp_stu = head_stu;
			head_stu = head_stu->next;
			//printf("%s\n", (*temp_stu).stu_name);
			free(temp_stu);
		}
		free(classes[i]);
	}
}

/******************************************************************************************************************
* Function Name: insertStudent
* Input: none
* Output: void
* Function Operation: the function scans an input from the user of the operation he chose, and calls to
*						the corresponding function.
******************************************************************************************************************/
void insertStudent()
{
	/*initialization for the chars: one of the input, 
	one ("wo") for the output without spaces, one for one of the copies 
	and one more to the srcond copy*/
	char* user_input[200], user_input_wo[200], after_copy[200], course_copy[200];

	//initialization of i counter
	int i;

	//char* user_input_wo[200];
	scanf(" %[^\n]", user_input);

	/*if the validity check returned 1-> the input invalid*/
	if (isValidClassorStudidity(user_input) == 1)
		return;
	
	/*ill remove the spaces by using the "remove spaces" function iv'e made*/
	remove_spaces(user_input, user_input_wo);

	//the name of the student
	char* name_stu = strtok(user_input, ":");

	//copy of the name of the student
	char* name_stu1 = strtok(user_input_wo, ":");

	//everything after the name of student
	char* after = strtok(NULL, "\0");
	
	//we need a copy to cut
	strcpy(after_copy, after);

	//the first course and grade and then we run
	char* course_grade = strtok(after_copy, ";");

	//char* course_copy[200];
	while (course_grade != NULL)
	{
		strcpy(course_copy, course_grade);

		//this is the course name
		char* course = strtok(course_grade, ",");

		/*finding the right course in the array*/
		for (i = 0; i < counter; i++)
		{

			/*if the right course is found*/
			if (strcmp(course, classes[i]->ID) == 0)
			{
				//the grade
				char* course = strtok(NULL, "\0");

				//ill make his grade a int
				int grade = atoi(course);

				/*if the student already in the system, ill just update 
				 his grade*/

				if (gradeUpdate(grade, name_stu, i) == 0)
					break;

				/*if the student isnt on the system, ill creadte a new node of his data*/
				create_node(name_stu, grade, i);
				break;
			}
			else
				continue;
		}

		//the current that ill manipulate string will be the segment that comes after the";".
		char* current = strtok(after, ";");

		//the next segment will be from the last token, until the end of the string
		after = strtok(NULL, "\0");

		//the grade will be the returned value of the token maker function
		course_grade = the_token_maker(after);
	}
	return;
}

/******************************************************************************************************************
* Function Name: isValidStudentInput
* Input: char* input 
* Output: 0=valid, 1=invalid
* Function Operation: the function checks if the input is valid, if it has an ";" on the last char, 
*						and if it has just one ":". if the answer is NO of one of that questions- 
*						the function returns 1- means invalid. if the answer to both of those questions 
*						is "YES"-> retuens 0.
******************************************************************************************************************/
int isValidClassorStudidity(char* input)
{
	/*if the input didnt passed the validity chek-> ill return 1*/
	if (isValidFunc1(input) == 1)
	{
		printf("Error: invalid name, class number or grade.\n");
		return 1;
	}

	/*if all the courses that the user had input are exist, if not->that func will return 1 and get out*/
	if (isTheCourseExist(input) == 1)
	{
		printf("Error: invalid name, class number or grade.\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

/******************************************************************************************************************
* Function Name: create_node
* Input: char* name_stu, int grade, int i
* Output: void
* Function Operation: the function creates a new node, for every new student. It allocates
					location at the heap memory for every student, by malloc function.
******************************************************************************************************************/
void create_node(char* name_stu, int grade, int i)
{
	//allocate new memory for a stu
	student* ptr = (student*)malloc(sizeof(student));

	/*if the location have failed, ill return.*/
	if (ptr == NULL)
	{
		printf("Error.\n");
		return;
	}
	
	//ill put in the struct the student name, by strcpy
	strcpy(ptr->stu_name, name_stu);

	//ill put it in ptr to grade, that grade data
	ptr->grade = grade;

	/*ill check if it is thew first item, and if it does, ill take forword the pointer to the student */
	if (classes[i]->next == NULL)
	{
		ptr->next = NULL;
		classes[i]->next = ptr;
	}

	/*if the item is the middle of last object and takr forword the objects correspondenly */
	else
	{
		ptr->next = classes[i]->next;
		classes[i]->next = ptr;
	}
	printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n", ptr->stu_name, classes[i]->ID, classes[i]->name, grade);
}

/******************************************************************************************************************
* Function Name: isTheCourseExist
* Input: char* input
* Output: int
* Function Operation: the function checks if the course is exist, and we can enroll the current student
*					for that course.
******************************************************************************************************************/
int isTheCourseExist(char* input)
{ 
	//initialization od the counter i
	int i;
	char* str[200];
	char* wo[200];
	char* to_cmp[200];
	strcpy(str, input);
	char* segment1 = strtok(str, ":");
	char* rest = strtok(NULL, "\0");
	remove_spaces(rest, wo);
	char* token = strtok(wo, ";");
	while (token != NULL)
	{
		for (i = 0; i < counter; i++)
		{
			copy_string(token, to_cmp);
			if (strcmp(to_cmp, classes[i]->ID) != 0)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if (i == counter)
		{
			return 1;
		}
		token = strtok(NULL, ";");
	}
	return 0;
}

/******************************************************************************************************************
* Function Name: copy_string
* Input: char* old, char* new
* Output: void
* Function Operation: the function duplicates the given input until the "," char
******************************************************************************************************************/
void copy_string(char* old, char* new)
{
	//intialization of counter 
	int g = 0;

	/*as long as the char isnt a ",", ill duplicate the string*/
	while (old[g] != ',')
	{
		new[g] = old[g];
		g++;
	}
	new[g] = '\0';
	return;
}

/******************************************************************************************************************
* Function Name: isValidStudentInput
* Input: char* input
* Output: int
* Function Operation: the function checks if the string is valid: if the last string is an ";",
*					if  theres no ":", the string invalid and the function will return 1. else-> the func retuen 0.
******************************************************************************************************************/

int isValidStudentInput(char* input)
{
	// initaialization of the length
	int len = strlen(input);

	/*if the last char is not equal to ";", ill return 1*/
	if (input[len-1] != ';')
	{
		return 1;
	}

	//initialization of the counter to 0
	int cnt = 0;

	/* for every char of the string, ill check if its equal to ":" */
	for (int i = 0; i < len; i++)
	{

		/* if it does equal to ":", ill increase the counnter*/
		if (input[i] == ':')
		{
			cnt++;
		}
	}

	/*if theres no ":" at all, its invalid - and ill return 1.*/
	if (cnt != 1)
	{
		return 1;
	}
	return 0;
}
/******************************************************************************************************************
* Function Name: remove_spaces
* Input: char* s (= string), char* s_wo (= String _ Wihtout Spaces)
* Output: void
* Function Operation: the function takes a two given strings: the original, and the destination empty string.
*					for every char of the original string, it copies that char to the new string, exept 
*					the space chars, until the string terminaor char.
******************************************************************************************************************/
void remove_spaces(char* s, char* s_wo)
{
	//initialization of the indexex by 0
	int i = 0, j = 0;

	/*while the index isnt equal to string terminator*/
	while (s[i] != '\0')
	{
		/* if the char is equal to space, ill increase the index runner only at the
		original string*/
		if (s[i] == ' ')
		{
			i++;
			continue;
		}

		/*if the char isnt a space, ill put that char at the same position
		at the new string.*/
		else
		{
			s_wo[j] = s[i];
			i++;
			j++;
		}
	}

	//a initialization of the string terminator
	s_wo[j] = '\0';
	return;
}

/******************************************************************************************************************
* Function Name: the_token_maker
* Input: char* old = the old string
* Output: char*
* Function Operation: the function thakes a string, duplicate him on a new empty string ive created,
					and cut that string for segments- by the
*					delimitor ";". and then - returns that string.
******************************************************************************************************************/
char* the_token_maker(char* old)
{
	/*if we reached the end*/
	if (old == NULL)
	{
		return NULL;
	}
	//initialization of a new cstring to copy the original to
	char* after_copy2[200];

	//copy of the original string into the new string
	strcpy(after_copy2, old);

	/*ill cut the new string by ";", to get to the next segment*/
	char* new_string = strtok(after_copy2, ";");
	return new_string;
}

/******************************************************************************************************************
* Function Name: gradeUpdate
* Input: int new_grade, char name, int k
* Output: int: 0 if the grade is need to be updated, and 1 if the student hasnt any grade yet.
* Function Operation: the function checks first if the student struct is empty. if it does,
*					it means that it needs to add a new stud. else, if the class is not empty,
*					the function checks at every node on the struct (bt while loop) if it is equal
*					to the given name, and if it does-> the function will update his grade, on the
*					current course.
******************************************************************************************************************/
int gradeUpdate(int new_grade, char* name, int k)
{
	student* head = NULL;
	if (classes[k]->next == NULL)
	{
		return 1;
	}
	head = classes[k]->next;
	while (head != NULL)
	{
		if (strcmp(head->stu_name, name) == 0)
		{
			head->grade = new_grade;
			printf("Student \"%s\" updated on class \"%s\" updated with grade %d.\n", name, classes[k]->ID, new_grade);
			return 0;
		}
		head = head->next;
	}
	return 1;
}

/******************************************************************************************************************
* Function Name: isID_Exist
* Input: none
* Output: void
* Function Operation: the function takes an input from the user, and for every course of the array, compares
*						to the input. if it is equal to one of the class ID's, it calls to a bubble sort 
*						function, sort it alphbethicly, and than prints the objects of the class, sorted by their 
*						names alphabet values!
******************************************************************************************************************/
void isID_Exist()
{
	//int i = 0;
	char input1[200];
	scanf("%s", input1);
	for (int i = 0; i < counter; i++)
	{
		student* start = classes[i]->next;

		if (strcmp(input1, classes[i]->ID) == 0)
		{
			if (classes[i]->next->stu_name == NULL)
			{
				printf("Class \"%s %s\" has no students.\n", classes[i]->ID, classes[i]->name);
			}
			else
			{
				bubbleSort(start, i);
				printf("Class \"%s %s\" students:\n", classes[i]->ID, classes[i]->name);
				printList(start); ///print function!
			}
			return;
		}

	}
	//if the ID doesnt exist!
	printf("Error: invalid class number.\n");
}

/******************************************************************************************************************
* Function Name: opt5_menu
* Input: none
* Output: void
* Function Operation: the function prints the menu of ass 5, if theres a classes on the array.
******************************************************************************************************************/
void opt5_menu()
{
	/*if the amount of courses is not 0, ill print that ineer memu*/
	if (counter != 0)
	{
		printf("Please select the aggregation method:\n	a. Average Grade.\n	b. Maximal Grade.\n	c. Minimal Grade.\n	d. Sum.\n	e. Count.\n	0. Return to the main menu.\n");
		optCooser_5();
	}

	/*if the opt is ==0, ill print an error*/
	else
	{
		printf("Error: there are no classes.\n");
	}
}

/******************************************************************************************************************
* Function Name: optCooser_5
* Input: none
* Output: void
* Function Operation: the function scans an option from the user, and by switch- case menu calls to annother 
*					functions on according to the user choice.
******************************************************************************************************************/
void optCooser_5()
{
	
	//string for the input
	char opt[100];
	// ill take an input from the user
	scanf(" %[^\n]", &opt);

	/*if the string is not valid->get out 1*/
	if (strlen(opt) != 1)
	{
		printf("Error: unrecognized operation.\n");
		selectNextOpt();
	}

	/*if he chosed a*/
	if (strcmp(opt, "a") == 0)
	{
		arithmethic_Iter('a');
		return;
	}

	/*if he chosed b*/
	else if (strcmp(opt, "b") == 0)
	{
		arithmethic_Iter('b');
	}

	/*if he chosed c*/
	else if (strcmp(opt, "c") == 0)
	{
		arithmethic_Iter('c');
	}

	/*if he chosed d*/
	else if (strcmp(opt, "d") == 0)
	{
		arithmethic_Iter('d');
	}

	/*if he chosed e*/
	else if (strcmp(opt, "e") == 0)
	{
		arithmethic_Iter('e');
	}

	/*if he chosed 0*/
	else if (strcmp(opt, "0") == 0)
	{
		selectNextOpt();
	}
	
	/*if he inserted an unvalid char/input*/
	else
	{
		printf("Error: unrecognized operation.\n");
	}

	return;
}

/******************************************************************************************************************
* Function Name: average_sum_count
* Input: int 
* Output: void
* Function Operation: the function checks firstly if the class is not empty.
*					if its not empty, it calculates togehter- the amount of students, the sum of their
*					grades, and their average. She suits th eoperation by the argument of the user input.
*					a for average, d for sum of the grades, and e for the students amount!
******************************************************************************************************************/
int average_sum_count(int i, char opt)
{
	//initialization of the counters
	int gradeSum = 0, numOfStudents = 0;

	/*initialization of the head pointer*/
	student* head = NULL;

	/*if the first object on the linked list is null*/
	if (classes[i]->next->stu_name == NULL)
	{
		printf("Class \"%s %s\" has no students.\n", classes[i]->ID, classes[i]->name);
		return 1;
	}

	/*foroword movement of the head*/
	head = classes[i]->next;

	/*as long as the head pointer isn't NULL, 
	ill calculate together the operations: ill count the students 
	amount and the grades amount  by increasing 
	the counters iv'e initialized, and moving forword the head on the linked list to the next object*/
	while (head != NULL)
	{
		gradeSum += head->grade;
		numOfStudents++;
		head = head->next;
	}

	//calculation of the avarage
	int av = gradeSum / numOfStudents;

	/*if the iser chose a, ill print the average*/
	if (opt == 'a')
	{
		printf("%s %s, %d\n", classes[i]->ID, classes[i]->name, av);
	}

	/*if the iser chose b, ill print the sum of the grades*/
	if (opt == 'd')
	{
		printf("%s %s, %d\n", classes[i]->ID, classes[i]->name, gradeSum);
	}

	/*if the iser chose e, ill print the number of the students*/
	if (opt == 'e')
	{
		printf("%s %s, %d\n", classes[i]->ID, classes[i]->name, numOfStudents);
	}
	
	return av;
}

/******************************************************************************************************************
* Function Name: arithmethic_Iter
* Input: char opt (option of the user)
* Output: void
* Function Operation: the function checks iterates in the array of classes, and calls the arithmethic operations
						function in according to the user input. she does that operation as many times
						as the number of classes that we have(counter).
******************************************************************************************************************/
void arithmethic_Iter(char opt)
{
	/*for "counter" times - as many times as the classes amount*/
	for (int j = 0; j < counter; j++)
	{

		/*if the user chose those options, ill call the function with the corresponding option*/
		if (opt == 'a' || opt == 'd' || opt =='e')
		{
			average_sum_count(j, opt);
		}

		/*if the option is b or c, ill call the function with the corresponding option*/
		else if (opt == 'b' || opt == 'c')
		{
			maxOrMin_grade(j, opt);
		}
	}
	return;
}

/******************************************************************************************************************
* Function Name: maxOrMin_grade
* Input: char str[], int len
* Output: int
* Function Operation: the function checks if the node is not empty, firslty. if it not empty, so it will point 
*					the head to the first object of the linked lst. if the user chosen the option b- so the 
*					function will calculate the maximal grade of the course. if the user chose the c option, the function
*					will calculate the minimal grade.
******************************************************************************************************************/

int maxOrMin_grade(int i, char op)
{
	//initialization of the maximum and minimum counters by 0.
	int MAX = 0, MIN = 0; 

	//initialization of the head ptr by null
	student* head = NULL;

	/*if the pointer to the first student points on null, the class is empty*/
	if (classes[i]->next->stu_name == NULL)
	{
		printf("Class \"%s %s\" has no students.\n", classes[i]->ID, classes[i]->name);
		return 1;
	}

	/*initialization of the head to point on the first student*/
	head = classes[i]->next;

	/*if the user chose 'b'*/
	if (op == 'b')
	{
		/*while the head dosen't point on null (as many times as the student amount)*/
		while (head != NULL)
		{
			/*if the maximum is amaller than the current object, that object value will be the maximum*/
			if (MAX < head->grade)
			{
				MAX = head->grade;
			}

			/*forword movement for the ptr*/
			head = head->next;
		}
		printf("%s %s, %d\n", classes[i]->ID, classes[i]->name, MAX);
	}

	/*if the user chose 'c'*/
	else if (op == 'c')
	{
		//initialization of the minimum to be the first object
		MIN = head->grade;

		/*while the head dosen't point on null (as many times as the student amount)*/
		while (head != NULL)
		{

			/*if the minimum is bigger than the current object, that object value will be the maximum*/
			if (MIN > head->grade)
			{
				MIN = head->grade;
			}

			/*forword movement for the ptr*/
			head = head->next;
		}
		printf("%s %s, %d\n", classes[i]->ID, classes[i]->name, MIN);
	}
	return 0;

}
/******************************************************************************************************************
* Function Name: gradeValidation
* Input: int i
* Output: int. 0 = valid, 1 = invalid
* Function Operation: the function checks if the grade is less than 1 or more than 100, and if it does it
*					returns 1 (means invalid). if not - returns 0 (means valid).
******************************************************************************************************************/

int gradeValidation(int grade)
{
	/*if the grade is more than the maximal grade or less than the minimal grade -> invalid*/
	if (grade < MINGRADE || grade > MAXGRADE)
	{
		return 1;
	}
	return 0;
}
/******************************************************************************************************************
* Function Name: bubbleSort
* Input: student* start, int i
* Output: void
* Function Operation: the function checks if the current name is alphabethicly smaller than the next ahead name,
*					by "strcmp" fumction, and if it does - it calls a swap function that i made,
*					and swaps between both of the nodes places on the list. it does that operation until the
*					pointer "ptr1" is points to NULL - it means we reaches the end of the list, and the list 
*					is sorted. and then, the func print the list.
******************************************************************************************************************/
void bubbleSort(student* start, int i)
{
	//initialization of the student ptr by null
	student* ptr1 = NULL;

	//initialization of swap counter
	int swapped;

	//initialization of one more student* ptr by null;
	student* lptr = NULL;

	/* ill check if the list empty of objects*/
	if (classes[i]->next->stu_name == NULL)
	{
		return;
	}

	/*ill do the action once, and after the first time ill keep doing that operation as long as the 
	swapped counter is not 0*/
	do
	{

		//swapped counter initialization
		swapped = 0;

		//ill point the ptre on the first object
		ptr1 = start;

		/*while the ptr isnt points on nothing*/
		while (ptr1->next != NULL)
		{

			/*if the ALPHABETHICAL value of the name of thecurrent object is BIGGER than the next object value,
			ill call the SWAP function to swap between both of the pointers so the bigger valued object
			will be the former object*/
			if (strcmp(ptr1->stu_name, ptr1->next->stu_name) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}

			// forwording the ptr
			ptr1 = ptr1->next;
		}

		//the first ptr will get the value of the next ptr
		lptr = ptr1;


	} while (swapped);
}

/******************************************************************************************************************
* Function Name: swap
* Input: student* a, student* b
* Output: void
* Function Operation: the function swaps bewtween two nodes. it takes the former node, keep it on an 
*					temporary variable, and than places the next node at the adress of the former node.
*					than, it places the temp, that keeps the former node value, and places it at the next
*					node value -> and that a SWAP! ill od that for both grade and name of the student
******************************************************************************************************************/
void swap(student* a, student* b)
{
	//initialization of null string for the temporary name copy
	char temp2[200];

	//initialization of temporary grade variable to keep a element value
	int temp = a->grade;

	//placement of the secont element at the adess of the first element, now both of them values is b value
	a->grade = b->grade;

	//placement of the a original a value at the address of b
	b->grade = temp;

	/*ill copy the a name element to temp2 addresss, to keep a's value. than ill copy b's 
	value to a's adrees->now both of the elements value is b value. then, ill place a's original value at b adress*/
	strcpy(temp2, a->stu_name);
	strcpy(a->stu_name, b->stu_name);
	strcpy(b->stu_name, temp2);
}

/******************************************************************************************************************
* Function Name: printList
* Input: student* start
* Output: void
* Function Operation: the function prints every object of the linked list, from the start to the end,
*					it keeps moving by promoting of the temp pointer, to the next node vevry time, and
*					every node- it peints.
******************************************************************************************************************/
void printList(student* start)
{
	//initialization of the temp ptr to the starting student
	student* temp = start;

	/*while the student pointer idnt points on nothing (NULL)
	ill keep printing the students data*/
	while (temp != NULL)
	{
		printf("%s, %d\n", temp->stu_name, temp->grade);

		/*move forword the pointer*/
		temp = temp->next;
	}
}
/******************************************************************************************************************
* Function Name: isStuInClass
* Input: none
* Output: int
* Function Operation: the function takes an input from the user. it breaks that string input to segments,
*					to the name segment, and segments of the courses (by strtok). It calls the removestudent
*					function that iv'e made, and if it returns 0(-means-valid), it calls it again to free that
*					student.
******************************************************************************************************************/
int isStuInClass()
{
	//initialization of the counter by 0
	int cnt = 0;

	//initialization of a new string that called WO-> means without spaces input
	char* wo[200];

	//initialization of a new string that will be the full input of the user
	char fullInput[200];
	scanf(" %[^\n]", &fullInput);

	//if the last char isnt ","
	if (fullInput[strlen(fullInput) - 1] != ',')
	{
		printf("Error: invalid name or class number.\n");
		return 1;
	}

	//how many ","
	int comas = howManyComas(fullInput);


	//the full name will points on the string segment that comes former to the ":"
	char* fullName = strtok(fullInput, ":");

	//the cAmount is the value of the number of students that the current students is emrolled to
	int cAmount = coursesCounter(fullName);

	if (comas >= cAmount)
	{
		printf("Error: student cannot be removed from all classes.\n");
		return;
	}
	//the corses ptr will points on the string segment that comes former to the end of the str
	char* courses = strtok(NULL, "\0");

	//ill remove the spaces of the courses str, and put that new str at the "wo" new str address
	remove_spaces(courses, wo);

	//the corses ptr will points on the string segment that comes former to the e","
	char* course_ID = strtok(wo, ",");

	/*while the pointer until the comma isnt points on null*/
	while (course_ID != NULL)
	{
	
		/*if the remove student function returns other than 0, the studnt isnt a member of the class*/
		if (removeStudent(fullName, course_ID) ==1)
		{
			printf("Error: student is not a member of class \"%s %s\"\n", course_ID, fullName);
			return 1;
		}
		if (removeStudent(fullName, course_ID) == 2)
		{
			printf("Error: invalid name or class number.\n");
		}

		//initialization of the pointer to the next segment until the comma
		course_ID = strtok(NULL, ",");
	}
	/*if the student is triyng to be removed from all of his courses*/

	return 0;
}

/******************************************************************************************************************
* Function Name: removeStudent
* Input: char str[], int len
* Output: void
* Function Operation: the function checks if the string is appears on the linked list. if he does, 
*						that func takes the former ptr, points him at the next student to come after
*						the student that we want to remove.
******************************************************************************************************************/
int removeStudent(char* fullName, char* course_ID)
{
	//initialization of the counter by 0
	int cnt = 0;

	/*for as many times as the courses amount*/
	for (int i = 0; i < counter; i++)
	{
		/*if one of the classes ID is similar ti the input*/
		if (strcmp(classes[i]->ID, course_ID) == 0)
		{
			cnt++;
			//initialization of 3 ptrs: head, previous and temporary
			student* head = classes[i]->next;
			student* prev = NULL;
			student* tmp = NULL;

			/*while theres students */
			while (head != NULL)
			{
				/*if the one of the students name is similar to the name input*/
				if (strcmp(head->stu_name, fullName) == 0)
				{

					/*ill put the head value at the temporary address*/
					tmp = head->next;

					/*if the previous student is null, it means that the current is the first*/
					if (prev == NULL)
					{

						/* ill set free the head, and put the ptr value at the classes->next address
						with the original value of the next student to come*/
						free(head);
						classes[i]->next = tmp;
					}

					/*if the student is at the middle/last*/
					else
					{

						/*ill set free the head and put the temporary value at the previous element ptr addres*/
						free(head);
						prev->next = tmp;
					}
					printf("Student \"%s\" removed from class \"%s %s\".\n", fullName, course_ID, classes[i]->name);

					return 0;
				}

				//ill place the values at the new locations pointers
				prev = head;
				head = head->next;
			}
		}

	}

	/*if the counter == 0 that means that the name invalid*/
	if (cnt == 0)
	{
		return 2;
	}
	return 1;
}

/******************************************************************************************************************
* Function Name: coursesCounter
* Input: char* studentName
* Output: int
* Function Operation: the function checks how many commas are on the input string, and
*						that also defines the amount of courses to delete from.
******************************************************************************************************************/
int coursesCounter(char* studentName)
{
	//initialization of the count by 0
	int cnt=0;

	/*for as many times as the courses amount*/
	for (int i = 0; i < counter; i++)
	{
		student* head = classes[i]->next;

		/*while the pinter to student isnt null*/
		while (head != NULL)
		{

			/*if the student is on the lunked list ill increase the counter*/
			if (strcmp(head->stu_name, studentName) == 0)
			{
				cnt++;
			}
			head = head->next;
		}
	}

	/*ill return the amount of courese that the student enrolled to*/
	return cnt;
}

/******************************************************************************************************************
* Function Name: howManyComas
* Input: char* str
* Output: int cnt (commas amount)
* Function Operation: the function checks how many commas are on the input string, and
*						that also defines the amount of courses to delete from.
******************************************************************************************************************/
int howManyComas(char* str)
{
	//initialization of the counter by 0
	int cnt = 0;

	/*for loop that iteratas as the length of the string*/
	for (int i = 0; i < strlen(str); i++)
	{

		/*if the char is a comma, ill increase the counter*/
		if (str[i] == ',')
		{
			cnt++;
		}
	}
	return cnt;
}

/******************************************************************************************************************
* Function Name: isValidFunc1
* Input: char* input
* Output: int 
* Function Operation: the function checks if the commas amount is valid, if the ":" amount is valid and also 
*					if the last char is an ";". if the answer for one of those questions is false-
*					the function will return 1. else -> 0.
******************************************************************************************************************/
int isValidFunc1(char* input )
{
	//nitialization of the counters by 0.
	int cnt = 0,  cnt2 = 0;

	//initialization of the new str to copy to
	char* new[200];

	/* for as many times as the len of the string, ill count the "," and the ":"*/
	for (int i = 0; i < strlen(input); i++)
	{
		//if the char is equal to comma
		if (input[i] == ',')
		{
			cnt++;
		}

		//if the char is equal to ":"
		if (input[i] == ':')
		{
			cnt2++;
		}
	}

	/*if the counters are return inavlid value*/
	if (cnt == 0 || cnt2 > 1)
	{
		return 1;
	}

	/*if the last char isnt semmicoluns*/
	if (input[strlen(input) - 1] != ';')
	{
		return 1;
	}
	return 0;
}