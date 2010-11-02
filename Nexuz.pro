CONFIG      += uitools qt warn_on DEBUG_MODE #RELEASE_MODE
QT          += network script
RESOURCES   = Nexuz.qrc

SOURCES     = src/Client/GUI/Helper/Utils.cpp \
              src/Client/GUI/MainWindow.cpp \
              src/Client/Network/Connection.cpp \
              src/Client/Process.cpp \
              src/Client/GUI/UI/AddAccount.cpp \ 
              src/Client/main.cpp

HEADERS     = src/Client/include.hpp \
              src/Client/GUI/MainWindow.hpp \
              src/Client/GUI/Helper/Utils.hpp \
              src/Client/Network/Connection.hpp \
              src/Client/GUI/UI/AddAccount.hpp \
              src/Client/Process.hpp

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