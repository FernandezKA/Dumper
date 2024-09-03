/**
 * @file Dumper.h
 * @author FernandezKA (fernandes.kir@yandex.ru)
 * @brief
 * @version 0.1
 * @date 2024-09-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <memory>
#include <string>
#include <Memory.h>
#include <iostream>
#include <fcntl.h>

class Dumper
{
public:
    Dumper(Memory &&memory, const std::string &path);
    ~Dumper();

    int dump();

private:
    Memory &&m_memory;
    std::string m_path;

    int fd = -1;
};