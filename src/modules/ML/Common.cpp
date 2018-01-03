#include "Common.h"
MnistClassifier::MnistClassifier() {
    this->logger = Logger::getLogger();
    tbl = {
        // clang-format off
        true, false, false, false, true, true, true, false, false, true, true, true, true, false, true, true,
        true, true, false, false, false, true, true, true, false, false, true, true, true, true, false, true,
        true, true, true, false, false, false, true, true, true, false, false, true, false, true, true, true,
        false, true, true, true, false, false, true, true, true, true, false, false, true, false, true, true,
        false, false, true, true, true, false, false, true, true, true, true, false, true, true, false, true,
        false, false, false, true, true, true, false, false, true, true, true, true, false, true, true, true
        // clang-format on
    };
}

MnistClassifier::MnistClassifier(tiny_dnn::core::backend_t backend_type) {
    this->backend_type = backend_type;
}

void MnistClassifier::construct_network() {
    using fc = tiny_dnn::layers::fc;
    using conv = tiny_dnn::layers::conv;
    using ave_pool = tiny_dnn::layers::ave_pool;
    using tanh = tiny_dnn::activation::tanh;

    using tiny_dnn::core::connection_table;
    using padding = tiny_dnn::padding;

    nn  <<  conv(32, 32, 5, 1, 6,   // C1, 1@32x32-in, 6@28x28-out
            padding::valid, true, 1, 1, backend_type)
        <<  tanh()
        <<  ave_pool(28, 28, 6, 2)   // S2, 6@28x28-in, 6@14x14-out
        <<  tanh()
        <<  conv(14, 14, 5, 6, 16,   // C3, 6@14x14-in, 16@10x10-out
            connection_table(tbl, 6, 16),
            padding::valid, true, 1, 1, backend_type)
     << tanh()
     << ave_pool(10, 10, 16, 2)  // S4, 16@10x10-in, 16@5x5-out
     << tanh()
     << conv(5, 5, 5, 16, 120,   // C5, 16@5x5-in, 120@1x1-out
             padding::valid, true, 1, 1, backend_type)
     << tanh()
     << fc(120, 10, true, backend_type)  // F6, 120-in, 10-out
     << tanh();
}

void MnistClassifier::_load_data(const std::string &data_dir_path) {
    logger->info("loading models");
    tiny_dnn::parse_mnist_labels(data_dir_path + "/train-labels.idx1-ubyte",
                               &train_labels);
    tiny_dnn::parse_mnist_images(data_dir_path + "/train-images.idx3-ubyte",
                               &train_images, -1.0, 1.0, 2, 2);
    tiny_dnn::parse_mnist_labels(data_dir_path + "/t10k-labels.idx1-ubyte",
                               &test_labels);
    tiny_dnn::parse_mnist_images(data_dir_path + "/t10k-images.idx3-ubyte",
                               &test_images, -1.0, 1.0, 2, 2);
    logger->info("models loaded");
}

void MnistClassifier::train(const int n_train_epochs, const int n_minibatch, double learning_rate) {
    this->construct_network();
    logger->info("training config: train_epochs: {:05d}, minibatch: {:05d}, learning rate: {:05d}", n_train_epochs, n_minibatch, learning_rate);
    logger->info("start training");
    tiny_dnn::adagrad optimizer;
    optimizer.alpha *= std::min(tiny_dnn::float_t(4), static_cast<tiny_dnn::float_t>(
        sqrt(n_minibatch) * learning_rate
    ));
    int epoch = 1;
    tiny_dnn::timer t;
    auto on_enumerate_epoch = [&]() {
        logger->info("Epoch: {:02d}/{:06d} finished. {3} sec elapsed.", epoch, n_train_epochs, t.elapsed());
        ++epoch;
        tiny_dnn::result res = nn.test(test_images, test_labels);
        logger->info("success rate: {:05d}/{:05d}", res.num_success, res.num_total);
        t.restart();
    };
    auto on_enumerate_minibatch = [&]() {

    };
    nn.train<tiny_dnn::mse>(optimizer, train_images,train_labels, n_minibatch, n_train_epochs, on_enumerate_minibatch, on_enumerate_epoch);
    nn.test(test_images, test_labels).print_detail(std::cout);
}