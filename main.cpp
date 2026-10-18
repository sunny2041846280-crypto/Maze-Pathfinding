#include <iostream>
#include<string>
#include<fstream>
#include<vector>
#include <iomanip>

#include"Maze.h"
#include"Stack.h"
#include"Queue.h"

vector<string> maze;

// 前4个是四方向：下、右、上、左；后4个是斜向：右下、右上、左下、左上
int dr[8]={1,0,-1,0,1,-1,1,-1};
int dc[8]={0,1,0,-1,1,1,-1,-1};
int dirCount=4;  // 控制方向数量，默认四方向
int m,n;

//读迷宫 
bool readMaze(const string&filename){
    ifstream fin(filename.c_str());
	 if(!fin){
	 	cout<<"打不开文件： "<<filename<<endl;
	 	return false;
	 }
	 
	 fin>>m>>n;
	 
	 //尺寸检查，防止越界 
	 if(m<=0||n<=0||m>MAXN||n>MAXN){
	 	cout<<"迷宫尺寸不合法"<<endl;
		 return false; 
	 } 
	 
	 maze.assign(m,string(n,'0'));
	 for(int i=0;i<m;i++){
	 	for(int j=0;j<n;j++){
	 		fin>>maze[i][j];
		 }
	 }
	 return true;
}

//打印迷宫 
void printMaze(const vector<string> &g){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<g[i][j]<<"\t";
		}
		cout<<endl;
	}
}

//DFS：栈版深度优先搜索 
bool dfs(vector<string> &out,int &visitCount, int& pathLen){
    //输出图 
	out.assign(m,string(n,'.'));
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(maze[i][j]=='1'){
				out[i][j]='#';            //输出墙 
			}
		}
	}
	
	//初始化visited+前驱 
    bool visited[MAXN][MAXN];
    int prevR[MAXN][MAXN];
    int prevC[MAXN][MAXN];
    for(int i=0;i<MAXN;i++){
    	for(int j=0;j<MAXN;j++){
    		visited[i][j]=false;
    		prevR[i][j]=-1;
    		prevC[i][j]=-1;
		}
	}
	
    Stack st;   
    
    Pos start;                   //创建起点并初始化 
    start.r=0;
    start.c=0;
    
    st.push(start);
    visited[0][0]=true;         //标记访问 
    visitCount=1;               //起点入栈并计数 
    
	bool found=false;           //记录是否能到终点 
	
    while(!st.empty()){
    	//弹出栈顶，处理当前格子 
    	Pos cur=st.top();
    	st.pop();
    	
    	//到终点 
    	if(cur.r==m-1&&cur.c==n-1){
    		found=true;
    		break;
		}
		
		//四个方向顺序入栈 
		for(int d=0;d<dirCount;d++){
			int nr=cur.r+dr[d];
			int nc=cur.c+dc[d];
						
			if(nr>=0&&nr<m&&nc>=0&&nc<n&&maze[nr][nc]=='0'&&!visited[nr][nc]){
				
				//入栈前标记+记录前驱 
				visited[nr][nc]=true;
				prevR[nr][nc]=cur.r;
    		    prevC[nr][nc]=cur.c;
    		    
				Pos next;
		    	next.r=nr;
			    next.c=nc;
    		    st.push(next);
    		    visitCount++;
			}
		}
	}
	if(!found){
		return false;
	}else{
		//从终点沿前驱回溯到起点 
		int r=m-1;
		int c=n-1;
		pathLen=0;
		
	while(r!=-1&&c!=-1){
		pathLen++;
		out[r][c]='*';
		
		int pr=prevR[r][c];
		int pc=prevC[r][c];
		r=pr;
		c=pc;
	}
	
	    //标记起点、终点 
		out[0][0]='S';         
		out[m-1][n-1]='E';
		return true;
	
	}
}

//BFS：队列版广度优先搜索 
bool bfs(vector<string>&out,int &visitCount,int &pathLen){
	out.assign(m,string(n,'.'));
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(maze[i][j]=='1'){
				out[i][j]='#'; 
			}
		} 
	}
	
	bool visited[MAXN][MAXN];
	int prevR[MAXN][MAXN];
	int prevC[MAXN][MAXN];
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			visited[i][j]=false;
			prevR[i][j]=-1;
			prevC[i][j]=-1;
		} 
	}
    
    //创建队列 
	Queue q;
	
	Pos start;
	start.r=0;
	start.c=0;
    
    //起点入队并标记
	q.enqueue(start);
	visited[0][0]=true;
	visitCount=1;
	  
    bool found=false;
    
while(!q.empty()){
	Pos cur=q.dequeue();
	
	//找到终点则跳出循环 
	if(cur.r==m-1&&cur.c==n-1){
		found=true;
		break;
	}
	
	for(int d=0;d<dirCount;d++){
		int nr=cur.r+dr[d];
		int nc=cur.c+dc[d];
		
		if(nr>=0&&nr<m&&nc>=0&&nc<n&&!visited[nr][nc]&&maze[nr][nc]=='0'){
		
		//入队前标记访问+记录前驱 
		visited[nr][nc]=true;
		prevR[nr][nc]=cur.r;
	    prevC[nr][nc]=cur.c;
	    
	    Pos next;
		next.r=nr;
		next.c=nc;
		q.enqueue(next);
		visitCount++;
	   }
	}
}

    if(!found){
	       return false;
    }else{
	    pathLen=0;
	    int r=m-1;
     	int c=n-1;
     	
	while(r!=-1&&c!=-1){
		pathLen++;
		out[r][c]='*';
		
		int pr=prevR[r][c];
		int pc=prevC[r][c];
		r=pr;
		c=pc;
	}
	
	out[0][0]='S';
	out[m-1][n-1]='E';
	return true;
    }			
}

