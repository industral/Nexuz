#include "MainWindow.hpp"

using namespace Nexuz::GUI;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow * mainWindow = new MainWindow();
  mainWindow -> load();

  delete mainWindow;
  mainWindow = NULL;

  return app.exec();
}
