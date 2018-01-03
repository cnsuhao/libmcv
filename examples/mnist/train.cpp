#include <iostream>
#include "Common.h"
int main() {
  MnistClassifier mc = new MnistClassifier();
  mc.construct_network();
  mc._load_data('.');
  mc.train();
  return 0;
}