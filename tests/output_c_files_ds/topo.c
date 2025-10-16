void topologicalSort(int graph[100][100],int n){  
    int inDegree[100];  
    int stack[100];  
    int top;  
    int i;  
    int j;  
    int node;  
    top=-1;  
    for(i=0;i<100;i=i+1){  
        inDegree[i]=0;  
    }  
    for(i=0;i<n;i=i+1){  
        for(j=0;j<n;j=j+1){  
            if(graph[j][i]!=0){  
                inDegree[i]=inDegree[i]+1;  
            }  
        }  
    }  
    for(i=0;i<n;i=i+1){  
        if(inDegree[i]==0){  
            top=top+1;  
            stack[top]=i;  
        }  
    }  
    while(top!=-1){  
        node=stack[top];  
        top=top-1;  
        for(i=0;i<n;i=i+1){  
            if(graph[node][i]!=0){  
                inDegree[i]=inDegree[i]-1;  
                if(inDegree[i]==0){  
                    top=top+1;  
                    stack[top]=i;  
                }  
            }  
        }  
    }  
    return;  
}
