#include <iostream>
#include <math.h>
#include <stdio.h>

#define N 256
#define CSV_SRC "SRC.csv"
#define CSV_DFT "DFT.csv"
#define CSV_IDFT "IDFT.csv"

using namespace std;

class Calc
{
    double SRC_re[N];
    double SRC_im[N];
    double DFT_re[N];
    double DFT_im[N];
    double IDFT_re[N];
    double IDFT_im[N];

    public:
        void makeSourceData();
        void executeDFT();
        void executeIDFT();

    private:
        double calcTerm(int n, double x);
};

void Calc::makeSourceData()
{
    int i;
    FILE *pf;
    pf = fopen(CSV_SRC,"w");
    for(i = 0; i < N; i++){
        SRC_re[i] = 30 * sin(5*(2*M_PI/N)*i)+5*cos(30*(2*M_PI/N)*i);
        SRC_im[i] = 0.0;
        fprintf(pf,"%lf\n",SRC_re[i]);
    }
    fclose(pf);
}

void Calc::executeDFT()
{
    int k,n;
    FILE *pf;

    pf = fopen(CSV_DFT,"w");
    
    // fprintf(pf,"k,f,x_re,x_im,X_re,X_im\n");

    for (k = 0; k < N; k++) {
        DFT_re[k] = 0.0;
        DFT_im[k] = 0.0;
        for (n = 0; n < N; n++) {
            DFT_re[k] += SRC_re[n] * ( cos((2 * M_PI / N) * k * n))
                       + SRC_im[n] * ( sin((2 * M_PI / N) * k * n));
            DFT_im[k] += SRC_re[n] * (-sin((2 * M_PI / N) * k * n))
                       + SRC_im[n] * ( cos((2 * M_PI / N) * k * n));
        }
        fprintf(pf,"%lf %lf\n",DFT_re[k],DFT_im[k]);
    }

    fclose(pf);
}

void Calc::executeIDFT()
{
    int k, n;  // LOOPインデックス
    FILE *pf;  // ファイルポインタ

    // 出力ファイルOPEN
    pf = fopen(CSV_IDFT, "w");

    // 計算・結果出力
    for (n = 0; n < N; n++) {
        IDFT_re[n] = 0.0;
        IDFT_im[n] = 0.0;
        for (k = 0; k < N; k++) {
            IDFT_re[n] += DFT_re[k] * (cos((2 * M_PI / N) * k * n))
                        - DFT_im[k] * (sin((2 * M_PI / N) * k * n));
            IDFT_im[n] += DFT_re[k] * (sin((2 * M_PI / N) * k * n))
                        + DFT_im[k] * (cos((2 * M_PI / N) * k * n));
        }
        IDFT_re[n] /= N;
        IDFT_im[n] /= N;
        fprintf(pf,"%lf %lf\n",IDFT_re[n],IDFT_im[n]);
    }

    // 出力ファイルCLOSE
    fclose(pf);
}



int main(int argc, char const *argv[])
{
    Calc objCalc;

    objCalc.makeSourceData();

    objCalc.executeDFT();

    objCalc.executeIDFT();

    return 0;
}

