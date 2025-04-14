#include<stdio.h>

int costMatrix[20][20],n;

struct routers
{
    int distance[20];
    int adjNode[20];
}node[20];

void readCostMatrix()
{
    int i,j;
    printf("\nEnter the cost matrix: \n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&costMatrix[i][j]);
            node[i].distance[j]=costMatrix[i][j];
            node[i].adjNode[j]=j;
        }
        costMatrix[i][i]=0;
    }
}

void calcRoutingTable()
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(node[i].distance[j]>costMatrix[i][k]+node[k].distance[j])
                {
                    node[i].distance[j]=node[i].distance[k]+node[k].distance[j];
                    node[i].adjNode[j]=k;
                }
            }
        }
    }
}

void displayRouter()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("\nRouter %d:\n",i+1);
        for(j=0;j<n;j++)
        {
            printf("\nNode %d via %d :Distance %d\n",j+1,node[i].adjNode[j]+1,node[i].distance[j]);
        }
    }
}

int main()
{
    printf("Number of nodes: ");
    scanf("%d",&n);
    readCostMatrix();
    calcRoutingTable();
    displayRouter();
    return 0;
}