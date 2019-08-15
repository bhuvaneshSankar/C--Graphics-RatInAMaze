#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
int sourceX, sourceY, destX, destY;
void initializeMaze(int maze[][8], int rowLen, int colLen){
  int i, j;
  for(i=0; i<rowLen; i++){
    for(j=0; j<colLen; j++){
      maze[i][j]=0;
    }
  }
}
void setWalls(int maze[][8], int rowLen, int colLen){
  int numberOfWalls, wall, wallx, wally;
  printf("enter the number of walls\n");

  do{
    scanf("%d", &numberOfWalls);
    if(numberOfWalls>=rowLen*colLen){
      printf("enter less number of walls\n");
    }
  }while(numberOfWalls>=rowLen*colLen);
  for(wall=0; wall<numberOfWalls; wall++){
    wallx = rand()%rowLen +1;
    wally = rand()%colLen +1;
    if(wallx == sourceX && wally == destY){
      printf("destination cant be reached");
      exit(0);
    }
    maze[wallx][wally]=1;
  }
}

void printMaze(int maze[][8], int visitedMaze[][8], int rowLen, int colLen, int sourceX, int sourceY, int destX, int destY){
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
	   if(i==destX && j==destY){
		putpixel(q, p, BLUE);
	   }
	   else if(i==sourceX && j==sourceY){
	     putpixel(q, p, YELLOW);
	   }
	    else if(maze[i][j]==1){
	      putpixel(q, p, RED);
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
int isWall(int maze[][8], int posx, int posy){
  if(maze[posx][posy]==1)
	return 1;
  else
	return 0;
}
int reachedDestination = 0;
void playGame(int maze[][8], int flagMaze[][8], int rowLen, int colLen, int posx, int posy, int sourceX, int sourceY, int destX, int destY){
  flagMaze[posx][posy]=1;
  if(posx == destX && posy == destY){
    reachedDestination=1;
    printMaze(maze, flagMaze, rowLen, colLen, sourceX, sourceY, destX, destY);
    exit(0);
  }
  else{
//    getch();
    printMaze(maze, flagMaze, rowLen, colLen, sourceX, sourceY, destX, destY);
    //move right
    if(posy+1!=colLen && !isWall(maze, posx, posy+1) && flagMaze[posx][posy+1]==0){
      playGame(maze, flagMaze, rowLen, colLen, posx, posy+1, sourceX, sourceY, destX, destY);
    }
    //move down
    if(posx+1!=rowLen && !isWall(maze, posx+1, posy) && flagMaze[posx+1][posy]==0){
      playGame(maze, flagMaze, rowLen, colLen, posx+1, posy, sourceX, sourceY, destX, destY);
    }
    //move left
    if(posy-1>=0 && !isWall(maze, posx, posy-1) && flagMaze[posx][posy-1]==0){
      playGame(maze, flagMaze, rowLen, colLen, posx, posy-1, sourceX, sourceY, destX, destY);
    }
    //move up
    if(posx-1>=0 && !isWall(maze, posx-1, posy)&& flagMaze[posx-1][posy]==0){
      playGame(maze, flagMaze, rowLen, colLen, posx-1, posy, sourceX, sourceY, destX, destY);
    }
  }
  flagMaze[posx][posy]=0;  //backtracking
}
void manualSetWalls(int maze[][8], int rowLen, int colLen){
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
    maze[wallx][wally]=1;
    }
 }


void main(){
  int rowLen=8, colLen=8;
  int maze[8][8], flagMaze[8][8];
  int gdriver, gmode, errorcode;
  clrscr();
  printf("Enter the source cell: \n");
  scanf("%d %d", &sourceX, &sourceY);
  printf("Enter the destination cell: \n");
  scanf("%d %d", &destX, &destY);
  initializeMaze(maze, rowLen, colLen);
  initializeMaze(flagMaze, rowLen, colLen);
  manualSetWalls(maze, rowLen, colLen);

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
  if(maze[sourceX][sourceY]==1 || maze[destX][destY]==1){

    printMaze(maze, flagMaze, rowLen, colLen, sourceX, sourceY, destX, destY);
    clrscr();
    printf("No path exists!");
  }
  else{
    printMaze(maze, flagMaze, rowLen, colLen, sourceX, sourceY, destX, destY);
    playGame(maze, flagMaze, rowLen, colLen, sourceX, sourceY, sourceX, sourceY, destX, destY);
  }
  cleardevice();
  closegraph();
  clrscr();
   if(reachedDestination==0){
      clrscr();
      printf("no path exists!");
    }

  getch();

 }
