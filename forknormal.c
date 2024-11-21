#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int n=5;
void bubble_sort1(int arr[]){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]<arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }

    }
}

void bubble_sort(int arr[]){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }

    }
}
void print(int arr[]){
    printf("array is :");
    for( int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void input(int arr []){
    printf("enter the element :");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
}

int main(){
    int arr[n];
    int p=0;
    input(arr);
     printf("input array taken.");
     print (arr);

    printf("p=%d \n my pid %d \n PPid is %d \n",p,getpid(),getppid());
    p = fork();
    printf("fork started .\n");
    
    printf("p=%d \n my pid %d \n PPid is %d \n",p,getpid(),getppid());
    if(p<0){
        printf("\error fork failed!\n");
        exit(1);
    }else if(p==0){
        bubble_sort(arr);
        printf("child array is :\n");
        for(int i=0;i<n;i++){
            printf("child: %d \n ",arr[i]);
            sleep(2);
        }
       printf("p=%d \n my pid %d \n PPid is %d \n",p,getpid(),getppid());
       printf("child process over");
    }
    else{
        bubble_sort1(arr);
        printf("parrent array is: \n");
        for(int i=0;i<n;i++){
            printf("\t\t parent %d\n",arr[i]);
            sleep(3);
        }
        printf("p=%d \n my pid %d \n PPid is %d \n",p,getpid(),getppid());
        printf("\t\t parnet over \n");
    }
     printf("bye p=%d \n my pid %d \n PPid is %d \n",p,getpid(),getppid());

}