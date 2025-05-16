#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Player
{
    char mark; // O or X
public:
    Player(char m) { mark = m; }
    virtual int getMove() = 0;
    char getMark() const { return mark; }
};
class HPlayer : public Player
{
public:
    HPlayer(char mark) : Player(mark) {}
    int getMove()
    {
        int index;
        cout << "Enter box number to put " << getMark() << " : ";
        cin >> index;
        return index;
    }
};

class NonSenseComputerPlayer : public Player
{
public:
    NonSenseComputerPlayer(char mark) : Player(mark)
    {
        srand(time(NULL));
    }
    int getMove()
    {
        int index = rand() % 9 + 1;
        cout << "Box at index " << index << " is selected." << endl;
        return index;
    }
};

class Board
{
    char arr[9];
    bool setMove(int index, char mark)
    {
        char m = arr[index - 1];
        cout << "Index:" << index << '\t' << "Mark:" << m << '\t';
        if (m >= '1' && m <= '9')
        {
            arr[index - 1] = mark;
            cout << arr[index - 1] << '\n';
            return true;
        }
        return false;
    }
    friend class Game;

public:
    void init()
    {
        for (int i = 0; i < 9; i++)
            arr[i] = i + 49;
    }
    void getBoard(char b[])
    {
        for (int i = 0; i < 9; i++)
            b[i] = arr[i];
    }
    void draw()
    {
        cout << endl;
        cout << " ___ ___ ___ " << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[0] << " | " << arr[1] << " | " << arr[2] << " |" << endl;
        cout << "|___|___|___|" << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[3] << " | " << arr[4] << " | " << arr[5] << " |" << endl;
        cout << "|___|___|___|" << endl;
        cout << "|   |   |   |" << endl;
        cout << "| " << arr[6] << " | " << arr[7] << " | " << arr[8] << " |" << endl;
        cout << "|___|___|___|" << endl;
        /*
        cout<<'\n';
        for (int i=0;i<9;i++){
            cout<<setw(2)<<arr[i];
            if (i==2 || i==5) cout<<"\n";
        }
        cout<<"\n\n";
        */
    }
};

class SensibleComputerPlayer : public Player
{
protected:
    Board *b;
    int lines[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}, // Rows
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8}, // Columns
        {0, 4, 8},
        {2, 4, 6} // Diagonals
    };
    // int checkForTwoInline(char boardArray[], char mark);
    int checkForTwoInline(char boardArray[], char mark)
    {
        for (int(&line)[3] : lines)
        {
            int markCount = 0;
            int emptyPos = -1; // means no empty cell till yet
            for (int pos : line)
            {
                if (boardArray[pos] == mark)
                {
                    markCount++;
                }
                else if (boardArray[pos] >= '1' && boardArray[pos] <= '9')
                {
                    emptyPos = pos;
                }
            }
            if (markCount == 2 && emptyPos != -1)
            {
                return emptyPos + 1;
            }
        }
        return -1;
    }
    int checkForOneInLine(char boardArray[], char mark)
    {
        vector<int> possibleMoves;
        for (int(&line)[3] : lines)
        {
            int markCount = 0;
            int emptyCount = 0;
            vector<int> emptyPositions;
            for (int pos : line)
            {
                if (boardArray[pos] == mark)
                    markCount++;
                else if (boardArray[pos] >= '1' && boardArray[pos] <= '9')
                {
                    emptyCount++;
                    emptyPositions.push_back(pos);
                }
            }
            if (markCount == 1 && emptyCount == 2)
            {
                for (int pos : emptyPositions)
                {
                    possibleMoves.push_back(pos + 1);
                }
            }
        }
        if (!possibleMoves.empty())
        {
            return possibleMoves[rand() % possibleMoves.size()];
        }
        return -1;
    }
    int findEmptyCell(char boardArray[], char mark)
    {
        int emptyCells[9];
        int emptyCount = 0;
        for (int i = 0; i < 9; i++)
        {
            if (boardArray[i] >= '1' && boardArray[i] <= '9')
                emptyCells[emptyCount++] = i + 1;
        }
        if (emptyCount > 0)
        {
            return emptyCells[rand() % emptyCount];
        }
        return 1;
    }

public:
    SensibleComputerPlayer(char mark, Board *_b) : Player(mark), b(_b) {}
    int getMove()
    {
        char boardArray[9];
        b->getBoard(boardArray);
        int move = 0;

        // if there are two marks in any line and i win the game
        move = checkForTwoInline(boardArray, getMark());
        if (move != -1)
        {
            cout << "Sensible Computer selects box " << move << " to put " << getMark() << "(winning move)" << endl;
            return move;
        }

        // if there are two opponent's marks in any line and i block the line
        int opponentMark = (getMark() == 'X') ? 'O' : 'X';
        move = checkForTwoInline(boardArray, opponentMark);
        if (move != -1)
        {
            cout << "Sensible Computer selects box " << move << " to put " << getMark() << "(blocking move)" << endl;
            return move;
        }

        // if there is one myMark in line and two empty cells then try to make win opportunity by selecting one of those two empty slots/cells randomly
        move = checkForOneInLine(boardArray, getMark());
        if (move != -1)
        {
            cout << "Sensible Computer selects box " << move << " to put " << getMark() << "(creating opportunity)" << endl;
            return move;
        }

        // if no opportunity to win or win cell(only one to win game) or block cell(block the opponent cell) found then select random cell from left empt cells
        move = findEmptyCell(boardArray, getMark());
        if (move != -1)
            cout << "Sensible Computer selects box " << move << " to put " << getMark() << "(random empty cell)" << endl;
        return move;
    }
};

