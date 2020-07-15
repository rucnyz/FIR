#include "Include/pieces.h"

Pieces::Pieces(void)
{
}

Pieces::Pieces(QPoint pt, bool bBlack)
{
    _pt = pt;
    _bBlack = bBlack;
}

Pieces::~Pieces(void)
{
}
