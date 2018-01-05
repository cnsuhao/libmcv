#include <iostream>
#include "../../src/modules/ML/Common.h"
int main() {
  MnistClassifier mc = MnistClassifier();
  mc.construct_network();
  const std::string data_path = ".";
  mc._load_data(data_path);
  mc.train(30,10,1.0);
  return 0;
}