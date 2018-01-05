#ifndef _LIBMCV_MODULES_CLASSIFIER_H_
#define _LIBMCV_MODULES_CLASSIFIER_H_

#include "../Logger/Logger.h"
#include "tiny_dnn/tiny_dnn.h"

class BaseClassifier {
protected:

public:
    BaseClassifier();
    void train();
    void predict();
    ~BaseClassifier();
};

#endif