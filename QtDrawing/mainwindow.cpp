#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float framePerSecond = 60; // 60fps, FIXME: not correct, consider variable remove

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    timer->start(1000 / framePerSecond);

    this->time = 0;
    //rect = QRectF(80,120,200,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setBrush(Qt::BDiagPattern);

    int frameNumber = this->time;
    int width = this->width();
    int height = this->height();

    double animationSpeed = 500.0;
    double angleFactor = (frameNumber % (int)animationSpeed) / animationSpeed;


    //cout << "tansformedX:" << tansformedX << endl;
    for ( int i = 0; i < 10; i++) {
        QColor color;
        color.setHsl(360.0*i/10.0, 50, 100/*, int a = 255*/);

        QPen pen;
        pen.setColor(color);
        pen.setWidth(5);

        painter.setPen(pen);

        QRect rect;

        double angleInPiUnits = 2*M_PI*angleFactor; // clock hand
        double tansformedX = sinf(angleInPiUnits + 2*M_PI*(i/10.0))*(width/10) + width/10 + 50;
        double tansformedY = cosf(angleInPiUnits + 2*M_PI*(i/10.0))*(width/10) + width/10 + 50;

        rect.setX( tansformedX );
        rect.setWidth( abs(width - tansformedX*2) );
        rect.setY( tansformedY );
        rect.setHeight( abs(height - tansformedY*2) );

        painter.drawRect(rect);
    }

    //painter.drawPoint();

    this->time ++;
}

