#include <iostream>
#include <vector>

#include "algo.h"
#include "parlay/internal/get_time.h"
#include "parlay/sequence.h"

int main() {
    const int RUNS = 5;
    SeqAlgo seq = SeqAlgo();
    ParAlgo par = ParAlgo();

    double seq_time = 0, par_time = 0;
    
    /*for (int run = 0; run < RUNS; run++) {
        SeqVec seqData = seq.createTestVec();
        auto t1 = std::chrono::high_resolution_clock::now();
        auto seq_result = seq.quicksort(seqData);
        auto t2 = std::chrono::high_resolution_clock::now();
        seq_time += std::chrono::duration<double>(t2-t1).count();
        
        ParVec parData = par.createTestVec();
        t1 = std::chrono::high_resolution_clock::now();
        auto par_result = par.quicksort(parData);
        t2 = std::chrono::high_resolution_clock::now();
        par_time += std::chrono::duration<double>(t2-t1).count();
    }
    
    std::cout << "Average Sequential Time: " << seq_time/RUNS << "s\n";
    std::cout << "Average Parallel Time: " << par_time/RUNS << "s\n";
    std::cout << "Speedup: " << seq_time/par_time << "x\n";
    
    std::cout << "--------------BFS----------------";
    seq_time = 0;
    par_time = 0;
    */
    auto seqGr = seq.createTestGraph();
    auto parGr = par.createTestGraph();

    for (int run = 0; run < RUNS; run++) {
        std::cout << "run " << run << " seq begin\n";
        auto t1 = std::chrono::high_resolution_clock::now();
        auto seq_result = seq.bfs(seqGr);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "run " << run << " seq end\n";
        seq_time += std::chrono::duration<double>(t2-t1).count();
        
        std::cout << "run " << run << " par begin\n";
        t1 = std::chrono::high_resolution_clock::now();
        auto par_result = par.bfs(parGr);
        t2 = std::chrono::high_resolution_clock::now();
        std::cout << "run " << run << " par out\n";
        par_time += std::chrono::duration<double>(t2-t1).count();
    }

    std::cout << "Average Sequential Time: " << seq_time/RUNS << "s\n";
    std::cout << "Average Parallel Time: " << par_time/RUNS << "s\n";
    std::cout << "Speedup: " << seq_time/par_time << "x\n";

    return 0;

}