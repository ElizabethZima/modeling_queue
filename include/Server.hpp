#ifndef MODELING_QUEUE_SERVER_HPP
#define MODELING_QUEUE_SERVER_HPP
#include "Request.hpp"

// Класс для обработки заявок и подсчета статистических показателей
class Server {
public:
    Server(double lambda, double mu, const std::string &arrival_log_file, const std::string &departure_log_file)
            : lambda(lambda), mu(mu), generator(std::random_device{}()),
              arrival_dist(lambda), service_dist(mu),
              current_time(0.0), next_arrival(arrival_dist(generator)),
              next_departure(std::numeric_limits<double>::infinity()),
              total_requests(0), served_requests(0), total_waiting_time(0.0),
              total_system_time(0.0), total_queue_length_time(0.0),
              total_system_length_time(0.0), last_event_time(0.0), free_time(0.0) {
        arrival_log.open(arrival_log_file, std::ios_base::app);
        departure_log.open(departure_log_file, std::ios_base::app);
    }

    ~Server();

    void process_request(std::queue<Request> &queue, std::ofstream &file, std::mutex &mtx, bool is_limited);

    bool should_continue() const;

    void print_statistics(const std::string &stats_file) const;

private:
    double lambda;
    double mu;
    std::default_random_engine generator;
    std::poisson_distribution<int> arrival_dist;
    std::exponential_distribution<double> service_dist;
    double current_time;
    double next_arrival;
    double next_departure;
    int total_requests;
    int served_requests;
    double total_waiting_time;
    double total_system_time;
    double total_queue_length_time;
    double total_system_length_time;
    double last_event_time;
    double free_time;
    std::ofstream arrival_log;
    std::ofstream departure_log;


    void handle_departure(std::queue<Request> &queue);
    void Server::handle_arrival(std::queue<Request> &queue, bool is_limited);
};


#endif //MODELING_QUEUE_SERVER_HPP
