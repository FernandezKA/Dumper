/**
 * @file Memory.cpp
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief   creates a new mapping in the virtual address space
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <Memory.h>

/**
 * @brief Constructor for Memory class
 *
 * Maps a memory region starting from @p baseAddr for @p length bytes
 * and stores the result in virtual_address.
 *
 * If the mapping fails, throws a std::runtime_error with a message
 * describing the error.
 *
 * @param baseAddr the start address of the memory region to map
 * @param length the length of the memory region to map
 */
Memory::Memory(uint64_t baseAddr, size_t length)
{
    virtual_address = reinterpret_cast<uint64_t *>(mapMemory(baseAddr, length));
    if (virtual_address == nullptr) {
        perror("Failed to map memory");
        throw std::runtime_error("Failed to map memory");
    }

    this->length = length;
}

/**
 * @brief Destructor for Memory class
 *
 * Unmaps the memory region previously mapped with the constructor.
 *
 * If the un-mapping fails, a std::runtime_error is thrown with a message
 * describing the error.
 */
Memory::~Memory() {
    unmapMemory(virtual_address, length);
}

/**
 * Maps a memory region starting from @p baseAddr for @p length bytes
 * into the process's virtual address space.
 *
 * If the mapping fails, a std::runtime_error is thrown with a message
 * describing the error.
 *
 * @param baseAddr the start address of the memory region to map
 * @param length the length of the memory region to map
 * @return a pointer to the mapped memory region
 */
void *Memory::mapMemory(uint64_t baseAddr, size_t length) {
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0)
        perror("Failed to open /dev/mem");

    void *addr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, baseAddr);
    if (addr == MAP_FAILED)
        perror("Failed to map /dev/mem");

    return addr;
}





/**
 * Unmaps a memory region previously mapped by Memory::mapMemory.
 *
 * If the un-mapping fails, a std::runtime_error is thrown with a message
 * describing the error.
 *
 * @param addr the address of the memory region to unmap
 * @param length the length of the memory region to unmap
 */
void Memory::unmapMemory(void *addr, size_t length) {
    munmap(addr, length);
    close(fd);
}
