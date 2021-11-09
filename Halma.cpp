#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


char firstColor[10] = "blue";
char secondColor[10] = "green";
int BoardLen, LCV;


void color(int textColor, int backColor = 0) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}


int basicValidMoveCkech(int a[][50], int i1, int j1, int i2, int j2) {
    if (a[i2 * 2 - 1][j2 * 2 - 1] == 1 || a[i2 * 2 - 1][j2 * 2 - 1] == 2) {
        return(1);     //appropriate move
    }
}


struct player {
    char user[20];     //username
    char password[20];
    //c stands for count;
    int draw_c;
    int win_c;
    int lose_c;
    int game_c;
    char last_game[400];     //saved position of last game in string in case the user decides to continue later(we used sttruct to find each user's game easily )
}players[100], best, worst;


int surrondedBead(int a[][50], int BoardLen) {
    int i, j, x, y, sw = 0;
    int count = 0;
    for (i = 0; i < BoardLen; i++) {
        for (j = 0; j < BoardLen; j++) {
            if (a[i][j] == 1) {     // to check a 5x5 sqaure around our each bead.
                for (x = i - 4; x <= i + 4; x = x + 2) {
                    for (y = j - 4; y <= j + 4; y = y + 2) {
                        if (a[x][y] == 2) {
                            count++;
                            if (count == 24) {
                                sw = 1;
                            }
                        }
                    }
                }
            }
            else if (a[i][j] == 2) {
                for (x = i - 4; x <= i + 4; x = x + 2) {
                    for (y = j - 4; y <= j + 4; y = y + 2) {
                        if (a[x][y] == 2) {
                            count++;
                            if (count == 24) {
                                sw = 2;
                            }
                        }
                    }
                }
            }
        }
    }

    if (sw == 1) {
        printf(" player2 won the game ! ");
        return (1);
    }
    else if (sw == 2) {
        printf(" player1 won the game ! ");
        return (2);
    }
}


void findingbestandworst(struct player best, struct player worst)     //saving best and worst players
{
    int i;
    for (i = 0; i < 100; i++) {
        if (players[i].win_c > best.win_c) {
            strcpy(best.user, players[i].user);
            best.win_c = players[i].win_c;
        }
        else
            if (players[i].win_c == best.win_c)     //if 2 players won equal number of games the one with more draws is the best
            {
                if (players[i].draw_c > best.draw_c) {
                    strcpy(best.user, players[i].user);
                    best.draw_c = players[i].draw_c;
                }
                else
                    if (players[i].draw_c == best.draw_c) {     //between 2 players with equal draws and wins the one with smaller number of loses is the best
                        if (players[i].lose_c < best.lose_c) {
                            strcpy(best.user, players[i].user);
                            best.lose_c = players[i].lose_c;
                        }
                    }
            }
            else
                if (players[i].lose_c > worst.lose_c) {
                    strcpy(worst.user, players[i].user);
                    worst.lose_c = players[i].win_c;
                }
                else if (players[i].lose_c == best.lose_c)     //if 2 players lost equal number of games the one with less draws is the worst
                {
                    if (players[i].draw_c < best.draw_c) {
                        strcpy(worst.user, players[i].user);
                        worst.draw_c = players[i].draw_c;
                    }
                    else
                        if (players[i].draw_c == best.draw_c) {     //between 2 players with equal draws and loses the one with smaller number of wins is the worst
                            if (players[i].win_c < best.win_c) {
                                strcpy(worst.user, players[i].user);
                                best.win_c = players[i].win_c;
                            }
                        }
                }
    }
}


int strstr2(const char str1[], const char str2[]) {
    int i, j;

    for (i = 0; str1[i]; i++)
        if (str1[i] == str2[0]) {
            for (j = 1; str2[j] && str1[i + j] == str2[j]; j++);
            if (!str2[j]) return(0);
        }
    return(-1);
}


int abs(int i);


int harkat(int a[][50], int i1, int j1, int i2, int j2) {
    int i, j, sw = 0;
    i1 = i1 * 2 - 1;     //these functions used to match player inputs with our array
    i2 = i2 * 2 - 1;
    j1 = j1 * 2 - 1;
    j2 = j2 * 2 - 1;
    if (a[i2][j2] == 0)     //barrasi ghanooni boodan jaye maghsad
    {
        //      8 jahate mojaz
        // if (i1+2 == i2 && j1+2==j2)
        // sw = 1;
        // if (i1-2 == i2 && j1-2==j2)
        // sw = 1;
        // if (i1 == i2 && j1+2==j2)
        // sw = 1;
        // if (i1+2 == i2 && j1==j2)
        // sw = 1;
        // if (i1 == i2 && j1-2==j2)
        // sw = 1;
        // if (i1-2 == i2 && j1==j2)
        // sw = 1;
        // if (i1+2 == i2 && j1-2==j2)
        // sw = 1;
        // if (i1-2 == i2 && j1+2==j2)
        // sw = 1;
        // Barrasi boodan maghsad dar 8 jahat mojaz.

        for (i = i1 - 2; i <= i1 + 2; i = i + 2)
            for (j = j1 - 2; j <= j1 + 2; j = j + 2)
            {
                if (i == i2 && j == j2)
                    sw = 1;
            }

        if (sw == 1)     //move is ok.
        {
            int TEMP = a[i1][j1];
            a[i1][j1] = 0;
            a[i2][j2] = TEMP;
            printf("Moved");
            printf("\n");
            return (1);
        }
        else
        {
            return (0);
        }
    }
    else
    {
        return (0);
    }
}


