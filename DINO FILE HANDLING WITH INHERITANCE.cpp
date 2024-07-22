#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <fstream>

// Define constants for the positions of the dinosaur and the hurdle
#define dinoPos 2
#define hurdlePos 74

using namespace std;

// Get the handle to the console window
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int speed = 8;
static int gameover = 0;
int lastscore;

// Function to set the cursor position in the console window
class imp_function
{
	private:
		
	public:
	void gotoxy(int x, int y)
	{
    	COORD coord;
    	coord.X = x;
    	coord.Y = y;
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
};

// Class representing the Dinosaur
class Dino: public imp_function
{
	private:
    	int dinoY; // The vertical position of the dinosaur
    	int foot; // Flag to alternate between foot positions

	public:
    	// Constructor to initialize the dinosaur position and foot flag
    	Dino()
		{
        	dinoY = 0;
        	foot = 0;
    	}

    	// Function to move the dinosaur
    	void move(int jump = 0)
		{
        	if (jump == 0)
            {
				dinoY = 0;
			}
        	else if (jump == 2)
			{
            	dinoY--;
        	}
        	else
            	dinoY++;

        	// Draw the dinosaur at the updated position
        	gotoxy(dinoPos, 15 - dinoY); cout << "                 ";
        	gotoxy(dinoPos, 16 - dinoY); cout << "         ÜÛßÛÛÛÛÜ";
        	gotoxy(dinoPos, 17 - dinoY); cout << "         ÛÛÛÛÛÛÛÛ";
        	gotoxy(dinoPos, 18 - dinoY); cout << "         ÛÛÛÛÛßßß";
        	gotoxy(dinoPos, 19 - dinoY); cout << " Û      ÜÛÛÛÛßßß ";
        	gotoxy(dinoPos, 20 - dinoY); cout << " ÛÛÜ  ÜÛÛÛÛÛÛÜÜÜ ";
        	gotoxy(dinoPos, 21 - dinoY); cout << " ßÛÛÛÛÛÛÛÛÛÛÛ  ß ";
        	gotoxy(dinoPos, 22 - dinoY); cout << "   ßÛÛÛÛÛÛÛß     ";
        	gotoxy(dinoPos, 23 - dinoY);

        	// Draw the foot position based on the jump state and foot flag
        	if (jump == 1 || jump == 2)
			{
            	cout << "    ÛÛß ßÛ       ";
            	gotoxy(2, 24 - dinoY);
            	cout << "    ÛÜ   ÛÜ      ";
        	}
        	else if (foot == 0)
			{
            	cout << "    ßÛÛß  ßßß    ";
            	gotoxy(2, 24 - dinoY);
            	cout << "      ÛÜ         ";
            	foot = !foot;
        	}
        	else if (foot == 1)
			{
	            cout << "     ßÛÜ ßÛ      ";
	            gotoxy(2, 24 - dinoY);
    	        cout << "          ÛÜ     ";
        	    foot = !foot;
        	}

        	// Draw the ground or empty space below the dinosaur
        	gotoxy(2, 25 - dinoY);
        	if (jump == 0)
			{
            	cout << "ßßßßßßßßßßßßßßßßß";
        	}
        	else
			{
            	cout << "                ";
        	}

       	 // Pause the program for a short duration to control the speed of the game
    	    Sleep(speed);
    	}

    	// Function to get the vertical position of the dinosaur
    	int getY()
		{
        return dinoY;
    	}
};

// Class representing the Hurdle
class Hurdle: public imp_function
{
	private:
	    int plantX; // The horizontal position of the hurdle
    	int score; // The score accumulated by the player

	public:
    	// Constructor to initialize the hurdle position and score
    	Hurdle()
		{
        	plantX = 0;
        	score = 0;
    	}

