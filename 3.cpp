#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<string>
#include<thread>
#include<mutex>
using namespace std;
mutex mtx;
const int n = 3;
int a = 0;
void f1(){
	for(int i = 0; i < 3; i++){
		
		mtx.lock();
		int x;
		cin >> x;
		a += x;
		mtx.unlock();
	}
	
}
void f2(){
	

		//mtx.lock();
		cout << a << '\n';
		//mtx.unlock();
	
}
int main(){
	thread t1(f1);
	t1.detach();
	
	thread t2(f1);
	t2.detach();
	
	thread t3(f1);
	t3.join();
	
	thread tout(f2);
	tout.join();
	
}