#ifndef SUDOKU_H
#define SUDOKU_H


class sudoku
{
private:
    int table[9][9][11];											//третье измерение понадобится для записи возможных вариантов чисел, которые могут быть в этой клетке
                                                                    //причем если там стоит 0, тогда вариантов больше нет
    bool ComLine(int i, int j, int m);

    bool ComBox(int i, int j, int m);

    bool ComLineBefore(int i, int j, int m);

    bool ComBoxBefore(int i, int j, int m);

    void findPoss(int i, int j);

public:
    void createPos();

    int get(int i, int j);

    sudoku();

    void set(int i, int j, int m);

    void reset();

private:
    bool check(int fI, int fJ);

public:
    void solve();
};


#endif // SUDOKU_H
