#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

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
    int checkLine(char arr[], int x, int y, int z, char myMark, char opponentMark)
    {
        int myCount = 0;
        int opponentCount = 0;
        int empty = -1;

        if (arr[x] == myMark)
            myCount++;
        else if (arr[x] == opponentMark)
            opponentCount++;
        else
            empty = x;

        if (arr[y] == myMark)
            myCount++;
        else if (arr[y] == opponentMark)
            opponentCount++;
        else
            empty = y;

        if (arr[z] == myMark)
            myCount++;
        else if (arr[z] == opponentMark)
            opponentCount++;
        else
            empty = z;

        if (myCount == 2 && empty != -1)
            return empty;
        if (opponentCount == 2 && empty != -1)
            return empty;
        if (myCount == 1 && opponentCount == 0 && empty != -1)
            return empty;

        return -1;
    }

public:
    SensibleComputerPlayer(char mark, Board *_b) : Player(mark), b(_b) {}
    int getMove()
    {
        char arr[9];
        b->getBoard(arr);

        char myMark = getMark();
        char opponentMark = (myMark == 'O') ? 'X' : 'O';

        int lines[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

        for (int i = 0; i < 8; i++)
        {
            int move = checkLine(arr, lines[i][0], lines[i][1], lines[i][2], myMark, opponentMark);
            if (move != -1)
            {
                cout << "Sensible Computer selects box at index " << move + 1 << endl;
                return move + 1;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (arr[i] != 'X' && arr[i] != 'O')
            {
                cout << "Sensible Computer selects box at index " << i + 1 << endl;
                return i + 1;
            }
        }
        return 1;
    }
};

class Game
{
    Board b;
    Player *p1, *p2;

public:
    Game()
    {
        init();
        int choice;
        cout << "Press 1 to select Human vs.Human & press 2 to select Human vs. Nonsense Computer : ";
        cin >> choice;
        p1 = new HPlayer('X');
        if (choice == 1)
            p2 = new HPlayer('O');
        else if (choice == 2)
            p2 = new NonSenseComputerPlayer('O');
        else if (choice == 3)
            p2 = new SensibleComputerPlayer('O', &b);
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
    Game g;
    g.runGame();
    return 0;
}
