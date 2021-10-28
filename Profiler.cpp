#include <dlfcn.h>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>

std::mutex mtx;

std::unordered_map<std::string, std::size_t> calls;

void __attribute__((no_instrument_function)) show(const std::string& action, void* callerFn, void* callAddress) {
    Dl_info info;
    dladdr(callerFn, &info);

    std::scoped_lock l(mtx);
    std::cerr << "\033[33m" << std::this_thread::get_id() << ": " << action << " " << info.dli_sname << " (" << callAddress << ")\033[0m" << std::endl;
    calls[info.dli_sname]++;

    /*for (const auto& [func, numCalls] : calls) {
        std::cerr << "\t\033[34m" << numCalls / 2 << " calls to " << func << "\033[0m" << std::endl;
    }*/
}

extern "C" {
void __attribute__((no_instrument_function)) __cyg_profile_func_enter(void* callerFn, void* callAddress) {
    show("enter", callerFn, callAddress);
}

void __attribute__((no_instrument_function)) __cyg_profile_func_exit(void* callerFn, void* callAddress) {
    show("exit", callerFn, callAddress);
}
}
