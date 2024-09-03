/**
 * @file Memory.h
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <sys/types.h>
#include <stdint.h>
#include <stdexcept>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
class Memory
{

public:
    Memory(uint64_t baseAddr, size_t length);
    ~Memory();

    template <typename T>
    T *getAddr(){
        return reinterpret_cast<T *>(virtual_address);
    }

    size_t GetLength() const
    {
        return length;
    }

private:

    void *mapMemory(uint64_t baseAddr, size_t length);
    void unmapMemory(void *virtual_address, size_t length);

    int fd = -1;

    uint64_t *virtual_address = nullptr;
    size_t length = 0;
};