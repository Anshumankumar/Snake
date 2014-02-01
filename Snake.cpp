#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum direction {up,down,left,right};
bool gameflag=true;
int maxx=9;int maxy= 3;
double speed=300;
class fruit
{
    int positionfx;
    int positionfy;
public:
    int point;
    void compare_snake(int,int,int&);
    void set_values();
    void displayfruit();


}fruit1,Bigfruit;




void fruit::set_values()
{
    srand(time(NULL));
    int a=1+int(rand()%(maxx-2));
    positionfx=a;
    int b=1+int(rand()%(maxy-2));
    positionfy=b;


}

void fruit::displayfruit()
{

    move(positionfy,positionfx);
    printw("#");
}

void fruit::compare_snake(int m,int n,int & size)
{
    if(positionfx==m && positionfy==n)
    {

        point++;
        set_values();
        displayfruit();
        move(n,m);
        printw(" ");
	size++;
	move(0,0);
	printw("%d",point);
	if (point%3==0)speed=speed*0.90;

    }
}


class snake
{

    int positionx;
    int positiony;
    direction keypressed;
    int fullpositionx[100];
    int fullpositiony[100];

public:
    int size;
    snake(int,int);

    void set_direction(int);
    void displaysnake();
    void displaysnake2();
    void get_position(int&,int&);
    void move_snake();
    void collision();


};

void snake::collision()
{
for (int i=1;i<size;i++)
{
if (fullpositionx[i]==positionx && fullpositiony[i]==positiony) gameflag=false;

}


}


void snake::move_snake()
{
    for(int i=size-1;i>0;i--)
{
	fullpositionx[i]=fullpositionx[i-1];
	fullpositiony[i]=fullpositiony[i-1];


}

fullpositionx[0]=positionx;
fullpositiony[0]=positiony;
}


void snake::get_position(int& m, int& n)
{
    m=positionx;
    n=positiony;
    	
	


}
snake::snake(int x,int y)
{
    positionx=x;
    positiony=y;
    keypressed=left;
    fullpositionx[0]=x+1;
    fullpositionx[1]=x+2;
    fullpositionx[2]=x+3;
    fullpositiony[0]=y;
    fullpositiony[1]=y;
    fullpositiony[2]=y;


};


void snake::set_direction(int a)
{

    if ((a==KEY_UP || (char)a=='w') && keypressed!=down)keypressed=up;
    if ((a==KEY_DOWN || (char)a=='s') && keypressed!=up)keypressed=down;

    
    if ((a==KEY_LEFT || (char)a=='a') && keypressed!=right) keypressed=left;
    if ((a==KEY_RIGHT || (char)a=='d') && keypressed!=left) keypressed=right;

}




void snake::displaysnake()
{
    if (positiony>0 && positiony<maxy-1)
    {
        if (keypressed==up)
        {	move(positiony,positionx);
            positiony--;
            if (positiony==0) {
		positiony++;
		gameflag=false;
}


            printw(" ");
            move(positiony,positionx);
            addch('0');
        }
        if (keypressed==down)
        {	move(positiony,positionx);
            positiony++;
            if (positiony==maxy-1) {positiony--;
gameflag=false;
}
            printw(" ");
            move(positiony,positionx);
            addch('0');
        }
    }
    if (positionx>0 && positionx<maxx-1)
    {
        if (keypressed==left)
        {	move(positiony,positionx);
            positionx--;
            if (positionx==0) {positionx++;
}
            printw(" ");
            move(positiony,positionx);
            addch('0');
        }
        if (keypressed==right)
        {	move(positiony,positionx);
            positionx++;
            if (positionx==maxx-1) {positionx--;
gameflag=false;
}
            printw(" ");
            move(positiony,positionx);
            addch('0');
        }

    }
move (fullpositiony[size-1],fullpositionx[size-1]);
printw(" ");
}



void snake::displaysnake2()
{

for(int i=0;i<size-1;i++)
{

move (fullpositiony[i],fullpositionx[i]);
addch('o');
}

}

void printboundary(){
    move(0,0);
    for (int i=0;i<=maxx-1;i++) printw("X");
    move(maxy-1,0);
    for (int i=0;i<=maxx;i++) printw("X");
    move(0,0);
    for (int i=0;i<=maxy;i++)
    {
        printw("X");
        move(i,0);
    }

    move(maxy-1,maxx-1);
    for (int i=0;i<=maxy;i++)
    {
        printw("X");
        move(i,maxx-1);
    }




}


int main()
{
    loop:
    clear();
    fruit1.point=0;
    speed=300;
    int a;
    int m,n;
    initscr();
    getmaxyx(stdscr,maxy,maxx);

    snake snake1(maxx/2,maxy/2);
    fruit1.set_values();

    printw("Press any key to start");

    getch();
    clear();
    printboundary();
    curs_set(0);
    snake1.size=3;
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);


   bool flag=true;

    fruit1.displayfruit();
    refresh();


    while(gameflag)
    {

        usleep(1000*speed);

        a=getch();
        snake1.set_direction(a);
        snake1.displaysnake();
	
	snake1.displaysnake2();
	snake1.collision();
	snake1.move_snake();
	
	fruit1.displayfruit();
        refresh();
        snake1.get_position(m,n);
        fruit1.compare_snake(m,n,snake1.size);
	
    }
    nodelay(stdscr, FALSE);
move(maxy/2,maxx/2-5);
printw("GAME OVERlll");
move(maxy/2+2,maxx/2-5);
printw("c to close");
move(maxy/2+1,maxx/2-5);
printw("p to play");
char k;
   while ((k=getch())!='c')
{
if (k=='p')
{
gameflag=true;
goto loop;

}
}

    endwin();

    return 0;
}

