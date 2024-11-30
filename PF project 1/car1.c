#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  
#include <windows.h> 

#define TrackWidth 75    
#define TrackHeight 15  //storage
#define ViewHeight 15 //display    
#define DELAY 500
#define MaxLeaderboard 50 // Maximum number of leaderboard entries
#define acceleration 10
#define HIDE_CURSOR printf("\e[?25l")    

struct LeaderboardEntry
{
    int score;
    char nickname[50];
};

// Functions
void showMenu();
void playGame();
void showRules();
void showLeaderboard();
void initializeTrack(char track[TrackHeight][TrackWidth]);
void printTrack(char track[TrackHeight][TrackWidth], int carPosX, int carPosY);
int checkCollision(char track[TrackHeight][TrackWidth], int carPosX, int carPosY);
void setTextColor(int color);
void saveScore(int score);
void loadLeaderboard(struct LeaderboardEntry leaderboard[], int *numEntries);
void displayLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries);
void sortLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries);
void delay(int milliseconds);
void titleScreen();
void backStory();

int main()
{ 
    HIDE_CURSOR;
    backStory();
    titleScreen();
    int choice;
    while(1)
    {
        showMenu(); 
        printf("Enter choice: ");
        
        while (!_kbhit()) {};
        choice = _getch();

        if(choice <= '1' && choice >= '4')
		{
            system("cls");
            continue;  
        }
        system("cls");
        switch(choice)
        {
        case '1':
            playGame();
            break;
        case '2':
            showRules();
            break;
        case '3':
            showLeaderboard();
            break;
        case '4':
            printf("Thanks for playing!\n");
            return 0;
        default:
            printf("Invalid choice try again\n");
        }
        printf("\nPRESS ANY KEY TO CONTINUE...");
        _getch();
        system("cls");
    }
    return 0;
}
void backStory()
{
 setTextColor(5);    
 printf("=== BACKSTORY===\n\n");

    printf("In the year 2154, Earth has made significant advancements in space travel and colonization.\n");
    printf("Humankind has established thriving colonies on Mars, the Moon, and beyond. However, these advancements\n");
    printf("have attracted the attention of a malevolent alien race known as the *Zylox*, a technologically advanced\n");
    printf("species that has set its sights on Earth for conquest.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("Unbeknownst to humanity, the Zylox have secretly infiltrated Earth, preparing for their invasion.\n");
    printf("Their first wave of attack comes unexpectedly in the form of mysterious, high-tech ships that begin appearing\n");
    printf("across the globe. The Zylox want to destabilize Earth, subdue its population, and harvest its resources.\n");
    printf("Their ships are equipped with sophisticated weaponry and cloaking devices, making them nearly impossible to detect.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("The world is in chaos. Cities are evacuated, governments scramble to mount a defense, and panic spreads.\n");
    printf("Amidst the chaos, a lone survivor, *Alex Cruz*, finds himself behind the wheel of an experimental car—an\n");
    printf("advanced, AI-powered vehicle designed for high-speed travel and exploration.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");
 printf("=== BACKSTORY===\n\n");   
    printf("The car, code-named *\"Vanguard\"*, was initially developed for exploration on hostile planetary surfaces,\n");
    printf("but now it becomes humanity's best hope. With no time to waste and no way to stop the alien invasion,\n");
    printf("Alex has to race through dangerous, alien-infested roads, dodging obstacles, and evading attacks from Zylox\n");
    printf("drones and spacecraft.\n\n");
    printf("\n<CONTINUE>");
    _getch();
    system("cls");  
    setTextColor(7);  
}
void titleScreen()
{
 setTextColor(1);
    printf("  __ __ __  __ __  __ ___    __ _    _ \n");
    printf(" |  _|   / _ \\|  _ \\|  __|/ __|  _ \\  / __| |  | |\n");
    printf(" | |_    | || |  | | |) | |_  | (_ | |_) | | (_ | |_| |\n");
    printf(" |  _|   | || |  | |  _  /|  _|  \\_ \\|  _  /   \\_ \\|  __  |\n");
    printf(" | |__ | || || | | \\ \\| |_ _) | | \\ \\   ___) | |  | |\n");
    printf(" |__|__|\\_/||  \\\\__|__/||  \\\\ |_/||  |_|\n");
    printf("                                                                  \n");
    printf("                                                                  \n");
    setTextColor(3);
    printf("       .-\"\"\"\"\"\"-.\n");
    printf("      /          \\\n");
    printf("     /            \\\n");
    printf("    |              |\n");
    printf("    |,  .-.  .-.  ,|\n");
    printf("    | )(o/  \\o)( |\n");
    printf("    |/     /\\     \\|\n");
    printf("    (_     ^^     _)\n");
    printf("     \\_|IIIIII|_/\n");
    printf("      | \\IIIIII/ |\n");
    printf("      \\          /\n");
    printf("       --------\n");
printf("ESCAPE THE ALIENS\n\n");   
setTextColor(7); 
printf("<<<PRESS ANY KEY TO CONTINUE>>>"); 
_getch();
system("cls");   
}
void showMenu()
{
    printf("\nMenu:\n");
    printf("1. Play\n");
    printf("2. Rules\n");
    printf("3. Leaderboard\n");
    printf("4. Quit\n");
}

void showRules()
{
    printf("\nGame Rules:\n");
    printf("1. Use 'a' or 'A' to swerve the car left.\n");
    printf("2. Use 'd' or 'D' to swerve the car right.\n");
    printf("4. Avoid Aliens (X). If the car crashes into an Alien, the game is over.\n");
    printf("5. Survive for as long as possible!\n\n");
    printf("6. Beware! The Aliens are unpredictable...they can move(horizontally) towards you\n\n");
}

void showLeaderboard()
{
    struct LeaderboardEntry leaderboard[MaxLeaderboard];
    int numEntries = 0;

    // Load leaderboard data from the file
    loadLeaderboard(leaderboard, &numEntries);

    // Sort the leaderboard in descending order of scores
    sortLeaderboard(leaderboard, numEntries);

    // Display the sorted leaderboard
    displayLeaderboard(leaderboard, numEntries);
}

void delay(int milliseconds) {
    Sleep(milliseconds); // Pauses the program for the specified duration in milliseconds
}

void playGame() // Core gameplay function that runs the main loop.
{
    char track[TrackHeight][TrackWidth]; // 2D array representing the game track.
    int carPosX = TrackWidth / 2; // X-position of the car, starts in the middle of the track.
    int carPosY = TrackHeight - 1; // Y-position of the car, starts at the bottom of the track.
    int gameOver = 0; // Boolean flag indicating whether the game is over.
    int score = 0; // Tracks the player's score.
    int input; // Stores player input.
    int i, j;
    int numEntries = 0; 
    // Loop counters for iterating over the track.

    srand(time(0)); // Seeds the random number generator for obstacle placement.
    initializeTrack(track); // Initializes the track with empty spaces.

    int delayed_time = DELAY; // Sets the initial delay between updates.
    printf("\033[%dm", 47); // Sets a white background color for the game display.

    while (!gameOver) // Main gameplay loop.
    {
        printTrack(track, carPosX, carPosY); // Displays the current state of the game.
        if (checkCollision(track, carPosX, carPosY)) // Checks if the car collides with an obstacle.
        {
            system("cls"); // Clears the screen.
            system("color 07"); // Resets the console color.
            printf("Game Over! You collided with an ALIEN.\n"); // Displays a game-over message.
            saveScore(score); // Saves the player's score.
            break; // Exits the loop.
        }

        score++; // Increments the player's score.

        if (_kbhit()) // Checks if a key is pressed.
        {
            input = _getch(); // Captures the pressed key.
            if ((input == 'a' || input == 'A') && carPosX > 0 && track[carPosY][carPosX - 1] != 'X')
            { 
                carPosX -= 4; // Moves the car left if possible.
                Beep(750, 10); // Plays a beep sound.
            }
            else if ((input == 'd' || input == 'D') && carPosX < TrackWidth - 1 && track[carPosY][carPosX + 1] != 'X')
            {
                carPosX += 4; // Moves the car right if possible.
                Beep(750, 10); // Plays a beep sound.
            }
        }

        for (i = TrackHeight - 1; i > 0; i--) // Updates the position of obstacles.
        {
            for (j = 0; j < TrackWidth; j++)
            {
                track[i][j] = track[i - 1][j]; // Shifts obstacles downward by one row.
            }
        }

        for (j = 0; j < TrackWidth; j++) // Generates new obstacles in the top row.
        {
            track[0][j] = (rand() % 100 == 0) ? 'X' : ' '; // 1% probability of placing an obstacle.
        }

        delayed_time /= acceleration; // Gradually decreases the delay for increasing difficulty.
        delay(delayed_time); // Decreases a delay at the end of each iteration.
    }

    struct LeaderboardEntry leaderboard[MaxLeaderboard]; // Array to hold leaderboard entries.
    loadLeaderboard(leaderboard, &numEntries); // Loads the leaderboard data.
    numEntries ++; // Tracks the number of entries.

    printf("\nYour score: %d\n", score); // Displays the final score.
}


void initializeTrack(char track[TrackHeight][TrackWidth])
{
    int i, j;  
    for (i = 0; i < TrackHeight; i++)
    {
        for (j = 0; j < TrackWidth; j++)
        {
            track[i][j] = ' ';
        }
    }
}

void printTrack(char track[TrackHeight][TrackWidth], int carPosX, int carPosY)
{
    int i, j;  
    system("cls");   
    for (i = 0; i < ViewHeight; i++)
    {
        for (j = 0; j < TrackWidth; j++)
        {
            if (i == carPosY && j == carPosX) 
            {
                setTextColor(1); // Blue for car
                printf("#!*!#");
            }
            else if (track[i][j] == 'X') 
            {
                setTextColor(4); // Red for obstacles
                printf("X");
            }
            else
            {
                setTextColor(0); // Default color
                printf(" ");
            }
        }
        printf("\n");
    }
    
}

int checkCollision(char track[TrackHeight][TrackWidth], int carPosX, int carPosY)
{
    if (carPosY >= 0 && carPosY < TrackHeight && carPosX >= 0 && carPosX < TrackWidth)
    {
        return track[carPosY][carPosX] == 'X'||
        track[carPosY][carPosX+1] == 'X'||
        track[carPosY][carPosX+2] == 'X'||
        track[carPosY][carPosX+3] == 'X'||
        track[carPosY][carPosX+4] == 'X'; // Check for obstacle collision
    }
    return 0;
}

void setTextColor(int color)
{
     printf("\033[%dm", 30 + color); // default colour
    
}

// Function to save a score with a nickname
void saveScore(int score)
{
    FILE *fptr;
    char name[50];

    fptr = fopen("scores.txt", "a+"); // Open scores file in append mode
    if (fptr == NULL)
    {
        printf("Error: Unable to save the score.\n");
        return;
    }

    printf("Enter your nickname: ");
    scanf("%49s", name); // Limit input to prevent overflow

    fprintf(fptr, "%d %s\n", score, name); // Write the score and nickname to the file
    fclose(fptr); // Close the file
}

// Function to load the leaderboard from a file
void loadLeaderboard(struct LeaderboardEntry leaderboard[], int *numEntries)
{
    FILE *fptr;
    int score;
    char nickname[50];

    fptr = fopen("scores.txt", "r"); // Open scores file in read mode
    if (fptr == NULL)
    {
        printf("Leaderboard is empty or missing.\n");
        *numEntries = 0; // No entries to load
        return;
    }

    *numEntries = 0; // Initialize entry count
    while (fscanf(fptr, "%d %49s", &score, nickname) != EOF && *numEntries < MaxLeaderboard)
    {
        leaderboard[*numEntries].score = score; // Store score
        strcpy(leaderboard[*numEntries].nickname, nickname); // Store nickname
        (*numEntries)++; // Increment entry count
    }

    fclose(fptr); 
}

// Function to sort the leaderboard in descending order of scores
void sortLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries)
{
    for (int i = 0; i < numEntries - 1; i++)
    {
        for (int j = 0; j < numEntries - i - 1; j++)
        {
            if (leaderboard[j].score < leaderboard[j + 1].score) // Compare scores
            {
                struct LeaderboardEntry temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

// Function to display the leaderboard
void displayLeaderboard(struct LeaderboardEntry leaderboard[], int numEntries)
{
    printf("\nLeaderboard:\n");
    printf("-----------------------------\n");
    printf("| %-5s | %-10s |\n", "Score", "Nickname");
    printf("-----------------------------\n");

    for (int i = 0; i < numEntries; i++)
    {
        printf("| %-5d | %-10s |\n", leaderboard[i].score, leaderboard[i].nickname);
    }

    printf("-----------------------------\n");

    if (numEntries == 0)
    {
        printf("No scores to display.\n");
    }
}