int main(int argc, char* argv[]) {
	//命令行参数：默认maze.txt 
    string filename="maze.txt";
    if(argc>1){
    	filename=argv[1];
	}
	
	if(!readMaze(filename)){
		return 1;
	}
	
	cout<<"= = = 原始迷宫 = = ="<<endl;
	printMaze(maze);
	cout<<endl;
	
	cout<<"= = = 解法一：栈（深度优先搜索）= = ="<<endl; 
	vector<string>outDFS;
	int visitDFS=0;
	int pathDFS=0;
	bool okDFS=dfs(outDFS,visitDFS,pathDFS);
	if(okDFS){
		printMaze(outDFS);
		cout<<"访问结点数："<<visitDFS <<endl;	
		cout<<"路径长度: "<<pathDFS<<endl;
		
	}else{
		cout<<"无解"<<endl;
		cout<<"访问结点数："<<visitDFS <<endl;
		cout<<"路径长度(格数): "<<"0"<<endl;
	}
	cout<<endl;
 
    cout<<"= = = 解法二：队列（广度优先搜索）= = ="<<endl;
    vector<string>outBFS;
	int visitBFS=0;
	int pathBFS=0;
	bool okBFS=bfs(outBFS,visitBFS,pathBFS);
	if(okBFS){
		printMaze(outBFS);
		cout<<"访问节点数："<<visitBFS <<endl;
		cout<<"路径长度: "<<pathBFS<<endl;
		
	}else{
		cout<<"无解"<<endl;
		cout<<"访问节点数："<<visitBFS <<endl;
		cout<<"路径长度: "<<"0"<<endl;
	}
	cout<<endl;
	
	cout<<"= = = 对比: = = ="<<endl;
	if(okDFS&&okBFS){
	cout<< left << setw(12)<<"指标"<<setw(20)<<"栈 DFS"<<setw(20)<<"队列 BFS"<<endl;
	cout<< left << setw(12)<<"路径长度"<<setw(20)<< pathDFS<<setw(20)<<pathBFS<<endl;
	cout<< left << setw(12)<<"访问结点数"<<setw(20)<< visitDFS<<setw(20)<<visitBFS<<endl;
	cout<< left << setw(12)<<"路径形态"<<setw(20)<<"反复曲折，沿墙绕行"<<setw(20)<<"平直、最短"<<endl; 
	int diff=pathDFS-pathBFS;
	 if(diff>0){
            cout<<"BFS的路径比DFS短"<<diff<<"格"<<endl;
        }else if(diff == 0){
            cout<<"BFS与DFS的路径长度相同。"<<endl;
        }else{
            cout<<"DFS的路径比BFS短"<<-diff<<"格"<<endl;
        }
    }else{
        cout<< "存在无解情况，无法对比。"<<endl;
    }
    
    dirCount=8;
    cout<<endl; 
    cout<<"= = =八方向拓展 = = ="<<endl; 
    cout<<"= = = 解法一：栈（深度优先搜索）【八方向】= = ="<<endl; 
	okDFS=dfs(outDFS,visitDFS,pathDFS);
	if(okDFS){
		printMaze(outDFS);
		cout<<"访问结点数："<<visitDFS <<endl;	
		cout<<"路径长度: "<<pathDFS<<endl;
		
	}else{
		cout<<"无解"<<endl;
		cout<<"访问结点数："<<visitDFS <<endl;
		cout<<"路径长度(格数): "<<"0"<<endl;
	}
	cout<<endl;
 
    cout<<"= = = 解法二：队列（广度优先搜索）【八方向】= = ="<<endl;
    okBFS=bfs(outBFS,visitBFS,pathBFS);
	if(okBFS){
		printMaze(outBFS);
		cout<<"访问节点数："<<visitBFS <<endl;
		cout<<"路径长度: "<<pathBFS<<endl;
		
	}else{
		cout<<"无解"<<endl;
		cout<<"访问节点数："<<visitBFS <<endl;
		cout<<"路径长度: "<<"0"<<endl;
	}
	cout<<endl;
	
	cout<<"= = = 八方向对比: = = ="<<endl;
	if(okDFS&&okBFS){
	cout<< left << setw(12)<<"指标"<<setw(20)<<"栈 DFS"<<setw(20)<<"队列 BFS"<<endl;
	cout<< left << setw(12)<<"路径长度"<<setw(20)<< pathDFS<<setw(20)<<pathBFS<<endl;
	cout<< left << setw(12)<<"访问结点数"<<setw(20)<< visitDFS<<setw(20)<<visitBFS<<endl;
	cout<< left << setw(12)<<"路径形态"<<setw(20)<<"反复曲折，沿墙绕行"<<setw(20)<<"平直、最短"<<endl; 
	int diff=pathDFS-pathBFS;
	 if(diff>0){
            cout<<"BFS的路径比DFS短"<<diff<<"格"<<endl;
        }else if(diff == 0){
            cout<<"BFS与DFS的路径长度相同。"<<endl;
        }else{
            cout<<"DFS的路径比BFS短"<<-diff<<"格"<<endl;
        }
    }else{
        cout<< "存在无解情况，无法对比。"<<endl;
    }
	return 0;
}
