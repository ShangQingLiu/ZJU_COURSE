/* author: sql
 * date 2018/04/14
 */
#include <iostream>
#include <string>
#include <cstring>
#include <streambuf>
#include <fstream>
#include <algorithm>
#define MAX 10
int H/* total number of contest hour*/,
        N/*total number of problems*/,
        t0/*reading time*/;
        std::string problemDes[MAX];//
int finishTime[MAX];
int debugTime[MAX];
//finish part
int finishMark[MAX];
int resultTotalTime;
int resultProblemOrder[MAX];
int tmpProblemOrder[MAX];
int RNP = 0;//result number of problems
std::string k;
void updateSolution(int NP,int rankTime){
    if(NP>RNP){//若是这次的方式能做更多题 那就选这个
        resultTotalTime = rankTime;
        RNP = NP;
        std::copy(tmpProblemOrder, tmpProblemOrder + NP, resultProblemOrder);
    }
    else if(NP == RNP && rankTime<resultTotalTime){//如果能做一样多题 却花较少时间 选这个
        resultTotalTime = rankTime;
        RNP = NP;
        std::copy(tmpProblemOrder,tmpProblemOrder+NP,resultProblemOrder);
    }
    else{
        return;
    }
}
void searchSolution(int NP,int rankTime, int spendTime ){
    auto FTF = [&](){ return spendTime + finishTime[tmpProblemOrder[NP]];};
    int FT = FTF();
    int DTS = (FT-1)/60;
    int newSpendTime = FT + DTS*debugTime[tmpProblemOrder[NP]];
    int newRankTime = rankTime+newSpendTime+DTS*20;
    //超时
    if(newSpendTime>H*60){
        updateSolution(NP,rankTime);
    }
    //finish
    else if(++NP<N){
        int index = 0;
       std::for_each(finishMark, finishMark+N, [&](int& a){
           if(a!=1){
               a = 1;
               tmpProblemOrder[NP] = index;
               searchSolution(NP,newRankTime,newSpendTime);
               a = 0;
           }
           index++;

       });
    }
    else{
        updateSolution(NP,newRankTime);
    }
}
int main() {
    //重定向数据
    //method1
    //std::streambuf *backup;
    //std::ifstream fin;
    //fin.open("C:\\Users\\ShangChingLiu\\CLionProjects\\ROPCR\\in.txt",std::ios::in);
    //backup = std::cin.rdbuf();
    //std::cin.rdbuf(fin.rdbuf());
    //读入数据
    std::cin>>H;
    if(std::cin.fail()){
        return 0;
    }
    //std::cout<<H;
    while(H>0){//代表没有结束
       std::cin>>N>>t0;
       for(int i = 0; i<N; i++){//读入N题
           std::cin>>problemDes[i]>>finishTime[i]>>debugTime[i];
       }
        RNP = 0;
       resultTotalTime = ~(1<<31);
       std::memset(resultProblemOrder,0, sizeof(resultProblemOrder));
       std::memset(finishMark,0, sizeof(finishMark));
       std::memset(tmpProblemOrder,0, sizeof(tmpProblemOrder));
       for(int i = 0; i<N;i++){
           finishMark[i] = 1;
           tmpProblemOrder[0] = i;
           int NP = 0;
           int rankTime = 0;
           searchSolution(NP,rankTime,t0);
           finishMark[i] = 0;
       }
       std::cout<<"Total time = "<<resultTotalTime<<std::endl;
       std::for_each(resultProblemOrder,resultProblemOrder+RNP,[](int &i){std::cout<<problemDes[i]<<std::endl;});
       std::cin>>H;
    }
    return 0;
}