#include "ackerman.h"


long long ackerman::ack(int m,int n){
    if (m == 0) return n + 1;
    if (m > 0 && n == 0) return ack(m - 1, 1);
    else return ack(m - 1, ack(m, n - 1));
}
