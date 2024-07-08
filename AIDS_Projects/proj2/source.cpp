// aidsproj2.2.cpp : Ten plik zawiera funkcjÄ âmainâ. W nim rozpoczyna siÄ i koÅczy wykonywanie programu.
//
#include <iostream>
#include <cstdio>
//#include <cstring>
#include <stdio.h>

#define MAX_BOARD 11
#define SPACES 3
#define DEFAULT_S 2
#define BLUE 2
#define RED 1


using namespace std;

//----------------------------------- FUNKCJE TWORZACE I WYPEÅNIAJACE STRUKTURE BOARD --------------------------------------------------------------------------

struct board
{
    int size = NULL;
    int positions[MAX_BOARD][MAX_BOARD];
    int pawns = NULL;
    int blue_pawns = NULL;
    int red_pawns = NULL;
};

void fillBetaPositions(board* hex, int beta_board[], int num)
{
    getchar();
    char c = getchar();

    switch (c)
    {
    case 'r':
        beta_board[num] = RED;
        hex->pawns += 1;
        hex->red_pawns += 1;
        break;

    case 'b':
        beta_board[num] = BLUE;
        hex->pawns += 1;
        hex->blue_pawns += 1;
        break;

    default:
        beta_board[num] = NULL;
        break;
    }
}

void betaToAlpha(board* hex, int beta_board[]) //changing board setup from T[] to T[][]
{                                              // and saving setup in struct "board"
    int size = hex->size, j = 0, k = 0, level = 0;
    for (int i = 0; i < size * size; i++)
    {
        hex->positions[k][j] = beta_board[i];
        k--;
        j++;
        if (k < 0 || j >= size)
        {
            level++;
            if (level < size)
            {
                k = level;
                j = 0;
            }
            else
            {
                k = size - 1;
                j = level - size + 1;
            }
        }
    }
    /*   to check corectness
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << hex->positions[i][j] << " ";
        }
        cout << endl;
    }*/
}

board parseBoard(int count)
{
    board hex;
    hex.size = count / SPACES;
    char c;
    int beta_board[MAX_BOARD * MAX_BOARD], num = 0;
    bool loading = true;
    do
    {
        c = getchar();
        if (c == '-')
        {
            c = getchar();
            if (c == '-')
            {
                c = getchar();
                if (c == '-')
                    loading = false;
            }
        }
        if (c == '<')
        {
            fillBetaPositions(&hex, beta_board, num);
            num++;
        }

    } while (loading);
    betaToAlpha(&hex, beta_board);
    return hex;
}

void copyPositions(int tocopy[MAX_BOARD][MAX_BOARD], int copyinto[MAX_BOARD][MAX_BOARD], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            copyinto[i][j] = tocopy[i][j];
        }
    }
}

int WhoDidLastMove(board hex)
{
    if (hex.red_pawns == hex.blue_pawns)
        return BLUE;
    else
        return RED;
}

