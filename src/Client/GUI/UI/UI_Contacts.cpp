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

      // Singleton
      Contacts * Contacts::_contacts = NULL;

      Contacts * Contacts::Instance() {
        if (_contacts == NULL) {
          _contacts = new Contacts();
        }
        return _contacts;
      }

      Contacts::~Contacts() {
      }

      void Contacts::init(QWidget * widget) {
        this -> widget = widget;
      }

      void Contacts::initRoster(const QList<QVariant> & rosterList) {
        this -> contactListEl = this -> widget-> findChild<QTreeWidget *> ("contactList");

        QList<QTreeWidgetItem *> contactItems;

        for (int i = 0; i < rosterList.size(); ++i) {
          QTreeWidgetItem * account = new QTreeWidgetItem();

          QString displayAccount = QString("%1 %2 (%3)").arg(rosterList.at(i).toMap().value("first_name").toString(),
              rosterList.at(i).toMap().value("last_name").toString(),
              rosterList.at(i).toMap().value("nickname").toString());

          account -> setText(1, displayAccount);

          contactItems << account;
        }

        this -> contactListEl -> insertTopLevelItems(0, contactItems);

        this -> chatWindowWidget = Helper::Utils::loadUI(":/forms/src/Client/GUI/design/ChatWindow.ui");
        ChatWindow * chatWindow = UI::ChatWindow::Instance();
        chatWindow -> init(this -> chatWindowWidget);

connect      (this -> contactListEl, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(contactClicked(QTreeWidgetItem *, int)));
    }

    // --------------------------------------------------------------------
    // Private methods
    // --------------------------------------------------------------------

    Contacts::Contacts(QWidget *parent) :
    QWidget(parent) {
    }

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------

    void Contacts::contactClicked(QTreeWidgetItem * item, int column) {
      this -> chatWindowWidget -> show();
    }

  }
}
}
