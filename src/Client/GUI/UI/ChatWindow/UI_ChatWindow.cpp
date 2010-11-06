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

#include "UI_ChatWindow.hpp"

namespace Nexuz {
  namespace GUI {
    namespace UI {

      // --------------------------------------------------------------------
      // Public methods
      // --------------------------------------------------------------------

      ChatWindow::ChatWindow(QWidget *parent) :
        CustomQTextEdit(parent) {
        this -> parent = parent;
      }

      ChatWindow::~ChatWindow() {
      }

      void ChatWindow::init(QWidget * widget) {
        cout << "init" << endl;

        this -> widget = widget;

        this -> chatInput = new ChatWindow();
        this -> chatInput2 = new QTextEdit();
        this -> chatInput2 -> setObjectName("chatInput2");
        this -> chatOutput = new QTextEdit();
        this -> chatOutput -> setReadOnly(true);

        QWidget * tabWidget = this -> widget -> findChild<QWidget *> ("tab");

        QVBoxLayout * layout = new QVBoxLayout();
        layout -> addWidget(this -> chatOutput);
        layout -> addWidget(this -> chatInput);
        layout -> addWidget(this -> chatInput2);

        layout -> setStretch(0, 4);
        layout -> setStretch(1, 1);

        delete tabWidget -> layout();
        tabWidget -> setLayout(layout);

        cout << this -> chatInput2 << endl;
      }

      // --------------------------------------------------------------------
      // Private methods
      // --------------------------------------------------------------------

      void ChatWindow::send() {
        qDebug() << "asdasd";

        cout << this -> chatInput2 << endl;

//        QTextEdit * t = this -> widget -> findChild<QTextEdit *> ("chatInput2");
//        qDebug() << t-> objectName();

        //                cout << this -> chatInput2 << endl;

        //         this -> chatInput2 -> toPlainText();
      }

    // --------------------------------------------------------------------
    // Slots
    // --------------------------------------------------------------------


    }
  }
}
