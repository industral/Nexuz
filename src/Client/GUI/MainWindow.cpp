/*******************************************************************************
 * Copyright (c) 2010, Alex Ivasyuv                                            *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 *                                                                             *
 * 1. Redistributions of source code must retain the above copyright           *
 *    notice, this list of conditions and the following disclaimer.            *
 * 2. Redistributions in binary form must reproduce the above copyright        *
 *    notice, this list of conditions and the following disclaimer in the      *
 *    documentation and/or other materials provided with the distribution.     *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY Alex Ivasyuv ''AS IS'' AND ANY                 *
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE      *
 * DISCLAIMED. IN NO EVENT SHALL Alex Ivasyuv BE LIABLE FOR ANY DIRECT,        *
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES          *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;*
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF    *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.           *
 ******************************************************************************/

#include "MainWindow.hpp"

namespace Nexuz {
  namespace GUI {
    MainWindow::MainWindow(QWidget *parent) :
      QWidget(parent) {
    }

    MainWindow::~MainWindow() {
    }

    void MainWindow::load() {
      QVBoxLayout *layout = new QVBoxLayout;

      QMainWindow * mainWidget = (QMainWindow *) LoadUI::loadUI(":/forms/src/Client/GUI/design/MainWindow.ui");
      QWidget * contacts = LoadUI::loadUI(":/forms/src/Client/GUI/design/Contacts.ui");

      // add "About Player" handler
      connect(mainWidget -> findChild<QAction *> ("actionAbout"), SIGNAL(triggered()), this, SLOT(about()));

      mainWidget -> setCentralWidget(contacts);
      mainWidget -> show();
    }

    void MainWindow::about() {
      QWidget * widget = LoadUI::loadUI(":/forms/src/Client/GUI/design/About.ui");
      if (widget != NULL) {
        widget -> show();
      } else {
        cerr << "Failed to open widget" << endl;
      }
    }

  }
}
