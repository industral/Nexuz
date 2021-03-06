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

#ifndef _NEXUZ_GUI_UI_MANAGEACCOUNTS_HPP_
#define _NEXUZ_GUI_UI_MANAGEACCOUNTS_HPP_

#include <include.hpp>
#include "../../App/Accounts.hpp"

namespace Nexuz {
  namespace GUI {
    namespace UI {

      class ManageAccounts: public QWidget {
        Q_OBJECT

        public:
          /**
           * Default constructor.
           */
        ManageAccounts(QWidget *parent = 0);

          /**
           * Default destructor.
           */
          ~ManageAccounts();

          /**
           * Init ManageAccounts widget.
           *
           * @param widget pointer to ariginal loaded widget from ui
           */
          void init(QWidget * widget);
        private slots:
          void accountClicked(QTreeWidgetItem * item, int column);
          void removeAccount();
        private:
          void addEvents();
          void refresh();

          QWidget * widget;
          QTreeWidget * accountsListEl;
    };
  }
}
}

#endif
