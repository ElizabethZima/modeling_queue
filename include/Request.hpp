#ifndef MODELING_QUEUE_REQUEST_HPP
#define MODELING_QUEUE_REQUEST_HPP
#include <queue>
#include <random>
#include <fstream>
#include <limits>
#include <thread>
#include <mutex>
#include <condition_variable>

// Структура для представления заявки
struct Request {
    double arrival_time;
    double start_service_time;
    double end_service_time;
};

#endif //MODELING_QUEUE_REQUEST_HPP
