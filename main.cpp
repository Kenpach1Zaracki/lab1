#include <iostream>
#include <string>
#include "storage.h"
#include "commands.h"

int main(int argc, char* argv[]) {
    std::string filename = "file.data"; 
    std::string query = "";
    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (query.empty()) {
        std::cout << "Usage: " << argv[0] << " --file <filename> --query '<command>'" << std::endl;
        std::cout << "Default file: file.data" << std::endl;
        return 1;
    }

    load_from_file(filename);

    process_command(query);

    save_to_file(filename);

    return 0;
}