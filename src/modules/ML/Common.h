#ifndef _LIBMCV_MODULES_COMMON_CLASSIFIER_H
#define _LIBMCV_MODULES_COMMON_CLASSIFIER_H

#include "iostream"
#include "Classifier.h"
#include "../Logger/Logger.h"

class FaceDetector : public BaseClassifier {
    
};

class MnistClassifier : public BaseClassifier {

public:
    MnistClassifier();
    MnistClassifier(tiny_dnn::core::backend_t backend_type);
    ~MnistClassifier();
    // Load Default Network
    void construct_network();
    void train(const int n_train_epochs, const int n_minibatch, double learning_rate);
    void predict();
    void _load_data(const std::string &data_dir_path);
private:
    std::vector<tiny_dnn::label_t> train_labels, test_labels;
    std::vector<tiny_dnn::vec_t> train_images, test_images;
    tiny_dnn::network<tiny_dnn::sequential> nn;
    tiny_dnn::core::backend_t backend_type;
    // connection table [Y.Lecun, 1998 Table.1]
    bool *tbl;
    std::shared_ptr<spdlog::logger> logger;  
};

class CifarClassifier : public BaseClassifier {

};

#endif