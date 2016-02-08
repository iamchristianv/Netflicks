#include <QApplication>
#include "Netflicks.h"
#include "LoginScreen.h"

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  Netflicks n(argc, argv);
  LoginScreen ls(&n);
  ls.show();
  return a.exec();
}
