
// Этот код написан под номера 1-3 //

#include <iostream>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <future>
#include <condition_variable>
using namespace std;


class node{
	
	public:
	node* prev;
	node* next;
	int val;
	node(int v, node* nxt, node* pr){
		
		val = v;
		if(pr!= NULL) (*pr).next = this;
		prev = pr;
	}
};

class Queue{
	public:
	//condition_variable c;
	mutex mtx, mtx_wnp; // mtx - используем для всего, mtx_wnp - для wait and pop
	node* front;
	node* back;
	int sz = 0;
	
	int size(){
		mtx.lock();
		mtx.unlock();
		return sz;
		
	}
	void put(int n){
		mtx.lock();
		if(sz != 0){
			
			node* newnode = new node(n, NULL, back);
			back = newnode;
			sz++;
			mtx_wnp.unlock();
		}
		else
		{
			node* newnode = new node(n, NULL, NULL);
			front = newnode;
			back = newnode;
			sz++;
			mtx_wnp.unlock();
		}
		mtx.unlock();
	}
	int pop(){
		mtx.lock();
		int a = front -> val;
		front = (*front).next;
		
		delete((*front).prev);
		sz--;
		if(0 == sz) {
			mtx_wnp.lock();
		}
		mtx.unlock();
		return a;
	}
	
	int get(int j){
		mtx.lock();
		node* a;
		a = front;
		for(int i = 0; i < j; i++){
			a = a->next;
		}
		mtx.unlock();
		return a -> val;
		
	}
	int wait_and_pop(){
		mtx_wnp.lock();
		mtx_wnp.unlock();
		return (*this).pop();
		
	}
	~Queue(){
		for(int i = 0; i < sz; i++){
			(*this).pop();
		}
	}
};

int main(){
	Queue a;
	a.put(1);
	
	cout << a.pop() << ' '; 
	

	cout << a.size() << ' ';
	cout << a.wait_and_pop();
}
