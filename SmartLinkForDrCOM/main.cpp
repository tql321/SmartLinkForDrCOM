#include "SmartLinkForDrCOM.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SmartLinkForDrCOM window;
    window.show();
    return app.exec();
}
