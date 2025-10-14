#include <iostream>

void printFormatted(const std::string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        if (i + 1 < input.length() && input[i] == '\\' && input[i+1] == 'n') {
            std::cout << '\n'; 
            i++; 
        } else {
            std::cout << input[i]; 
        }
    }
    
    std::cout << std::endl;
}
int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    std::string input_text = argv[1];
    printFormatted(input_text);
}
