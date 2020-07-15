#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QElapsedTimer>
#include <QCoreApplication>

#include "pieces.h"
#include "easyai.h"

#define RECT_WIDTH 65
#define RECT_HEIGHT 64

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    void setDiff(int diff);

    int pos[15][15] = {{0}};

private:
    void DrawPieces();
    void DrawChessAtPoint(QPainter &painter, QPoint &pt);
    void DrawPieceWithMouse();
    void appendPiece(QPoint pos);
    void checkWin(Pieces piece);
    //void DrawChessboard();

    int CountNearItem(Pieces item, QPoint ptDirection);

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

private:
    int _diff = 0;
    QVector<Pieces> _pieces;
    bool _isYourTurn; //当前该黑棋下
    EasyAI easyAI;

signals:
    void aiTurn();
};

#endif // GAMEWIDGET_H
