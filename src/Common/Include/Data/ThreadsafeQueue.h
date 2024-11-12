#pragma once

#include <condition_variable>
#include <mutex>
#include <memory>


namespace Tetris::Common::Data
{

    /// @brief Потокобезопасная реализация очереди с блокировкой
    /// @tparam T Хранимый тип в очереди
    template <typename T>
    class ThreadsafeQueue
    {
        /// @brief Узел очереди
        struct Node
        {
            std::shared_ptr<T> data;
            std::unique_ptr<Node> next;
        };

    public:
        /// @brief Конструктор по умолчанию
        explicit ThreadsafeQueue() : _head(new Node), _tail(_head.get()) {};

        /// @brief Удалённый копирующий конструктор
        /// @param other Копируемый объект
        ThreadsafeQueue(const ThreadsafeQueue &other) = delete;

        /// @brief Удалённый оператор присвоения
        /// @param other Копируемый объект
        /// @return Новая очередь
        ThreadsafeQueue &operator=(const ThreadsafeQueue &other) = delete;

        /// @brief Попробовать получить значение из очереди
        /// @return При неудачи nullptr
        std::shared_ptr<T> try_pop()
        {
            std::unique_ptr<Node> old_head = try_pop_head();
            return old_head ? old_head->data : std::shared_ptr<T>();            
        }

        /// @brief Попробовать получить значение из очереди
        /// @param value Переменная в которую записывается значение очереди
        /// @return Успешное или не успешное взятие элемента
        bool try_pop(T &value)
        {
            std::unique_ptr<Node> const old_head=try_pop_head(value);
            return old_head.get();
        }

        /// @brief Ожидать если нет значения и получить значение 
        /// @return Значение из очереди
        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_ptr<Node> const ol_head = wait_pop_head();
            return ol_head->data;
        }

        /// @brief Ожидать если нет значения и получить значение 
        /// @param value Переменная в которую записывается значение очереди
        void wait_and_pop(T &value)
        {
            std::unique_ptr<Node> const old_head = wait_pop_head(value);
        }

        /// @brief Вставить элемент в очередь
        /// @param newValue Новое значение
        void push(T newValue)
        {
            std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
            std::unique_ptr<Node> p(new Node);
            {
                std::lock_guard<std::mutex> tail_lock(_tailMutex);
                _tail->data=newData;
                Node* const newTail = p.get();
                _tail->next = std::move(p);
                _tail=newTail;
            }
            _dataCond.notify_one();
        }

        /// @brief Проверка на пустой список
        /// @return Пустой или нет
        bool empty()
        {
            std::lock_guard<std::mutex> head_lock(_headMutex);
            return (_head.get() == get_tail());            
        }

    private:
        Node *get_tail()
        {
            std::lock_guard<std::mutex> tailLock(_tailMutex);
            return _tail;
        };

        std::unique_ptr<Node> pop_head()
        {
            std::unique_ptr<Node> oldHead = std::move(_head);
            _head = std::move(oldHead->next);
            return oldHead;
        };

        std::unique_ptr<std::mutex> wait_for_data()
        {
            std::unique_ptr<std::mutex> headLock(_headMutex);
            _dataCond.wait(headLock, [&](){return (_head.get() != get_tail());});
            return std::move(headLock);
        };

        std::unique_ptr<Node> wait_pop_head()
        {
            std::unique_ptr<std::mutex> head_lock(wait_for_data());
            return pop_head();
        };

        std::unique_ptr<Node> wait_pop_head(T &value)
        {
            std::unique_ptr<std::mutex> head_lock(wait_for_data());
            value = std::move(*_head->data);
            return pop_head();
        };

        std::unique_ptr<Node> try_pop_head()
        {
            std::lock_guard<std::mutex> head_lock(_headMutex);
            if(_head.get() == get_tail())
                return std::unique_ptr<Node>();

            return pop_head();
        };

        std::unique_ptr<Node> try_pop_head(T &value)
        {
            std::lock_guard<std::mutex> head_lock(_headMutex);
            if(_head.get() == get_tail())
                return std::unique_ptr<Node>();

            value=std::move(*_head->data);
            return pop_head();
        };

        std::unique_ptr<Node> _head;
        Node *_tail;
        std::mutex _headMutex;
        std::mutex _tailMutex;
        std::condition_variable _dataCond;
    };

} // namespace