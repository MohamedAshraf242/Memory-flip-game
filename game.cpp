#include<iostream>
#include<conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 115
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int score=0;  // player score
int rand_pos; // position of the pattern between 4 multible choices
int pos;
int select_arrow = 0; // position of the arrow on the screen

void play();



//_______________________STACK__________________________
class Stack
{
    public:
    int top;
    unsigned capacity;
    char* array;
};

// function to create a stack of given
// capacity. It initializes size of stack as 0
Stack* createStack(unsigned capacity)
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = new char[(stack->capacity * sizeof(char))];
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack){
    return stack->top == stack->capacity - 1;
    }

// Stack is empty when top is equal to -1
int isEmpty(Stack* stack){
    return stack->top == -1;
    }

// Function to add an item to stack.
// It increases top by 1
void push(Stack* stack, char item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.
// It decreases top by 1
char pop(Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}





void gotoxy(int x, int y){ // moving cursor to x,y position
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}


void setcursor(bool visible, DWORD size){ // setup cursor
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void gameover(){ // printing GAME OVER screen
	system("cls");
	cout<<endl;
    gotoxy(42,5); cout<<" ------------------------------ ";
    gotoxy(42,6); cout<<" |          GAME OVER         | ";
    gotoxy(42,7); cout<<" ------------------------------";
    gotoxy(55,9); cout<<"SCORE: "<<score;
	gotoxy(48,15);
    cout<<" _____         _____";
    gotoxy(48,16);
    cout<<"|     |       |     |";
    gotoxy(48,17);
    cout<<"|  A  |       |  D  |";
    gotoxy(48,18);
    cout<<"|_____|       |_____|";
    gotoxy(48,19);
    cout<<"REPLAY          MENU";
    score=0;
	if (getch() == 'a')
        play();

}

void win(){ // printing YOU WIN screen
	system("cls");
	score +=1;
	cout<<endl;
    gotoxy(42,5); cout<<" ------------------------------ ";
    gotoxy(42,6); cout<<" |           You Win          | ";
    gotoxy(42,7); cout<<" ------------------------------";
    gotoxy(55,9); cout<<"SCORE: "<<score;
	gotoxy(48,15);
    cout<<" _____         _____";
    gotoxy(48,16);
    cout<<"|     |       |     |";
    gotoxy(48,17);
    cout<<"|  A  |       |  D  |";
    gotoxy(48,18);
    cout<<"|_____|       |_____|";
    gotoxy(48,19);
    cout<<"CONTINUE        MENU";
	if (getch() == 'a')
        play();
    }

void win_over(){ // printing You Are intelligent and end game
	system("cls");
	score +=1;
	cout<<endl;
    gotoxy(42,5); cout<<" ------------------------------ ";
    gotoxy(42,6); cout<<" |     You Are Intelligent    | ";
    gotoxy(42,7); cout<<" ------------------------------";
    gotoxy(55,9); cout<<"SCORE: "<<score;
	gotoxy(41,11);
    cout<<"         ,---,_          ,";
    gotoxy(41,12);
    cout<<"          _>   `'-.  .--'/";
    gotoxy(41,13);
    cout<<"     .--'` ._      `/   <_";
    gotoxy(41,14);
    cout<<"      >,-' ._'.. ..__ . ' '-.";
    gotoxy(41,15);
    cout<<"   .-'   .'`         `'.     '.";
    gotoxy(41,16);
    cout<<"    >   / >`-.     .-'< \ , '._\ ";
    gotoxy(41,17);
    cout<<"   /    ; '-._>   <_.-' ;  '._>";
    gotoxy(41,18);
    cout<<"   `>  ,/  /___\\ /___\\  \_  /";
    gotoxy(41,19);
    cout<<"   `.-|(|  \\o_/  \\o_/   |)|";
    gotoxy(41,20);
    cout<<"       \;        \      ;/";
    gotoxy(41,21);
    cout<<"         \  .-,   )-.  /";
    gotoxy(41,22);
    cout<<"          /`  .'-'.  `\ ";
    gotoxy(41,23);
    cout<<"         ;_.-`.___.'-.;";
    gotoxy(42,25);
    cout<<"Press any key to go back to menu";
    score=0;


	getch();
}

void instructions(){ // printing game instructions screen

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n1. A random pattern will appear to you like this\n           XOOXOO ";
	cout<<"\n\n2. After 3 seconds it will disappear";
	cout<<"\n\n3. You should choose the reversed pattern";
	cout<<"\n\n         OXXXOX  XXOXOX  OOXOOX";
	cout<<"\n\n                           ^";
	cout<<"\n                           ^";
	cout<<"\n                           ^";
	cout<<"\n\n\n\n\nPress any key to go back to menu";
	getch();
}

char rand_char (){ // returning O , X  randomly
if (rand()%2 ==1)
    return 'X';
else
    return 'O';
}




void play(){
    char ch;
    system("cls"); // clear screen

    for(int i=3; i>0; i--){ // counting 3, 2, 1
        gotoxy(SCREEN_WIDTH/2,10); cout<<i;
        Sleep(500);
        system("cls");
        Sleep(500);
    }

    gotoxy(2,2); // printing score top left
    cout<<"SCORE:";
    gotoxy(10,2);
    cout<<score;

    Stack* stack = createStack(6+score); // create stack to store the random pattern

    for (int i=0; i<(6+score); i++){ // printing random pattern and store it on stack
        char x = rand_char();
        gotoxy(SCREEN_WIDTH/2+i-3,10); cout<<x; push(stack,x);
    }

    gotoxy(0,5);
    cout<<"-----------------------------------------------------------------------------------------------------------------------";
    for(int i=0; i<=120; i++){ // erasing the line in 3 seconds
        gotoxy(i,5);    cout<<" ";
        Sleep(40);
    }

    for (int i=0; i<(6+score); i++){ // erasing the random pattern
        gotoxy(SCREEN_WIDTH/2+i-3,10); cout<<' ';
    }




    rand_pos = rand()%3; // the random position of the pattern between 4 multible choices
    for (int i=0; i<rand_pos; i++){ //printing the other patterns before the original one
        pos = SCREEN_WIDTH*i/4+15;
        for (int j=0; j<(6+score); j++){
            gotoxy(pos+j,10); cout<<rand_char();
        }
    }

    pos = SCREEN_WIDTH*rand_pos/4+15;
    for (int i=0; i<(6+score); i++){ //printing the reversed original pattern
        gotoxy(pos+i,10); cout<<pop(stack);
    }

    for (int i=(rand_pos+1); i<4; i++){ //printing the other patterns before the original one
        pos = SCREEN_WIDTH*i/4+15;
        for (int j=0; j<(6+score); j++){
            gotoxy(pos+j,10); cout<<rand_char();
        }
    }

    gotoxy(45,18); // printing the keys
    cout<<" _____       _____       _____";
    gotoxy(45,19);
    cout<<"|     |     |     |     |     |";
    gotoxy(45,20);
    cout<<"|  A  |     |  S  |     |  D  |";
    gotoxy(45,21);
    cout<<"|_____|     |_____|     |_____|";
    gotoxy(45,22);
    cout<<" LEFT         OK         RIGHT";


    do{ // printing arrow on screen to choose the correct answer
        pos = SCREEN_WIDTH*select_arrow/4+15;
        for (int i=0; i<3;i++){
            gotoxy(pos+3,12+i); cout<<'^';
        }
        ch = getch();
        if (ch == 'd' && select_arrow<3)
            select_arrow += 1;

        else if (ch == 'a' && select_arrow>0)
            select_arrow -= 1;

        for (int i=0; i<3;i++){
            gotoxy(pos+3,12+i); cout<<' ';
        }

    }while(ch != 's');

    if (select_arrow == rand_pos)
        if (score < 3)
            win();
        else
            win_over();
    else
        gameover();
}

int main()
{
//_______________________________
//          opening
//_______________________________
// printing intro
    gotoxy(50,9);
    for(int i=0; i<13; i++){
        cout<<"Original Work"[i];
        Sleep(100);
    }

    gotoxy(46,10);
    for(int i=0; i<21; i++){
        cout<<"EECE Cairo University"[i];
        Sleep(100);
    }
    Sleep(2500);




//_______________________________
//          main_screen
//_______________________________

    while(1){
        setcursor(0,0);
        srand( (unsigned)time(NULL));


        system("cls");
        gotoxy(42,5); cout<<" ------------------------------ ";
        gotoxy(42,6); cout<<" |         MEMORY FLIP        | ";
        gotoxy(42,7); cout<<" ------------------------------";
        gotoxy(50,9); cout<<"1. Start Game";
        gotoxy(50,10); cout<<"2. Instructions";
        gotoxy(50,11); cout<<"3. Quit";
        char op = getche();

        if( op=='1') play();
        else if( op=='2') instructions();
        else if( op=='3') exit(0);
    }

	return 0;
}
