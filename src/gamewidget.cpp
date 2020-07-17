#include "Include/gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    this->setFixedSize(1000, 1000);
    decideWhoStart();
}
GameWidget::~GameWidget()
{
}
void GameWidget::decideWhoStart()
{
    int rb = QMessageBox::question(NULL, "选择类型", "你是否选择黑棋？", QMessageBox::Yes, QMessageBox::No);
    if (rb == 16384)
    {
        _isYourTurn = true;
    }
    else // rb == 65536 (不知道这是怎么想的^-^)
    {
        _isYourTurn = false;
    }
}
void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/picture/table.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    DrawPieces();         //画棋子
    DrawPieceWithMouse(); //画鼠标（当前方的棋子形状）
    if (!_isYourTurn)
    {
        QPoint pt;
        if (_diff == 0)
        {
            pt = easyAI.Go(board);
        }
        else if (_diff == 1)
        {
            pt = AI.GoNormal(board);
        }
        else
        {
            pt = AI.GoHard(board);
        }
        qDebug() << pt.x() << pt.y();
        board[pt.x()][pt.y()] = 2;

        appendPiece(pt);
    }
    update();
}

void GameWidget::setDiff(int diff)
{
    _diff = diff;
}

void GameWidget::DrawPieces()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    static int tmp = 0;
    //使得程序看起来似乎是思考了一下才下子
    if (tmp != _pieces.size() && _isYourTurn)
    {
        QElapsedTimer time;
        time.start();
        while (time.elapsed() < 350)
        {
            QCoreApplication::processEvents(); //处理事件
        }
    }
    for (int i = 0; i < _pieces.size(); i++)
    {
        Pieces pieces = _pieces[i];
        if (pieces._bBlack)
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(Qt::white);
        }
        DrawChessAtPoint(painter, pieces._pt);
    }

    tmp = _pieces.size();
}

void GameWidget::DrawChessAtPoint(QPainter &painter, QPoint &pt)
{
    QPoint ptCenter(13 + (pt.x() + 0.5) * RECT_WIDTH, 16 + (pt.y() + 0.5) * RECT_HEIGHT);
    painter.drawEllipse(ptCenter, RECT_WIDTH / 2, RECT_HEIGHT / 2);
}

void GameWidget::DrawPieceWithMouse()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    if (_isYourTurn)
    {
        painter.setBrush(Qt::black);
        painter.drawEllipse(mapFromGlobal(QCursor::pos()), RECT_WIDTH / 4, RECT_HEIGHT / 4);
    }
}
void GameWidget::appendPiece(QPoint pos)
{
    Pieces piece(pos, _isYourTurn);
    _pieces.append(piece);
    checkWin(piece);
}
void GameWidget::checkWin(Pieces piece)
{
    //统计4个方向是否五子连
    int nLeft = CountNearItem(piece, QPoint(-1, 0));
    int nLeftUp = CountNearItem(piece, QPoint(-1, -1));
    int nUp = CountNearItem(piece, QPoint(0, -1));
    int nRightUp = CountNearItem(piece, QPoint(1, -1));
    int nRight = CountNearItem(piece, QPoint(1, 0));
    int nRightDown = CountNearItem(piece, QPoint(1, 1));
    int nDown = CountNearItem(piece, QPoint(0, 1));
    int nLeftDown = CountNearItem(piece, QPoint(-1, 1));
    if ((nLeft + nRight) >= 4 ||
        (nLeftUp + nRightDown) >= 4 ||
        (nUp + nDown) >= 4 ||
        (nRightUp + nLeftDown) >= 4)
    {
        QString str = _isYourTurn ? "You Win!" : "You Lose!";
        QMessageBox::information(NULL, "GAME OVER", str, QMessageBox::Yes, QMessageBox::Yes);
        _pieces.clear();
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                board[i][j] = 0;
            }
        }
        decideWhoStart();
        return;
    }
    //该另一方下棋了
    _isYourTurn = !_isYourTurn;
}
void GameWidget::mousePressEvent(QMouseEvent *e)
{
    //求鼠标点击处的棋子点pt
    QPoint pt;
    if (_isYourTurn)
    {
        int x = e->pos().x() - 13, y = e->pos().y() - 16;
        if (x > 975 || y > 960 || x < 0 || y < 0)
        {
            return;
        }
        pt.setX(x / RECT_WIDTH);
        pt.setY(y / RECT_HEIGHT);
        //如果已存在棋子，就什么也不做
        qDebug() << pt.x() << pt.y();
        for (int i = 0; i < _pieces.size(); i++)
        {
            Pieces piece = _pieces[i];
            if (piece._pt == pt)
            {
                //已有棋子
                return;
            }
        }
        board[pt.x()][pt.y()] = 1;
    }
    //不存在棋子，就下一个
    appendPiece(pt);
}

int GameWidget::CountNearItem(Pieces piece, QPoint ptDirection)
{
    int nCount = 0;
    piece._pt += ptDirection;

    while (_pieces.contains(piece))
    {
        nCount++;
        piece._pt += ptDirection;
    }
    return nCount;
}
