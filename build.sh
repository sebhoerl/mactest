mkdir -p build
cd build
export PKG_CONFIG_PATH=/usr/X11/lib/pkgconfig
cmake ..
make
cp libtest.dylib ../libtest.so
cd ..
python test.py
