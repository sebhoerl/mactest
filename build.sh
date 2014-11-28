mkdir -p build
cd build
cmake ..
make
cp libtest.dylib ../libtest.so
cd ..
python test.py
