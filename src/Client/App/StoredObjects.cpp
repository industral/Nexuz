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

/**
 * @see http://wiki.forum.nokia.com/index.php/Saving_custom_structures_and_classes_to_QSettings
 */

#include "StoredObjects.hpp"

namespace Nexuz {

  // Singleton
  StoredObjects * StoredObjects::_storedObjects = NULL;

  StoredObjects * StoredObjects::Instance() {
    if (_storedObjects == NULL) {
      _storedObjects = new StoredObjects();
      _storedObjects -> init();
    }
    return _storedObjects;
  }

  StoredObjects::~StoredObjects() {
  }

  // --------------------------------------------------------------------
  // Private methods
  // --------------------------------------------------------------------

  StoredObjects::StoredObjects() {
  }

  void StoredObjects::init() {
    qRegisterMetaType<AccountInfo> ("AccountInfo");
    qRegisterMetaTypeStreamOperators<AccountInfo> ("AccountInfo");
  }

}

QDataStream &operator<<(QDataStream &out, const AccountInfo &obj) {
  out << obj.id << obj.accountType << obj.userName << obj.password;
  return out;
}

QDataStream &operator>>(QDataStream &in, AccountInfo &obj) {
  in >> obj.id >> obj.accountType >> obj.userName >> obj.password;
  return in;
}
