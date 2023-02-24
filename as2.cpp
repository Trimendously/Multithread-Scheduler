/*
Guest  random selected
    Guest ask for cupcake
        Cupcake is unavailable
                Cupcake is resupplied
                    Guest eats cupcake
                    Guest doesn't eat cupcake
        Cupcake is available
            Guest eats cupcake
            Guest doesn't eat cupcake
    Guest doesn't ask for cupcake

*/

/*
Create N threads (1,2,...,n)

The best algoirthmic approach would be a 
Thread #1 will keep track of the number of times a cupcake is replaced

Thread #2-n (n-1 in total) will eat the 

fifo 
*/

#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <math.h>
#include <chrono>
#include <mutex>
#include <random>
#include<cstdlib> // for rand



using namespace std;


using namespace std::chrono;

#define N 25

mutex m; // Protects Global variables

int activeGuest; // Keeps track of the guests

int count = 0; // Keeps track of # of guest who have been picked at least once
int cupcake_count= 0; // Keeps track of # of cupcakes eaten
int total_cupcake = N *2 ; // Total number of cupcakes
int request_count = 0; // Number of time a cupcake was requested
int extra_count = 0;

bool *picked  = new bool[N]; // Keeps tracked of who was already picked
bool *cupcakeEaten = new bool[N]; // Keeps track of who has eaten at least 1 cupcake

bool cupcake = true; // If the cupcake is available


// This approach was used as rand() was failing in uniqueness
unsigned int randomNumber(int min, int max) 
{
    //std::default_random_engine generator; // Offers no practical guarantees so not used
    static thread_local std::mt19937 seedGenerator; // Static gets around generating the seed every call
    std::uniform_int_distribution<int> uni_distribution(min,max);
    return uni_distribution(seedGenerator);
}

// Waiter serves cupcakes if no cupcake is available one will be supplied and we increment the number of cupcakes consumed
void waiter() {
    while (cupcake_count < total_cupcake) {
        m.lock();

        if (activeGuest == 0) // Only thread 1
        {
            if (!cupcake) 
            {
                cupcake_count++; // Cupcake was eaten
                cupcake = true; // Waiter restocks cupcake
            } 
        }

        m.unlock();
    }
}

void labrynth(int i)
{
    int request, eat;
    while(cupcake_count < total_cupcake)
    {
        m.lock();

        if (activeGuest == i)
        {
            if (!picked[i]) 
            {
                count++;
                cout << " Guest " << i+1 << " was picked for the first time." << endl;
            }
            picked[i] = true;
            
            // 10% chance guest requests a cupcake
            //request = rand() %10;
            request = 1;

            // Guest requests cupcake
            if (request == 1)
            {
                request_count++;
                // 10% chance guest eats a cupcake
                //eat = rand() % 10;
                eat = 1;

                // Guest eats a cupcake
                if (eat == 1)
                {
                    extra_count++;
                    cout << "Guest #" << i << " ate a cupcake. Only " << N-count << " more to go."<< endl;
                    cupcake = false; // Cupcake is now empty
                    cupcakeEaten[i] = true;
                }
                
            }
        }
        m.unlock();
    }
}


int main()
{
    vector<thread> v;
    srand (time(NULL));
    auto start = high_resolution_clock::now();
  
    v.push_back(thread(waiter));

    for (int i = 0; i <  N; i++)
        v.push_back(thread(labrynth,i));
    

    // Randomly picks guest until every guest has entered at least once
    
    while(count < N)
    {
        while (cupcake_count < total_cupcake)
            activeGuest = randomNumber(0,N);
        
    }

    for (auto& th : v) th.join();    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    

    for (int j = 0; j < N; j++)
    {
        std::cout << cupcakeEaten[j] << std::endl;

    }

    cout << "Party ended in " << duration.count() << " milliseconds" << endl;
    cout << count << " out of " << N << " guest entered." << endl;
    cout << cupcake_count << " out of " << total_cupcake << " cupcakes were eaten"<< endl;
    cout << extra_count << " cupcakes were requested"<< endl;

}