#include "Common.h"
MnistClassifier::MnistClassifier() {
    tbl[]= {
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