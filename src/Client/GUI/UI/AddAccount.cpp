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

#include "AddAccount.hpp"

namespace Nexuz {
  namespace GUI {
    namespace UI {

      AddAccount::AddAccount(QWidget *parent) :
        QWidget(parent) {
      }

      AddAccount::~AddAccount() {
      }

      void AddAccount::init(QWidget * widget) {
        this -> widget = widget;

        QList < QString > toggleLayouts;
        toggleLayouts << "customServer" << "repeatPassword";

        this -> toggleLayoutsAccountType << "customServer";
        this -> toggleWidgetsAccountType << "checkUserName" << "checkUserNameOK";

        // hide some layouts and widgets by default
        Nexuz::GUI::Helper::Utils::toggleLayout(this -> widget, toggleLayouts, false);
        Nexuz::GUI::Helper::Utils::toggleWidget(this -> widget, this -> toggleWidgetsAccountType, false);

        // add/create account
        QButtonGroup * accountActionEl = this -> widget-> findChild<QButtonGroup *> ("buttonGroup");
        connect(accountActionEl, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(changeAccountAction(QAbstractButton *)));

        // account type
        QComboBox * accountTypeEl = this -> widget-> findChild<QComboBox *> ("accoutType");
        connect(accountTypeEl, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAccountType(int)));

        // track page changes in wizard
        connect(this -> widget, SIGNAL(currentIdChanged(int)), this, SLOT(wizardPageChanged(int)));
      }

      void AddAccount::changeAccountType(int index) {
        bool toggleView = false;

        if (index == 1) {
          toggleView = true;
        }

        Nexuz::GUI::Helper::Utils::toggleLayout(this -> widget, this -> toggleLayoutsAccountType, toggleView);
      }

      void AddAccount::changeAccountAction(QAbstractButton * button) {
        this -> toggleAccountActionType(button -> objectName());
      }

      void AddAccount::toggleAccountActionType(const QString & type) {
        QList < QString > widgetList;

        bool toggleView = false;

        if (type == "createNew") {
          toggleView = true;
        }

        Nexuz::GUI::Helper::Utils::toggleLayout(this -> widget, "repeatPassword", toggleView);
        Nexuz::GUI::Helper::Utils::toggleWidget(this -> widget, this -> toggleWidgetsAccountType, toggleView);
      }

      void AddAccount::wizardPageChanged(int pageId) {
        if (pageId == 1) {

        }
      }

    }
  }
}
