/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

//Task One ///////////////////////////////////////////////////////////////
void MakeBox(char *design, int width, int height)
{
	//length here doesn't include the \0
	int length=(width+1)*height;
	design[length]='\0';
	for (int i=0;i<length;i++){
		design[i]=' ';
	}

	for (int i=width;i<length;i=i+width+1){
    	design[i]='\n';
	}
	
	for (int i=0;i<width;i++){
		design[i]='#';
	}

    for (int i=length-2;i>=(length-width-1);i--){
		design[i]='#';
	}

	for (int i=width+1;i<(length-width-2);i=i+width+1){
		design[i]='#';
	}

	for (int i=2*width;i<(length-width-2);i=i+width+1){
		design[i]='#';
	}

	if (width>2 && height>2){
		//if both width and height even --> tested
		if (width%2==0 && height%2==0) {
			design[(-1+height/2)*(width+1)+-1+width/2]='X';
			design[(-1+height/2)*(width+1)+width-width/2]='X';
			design[(height-height/2)*(width+1)+-1+width/2]='X';
			design[(height-height/2)*(width+1)+width/2]='X';
		}
		//both odd --> tested
		else if (width%2!=0 && height%2!=0){
			design[(height/2)*(width+1)+width/2]='X';
		}
		//width even only --> tested
		else if (width%2==0 && height%2!=0) {
			design[(height/2)*(width+1)+-1+width/2]='X';
			design[(height/2)*(width+1)+width/2]='X';
		}

		//height even only
		else {
			design[(-1+height/2)*(width+1)+width/2]='X';
			design[(height-height/2)*(width+1)+width/2]='X';
		}
	}

}

// Task Two ///////////////////////////////////////////////////////////////
void PrintRoom(int room[ROWS][COLS])
{
	for (int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){

			if (room[i][j]==SPACE){
				printf(" "); // new lines
			}
			else if (room[i][j]==WALL){
				printf("#");
			}
			else if (room[i][j]==TARGET){
				printf("*");
			}
			else if (room[i][j]==BOX){
				printf("O");
			}
			else if (room[i][j]==BOX_ON_TARGET){
				printf("@");
			}
			else if (room[i][j]==PERSON){
				printf("X");
			}
			else {
				printf("X");
			}
			if (j==COLS-1){
				printf("\n");
			}
		}
	}
}

// Task Three ///////////////////////////////////////////////////////////////
void InitialiseRoom(int room[ROWS][COLS], char *layout)
{
	int length = strlen(layout);
	int k=0;
		for (int i=0; i<ROWS; i++){
			for (int j=0; j<COLS; j++){
				if (k<length){
				room[i][j]=layout[k]-48;
				k++;
				}
				else {
				room[i][j]=1;
				}
			}
		}		

}

// Task Four ///////////////////////////////////////////////////////////////
void LocatePerson(int room[ROWS][COLS], int *row, int *col)
{
	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLS; j++){
			if (room[i][j]==PERSON || room[i][j]==PERSON_ON_TARGET){
				*row=i; 
				*col=j;
			}
		}
	}
}

