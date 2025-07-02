#include "Timer.h"
#include<iostream>
using namespace std;
void timer_test() {
    Timer timer;
    timer.reset();
    for (int i = 0; i < 1000000; ++i);
    double elapsed_time = timer.elapsed();
    cout << "Elapsed time: " << elapsed_time << " seconds" << endl;
    timer.reset();
    for (int i = 0; i < 1000000; ++i);
    elapsed_time = timer.elapsed();
    cout << "Elapsed time: " << elapsed_time << " seconds" << endl;
    timer.reset();
    for (int i = 0; i < 1000000; ++i);
    elapsed_time = timer.elapsed();
    cout << "Elapsed time: " << elapsed_time << " seconds" << endl;
    timer.reset();
    for (int i = 0; i < 1000000; ++i);
    elapsed_time = timer.elapsed();
    cout << "Elapsed time: " << elapsed_time << " seconds" << endl;
    cout<<endl;
}
int main(){
    timer_test();
    return 0;
}