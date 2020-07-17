#ifndef EASYAI_H
#define EASYAI_H

#include <QPoint>

class EasyAI
{
public:
    EasyAI();
    QPoint Go(int pos[][15]);

private:
    void evaluate_naive(int (*pos)[15]);

private:
    int score[15][15];
};

#endif // EASYAI_H
