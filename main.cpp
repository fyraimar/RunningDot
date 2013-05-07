#include <QApplication>
#include "gameLoop.h"


int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    gameLoop gmainloop;

    gmainloop.show();
    return app.exec();
}
