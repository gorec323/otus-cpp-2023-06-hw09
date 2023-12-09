#pragma once

#include <cinttypes>

namespace async {

    /// @brief Тип контекста обработки команд
    using print_handler_t = void *;

    /// @brief Создаётся контекст с передачей размера блока команд
    /// @param bulkLimit Размер блока команд
    /// @return Контекст выполнения функции
    print_handler_t connect(std::size_t bulkLimit);

    /// @brief Передача команды в рамках контекста, полученного вызовом команды connect
    /// @param handler Контекст обработка команды 
    /// @param data Указатель на начало команды
    /// @param dataSize Размер блока команды
    void receive(print_handler_t const handler, const char * const data, std::size_t dataSize);

    /// @brief Завершение обработки команд
    /// @param handler Контекст обработки команд
    void disconnect(print_handler_t handler);
}