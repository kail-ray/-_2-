#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#include <bitset>

int main() 
{
    bitset<19> b1,sum1,s1,n1;
    bitset<118> b2,sum2,s2,n2;
    // Генерация рандомных значений для массива бит
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < 19; ++i) {
         b1[i] = dis(gen);
    }
    for (int i = 0; i < 118; ++i) {
         b2[i] = dis(gen);
    }
    int  d, kk,c1=0,c0=0,c00=0,c01=0,c10=0,c11=0,c000=0,c001=0,c010=0,c011=0,c100=0,c101=0,c110=0,c111=0;
    int c0000=0,c0001=0,c0010=0,c0011=0,c0100=0,c0101=0,c0110=0,c0111=0,c1000=0,c1001=0,c1010=0,c1011=0,c1100=0,c1101=0,c1110=0,c1111=0;
    cout<<"Введите число выходных бит: ";
    cin>>d;
    cout<<"Введите длину комбинации для подсчёта статистики(от 1 до 4 бит): ";
    cin>>kk;
    //size_t d2 = static_cast<size_t>(d);
    //bitset<d2> result;
    //cout<<(b2);
        //cout<<endl;
    std::vector<bool> result(d);
    for (int i=0;i<d;++i) 
    {
        //cout<<i;
        s1=1;//маска. последовательность в двоичным виде последний разряд равен 1, остальные 0
        n1=128;//маска. последовательность в двоичным виде 7 разряд равен 1, остальные 0
        sum1=(b1&s1)^((b1&n1)>>7)&s1;//сумма по модулю 2 двух последних разрядов
        b1=(b1>>1)|(sum1<<18);//перенос на 1 разряд вправо исходной последовательности и добавление числа полученного в результате суммы по модулю 2
    
        //cout<<endl;
        s2=1;//маска. последовательность в двоичным виде последний разряд равен 1, остальные 0
        n2=8589934592;//маска. последовательность в двоичным виде 33 разряд равен 1, остальные 0
        //cout<<();
       //cout<<endl;
        sum2=(b2&s2)^((b2&n2)>>33)&s2;//сумма по модулю 2 двух последних разрядов
        b2=(b2>>1)|(sum2<<117);//перенос на 1 разряд вправо исходной последовательности и добавление числа полученного в результате суммы по модулю 2
        //cout<<(b2);
       //cout<<endl;
        result[i]=(b1[18]^b2[117]);
        //cout<<result[i]<<endl;
        //если число бит = 1;
        if (kk==1){
        
            if (result[i]==1){
                c1++;
            }
            else{
                c0++;
            }
        }
         //если число бит = 2;
        if ((kk==2)and (i>0)){
            if ((result[i]==0) and (result[i-1]==0)){
                c00++;}
            if ((result[i]==1) and (result[i-1]==0)){
                c01++;}
            if ((result[i]==0) and (result[i-1]==1)){
                c10++;}
            if ((result[i]==1) and (result[i-1]==1)){
                c11++;   
            }
        }
         //если число бит = 3;
        if ((kk==3)and (i>1)){
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==0)){
                c000++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==0)){
                c001++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==0)){
                c010++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==0)){
                c011++;}
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==1)){
                c100++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==1)){
                c101++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==1)){
                c110++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==1)){
                c111++;}
            
        }
        //если число бит = 4;
        if ((kk==4)and (i>2)){
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==0)and (result[i-3]==0)){
                c0000++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==0)and (result[i-3]==0)){
                c0001++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==0)and (result[i-3]==0)){
                c0010++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==0)and (result[i-3]==0)){
                c0011++;}
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==1)and (result[i-3]==0)){
                c0100++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==1)and (result[i-3]==0)){
                c0101++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==1)and (result[i-3]==0)){
                c0110++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==1)and (result[i-3]==0)){
                c0111++;}
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==0)and (result[i-3]==1)){
                c1000++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==0)and (result[i-3]==1)){
                c1001++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==0)and (result[i-3]==1)){
                c1010++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==0)and (result[i-3]==1)){
                c1011++;}
            if ((result[i]==0)and (result[i-1]==0)and(result[i-2]==1)and (result[i-3]==1)){
                c1100++;}
            if ((result[i]==1)and (result[i-1]==0)and(result[i-2]==1)and (result[i-3]==1)){
                c1101++;}
            if ((result[i]==0)and (result[i-1]==1)and(result[i-2]==1)and (result[i-3]==1)){
                c1110++;}
            if ((result[i]==1)and (result[i-1]==1)and(result[i-2]==1)and (result[i-3]==1)){
                c1111++;}
            
        }

    }
    if (kk==1){
         //double result = static_cast<double>(c0)/d;
        cout<<"последовательность '0' выпадает с вероятностью: "<< static_cast<double>(c0)/d <<endl;
        cout<<"последовательность '1' выпадает с вероятностью: "<<static_cast<double>(c1)/d<<endl;
    }
    if (kk==2){
        cout<<"последовательность '00' выпадает с вероятностью: "<<static_cast<double>(c00)/(d-1)<<endl;
        cout<<"последовательность '01' выпадает с вероятностью: "<<static_cast<double>(c01)/(d-1)<<endl;
        cout<<"последовательность '10' выпадает с вероятностью: "<<static_cast<double>(c10)/(d-1)<<endl;
        cout<<"последовательность '11' выпадает с вероятностью: "<<static_cast<double>(c11)/(d-1)<<endl;
        cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c10+c01)/(d-1)<<endl;
    }
    if (kk==3){
        cout<<"последовательность '000' выпадает с вероятностью: "<<static_cast<double>(c000)/(d-2)<<endl;
        cout<<"последовательность '001' выпадает с вероятностью: "<<static_cast<double>(c001)/(d-2)<<endl;
        cout<<"последовательность '010' выпадает с вероятностью: "<<static_cast<double>(c010)/(d-2)<<endl;
        cout<<"последовательность '011' выпадает с вероятностью: "<<static_cast<double>(c011)/(d-2)<<endl;
        cout<<"последовательность '100' выпадает с вероятностью: "<<static_cast<double>(c100)/(d-2)<<endl;
        cout<<"последовательность '101' выпадает с вероятностью: "<<static_cast<double>(c101)/(d-2)<<endl;
        cout<<"последовательность '110' выпадает с вероятностью: "<<static_cast<double>(c110)/(d-2)<<endl;
        cout<<"последовательность '111' выпадает с вероятностью: "<<static_cast<double>(c111)/(d-2)<<endl;
        cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c100+c010+c001)/(d-2)<<endl;
        cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c110+c011+c101)/(d-2)<<endl;
    }
    if (kk==4){
        cout<<"последовательность '0000' выпадает с вероятностью: "<<static_cast<double>(c0000)/(d-3)<<endl;
        cout<<"последовательность '0001' выпадает с вероятностью: "<<static_cast<double>(c0001)/(d-3)<<endl;
        cout<<"последовательность '0010' выпадает с вероятностью: "<<static_cast<double>(c0010)/(d-3)<<endl;
        cout<<"последовательность '0011' выпадает с вероятностью: "<<static_cast<double>(c0011)/(d-3)<<endl;
        cout<<"последовательность '0100' выпадает с вероятностью: "<<static_cast<double>(c0100)/(d-3)<<endl;
        cout<<"последовательность '0101' выпадает с вероятностью: "<<static_cast<double>(c0101)/(d-3)<<endl;
        cout<<"последовательность '0110' выпадает с вероятностью: "<<static_cast<double>(c0110)/(d-3)<<endl;
        cout<<"последовательность '0111' выпадает с вероятностью: "<<static_cast<double>(c0111)/(d-3)<<endl;
        cout<<"последовательность '1000' выпадает с вероятностью: "<<static_cast<double>(c1000)/(d-3)<<endl;
        cout<<"последовательность '1001' выпадает с вероятностью: "<<static_cast<double>(c1001)/(d-3)<<endl;
        cout<<"последовательность '1010' выпадает с вероятностью: "<<static_cast<double>(c1010)/(d-3)<<endl;
        cout<<"последовательность '1011' выпадает с вероятностью: "<<static_cast<double>(c1011)/(d-3)<<endl;
        cout<<"последовательность '1100' выпадает с вероятностью: "<<static_cast<double>(c1100)/(d-3)<<endl;
        cout<<"последовательность '1101' выпадает с вероятностью: "<<static_cast<double>(c1101)/(d-3)<<endl;
        cout<<"последовательность '1110' выпадает с вероятностью: "<<static_cast<double>(c1110)/(d-3)<<endl;
        cout<<"последовательность '1111' выпадает с вероятностью: "<<static_cast<double>(c1111)/(d-3)<<endl; 
        cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c0100+c0010+c0001+c1000)/(d-3)<<endl;
        cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c0110+c0011+c0101+c1100+c1001+c1010)/(d-3)<<endl;
        cout<<"вероятность выпадания числа с тремя единицами "<<static_cast<double>(c0111+c1011+c1101+c1110)/(d-3)<<endl; 
    }
    int t;
    cout<<"введите число тетта от 1 до 32(число на которое биты будут отставать друг от друга): ";
    cin>>t;
    cout<<endl;
    int schet=0;
    for (int i=0;i<(d-t);++i){
        if (result[i]==result[i+t]){
            schet++;
        }
    }
    cout<<"количество совпавших бит "<<schet<<endl;
    cout<<"количество не совпавших бит "<<d-t-schet<<endl;
    cout<<"расчёт автокорреляции "<<static_cast<double>(schet-(d-t-schet))/(schet+(d-t-schet))<<endl;


return 0;
}