// Task Five - Task Eight ////////////////////////////////////////////////////////
void MakeMove(int room[ROWS][COLS], char move, char *allMoves)
{
	int row, col;
	LocatePerson(room, &row, &col);
	if (move=='w'){//or w without ' '
		//need also if that row-1 is not less than 0?? no cause wall would exist around.
		if (room[row-1][col]==SPACE){
			if(room[row][col]==PERSON){
			room[row-1][col]=PERSON;
			room[row][col]=SPACE;

			strcat(allMoves, "w0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row-1][col]=PERSON;
			room[row][col]=TARGET;

			strcat(allMoves, "w0");//why no * here? also how to add 0 prop.
			}
		}

		if (room[row-1][col]==TARGET){
			if(room[row][col]==PERSON){
			room[row-1][col]=PERSON_ON_TARGET;
			room[row][col]=SPACE;

			strcat(allMoves, "w0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row-1][col]=PERSON_ON_TARGET;
			room[row][col]=TARGET;

			strcat(allMoves, "w0");//why no * here? also how to add 0 prop.
			}
		}


			//new
			//person(the person on T) - box - target
		if (room[row-1][col]==BOX){
			if(room[row-2][col]==TARGET){
				if (room[row][col]==PERSON){
					room[row-1][col]=PERSON;
					room[row][col]=SPACE;
					room[row-2][col]=BOX_ON_TARGET;

					strcat(allMoves, "w1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON;
					room[row][col]=TARGET;
					room[row-2][col]=BOX_ON_TARGET;

				strcat(allMoves, "w1");
				}

				}
		}
 // person then person on T - box on T - Target
		if (room[row-1][col]==BOX_ON_TARGET){
			if(room[row-2][col]==TARGET){
				if (room[row][col]==PERSON){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row-2][col]=BOX_ON_TARGET;

					strcat(allMoves, "w1");//why no * here? also how to add 0 prop.
				}

				if (room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row-2][col]=BOX_ON_TARGET;

					strcat(allMoves, "w1");//why no * here? also how to add 0 prop.
				}

			}
		}
		
//person then person on T - box on T - space
		if (room[row-1][col]==BOX_ON_TARGET){
			if(room[row-2][col]==SPACE){
				if(room[row][col]==PERSON){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row-2][col]=BOX;

					strcat(allMoves, "w1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row-2][col]=BOX;

					strcat(allMoves, "w1");
				}
			}

		}
		
//person then person on T - box - space

		if (room[row-1][col]==BOX){
			if(room[row-2][col]==SPACE){
				if(room[row][col]==PERSON){
				room[row-1][col]=PERSON;
				room[row][col]=SPACE;
				room[row-2][col]=BOX;

				strcat(allMoves, "w1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON;
					room[row][col]=TARGET;
					room[row-2][col]=BOX;

					strcat(allMoves, "w1");
				}				
			}

	}

	}

	if (move=='a'){
		if (room[row][col-1]==SPACE){
			if(room[row][col]==PERSON){
			room[row][col-1]=PERSON;
			room[row][col]=SPACE;

			strcat(allMoves, "a0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row][col-1]=PERSON;
			room[row][col]=TARGET;

			strcat(allMoves, "a0");//why no * here? also how to add 0 prop.
			}
		}

		if (room[row][col-1]==TARGET){
			if(room[row][col]==PERSON){
			room[row][col-1]=PERSON_ON_TARGET;
			room[row][col]=SPACE;

			strcat(allMoves, "a0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row][col-1]=PERSON_ON_TARGET;
			room[row][col]=TARGET;

			strcat(allMoves, "a0");//why no * here? also how to add 0 prop.
			}
		}

		//new
			//person(the person on T) - box - target
		if (room[row][col-1]==BOX){
			if(room[row][col-2]==TARGET){
				if (room[row][col]==PERSON){
					room[row][col-1]=PERSON;
					room[row][col]=SPACE;
					room[row][col-2]=BOX_ON_TARGET;

					strcat(allMoves, "a1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON;
					room[row][col]=TARGET;
					room[row][col-2]=BOX_ON_TARGET;

				strcat(allMoves, "a1");
				}

				}
		}
 // person then person on T - box on T - Target
		if (room[row][col-1]==BOX_ON_TARGET){
			if(room[row][col-2]==TARGET){
				if (room[row][col]==PERSON){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row][col-2]=BOX_ON_TARGET;

					strcat(allMoves, "a1");//why no * here? also how to add 0 prop.
				}

				if (room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row][col-2]=BOX_ON_TARGET;

					strcat(allMoves, "a1");//why no * here? also how to add 0 prop.
				}

			}
		}
		
//person then person on T - box on T - space
		if (room[row][col-1]==BOX_ON_TARGET){
			if(room[row][col-2]==SPACE){
				if(room[row][col]==PERSON){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row][col-2]=BOX;

					strcat(allMoves, "a1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row][col-2]=BOX;

					strcat(allMoves, "a1");
				}
			}

		}
		
//person then person on T - box - space

		if (room[row][col-1]==BOX){
			if(room[row][col-2]==SPACE){
				if(room[row][col]==PERSON){
				room[row][col-1]=PERSON;
				room[row][col]=SPACE;
				room[row][col-2]=BOX;

				strcat(allMoves, "a1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON;
					room[row][col]=TARGET;
					room[row][col-2]=BOX;

					strcat(allMoves, "a1");
				}				
			}

	}

	}

    if (move=='s'){
		if (room[row+1][col]==SPACE){
			if(room[row][col]==PERSON){
			room[row+1][col]=PERSON;
			room[row][col]=SPACE;

			strcat(allMoves, "s0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row+1][col]=PERSON;
			room[row][col]=TARGET;

			strcat(allMoves, "s0");//why no * here? also how to add 0 prop.
			}
		}

		if (room[row+1][col]==TARGET){
			if(room[row][col]==PERSON){
			room[row+1][col]=PERSON_ON_TARGET;
			room[row][col]=SPACE;

			strcat(allMoves, "s0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row+1][col]=PERSON_ON_TARGET;
			room[row][col]=TARGET;

			strcat(allMoves, "s0");//why no * here? also how to add 0 prop.
			}
		}

		//new
			//person(the person on T) - box - target
		if (room[row+1][col]==BOX){
			if(room[row+2][col]==TARGET){
				if (room[row][col]==PERSON){
					room[row+1][col]=PERSON;
					room[row][col]=SPACE;
					room[row+2][col]=BOX_ON_TARGET;

					strcat(allMoves, "s1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON;
					room[row][col]=TARGET;
					room[row+2][col]=BOX_ON_TARGET;

				strcat(allMoves, "s1");
				}

				}
		}
 // person then person on T - box on T - Target
		if (room[row+1][col]==BOX_ON_TARGET){
			if(room[row+2][col]==TARGET){
				if (room[row][col]==PERSON){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row+2][col]=BOX_ON_TARGET;

					strcat(allMoves, "s1");//why no * here? also how to add 0 prop.
				}

				if (room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row+2][col]=BOX_ON_TARGET;

					strcat(allMoves, "s1");//why no * here? also how to add 0 prop.
				}

			}
		}
		
//person then person on T - box on T - space
		if (room[row+1][col]==BOX_ON_TARGET){
			if(room[row+2][col]==SPACE){
				if(room[row][col]==PERSON){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row+2][col]=BOX;

					strcat(allMoves, "s1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row+2][col]=BOX;

					strcat(allMoves, "s1");
				}
			}

		}
		
//person then person on T - box - space

		if (room[row+1][col]==BOX){
			if(room[row+2][col]==SPACE){
				if(room[row][col]==PERSON){
				room[row+1][col]=PERSON;
				room[row][col]=SPACE;
				room[row+2][col]=BOX;

				strcat(allMoves, "s1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON;
					room[row][col]=TARGET;
					room[row+2][col]=BOX;

					strcat(allMoves, "s1");
				}				
			}

	}
	}

	if (move=='d'){
		if (room[row][col+1]==SPACE){
			if(room[row][col]==PERSON){
			room[row][col+1]=PERSON;
			room[row][col]=SPACE;

			strcat(allMoves, "d0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row][col+1]=PERSON;
			room[row][col]=TARGET;

			strcat(allMoves, "d0");//why no * here? also how to add 0 prop.
			}
		}

		if (room[row][col+1]==TARGET){
			if(room[row][col]==PERSON){
			room[row][col+1]=PERSON_ON_TARGET;
			room[row][col]=SPACE;

			strcat(allMoves, "d0");//why no * here? also how to add 0 prop.
			}

			if(room[row][col]==PERSON_ON_TARGET){
			room[row][col+1]=PERSON_ON_TARGET;
			room[row][col]=TARGET;

			strcat(allMoves, "d0");//why no * here? also how to add 0 prop.
			}
		}

				//new
			//person(the person on T) - box - target
		if (room[row][col+1]==BOX){
			if(room[row][col+2]==TARGET){
				if (room[row][col]==PERSON){
					room[row][col+1]=PERSON;
					room[row][col]=SPACE;
					room[row][col+2]=BOX_ON_TARGET;

					strcat(allMoves, "d1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON;
					room[row][col]=TARGET;
					room[row][col+2]=BOX_ON_TARGET;

				strcat(allMoves, "d1");
				}

				}
		}
 // person then person on T - box on T - Target
		if (room[row][col+1]==BOX_ON_TARGET){
			if(room[row][col+2]==TARGET){
				if (room[row][col]==PERSON){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row][col+2]=BOX_ON_TARGET;

					strcat(allMoves, "d1");//why no * here? also how to add 0 prop.
				}

				if (room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row][col+2]=BOX_ON_TARGET;

					strcat(allMoves, "d1");//why no * here? also how to add 0 prop.
				}

			}
		}
		
//person then person on T - box on T - space
		if (room[row][col+1]==BOX_ON_TARGET){
			if(room[row][col+2]==SPACE){
				if(room[row][col]==PERSON){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
					room[row][col+2]=BOX;

					strcat(allMoves, "d1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
					room[row][col+2]=BOX;

					strcat(allMoves, "d1");
				}
			}

		}
		
//person then person on T - box - space

		if (room[row][col+1]==BOX){
			if(room[row][col+2]==SPACE){
				if(room[row][col]==PERSON){
				room[row][col+1]=PERSON;
				room[row][col]=SPACE;
				room[row][col+2]=BOX;

				strcat(allMoves, "d1");
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON;
					room[row][col]=TARGET;
					room[row][col+2]=BOX;

					strcat(allMoves, "d1");
				}				
			}

	}

	}

	if (move=='z'){
		UndoMove(room, allMoves);
	}
}

// Task Nine /////////////////////////////////////////////////////////////////
int CheckGameOver(int room[ROWS][COLS])
{
	for (int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			//printf("%d", room[4][7]);
			if(room[i][j]==TARGET || room[i][j]==PERSON_ON_TARGET){
			return 0;
			}
		}

	}

	for (int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			if(room[i][j]==BOX_ON_TARGET){
			return 1;
			}
		}

	}
	return 0;


}

// Task Ten /////////////////////////////////////////////////////////////////
void UndoMove(int room[ROWS][COLS], char *allMoves)
{
	int length = strlen(allMoves);
	char directionOfMovement = allMoves[length-2];
	int boxOrNoBox = allMoves [length-1];
	int row, col;
	LocatePerson(room, &row, &col);

	if (directionOfMovement=='s'){
		if (boxOrNoBox=='1'){//a box moved
			if (room[row-1][col]==SPACE){
				if(room[row][col]==PERSON){
					if(room[row+1][col]==BOX){
						room[row-1][col]=PERSON;
						room[row][col]=BOX;
						room[row+1][col]=SPACE;
					}

					if(room[row+1][col]==BOX_ON_TARGET){
						room[row-1][col]=PERSON;
						room[row][col]=BOX;
						room[row+1][col]=TARGET;
					}
				}

				if(room[row][col]==PERSON_ON_TARGET){
					if(room[row+1][col]==BOX){
						room[row-1][col]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row+1][col]=SPACE;
					}

					if(room[row+1][col]==BOX_ON_TARGET){
						room[row-1][col]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row+1][col]=TARGET;
					}
				}
			}

				//no space 
				if (room[row-1][col]==TARGET){
					if(room[row][col]==PERSON){
						if(room[row+1][col]==BOX){
							room[row-1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row+1][col]=SPACE;
						}

						if(room[row+1][col]==BOX_ON_TARGET){
							room[row-1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row+1][col]=TARGET;
						}
					}

					if(room[row][col]==PERSON_ON_TARGET){
						if(room[row+1][col]==BOX){
							room[row-1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row+1][col]=SPACE;
						}

						if(room[row+1][col]==BOX_ON_TARGET){
							room[row-1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row+1][col]=TARGET;
						}
				}
			}
		}

		if (boxOrNoBox=='0'){//a box didn't move
			if (room[row-1][col]==SPACE){
				if(room[row][col]==PERSON){
					room[row-1][col]=PERSON;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON;
					room[row][col]=TARGET;
				}
			}

			if (room[row-1][col]==TARGET){
				if(room[row][col]==PERSON){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row-1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
				}
			}
		}
	}
//w move
	if (directionOfMovement=='w'){
		if (boxOrNoBox=='1'){//a box moved
			if (room[row+1][col]==SPACE){
				if(room[row][col]==PERSON){
					if(room[row-1][col]==BOX){
						room[row+1][col]=PERSON;
						room[row][col]=BOX;
						room[row-1][col]=SPACE;
					}

					if(room[row-1][col]==BOX_ON_TARGET){
						room[row+1][col]=PERSON;
						room[row][col]=BOX;
						room[row-1][col]=TARGET;
					}
				}

				if(room[row][col]==PERSON_ON_TARGET){
					if(room[row-1][col]==BOX){
						room[row+1][col]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row-1][col]=SPACE;
					}

					if(room[row-1][col]==BOX_ON_TARGET){
						room[row+1][col]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row-1][col]=TARGET;
					}
				}
			}

				//no space 
				if (room[row+1][col]==TARGET){
					if(room[row][col]==PERSON){
						if(room[row-1][col]==BOX){
							room[row+1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row-1][col]=SPACE;
						}

						if(room[row-1][col]==BOX_ON_TARGET){
							room[row+1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row-1][col]=TARGET;
						}
					}

					if(room[row][col]==PERSON_ON_TARGET){
						if(room[row-1][col]==BOX){
							room[row+1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row-1][col]=SPACE;
						}

						if(room[row-1][col]==BOX_ON_TARGET){
							room[row+1][col]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row-1][col]=TARGET;
						}
				}
			}
		}

		if (boxOrNoBox=='0'){//a box didn't move
			if (room[row+1][col]==SPACE){
				if(room[row][col]==PERSON){
					room[row+1][col]=PERSON;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON;
					room[row][col]=TARGET;
				}
			}

			if (room[row+1][col]==TARGET){
				if(room[row][col]==PERSON){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row+1][col]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
				}
			}
		}
	}
