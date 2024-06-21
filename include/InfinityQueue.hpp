#ifndef MODELING_QUEUE_INFINITYQUEUE_HPP
#define MODELING_QUEUE_INFINITYQUEUE_HPP
#include "Server.hpp"

// Класс для управления бесконечной очередью и записи её состояния в файл
class InfinityQueue {
public:
    InfinityQueue(double lambda, double mu)
            : server(lambda, mu, "infinity_queue_arrival_log.txt", "infinity_queue_departure_log.txt") {}

    void simulate();

private:
    Server server;
    std::queue<Request> queue;
    std::ofstream output_file;
    std::mutex mtx;
};


#endif //MODELING_QUEUE_INFINITYQUEUE_HPP
