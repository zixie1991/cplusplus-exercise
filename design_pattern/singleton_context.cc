#include <assert.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
using std::cout;
using std::endl;
// a light weight global flags
class Context {
    public:
        static Context& get_instance();
        ~Context();
        int get_int(std::string key);
        double get_double(std::string key);
        bool get_bool(std::string key);
        std::string get_string(std::string key);
        void set(std::string key, int value);
        void set(std::string key, double value);
        void set(std::string key, bool value);
        void set(std::string key, const char* value);
    private:
        Context();
        std::map<std::string, std::string> ctx_;
};
Context& Context::get_instance() {
    static Context context_;
    return context_;
}
Context::Context() {}
Context::~Context() {}
int Context::get_int(std::string key) {
    return atoi(get_string(key).c_str());
}
double Context::get_double(std::string key) {
    return atof(get_string(key).c_str());
}
bool Context::get_bool(std::string key) {
    return get_string(key).compare("true") == 0;
}
std::string Context::get_string(std::string key) {
    auto iter = ctx_.find(key);
    assert(iter != ctx_.end());
    return iter->second;
}
void Context::set(std::string key, int value) {
    ctx_[key] = std::to_string(value);
}
void Context::set(std::string key, double value) {
    ctx_[key] = std::to_string(value);
}
void Context::set(std::string key, bool value) {
    ctx_[key] = (value) ? "true" : "false";
}
void Context::set(std::string key, const char* value) {
    ctx_[key] = value;
}
int main() {
    Context context = Context::get_instance();
    context.set("a", 1);
    context.set("b", 2.0);
    context.set("c", true);
    context.set("d", "d");
    cout << context.get_int("a") << endl;
    cout << context.get_double("b") << endl;
    cout << context.get_bool("c") << endl;
    cout << context.get_string("d") << endl;
    return 0;
}
