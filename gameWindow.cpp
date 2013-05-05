#include "gameWindow.h"
#include <iostream>
#include <vector>

using namespace std;

gameWindow::gameWindow(QWidget * parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    setWindowTitle(tr("Running Dot ~"));
    MenuBarSize = 20;
    setFixedSize(500,500+MenuBarSize);
    setupMenu();
    IsDie = false;
    bRun = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshTimer()));
    times = 200;
    timer->start(times);
}

gameWindow::~gameWindow()
{
}

void gameWindow::refreshTimer(void)
{
    if (bRun == false)
    {
        timer->stop();
        return;
    }
    if (IsDie)
    {
        timer->stop();
        bRun = false;
        QMessageBox::information(this, tr("Game Over"),
                tr("Over!"));
        IsDie = false;

        return;
    }
    update();
}

void gameWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, size().width(), size().height());
    if (IsDie || !bRun)
    {
        return;
    }

    painter.setBrush(Qt::white);
    for (int x=0; x<500; x+=25) painter.drawLine(x, MenuBarSize, x, 500+MenuBarSize);
    for (int y=MenuBarSize; y<500+MenuBarSize; y+=25) painter.drawLine(0, y, 500, y);

    QWidget::paintEvent(event);
}

void gameWindow::mouseEvent(QMouseEvent * event)
{

}

void gameWindow::keyPressEvent(QKeyEvent * event)
{

    switch (event->key())
    {

    default:
        break;
    }

    QWidget::keyPressEvent(event);
}


void gameWindow::setupMenu(void)
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

void gameWindow::showAbout(void)
{
    QMessageBox::information(this, tr("Written by Fyr"),
                   tr("Based on qt4.8."));
}

void gameWindow::showHelp(void)
{
    QMessageBox::information(this, tr("Help"),
                   tr("To control the Dot or Wall."));
}

void gameWindow::startGame(void)
{
    bRun = true;
    timer->start(times);
}

void gameWindow::pauseGame(void)
{
    bRun = false;
    timer->stop();
}

