#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<string>
#include<thread>
#include<mutex>
using namespace std;
mutex mtx;
int a = 0;
void f1(){
	for(int i = 0; i < 10; i++){
		
		mtx.lock();
		int x;
		cin >> x;
		a += x;
		mtx.unlock();
		
	}
	
}
void f2(){
	

		mtx.lock();
		cout << a << '\n';
		mtx.unlock();
	
}
int main(){
	thread t1(f1);
	t1.detach();
	thread t2(f2);
	t2.join();
	
}