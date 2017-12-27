echo "Building libjpeg-turbo"
cd lib/libjpeg-turbo
autoreconf --fiv
mkdir build
cd build
../configure
make
cp jconfig.h ../