#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;
int cnt = 0;
void f1(){
	for(int i = 0; i < 1000000; i++){
		mtx.lock();
		
		cout << i << ' ' << this_thread::get_id() << '\n' ;
		mtx.unlock();
	}
}

int main(){
	
	
	thread t1(f1);
	t1.detach();
	thread t2(f1);
	t2.detach();
	thread t3(f1);
	t3.join();
	
}