int change_turn(int turn, int* lcv) {
    if (turn == 1) {
        turn = 2;
    }
    else {
        turn = 1;
    }
    (*lcv)++;     //counting moves for leavecamp value.
    return(turn);
}


int  jump(int board[][50], int i1, int j1, int i2, int j2) {
    int sw = 0;
    int j;
    //these functions are used to match player inputs with our array.
    i1 = i1 * 2 - 1;
    i2 = i2 * 2 - 1;
    j1 = j1 * 2 - 1;
    j2 = j2 * 2 - 1;

    //the first if is for dimension.
    if ((board[(i1 + i2) / 2][(j1 + j2) / 2] == 1 || board[(i1 + i2) / 2][(j1 + j2) / 2] == 2) && board[i2][j2] == 0 && abs(i2 - i1) == 4 && abs(j2 - j1) == 4) {
        //check if there is any peice to jump over.                        //check if the distance is ok.

        sw = 1;
    }

    //the second if is for rows.
    if ((board[(i1 + i2) / 2][(j1 + j2) / 2] == 1 || board[(i1 + i2) / 2][(j1 + j2) / 2] == 2) && board[i2][j2] == 0 && (abs(i2 - i1) == 4 && (j2 == j1))) {
        //check if there is any peice to jump over.                        //check if the distance is ok.

        sw = 1;
    }

    //the third if is for columns.
    if ((board[(i1 + i2) / 2][(j1 + j2) / 2] == 1 || board[(i1 + i2) / 2][(j1 + j2) / 2] == 2) && board[i2][j2] == 0 && (abs(j2 - j1) == 4 && (i2 == i1))) {
        //check if there is any peice to jump over.                        //check if the distance is ok.

        sw = 1;
    }

    if (sw == 1)     //move is ok.
    {
        int TEMP = board[i1][j1];
        board[i1][j1] = 0;
        board[i2][j2] = TEMP;
        printf("WHAT A great JUMP !\n");
        printf("\n");
        return(1);
    }
}


