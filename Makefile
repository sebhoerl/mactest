CC = g++

PYTHON_CONFIG = python-config
BOOST_PYTHON = boost_python

PKG_CONFIG = pkg-config
PKG_PACKAGES = gtkmm-3.0 glfw3

PKG_INCLUDE = `${PKG_CONFIG} --cflags ${PKG_PACKAGES}`
PKG_LIBS = `${PKG_CONFIG} --libs ${PKG_PACKAGES}` -lGL -lGLU -lboost_system -l${BOOST_PYTHON} -lboost_thread

PYTHON_INCLUDE = `${PYTHON_CONFIG} --cflags`
PYTHON_LIBS = `${PYTHON_CONFIG} --libs`

INCLUDE = $(PKG_INCLUDE) $(PYTHON_INCLUDE)
LIBS = $(PKG_LIBS) $(PYTHON_LIBS)

all: python2
python2: test.cpp
	$(CC) -Wall -shared -fPIC $(INCLUDE) $(LIBS) test.cpp -o libtest.so
