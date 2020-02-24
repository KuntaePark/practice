#include<iostream>
#include<cstring>

#define MAX 1000000
//13458

int main() {
    int n, b, c, t;
    int A[MAX];
    long long count = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d %d", &b, &c);
    
    for(int i = 0; i < n; i++) {
        t = A[i];
        count++;
        if(t > b) {
            t -= b;
            count += t/c;
            if(t%c != 0) count++;
        }
    }
    std::cout<<count;
}