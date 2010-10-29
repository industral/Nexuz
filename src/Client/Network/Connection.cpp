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

#include "Connection.hpp"

namespace Nexuz {
  namespace Network {
    Connection::Connection(QWidget *parent) :
      QWidget(parent) {
    }

    Connection::~Connection() {
    }

    bool Connection::auth() {
      this -> manager = new QNetworkAccessManager();

      QNetworkRequest request;
      request.setUrl(QUrl("http://localhost:5984"));

      this -> reply = this -> manager -> get(request);
      connect(reply, SIGNAL(readyRead()), this, SLOT(httpFinished()));
      connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));

      return true;
    }

    void Connection::httpFinished() {
      QString response = QString("[") + QString(this -> reply -> readAll().data()) + QString("]");

      QScriptEngine engine;
      QScriptValue sc = engine.evaluate(response);

      cout << sc.property("0").property("couchdb").toString().toStdString() << endl;

//      QScriptValue sv;
//      Helper::Utils::parseJSON(/*QString(this -> reply -> readAll().data())*/"{'couchdb': '1'}", sv, a);
//      //      qDebug() << sv.toString();
//
//      cout << sv.property("0").property("couchdb").toString().toStdString() << endl;

      //      if (sc.property("result").isArray()) {
      //        QScriptValueIterator it(sc.property("result"));
      //        while (it.hasNext()) {
      //          it.next();
      //          qDebug("Nick %s", it.value().property("nick").toString().toStdString().c_str());
      //        }
      //      }

    }

    void Connection::slotError(QNetworkReply::NetworkError error) {

      QMetaObject meta = QNetworkReply::staticMetaObject;
      for (int i = 0; i < meta.enumeratorCount(); ++i) {
        QMetaEnum m = meta.enumerator(i);
        if (m.name() == QLatin1String("NetworkError")) {
          cerr << m.valueToKey(error) << endl;
          break;
        }
      }

    }

  }
}

