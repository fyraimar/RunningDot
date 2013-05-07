#include "gameLoop.h"
#include <iostream>
#include <vector>

using namespace std;

gameLoop::gameLoop(QWidget * parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    setWindowTitle(tr("Running Dot ~"));
    setFixedSize(600,600+MENUHEIGHT);
    setupMenu();
    ifRunning = 0;
}

gameLoop::~gameLoop()
{
}

void gameLoop::refreshTimer(void)
{

    if (ifRunning == 0)
    {
        return;
    }

    Position toNext;
    toNext.x = dot.pos.x;
    toNext.y = dot.pos.y;

    switch (direct)
    {
    case 1:
        toNext.y -= 1;
        break;
    case 2:
        toNext.x += 1;
        break;
    case 3:
        toNext.y += 1;
        break;
    case 4:
        toNext.x -= 1;
        break;
    }

    int ifValid = 1;

    for (int i=0; i<wall.rocks.size(); i++)
    {\
        if (wall.rocks[i].x==toNext.x && wall.rocks[i].y==toNext.y)
        {
            ifValid = 0;
            break;
        }
    }
    if (!ifValid) return;

    dot.pos.x = toNext.x;
    dot.pos.y = toNext.y;
    update();
    wall.addRocks(dot.pos);
    update();
}

void gameLoop::paintEvent(QPaintEvent * event)
{

    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, size().width(), size().height());


    painter.setBrush(Qt::white);
    for (int x=0; x<600; x+=24) painter.drawLine(x, MENUHEIGHT, x, 600+MENUHEIGHT);
    for (int y=MENUHEIGHT; y<600+MENUHEIGHT; y+=24) painter.drawLine(0, y, 600, y);

    painter.setBrush(Qt::yellow);
    for (int i=0; i<wall.rocks.size(); i++)
    {\
        painter.drawRect(24*wall.rocks[i].x, 24*wall.rocks[i].y+MENUHEIGHT, 25, 25);
    }

    painter.setBrush(Qt::red);
    painter.drawEllipse(24*dot.pos.x, 24*dot.pos.y+MENUHEIGHT, 24, 24);

    QWidget::paintEvent(event);
}

/*
void gameLoop::mouseEvent(QMouseEvent * event)
{
    QWidget::mouseEvent(event);
}
*/

void gameLoop::keyPressEvent(QKeyEvent * event)
{

    switch (event->key())
    {
    case Qt::Key_Up:
        this->direct = 1;
        break;
    case Qt::Key_Right:
        this->direct = 2;
        break;
    case Qt::Key_Down:
        this->direct = 3;
        break;
    case Qt::Key_Left:
        this->direct = 4;
        break;
    default:
        break;
    }
    QWidget::keyPressEvent(event);
    refreshTimer();
}


void gameLoop::setupMenu(void)
{
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * gameMenu = new QMenu(tr("Game"), menuBar);
    QMenu * modeMenu = new QMenu(tr("Mode"), menuBar);
    QMenu * helpMenu = new QMenu(tr("Help"), menuBar);

    QAction * startGame = new QAction(tr("Start"), gameMenu);
    QAction * pauseGame = new QAction(tr("Pause"), gameMenu);
    QAction * quitGame = new QAction(tr("Quit"), gameMenu);
    gameMenu->addAction(startGame);
    gameMenu->addAction(pauseGame);
    gameMenu->addAction(quitGame);
    menuBar->addMenu(gameMenu);
    connect(startGame, SIGNAL(triggered()), this, SLOT(startGame()));
    connect(pauseGame, SIGNAL(triggered()), this, SLOT(pauseGame()));
    connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));

    QAction * dotMode = new QAction(tr("I'm dot!"), gameMenu);
    QAction * wallMode = new QAction(tr("T'm walls!"), gameMenu);
    modeMenu->addAction(dotMode);
    modeMenu->addAction(wallMode);
    menuBar->addMenu(modeMenu);
    //
    //

    QAction * helpGame = new QAction(tr("游戏帮助"), helpMenu);
    QAction * aboutGame = new QAction(tr("关于"), helpMenu);
    helpMenu->addAction(helpGame);
    helpMenu->addAction(aboutGame);
    menuBar->addMenu(helpMenu);
    connect(helpGame, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(aboutGame, SIGNAL(triggered()), this, SLOT(showAbout()));


    menuBar->addMenu(helpMenu);


    setMenuBar(menuBar);


}

void gameLoop::showAbout(void)
{
    QMessageBox::information(this, tr("Written by Fyr"),
                   tr("Based on qt4.8."));
}

void gameLoop::showHelp(void)
{
    QMessageBox::information(this, tr("Help"),
                   tr("To control the Dot or Wall."));
}

void gameLoop::startGame(void)
{
    ifRunning = 1;
}

void gameLoop::pauseGame(void)
{
    ifRunning = 0;
}

