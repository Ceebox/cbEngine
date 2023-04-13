#include <iostream>

#include "app.h"


int main() {
    try {
        cbengine::App app;
        app.run();
    } catch(const std::runtime_error& _error) {
        std::cerr << _error.what() << std::endl;
    }

    return 0;
}
