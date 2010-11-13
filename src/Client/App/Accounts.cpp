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

#include "Accounts.hpp"

namespace Nexuz {

  Accounts::Accounts() {
    this -> settings = Settings::Instance() -> getInstance();
  }

  Accounts::~Accounts() {
  }

  QList<AccountInfo> Accounts::getList() {
    QList < QVariant > list;
    QList < AccountInfo > outputList;

    list << this -> settings -> value("accounts").value<QList<QVariant> > ();

    for (int i = 0; i < list.size(); ++i) {
      AccountInfo account = list.at(i).value<AccountInfo> ();
      outputList << account;
    }

    return outputList;
  }

  void Accounts::add(int accountType, const QString & userName, const QString & password, const QString & serverName) {
    if (accountType == 0) {
      // fetch a list of existed accounts
      QList < AccountInfo > accountList = this -> getList();

      // generate UUID
      QDateTime t;

      // create new account obj
      AccountInfo contact = { t.toTime_t(), accountType, userName, password };

      // add to existed list
      accountList << contact;

      // save
      this -> save(accountList);
    }

  }

  bool Accounts::remove(int id) {
    bool returnValue = false;

    QList < AccountInfo > accounts = this -> getList();

    for (int i = 0; i < accounts.size(); ++i) {
      AccountInfo account = accounts.at(i);
      if (account.id == id) {
        accounts.removeAt(i);

        returnValue = true;
      }
    }

    this -> save(accounts);
    return returnValue;
  }

  void Accounts::save(const QList<AccountInfo> & accountsData) {
    QList < QVariant > outputList;

    for (int i = 0; i < accountsData.size(); ++i) {
      AccountInfo account = accountsData.at(i);
      outputList << qVariantFromValue(account);
    }

    this -> settings -> setValue("accounts", outputList);
  }

// --------------------------------------------------------------------
// Private methods
// --------------------------------------------------------------------


}
