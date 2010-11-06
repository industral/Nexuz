CONFIG      += uitools qt warn_on DEBUG_MODE #RELEASE_MODE
QT          += network script
RESOURCES   = Nexuz.qrc

SOURCES     = src/Client/GUI/Helper/Utils.cpp \
              src/Client/GUI/MainWindow.cpp \
              src/Client/Network/Connection.cpp \
              src/Client/Process.cpp \
              src/Client/GUI/UI/UI_AddAccount.cpp \
              src/Client/GUI/UI/UI_Contacts.cpp \
              src/Client/GUI/UI/ChatWindow/CustomChatWindow.cpp \
              src/Client/GUI/UI/ChatWindow/UI_ChatWindow.cpp \
              src/Client/GUI/UI/UI_ManageAccounts.cpp \
              src/Client/App/Settings.cpp \
              src/Client/App/StoredObjects.cpp \
              src/Client/App/App.cpp \
              src/Client/App/Accounts.cpp \
              src/Client/main.cpp

HEADERS     = src/Client/include.hpp \
              src/Client/GUI/MainWindow.hpp \
              src/Client/GUI/Helper/Utils.hpp \
              src/Client/Network/Connection.hpp \
              src/Client/GUI/UI/UI_AddAccount.hpp \
              src/Client/GUI/UI/UI_Contacts.hpp \
              src/Client/GUI/UI/ChatWindow/CustomChatWindow.hpp \
              src/Client/GUI/UI/ChatWindow/UI_ChatWindow.hpp \
              src/Client/GUI/UI/UI_ManageAccounts.hpp \
              src/Client/GUI/UI/include.hpp \
              src/Client/App/Settings.hpp \
              src/Client/App/StoredObjects.hpp \
              src/Client/App/App.hpp \
              src/Client/App/Accounts.hpp \
              src/Client/Process.hpp \
              src/Client/include.hpp

Libraries = 

StaticLibraries = 

CONFIG(DEBUG_MODE) {
  QMAKE_CXXFLAGS += -ggdb
  QMAKE_CFLAGS += -ggdb

  for(lib, Libraries) {
    LIBS += -l$$lib
  }
} else {
  QMAKE_CXXFLAGS += -O3
  QMAKE_CFLAGS += -O3
  
  for(lib, StaticLibraries) {
    LIBS += "/usr/lib/lib$$lib".a
  }
}

INCLUDEPATH = src/Client
OBJECTS_DIR = tmp/objects
MOC_DIR = tmp/moc
RCC_DIR =  tmp/rcc