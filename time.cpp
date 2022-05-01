#include <bits/stdc++.h>  //Libraries  used
#include <algorithm>
#include <sys/time.h> 
using namespace std;

long gettime() {               //Execution time function
    struct timeval start;
    gettimeofday(&start,NULL);
    return start.tv_sec*1000000+start.tv_usec; //time value in Micro sec 
}
int main(){
    long start= gettime();  //time before 
//rand_char() 
//function 
    long end= gettime();  //time after 
    cout<<"time execution = "<<end-start<<"  Micro sec"; 
//time execution = time difference between before and after  
    return 0;
}
