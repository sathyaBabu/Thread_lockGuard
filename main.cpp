//
//  main.cpp
//  Thread_ConditonLockGuard_4
//
//  Created by Sathya Babu on 07/08/23.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::mutex mtx;
std::condition_variable condition;
bool dataReady = false;

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
    {
        std::lock_guard<std::mutex> lock(mtx);
        dataReady = true;
    }
    condition.notify_one(); // Notify waiting thread
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
   
    condition.wait(lock, [] {
        
        cout << " waiting for notification to deliver.."<< endl; return dataReady;
        
                 }); // Wait until data is ready
    
    std::cout << "Data is ready : " << dataReady << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
/*
 waiting for notification to deliver..
 waiting for notification to deliver..
Data is ready : 1
Program ended with exit code: 0
 */
