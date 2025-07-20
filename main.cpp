#include <thread>
#include <vector>
#include "lib/logger.h"
using std::string;

int main(int argc, char* argv[]) {

    string filename = (argc > 1 ? argv[1] : "log.txt");

    LogLvl lvl = LogLvl::debug;
    if (argc > 2) {
        string s = argv[2];
        if (s == "warning") lvl = LogLvl::warning;
        else if (s == "error") lvl = LogLvl::error;
    }

    Logger logger(filename, lvl);
 
    std::vector<std::thread> threads;

    for (int t = 0; t < 12; ++t) {
        threads.emplace_back([&logger, lvl, t]() {

            for (int i = 0; i < 10; ++i) {
                logger.Write("Поток " + std::to_string(t) + " значение " + std::to_string(i), lvl);
            }

            });
    }

    for (auto& th : threads) {
        if (th.joinable())
        {
            th.join();
        }
    }

    return 0;
}
