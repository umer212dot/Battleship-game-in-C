
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

char boardP1[9][9], turnBoardP1[9][9];
char boardP2[9][9], turnBoardP2[9][9];
char ship5P1[2][2], ship4P1[2][2], ship3P1[2][2], ship2P1[2][2];
int hor, ver, sunk5P1, sunk4P1, sunk3P1, sunk2P1, max_score,turnCount,curr_score;
int sunk5P2, sunk4P2, sunk3P2, sunk2P2;
int ship5P2[2][2], ship4P2[2][2], ship3P2[2][2], ship2P2[2][2]; // it will store the ship pos

char menu();
int userPlaceP1();
int userPlaceP2();
int CompPlace();
int shipPlace(int Fpoint[][2], int Lpoint[][2], char CompBoard[9][9], int check_xy);
int checkShip(int Fpoint[][2], int Lpoint[][2], char CompBoard[9][9], int check_xy);
void saveGame();
void loadGame();
void saveScore();
void loadScore();
int sinksAndWin();
int compTurn();
int User_tryP1();
int User_tryP2();
int sinksAndUserWinP1();
int sinksAndUserWinP2();
int initializeBoard(char board[9][9]);
int outputBoard(char board[9][9]);

char menu()
{ // return num for continue and letter for normal
  // 1 for comp, 0 for 2player , p for 2player , c for comp
    int key;
    int press;
    char play, button, out;

    printf("\n \t\t\t\t\t\t \"BATTLESHIP\"");
    printf("\n\n Press Any Key...... ");
    getch();
    system("CLS");

MainMenu:
    printf("\n\n\n\n\n\t\t\t\t\t\t    1.Play\n");
    printf("\n \t\t\t\t\t\t2.Instructions\n");
    printf("\n \t\t\t\t\t\t    3.Exit\n");
    printf("\n (Press 1 For Play, 2 For Instructions, 3 For Exit The Game.): ");
    key = -1;
    scanf("%d", &key);
    if (key == 1)
    {
    SubMenu:
        system("CLS");
        printf("\n\t\t\t\t\t\t      Continue \n");
        printf("\n\t\t\t\t\t\t      New Game \n");
        printf("\n\t\t\t\t\t\t     High Score\n");
        printf("\n\t\t\t\t\t\t     Main Menu\n");

        printf("\n (Now Press 1 For Continue, 2 For New Game, 3 For High Score,and 4 To Go To Menu.): ");
        scanf("%d", &press);
        system("CLS");

        if (press == 1)
        {
            printf("\n\t\t\t\t\t 2 Players\n");
            printf("\n\t\t\t\t\t You vs Computer\n ");

            printf("\n  Press P To Play Two Players Mode And C To Play vs Computer or Press 1 If You Want To Go Back : ");
            press = getch();

            if (press == 1)
            {

                system("CLS");
                goto SubMenu;
            }
            
            if (press == 'P' || press == 'p')
            {
                system("CLS");
                return '0';
                // Game starts
            }
            else if (press == 'C' || press == 'c')
            {

                system("CLS");
                return '1';

                // Game Starts
            }
            else
            {
                printf("\n Please, Enter Right Key.");
                printf("\n Key: ");
                press = getch();
                system("CLS");
            }
            
        }

        else if (press == 2)
        {
            printf("\n\t\t\t\t\t 2 Players\n");
            printf("\n\t\t\t\t\t You vs Computer\n ");

            printf("\n  Press P To Play Two Players Mode And C To Play vs Computer or Press 1 If You Want To Go Back : ");
            press = getch();

            if (press == 1)
            {

                system("CLS");
                goto SubMenu;
            }
            
            if (press == 'P' || press == 'p')
            {
                system("CLS");
                return 'p';
                // Game starts
            }
            else if (press == 'C' || press == 'c')
            {

                system("CLS");
                return 'c';

                // Game Starts
            }
            else
            {
                printf("\n Please, Enter Right Key.");
                printf("\n Key: ");
                press = getch();
                system("CLS");
            }
        }
        else if (press == 3)
        {
            system("CLS");
            printf("\n Your Highest Score Is %d", max_score);
            printf("\n Press B To Go Back: ");
            scanf(" %c", &play);
            system("CLS");

            if (play == 'B' || play == 'b')
            {
                goto SubMenu;
            }
            
        }
        else if (press == 4)
        {
            goto MainMenu;
        }
        else
        {
            printf("\n Error!");
            printf("\n Please, Press right key....");
            getch();
            system("CLS");
            goto SubMenu;
        }
    }

    else if (key == 2)
    {
        system("CLS");
        printf("\n \t\t\t\t\t\t \'Instructions.\'");
        printf("\nSetting Up the Game:\nEach player takes a game board and places it in front of them.\n"
        "Players should not show their boards to each other.");
        printf("\n\nPlacing Your Fleet:\n");
        printf("Each player arranges their fleet of ships on their board. The fleet consists of:\n");
        printf("Destroyer(5 slots)\nTerminator(4 slots)\nExecutioner(3 slots)\nMammoth(2 slots)\n");
        printf("Ships can only be placed vertically or horizontally, not diagonally.");
        printf("\nTo place the ships, select the start and end point of a ship in such a way that it occupies the number of slots required by the ship.");
        printf("\n\nGameplay:");
        printf("\n Players take turns calling out coordinates to locate and sink the opponent's ships.");
        printf("\nCoordinates are a combination of a number (0-8) and a letter (A-I).");
        printf("\nFor example, 4B or 8H.");
        printf("\nThe ship is marked with \"H\"[HIT] if a ship is at that location or \"M\"[MISS] if it's an empty space.");
        printf("\nShips are marked \"S\" to indicate sunken ship");
        printf("\n\nWinning the Game:");
        printf("\nThe game continues until one player has successfully sunk all of the opponent's ships.");
        printf("\n\nHave fun and enjoy the strategic challenge of hunting down your opponent's fleet!\n");


        printf("\n Press B To Go Back: ");
        scanf(" %c", &play);

        if (play == 'B' || play == 'b')
        {
            system("CLS");
            goto MainMenu;
            system("CLS");
        }

        else
            ;
    }
    else if (key == 3)
    {
        printf("\n\t\t\t\t\t Are You Sure You Want To Exit The Game.");

        printf("\n Press Y For Yes And N For No: ");
        scanf(" %c", &out);

        if (out == 'Y' || out == 'y')
        {
            system("CLS");
        }
        else if (out == 'N' || out == 'n')
        {
            system("CLS");
            goto MainMenu;
            system("CLS");
        }
    }
    else
    {
        system("CLS");
        goto MainMenu;
    }
}

