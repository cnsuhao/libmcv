echo "Building libjpeg-turbo"
cd ../lib/libjpeg-turbo
chmod +x simd/nasm_lt.sh
autoreconf -fiv
mkdir build
cd build
../configure
make
cp jconfig.h ../
