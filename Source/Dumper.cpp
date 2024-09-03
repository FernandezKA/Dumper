/**
 * @file Dumper.cpp
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Dumper.h>

Dumper::Dumper(Memory &&memory, const std::string &path) : m_memory(std::move(memory)), m_path(path)
{

    if (m_path.size() == 0)
    {
        std::cout << "Log into the stdout \n\r";
        fd = STDOUT_FILENO;
    }
    else
    {
        fd = open(m_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd < 0)
        {
            perror("Failed to open file");
            throw std::runtime_error("Failed to open file");
        }
    }
}

Dumper::~Dumper()
{
    if (fd > 0 || fd != STDOUT_FILENO)
    {
        close(fd);
    }
}

int Dumper::dump()
{
    /*Read from memory to vector*/
    auto addr = m_memory.getAddr<uint8_t>();

    if(addr == nullptr){
        perror("Failed to read from memory");
        throw std::runtime_error("Failed to read from memory");
    }

    size_t wrLen = 0u;
    /*Write to stream*/
    for (size_t i = 0; i < m_memory.GetLength(); i++) {
        wrLen += write(fd, &addr[i], 1);
    }

    std::cout << "Writed to file: " << m_path << " length: " << m_memory.GetLength() << std::endl;

    return (wrLen == m_memory.GetLength()) ? 0 : -1;
}
