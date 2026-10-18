#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>
using namespace std;

//坐标：r行，c列 
struct Pos{
	int r,c;
};

//最大迷宫尺寸 
const int MAXN=105;

extern vector<string> maze;    //存储迷宫 
extern int dr[8];              //行方向：前4个是四方向：下、右、上、左；后4个是斜向：右下、右上、左下、左上
extern int dc[8];              //列方向
extern int dirCount;           //控制方向数量，默认四方向
extern int m,n;                //行数，列数 

//从文件读迷宫 
bool readMaze(const string& filename);

//打印迷宫 
void printMaze(const vector<string>& g);

#endif