    	// Function to draw the hurdle and check for collisions with the dinosaur
    	void draw(Dino& dino)
		{
	        // Check if there is a collision between the hurdle and the dinosaur
	        if (plantX == 56 && dino.getY() < 4)
			{
        	
//            ofstream file("score.txt", ios::app);
//            file << score << endl;                //writing in file :(
//            file.close();
			ofstream write("score.txt");          //writing in file :)
			write<<score<<endl;
            
            score = 0;
            speed = 20;

            // Display "Game Over" message and wait for a key press
            gotoxy(36, 8); cout << "Game Over";
            getch();
            gameover = 1;
        	}	

        // Draw the hurdle at the current position
        gotoxy(hurdlePos - plantX, 21); cout << "|_| ";
        gotoxy(hurdlePos - plantX, 22); cout << "|_| ";
        gotoxy(hurdlePos - plantX, 23); cout << " |  ";
        gotoxy(hurdlePos - plantX, 24); cout << " |  ";

        plantX++;

        // If the hurdle reaches the end of the screen, reset its position, increase the score,
        // and adjust the speed of the game
        if (plantX == 73)
		{
            plantX = 0;
            score++;
            gotoxy(11, 2); cout << "     ";
            gotoxy(11, 2); cout << score;
        }
    }
};

// Function to set the cursor visibility and size
class test: public imp_function
{
	public:
		void setcursor(bool visible, DWORD size) {
    	if (size == 0)
		{
        	size = 20; // default cursor size. Changing to numbers from 1 to 20 decreases cursor width
    	}
    	CONSOLE_CURSOR_INFO lpCursor;
    	lpCursor.bVisible = visible;
    	lpCursor.dwSize = size;
    	SetConsoleCursorInfo(console, &lpCursor);
	}
	
	void Read()
	{
		ifstream read("score.txt");  
		 read>>lastscore;
	}
	
	// Function to initialize the game
	void init()
	{
		Read();
    	system("cls");
    	gameover = 0;

	    gotoxy(3, 2); cout << "SCORE : ";
	    gotoxy(20, 2); cout << "Last SCORE : "<<lastscore;
     
	    for (int i = 0; i < 79; i++)
		{
        	gotoxy(1 + i, 1); cout << "ß"; // Draw the top border
        	gotoxy(1 + i, 25); cout << "ß"; // Draw the bottom border
    	}
     
	}

	// Function to start the game
	void play()
	{
	    system("cls");
	    int i;
	    init();
	    Dino dino;
    	Hurdle hurdle;
    	while (true)
		{
	        // Move the dinosaur and draw the hurdle until a key is pressed
	        while (!kbhit())
			{
            	if (gameover == 1)
				{
                	return;
            	}
            	dino.move();
            	hurdle.draw(dino);
        	}
        	char key = getch();
        	if (key == ' ')
			{
            	i = 0;
            	// Perform a jump animation when a key is pressed
            	while (i < 12)
				{
	                dino.move(1);
    	            hurdle.draw(dino);
        	        i++;
            	}
            	// Restore the dinosaur position after the jump animation
            	while (i > 0)
				{
                	dino.move(2);
                	hurdle.draw(dino);
                	i--;
            	}
        	}
        	else if (key == 'q' || key == 'Q')
			{
	            system("cls");
	            exit(0);
    	    }
    	}
};
// Function to display game instructions
void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n1. Avoid hurdles by jumping";
    cout << "\n2. Press 'Spacebar' to jump";
    cout << "\n3. Press 'p' to pause the game";
    cout << "\n4. Press 'Escape' to exit the game";
    cout << "\n\nPress any key to go back to the menu";
    getch();
}

// Function to display the last score from the file


};

int main()
{
	test t1;
    t1.setcursor(0, 0); // Hide the cursor

    do {
        system("cls");
        t1.gotoxy(20, 5); cout << " -------------------------- ";
        t1.gotoxy(20, 6); cout << " |        DINO RUN        | ";
        t1.gotoxy(20, 7); cout << " -------------------------- ";
        t1.gotoxy(20, 9); cout << "1. Start Game";
        t1.gotoxy(20, 10); cout << "2. Instructions";
        t1.gotoxy(20, 11); cout << "3. Quit";
        t1.gotoxy(20, 13); cout << "Select option: ";
        char op = getche();

        if (op == '1')
		{
            t1.init(); // Initialize the game
           // displayLastScore(); // Display the last score
            t1.play(); // Start the game
        }
        else if (op == '2')
        {
			t1.instructions(); // Display instructions
		}
        else if (op == '3')
        {
		    exit(0); // Quit the program
    	}

    }
	while (1);

    return 0;
}

