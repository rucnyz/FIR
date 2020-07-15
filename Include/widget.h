#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "gamewidget.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
	class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();
	void paintEvent(QPaintEvent *);

private:
	Ui::Widget *ui;

	GameWidget *_gameWidget;
};

#endif // WIDGET_H
