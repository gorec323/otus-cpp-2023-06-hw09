#pragma once

namespace helpers {

/// @brief Шаблонная RAII-структура для восстановления изменённого буфера стрима
/// @tparam T тип стрима, для которого подменяется буфер
template <typename T>
struct stream_redirect 
{
    /// @brief Конструктор
    /// @param stream Ссылка на объект потока
    /// @param new_buffer Указатель на новый буфер для потока
    stream_redirect(T &stream, std::streambuf * new_buffer ) 
        : m_stream {stream}, old(stream.rdbuf(new_buffer))
    { }

    /// @brief Деструктор
    ~stream_redirect( ) 
    {
        m_stream.rdbuf( old );
    }

private:
    T &m_stream;
    std::streambuf * old;
};

}