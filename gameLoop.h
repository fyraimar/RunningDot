#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#define MENUHEIGHT 20
#include <Walls.h>
#include <Dot.h>
#include <QtGui>

class gameLoop : public QMainWindow
{
    Q_OBJECT

public:
    gameLoop(QWidget * parent = 0);
    ~gameLoop(void);

protected slots:
    void refreshTimer();
    void restartGame();

protected:
    void keyPressEvent(QKeyEvent * event);
    void paintEvent(QPaintEvent * event);
    //void mouseEvent(QMouseEvent * event);

private:
    void setupMenu(void);
    bool checkWin();
    bool checkLoose();

private:
    Dot dot;
    Walls wall;
    void setInit();
    int ifWin;
    int direct;
};

#endif