//move a
	if (directionOfMovement=='a'){
		if (boxOrNoBox=='1'){//a box moved
			if (room[row][col+1]==SPACE){
				if(room[row][col]==PERSON){
					if(room[row][col-1]==BOX){
						room[row][col+1]=PERSON;
						room[row][col]=BOX;
						room[row][col-1]=SPACE;
					}

					if(room[row][col-1]==BOX_ON_TARGET){
						room[row][col+1]=PERSON;
						room[row][col]=BOX;
						room[row][col-1]=TARGET;
					}
				}

				if(room[row][col]==PERSON_ON_TARGET){
					if(room[row][col-1]==BOX){
						room[row][col+1]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row][col-1]=SPACE;
					}

					if(room[row][col-1]==BOX_ON_TARGET){
						room[row][col+1]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row][col-1]=TARGET;
					}
				}
			}

				//no space 
				if (room[row][col+1]==TARGET){
					if(room[row][col]==PERSON){
						if(room[row][col-1]==BOX){
							room[row][col+1]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row][col-1]=SPACE;
						}

						if(room[row][col-1]==BOX_ON_TARGET){
							room[row][col+1]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row][col-1]=TARGET;
						}
					}

					if(room[row][col]==PERSON_ON_TARGET){
						if(room[row][col-1]==BOX){
							room[row][col+1]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row][col-1]=SPACE;
						}

						if(room[row][col-1]==BOX_ON_TARGET){
							room[row][col+1]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row][col-1]=TARGET;
						}
				}
			}
		}

		if (boxOrNoBox=='0'){//a box didn't move
			if (room[row][col+1]==SPACE){
				if(room[row][col]==PERSON){
					room[row][col+1]=PERSON;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON;
					room[row][col]=TARGET;
				}
			}

			if (room[row][col+1]==TARGET){
				if(room[row][col]==PERSON){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col+1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
				}
			}
		}
	}
