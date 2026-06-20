#include <iostream>
#include <string>
#include <ship/Context.h>

int main(int argc, char* argv[]) {
    std::cout << "Testing libultraship linkage..." << std::endl;

    std::string appDir = Ship::Context::GetAppDirectoryPath("vinny");
    std::cout << "App directory path: " << appDir << std::endl;

    if (!appDir.empty()) {
        std::cout << "✓ libultraship is linked and static Context utilities are callable" << std::endl;
        return 0;
    }

    std::cout << "✗ static Context utility returned an empty path" << std::endl;
    return 1;
}