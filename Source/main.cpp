#include <Dumper.h>
#include <Memory.h>
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char *argv[])
{   
    if(argc < 3){
        std::cout << "Usage: " << argv[0] << " <base_addr> <length> <path to the log file>" << std::endl;
        return -1;
    }

    uint64_t baseAddr = strtoull(argv[1], nullptr, 16);
    uint64_t length = strtoull(argv[2], nullptr, 16);
    std::string path = "";

    if (argc == 4) {
        path = std::string(argv[3]);
    }

    std::cout << "Base address: 0x" << std::hex << baseAddr << std::endl;
    std::cout << "Length: 0x" << std::hex << length << std::endl;
    if(path.size() > 0){
        std::cout << "Path to the log file: " << path << std::endl;
    }
    else{
        std::cout << "Log into the stdout \n\r";
    }

    std::unique_ptr<Dumper> dumper = std::make_unique<Dumper>(Memory(baseAddr, length), path);
    dumper->dump();

    return 0;
}