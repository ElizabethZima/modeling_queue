#include <iostream>
#include "include/LimitedQueue.hpp"
#include "include/InfinityQueue.hpp"


int main() {
    double lambda = 1.2; // Интенсивность поступления заявок
    double mu = 2;     // Интенсивность обслуживания

    // Создание объектов для бесконечной и ограниченной очередей
    InfinityQueue infinity_queue(lambda, mu);
    LimitedQueue limited_queue(lambda, mu);

    // Запуск симуляций в отдельных потоках
    std::thread t1(&InfinityQueue::simulate, &infinity_queue);
    std::thread t2(&LimitedQueue::simulate, &limited_queue);

    // Ожидание завершения симуляций
    t1.join();
    t2.join();

    return 0;
}
