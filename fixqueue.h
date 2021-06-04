#ifndef HELPERS_INCLUDE_FIXED_SIZE_QUEUE_H
#define HELPERS_INCLUDE_FIXED_SIZE_QUEUE_H

#include <cassert>
#include <deque>
#include <stdexcept>

namespace helpers
{
template<typename T>
class FixedSizeQueue : public std::deque<T>
{
public:
    explicit FixedSizeQueue(std::size_t size)
        : _size{size}
    {
        if (size == 0) {
            throw std::runtime_error("FixedSizeQueue: the size must be bigger than zero!");
        }
    }

    void push(T &&value)
    {
        assert(this->size() <= _size);  
        if (isFull()) {
            std::deque<T>::pop_front();
        }
        std::deque<T>::emplace_back(value);
    }

    [[nodiscard]] bool isFull() const
    {
        return this->size() == _size;
    }

private:
    void push_front(T &&value);
    void push_front(const T &value);
    void push_back(T &&value);
    void push_back(const T &value);
    void pop_front();
    void pop_back();

    const std::size_t _size;
};

}  // namespace helpers

#endif  // FIXED_SIZE_QUEUE_H
