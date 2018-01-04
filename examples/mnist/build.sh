clang++ -std=c++14 -I ../../lib -I ../../src/modules/ML -L ../../build/ -lmcvImage -lmcvLogger -lmcvML -o train train.cpp 
export LD_LIBRARY_PATH=/home/sfermi/Documents/code/libmcv/build/