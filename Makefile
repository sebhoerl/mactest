CC = g++

PKG_CONFIG = pkg-config
PKG_PACKAGES = python3 gtkmm-3.0 glfw3 gl glu

INCLUDE = `${PKG_CONFIG} --cflags ${PKG_PACKAGES}`
LIBS = `${PKG_CONFIG} --libs ${PKG_PACKAGES}` -lboost_system -lboost_python3 -lboost_thread

all: python2
python2: test.cpp
	$(CC) -Wall -shared -fPIC $(INCLUDE) $(LIBS) test.cpp -o libtest.so
