#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 8;




class ChessBoard {
public:
    ChessBoard() {
        board.resize(SIZE, vector<char>(SIZE, '.'));
        setupBoard();
    }

    void display() {
        cout << "  0 1 2 3 4 5 6 7" << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << i << " ";
            for (int j = 0; j < SIZE; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    void reverseBoard() {
        // Odwrócenie tablicy w pionie
        for (int i = 0; i < SIZE / 2; ++i) {
            swap(board[i], board[SIZE - i - 1]);
        }

        // Odwrócenie tablicy w poziomie
        for (int i = 0; i < SIZE; ++i) {
            reverse(board[i].begin(), board[i].end());
        }
    }


    bool move(int poczx, int poczy, int konx, int kony) {
        if (IsValid(poczx, poczy, konx, kony)) {
            char ruch = board[poczx][poczy];
            board[poczx][poczy] = '.';
            board[konx][kony] = ruch;
            return true;
        }
        return false;
    }

    bool czyMat(char krol) {
        int krolX, krolY;
        findKing(krol, krolX, krolY);
        return czyKrolWSzachu(krolX, krolY, krol);
    }


    void findKing(char krol, int& krolX, int& krolY) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == krol) {
                    krolX = i;
                    krolY = j;
                    return;
                }
            }
        }
    }

    bool czyKrolWSzachu(int krolX, int krolY, char krol) {
        bool czyBialyKrol = (krol == 'K');
        char wieza = czyBialyKrol ? 'w' : 'W';
        char goniec = czyBialyKrol ? 'g' : 'G';
        char hetman = czyBialyKrol ? 'h' : 'H';
        char skoczek = czyBialyKrol ? 's' : 'S';
        char pionek = czyBialyKrol ? 'p' : 'P';

        for (int dx = -1; dx <= 1; dx += 2) {
            int x = krolX + dx;
            if (x >= 0 && x < SIZE) {
                char figura = board[x][krolY];
                if (figura == wieza || figura == hetman) return true;
            }
        }
        for (int dy = -1; dy <= 1; dy += 2) {
            int y = krolY + dy;
            if (y >= 0 && y < SIZE) {
                char figura = board[krolX][y];
                if (figura == wieza || figura == hetman) return true;
            }
        }

        for (int dx = -1; dx <= 1; dx += 2) {
            for (int dy = -1; dy <= 1; dy += 2) {
                int x = krolX + dx, y = krolY + dy;
                if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
                    char figura = board[x][y];
                    if (figura == goniec || figura == hetman) return true;
                }
            }
        }

        vector<pair<int, int>> skoczekRuchy = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
        for (auto v : skoczekRuchy) {
            int x = krolX + v.first, y = krolY + v.second;
            if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == skoczek) return true;
        }

        int pionekRuch = czyBialyKrol ? -1 : 1;
        if (krolX + pionekRuch >= 0 && krolX + pionekRuch < SIZE) {
            if ((krolY - 1 >= 0 && board[krolX + pionekRuch][krolY - 1] == pionek) ||
                (krolY + 1 < SIZE && board[krolX + pionekRuch][krolY + 1] == pionek)) {
                return true;
            }
        }
        return false;
    }

    bool BorC(int poczx, int poczy, int konx, int kony, int tura)
    {
        if (tura % 2 == 1)
        {
            if (int(board[poczx][poczy]) > 90)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            if (int(board[poczx][poczy]) < 97)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    bool zasady(int poczx, int poczy, int konx, int kony, char krol)
    {
        int licznikskoczka = 0;
        bool czyBialyKrol = (krol == 'K');
        char wieza = czyBialyKrol ? 'w' : 'W';
        char goniec = czyBialyKrol ? 'g' : 'G';
        char hetman = czyBialyKrol ? 'h' : 'H';
        char skoczek = czyBialyKrol ? 's' : 'S';



        if (board[poczx][poczy] == skoczek)
        {
            vector<pair<int, int>> ruchyskoczka = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
            for (auto v : ruchyskoczka)
            {
                if (konx == poczx + v.first && kony == poczy + v.second)
                {

                    return true;

                }
                else
                {
                    licznikskoczka++;

                }

            }
            if (licznikskoczka == 8)
            {
                return false;
            }
        }

        if (board[poczx][poczy] == wieza)
        {
            if (poczx == konx || poczy == kony)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (board[poczx][poczy] == goniec)
        {
            vector<pair<int, int>> kierunkigonca = { {1 ,1}, {1, -1},{-1,-1},{-1, 1} };
            for (auto v : kierunkigonca)
            {
                for (int i = 0; i < SIZE; i++)
                {
                    if (konx == poczx + i * v.first && kony == poczy + i * v.second)
                    {
                        return true;

                    }
                }
            }


            return false;
        }

        if (board[poczx][poczy] == hetman)
        {
            vector<pair<int, int>> kierunkigonca = { {1 ,1}, {1, -1},{-1,-1},{-1, 1} };
            for (auto v : kierunkigonca)
            {
                for (int i = 0; i < SIZE; i++)
                {
                    if ((konx == poczx + i * v.first && kony == poczy + i * v.second) || (poczx == konx || poczy == kony))
                    {
                        return true;

                    }
                }
            }
            return false;
        }



    }

private:
    vector<vector<char>> board;

    void setupBoard() {
        board[0] = { 'w', 's', 'g', 'h', 'k', 'g', 's', 'w' };
        board[1] = { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' };
        board[6] = { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' };
        board[7] = { 'W', 'S', 'G', 'H', 'K', 'G', 'S', 'W' };
        for (int i = 2; i < 6; ++i) {
            fill(board[i].begin(), board[i].end(), '.');
        }
    }



    bool IsValid(int poczx, int poczy, int konx, int kony) {
        return !(poczx < 0 || poczx >= SIZE || poczy < 0 || poczy >= SIZE ||
            konx < 0 || konx >= SIZE || kony < 0 || kony >= SIZE ||
            board[poczx][poczy] == '.');
    }




};

int main() {
    int tura = 1;
    char krol;
    cout << "WSPOLRZEDNE: 1.WIERSZ 2.KOLUMNA!!!" << endl << endl;
    ChessBoard chessBoard;
    chessBoard.display();

    while (true) {
        if (tura % 2 == 1) {
            cout << "TURA BIALYCH (WIELKIE LITERY)" << endl;
            krol = 'k';
        }
        else {
            cout << "TURA CZARNYCH (MALE LITERY)" << endl;
            krol = 'K';
        }

        int poczx, poczy, konx, kony;
        cout << endl << "Podaj pozycje poczatkowa i koncowa (pocz x pocz y kon x kon y): ";
        cin >> poczx >> poczy >> konx >> kony;
        if (chessBoard.BorC(poczx, poczy, konx, kony, tura))
        {
            if (chessBoard.zasady(poczx, poczy, konx, kony, krol)) {

                if (chessBoard.move(poczx, poczy, konx, kony)) {

                    chessBoard.reverseBoard();
                    chessBoard.display();
                    tura++;
                }
                else {
                    cout << "Nieprawidłowy ruch! Spróbuj ponownie." << endl;
                }

            }
            else
            {
                cout << "Nieprawidłowy ruch! Spróbuj ponownie." << endl;
            }
            int krolX, krolY;
            chessBoard.findKing(krol, krolX, krolY);

            if (chessBoard.czyKrolWSzachu(krolX, krolY, krol)) {
                cout << "Szach!" << endl;

                if (chessBoard.czyMat(krol)) {
                    cout << "Mat! Koniec gry." << endl;
                    break;
                }
            }

        }
        else {
            cout << "Nieprawidłowy ruch! Spróbuj ponownie." << endl;
        }
    }
    return 0;
}



