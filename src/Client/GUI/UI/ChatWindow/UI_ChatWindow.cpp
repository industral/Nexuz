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

      // Singleton
      ChatWindow * ChatWindow::_chatWindow = NULL;

      ChatWindow * ChatWindow::Instance() {
        if (_chatWindow == NULL) {
          _chatWindow = new ChatWindow();
        }
        return _chatWindow;
      }

      ChatWindow::~ChatWindow() {
      }

      void ChatWindow::init(QWidget * widget) {
        this -> widget = widget;

        this -> chatInput = Instance();
        this -> chatOutput = new QTextEdit();
        this -> chatOutput -> setReadOnly(true);

        QWidget * tabWidget = this -> widget -> findChild<QWidget *> ("tab");

        QVBoxLayout * layout = new QVBoxLayout();
        layout -> addWidget(this -> chatOutput);
        layout -> addWidget(this -> chatInput);

        layout -> setStretch(0, 4);
        layout -> setStretch(1, 1);

        delete tabWidget -> layout();
        tabWidget -> setLayout(layout);

        this -> netAccounts = Nexuz::Network::NetAccounts::Instance();
      }

      void ChatWindow::initChat(const QString & id) {
        QTabWidget * tabWidget = this -> widget -> findChild<QTabWidget *> ("tabWidget");

        const int count = tabWidget -> count();
        if (count == 1) {
          tabWidget -> widget(0) -> setProperty("id", id);
        }
      }

      void ChatWindow::input(const QString & message) {
        const QString origChatOutput = this -> chatOutput -> toPlainText();
        this -> chatOutput -> setPlainText(origChatOutput + message);
      }

      // --------------------------------------------------------------------
      // Private methods
      // --------------------------------------------------------------------

      ChatWindow::ChatWindow(QWidget *parent) {
      }

      void ChatWindow::send() {
        const QString typedText = this -> chatInput -> toPlainText();
        this -> chatInput -> clear();

        this -> input(typedText);

        NexuzProtocol protocolData;
        protocolData.protocolName = {'N', 'E', 'X', 'U', 'Z'};
        protocolData.dataType = {'T', 'E', 'X', 'T'};
        protocolData.size = typedText.size();

        strcpy(protocolData.data, typedText.toStdString().c_str());

        QTabWidget * tabWidget = this -> widget -> findChild<QTabWidget *> ("tabWidget");
        const QString id = tabWidget -> currentWidget() -> property("id").toString();
        this -> netAccounts -> write(id, protocolData, sizeof(NexuzProtocol));
      }

    }
  }
}
