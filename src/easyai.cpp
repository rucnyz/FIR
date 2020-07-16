#include "Include/easyai.h"
#include <string.h>

EasyAI::EasyAI()
{
}
QPoint EasyAI::Go(int (*pos)[15])
{
    int max_score = 0;
    int x0, y0;
    evaluate_naive(pos);
    for (int j = 0; j < 15; j++)
    {
        for (int k = 0; k < 15; k++)
        {
            if (score[j][k] > max_score)
            {
                max_score = score[j][k];
                x0 = j;
                y0 = k;
            }
        }
    }
    return QPoint(x0, y0);
}
void EasyAI::evaluate_naive(int (*pos)[15]) //每个空子的评估函数。需要对人落子和电脑已落子进行评价。人落子电脑要堵，电脑自己落子要做成5子
{
    memset(score, 0, sizeof(score));
    int number1, number2, empty;

    for (int x = 0; x < 15; ++x)
    {
        for (int y = 0; y < 15; ++y)
        {
            if (pos[x][y] == 0) //评估每个空子
            {
                for (int i = -1; i <= 1; ++i)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        if (!(i == 0 && j == 0)) //0,0不动不用算
                        {
                            number1 = 0, number2 = 0, empty = 0;

                            //对人落子评分
                            for (int k = 1; k <= 5; ++k)
                            {
                                if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 1)
                                {
                                    ++number1;
                                }
                                else if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 0)
                                {
                                    ++empty;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (int k = -1; k >= -5; --k)
                            {
                                if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 1)
                                {
                                    ++number1;
                                }
                                else if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 0)
                                {
                                    ++empty;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if (number1 == 1)
                            {
                                score[x][y] += 1; //人若下该空子，就两子了，那么不管死活都是+1
                            }
                            else if (number1 == 2)
                            {
                                if (empty == 1)
                                {
                                    score[x][y] += 5; //三子，死，+5
                                }
                                else if (empty == 2)
                                {
                                    score[x][y] += 10; //三子，活，+10
                                }
                            }
                            else if (number1 == 3)
                            {
                                if (empty == 1)
                                {
                                    score[x][y] += 20; //四子，死，+20
                                }
                                else if (empty == 2)
                                {
                                    score[x][y] += 100; //四子，活，+100
                                }
                            }
                            else if (number1 == 4)
                            {
                                score[x][y] += 1000; //五子，+1000
                            }
                            //对电脑落子评分（我自己下了这个空子，会怎样）
                            empty = 0;

                            for (int k = 1; k <= 5; ++k)
                            {
                                if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 2)
                                {
                                    ++number2;
                                }
                                else if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 0)
                                {
                                    ++empty;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (int k = -1; k >= -5; --k)
                            {
                                if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 2)
                                {
                                    ++number2;
                                }
                                else if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == 0)
                                {
                                    ++empty;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if (number2 == 0)
                            {
                                score[x][y] += 1; //电脑若下了该空子，就一子了，那么不管死活都是+1
                            }
                            else if (number2 == 1)
                            {
                                score[x][y] += 2; //两子，+2
                            }
                            else if (number2 == 2)
                            {
                                if (empty == 1)
                                {
                                    score[x][y] += 8; //三子，死，+8
                                }
                                else if (empty == 2)
                                {
                                    score[x][y] += 30; //三子，活，+30
                                }
                            }
                            else if (number2 == 3)
                            {
                                if (empty == 1)
                                {
                                    score[x][y] += 50; //四子，死，+50
                                }
                                else if (empty == 2)
                                {
                                    score[x][y] += 200; //四子，活，+200
                                }
                            }
                            else if (number2 == 4)
                            {
                                score[x][y] += 10000; //五子，+10000
                            }
                        }
                    }
                }
            }
        }
    }
}
bool EasyAI::can_win(int x, int y, int (*pos)[15])
{
    int number = 0;
    int t = pos[x][y];
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (!(i == 0 && j == 0)) //0,0不动不用算
            {
                for (int k = 1; k <= 5; ++k)
                {
                    if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == t)
                    {
                        ++number;
                    }
                }
                for (int k = -1; k >= -5; --k)
                {
                    if (x + i * k >= 0 && x + i * k < 19 && y + j * k >= 0 && y + j * k < 19 && pos[x + i * k][y + j * k] == t)
                    {
                        ++number;
                    }
                }
                if (number == 4)
                {
                    return true;
                }
                number = 0;
            }
        }
    }
    return false;
}
bool EasyAI::can_Awin(int (*pos)[15])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (pos[i][j] == 1)
            {
                if (can_win(i, j, pos))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool EasyAI::can_Bwin(int (*pos)[15])
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (pos[i][j] == 2)
            {
                if (can_win(i, j, pos))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