//move d
	if (directionOfMovement=='d'){
		if (boxOrNoBox=='1'){//a box moved
			if (room[row][col-1]==SPACE){
				if(room[row][col]==PERSON){
					if(room[row][col+1]==BOX){
						room[row][col-1]=PERSON;
						room[row][col]=BOX;
						room[row][col+1]=SPACE;
					}

					if(room[row][col+1]==BOX_ON_TARGET){
						room[row][col-1]=PERSON;
						room[row][col]=BOX;
						room[row][col+1]=TARGET;
					}
				}

				if(room[row][col]==PERSON_ON_TARGET){
					if(room[row][col+1]==BOX){
						room[row][col-1]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row][col+1]=SPACE;
					}

					if(room[row][col+1]==BOX_ON_TARGET){
						room[row][col-1]=PERSON;
						room[row][col]=BOX_ON_TARGET;
						room[row][col+1]=TARGET;
					}
				}
			}

				//no space 
				if (room[row][col-1]==TARGET){
					if(room[row][col]==PERSON){
						if(room[row][col+1]==BOX){
							room[row][col-1]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row][col+1]=SPACE;
						}

						if(room[row][col+1]==BOX_ON_TARGET){
							room[row][col-1]=PERSON_ON_TARGET;
							room[row][col]=BOX;
							room[row][col+1]=TARGET;
						}
					}

					if(room[row][col]==PERSON_ON_TARGET){
						if(room[row][col+1]==BOX){
							room[row][col-1]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row][col+1]=SPACE;
						}

						if(room[row][col+1]==BOX_ON_TARGET){
							room[row][col-1]=PERSON_ON_TARGET;
							room[row][col]=BOX_ON_TARGET;
							room[row][col+1]=TARGET;
						}
				}
			}
		}

		if (boxOrNoBox=='0'){//a box didn't move
			if (room[row][col-1]==SPACE){
				if(room[row][col]==PERSON){
					room[row][col-1]=PERSON;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON;
					room[row][col]=TARGET;
				}
			}

			if (room[row][col-1]==TARGET){
				if(room[row][col]==PERSON){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=SPACE;
				}

				if(room[row][col]==PERSON_ON_TARGET){
					room[row][col-1]=PERSON_ON_TARGET;
					room[row][col]=TARGET;
				}
			}
		}
	}

	allMoves[length-2] ='\0';
}


/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z')) {
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{
	char layout[200] = "0011111000111005100010032011001002320100111043010000100011000011111000000000000000000000000000000000";
	int room[ROWS][COLS] = {0};
	char allMoves[1000]  = {0};

	printf("ENGGEN131 - C Project 2024\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room)) {
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	return 0;
}


