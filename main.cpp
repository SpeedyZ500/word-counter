#include <iostream>

#include <sstream>
#include <ostream>
#include <fstream>
#include <string>


bool checkForMatchingExtension(const std::string& str, const std::string& ext){
    int n = str.length();
    int m = ext.length();
    if(m > n){
        return false;
    }
    return str.substr(n-m, m) == ext;
}

int main(int argc, const char * argv[]){
    if(argc < 2){
        std::cout << "Please provide an input file" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string input = buffer.str();
    in.close();

    std::string outfile = "";

    if(argc < 3){
        std::cout << "Would you like to provide an output file? Y/n" << std::endl;
        std::string provideInput = "";
        std::getline(std::cin, provideInput);
        std::transform(provideInput.begin(), provideInput.end(), provideInput.begin(),
        [](unsigned char c){ return std::toupper(c); });

        if(provideInput == "Y" || provideInput == "YES"){
            std::getline(std::cin, provideInput);
            if(checkForMatchingExtension(provideInput, ".txt")){
                outfile = provideInput;
            }
            else{
                outfile = provideInput.append(".txt");
            }
        }
    }
    else{
        outfile = argv[2];
    }
    std::ofstream file;
    std::ostream& out = (outfile.empty()) ? std::cout : file;

    if (!outfile.empty()) {
        file.open(outfile);
        if (!file) {
            std::cerr << "Failed to create " << outfile << " for output.\n";
            return 1;
        }
    }
    file.close();

    return 0;
}