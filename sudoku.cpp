#include "sudoku.h"


    bool sudoku::ComLine(int i, int j, int m)								//проверяем, что числа m нет в столбце j и строке i; возвращаем true если есть
    {
        for (int k = 0; k < 9; k++)
            if ((m == table[i][k][0]) && (k != j))
                return true;

        for (int k = 0; k < 9; k++)
            if ((m == table[k][j][0]) && (k != i))
                return true;

        return false;
    }

    bool sudoku::ComBox(int i, int j, int m)								//проверяем, что числа m нет в квадрате 3х3, которому принадлежит элемент ixj; возвращаем true если есть
    {
        int boxi = i % 3;											//находим положение i внутри квадрата
        int boxj = j % 3;											//находим положение j внутри квадрата

        for (int k = i - boxi; k < i - boxi + 3; k++)
            for (int l = j - boxj; l < j - boxj + 3; l++)
                if ((table[k][l][0] == m) && (k != i) && (l != j))
                    return true;

        return false;

    }

    bool sudoku::ComLineBefore(int i, int j, int m)							//проверяем, что числа m нет в столбце j и строке i до i и j; возвращаем true если есть
        {
            for (int k = 0; k < 9; k++)
                if (m == table[i][k][0])
                {
                    if (k == j)
                        break;
                    return true;
                }

            for (int k = 0; k < 9; k++)
                if (m == table[k][j][0])
                {
                    if (k == i)
                        break;
                    return true;
                }

            return false;
        }

        bool sudoku::ComBoxBefore(int i, int j, int m)							//проверяем, что числа m нет в квадрате 3х3, которому принадлежит элемент ixj до элемента boxIxboxJ; возвращаем true если есть
        {
            int boxi = i % 3;											//находим положение i внутри квадрата
            int boxj = j % 3;											//находим положение j внутри квадрата

            for (int k = i - boxi; k < i - boxi + 3; k++)
                for (int l = j - boxj; l < j - boxj + 3; l++)
                {
                    if ((k == i) && (l == j))
                        return false;
                    if (table[k][l][0] == m)
                        return true;
                }

            return false;

        }

    void sudoku::findPoss(int i, int j)										//находим возможные значения в ячейке ixj
    {
        int m = 1;
        for (int k = 1; k < 10; k++)
            if (!ComBox(i, j, k) && !ComLine(i, j, k))
            {
                table[i][j][m] = k;
                m++;
            }
        table[i][j][m] = 0;
        return;
    }


    void sudoku::createPos()												//находим все возможные значения во всех пустых клетках
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (table[i][j][1] != 0)
                    findPoss(i, j);
            }
    }

    int sudoku::get(int i, int j)
    {
        return table[i][j][0];
    }

    sudoku::sudoku()
    {
        for (int i = 0; i < 9; i++)
                    for (int j = 0; j < 9; j++)
                    {
                        table[i][j][0] = 0;
                        for (int k = 1; k < 11; k++)
                            table[i][j][k] = -1;
                    }
    }

    void sudoku::set(int i, int j, int m)
    {
        if ((m < 0) || (m > 9))
        {
            return;
        }

        table[i][j][0] = m;
        if (m != 0)
            table[i][j][1] = 0;

        return;
    }

    bool sudoku::check(int fI, int fJ)													//пытаемся подобрать решение путем переборов всех доступных элементов в третьем измерении массива
    {
        int d;
                bool ifX = true, ifY = true;

                for (int i = 0; i < 9; i++)
                {
                    if (ifX && (i != fI))
                        continue;
                    for (int j = 0; j < 9; j++)
                    {
                        ifX = false;
                        if (ifY && (j != fJ))
                            continue;
                        ifY = false;
                        for (int k = 1; k < 11; k++)
                        {
                            if (table[i][j][k] != 0)
                            {
                                if (!ComBoxBefore(i, j, table[i][j][k]) && !ComLineBefore(i, j, table[i][j][k]))
                                {
                                    table[i][j][0] = table[i][j][k];
                                    d = table[i][j][1];
                                    table[i][j][1] = 0;
                                    if (!check(i, j))
                                    {
                                        table[i][j][1] = d;
                                        table[i][j][0] = 0;
                                    }
                                    else return true;
                                }
                            }
                            else break;
                        }

                        if (table[i][j][0] == 0)
                            return false;
                    }
                }
                return true;
    }

    void sudoku::solve()
    {
        bool canStart = false;
                
                while (!canStart)
                {
                    createPos();
                    canStart = true;
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                        {
                            if (table[i][j][2] == 0)
                            {
                                canStart = false;
                                table[i][j][0] = table[i][j][1];
                                table[i][j][1] = 0;
                                table[i][j][2] = -1;
                            }
                        }
                }

                check(0, 0);
                return;
    }

    void sudoku::reset()
    {
        for (int i=0; i<9; i++)
            for (int j=0; j<9; j++)
                for (int k=0; k<11; k++)
                {
                    if (k > 0)
                        table[i][j][k] = -1;
                    else
                        table[i][j][k] = 0;
                }
    }