int userPlaceP1()
{
    int i, j, placed5, placed4, placed3, placed2, allPlaced, xchange, ychange, canPlace5, canPlace4, canPlace3, canPlace2;
    char Fpoint[1][2], Lpoint[1][2];
    placed2 = placed3 = placed4 = placed5 = allPlaced = xchange = ychange = 0;

    initializeBoard(boardP1);

    if (0)
    {
    ShipAlreadyThere:
        printf("\n");
        printf("\nThere is a ship already there");
        Sleep(1500);
    Invalid:
        system("CLS");
        printf("\nInvalid Input. Try Again\n");
    }

    outputBoard(boardP1);

    while (placed5 == 0)
    {
        canPlace5 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Destroyer! (5 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // 0,0 stores row 0-8 , 0,1 stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // 0,0 stores row 0-8 , 0,1 stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 4 || Fpoint[0][0] - Lpoint[0][0] == -4) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 4 || Fpoint[0][1] - Lpoint[0][1] == -4) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            {
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from charnum
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from charalpha
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {                                 /////////////////////////////////////////////
                        ship5P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P1[1][0] = Fpoint[0][0];
                        ship5P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 4; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P1[1][0] = Lpoint[0][0];
                        ship5P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 4; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            {
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P1[1][0] = Fpoint[0][0];
                        ship5P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 4; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P1[1][0] = Lpoint[0][0];
                        ship5P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 4; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace5)
            {
                placed5 = 1;
                printf("\nDestroyer placed!\n");
                outputBoard(boardP1);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed4 == 0)
    {
        canPlace4 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Terminator! (4 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 3 || Fpoint[0][0] - Lpoint[0][0] == -3) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 3 || Fpoint[0][1] - Lpoint[0][1] == -3) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P1[1][0] = Fpoint[0][0];
                        ship4P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 3; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P1[1][0] = Lpoint[0][0];
                        ship4P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 3; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P1[1][0] = Fpoint[0][0];
                        ship4P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 3; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P1[1][0] = Lpoint[0][0];
                        ship4P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 3; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace4)
            {
                placed4 = 1;
                printf("\nTerminator placed!\n");
                outputBoard(boardP1);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed3 == 0)
    {
        canPlace3 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Executioner! (3 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 2 || Fpoint[0][0] - Lpoint[0][0] == -2) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 2 || Fpoint[0][1] - Lpoint[0][1] == -2) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P1[1][0] = Fpoint[0][0];
                        ship3P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 2; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P1[1][0] = Lpoint[0][0];
                        ship3P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 2; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P1[1][0] = Fpoint[0][0];
                        ship3P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 2; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P1[1][0] = Lpoint[0][0];
                        ship3P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 2; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace3)
            {
                placed3 = 1;
                printf("\nExecutioner placed!\n");
                outputBoard(boardP1);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed2 == 0)
    {
        canPlace2 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Mammoth! (2 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 1 || Fpoint[0][0] - Lpoint[0][0] == -1) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 1 || Fpoint[0][1] - Lpoint[0][1] == -1) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P1[1][0] = Fpoint[0][0];
                        ship2P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 1; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP1[Fpoint[0][0]][i] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P1[1][0] = Lpoint[0][0];
                        ship2P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 1; i++)
                        {
                            boardP1[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P1[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P1[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P1[1][0] = Fpoint[0][0];
                        ship2P1[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 1; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP1[i][Fpoint[0][1]] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P1[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P1[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P1[1][0] = Lpoint[0][0];
                        ship2P1[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 1; i++)
                        {
                            boardP1[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace2)
            {
                placed2 = 1;
                printf("\nMammoth placed!\n");
                outputBoard(boardP1);
            }
        }
        else
        {
            goto Invalid;
        }
    }
    printf("All ships placed successfully!\n");
    Sleep(1500);
    system("CLS");
    allPlaced = 1;
    return allPlaced;
}
int userPlaceP2()
{
    int i, j, placed5, placed4, placed3, placed2, allPlaced, xchange, ychange, canPlace5, canPlace4, canPlace3, canPlace2;
    char Fpoint[1][2], Lpoint[1][2];
    placed2 = placed3 = placed4 = placed5 = allPlaced = xchange = ychange = 0;

    initializeBoard(boardP2);

    if (0)
    {
    ShipAlreadyThere:
        printf("\n");
        printf("\nThere is a ship already there");
        Sleep(1500);
    Invalid:
        system("CLS");
        printf("\nInvalid Input. Try Again\n");
    }

    outputBoard(boardP2);

    while (placed5 == 0)
    {
        canPlace5 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Destroyer! (5 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // 0,0 stores row 0-8 , 0,1 stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // 0,0 stores row 0-8 , 0,1 stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 4 || Fpoint[0][0] - Lpoint[0][0] == -4) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 4 || Fpoint[0][1] - Lpoint[0][1] == -4) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            {
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from charnum
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from charalpha
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {                                 /////////////////////////////////////////////
                        ship5P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P2[1][0] = Fpoint[0][0];
                        ship5P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 4; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P2[1][0] = Lpoint[0][0];
                        ship5P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 4; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            {
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P2[1][0] = Fpoint[0][0];
                        ship5P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 4; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace5 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace5)
                    {
                        ship5P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship5P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship5P2[1][0] = Lpoint[0][0];
                        ship5P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 4; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace5)
            {
                placed5 = 1;
                printf("\nDestroyer placed!\n");
                outputBoard(boardP2);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed4 == 0)
    {
        canPlace4 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Terminator! (4 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 3 || Fpoint[0][0] - Lpoint[0][0] == -3) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 3 || Fpoint[0][1] - Lpoint[0][1] == -3) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P2[1][0] = Fpoint[0][0];
                        ship4P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 3; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P2[1][0] = Lpoint[0][0];
                        ship4P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 3; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P2[1][0] = Fpoint[0][0];
                        ship4P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 3; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace4 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace4)
                    {
                        ship4P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship4P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship4P2[1][0] = Lpoint[0][0];
                        ship4P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 3; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace4)
            {
                placed4 = 1;
                printf("\nTerminator placed!\n");
                outputBoard(boardP2);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed3 == 0)
    {
        canPlace3 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Executioner! (3 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 2 || Fpoint[0][0] - Lpoint[0][0] == -2) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 2 || Fpoint[0][1] - Lpoint[0][1] == -2) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P2[1][0] = Fpoint[0][0];
                        ship3P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 2; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P2[1][0] = Lpoint[0][0];
                        ship3P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 2; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P2[1][0] = Fpoint[0][0];
                        ship3P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 2; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace3 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace3)
                    {
                        ship3P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship3P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship3P2[1][0] = Lpoint[0][0];
                        ship3P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 2; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace3)
            {
                placed3 = 1;
                printf("\nExecutioner placed!\n");
                outputBoard(boardP2);
            }
        }
        else
        {
            goto Invalid;
        }
    }

    while (placed2 == 0)
    {
        canPlace2 = 1;
        xchange = ychange = 0;
        printf("\n\nPlace the Mammoth! (2 slot ship)\nEnter row of first point(0-8) then column of first point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Fpoint[0][0] = getche();
        Fpoint[0][1] = getche();
        printf("\nEnter row of last point(0-8) then column of last point(A-I)"); // [0,0] stores row 0-8 , [0,1] stores column a-i
        Lpoint[0][0] = getche();
        Lpoint[0][1] = getche();

        Fpoint[0][1] = toupper(Fpoint[0][1]);
        Lpoint[0][1] = toupper(Lpoint[0][1]);
        if ((Fpoint[0][0] >= '0' && Fpoint[0][0] <= '8') && (Fpoint[0][1] >= 'A' && Fpoint[0][1] <= 'I') && (Lpoint[0][0] >= '0' && Lpoint[0][0] <= '8') && (Lpoint[0][1] >= 'A' && Lpoint[0][1] <= 'I')) // checks input is within array bounds
        {

            if ((Fpoint[0][0] - Lpoint[0][0] == 1 || Fpoint[0][0] - Lpoint[0][0] == -1) && (Fpoint[0][1] - Lpoint[0][1] == 0)) // checks how ship is being placed , horizontal or vertical
                ychange = 1;
            if ((Fpoint[0][1] - Lpoint[0][1] == 1 || Fpoint[0][1] - Lpoint[0][1] == -1) && (Fpoint[0][0] - Lpoint[0][0] == 0))
                xchange = 1;

            if ((xchange == 0 && ychange == 1) || (xchange == 1 && ychange == 0))
            { // checks that ship is not being placed diagonal
                system("CLS");
            }
            else
                goto Invalid;

            Fpoint[0][0] = Fpoint[0][0] - '0'; // convert to numbers from char to decimal num, ex : '0' is 48 in decimal
            Lpoint[0][0] = Lpoint[0][0] - '0';
            Fpoint[0][1] = Fpoint[0][1] - 'A'; // convert to numbers from char to decimal num, ex : 'A' is 65 in decimal
            Lpoint[0][1] = Lpoint[0][1] - 'A';
            if (xchange == 1 && ychange == 0)
            { // placing ship horizontal
                if (Fpoint[0][1] > Lpoint[0][1])
                {
                    for (i = Lpoint[0][1]; i <= Fpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P2[1][0] = Fpoint[0][0];
                        ship2P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][1]; i <= Lpoint[0][1] + 1; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
                if (Fpoint[0][1] < Lpoint[0][1])
                {
                    for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
                    {
                        if (boardP2[Fpoint[0][0]][i] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P2[1][0] = Lpoint[0][0];
                        ship2P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][1]; i <= Fpoint[0][1] + 1; i++)
                        {
                            boardP2[Fpoint[0][0]][i] = 'X';
                        }
                    }
                }
            }
            if (xchange == 0 && ychange == 1)
            { // placing ship vertical
                if (Fpoint[0][0] > Lpoint[0][0])
                {
                    for (i = Lpoint[0][0]; i <= Fpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P2[0][0] = Lpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P2[0][1] = Lpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P2[1][0] = Fpoint[0][0];
                        ship2P2[1][1] = Fpoint[0][1];
                        for (i = Lpoint[0][0]; i <= Lpoint[0][0] + 1; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
                if (Fpoint[0][0] < Lpoint[0][0])
                {
                    for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
                    {
                        if (boardP2[i][Fpoint[0][1]] != '+')
                        {
                            canPlace2 = 0;
                            goto ShipAlreadyThere;
                        }
                    }
                    if (canPlace2)
                    {
                        ship2P2[0][0] = Fpoint[0][0]; // starting point saved in 0th row and end point stored in 1th row
                        ship2P2[0][1] = Fpoint[0][1]; // rows in 1st column and columns in 2nd column
                        ship2P2[1][0] = Lpoint[0][0];
                        ship2P2[1][1] = Lpoint[0][1];
                        for (i = Fpoint[0][0]; i <= Fpoint[0][0] + 1; i++)
                        {
                            boardP2[i][Fpoint[0][1]] = 'X';
                        }
                    }
                }
            }
            if (canPlace2)
            {
                placed2 = 1;
                printf("\nMammoth placed!\n");
                outputBoard(boardP2);
            }
        }
        else
        {
            goto Invalid;
        }
    }
    printf("All ships placed successfully!\n");
    Sleep(1500);
    system("CLS");
    allPlaced = 1;
    return allPlaced;
}

int CompPlace()
{
    int i, j, x, y, temp, temp2, check_xy;
    int Fpoint[1][2], Lpoint[1][2], lower = 0, upper = 8;

    initializeBoard(boardP2);
    srand(time(0));
    // ship5 dimension5x5

    check_xy = rand() % 2;
    if (check_xy == 1)
    {                                                          // 1 means ship will be placed horizontally/x-axis
        Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
        Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
        Lpoint[0][0] = Fpoint[0][0]; // row is fixed,
        while ((Lpoint[0][1] - Fpoint[0][1] != 5) && (Lpoint[0][1] - Fpoint[0][1] != -5))
        { // column is changing
            Lpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
        }
        if (Lpoint[0][1] > Fpoint[0][1])
        {
        }
        else
        {
            temp = Lpoint[0][1];
            Lpoint[0][1] = Fpoint[0][1];
            Fpoint[0][1] = temp;
        }
    }
    else
    {
        Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
        Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
        Lpoint[0][1] = Fpoint[0][1]; // col is fixed,
        while ((Lpoint[0][0] - Fpoint[0][0] != 5) && (Lpoint[0][0] - Fpoint[0][0] != -5))
        { // column is changing
            Lpoint[0][0] = (rand() % (upper - lower + 1)) + lower;
        }
        if (Lpoint[0][0] > Fpoint[0][0])
        {
        }
        else
        {
            temp = Lpoint[0][0];
            Lpoint[0][0] = Fpoint[0][0];
            Fpoint[0][0] = temp;
        }
    }
    ship5P2[0][0] = Fpoint[0][0]; // coordinates of f point in 0,0 and 0,1
    ship5P2[0][1] = Fpoint[0][1];
    ship5P2[1][0] = Lpoint[0][0]; // coordinates of l point in 1,0 and 1,1
    ship5P2[1][1] = Lpoint[0][1];
    if (check_xy == 1)
    {
        ship5P2[1][1]--;
    }
    else
    {
        ship5P2[1][0]--;
    }

    shipPlace(Fpoint, Lpoint, boardP2, check_xy);

    // ship4 dimension4x4
    Sleep(1000);
    check_xy = rand() % 2;
    temp2 = 0;
    if (check_xy == 1)
    { // 1 means ship will be placed horizontally/x-axis
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][0] = Fpoint[0][0]; // row is fixed,
            while ((Lpoint[0][1] - Fpoint[0][1] != 4) && (Lpoint[0][1] - Fpoint[0][1] != -4))
            { // column is changing
                Lpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            }
            if (Lpoint[0][1] > Fpoint[0][1])
            {
            }
            else
            {
                temp = Lpoint[0][1];
                Lpoint[0][1] = Fpoint[0][1];
                Fpoint[0][1] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }
    else
    {
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][1] = Fpoint[0][1]; // col is fixed,
            while ((Lpoint[0][0] - Fpoint[0][0] != 4) && (Lpoint[0][0] - Fpoint[0][0] != -4))
            { // column is changing
                Lpoint[0][0] = (rand() % (upper - lower + 1)) + lower;
            }

            if (Lpoint[0][0] > Fpoint[0][0])
            {
            }
            else
            {
                temp = Lpoint[0][0];
                Lpoint[0][0] = Fpoint[0][0];
                Fpoint[0][0] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }

    ship4P2[0][0] = Fpoint[0][0]; // coordinates of f point in 0,0 and 0,1
    ship4P2[0][1] = Fpoint[0][1];
    ship4P2[1][0] = Lpoint[0][0]; // coordinates of l point in 1,0 and 1,1
    ship4P2[1][1] = Lpoint[0][1];
    if (check_xy == 1)
    {
        ship4P2[1][1]--;
    }
    else
    {
        ship4P2[1][0]--;
    }
    shipPlace(Fpoint, Lpoint, boardP2, check_xy);

    // ship3x3
    Sleep(1000);
    check_xy = rand() % 2;
    temp2 = 0;
    if (check_xy == 1)
    { // 1 means ship will be placed horizontally/x-axis
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][0] = Fpoint[0][0]; // row is fixed,
            while ((Lpoint[0][1] - Fpoint[0][1] != 3) && (Lpoint[0][1] - Fpoint[0][1] != -3))
            { // column is changing
                Lpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            }
            if (Lpoint[0][1] > Fpoint[0][1])
            {
            }
            else
            {
                temp = Lpoint[0][1];
                Lpoint[0][1] = Fpoint[0][1];
                Fpoint[0][1] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }
    else
    {
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][1] = Fpoint[0][1]; // col is fixed,
            while ((Lpoint[0][0] - Fpoint[0][0] != 3) && (Lpoint[0][0] - Fpoint[0][0] != -3))
            { // column is changing
                Lpoint[0][0] = (rand() % (upper - lower + 1)) + lower;
            }
            if (Lpoint[0][0] > Fpoint[0][0])
            {
            }
            else
            {
                temp = Lpoint[0][0];
                Lpoint[0][0] = Fpoint[0][0];
                Fpoint[0][0] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }

    ship3P2[0][0] = Fpoint[0][0]; // coordinates of f point in 0,0 and 0,1
    ship3P2[0][1] = Fpoint[0][1];
    ship3P2[1][0] = Lpoint[0][0]; // coordinates of l point in 1,0 and 1,1
    ship3P2[1][1] = Lpoint[0][1];
    if (check_xy == 1)
    {
        ship3P2[1][1]--;
    }
    else
    {
        ship3P2[1][0]--;
    }

    shipPlace(Fpoint, Lpoint, boardP2, check_xy);

    // ship2x2
    Sleep(1000);
    check_xy = rand() % 2;
    temp2 = 0;
    if (check_xy == 1)
    { // 1 means ship will be placed horizontally/x-axis
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][0] = Fpoint[0][0]; // row is fixed,
            while ((Lpoint[0][1] - Fpoint[0][1] != 2) && (Lpoint[0][1] - Fpoint[0][1] != -2))
            { // column is changing
                Lpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            }
            if (Lpoint[0][1] > Fpoint[0][1])
            {
            }
            else
            {
                temp = Lpoint[0][1];
                Lpoint[0][1] = Fpoint[0][1];
                Fpoint[0][1] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }
    else
    {
        while (temp2 == 0)
        {

            Fpoint[0][0] = (rand() % (upper - lower + 1)) + lower; // 0,0 stores row no. and 0,1 stores column no of the point
            Fpoint[0][1] = (rand() % (upper - lower + 1)) + lower;
            Lpoint[0][1] = Fpoint[0][1]; // col is fixed,
            while ((Lpoint[0][0] - Fpoint[0][0] != 2) && (Lpoint[0][0] - Fpoint[0][0] != -2))
            { // column is changing
                Lpoint[0][0] = (rand() % (upper - lower + 1)) + lower;
            }
            if (Lpoint[0][0] > Fpoint[0][0])
            {
            }
            else
            {
                temp = Lpoint[0][0];
                Lpoint[0][0] = Fpoint[0][0];
                Fpoint[0][0] = temp;
            }
            temp2 = checkShip(Fpoint, Lpoint, boardP2, check_xy);
        }
    }

    ship2P2[0][0] = Fpoint[0][0]; // coordinates of f point in 0,0 and 0,1
    ship2P2[0][1] = Fpoint[0][1];
    ship2P2[1][0] = Lpoint[0][0]; // coordinates of l point in 1,0 and 1,1
    ship2P2[1][1] = Lpoint[0][1];
    if (check_xy == 1)
    {
        ship2P2[1][1]--;
    }
    else
    {
        ship2P2[1][0]--;
    }

    shipPlace(Fpoint, Lpoint, boardP2, check_xy);
}

int shipPlace(int Fpoint[][2], int Lpoint[][2], char CompBoard[9][9], int check_xy)
{
    int i, j;
    if (check_xy == 1)
    {
        for (i = Fpoint[0][1]; i != Lpoint[0][1]; i++)
        {
            CompBoard[Fpoint[0][0]][i] = 'X';
        }
    }
    else
    {
        for (i = Fpoint[0][0]; i != Lpoint[0][0]; i++)
        {
            CompBoard[i][Fpoint[0][1]] = 'X';
        }
    }
}
int checkShip(int Fpoint[][2], int Lpoint[][2], char CompBoard[9][9], int check_xy)
{
    int i, j;
    if (check_xy == 1)
    {
        for (i = Fpoint[0][1]; i <= Lpoint[0][1]; i++)
        {
            if (CompBoard[Fpoint[0][0]][i] == 'X')
            {
                return 0;
            }
            else
            {
            }
        }
        return 1;
    }
    else
    {
        for (i = Fpoint[0][0]; i <= Lpoint[0][0]; i++)
        {
            if (CompBoard[i][Fpoint[0][1]] == 'X')
            {
                return 0;
            }
            else
            {
            }
        }
        return 1;
    }
}

void saveGame()
{
    FILE *file = fopen("game_data.dat", "wb");

    if (file != NULL)
    {

        fwrite(boardP1, sizeof(boardP1[0][0]), sizeof(boardP1) / sizeof(boardP1[0][0]), file);
        fwrite(boardP2, sizeof(boardP2[0][0]), sizeof(boardP2) / sizeof(boardP2[0][0]), file);
        fwrite(turnBoardP1, sizeof(turnBoardP1[0][0]), sizeof(turnBoardP1) / sizeof(turnBoardP1[0][0]), file);
        fwrite(turnBoardP2, sizeof(turnBoardP2[0][0]), sizeof(turnBoardP2) / sizeof(turnBoardP2[0][0]), file);

        fwrite(ship5P1, sizeof(ship5P1), 1, file);
        fwrite(ship4P1, sizeof(ship4P1), 1, file);
        fwrite(ship3P1, sizeof(ship3P1), 1, file);
        fwrite(ship2P1, sizeof(ship2P1), 1, file);

        fwrite(&hor, sizeof(hor), 1, file);
        fwrite(&ver, sizeof(ver), 1, file);
        fwrite(&sunk5P1, sizeof(sunk5P1), 1, file);
        fwrite(&sunk4P1, sizeof(sunk4P1), 1, file);
        fwrite(&sunk3P1, sizeof(sunk3P1), 1, file);
        fwrite(&sunk2P1, sizeof(sunk2P1), 1, file);
        fwrite(&sunk5P2, sizeof(sunk5P2), 1, file);
        fwrite(&sunk4P2, sizeof(sunk4P2), 1, file);
        fwrite(&sunk3P2, sizeof(sunk3P2), 1, file);
        fwrite(&sunk2P2, sizeof(sunk2P2), 1, file);

        fwrite(ship5P2, sizeof(ship5P2), 1, file);
        fwrite(ship4P2, sizeof(ship4P2), 1, file);
        fwrite(ship3P2, sizeof(ship3P2), 1, file);
        fwrite(ship2P2, sizeof(ship2P2), 1, file);

        fclose(file);
    }
    else
    {
        printf("Error opening file for writing.\n");
    }
}

void loadGame()
{
    FILE *file = fopen("game_data.dat", "rb");

    if (file != NULL)
    {

        fread(boardP1, sizeof(boardP1[0][0]), sizeof(boardP1) / sizeof(boardP1[0][0]), file);
        fread(boardP2, sizeof(boardP2[0][0]), sizeof(boardP2) / sizeof(boardP2[0][0]), file);
        fread(turnBoardP1, sizeof(turnBoardP1[0][0]), sizeof(turnBoardP1) / sizeof(turnBoardP1[0][0]), file);
        fread(turnBoardP2, sizeof(turnBoardP2[0][0]), sizeof(turnBoardP2) / sizeof(turnBoardP2[0][0]), file);

        fread(ship5P1, sizeof(ship5P1), 1, file);
        fread(ship4P1, sizeof(ship4P1), 1, file);
        fread(ship3P1, sizeof(ship3P1), 1, file);
        fread(ship2P1, sizeof(ship2P1), 1, file);

        fread(&hor, sizeof(hor), 1, file);
        fread(&ver, sizeof(ver), 1, file);
        fread(&sunk5P1, sizeof(sunk5P1), 1, file);
        fread(&sunk4P1, sizeof(sunk4P1), 1, file);
        fread(&sunk3P1, sizeof(sunk3P1), 1, file);
        fread(&sunk2P1, sizeof(sunk2P1), 1, file);
        fread(&sunk5P2, sizeof(sunk5P2), 1, file);
        fread(&sunk4P2, sizeof(sunk4P2), 1, file);
        fread(&sunk3P2, sizeof(sunk3P2), 1, file);
        fread(&sunk2P2, sizeof(sunk2P2), 1, file);

        fread(ship5P2, sizeof(ship5P2), 1, file);
        fread(ship4P2, sizeof(ship4P2), 1, file);
        fread(ship3P2, sizeof(ship3P2), 1, file);
        fread(ship2P2, sizeof(ship2P2), 1, file);

        fclose(file);
    }
    else
    {
        printf("Error opening file for reading.\n");
    }
}
void saveScore(){
    FILE *file = fopen("game_score.dat", "wb");

    if (file != NULL)
    {

        fwrite(&max_score, sizeof(max_score), 1, file);

        fclose(file);
    }
    else
    {
        printf("Error opening file for writing.\n");
    }
}
void loadScore(){
     FILE *file = fopen("game_score.dat", "rb");

    if (file != NULL)
    {
        fread(&max_score, sizeof(max_score), 1, file);

        fclose(file);
    }
    
}
int sinksAndWin()
{

    int i, j, sinking, allSink;

    if (ship5P1[1][0] - ship5P1[0][0] == 0 && sunk5P1 != 1)
    { // horizontally placed ship5
        sinking = 1;
        for (i = ship5P1[0][1]; i <= ship5P1[1][1]; i++)
        {
            if (turnBoardP2[ship5P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P1 = 1;
            hor = ver = 1;
            for (i = ship5P1[0][1]; i <= ship5P1[1][1]; i++)
            {
                turnBoardP2[ship5P1[1][0]][i] = 'S';
                boardP1[ship5P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship4P1[1][0] - ship4P1[0][0] == 0 && sunk4P1 != 1)
    { // horizontally placed ship4
        sinking = 1;
        for (i = ship4P1[0][1]; i <= ship4P1[1][1]; i++)
        {
            if (turnBoardP2[ship4P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P1 = 1;
            hor = ver = 1;
            for (i = ship4P1[0][1]; i <= ship4P1[1][1]; i++)
            {
                turnBoardP2[ship4P1[1][0]][i] = 'S';
                boardP1[ship4P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship3P1[1][0] - ship3P1[0][0] == 0 && sunk3P1 != 1)
    { // horizontally placed ship3
        sinking = 1;
        for (i = ship3P1[0][1]; i <= ship3P1[1][1]; i++)
        {
            if (turnBoardP2[ship3P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P1 = 1;
            hor = ver = 1;
            for (i = ship3P1[0][1]; i <= ship3P1[1][1]; i++)
            {
                turnBoardP2[ship3P1[1][0]][i] = 'S';
                boardP1[ship3P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship2P1[1][0] - ship2P1[0][0] == 0 && sunk2P1 != 1)
    { // horizontally placed ship2
        sinking = 1;
        for (i = ship2P1[0][1]; i <= ship2P1[1][1]; i++)
        {
            if (turnBoardP2[ship2P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P1 = 1;
            hor = ver = 1;
            for (i = ship2P1[0][1]; i <= ship2P1[1][1]; i++)
            {
                turnBoardP2[ship2P1[1][0]][i] = 'S';
                boardP1[ship2P1[1][0]][i] = 'S';
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    if (ship5P1[1][1] - ship5P1[0][1] == 0 && sunk5P1 != 1)
    { // vertically placed ship5
        sinking = 1;
        for (i = ship5P1[0][0]; i <= ship5P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship5P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P1 = 1;
            hor = ver = 1;
            for (i = ship5P1[0][0]; i <= ship5P1[1][0]; i++)
            {
                turnBoardP2[i][ship5P1[1][1]] = 'S';
                boardP1[i][ship5P1[1][1]] = 'S';
            }
        }
    }
    if (ship4P1[1][1] - ship4P1[0][1] == 0 && sunk4P1 != 1)
    { // vertically placed ship4
        sinking = 1;
        for (i = ship4P1[0][0]; i <= ship4P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship4P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P1 = 1;
            hor = ver = 1;
            for (i = ship4P1[0][0]; i <= ship4P1[1][0]; i++)
            {
                turnBoardP2[i][ship4P1[1][1]] = 'S';
                boardP1[i][ship4P1[1][1]] = 'S';
            }
        }
    }
    if (ship3P1[1][1] - ship3P1[0][1] == 0 && sunk3P1 != 1)
    { // vertically placed ship3
        sinking = 1;
        for (i = ship3P1[0][0]; i <= ship3P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship3P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P1 = 1;
            hor = ver = 1;
            for (i = ship3P1[0][0]; i <= ship3P1[1][0]; i++)
            {
                turnBoardP2[i][ship3P1[1][1]] = 'S';
                boardP1[i][ship3P1[1][1]] = 'S';
            }
        }
    }
    if (ship2P1[1][1] - ship2P1[0][1] == 0 && sunk2P1 != 1)
    { // vertically placed ship2
        sinking = 1;
        for (i = ship2P1[0][0]; i <= ship2P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship2P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P1 = 1;
            hor = ver = 1;
            for (i = ship2P1[0][0]; i <= ship2P1[1][0]; i++)
            {
                turnBoardP2[i][ship2P1[1][1]] = 'S';
                boardP1[i][ship2P1[1][1]] = 'S';
            }
        }
    }

    if (sunk2P1 && sunk3P1 && sunk4P1 && sunk5P1)
    {
        return 1;
    }
    else
        return 0;
}

int compTurn()
{

    char origin[2] = {-1, -1}; // 1st stores row , 2nd stores column
    int i, j, randomR, randomC, row, col;
    // hor = ver = 1; initialized by sinkAndWin function after ship sinks

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (boardP1[i][j] == 'H')
            {
                origin[0] = i;
                origin[1] = j;
            }
        }
    }
    if (origin[0] == -1)
    {
        srand(time(0));
        do
        {
            randomR = (rand() % 9);
            randomC = (rand() % 9);
        } while (turnBoardP2[randomR][randomC] != '+');
        printf("\nThe computer shoots the the point : %d%c", randomR, randomC + 'A');
        if (boardP1[randomR][randomC] == 'X')
        {
            boardP1[randomR][randomC] = 'H';
            turnBoardP2[randomR][randomC] = 'H';
            printf("\nIt is a HIT!");
            return 0;
        }
        if (boardP1[randomR][randomC] == '+')
        {
            boardP1[randomR][randomC] = 'M';
            turnBoardP2[randomR][randomC] = 'M';
            printf("\nIt is a MISS!");
            return 0;
        }
    }
    else
    {
        if (hor == 1)
        {
            row = origin[0];
            col = origin[1];

            while (turnBoardP2[row][col] == 'H' && col < 8) // going right
            {
                col++;
            }
            if (col != origin[1])
            {
                if (turnBoardP2[row][col] == '+')
                {
                    printf("\nThe computer shoots the the point : %d%c", row, col + 'A');
                    if (boardP1[row][col] == 'X')
                    {
                        boardP1[row][col] = 'H';
                        turnBoardP2[row][col] = 'H';
                        printf("\nIt is a HIT!");
                        return 0;
                    }
                    if (boardP1[row][col] == '+')
                    {
                        boardP1[row][col] = 'M';
                        turnBoardP2[row][col] = 'M';
                        printf("\nIt is a MISS!");
                        return 0;
                    }
                }
            }
            if (turnBoardP2[row][col] == 'M' || col == origin[1]) // going left
            {
                row = origin[0];
                col = origin[1];

                while (turnBoardP2[row][col] == 'H' && col > 0)
                {
                    col--;
                }
                if (col != origin[1])
                {
                    if (turnBoardP2[row][col] == '+')
                    {
                        printf("\nThe computer shoots the the point : %d%c", row, col + 'A');
                        if (boardP1[row][col] == 'X')
                        {
                            boardP1[row][col] = 'H';
                            turnBoardP2[row][col] = 'H';
                            printf("\nIt is a HIT!");
                            return 0;
                        }
                        if (boardP1[row][col] == '+')
                        {
                            boardP1[row][col] = 'M';
                            turnBoardP2[row][col] = 'M';
                            printf("\nIt is a MISS!");
                            return 0;
                        }
                    }
                }
            }

            hor = 0;
        }
        if (ver == 1)
        {
            row = origin[0];
            col = origin[1];

            while (turnBoardP2[row][col] == 'H' && row < 8) // going down
            {
                row++;
            }
            if (row != origin[0])
            {
                if (turnBoardP2[row][col] == '+')
                {
                    printf("\nThe computer shoots the the point : %d%c", row, col + 'A');
                    if (boardP1[row][col] == 'X')
                    {
                        boardP1[row][col] = 'H';
                        turnBoardP2[row][col] = 'H';
                        printf("\nIt is a HIT!");
                        return 0;
                    }
                    if (boardP1[row][col] == '+')
                    {
                        boardP1[row][col] = 'M';
                        turnBoardP2[row][col] = 'M';
                        printf("\nIt is a MISS!");
                        return 0;
                    }
                }
            }
            if (turnBoardP2[row][col] == 'M' || row == origin[0]) // going up
            {
                row = origin[0];
                col = origin[1];

                while (turnBoardP2[row][col] == 'H' && row > 0)
                {
                    row--;
                }
                if (row != origin[0])
                {
                    if (turnBoardP2[row][col] == '+')
                    {
                        printf("\nThe computer shoots the the point : %d%c", row, col + 'A');
                        if (boardP1[row][col] == 'X')
                        {
                            boardP1[row][col] = 'H';
                            turnBoardP2[row][col] = 'H';
                            printf("\nIt is a HIT!");
                            return 0;
                        }
                        if (boardP1[row][col] == '+')
                        {
                            boardP1[row][col] = 'M';
                            turnBoardP2[row][col] = 'M';
                            printf("\nIt is a MISS!");
                            return 0;
                        }
                    }
                }
            }

            ver = 0;
        }
    }
}

int User_tryP1()
{
    char x, y;
    int temp = 0;

    // outputBoard();
    printf("\nIt's user 1 turn,choose from 0-8 for row and a-i:");
startagain:
    x = getche();
    printf("-");
    y = getche();
    if (x < '0' || x > '8')
    {
        goto invalid1;
    }
    else
    {
    }
    if (y < 'a' || y > 'i')
    {
        goto invalid2;
    }
    int temp1 = x - '0';
    int temp2 = y - 'a';
    if (boardP2[temp1][temp2] == 'X')
    {
        printf("\nIt's a Hit\n");
        boardP2[temp1][temp2] = 'H';
        turnBoardP1[temp1][temp2] = 'H';
    }
    else if (boardP2[temp1][temp2] == 'H')
    {
        printf("\nIt's a Miss\n");
    }
    else if (boardP2[temp1][temp2] == 'S')
    {
        printf("\nIt's a Miss\n");
    }

    else
    {
        boardP2[temp1][temp2] = 'M';
        turnBoardP1[temp1][temp2] = 'M';
        printf("\nIt's a Miss\n");
    }
    if(turnCount<15){
        curr_score = 0;
    }
    else{
        curr_score = 10000 - ((turnCount-14)*244);
    }

    if (0)
    {

    invalid1:
    {
        printf("\ninvalid row try again:");
        goto startagain;
    }
    invalid2:
    {
        printf("\nInvalid column please try again:");
        goto startagain;
    }
    }
}
int User_tryP2()
{
    char x, y;

    int temp = 0;

    // outputBoard();
    printf("\nIt's user 2 turn,choose from 0-8 for row and a-i:");
startagain:
    x = getche();
    printf("-");
    y = getche();
    if (x < '0' || x > '8')
    {
        goto invalid1;
    }
    else
    {
    }
    if (y < 'a' || y > 'i')
    {
        goto invalid2;
    }
    int temp1 = x - '0';
    int temp2 = y - 'a';
    if (boardP1[temp1][temp2] == 'X')
    {
        printf("\nIt's a Hit\n");
        boardP1[temp1][temp2] = 'H';
        turnBoardP2[temp1][temp2] = 'H';
    }
    else if (boardP1[temp1][temp2] == 'H')
    {
        printf("\nIt's a Miss\n");
    }
    else if (boardP1[temp1][temp2] == 'S')
    {
        printf("\nIt's a Miss\n");
    }

    else
    {
        boardP1[temp1][temp2] = 'M';
        turnBoardP2[temp1][temp2] = 'M';
        printf("\nIt's a Miss\n");
    }

    if (0)
    {

    invalid1:
    {
        printf("\ninvalid row try again:");
        goto startagain;
    }
    invalid2:
    {
        printf("\nInvalid column please try again:");
        goto startagain;
    }
    }
}

int sinksAndUserWinP1()
{
    int i, j, sinking, allSink;

    if (ship5P2[1][0] - ship5P2[0][0] == 0 && sunk5P2 != 1)
    { // horizontally placed ship5
        sinking = 1;
        for (i = ship5P2[0][1]; i <= ship5P2[1][1]; i++)
        {
            if (turnBoardP1[ship5P2[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P2 = 1;
            for (i = ship5P2[0][1]; i <= ship5P2[1][1]; i++)
            {
                boardP2[ship5P2[1][0]][i] = 'S';
                turnBoardP1[ship5P2[1][0]][i] = 'S';
            }
        }
    }
    if (ship4P2[1][0] - ship4P2[0][0] == 0 && sunk4P2 != 1)
    { // horizontally placed ship4
        sinking = 1;
        for (i = ship4P2[0][1]; i <= ship4P2[1][1]; i++)
        {
            if (turnBoardP1[ship4P2[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P2 = 1;
            for (i = ship4P2[0][1]; i <= ship4P2[1][1]; i++)
            {
                boardP2[ship4P2[1][0]][i] = 'S';
                turnBoardP1[ship4P2[1][0]][i] = 'S';
            }
        }
    }
    if (ship3P2[1][0] - ship3P2[0][0] == 0 && sunk3P2 != 1)
    { // horizontally placed ship3
        sinking = 1;
        for (i = ship3P2[0][1]; i <= ship3P2[1][1]; i++)
        {
            if (turnBoardP1[ship3P2[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P2 = 1;
            for (i = ship3P2[0][1]; i <= ship3P2[1][1]; i++)
            {
                boardP2[ship3P2[1][0]][i] = 'S';
                turnBoardP1[ship3P2[1][0]][i] = 'S';
            }
        }
    }
    if (ship2P2[1][0] - ship2P2[0][0] == 0 && sunk2P2 != 1)
    { // horizontally placed ship2
        sinking = 1;
        for (i = ship2P2[0][1]; i <= ship2P2[1][1]; i++)
        {
            if (turnBoardP1[ship2P2[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P2 = 1;
            for (i = ship2P2[0][1]; i <= ship2P2[1][1]; i++)
            {
                boardP2[ship2P2[1][0]][i] = 'S';
                turnBoardP1[ship2P2[1][0]][i] = 'S';
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    if (ship5P2[1][1] - ship5P2[0][1] == 0 && sunk5P2 != 1)
    { // vertically placed ship5
        sinking = 1;
        for (i = ship5P2[0][0]; i <= ship5P2[1][0]; i++)
        {
            if (turnBoardP1[i][ship5P2[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P2 = 1;
            for (i = ship5P2[0][0]; i <= ship5P2[1][0]; i++)
            {
                boardP2[i][ship5P2[1][1]] = 'S';
                turnBoardP1[i][ship5P2[1][1]] = 'S';
            }
        }
    }
    if (ship4P2[1][1] - ship4P2[0][1] == 0 && sunk4P2 != 1)
    { // vertically placed ship4
        sinking = 1;
        for (i = ship4P2[0][0]; i <= ship4P2[1][0]; i++)
        {
            if (turnBoardP1[i][ship4P2[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P2 = 1;
            for (i = ship4P2[0][0]; i <= ship4P2[1][0]; i++)
            {
                boardP2[i][ship4P2[1][1]] = 'S';
                turnBoardP1[i][ship4P2[1][1]] = 'S';
            }
        }
    }
    if (ship3P2[1][1] - ship3P2[0][1] == 0 && sunk3P2 != 1)
    { // vertically placed ship3
        sinking = 1;
        for (i = ship3P2[0][0]; i <= ship3P2[1][0]; i++)
        {
            if (turnBoardP1[i][ship3P2[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P2 = 1;
            for (i = ship3P2[0][0]; i <= ship3P2[1][0]; i++)
            {
                boardP2[i][ship3P2[1][1]] = 'S';
                turnBoardP1[i][ship3P2[1][1]] = 'S';
            }
        }
    }
    if (ship2P2[1][1] - ship2P2[0][1] == 0 && sunk2P2 != 1)
    { // vertically placed ship2
        sinking = 1;
        for (i = ship2P2[0][0]; i <= ship2P2[1][0]; i++)
        {
            if (turnBoardP1[i][ship2P2[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P2 = 1;
            for (i = ship2P2[0][0]; i <= ship2P2[1][0]; i++)
            {
                boardP2[i][ship2P2[1][1]] = 'S';
                turnBoardP1[i][ship2P2[1][1]] = 'S';
            }
        }
    }

    if (sunk2P2 && sunk3P2 && sunk4P2 && sunk5P2)
    {
        return 1;
    }
    else
        return 0;
}

int sinksAndUserWinP2()
{
    int i, j, sinking, allSink;

    if (ship5P1[1][0] - ship5P1[0][0] == 0 && sunk5P1 != 1)
    { // horizontally placed ship5
        sinking = 1;
        for (i = ship5P1[0][1]; i <= ship5P1[1][1]; i++)
        {
            if (turnBoardP2[ship5P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P1 = 1;
            for (i = ship5P1[0][1]; i <= ship5P1[1][1]; i++)
            {
                boardP1[ship5P1[1][0]][i] = 'S';
                turnBoardP2[ship5P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship4P1[1][0] - ship4P1[0][0] == 0 && sunk4P1 != 1)
    { // horizontally placed ship4
        sinking = 1;
        for (i = ship4P1[0][1]; i <= ship4P1[1][1]; i++)
        {
            if (turnBoardP2[ship4P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P1 = 1;
            for (i = ship4P1[0][1]; i <= ship4P1[1][1]; i++)
            {
                boardP1[ship4P1[1][0]][i] = 'S';
                turnBoardP2[ship4P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship3P1[1][0] - ship3P1[0][0] == 0 && sunk3P1 != 1)
    { // horizontally placed ship3
        sinking = 1;
        for (i = ship3P1[0][1]; i <= ship3P1[1][1]; i++)
        {
            if (turnBoardP2[ship3P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P1 = 1;
            for (i = ship3P1[0][1]; i <= ship3P1[1][1]; i++)
            {
                boardP1[ship3P1[1][0]][i] = 'S';
                turnBoardP2[ship3P1[1][0]][i] = 'S';
            }
        }
    }
    if (ship2P1[1][0] - ship2P1[0][0] == 0 && sunk2P1 != 1)
    { // horizontally placed ship2
        sinking = 1;
        for (i = ship2P1[0][1]; i <= ship2P1[1][1]; i++)
        {
            if (turnBoardP2[ship2P1[1][0]][i] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P1 = 1;
            for (i = ship2P1[0][1]; i <= ship2P1[1][1]; i++)
            {
                boardP1[ship2P1[1][0]][i] = 'S';
                turnBoardP2[ship2P1[1][0]][i] = 'S';
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    if (ship5P1[1][1] - ship5P1[0][1] == 0 && sunk5P1 != 1)
    { // vertically placed ship5
        sinking = 1;
        for (i = ship5P1[0][0]; i <= ship5P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship5P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nDESTROYER SUNK!!!\n");
            sunk5P1 = 1;
            for (i = ship5P1[0][0]; i <= ship5P1[1][0]; i++)
            {
                boardP1[i][ship5P1[1][1]] = 'S';
                turnBoardP2[i][ship5P1[1][1]] = 'S';
            }
        }
    }
    if (ship4P1[1][1] - ship4P1[0][1] == 0 && sunk4P1 != 1)
    { // vertically placed ship4
        sinking = 1;
        for (i = ship4P1[0][0]; i <= ship4P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship4P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nTERMINATOR SUNK!!!\n");
            sunk4P1 = 1;
            for (i = ship4P1[0][0]; i <= ship4P1[1][0]; i++)
            {
                boardP1[i][ship4P1[1][1]] = 'S';
                turnBoardP2[i][ship4P1[1][1]] = 'S';
            }
        }
    }
    if (ship3P1[1][1] - ship3P1[0][1] == 0 && sunk3P1 != 1)
    { // vertically placed ship3
        sinking = 1;
        for (i = ship3P1[0][0]; i <= ship3P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship3P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nEXECUTIONER SUNK!!!\n");
            sunk3P1 = 1;
            for (i = ship3P1[0][0]; i <= ship3P1[1][0]; i++)
            {
                boardP1[i][ship3P1[1][1]] = 'S';
                turnBoardP2[i][ship3P1[1][1]] = 'S';
            }
        }
    }
    if (ship2P1[1][1] - ship2P1[0][1] == 0 && sunk2P1 != 1)
    { // vertically placed ship2
        sinking = 1;
        for (i = ship2P1[0][0]; i <= ship2P1[1][0]; i++)
        {
            if (turnBoardP2[i][ship2P1[1][1]] != 'H')
            {
                sinking = 0;
            }
        }
        if (sinking)
        {
            printf("\nMAMMOTH SUNK!!!\n");
            sunk2P1 = 1;
            for (i = ship2P1[0][0]; i <= ship2P1[1][0]; i++)
            {
                boardP1[i][ship2P1[1][1]] = 'S';
                turnBoardP2[i][ship2P1[1][1]] = 'S';
            }
        }
    }

    if (sunk2P1 && sunk3P1 && sunk4P1 && sunk5P1)
    {
        return 1;
    }
    else
        return 0;
}

int initializeBoard(char board[9][9])
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            board[i][j] = '+';
        }
    }
}

int outputBoard(char board[9][9])
{
    int i, j;
    printf("    a   b   c   d   e   f   g   h   i   \n\n");
    for (i = 0; i < 9; i++)
    {
        printf("%d   ", i);
        for (j = 0; j < 9; j++)
        {
            printf("%c   ", board[i][j]);
        }
        printf("\n\n");
    }
    return 1;
}
int main()
{
    loadScore();
    int win1 = 0;
    int win2 = 0;
    int count = 0;
    int i, j;
    char exit;
    hor = ver = 1;
    sunk5P1 = sunk4P1 = sunk3P1 = sunk2P1 = 0;
    sunk5P2 = sunk4P2 = sunk3P2 = sunk2P2 = 0;
    turnCount = 0;
    char option;
    system("CLS");
    option = menu();

    if (option == 'c')
    {
        initializeBoard(turnBoardP1);
        initializeBoard(turnBoardP2);
        userPlaceP1();
        CompPlace();

        do
        {
            system("CLS");
            printf("\n\t Computer's Board\n");
            outputBoard(turnBoardP1);
            printf("-------------------------------------\n\n");
            printf("\n\t  Your Board\n");
            outputBoard(boardP1);
            User_tryP1();
            win1 = sinksAndUserWinP1();
            compTurn();
            win2 = sinksAndWin();
            turnCount++;
            printf("\n\nPress any key to continue.......or press s to save the game and exit");
            exit = getch();
        } while (!win2 && !win1 && exit != 'S' && exit != 's');
        if (exit == 'S' || exit == 's')
        {
            saveGame();
            return 0;
        }
    }

    if (option == '1')
    {
        loadGame();
        win1 = sinksAndUserWinP1();
        win2 = sinksAndWin();
        if (!win1 && !win2)
        {
            do
            {
                system("CLS");
                printf("\n\t Computer's Board\n");
                outputBoard(turnBoardP1);
                printf("-------------------------------------\n\n");
                printf("\n\t  Your Board\n");
                outputBoard(boardP1);
                User_tryP1();
                win1 = sinksAndUserWinP1();
                compTurn();
                win2 = sinksAndWin();
                turnCount++;
                printf("\n\nPress any key to continue.......or press s to save the game and exit");
                exit = getch();
            } while (!win2 && !win1 && exit != 'S' && exit != 's');
            if (exit == 'S' || exit == 's')
            {
                saveGame();
                return 0;
            }
        }
    }
    if (option == '1' || option == 'c')
    {
        if (win2)
            printf("\n\nYOU LOST :(\nTHE COMPUTER SUNK ALL YOUR SHIPS\n\n\t\tBETTER LUCK NEXT TIME!");
        else if (win1)
            printf("\n\nYOU WON!!!\nYOU SUNK ALL THE SHIPS\n\n\t\tGREAT JOB!");

            printf("\n\t\tYour score was = %d",curr_score);
            if(max_score < curr_score){
            max_score = curr_score;
    }
            saveScore();
    }

    if (option == 'p')
    {
        initializeBoard(turnBoardP1);
        initializeBoard(turnBoardP2);
        printf("\nPlayer 1, Place your fleet!\n\n");
        userPlaceP1();
        printf("\nPlayer 2, Place your fleet!\n\n");
        userPlaceP2();

        do
        {
            system("CLS");
            printf("\n\t Player 2 Board\n");
            outputBoard(turnBoardP1);
            printf("-------------------------------------\n\n");
            printf("\n\t  Player 1 Board\n");
            outputBoard(turnBoardP2);
            User_tryP1();
            win1 = sinksAndUserWinP1();
            User_tryP2();
            win2 = sinksAndUserWinP2();
            printf("\n\nPress any key to continue.......or press s to save the game and exit");
            exit = getch();
        } while (!win2 && !win1 && exit != 'S' && exit != 's');
        if (exit == 'S' || exit == 's')
        {
            saveGame();
            return 0;
        }
    }

    if (option == '0')
    {
        loadGame();
        win1 = sinksAndUserWinP1();
        win2 = sinksAndUserWinP2();
        if (!win1 && !win2)
        {
            do
        {
            system("CLS");
            printf("\n\t Player 2 Board\n");
            outputBoard(turnBoardP1);
            printf("-------------------------------------\n\n");
            printf("\n\t  Player 1 Board\n");
            outputBoard(turnBoardP2);
            User_tryP1();
            win1 = sinksAndUserWinP1();
            User_tryP2();
            win2 = sinksAndUserWinP2();
            printf("\n\nPress any key to continue.......or press s to save the game and exit");
            exit = getch();
        } while (!win2 && !win1 && exit != 'S' && exit != 's');
            if (exit == 'S' || exit == 's')
            {
                saveGame();
                return 0;
            }
        }
    }
    if (option == '0' || option == 'p')
    {
        if (win2)
            printf("\n\nPlayer 2 WON!!!\nYOU SUNK ALL THE SHIPS\n\n\t\tGREAT JOB!");
        else if (win1)
            printf("\n\nPlayer 1 WON!!!\nYOU SUNK ALL THE SHIPS\n\n\t\tGREAT JOB!");
    }
}
