void kruskal(int numVertices,int numEdges,int edgeData[100][3]){
    int parent[10];
    int edges[100][3];
    int mstWeight=0;
    
    for(int i=0;i<10;i=i+1){
        parent[i]=i;
    }
    
    for(int i=0;i<100;i=i+1){
        if(i<numEdges){
            edges[i][0]=edgeData[i][0];
            edges[i][1]=edgeData[i][1];
            edges[i][2]=edgeData[i][2];
        }
    }
    
    for(int i=0;i<100-1;i=i+1){
        for(int j=0;j<100-i-1;j=j+1){
            if(j<numEdges-1){
                if(edges[j][2]>edges[j+1][2]){
                    int t0=edges[j][0];
                    int t1=edges[j][1];
                    int t2=edges[j][2];
                    edges[j][0]=edges[j+1][0];
                    edges[j][1]=edges[j+1][1];
                    edges[j][2]=edges[j+1][2];
                    edges[j+1][0]=t0;
                    edges[j+1][1]=t1;
                    edges[j+1][2]=t2;
                }
            }
        }
    }
    
    for(int i=0;i<100;i=i+1){
        if(i<numEdges){
            int u=edges[i][0];
            int v=edges[i][1];
            int w=edges[i][2];
            int x=u;
            int y=v;
            
            while(parent[x]!=x){
                int temp=parent[x];
                parent[x]=parent[temp];
                x=temp;
            }
            while(parent[y]!=y){
                int temp=parent[y];
                parent[y]=parent[temp];
                y=temp;
            }
            
            if(x!=y){
                mstWeight=mstWeight+w;
                parent[x]=y;
            }
        }
    }
    
    return;
}
