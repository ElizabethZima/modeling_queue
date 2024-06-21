#include "../include/InfinityQueue.hpp"
void InfinityQueue::simulate() {
    while (server.should_continue()) {
        server.process_request(queue, output_file, mtx, false);
    }
    server.print_statistics("infinity_queue_statistics.txt");
}