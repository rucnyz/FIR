#include "Include/widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    //设置开始场景
    this->setFixedSize(1000, 1000);
    connect(ui->pushButton, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=](){
            _gameWidget = new GameWidget;
            this->hide();
            _gameWidget->show();
            _gameWidget->setDiff(0);
                });
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=](){
            _gameWidget = new GameWidget;
            this->hide();
            _gameWidget->show();
            _gameWidget->setDiff(1);
                });
    });
    connect(ui->pushButton_3, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=](){
            _gameWidget = new GameWidget;
            this->hide();
            _gameWidget->show();
            _gameWidget->setDiff(2);
                });
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/picture/startmenu.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

//gameWidget::gameWidget(QWidget* parent)
//	:QWidget(parent)
//{

//}