int  superjump(int board[][50], int i1, int j1, int i2, int j2) {
    int j, i, sw = 0;

    //SUPER JUMP CHECK FOR ROWS!

    int count = 0;
    if (((i1 * 2 - 1 == i2 * 2 - 1) && ((board[i2 * 2 - 1][j1 + j2 - 1] == 1) || (board[i2 * 2 - 1][j1 + j2 - 1] == 2)))) {
        if (j2 > j1) {     //right to left superjump.
            for (j = j1 * 2 - 1 + 2; j < j2 * 2 - 2; j++) {     //check if there is just one bead between starting point and distination or not.
                if (board[i1 * 2 - 1][j] == 1 || board[i1 * 2 - 1][j] == 2) {
                    count++;
                }
            }

            if (count == 1) {     //if we had one bead and all of the previous rules were established , then superjump is allowed !
                sw = 1;     //to check the position of our movement.
            }
        }
        else {     //left to right superjump.
            for (j = j1 * 2 - 1 - 2; j > j2 * 2 - 1 + 2; j--) {
                if (board[i1 * 2 - 1][j] == 1 || board[i1 * 2 - 1][j] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
    }

    //SUPER JUMP CHECK FOR COLUMNS!
    //just like the previous part , but for COLUMNS

    count = 0;
    if ((((j1 * 2 - 1 == j2 * 2 - 1) && ((board[i1 + i2 - 1][j2 * 2 - 1] == 1) || (board[i1 + i2 - 1][j2 * 2 - 1] == 2))))) {
        if (i2 > i1) {
            for (i = i1 * 2 - 1 + 2; i < i2 * 2 - 2; i++) {
                if (board[i][j1 * 2 - 1] == 1 || board[i][j1 * 2 - 1] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
        else {
            for (i = i1 * 2 - 1 - 2; i > i2 * 2 + 2; i--) {
                if (board[i][j1 * 2 - 1] == 1 || board[i][j1 * 2 - 1] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
    }
    //SUPER JUMP CHECK FOR Diameter!
    // just like the previous part , but for Diameter!

    count = 0;
    if ((i2 - i1 == j2 - j1) && ((board[i2 + i1 - 1][j2 + j1 - 1] == 1) || (board[i2 + i1 - 1][j2 + j1 - 1] == 2))) {
        if (i2 > i1) {
            for (i = i1 * 2 - 1 + 2, j = j1 * 2 - 1 + 2; i < i2 * 2 - 1, j < j2 * 2 - 1; j++, i++) {
                if (board[i][j] == 1 || board[i][j] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
        else {
            for (i = i1 * 2 - 1 - 2, j = j1 * 2 - 1 - 2; i > i2 * 2 - 1, j > j2 * 2 - 1; j--, i--) {
                if (board[i][j] == 1 || board[i][j] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
    }

    count = 0;
    if ((abs(i2 - i1) == abs(j2 - j1)) && ((board[i2 + i1 - 1][j2 + j1 - 1] == 1) || (board[i2 + i1 - 1][j2 + j1 - 1] == 2))) {
        if (i1<i2 && j1>j2) {
            for (i = i1 * 2 - 1, j = j1 * 2 + 1 - 2; i<i2 * 2 - 1, j>j2 * 2 - 1; j--, i++) {
                if (board[i][j] == 1 || board[i][j] == 2) {
                    count++;
                }
            }
            if (count == 1 || count == 2) {
                sw = 1;
            }
        }
        else if (i1 > i2 && j1 < j2) {
            for (i = i2 * 2 - 1 + 2, j = j2 * 2 - 1; i > i1 * 2 - 1, j < j1 * 2 - 1; j++, i--) {
                printf("%d", board[i][j]);
                if (board[i][j] == 1 || board[i][j] == 2) {
                    count++;
                }
            }
            if (count == 1) {
                sw = 1;
            }
        }
    }
    if (sw == 1) {
        int TEMP = board[i1 * 2 - 1][j1 * 2 - 1];
        board[i1 * 2 - 1][j1 * 2 - 1] = 0;
        board[i2 * 2 - 1][j2 * 2 - 1] = TEMP;
        printf("WHAT A SUPERJUMP !");
        printf("\n");
        return (1);
    }
    else
        printf("wrong move! \n ");
    return (0);
}


void showboard(int board[][50], int LEN) {

    //---------Game Board Print
    //---the  number :3 for row
    //---the number:4 for column
    //---the number:1 for player1's beads
    //---the number:2 for player2's beads

    int row = 0;
    int column = 0;
    if (strcmp(firstColor, "green") == 0) {
        for (row = 0; row < LEN; row++) {
            for (column = 0; column < LEN; column++) {
                if (board[row][column] == 3)
                    printf("-");
                if (board[row][column] == 4)
                    printf("|");
                if (board[row][column] == 0)
                    printf(" ");
                if (board[row][column] == 1) {
                    color(2, 0);
                    printf("O");
                    color(15, 0);
                }
                if (board[row][column] == 2) {
                    color(1, 0);
                    printf("O");
                    color(15, 0);
                }
            }
            printf("\n");
        }
    }
    else if (strcmp(firstColor, "blue") == 0) {
        for (row = 0; row < LEN; row++) {
            for (column = 0; column < LEN; column++) {
                if (board[row][column] == 3)
                    printf("-");
                if (board[row][column] == 4)
                    printf("|");
                if (board[row][column] == 0)
                    printf(" ");
                if (board[row][column] == 1) {
                    color(1, 0);
                    printf("O");
                    color(15, 0);
                }
                if (board[row][column] == 2) {
                    color(2, 0);
                    printf("O");
                    color(15, 0);
                }
            }
            printf("\n");
        }
    }
}


void initial_board(int board[][50], int boardlen, int i) {
    int row, column, k, j;

    //board

    for (row = 0; row < boardlen; row++) {
        for (column = 0; column < boardlen; column++) {
            if (row % 2 == 0) {
                board[row][column] = 3;
            }
            else if (column % 2 == 0) {
                board[row][column] = 4;
            }
        }
    }

    //beads
    //i is the biggest number in order of peices

    i++;

    //some mathematical equation to order an i*i triangle
    for (k = 1; k < 2 * i; k += 2) {
        for (j = 1; j <= 2 * i - k; j += 2) {
            board[k][j] = 1;
        }
    }
    //deleting 2 peices to make the suitable order for peices
    board[1][2 * i - 1] = 0;
    board[2 * i - 1][1] = 0;

    //some mathematical equation to order an i*i triangle
    int count = i;
    for (k = boardlen - 1; k >= (boardlen - 1 - (2 * i)) + 2; k -= 2) {
        for (j = boardlen - 1; j >= (boardlen - 1 - (2 * count) + 2); j -= 2) {
            board[k][j] = 2;
        }
        count--;
    }

    //deleting 2 peices to make the suitable order for peices
    board[boardlen - 1][((boardlen - 1 - (2 * i))) + 2] = 0;
    board[(boardlen - 1 - (2 * i)) + 2][boardlen - 1] = 0;
}


//this function is written for LEAVE CAMP VALUE
int  leave_camp_value(int board[][50], int i, int boardlen) {
    int limitP1;
    int limitP2;
    int sw = 0;
    int k, j;

    //same codes for initial board to check if there is any piece in camps

    i++;

    for (k = 1; k < 2 * i && sw == 0; k += 2) {
        for (j = 1; j <= 2 * i - k && sw == 0; j += 2) {
            if (board[k][j] == 1) {
                limitP1 = 1;
                sw = 1;     //this function prevents wasting time
                if ((k == 1 && j != 2 * i - 1) || (k == 2 * i - 1 && j == 1)) {
                    limitP1 = 0;
                    sw = 0;     //these are the pieces in triangle(int the initial board) that we deleted for suitable order
                }
            }
        }
    }

    //same codes for initial board to check if there is any piece in camps

    sw = 0;
    int count = i;

    for (k = boardlen - 1; k >= (boardlen - 1 - (2 * i)) + 2 && sw == 0; k -= 2) {
        for (j = boardlen - 1; j >= (boardlen - 1 - (2 * count) + 2) && sw == 0; j -= 2) {
            if (board[k][j] == 2) {
                limitP2 = 1;
                sw = 1;     //this function prevents wasting time
                if ((j == boardlen - 1 && k == (boardlen - 1 - (2 * i)) + 2) || (j == (boardlen - 1 - (2 * i)) + 2 && k == boardlen - 1)) {//---these are the pieces in triangle(int the initial board) that we deleted for suitable order
                    limitP2 = 0;
                    sw = 0;
                }
            }
        }
        count--;
    }

    if ((limitP1 == 1) && (limitP2 != 1)) {
        printf("player 2 is the winner!");
        return (2);
    }
    else if ((limitP2 == 1) && (limitP1 != 1)) {
        printf("player 1 is the winner!");
        return (1);
    }
    else if ((limitP1 == 1) && (limitP2 == 1)) {
        printf("it is a draw!");
        return (12);
    }
    else
        return (0);
}


int win(int board[][50], int i, int boardlen) {
    //checking camps to see if there is any camp full of opponent peices with codes in initial board

    int sw = 0;
    int k, j;
    i++;

    for (k = 1; k < 2 * i && sw == 0; k += 2) {
        for (j = 1; j <= 2 * i - k && sw == 0; j += 2) {
            if (board[k][j] != 2) {
                sw = 1;
                if ((k == 1 && j == 2 * i - 1) || (k == 2 * i - 1 && j == 1)) {//---these are the pieces in triangle(int the initial board) that we deleted for suitable order
                    sw = 0;
                }
            }
        }
    }
    if (sw == 0) {
        printf("What an awsome game ! Player2 won!");
        return(2);
    }
    else {
        sw = 0;
        int count = i;
        for (k = boardlen - 1; k >= (boardlen - 1 - (2 * i)) + 2 && sw == 0; k -= 2) {
            for (j = boardlen - 1; j >= (boardlen - 1 - (2 * count) + 2) && sw == 0; j -= 2) {
                if (board[k][j] != 1) {
                    sw = 1;
                    if ((k == boardlen - 1 && j == (boardlen - 1 - (2 * i)) + 2) || (k == (boardlen - 1 - (2 * i)) + 2 && j == boardlen - 1)) {//---these are the pieces in triangle(int the initial board) that we deleted for suitable order
                        sw = 0;
                    }
                }
            }
            count--;
        }
        if (sw == 0) {
            printf("What an awsome game ! player1 won!");
            return(1);
        }
        else if (sw == 1)
            return(0);
    }
}


//saving position to check if the result is draw and save it in case user wants to continue later
void save_position(int board[][50], int boardlen, char string[]) {
    int k = 0;
    int i, j;
    for (i = 1; i < boardlen; i += 2) {
        for (j = 1; j < boardlen; j += 2) {
            string[k] = board[i][j] + '0';
            k++;
        }
    }
}

// int special_draw(int board[][50], char string[][3], int Boardlen) {
// char c;
// shift up the string to save last position
// strcpy(string[1], string[2]);
// strcpy(string[2], string[3]);
// save_position(board, Boardlen, string[3]);
// last functions used to save 3 last position of the game to compare
// next functions are going to compare 3 last positions
// if (strcmp(string[1], string[2]) == 0) {
//    if (strstr(string[2], string[3]) == 0) {
//      printf("are you willing to offer draw?");
//    scanf("%d", &c);
//  if (c == 'y' || c == 'Y') {
//    printf("do you accept the draw suggestion?");
//                if (c == 'y' || c == 'Y') {
//                    printf("good game!result is draw :)");
//                    return (1);
//                }
//            }
//            else return (0);
//        }
//    }
//    else
//        return (0);
//}


void setting(int* boardlen, int* beadsnum, int* LCV) {
    //Reading the File
    //we need these informations in all parts of game so we should call inputs by reference and use pointer

    FILE* inputFile;
    inputFile = fopen("Config.txt", "rt");
    int iF, jF;

    char Char[5], Char2[5], x[5], temp;
    int  playerNum = 2;
    *boardlen = 10; *LCV = 40, * beadsnum = 3;
    char toSave1[10], toSave2[10], toSave3[10], toSave4[50];

    fscanf(inputFile, "%s", Char);
    strcpy(x, Char);

    while (strstr2(toSave1, "}") != 0) {
        fscanf(inputFile, "%s = ", toSave1);
        if (strstr2(toSave1, "Size") == 0) {
            fscanf(inputFile, "%d", &iF);
            *boardlen = iF;
        }
        if (strstr2(toSave1, "First_Color") == 0) {
            fscanf(inputFile, "%s", toSave2);
            strcpy(firstColor, toSave2);
        }
        if (strstr2(toSave1, "Second_Color") == 0) {
            fscanf(inputFile, "%s", toSave3);
            strcpy(secondColor, toSave3);
        }
        if (strstr2(toSave1, "leave_camp_value") == 0) {
            fscanf(inputFile, "%d", &jF);
            *LCV = jF;
        }
        if (strstr2(toSave1, "Beads_order") == 0) {
            fgets(toSave4, 50, inputFile);
            *beadsnum = toSave4[strlen(toSave4) - 4] - '0';
        }
    }
}


int gamewithccamputer(struct player players[], int playernum, int currentplayer) {
    char saving_string[100][3];     //this string saves last 3 positions
    int turn = 1;
    int BoardLen, beadsnum, LCV;
    int i1, j1, i2, j2;
    int board[50][50] = {};
    int row, column;
    int lcv = 0;     //counting moves for leave camp value.

    //reading from file
    setting(&BoardLen, &beadsnum, &lcv);
    BoardLen *= 2;

    //beads
    initial_board(board, BoardLen, beadsnum);
    showboard(board, BoardLen);
    while (1) {
        if (turn != playernum) {

            //choosing random valid bead

            int num, num2, i, j, count = 0;
            int sw2 = 0;

            srand(time(NULL));

            num = ((rand() % (((beadsnum * (beadsnum + 1)) / 2) + beadsnum - 1))) + 1;
            for (i = 1; i < BoardLen; i++) {
                if (sw2 == 1) break;
                for (j = 1; j < BoardLen && sw2 == 0; j++) {
                    if (board[i * 2 - 1][j * 2 - 1] == 1) {
                        count++;
                        if (count == num) {
                            sw2 = 1;
                        }
                    }
                }
            }

            i1 = i - 1;
            j1 = j - 1;

            sw2 = 0, count = 0;

            for (i = 1; i < BoardLen && sw2 == 0; i++) {
                for (j = 1; j < BoardLen && sw2 == 0; j++) {
                    if (harkat(board, i1, j1, i, j) == 1) {
                        turn = change_turn(turn, &lcv);
                        showboard(board, BoardLen);
                        sw2 = 1;
                    }
                    else if (jump(board, i1, j1, i, j) == 1 && basicValidMoveCkech(board, i1, j1, i, j) != 1) {
                        turn = change_turn(turn, &lcv);
                        showboard(board, BoardLen);
                        sw2 = 1;
                    }
                }
            }
            if (win(board, beadsnum, BoardLen) == playernum)
            {
                players[currentplayer].win_c++;
                return 0;
            }
            else
                if (win(board, beadsnum, BoardLen) != 0)//someone won but its not our user so the user lost the game
                {
                    players[currentplayer].lose_c++;
                    return 0;
                }
            if (lcv % 2 == 1)     //lcv counts movements and we want to check special draw once in 2 movements
            {
                // if (special_draw(board,saving_string,BoardLen)==1) {
                // players[currentplayer].draw_c++;
                // return 0;}
            }
        }

        // receiving the coordinates
        printf("Please enter place of the bead and destination\n");
        scanf("%d", &i1);

        if (i1 == -1) {
            printf(" Wish you had a good game ! do you wanna save the game or not ?  press y for yes and n for no");
            char e;
            if (e == 'n' || e == 'N') {
                return 0;
            }
            //else if (e == y || e == Y) {
           // save_position(board, BoardLen, saving_string);
           // strcpy(players[currentplayer].last_game, saving_string);
           //}
        }

        scanf("%d", &j1);
        scanf("%d %d", &i2, &j2);

        if ((board[i1 * 2 - 1][j1 * 2 - 1] != 1 && board[i1 * 2 - 1][j1 * 2 - 1] != 2) || (board[i2 * 2 - 1][j2 * 2 - 1] == 1 || board[i2 * 2 - 1][j2 * 2 - 1] == 2)) {
            printf("WRONG MOVE , IMPOSSIBLE! \n");
            continue;
        }

        //CHECkING TURN
        if (turn == 1) {
            if ((board[i1 * 2 - 1][j1 * 2 - 1] == 2)) {
                printf("THAT'S NOT YOUR TURN!\n");
                continue;
            }
        }
        else if (turn == 2) {
            if ((board[i1 * 2 - 1][j1 * 2 - 1] == 1)) {
                printf("THAT'S NOT YOUR TURN!\n");
                continue;
            }
        }
        if (harkat(board, i1, j1, i2, j2) == 1)     //check if the inputs are not for jump and we can change turn
        {
            showboard(board, BoardLen);
            turn = change_turn(turn, &lcv);
            if (lcv > LCV) {
                leave_camp_value(board, beadsnum, BoardLen);
                if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                    return 0;
            }
            if (win(board, beadsnum, BoardLen) != 0)
                return 0;
            else
                continue;
        }

        //if the inputs are for jump and we may have several consecutive jumps
        else if (jump(board, i1, j1, i2, j2) == 1) {
            while (1) {
                jump(board, i1, j1, i2, j2);
                showboard(board, BoardLen);
                printf("Do you want to continue to jump ? (y for yes N for no) \n");
                char C;
                scanf(" %c", &C);;
                if (C != 'y' && C != 'Y')     //check if player quits jumping
                {
                    turn = change_turn(turn, &lcv);
                    if (lcv > LCV) {
                        leave_camp_value(board, beadsnum, BoardLen);
                        if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                            return 0;
                    }

                    if (win(board, beadsnum, BoardLen) != 0)
                        return 0;
                    else
                        break;
                }
                else {
                    i1 = i2;
                    j1 = j2;
                    printf("what is yor next destination \n");
                    scanf("%d %d", &i2, &j2);
                    continue;
                }
            }
        }

        else if (superjump(board, i1, j1, i2, j2) == 1) {//check if the inputs are for superjump and we can change turn

            showboard(board, BoardLen);
            turn = change_turn(turn, &lcv);

            if (lcv > LCV) {
                leave_camp_value(board, beadsnum, BoardLen);
                if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                    return 0;
            }
            if (win(board, beadsnum, BoardLen) != 0) {
                printf("wrong move! \n");
                return 0;
            }
            else
                continue;
        }
        if (win(board, beadsnum, BoardLen) == playernum) {
            players[currentplayer].win_c++;
            return 0;
        }
        else
            if (win(board, beadsnum, BoardLen) != 0) {
                //someone won but its not our user so the user lost the game

                players[currentplayer].lose_c++;
                return 0;
            }

        if (lcv % 2 == 1) {
            // lcv counts movements and we want to check special draw once in 2 movements
            // if (special_draw(board,saving_string,BoardLen)==1)
            // {players[currentplayer].draw_c++;
            // return 0;
            //}
        }
        else
            continue;
    }
}


int gamewithanotherplayer(struct player players[], int playernum, int currentplayer) {
    char saving_string[100][3];     //this string saves last 3 positions
    int turn = 1;
    int BoardLen, beadsnum, LCV;
    int i1, j1, i2, j2;
    int board[50][50] = {};
    int row, column;
    int lcv = 0;     //counting moves for leave camp value

    //reading from file
    setting(&BoardLen, &beadsnum, &lcv);
    BoardLen *= 2;

    //beads
    initial_board(board, BoardLen, beadsnum);
    showboard(board, BoardLen);
    while (1) {
        //receiving the coordinates
        printf("Please enter place of the bead and destination\n");
        scanf("%d", &i1);

        if (i1 == -1) {
            printf(" Wish you had a good game ! do you wanna save the game or not ?  press y for yes and n for no");
            char e;
            if (e == 'n' || e == 'N') {
                return 0;
            }
            // else if( e == y || e== Y ){
            // save_position(board,BoardLen,saving_string);
            // strcpy(players[currentplayer].last_game,saving_string);  
            // }
        }

        scanf("%d", &j1);
        scanf("%d %d", &i2, &j2);

        // checking simple valid moves' conditions.
        if ((board[i1 * 2 - 1][j1 * 2 - 1] != 1 && board[i1 * 2 - 1][j1 * 2 - 1] != 2) || (board[i2 * 2 - 1][j2 * 2 - 1] == 1 || board[i2 * 2 - 1][j2 * 2 - 1] == 2)) {
            printf("WRONG MOVE , IMPOSSIBLE! \n");
            continue;
        }

        //checking turns
        if (turn == 1) {
            if ((board[i1 * 2 - 1][j1 * 2 - 1] == 2)) {
                printf("THAT'S NOT YOUR TURN!\n");
                continue;
            }
        }
        else if (turn == 2) {
            if ((board[i1 * 2 - 1][j1 * 2 - 1] == 1)) {
                printf("THAT'S NOT YOUR TURN!\n");
                continue;
            }
        }

        if (harkat(board, i1, j1, i2, j2) == 1) {
            //check if the inputs are not for jump and we can change turn.

            showboard(board, BoardLen);
            turn = change_turn(turn, &lcv);
            if (lcv > LCV) {
                leave_camp_value(board, beadsnum, BoardLen);
                if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                    return 0;
            }
            if (win(board, beadsnum, BoardLen) != 0)
                return 0;
            else
                continue;
        }

        //if the inputs are for jump and we may have several consecutive jumps
        else if (jump(board, i1, j1, i2, j2) == 1) {
            while (1) {
                jump(board, i1, j1, i2, j2);
                showboard(board, BoardLen);
                printf("Do you want to continue to jump ? (y for yes N for no) \n");
                char C;
                scanf(" %c", &C);;
                if (C != 'y' && C != 'Y')//check if player quits jumping
                {
                    turn = change_turn(turn, &lcv);
                    if (lcv > LCV) {
                        leave_camp_value(board, beadsnum, BoardLen);
                        if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                            return 0;
                    }
                    if (win(board, beadsnum, BoardLen) != 0)
                        return 0;
                    else
                        break;
                }
                else {
                    i1 = i2;
                    j1 = j2;
                    printf("what is yor next destination \n");
                    scanf("%d %d", &i2, &j2);
                    continue;
                }
            }
        }
        else if (superjump(board, i1, j1, i2, j2) == 1) {
            //check if the inputs are for superjump and we can change turn

            showboard(board, BoardLen);
            turn = change_turn(turn, &lcv);
            if (lcv > LCV) {
                leave_camp_value(board, beadsnum, BoardLen);
                if (leave_camp_value(board, beadsnum, BoardLen) != 0)
                    return 0;
            }
            if (win(board, beadsnum, BoardLen) != 0) {
                printf("wrong move! \n");
                return 0;
            }
            else
                continue;
        }
        if (win(board, beadsnum, BoardLen) == playernum)
        {
            players[currentplayer].win_c++;
            return 0;
        }
        else
            if (win(board, beadsnum, BoardLen) != 0)//someone won but its not our user so the user lost the game
            {
                players[currentplayer].lose_c++;
                return 0;
            }
        if (lcv % 2 == 1) {
            //lcv counts movements and we want to check special draw once in 2 movements
         //   if (special_draw(board, saving_string, BoardLen) == 1)
           // {
             //   players[currentplayer].draw_c++;
               // return 0;
            // }
        }
        else
            continue;
    }
}


void systemlogin(int* currentplayer) {
    //using many  while(1) to skip goto prohibitions

    char ch;
    char temp[20], temppass[20];
    char tmp;
    FILE* usersfile;
    int playerscount = 0;
    int k = 0, i;     //counting the place of char in password
    int swlogin = 0;     //to continue after player logged in out of while ring?!

    findingbestandworst(best, worst);

    printf("__________________________________________________________________________________________________\n\n");
    printf("----------------------------------  WELCOME TO HALMA GAME ! -------------------------------------- \n");
    printf("__________________________________________________________________________________________________\n\n\n");
    printf("Do you wanna sign up or sign in ? ( u for signup,i for sign in ) \n");

    while (1) {
        scanf("%c", &ch);
        if (ch == 'u' || ch == 'U') {
            printf("What is your recommended username? \n");
            while (1) {
                scanf("%s", temp);
                int i;
                for (i = 0; i <= playerscount; i++) {
                    if (strcmp(players[i].user, temp) == 0)     //check for similar username
                    {
                        printf("This username has been taken ! please try another username \n");
                        continue;
                    }
                    else {
                        strcpy(players[playerscount].user, temp);
                    }
                }
                printf("please enter your recommended password \n");
                k = 0;
                do
                {
                    tmp = getch();

                    if (tmp != 13) {
                        printf("X");
                        players[playerscount].password[k] = tmp;
                        k++;
                    }
                    if (tmp == '\b')
                    {
                        printf("\b");
                        players[playerscount].password[k] = '\0';
                        k--;
                    }
                } while (tmp != 13);

                players[playerscount].password[k] = '\0';
                printf("\n");
                printf("Signed up successfully ! \n");
                printf("Do you wanna sign up or sign in ? ( u for signup,i for sign in ) \n");
                playerscount++;     //one player added to the total player count
                break;
            }
        }

        else if (ch == 'i' || ch == 'I') {
            printf("Please enter your username ! \n");
            while (1) {
                int usw = 0;     //having sw prevents wasting time
                scanf("%s", temp);
                for (i = 0; i <= playerscount && usw == 0; i++) {
                    if (strcmp(players[i].user, temp) == 0) {
                        usw = 1;
                        printf("Please enter password! \n");
                        while (1) {
                            k = 0;
                            do {
                                tmp = getch();
                                if (tmp != 13) {
                                    printf("X \n");
                                    temppass[k] = tmp;
                                    k++;
                                }
                                if (tmp == '\b') {
                                    printf("\b \n");
                                    temppass[k] = '\0';
                                    k--;
                                }
                            } while (tmp != 13);

                            temppass[k] = '\0';

                            if (strcmp(temppass, players[i].password) == 0) {
                                printf("You signed in successfully! \n");
                                *currentplayer = i;     //recognizing the player in players struct to know which informations we can give
                                swlogin = 1;     //to show that someone logged in and continue
                                return;
                            }
                            else
                                printf("Wrong pass ! Please try again! \n");
                            continue;
                        }
                    }
                }
                if (usw == 0) {
                    printf("This user doesn't exist !! \n");
                    continue;
                }
            }
        }

        else if (ch == 27) {
            return;
        }
    }
}


int main() {

    int currentplayer;
    int playernum;
    systemlogin(&currentplayer);
    int code;

    printf(" Please enter the code of your request \n", players[currentplayer].user);
    printf("Codes : '1' for playing game , '2' for player's games statistics ! \n");
    scanf("%d", &code);

    if (code == 1) {
        printf("New game? (press 1 for new game)  or Wanna Continue last game and finish it !? (press 2 for continue) \n");
        scanf("%d", &code);
        if (code == 1) {
            //player decided to play new game

            printf("Wanna play with me ? (press 1) ?  Or you found your own opponent ? :D  (press 2) \n");
            scanf("%d", &code);

            if (code == 1)
            {
                printf("Which player do you want to be ? Press 1 for first player 2 for second player \n");
                scanf("%d", &playernum);

                if (playernum == 1 || playernum == 2) {
                    system("cls");

                    printf("______________________________________________________________________________________________________________\n\n");
                    printf("---------------------- Hi  !! Welcome to HALMA ! We whish you enjoy playing this game !!! -----------------------\n");
                    printf("______________________________________________________________________________________________________________\n\n");
                    printf("ATTENTION !! --------  Whenever you wanted to exit the game , enter -1 ! --------- ATTENTION !!\n ");

                    gamewithccamputer(&players[currentplayer], playernum, currentplayer);
                }
                else
                    printf("Wrong input! We only have 2 players player 1 & 2 \n");
            }
        }

        if (code == 2) {
            //we have 2 player user should choose his/her playernum

            printf("Which player do you want to be ? Press 1 for first player 2 for second player \n");
            scanf("%d", &playernum);

            if (playernum == 1 || playernum == 2) {
                system("cls");

                printf("______________________________________________________________________________________________________________\n\n");
                printf("---------------------- Hi  !! Welcome to HALMA ! We whish you enjoy playing this game !!! -----------------------\n");
                printf("______________________________________________________________________________________________________________\n\n");
                printf("ATTENTION !! --------  Whenever you wanted to exit the game , enter -1 ! --------- ATTENTION !!\n ");

                gamewithanotherplayer(&players[currentplayer], playernum, currentplayer);
            }
            else
                printf("Wrong input! We only have 2 players player 1 & 2 \n");
        }
    }

    if (code == 2) {
        printf("games : %d \n   ,   winnings : %d \n   ,   loses : %d \n    ,     draws : %d \n ", players[currentplayer].game_c, players[currentplayer].win_c, players[currentplayer].lose_c, players[currentplayer].draw_c);
        printf("Best results are for : %s \n    Worst results are for : %s \n ", best.user, worst.user);
        printf("Best player with having  %d wins and %d loses and %d draws in %d games \n ", best.win_c, best.lose_c, best.draw_c, best.game_c);
        printf("Worst player with having  %d wins and %d loses and %d draws in %d games \n ", worst.win_c, worst.lose_c, worst.draw_c, worst.game_c);
    }
    return 0;
}














// HERE IS OUR ATTEMPT TO USE ALLEGRO LIBRARY , WE TRIED OUR BEST BUT WE HAD SOME PROBLEMS SUCH AS INSTALLING MOUSE , ETC.  
// SO WE PUT IT HERE JUST IN CASE YOU WANTED TO CHECK IT OUT AND CONSIDER OUR TRY TO LEARN NEW THINGS  :)) 




//void showboard(int board[][50], int LEN)
//
//{
//    //---------Game Board Print
//    //---the  number :3 for row
//    //---the number:4 for column
//    //---the number:1 for player1's beads
//    //---the number:2 for player2's beads
//    
//    int row, column, sw;
//
//    ALLEGRO_MOUSE_STATE state;
//
//    //initialazation.
//    al_init();
//    al_install_keyboard();
//    al_install_mouse();
//    al_init_primitives_addon();
//
//    // pointers.
//    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
//    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
//    ALLEGRO_DISPLAY* disp = al_create_display(600, 600);
//    ALLEGRO_FONT* font = al_create_builtin_font();
//
//    //registration.
//    al_register_event_source(queue, al_get_keyboard_event_source());
//    al_register_event_source(queue, al_get_display_event_source(disp));
//    al_register_event_source(queue, al_get_timer_event_source(timer));
//
//    //bools.
//    bool redraw = true;
//    ALLEGRO_EVENT event;
//
//    al_start_timer(timer);
//    while (al_is_event_queue_empty(queue))
//    {
//        al_wait_for_event(queue, &event);
//
//        if (event.type == ALLEGRO_EVENT_TIMER)
//            redraw = true;
//        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
//            break;
//
//        if (redraw && al_is_event_queue_empty(queue))
//        {
//            al_get_mouse_state(&state);
//            
//            if (state.buttons == 1) {
//                /* Primary (e.g. left) mouse button is held. */
//                printf("Mouse position: (%d, %d)\n", state.x, state.y); 
//                if (sw == 0) {
//                    sw = 1;
//                printf:("first click!");
//                }
//                else if (sw == 1) {
//                    sw = 0;
//                    printf("second click!");
//                }
//            }
//            al_clear_to_color(al_map_rgb(0, 0, 0)); 
//
//            //creating the board.
//            for (row = 150; row < LEN*20; row+=40) {
//                for (column = 150; column < LEN*20 ; column+=40) {
//                    al_draw_rectangle(row, column, row + 40, column + 40, al_map_rgb(255, 255, 255), 5);
//
//                }
//             }
//
//            // drawing first player's peices (yellow color).
//            for (row = 170, column = 170; row <= 250; row += 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(65, 210, 36));
//            }
//
//            for (row = 170, column = 210; row <= 250; row += 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(65, 210, 36));
//            }
//
//            for (row = 170, column = 250; row <= 210; row += 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(65, 210, 36));
//            }
//
//            // drawing second player's peices (blue color).
//            for (row = 410, column = 410; row >= 330; row -= 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(0, 0, 255));
//            }
//
//            for (row = 410, column = 370; row >= 330; row -= 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(0, 0, 255));
//            }
//
//            for (row = 410, column = 330; row >= 350; row -= 40) {
//                al_draw_filled_circle(row, column, 10, al_map_rgb(0, 0, 255));
//            }
//
//            al_flip_display();
//
//            redraw = false;
//        }
//    } // end of "while(1)".
//
//    // destroying fuctions in order to save storage.
//    al_uninstall_keyboard();
//    al_uninstall_mouse();
//    al_destroy_display(disp);
//    al_destroy_font(font);
//}

