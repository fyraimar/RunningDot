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
    ifWin = -1;
    setInit();
    //QMessageBox::information(this, tr("Ready?!"),tr("Run to the Edge of the square!!!"));
}

gameLoop::~gameLoop()
{
}

void gameLoop::refreshTimer(void)
{


    if (this->ifWin==0)
    {
        QMessageBox::information(this, tr("GameOver!!!"),tr("You DIE!!!"));
        ifWin=-1;
        setInit();
        return;
    }
    if (this->ifWin==1)
    {
        QMessageBox::information(this, tr("Congratulation!!!"),tr("You ESCAPED!!!"));
        ifWin=-1;
        setInit();
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
    if ( checkWin() ) return;
    wall.addRocks(dot.pos, direct);
    checkLoose();
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

    QAction * restartGame = new QAction(tr("Restart"), gameMenu);
    QAction * quitGame = new QAction(tr("Quit"), gameMenu);
    gameMenu->addAction(restartGame);
    gameMenu->addAction(quitGame);
    menuBar->addMenu(gameMenu);
    connect(restartGame, SIGNAL(triggered()), this, SLOT(restartGame()));
    connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));


    setMenuBar(menuBar);


}



bool gameLoop::checkLoose()
{
    Position up=dot.pos;
    Position right=dot.pos;
    Position down=dot.pos;
    Position left=dot.pos;

    up.y = dot.pos.y - 1;
    right.x =dot.pos.x + 1;
    down.y = dot.pos.y + 1;
    left.x =dot.pos.x - 1;

    int ifValid1 = 1;
    int ifValid2 = 1;
    int ifValid3 = 1;
    int ifValid4 = 1;
    for (int i=0; i<wall.rocks.size(); i++)
    {\
        if (wall.rocks[i].x==up.x && wall.rocks[i].y==up.y)
        {
            ifValid1=0;
        }
        if (wall.rocks[i].x==right.x && wall.rocks[i].y==right.y)
        {
            ifValid2=0;
        }
        if (wall.rocks[i].x==down.x && wall.rocks[i].y==down.y)
        {
            ifValid3=0;
        }
        if (wall.rocks[i].x==left.x && wall.rocks[i].y==left.y)
        {
            ifValid4=0;
        }
    }
    if (ifValid1 + ifValid2 + ifValid3 + ifValid4 == 0)
    {
        ifWin = 0;
        return true;
    }
    return false;
}

bool gameLoop::checkWin()
{
    if (dot.pos.x==0 || dot.pos.y==0 || dot.pos.x==24 || dot.pos.y==24)
    {
        ifWin = 1;
        update();
        return true;
    }
    return false;
}

void gameLoop::setInit()
{
    wall.rocks.clear();
    dot.pos.x = 12;
    dot.pos.y = 12;
    QMessageBox::information(this, tr("Ready?!"),tr("Run to the Edge of the square!!!"));
    update();
}

void gameLoop::restartGame(void)
{
    setInit();
}
