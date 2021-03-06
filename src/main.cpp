// Copyright 2015 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifdef USE_QT

#include "ui/mainwindow/mainwindow.h"
#include <QApplication>

/*
 * This is the main function, which starts QT
 */
int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}

#else
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{
  signal(SIGSEGV, handler);   // install our handler
  cout << "Welcome to SFM" << endl;

  cout << "Done. Press enter to quit" << endl;
  string str;
  getline(cin, str);
  return 0;
}
#endif

