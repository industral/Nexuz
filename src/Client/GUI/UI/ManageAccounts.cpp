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

#include "ManageAccounts.hpp"

namespace Nexuz {
  namespace GUI {
    namespace UI {

      // --------------------------------------------------------------------
      // Public methods
      // --------------------------------------------------------------------

      ManageAccounts::ManageAccounts(QWidget *parent) :
        QWidget(parent) {
      }

      ManageAccounts::~ManageAccounts() {
      }

      void ManageAccounts::init(QWidget * widget) {
        this -> widget = widget;
        this -> accountsListEl = this -> widget-> findChild<QTreeWidget *> ("accountsList");

        // show accounts list
        this -> refresh();

        // add events
        this -> addEvents();
      }

      void ManageAccounts::refresh() {
        Accounts accounts;

        this -> accountsListEl -> clear();

        QList < AccountInfo > accountsList = accounts.getList();
        QList<QTreeWidgetItem *> accountItems;

        for (int i = 0; i < accountsList.size(); ++i) {
          QTreeWidgetItem * account = new QTreeWidgetItem();
          AccountInfo accountItem = accountsList.at(i);

          account -> setText(0, accountItem.userName);
          account -> setText(1, accountItem.accountType ? "Internal" : "Global Internet");
          account -> setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
          account -> setCheckState(0, Qt::Checked);
          account -> setData(0, 1, QVariant(accountItem.id));

          accountItems << account;
        }

        this -> accountsListEl -> insertTopLevelItems(0, accountItems);
      }

      // --------------------------------------------------------------------
      // Private methods
      // --------------------------------------------------------------------

      void ManageAccounts::addEvents() {
        QPushButton * deleteAccountEl = this -> widget-> findChild<QPushButton *> ("deleteAccount");

        connect (this -> accountsListEl, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(accountClicked(QTreeWidgetItem *, int)));
        connect(deleteAccountEl, SIGNAL(clicked()), this, SLOT(removeAccount()));
      }

      // --------------------------------------------------------------------
      // Slots
      // --------------------------------------------------------------------

      void ManageAccounts::accountClicked(QTreeWidgetItem * item, int column) {
        qDebug() << item -> data(0, 1);
      }

      void ManageAccounts::removeAccount() {
        const int accountId = this -> accountsListEl -> currentItem() -> data(0, 1).toInt();

        Accounts accounts;
        bool ok = accounts.remove(accountId);

        if (ok) {
          this -> accountsListEl -> takeTopLevelItem(this -> accountsListEl -> indexOfTopLevelItem(
              this -> accountsListEl -> currentItem()));
        }
      }

    }
  }
}
