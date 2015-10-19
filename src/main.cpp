#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

/** @function main */
#ifdef USE_GUI
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();


  return a.exec();
}
#else
int main(int argc, char** argv)
{
    cout << "Welcome to SFM" << endl;

    cout << "Done. Press enter to quit" << endl;
    string str;
    getline(cin, str);
    return 0;
}
#endif