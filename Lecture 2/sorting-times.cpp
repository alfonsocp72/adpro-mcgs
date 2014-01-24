#include <iostream>
#include <iterator>
#include <vector>

#include <algorithm>
#include <functional>

#include <random>
#include <sstream>
#include <chrono>

// borrowed from http://anandpandia.blogspot.com.es/2012/08/quicksort-algorithm-and-example-in-c.html
// (ask for permission!)

void quickSort(std::vector< int > &input, int left, int right)
{
    int i = left, j = right;
    int pivot = input[(i + j) / 2];

    // partition  
    while (i <= j) {
        while (input[i] < pivot)
            i++;

        while (input[j] > pivot)
            j--;

        if (i <= j) {
            int tmp = input[i];
            input[i] = input[j];
            input[j] = tmp;

            i++;
            j--;
        }
    }

    // recursion  
    if (left < j)
        quickSort(input, left, j);

    if (i < right)
        quickSort(input, i, right);
}

void quickSort(std::vector< int > &input)
{
    quickSort(input, 0, input.size() - 1);
}

// adapted from 
// http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Bubble_sort#C.2B.2B
void bubbleSort(std::vector< int > &list)
{
    auto first = list.begin();
    auto last = list.end();

    for (auto i = first; i != last; i++) {
        for (auto j = first; j < i; j++) {
            if (*i < *j) {
                iter_swap(i, j);
            }
        }
    }
}

int main(int argc, char const *argv[])
{

    std::chrono::time_point<std::chrono::system_clock> start,end;
    std::chrono::duration<double> timeB, timeQ;
    
    // random the c++11 way
    std::random_device rd;
   
    std::mt19937 gen(rd());
     
    std::uniform_int_distribution < int >dis(1, 1000);

    std::vector<int> listB;
    std::vector<int> listQ;

    

    // bubble
    for(int elem = 100; elem <= 2000; elem += 100 )
    {
	  int temp_value;
	  for (int n = 0; n < elem; ++n)
	  {
	    temp_value = dis(gen);
	    listB.push_back(temp_value);
	    listQ.push_back(temp_value);
	  }
	  
	  start = std::chrono::system_clock::now(); 
	  bubbleSort(listB);
	  end = std::chrono::system_clock::now();
	  timeB = end -start;
	  //std::cout << "N = " ;//<< elem << "Bubble = " << timeB.count();
	  
	  start = std::chrono::system_clock::now();
	  quickSort(listQ);
	  end = std::chrono::system_clock::now();
	  timeQ = end -start;
	  
	  //std::cout << "N = " << elem << "\tBubble = " << timeB.count() << "\tQuick = " << timeQ.count() << std::endl;
	  std::cout << elem << "\t" << timeB.count() << "\t" << timeQ.count() << std::endl;
    }
    
    return 0;
    

}