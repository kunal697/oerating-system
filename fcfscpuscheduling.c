#include <stdio.h>
int arr[100][6];

void FIFS(int n){
            int st=0;
        for(int i=0;i<n;i++){
            if(st<arr[i][0]){
                arr[i][2]=arr[i][0];
                arr[i][3]=arr[i][0]+arr[i][1];
                st=arr[i][3];
               
            }
            else{
                arr[i][2]=st;
                arr[i][3]=st+arr[i][1];
                st=arr[i][3];
            }
           
            arr[i][5]=arr[i][3]-arr[i][0];
            arr[i][4]=arr[i][5]-arr[i][1];
        }
}
void sort(int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i][0]>arr[j][0]){
                for(int k=0;k<2;k++){
                    int temp=arr[i][k];
                    arr[i][k]=arr[j][k];
                    arr[j][k]=temp;
                }
            }
           
        }
    }
       
}

int main()
{
    int n;
    int temp;
    printf("enter nunber of processes");
    scanf("%d",&n);
   
   
    // int arr[n][6];
    for(int i=0;i<n;i++){
     for(int j=0;j<6;j++){
           arr[i][j]=0;
           
        }
    }
   
   
    for(int i=0;i<n;i++){
          printf("enter at and bt");
        for(int j=0;j<2;j++){
           
            scanf("%d",&arr[i][j]);
           
        }
    }
   
        sort(n);
        FIFS(n);
     
       
         printf("at      bt      st      et      wt      twt\n");
    for(int i=0;i<n;i++){
       
       
        for(int j=0;j<6;j++){
           
            printf("%d \t",arr[i][j]);
           
        }
        printf("\n");
    }
    int total_waiting_time=0;
    for(int i=0;i<n;i++){
   total_waiting_time += arr[i][4];
    }

    int total_turnaround_time=0;
    for(int i=0;i<n;i++){
   total_turnaround_time += arr[i][5];
    }


    printf("avg waiting time = %d/%d",total_waiting_time,n);
    printf("avg turnaround time = %d/%d",total_turnaround_time,n);
  
    
    return 0;
}