
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#define MAX 300
int shortestLength;
int reachedDestination = 0;

int queue[MAX], rear=-1, front=-1;

//void printMaze(int maze[][8], int visitedMaze[][8], int rowLen, int colLen);

void printMazecli(int maze[][8], int rowLen, int colLen){
  int i, j;
  for(i=0; i<rowLen; i++){
    for(j=0; j<colLen; j++){
      printf("%d ", maze[i][j]);
    }
    printf("\n");
  }
  printf("\n\n");
}
void initializeMaze(int maze[][8], int rowLen, int colLen){
  int i, j;
  for(i=0; i<rowLen;i++){
    for(j=0; j<colLen; j++){
      maze[i][j]=0;
    }
  }
}

int isWall(int maze[][8], int posx, int posy){
  if(maze[posx][posy]==1)
	return 1;
  else
	return 0;
}

void manualSetWalls(int maze[][8], int rowLen, int colLen, int startx, int starty, int endx, int endy){
  int numberOfWalls, wall, wallx, wally;
  printf("enter the number of walls\n");
  do{
    scanf("%d", &numberOfWalls);
    if(numberOfWalls>=rowLen*colLen){
      printf("enter less number of walls\n");
    }
  }while(numberOfWalls>=rowLen*colLen);
  for(wall=0; wall<numberOfWalls; wall++){
    printf("enter coordinates\n");
    scanf("%d %d", &wallx, &wally);
    if((wallx == startx && wally == starty)||(wallx==endx && wally ==endy)){
       printf("No path exists!");
       return;
   }
    maze[wallx][wally]=1;
    }
 }
 int indexToPos(int x, int y){
   if(x==0 && y!=0)
	return y;
   else if(x!=0 && y==0)
       return(x*10);
   else if(x==0 && y==0)
	return 0;
   else
	return(x*10 + y);
   }
   void enqueue(int data){
     if(rear==MAX-1)
       return;
     else{
       if(front==-1)
	  front=0;
       rear=rear+1;
       queue[rear]=data;
     }
   }
   int dequeue(){
     if(front==-1 || front>rear)
	return -1;
     else{
       int val = queue[front];
       front += 1;
       return val;
    }
   }
int isEmpty(){
  if(front>rear || (front==-1 && rear==-1))
	return 1;
  return 0;
}
void display()
{
    int i;
    if (front == - 1)
	printf("Queue is empty \n");
    else
    {
	printf("Queue is : \n");
	for (i = front; i <= rear; i++)
	    printf("%d ", queue[i]);
	printf("\n");
    }
}


void printMaze(int maze[][8], int visitedMaze[][8], int rowLen, int colLen, int startx, int starty, int endx, int endy){
  int left, top, right, bottom, linesx, linesy, lineex, lineey, i, j, k;
  int x=50, y=50, p, q ;

  for(i=0; i<rowLen; i++){
    for(j=0; j<colLen; j++){
      left=x+(j*50);
	right = left+50;
	top = x+(i*50);
	bottom= top+50;
	for(p=top; p<bottom; p++){
	  for(q=left; q<right; q++){
	    if(maze[i][j]==1){
	      putpixel(q, p, RED);
	    }
	    else if(i==startx && j==starty){
	      putpixel(q, p, YELLOW);
	    }
	    else if(i==endx && j==endy){
	      putpixel(q, p, BLUE);
	    }
	    else if(visitedMaze[i][j]==1){
	      putpixel(q, p, GREEN);
	    }
	    else{
	      putpixel(q, p, WHITE);
	    }
	  }
	} //p
    }
  }          //i
  left=50;
  top=50;
  bottom = 50+(50*rowLen);
  right = 50+(50*colLen);
  for(i=0; i<rowLen; i++){
    setcolor(BLACK);
    line(left, top+(i*50), right, top+(i*50));
  }
  for(i=0; i<colLen; i++){
    setcolor(BLACK);
    line(left+(i*50), top, left+(i*50), bottom);
  }


   getch();
   cleardevice();
}

