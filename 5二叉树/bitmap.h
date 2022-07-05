#include "stdio.h"
#include<cstring>
class Bitmap {
private:
    char* M;//比特图所存放的空间M[]
    int N;//容量为N*sizeof(char)*8的比特
protected:
    void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); }
public:
    Bitmap(int n = 8) { init(n); }
    Bitmap(char* file, int n = 8)
    {
        init(n);FILE* fp = fopen(file, "r");fread(M, sizeof(char), N fp);fclose(fp);
    }
    ~Bitmap() { delete[]M = NULL; }

    void set(int k) {}
    void clear(int k) {}
    bool test(int k) { return; }

    void expand(int k) {
        if (k < 8 * N)return;
        int oldN = N;char* oldM = M;
        init(2 * k);
        memcpy_s(M, N, oldM, oldN);
        delete[]oldM;
    }
};