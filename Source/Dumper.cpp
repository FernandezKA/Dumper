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


/**
 * @brief Constructor for Dumper class
 *
 * Creates a new Dumper object which dumps the content of the memory region
 * specified by the @p memory parameter into the file specified by the
 * @p path parameter.
 *
 * If the @p path parameter is empty, the content of the memory region is
 * dumped into the stdout.
 *
 * If the @p path parameter is not empty, the content of the memory region
 * is dumped into the file specified by the @p path parameter.
 *
 * If the file can not be opened, a std::runtime_error is thrown with a
 * message describing the error.
 *
 * @param memory the memory region to dump
 * @param path the path of the file to dump the memory region. If empty, the
 * memory region is dumped into the stdout.
 */
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

/**
 * @brief Destructor for Dumper class
 *
 * Closes the file descriptor of the file used to dump the memory region.
 *
 * If the file descriptor is not valid (i.e. it is equal to STDOUT_FILENO), the
 * destructor does nothing.
 */
Dumper::~Dumper()
{
    if (fd > 0 || fd != STDOUT_FILENO)
    {
        close(fd);
    }
}



/**
 * @brief Dumps the memory region into a file or stdout.
 *
 * If the file descriptor of the file used to dump the memory region is valid
 * (i.e. it is not equal to STDOUT_FILENO), the function dumps the memory region
 * into the file specified by the file descriptor. Otherwise, the function dumps
 * the memory region into the stdout.
 *
 * If the memory region can not be read, a std::runtime_error is thrown with a
 * message describing the error.
 *
 * @return 0 if the memory region has been successfully dumped, -1 otherwise.
 */
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
