
#include <Sugarscape.cpp>
#include <ControlWidget.h>
#include <ControlWidgetSlim.h>
#include <QMenuBar>

int main(int argc,   char **argv)
{
    QApplication App(argc, argv);

    // Create and Add Slim View Widget within Viewport
    ControlWidgetSlim* ControlSlimView = new ControlWidgetSlim();
    ControlSlimView->setWindowTitle("Viewport");
    ControlSlimView->setMinimumSize(425, 500);
    ControlSlimView->setMaximumSize(425, 500);

    ControlSlimView->show();
    return App.exec();

}

void windowSetup()
{

}
