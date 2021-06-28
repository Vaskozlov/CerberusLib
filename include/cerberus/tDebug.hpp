#include <chrono>
#include <cerberus/cerberus.h>

namespace  cerb
{
    template<typename _TimeType = std::chrono::high_resolution_clock::time_point, auto _GetTime = std::chrono::high_resolution_clock::now, typename _ResultType = std::chrono::duration<double>>
    class tDebug{
        const char *name;
        _TimeType _begin = _GetTime();
    
    public:
        always_inline void start(){
            _begin = _GetTime();
        }

        always_inline void stop(){
            _ResultType elapsed = _GetTime() - _begin;
            cerbPrintf("%s elapsed in %e\n", name, elapsed.count());
        }

    public:
        tDebug(const char *profileName) : name(profileName) {}
        ~tDebug() { stop(); }
    };
    
} // namespace  cerb
