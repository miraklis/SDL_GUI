#ifndef EVENT_H
#define EVENT_H

#include <unordered_map>

namespace SDL_GUI {

    template<typename ...Args>
    using EventDelegate = std::function<void(Args...)>;

    template<typename ...Args>
    class Event final {
    private:
        std::unordered_map<int, EventDelegate<Args...>> handlers;
        unsigned long handlerNum{ 0 };
    public:
        int AddListener(EventDelegate<Args...> func) {
            handlers[++handlerNum] = func;
            return handlerNum;
        }

        void RemoveListener(int handleNum) {
            auto it = handlers.find(handleNum);
            if(it != handlers.end())
                handlers.erase(it);
        }

        void Raise(Args... params) {
            for(auto& handler : handlers) {
                handler.second(params...);
            }
        }

        void operator() (Args... params) {
            Raise(params...);
        }
    };

}

#endif // EVENT_H