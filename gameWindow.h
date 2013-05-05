#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <Walls.h>
#include <Dot.h>
#include <QtGui>

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    gameWindow(QWidget * parent = 0);
    ~gameWindow(void);

protected slots:
    void refreshTimer(void);
    void showAbout(void);
    void showHelp(void);
    void startGame(void);
    void pauseGame(void);

protected:
    void keyPressEvent(QKeyEvent * event);
    void paintEvent(QPaintEvent * event);

private:
    void setupMenu(void);

private:

    bool IsDie;
    bool bRun;
    QTimer * timer;
    int times;
    int MenuBarSize;
};

#endif