class Game
{
    Board b;
    Player *p1, *p2;

public:
    Game(int gameMode, char p1Mark = 'X', char p2Mark = 'O')
    {
        init();
        switch (gameMode)
        {
        case 1:
            p1 = new HPlayer(p1Mark);
            p2 = new HPlayer(p2Mark);
            cout << "Game Mode: Human vs Human" << endl;
            break;
        case 2:
            p1 = new HPlayer(p1Mark);
            p2 = new NonSenseComputerPlayer(p2Mark);
            cout << "Game Mode: Human vs NonSense Computer" << endl;
            break;
        case 3:
            p1 = new HPlayer(p1Mark);
            p2 = new SensibleComputerPlayer(p2Mark, &b);
            cout << "Game Mode: Human vs Sensible Computer" << endl;
            break;
        case 4:
            p1 = new NonSenseComputerPlayer(p1Mark);
            p2 = new SensibleComputerPlayer(p2Mark, &b);
            cout << "Nonsense Computer vs Sensible Computer" << endl;
            break;

        default:
            break;
        }
        b.draw();
    }
    void init()
    {
        b.init();
    }
    bool checkRow(char b[], int r, char mark)
    {
        for (int i = r; i < r + 3; i++)
            if (b[i] != mark)
                return false;
        return true;
    }
    bool checkColumn(char b[], int r, char mark)
    {
        for (int i = r; i < 9; i += 3)
            if (b[i] != mark)
                return false;
        return true;
    }
    bool checkD1(char b[], char mark)
    {
        return (b[0] == mark && b[4] == mark && b[8] == mark);
    }
    bool checkD2(char b[], char mark)
    {
        return (b[2] == mark && b[4] == mark && b[6] == mark);
    }
    bool checkWin(char b[], int pos, char mark)
    {
        if (checkRow(b, pos / 3, mark))
            return true;
        int index;
        if (pos == 0 || pos == 3 || pos == 6)
            index = 0;
        else if (pos == 1 || pos == 4 || pos == 7)
            index = 1;
        else
            index = 2;
        if (checkColumn(b, index, mark))
            return true;
        if ((pos == 0 || pos == 4 || pos == 8) && checkD1(b, mark))
            return true;
        return checkD2(b, mark);
    }
    void runGame()
    {
        int count = 0, pos, turn = 1;
        char a[9], mark = p1->getMark();
        Player *currentPlayer = p1;
        while (count < 9)
        {
            do
            {
                pos = currentPlayer->getMove();
                mark = currentPlayer->getMark();
            } while (!b.setMove(pos, mark));
            if (turn == 1)
            {
                turn = 2;
                currentPlayer = p2;
            }
            else
            {
                turn = 1;
                currentPlayer = p1;
            }
            b.draw();
            b.getBoard(a);
            if (checkWin(a, pos - 1, mark))
                break;
            count++;
        }
        if (count == 9)
            cout << "Draw\n";
        else if (mark == p1->getMark())
            cout << "Player 1 Won\n";
        else
            cout << "Player 2 Won\n";
    }
};
int main()
{
    char playAgain;
    do
    {
        int gameMode;
        cout << "\n==== TIC TAC TOE ====\n";
        cout << "Select game mode:" << endl;
        cout << "1: Human vs Human" << endl;
        cout << "2: Human vs Nonsense Computer" << endl;
        cout << "3: Human vs Sensible Computer" << endl;
        cout << "4: Nonsense Computer vs Sensible Computer" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> gameMode;
        while (gameMode < 1 || gameMode > 4)
        {
            cout << "Invalid choice. Please enter a number between 1 and 4: ";
            cin >> gameMode;
        }
        char p1Mark, p2Mark;
        cout << "Choose mark for Player 1 (O/X): ";
        cin >> p1Mark;
        while (toupper(p1Mark) != 'O' && toupper(p1Mark) != 'X')
        {
            cout << "Invalid mark. Please choose O or X: ";
            cin >> p1Mark;
        }
        p1Mark = toupper(p1Mark);
        p2Mark = (p1Mark == 'O') ? 'X' : 'O';
        Game g(gameMode, p1Mark, p2Mark);
        g.runGame();
        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
    } while (toupper(playAgain) == 'Y');
    cout << "\nThanks for playing Tic Tac Toe!\n";
    return 0;
}
