#ifndef CBENGINE_APP_H
#define CBENGINE_APP_H


#include "window.h"


namespace cbengine {
    class App {
    public:
        App(const App& _app) = delete;
        App();
        ~App();

        App& operator =(const App& _app) = delete;

        void run();
    private:
        Window _win;
    };
}

#endif // CBENGINE_APP_H
