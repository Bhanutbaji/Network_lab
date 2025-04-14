#include<stdio.h>

void main()
{
    int bsize,n,in,out;
    int bucketstatus=0;

    printf("Enter the bucket size:\n");
    scanf("%d",&bsize);
    printf("Enter the number of packets: \n");
    scanf("%d",&n);
    printf("Enter the outgoing rate");
    scanf("%d",&out);

    for(int i=0;i<n;i++)
    {
        printf("\nEnter the incoming packet size : ");
        scanf("%d",&in);

        if(in>(bsize-bucketstatus))
        {
            printf("\nNo of packets discarded : %d",in-(bsize-bucketstatus));
            bucketstatus=bsize;
        }
        else
        {
            bucketstatus+=in;
            printf("\nThere are %d out of %d packets present in the bucket",bucketstatus,bsize);
        }
        bucketstatus-=out;
        if(bucketstatus<0)
        {
         bucketstatus=0;
        }
        printf("\nAfter outgoing : %d out of %d packets are present in the bucket",bucketstatus,bsize);
    }
}