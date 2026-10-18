#ifndef STACK_H
#define STACK_H

#include "Maze.h"

class Stack{
private:
		Pos data[10050];               //Õ»ÔªËØ 
		int topidx;                    //Õ»¶¥ 
		
public:
		//³õÊ¼»¯ 
		Stack(){
			topidx=-1;                
		}
		
		//ÈëÕ» 
		void push(Pos p){
			topidx++;
			data[topidx]=p;
		}
		
		//³öÕ» 
		void pop(){
			if(topidx>-1){
			topidx--;}
		}
		
		//È¡Õ»¶¥ 
		Pos top(){
			return data[topidx];
		}
		
		//ÅÐ¿Õ 
		bool empty(){
			if(topidx!=-1){
				return false;
			}else{
				return true;
			}
		}		
};

#endif
