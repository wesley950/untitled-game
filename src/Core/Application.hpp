//
// Created by wesley on 15/04/22.
//

#ifndef UNTITLED_APPLICATION_HPP
#define UNTITLED_APPLICATION_HPP

class Application {
public:
    virtual ~Application() = default;
    virtual void run() = 0;

    static Application* get_instance() { return s_Instance; }

protected:
    static Application* s_Instance;
};

Application* create_application();

#endif //UNTITLED_APPLICATION_HPP
