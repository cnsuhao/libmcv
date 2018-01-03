#ifndef _LIBMCV_MODULES_COMMON_CLASSIFIER_H
#define _LIBMCV_MODULES_COMMON_CLASSIFIER_H

#include "Classifier.h"
#include "../Logger/Logger.h"

class FaceDetector : public BaseClassifier {
    
};

class MnistClassifier : public BaseClassifier {

public:
    MnistClassifier();
    MnistClassifier(tiny_dnn::core::backend_t backend_type);
    // Load Default Network
    void construct_network();
    void train();
    void predict();
private:
    tiny_dnn::network<tiny_dnn::sequential> nn;
    tiny_dnn::core::backend_t backend_type;
    // connection table [Y.Lecun, 1998 Table.1]
    bool tbl[];
};

class CifarClassifier : public BaseClassifier {

};

#endif