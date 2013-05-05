#include <QApplication>
#include "gameWindow.h"


int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    gameWindow gwindow;

    gwindow.show();
    return app.exec();
}
