#include "../include/LimitedQueue.hpp"

void LimitedQueue::simulate() {
    while (server.should_continue()) {
        server.process_request(queue, output_file, mtx, true);
    }
    server.print_statistics("limited_queue_statistics.txt");
}