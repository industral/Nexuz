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

#include "App.hpp"

namespace Nexuz {

  App::App() {
    this -> init();
  }

  App::~App() {
  }

  void App::init() {
    this -> checkApplicationDir();

//    QSettings * settings = Settings::Instance() -> getInstance();

//            AccountInfo contact = { 1, 0, "alex", "qwerty" };
//            AccountInfo contact2 = { 2, 0, "alex1", "qwerty1" };
//
//            QList <QVariant> list;
//            list << qVariantFromValue(contact) << qVariantFromValue(contact2);
//
//            settings -> setValue("accounts", list);

//    QList < QVariant > list;
//    list << settings -> value("accounts").value<QList<QVariant> > ();
//
//    for (int i = 0; i < list.size(); ++i) {
//      AccountInfo contact = list.at(i).value<AccountInfo> ();
//      qDebug() << contact.accountType << contact.userName << contact.password;
//    }

//    AccountInfo contact = settings -> value("accounts").value<AccountInfo> ();
//    qDebug() << contact.accountType << contact.userName << contact.password;
  }

  // --------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------

  void App::checkApplicationDir() {
    const QString appPath = QDir::homePath() + QDir::separator() + USER_APPLICATION_FOLDER_NAME;

    if (!qDir.exists(appPath)) {
      qDir.mkdir(appPath);
    }

  }

}