void setWalls(int maze[][8], int rowLen, int colLen, int startx, int starty, int endx, int endy){
  int numberOfWalls, wall, wallx, wally;
  printf("enter the number of walls\n");

  do{
    scanf("%d", &numberOfWalls);
    if(numberOfWalls>=rowLen*colLen){
      printf("enter less number of walls\n");
    }
  }while(numberOfWalls>=rowLen*colLen);
  for(wall=0; wall<numberOfWalls; wall++){
   wallx = rand()%rowLen ;
    wally = rand()%colLen ;
     if((wallx == startx && wally == starty)||(wallx==endx && wally ==endy)){
       printf("No path exists!");
       return;
   }
    maze[wallx][wally]=1;
  }
}

void findPath(int maze[][8], int flagMaze[][8], int prevMaze[][8], int rowLen, int colLen, int startx, int starty, int endx, int endy){
  int x, y, i, j, val=1, pos, nx, ny, localPos, reached=0;
  int neigX[4] = {-1, 0, 1, 0};
  int neigY[4] = {0,1,0,-1};
  x=startx;
  y=starty;
  for(i=0; i<rowLen; i++){
    for(j=0; j<colLen; j++){
      prevMaze[i][j] = val++;
      }
   }
   pos = indexToPos(startx, starty);
   enqueue(pos);
   flagMaze[startx][starty]=1;

   while(!isEmpty() && reached==0){
      localPos = dequeue();

      x=localPos/10;

      y=localPos%10;
 
      for(i=0; i<4 && reached==0; i++){
	nx = x+neigX[i];
	ny = y+neigY[i];
     if(nx==endx && ny==endy){
	 flagMaze[nx][ny]=1;
	 prevMaze[nx][ny] = indexToPos(x, y);
	 reachedDestination=1;
	 reached=1;
	 }
	 else if(nx>=0 && ny>=0 && nx<rowLen && ny<colLen && !isWall(maze, nx, ny) && flagMaze[nx][ny]==0){
	    enqueue(indexToPos(nx, ny));
	    flagMaze[nx][ny]=1;
	    prevMaze[nx][ny] = indexToPos(x, y);
      }
    }
  }

}
void findShortestPath(int maze[][8], int prevMaze[][8], int shortestPath[][8], int rowLen, int colLen, int startx, int starty, int endx, int endy){
  int currPos, prevx, prevy, x, y;
  shortestPath[endx][endy]=1;
  x=endx;
  y=endy;
  while(1){
    currPos = prevMaze[x][y];
    prevx = currPos/10;
    prevy = currPos%10;
    shortestPath[prevx][prevy] = 1;
    if(prevx==startx && prevy==starty)
      break;
    currPos = indexToPos(prevx, prevy);
    x = prevx;
    y = prevy;

  }

}

int main(){
  int rowLen=8, colLen=8;
    int maze[8][8], flagMaze[8][8];
    int prevMaze[8][8], shortestPath[8][8];
    int startx, starty, endx, endy;
    int gdriver, gmode, errorcode;
    clrscr();
     printf("enter the starting and ending points\n");
  scanf("%d %d %d %d", &startx, &starty, &endx, &endy);
  shortestLength = rowLen*colLen;

  initializeMaze(maze, rowLen, colLen);
  initializeMaze(flagMaze, rowLen, colLen);
  initializeMaze(shortestPath, rowLen, colLen);
  setWalls(maze, rowLen, colLen, startx, starty, endx, endy);
    gdriver = DETECT;
    initgraph(&gdriver, &gmode, "");
    errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
   cleardevice();
   fflush(stdout);

  if(maze[endx][endy]==1 || maze[startx][starty]==1){
  //  printf("No path exists!");
    printMaze(maze, flagMaze, rowLen, colLen, startx, starty, endx, endy);
  }
  else{
  //  printMazecli(maze, rowLen, colLen);
    printMaze(maze, flagMaze, rowLen, colLen, startx, starty, endx, endy);
  //  playGame(maze, flagMaze, rowLen, colLen, 0, 0, 1);
    findPath(maze, flagMaze, prevMaze, rowLen, colLen, startx, starty, endx, endy);
    if(reachedDestination==0){
      printf("No path exists!");
      printMaze(maze, shortestPath, rowLen, colLen, startx, starty, endx, endy);
    }
    else{
	findShortestPath(maze, prevMaze, shortestPath, rowLen, colLen, startx, starty, endx, endy);
	printMaze(maze, shortestPath, rowLen, colLen, startx, starty, endx, endy);
    //	printMazecli(shortestPath, rowLen, colLen);
	}
  }
   closegraph();
 }

