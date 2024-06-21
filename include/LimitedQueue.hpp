#ifndef MODELING_QUEUE_LIMITEDQUEUE_HPP
#define MODELING_QUEUE_LIMITEDQUEUE_HPP
#include "Server.hpp"

// Класс для управления ограниченной очередью и записи её состояния в файл
class LimitedQueue {
public:
    LimitedQueue(double lambda, double mu)
            : server(lambda, mu, "limited_queue_arrival_log.txt", "limited_queue_departure_log.txt") {}

    void simulate();

private:
    Server server;
    std::queue<Request> queue;
    std::ofstream output_file;
    std::mutex mtx;
};

#endif //MODELING_QUEUE_LIMITEDQUEUE_HPP