int getOpponent(int player) {
    if (player == RED) return BLUE;
    else return RED;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

bool isCorrect(board hex)
{
    return (hex.red_pawns == hex.blue_pawns || hex.red_pawns == hex.blue_pawns + 1);
}

bool isOver(board hex, int x, int y, int color, int positions[MAX_BOARD][MAX_BOARD])
{
    positions[y][x] = 0; //wyzerowanie miejsca w ktÃłrym stoimy 
    if (color == RED && x == hex.size - 1)
        return true;

    else if (color == BLUE && y == hex.size - 1)
        return true;


    if (y < hex.size - 1 && positions[y + 1][x] == color)
        if (isOver(hex, x, y + 1, color, positions))
            return true;

    if (y > 0 && positions[y - 1][x] == color)
        if (isOver(hex, x, y - 1, color, positions))
            return true;

    if (y < hex.size - 1 && x < hex.size - 1 && positions[y + 1][x + 1] == color)
        if (isOver(hex, x + 1, y + 1, color, positions))
            return true;

    if (y > 0 && x > 0 && positions[y - 1][x - 1] == color)
        if (isOver(hex, x - 1, y - 1, color, positions))
            return true;

    if (x < hex.size - 1 && positions[y][x + 1] == color)
        if (isOver(hex, x + 1, y, color, positions))
            return true;

    if (x > 0 && positions[y][x - 1] == color)
        if (isOver(hex, x - 1, y, color, positions))
            return true;

    return false;
}

int isGameOver(board hex)
{
    char over;
    int positions_tmp[MAX_BOARD][MAX_BOARD];
    copyPositions(hex.positions, positions_tmp, hex.size);
    if (isCorrect(hex))
    {
        for (int i = 0; i < hex.size; i++)
        {
            if (positions_tmp[i][0] == RED)
            {
                if (isOver(hex, 0, i, RED, positions_tmp))
                {
                    return RED;
                }
            }
            if (positions_tmp[0][i] == BLUE)
            {

                if (isOver(hex, i, 0, BLUE, positions_tmp))
                {
                    return BLUE;
                }
            }
        }
    }
    return NULL;
}

bool isPossible(board hex)
{
    int winner = isGameOver(hex), lastmove = WhoDidLastMove(hex);
    if (winner == NULL)
        return true;
    if (winner != lastmove)
        return false;

    for (int i = 0; i < hex.size; i++)
    {
        for (int j = 0; j < hex.size; j++)
        {
            if (hex.positions[i][j] == winner)
            {
                hex.positions[i][j] = NULL;
                if (isGameOver(hex) == NULL)
                {
                    hex.positions[i][j] = winner;
                    return true;
                }
                hex.positions[i][j] = winner;
            }
        }
    }
    return false;
}

void findEmptyPositions(board hex, int positionsX[], int positionsY[])
{
    int count = 0;
    for (int i = 0; i < hex.size; i++)
    {
        for (int j = 0; j < hex.size; j++)
        {
            if (hex.positions[i][j] == NULL)
            {
                positionsX[count] = i;
                positionsY[count] = j;
                count++;
            }
        }
    }
}

bool makeTwoMovesNaive(int player, int opponent, board hex, int movesLeft, int positionsX[], int positionsY[], int numOfEmptyPositions)
{
    if (movesLeft > numOfEmptyPositions)
        return false;
    movesLeft -= 1;
    for (int i = 0; i < numOfEmptyPositions; i++) {
        hex.positions[positionsX[i]][positionsY[i]] = player;
        if (isGameOver(hex) == player) { //sprawdzamy czy przez przypadek nie wygralismy jednym ruchem
            hex.positions[positionsX[i]][positionsY[i]] = 0;
            continue;
        }
        for (int j = 0; j < numOfEmptyPositions; j++) {
            if (j == i)
                continue;
            hex.positions[positionsX[j]][positionsY[j]] = player;
            if (isGameOver(hex) == player) {
                for (int k = 0; k < numOfEmptyPositions; k++) {
                    //if (k == i || k==j)
                      //  continue;
                    hex.positions[positionsX[k]][positionsY[k]] = opponent;
                    if (movesLeft == 3) {
                        for (int m = 0; m < numOfEmptyPositions; m++) {
                            //    if (m == i || m == j || m == k)
                              //      continue;
                            hex.positions[positionsX[m]][positionsY[m]] = opponent;
                            if (isPossible(hex)) {
                                hex.positions[positionsX[m]][positionsY[m]] = 0;
                                hex.positions[positionsX[j]][positionsY[j]] = 0;
                                hex.positions[positionsX[i]][positionsY[i]] = 0;
                                hex.positions[positionsX[k]][positionsY[k]] = 0;
                                return true;
                            }
                            hex.positions[positionsX[m]][positionsY[m]] = 0;
                        }
                    }
                    else {
                        if (isPossible(hex)) {
                            hex.positions[positionsX[j]][positionsY[j]] = 0;
                            hex.positions[positionsX[i]][positionsY[i]] = 0;
                            hex.positions[positionsX[k]][positionsY[k]] = 0;
                            return true;
                        }
                    }
                    hex.positions[positionsX[k]][positionsY[k]] = 0;
                }
            }
            hex.positions[positionsX[j]][positionsY[j]] = 0;
        }
        hex.positions[positionsX[i]][positionsY[i]] = 0;
    }
    return false;
}

bool makeOneMoveNaive(int player, int opponent, board hex, int movesLeft, int positionsX[], int positionsY[], int numOfEmptyPositions)
{
    if (movesLeft > numOfEmptyPositions)
        return false;
    movesLeft -= 1;
    for (int i = 0; i < numOfEmptyPositions; i++) {
        hex.positions[positionsX[i]][positionsY[i]] = player;
        if (isGameOver(hex) == player) {
            if (movesLeft == 0) {
                hex.positions[positionsX[i]][positionsY[i]] = 0;
                return true;
            }
            if (movesLeft == 1) {
                for (int j = 0; j < numOfEmptyPositions; j++) {
                    if (j == i)
                        continue;
                    hex.positions[positionsX[j]][positionsY[j]] = opponent;
                    if (isPossible(hex)) {
                        hex.positions[positionsX[j]][positionsY[j]] = 0;
                        return true;
                    }
                    hex.positions[positionsX[j]][positionsY[j]] = 0;
                }
            }
        }
        hex.positions[positionsX[i]][positionsY[i]] = 0;
    }
    return false;
}

void canTheyWin(board hex, int boardNum)
{
    if (!isCorrect(hex) || isGameOver(hex) > NULL) {
        cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl << endl;
        return;
    }
    int numOfEmptyPositions = (hex.size * hex.size) - hex.pawns;
    int positionsX[MAX_BOARD * MAX_BOARD];
    int positionsY[MAX_BOARD * MAX_BOARD];
    if (!positionsX || !positionsY)
    {
        perror("malloc");
        return;
    }
    findEmptyPositions(hex, positionsX, positionsY);
    if (WhoDidLastMove(hex) == RED) {
        if (makeOneMoveNaive(RED, BLUE, hex, 2, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeOneMoveNaive(BLUE, RED, hex, 1, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeTwoMovesNaive(RED, BLUE, hex, 4, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeTwoMovesNaive(BLUE, RED, hex, 3, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    else { //whoDidLastMove == BLUE
        if (makeOneMoveNaive(RED, BLUE, hex, 1, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeOneMoveNaive(BLUE, RED, hex, 2, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeTwoMovesNaive(RED, BLUE, hex, 3, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        if (makeTwoMovesNaive(BLUE, RED, hex, 4, positionsX, positionsY, numOfEmptyPositions))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    cout << endl;
}

int countWinningPositions(board hex, int player, int positionsX[], int positionsY[], int numOfEmptyPositions)
{
    int count = 0;
    for (int i = 0; i < numOfEmptyPositions; i++) {
        hex.positions[positionsX[i]][positionsY[i]] = player;
        if (isGameOver(hex) == player)
            count++;
        hex.positions[positionsX[i]][positionsY[i]] = 0;
    }
    return count;
}

bool firstPlayerWin(int player, const board hex, int positionsX[], int positionsY[], int numOfEmptyPositions)
{//funkcja która sprawdzi czy gracz ruszajacy jako pierwszy wygra gre w pierwszym ruchu
    if (player == BLUE) {
        return makeOneMoveNaive(BLUE, RED, hex, 1, positionsX, positionsY, numOfEmptyPositions);
    }
    else {
        return makeOneMoveNaive(RED, BLUE, hex, 1, positionsX, positionsY, numOfEmptyPositions);
    }
}

bool secondPlayerWin(int player, board hex, int positionsX[], int positionsY[], int numOfEmptyPositions)
{//TODO
    if (2 > numOfEmptyPositions)
        return false;
    int opponent = getOpponent(player);
    if (firstPlayerWin(opponent, hex, positionsX, positionsY, numOfEmptyPositions)) {
        return false;
    }
    else {
        if (countWinningPositions(hex, RED, positionsX, positionsY, numOfEmptyPositions) > 1) { //jesli red ma wiecej niz 1 pozycje wygrywajacą to wygra
            return true;
        }
        return false;
    }
}

bool thirdPlayerWin(int player, board hex, int positionsX[], int positionsY[], int numOfEmptyPositions) {
    if (3 > numOfEmptyPositions)
        return false;
    int opponent = getOpponent(player);
    for (int i = 0; i < numOfEmptyPositions; i++) {
        hex.positions[positionsX[i]][positionsY[i]] = player;
        if (!secondPlayerWin(opponent, hex, positionsX, positionsY, numOfEmptyPositions))
            return true;
        hex.positions[positionsX[i]][positionsY[i]] = 0;
    }
    return false;
}

bool fourthPlayerWin(int player, board hex, int positionsX[], int positionsY[], int numOfEmptyPositions) {
    if (4 > numOfEmptyPositions)
        return false;
    int opponent = getOpponent(player);
    if (makeOneMoveNaive(opponent, player, hex, 1, positionsX, positionsY, numOfEmptyPositions)){
        return false;
    }
    for (int i = 0; i < numOfEmptyPositions; i++) {
        hex.positions[positionsX[i]][positionsY[i]] = opponent;
        for (int j = 0; j < numOfEmptyPositions; j++) {
            hex.positions[positionsX[j]][positionsY[j]] = player;
            if (secondPlayerWin(player, hex, positionsX, positionsY, numOfEmptyPositions)) {
                return true;
            }
        }
        hex.positions[positionsX[i]][positionsY[i]] = 0;
    }
    return false;
}

void oneMovePerfect(board hex, int positionsX[], int positionsY[], int numOfEmptyPositions)
{
    if (WhoDidLastMove(hex) == RED) {//kolej na ruch blue
        if (firstPlayerWin(BLUE, hex, positionsX, positionsY, numOfEmptyPositions)) {
            cout << "NO" << endl << "YES" << endl;//jesli blue moze wygrac w jednym ruchu red napewno nie wygra
        }
        else {
            if (countWinningPositions(hex, RED, positionsX, positionsY, numOfEmptyPositions) > 1) { //jesli red ma wiecej niz 1 pozycje wygrywajacą to wygra
                cout << "YES" << endl;
            }
            else cout << "NO" << endl;
            cout << "NO" << endl;
        }
    }
    else {
        if (firstPlayerWin(RED, hex, positionsX, positionsY, numOfEmptyPositions)) {
            cout << "YES" << endl << "NO" << endl;
        }
        else {
            cout << "NO" << endl;
            if (countWinningPositions(hex, BLUE, positionsX, positionsY, numOfEmptyPositions) > 1) {
                cout << "YES" << endl;
            }
            else cout << "NO" << endl;
        }
    }
}

void twoMovesPerfect(board hex, int positionsX[], int positionsY[], int numOfEmptyPositions)
{
    //cout << WhoDidLastMove(hex) << endl;
    if (WhoDidLastMove(hex) == RED) {//kolej blue
        if (makeTwoMovesNaive(RED, BLUE, hex, 4, positionsX, positionsY, numOfEmptyPositions)) {
            if (fourthPlayerWin(RED, hex, positionsX, positionsY, numOfEmptyPositions))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else 
            cout << "NO" << endl;

        if (makeTwoMovesNaive(BLUE, RED, hex, 3, positionsX, positionsY, numOfEmptyPositions)) {
            if (thirdPlayerWin(BLUE, hex, positionsX, positionsY, numOfEmptyPositions))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else
            cout << "NO" << endl;
    }
    else {//kolej red
        if (makeTwoMovesNaive(RED, BLUE, hex, 3, positionsX, positionsY, numOfEmptyPositions)) {
            if (thirdPlayerWin(RED, hex, positionsX, positionsY, numOfEmptyPositions))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else 
            cout << "NO" << endl;

        if (makeTwoMovesNaive(BLUE, RED, hex, 4, positionsX, positionsY, numOfEmptyPositions)) {
            if (fourthPlayerWin(BLUE, hex, positionsX, positionsY, numOfEmptyPositions))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
        else
            cout << "NO" << endl;
    }
}

void canWinPerfect(board hex)
{
    if (!isCorrect(hex) || isGameOver(hex) > NULL) {
        cout << "NO" << endl << "NO" << endl << "NO" << endl << "NO" << endl << endl;
        return;
    }
    int numOfEmptyPositions = (hex.size * hex.size) - hex.pawns;
    int positionsX[MAX_BOARD * MAX_BOARD];
    int positionsY[MAX_BOARD * MAX_BOARD];
    if (!positionsX || !positionsY)
    {
        perror("malloc");
        return;
    }
    findEmptyPositions(hex, positionsX, positionsY);
    oneMovePerfect(hex, positionsX, positionsY, numOfEmptyPositions);
    twoMovesPerfect(hex, positionsX, positionsY, numOfEmptyPositions);
    cout << endl;
}

void readCommands(board hex, int boardNum)
{
    char c = '.';
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case 'B':
            //board size
            for (int i = 0; i < 9; i++) getchar();
            cout << hex.size << endl;
            break;

        case 'P':
            //pawns number
            for (int i = 0; i < 11; i++) getchar();
            cout << hex.pawns << endl;
            break;

        case 'I':
            for (int i = 0; i < 2; i++) getchar();
            c = getchar();
            if (c == 'B')
            {
                if (isCorrect(hex))
                {
                    for (int i = 0; i < 5; i++) getchar();
                    c = getchar();
                    if (c == 'C') {
                        for (int i = 0; i < 6; i++) getchar();
                        cout << "YES" << endl << endl;
                    }

                    else
                    {
                        for (int i = 0; i < 7; i++) getchar();
                        if (isPossible(hex))
                            cout << "YES" << endl << endl;
                        else
                            cout << "NO" << endl << endl;
                    }
                }
                else {
                    cout << "NO" << endl << endl;
                    for (int i = 0; i < 12; i++) getchar();
                }

            }
            if (c == 'G')
            {
                int winner = isGameOver(hex);

                if (winner == RED)
                    cout << "YES RED" << endl << endl;
                else if (winner == BLUE)
                    cout << "YES BLUE" << endl << endl;
                else
                    cout << "NO" << endl << endl;
                for (int i = 0; i < 8; i++) getchar();
            }
            break;

        case 'C':
            for (int i = 0; i < 26; i++) getchar();
            c = getchar();
            if (c == 'N') {
                for (int i = 0; i < 143; i++) getchar();
                canTheyWin(hex, boardNum);
            }
            else {
                for (int i = 0; i < 151; i++) getchar();
                canWinPerfect(hex);
            }


        case ' ':
            return;
        }
    }
}

int main()
{
    int count = DEFAULT_S, boardNum = 0;
    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '-')
        {
            boardNum++;
            board hex = parseBoard(count);
            readCommands(hex, boardNum);
            count = DEFAULT_S + 1;
        }
        else if (ch == ' ') {
            count++;
        }
        else count = DEFAULT_S;
    }
}
