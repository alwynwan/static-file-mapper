#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

int main()
{
    char* mapped_bytes = nullptr;

    while (true) {
        printf("Drag a file in here to be mapped into memory, or type quit to exit: ");

        std::string input;
        std::getline(std::cin, input);

        if (mapped_bytes != nullptr)
            free(mapped_bytes);

        if (!strcmp(input.c_str(), "quit"))
            break;

        // Remove quotes from file path
        if (input.c_str()[0] == '\"')
            input.replace(0, 1, "");

        if(input.c_str()[input.size() - 1] == '\"')
            input.replace(input.size() - 1, input.size(), "");

        if (!std::filesystem::exists(input)) {
            printf("Invalid file path provided\n%s\n", input.c_str());
            continue;
        }

        std::ifstream input_stream = std::ifstream(input, std::ios::binary);

        input_stream.seekg(0, std::ios::end);

        int size = input_stream.tellg();

        mapped_bytes = new char[size];

        input_stream.seekg(0, std::ios::beg);

        input_stream.read(mapped_bytes, size);

        printf("Mapped %i bytes at %p\n", size, mapped_bytes);
    }
}