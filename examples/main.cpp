#include "examples/Personal.h"
#include "examples/AppConfig.h"

void showAvaliableExampleCases() {
    std::cout << "All available example cases: \n";
    std::cout << "- personal\n";
    std::cout << "- appconfig\n";
}

void showHelp(const char* arg) {
    std::cout << "Usage: " << arg << " [OPTIONS]\n";
    std::cout << "[VALUE]                    Example case\n";
    std::cout << "-l, --list                 List all available example cases\n";
    std::cout << "-h, --help                 Display help information\n";
    std::cout << "-v, --version              Display version info\n";
}

void showVersion() {
    std::cout << "JsonBuilder Example v1.0.0\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        showHelp(argv[0]);
        return 1;
    }
    std::string option = argv[1];
    if (option == "-l" || option == "--list") {
        showAvaliableExampleCases();
        return 0;
    } else if (option == "-h" || option == "--help") {
        showHelp(argv[0]);
        return 0;
    } else if (option == "-v" || option == "--version") {
        showVersion();
        return 0;
    } else if (option == "personal") {
        return Personal::start();
    } else if (option == "appconfig") {
        return AppConfig::start();
    }
    return 0;
}