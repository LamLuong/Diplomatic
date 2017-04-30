#include <QApplication>

#include "ui_main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UI_Window window;
    window.show();
    return app.exec();
}
