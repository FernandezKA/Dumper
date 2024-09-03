/**
 * @file Memory.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Memory.h>

Memory::Memory(uint64_t baseAddr, size_t length)
{
    virtual_address = reinterpret_cast<uint64_t *>(mapMemory(baseAddr, length));
    if (virtual_address == nullptr)
    {
        perror("Failed to map memory");
        throw std::runtime_error("Failed to map memory");
    }

    this->length = length;
}

Memory::~Memory()
{
    unmapMemory(virtual_address, length);
}

void *Memory::mapMemory(uint64_t baseAddr, size_t length)
{
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
        perror("Failed to open /dev/mem");

    void *addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, baseAddr);
    if (addr == MAP_FAILED)
        perror("Failed to map /dev/mem");

    return addr;
}

void Memory::unmapMemory(void *addr, size_t length)
{
    munmap(addr, length);
    close(fd);
}