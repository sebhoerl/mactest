mkdir -p build
cd build
export PKG_CONFIG_PATH=/usr/X11/lib/pkgconfig
cmake ..
make
cp libtest.so ../libtest.so
cd ..
python3 test.py
