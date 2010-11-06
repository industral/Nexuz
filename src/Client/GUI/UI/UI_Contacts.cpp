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

#include "UI_Contacts.hpp"

namespace Nexuz {
  namespace GUI {
    namespace UI {

      // --------------------------------------------------------------------
      // Public methods
      // --------------------------------------------------------------------

      Contacts::Contacts(QWidget *parent) :
        QWidget(parent) {
      }

      Contacts::~Contacts() {
      }

      void Contacts::init(QWidget * widget) {
        this -> widget = widget;

        this -> contactListEl = this -> widget-> findChild<QTreeWidget *> ("contactList");

        QList<QTreeWidgetItem *> contactItems;

        QTreeWidgetItem * account = new QTreeWidgetItem();
        QTreeWidgetItem * account2 = new QTreeWidgetItem();
        account -> setText(0, "asd");
        account -> setText(1, "asd");
        account -> setText(2, "asd");

        account2 -> setText(0, "AAA");
        account2 -> setText(1, "AAA");
        account2 -> setText(2, "AAAA");

        contactItems << account << account2;

        this -> contactListEl -> insertTopLevelItems(0, contactItems);

        this -> chatWindowWidget = Helper::Utils::loadUI(":/forms/src/Client/GUI/design/ChatWindow.ui");
        ChatWindow * chatWindow = UI::ChatWindow::Instance();
        chatWindow -> init(this -> chatWindowWidget);

        //        qDebug() << this -> contactListEl -> topLevelItemCount();

connect      (this -> contactListEl, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(contactClicked(QTreeWidgetItem *, int)));

      //        QList < QString > toggleLayouts;
      //        toggleLayouts << "customServer" << "repeatPassword";
      //
      //        this -> toggleLayoutsAccountType << "customServer";
      //        this -> toggleWidgetsAccountType << "checkUserName" << "checkUserNameOK";
      //
      //        // hide some layouts and widgets by default
      //        Nexuz::GUI::Helper::Utils::toggleLayout(this -> widget, toggleLayouts, false);
      //        Nexuz::GUI::Helper::Utils::toggleWidget(this -> widget, this -> toggleWidgetsAccountType, false);
      //
      //        // add/create account
      //        QButtonGroup * accountActionEl = this -> widget-> findChild<QButtonGroup *> ("buttonGroup");
      //        connect(accountActionEl, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(changeAccountAction(QAbstractButton *)));
      //
      //        // account type
      //        QComboBox * accountTypeEl = this -> widget-> findChild<QComboBox *> ("accoutType");
      //        connect(accountTypeEl, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAccountType(int)));
      //
      //        // track page changes in wizard
      //        connect(this -> widget, SIGNAL(currentIdChanged(int)), this, SLOT(wizardPageChanged(int)));
    }

    // --------------------------------------------------------------------
    // Private methods
    // --------------------------------------------------------------------

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------

    void Contacts::contactClicked(QTreeWidgetItem * item, int column) {
      this -> chatWindowWidget -> show();
    }

  }
}
}
