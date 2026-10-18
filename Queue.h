#ifndef QUEUE_H
#define QUEUE_H

#include "Maze.h"

class Queue{
private:
		Pos data[10050];            //队列元素 
		int front;                  //队头 
		int rear;                   //队尾 
		int maxsize;                //容量 
		
public:
		//初始化 
		Queue(){
			front=0;
			rear=0;
			maxsize=10050;	
			}
		//判满 
		bool full(){
			if(front==(rear+1)%maxsize){
				return true;
			}else{
				return false;
			}
		}
		
		//判空 
		bool empty(){
			if(rear==front){
				return true;
			}else{
				return false;
			}
		}
		
		//入队 
		void enqueue(Pos p){
			if(!full()){
			data[rear]=p;
			rear=(rear+1)%maxsize;
		    }
		}	
		
		//出队 
		Pos dequeue(){
			Pos p;
            p.r = -1;
            p.c = -1;
			if(!empty()){
			   p=data[front];
			   front=(front+1)%maxsize;
		    } 
		    return p;
		}	
};

#endif
