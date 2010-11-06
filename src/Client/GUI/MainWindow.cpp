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

      this -> mainWidget = (QMainWindow *) Helper::Utils::loadUI(":/forms/src/Client/GUI/design/MainWindow.ui");
      QWidget * contacts = Helper::Utils::loadUI(":/forms/src/Client/GUI/design/Contacts.ui");

      // add events
      this -> addEvents();

      this -> mainWidget -> setCentralWidget(contacts);
      this -> mainWidget -> show();

      UI::Contacts * uiContacts = new UI::Contacts();
      uiContacts -> init(contacts);
    }

    void MainWindow::addEvents() {
      // create signals mapper
      this -> signalMapper = new QSignalMapper(this);

      // get actions
      QAction * actionAbout = this -> mainWidget -> findChild<QAction *> ("actionAbout");
      QAction * actionManageAccounts = this -> mainWidget -> findChild<QAction *> ("actionManageAccounts");

      // map actions
      this -> signalMapper -> setMapping(actionAbout, QString("About"));
      this -> signalMapper -> setMapping(actionManageAccounts, QString("ManageAccounts"));

      // connect actions
      connect(actionAbout, SIGNAL(triggered()), this -> signalMapper, SLOT(map()));
      connect(actionManageAccounts, SIGNAL(triggered()), this -> signalMapper, SLOT(map()));

      // connect signal mapper
connect    (signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(doAction(const QString &)));
  }

  void MainWindow::doAction(const QString & action) {
    //TODO: one instance
    QWidget * widget = Helper::Utils::loadUI(":/forms/src/Client/GUI/design/" + action + ".ui");

    if (widget != NULL) {
      widget -> show();

      // attach events on widgets
      if (action == "ManageAccounts") {
        QPushButton * addAccount = widget -> findChild<QPushButton *> ("addAccount");

        UI::ManageAccounts * account = new UI::ManageAccounts();
        account -> init(widget);

        this -> signalMapper -> setMapping(addAccount, QString("AddAccount"));
        connect(addAccount, SIGNAL(clicked()), this -> signalMapper, SLOT(map()));
      } else if (action == "AddAccount") {
        UI::AddAccount * account = new UI::AddAccount();
        account -> init(widget);
      }

    } else {
      cerr << "Failed to open widget" << endl;
    }
  }

}
}
