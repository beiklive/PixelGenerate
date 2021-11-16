#include "PixelGenerate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PixelGenerate w;
    w.show();
    return a.exec();
}
