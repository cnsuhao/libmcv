#include <iostream>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation_layer;

void convnet(void) {
    network<mse, adagrad> nn;
    nn  <<  convolutional_layer<tanh> (32, 32, 5, 1, 6)
        <<  average_pooling_layer<tanh> (28, 28, 6, 2)
        <<  convolutional_layer<tanh> (14, 14, 5, 6, 16)
        <<  average_pooling_layer<tanh> (10, 10, 16, 2)
        << convolutional_layer<tanh> (5, 5, 5, 16, 120)
        << fully_connected_layer<tanh> (120,10);
    std::cout << "Load Models" << std::endl;
    std::vector<label_t> train_labels, test_labels;
    std::vector<vec_t> train_images, test_images;
    
    parse_mnist_labels("train-labels.idx1-ubyte", & train_labels);
    parse_mnist_images("train-images.idx3-ubyte", & train_images);
    parse_mnist_labels("t10k-labels.idx1-ubyte", & train_labels);
    parse_mnist_images("t10k-images.idx3-ubyte", & train_images);

    std::cout << "start learning" << std::endl;
    boost::progress(train_images.size());
    boost::timer t;

    int minibatch_size = 10;
    int num_epochs = 30;
    nn.optimizer().alpha * = std::sqrt(minibatch_size);
    auto on_enumerate_epoch = [&]() {
        std::cout << t.elapsed() << "s elapsed." << std::endl;
        tiny_dnn::result res = nn.test(test_images, test_labels);
        std::cout << res.num_success << "/" << res.num_total << std::endl;
        disp.restart(train_images.size());
        t.restart();
    };
    
    auto on_enumerate_minibatch = [&]() {
        disp += minibatch_size;
    };

    nn.train(train_images, train_labels, minibatch_size, num_epochs,
             on_enumerate_minibatch, on_enumerate_epoch);
    
    std::out << "end training" << std::endl;

    nn.test(test_images, test_labels).print_detail(std::out);

    std::ofstream ofs("LeNets-weights");
    ofs<<nn;
}

int main() {
    convnet();
}