#include <future>
#include <iostream>
#include <vector>

int turkey(int x) {
    return x + 5;
}

int sheep(int x) {
    std::vector<std::future<int>> resultFutures;

    for (int i = 0; i < x; i++) {
        resultFutures.emplace_back(std::async(std::launch::async, turkey, i));
    }

    auto res = 0;
    for (auto& fut : resultFutures) {
        res += fut.get();
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::cout << sheep(10) << std::endl;
}
