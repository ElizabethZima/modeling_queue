#include "../include/Server.hpp"

void Server::handle_departure(std::queue<Request> &queue) {
    current_time = next_departure;

    total_queue_length_time += queue.size() * (current_time - last_event_time);
    total_system_length_time +=
            (queue.size() + (next_departure != std::numeric_limits<double>::infinity() ? 1 : 0)) *
            (current_time - last_event_time);

    Request &front = queue.front();
    front.end_service_time = current_time;
    total_waiting_time += front.start_service_time - front.arrival_time;
    total_system_time += front.end_service_time - front.arrival_time;

    queue.pop();
    served_requests++;

    if (!queue.empty()) {
        Request &next = queue.front();
        next.start_service_time = current_time;
        next_departure = current_time + service_dist(generator);
    } else {
        next_departure = std::numeric_limits<double>::infinity();
        free_time += next_arrival - current_time;
    }

    departure_log << "Arrival time: " << front.arrival_time
                  << " Serving time: " << front.end_service_time - front.start_service_time
                  << " Start serving time: " << front.start_service_time
                  << " End serving time: " << front.end_service_time << std::endl;

    last_event_time = current_time;
}

void Server::handle_arrival(std::queue<Request> &queue, bool is_limited) {
    current_time = next_arrival;

    total_queue_length_time += queue.size() * (current_time - last_event_time);
    total_system_length_time +=
            (queue.size() + (next_departure != std::numeric_limits<double>::infinity() ? 1 : 0)) *
            (current_time - last_event_time);

    Request req;
    req.arrival_time = current_time;
    int next = arrival_dist(generator);

    if (!is_limited || (is_limited && queue.size() < 4)) {
        queue.push(req);
        arrival_log << "New customer in queue: " << queue.size()
                    << " Serving time: " << service_dist(generator)
                    << " Arrival time between: " << next
                    << " Arrival time: " << current_time - 1 << std::endl;
    } else {
        arrival_log << "Queue full at time: " << current_time << std::endl;
    }

    next_arrival = current_time + next;

    if (queue.size() == 1) {
        Request &front = queue.front();
        front.start_service_time = current_time;
        next_departure = current_time + service_dist(generator);
    }

    total_requests++;
    last_event_time = current_time;
}

void Server::process_request(std::queue<Request> &queue, std::ofstream &file, std::mutex &mtx, bool is_limited) {
    std::unique_lock<std::mutex> lock(mtx);
    if (next_arrival < next_departure) {
        handle_arrival(queue, is_limited);
    } else {
        handle_departure(queue);
    }
}

void Server::print_statistics(const std::string &stats_file) const {
    std::ofstream log(stats_file, std::ios_base::app);
    double average_waiting_time_queue = total_waiting_time / served_requests;
    double average_time_in_system = total_system_time / served_requests;
    double average_queue_length = total_queue_length_time / current_time;
    double average_system_length = total_system_length_time / current_time;

    log << "Total requests: " << total_requests << std::endl;
    log << "Served requests: " << served_requests << std::endl;
    log << "Average waiting time in queue (Wq): " << average_waiting_time_queue << std::endl;
    log << "Average time in system (W): " << average_time_in_system << std::endl;
    log << "Average number of requests in queue (Lq): " << average_queue_length << std::endl;
    log << "Average number of requests in system (L): " << average_system_length << std::endl;
    log << "Total free time: " << free_time << std::endl;
    log << "Total working time: " << current_time - free_time << std::endl;
}

bool Server::should_continue() const {
    return served_requests < 1000;
}

Server::~Server() {
    if (arrival_log.is_open()) arrival_log.close();
    if (departure_log.is_open()) departure_log.close();
}