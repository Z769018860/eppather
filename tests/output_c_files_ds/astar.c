void astar(int rows,int cols,int grid[100][100],int start_x,int start_y,int goal_x,int goal_y){
    int openSet[100][100];
    int g[100][100];
    int f[100][100];
    int parentX[100][100];
    int parentY[100][100];
    
    for(int i=0;i<100;i=i+1){
        for(int j=0;j<100;j=j+1){
            g[i][j]=10000;
            f[i][j]=10000;
            parentX[i][j]=-1;
            parentY[i][j]=-1;
            openSet[i][j]=0;
        }
    }
    
    g[start_x][start_y]=0;
    int delta_x=start_x-goal_x;
    if(delta_x<0){delta_x=-delta_x;}
    int delta_y=start_y-goal_y;
    if(delta_y<0){delta_y=-delta_y;}
    f[start_x][start_y]=delta_x+delta_y;
    openSet[start_x][start_y]=1;
    
    while(1){
        int min_f=10000;
        int current_x=-1;
        int current_y=-1;
        
        for(int i=0;i<rows;i=i+1){
            for(int j=0;j<cols;j=j+1){
                if(openSet[i][j]!=0){
                    if(f[i][j]<min_f){
                        min_f=f[i][j];
                        current_x=i;
                        current_y=j;
                    }
                }
            }
        }
        
        if(current_x==-1){break;}
        if(current_x==goal_x&&current_y==goal_y){break;}
        
        openSet[current_x][current_y]=0;
        
        int dx[4]={-1,1,0,0};
        int dy[4]={0,0,-1,1};
        
        for(int k=0;k<4;k=k+1){
            int neighbor_x=current_x+dx[k];
            int neighbor_y=current_y+dy[k];
            
            if(neighbor_x>=0){
                if(neighbor_x<rows){
                    if(neighbor_y>=0){
                        if(neighbor_y<cols){
                            if(grid[neighbor_x][neighbor_y]==0){
                                int tentative_g=g[current_x][current_y]+1;
                                
                                if(tentative_g<g[neighbor_x][neighbor_y]){
                                    parentX[neighbor_x][neighbor_y]=current_x;
                                    parentY[neighbor_x][neighbor_y]=current_y;
                                    g[neighbor_x][neighbor_y]=tentative_g;
                                    
                                    int h_dx=neighbor_x-goal_x;
                                    if(h_dx<0){h_dx=-h_dx;}
                                    int h_dy=neighbor_y-goal_y;
                                    if(h_dy<0){h_dy=-h_dy;}
                                    f[neighbor_x][neighbor_y]=tentative_g+h_dx+h_dy;
                                    
                                    openSet[neighbor_x][neighbor_y]=1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
