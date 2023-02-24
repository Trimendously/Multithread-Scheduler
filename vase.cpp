#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <set>
#include <thread>

#define N 10 // Number of guests


bool room = true; // Status of the showroom (busy/ available)
std::set<std::thread::id> visited; // Keeps track of thread's id of who visited showroom
std::mutex m; // Protects global vars

// This approach was used as rand() was failing in uniqueness
unsigned int randomNumber(int min, int max) 
{
    //std::default_random_engine generator; // Offers no practical guarantees so not used
    static thread_local std::mt19937 seedGenerator; // Static gets around generating the seed every call
    std::uniform_int_distribution<int> uni_distribution(min,max);
    return uni_distribution(seedGenerator);
}

void showroom(int index)
{
    std::thread::id tid = std::this_thread::get_id();

    while(visited.size() < N)
    {
        m.lock();

        if (room == true && visited.find(tid) == visited.end()) // Room is available
        {
            std::cout << "      Guest " << index+1 << " has entered the showroom.\n         <Unavailable>"<< std::endl;
            room = false;

            
            std::this_thread::sleep_for(std::chrono::milliseconds(randomNumber(10,100))); // Random time guest stay in showroom 

            std::cout << "                  Guest " << index+1 << " has left the showroom.\n<AVAILABLE>"<< std::endl;
            room = true;

            visited.insert(tid);
        }
        m.unlock();
    }

}


int main()
{
    std::vector<std::thread> v;

    auto start = std::chrono::high_resolution_clock::now();
  
    std::cout<< "<AVAILABLE>" << std::endl;
    for (int i = 0; i <  N; i++)
        v.push_back(std::thread(showroom,i));
    

    for (auto& th : v) th.join();    

    std::cout << "Closed" << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    

    std::cout << "Showroom viewing ended in " << duration.count() << " milliseconds" << std::endl;
    std::cout << visited.size() << " out of " << N << " guests visited." << std::endl;


}