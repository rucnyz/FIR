#ifndef PIECES_H
#define PIECES_H

#include <QPoint>
class Pieces
{
public:
    Pieces(void);
    Pieces(QPoint pt, bool bBlack);
    ~Pieces(void);

    inline bool operator==(const Pieces &t1) const
    {
        return ((_pt == t1._pt) && (_bBlack == t1._bBlack));
    }

    QPoint _pt;
    bool _bBlack;

private:
};

#endif // PIECES_H
