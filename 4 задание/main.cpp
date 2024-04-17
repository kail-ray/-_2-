#include <iostream>
#include <bitset>
#include <random>
#include <vector>
#include <fstream>

std::bitset<8> calculateModuloSum() {
    // Объявляем переменные для хранения битовых массивов и результатов
    std::bitset<19> b1, sum1, s1, n1;
    std::bitset<118> b2, sum2, s2, n2;
    
    // Генерация случайных значений для массивов бит
    //std::random_device rd;
    std::mt19937 gen(1234);
    std::uniform_int_distribution<> dis(0, 1);

    // Заполнение первого массива бит случайными значениями
    for (int i = 0; i < 19; ++i) {
        b1[i] = dis(gen);
    }


    // Заполнение второго массива бит случайными значениями
    for (int i = 0; i < 118; ++i) {
        b2[i] = dis(gen);
    }

    // Объявляем переменную для хранения результата операции
    std::bitset<8> result;

    // Выполняем вычисления суммы по модулю 2 для последних двух разрядов
    for (int i = 0; i < 8; ++i) {
        // Вычисляем сумму по модулю 2 для первого массива бит
        s1 = 1;
        n1 = 128;
        sum1 = (b1 & s1) ^ ((b1 & n1) >> 7) & s1;
        b1 = (b1 >> 1) | (sum1 << 18);

        // Вычисляем сумму по модулю 2 для второго массива бит
        s2 = 1;
        n2 = 8589934592;
        sum2 = (b2 & s2) ^ ((b2 & n2) >> 33) & s2;
        b2 = (b2 >> 1) | (sum2 << 117);

        // Получаем результат сравнения последних разрядов и сохраняем его
        result[i] = b1[18] ^ b2[117];
    }

    // Возвращаем результат
    return result;
}

// Функция для чтения данных из файла с бинарным форматом и записи их в новый файл
void readWriteBinaryFile(const std::string& inputFileName, const std::string& outputFileName) {
    // Открываем входной файл для чтения и выходной файл для записи в бинарном режиме
    std::ifstream inputFile(inputFileName, std::ios::binary);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    // Проверяем, успешно ли открыли файлы
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Не удалось открыть файлы." << std::endl;
        return;
    }

    char buffer; // Буфер для считывания одного символа из файла
    std::bitset<8> bits; // Битовый набор для хранения 8 бит данных
    int h=0;  
    // Читаем данные по 8 бит из входного файла и записываем их в выходной файл
    while (inputFile.read(&buffer, sizeof(char))) {
        bits = std::bitset<8>(buffer); // Преобразуем символ в битовый набор из 8 бит
        std::bitset <8> result = calculateModuloSum();
        for (int i=0;i<8;i++){
            bits[i]=bits[i]^result[i];
            if (bits[i]==1){//каждая восьмая единица инвертируется
                h++;
                if (h==8){
                    bits[i]=0;
                    h=0;
                }
            }

        }
        //std::cout<<bits;
        //std::cout<<std::endl;

        char byte = static_cast<char>(bits.to_ulong()); // Преобразуем битовый набор обратно в символ
        outputFile.write(&byte, sizeof(char)); // Записываем символ в выходной файл
    }

    // Закрываем файлы после завершения работы
    inputFile.close();
    outputFile.close();

    std::cout << "Данные успешно считаны из файла '" << inputFileName << "' и записаны в файл '" << outputFileName << "'." << std::endl;
}

int main() {
    // Укажите имена входного и выходного файлов
    std::string inputFileName = "file1.txt";
    std::string outputFileName = "file2.txt";

    // Вызываем функцию для чтения и записи данных
    readWriteBinaryFile(inputFileName, outputFileName);
    std::ifstream file_do("file1.txt", std::ios::binary); // Открываем файл в бинарном режиме для чтения

    if (!file_do.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    // Определяем размер файла
    file_do.seekg(0, std::ios::end);
    std::streampos fileSize = file_do.tellg();
    file_do.seekg(0, std::ios::beg);

    // Вычисляем количество байт, необходимых для хранения файла в массиве
    std::vector<unsigned char> buffer(fileSize);
    std::cout<<fileSize<<std::endl;
    // Считываем данные файла в буфер
    file_do.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file_do.close(); // Закрываем файл

    // Создаем массив для хранения каждого бита
    std::vector<bool> result;
    for (size_t i = 0; i < fileSize; ++i) {
        for (int j = 7; j >= 0; --j) {
            result.push_back((buffer[i] >> j) & 1);
        }
    }
    int kk,c1=0,c0=0,c00=0,c01=0,c10=0,c11=0,c000=0,c001=0,c010=0,c011=0,c100=0,c101=0,c110=0,c111=0;
    int c0000=0,c0001=0,c0010=0,c0011=0,c0100=0,c0101=0,c0110=0,c0111=0,c1000=0,c1001=0,c1010=0,c1011=0,c1100=0,c1101=0,c1110=0,c1111=0;
    std::cout<<"РАБОТА С ФАЙЛОМ ДО МАСКИРОВАНИЯ"<<std::endl;
    std::cout<<"введите длину последовательности от 1 до 4 бит: "<<std::endl;
    std::cin>>kk;
    for (int i=0;i<fileSize;++i){
        //цикл подсчёта всех последовательностей
        if (kk==1){
        
            if (result[i]==1){
                c1++;
            }
            else{
                c0++;
            }
        }
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
    int d=fileSize;
    if (kk==1){
         //double result = static_cast<double>(c0)/d;
        std::cout<<"последовательность '0' выпадает с вероятностью: "<< static_cast<double>(c0)/d <<std::endl;
        std::cout<<"последовательность '1' выпадает с вероятностью: "<<static_cast<double>(c1)/d<<std::endl;
    }
    if (kk==2){
        std::cout<<"последовательность '00' выпадает с вероятностью: "<<static_cast<double>(c00)/(d-1)<<std::endl;
        std::cout<<"последовательность '01' выпадает с вероятностью: "<<static_cast<double>(c01)/(d-1)<<std::endl;
        std::cout<<"последовательность '10' выпадает с вероятностью: "<<static_cast<double>(c10)/(d-1)<<std::endl;
        std::cout<<"последовательность '11' выпадает с вероятностью: "<<static_cast<double>(c11)/(d-1)<<std::endl;
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c10+c01)/(d-1)<<std::endl;
    }
    if (kk==3){
        std::cout<<"последовательность '000' выпадает с вероятностью: "<<static_cast<double>(c000)/(d-2)<<std::endl;
        std::cout<<"последовательность '001' выпадает с вероятностью: "<<static_cast<double>(c001)/(d-2)<<std::endl;
        std::cout<<"последовательность '010' выпадает с вероятностью: "<<static_cast<double>(c010)/(d-2)<<std::endl;
        std::cout<<"последовательность '011' выпадает с вероятностью: "<<static_cast<double>(c011)/(d-2)<<std::endl;
        std::cout<<"последовательность '100' выпадает с вероятностью: "<<static_cast<double>(c100)/(d-2)<<std::endl;
        std::cout<<"последовательность '101' выпадает с вероятностью: "<<static_cast<double>(c101)/(d-2)<<std::endl;
        std::cout<<"последовательность '110' выпадает с вероятностью: "<<static_cast<double>(c110)/(d-2)<<std::endl;
        std::cout<<"последовательность '111' выпадает с вероятностью: "<<static_cast<double>(c111)/(d-2)<<std::endl;
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c100+c010+c001)/(d-2)<<std::endl;
       std::cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c110+c011+c101)/(d-2)<<std::endl;
    }
    if (kk==4){
        std::cout<<"последовательность '0000' выпадает с вероятностью: "<<static_cast<double>(c0000)/(d-3)<<std::endl;
        std::cout<<"последовательность '0001' выпадает с вероятностью: "<<static_cast<double>(c0001)/(d-3)<<std::endl;
        std::cout<<"последовательность '0010' выпадает с вероятностью: "<<static_cast<double>(c0010)/(d-3)<<std::endl;
        std::cout<<"последовательность '0011' выпадает с вероятностью: "<<static_cast<double>(c0011)/(d-3)<<std::endl;
        std::cout<<"последовательность '0100' выпадает с вероятностью: "<<static_cast<double>(c0100)/(d-3)<<std::endl;
        std::cout<<"последовательность '0101' выпадает с вероятностью: "<<static_cast<double>(c0101)/(d-3)<<std::endl;
        std::cout<<"последовательность '0110' выпадает с вероятностью: "<<static_cast<double>(c0110)/(d-3)<<std::endl;
        std::cout<<"последовательность '0111' выпадает с вероятностью: "<<static_cast<double>(c0111)/(d-3)<<std::endl;
        std::cout<<"последовательность '1000' выпадает с вероятностью: "<<static_cast<double>(c1000)/(d-3)<<std::endl;
        std::cout<<"последовательность '1001' выпадает с вероятностью: "<<static_cast<double>(c1001)/(d-3)<<std::endl;
        std::cout<<"последовательность '1010' выпадает с вероятностью: "<<static_cast<double>(c1010)/(d-3)<<std::endl;
        std::cout<<"последовательность '1011' выпадает с вероятностью: "<<static_cast<double>(c1011)/(d-3)<<std::endl;
        std::cout<<"последовательность '1100' выпадает с вероятностью: "<<static_cast<double>(c1100)/(d-3)<<std::endl;
        std::cout<<"последовательность '1101' выпадает с вероятностью: "<<static_cast<double>(c1101)/(d-3)<<std::endl;
        std::cout<<"последовательность '1110' выпадает с вероятностью: "<<static_cast<double>(c1110)/(d-3)<<std::endl;
        std::cout<<"последовательность '1111' выпадает с вероятностью: "<<static_cast<double>(c1111)/(d-3)<<std::endl; 
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c0100+c0010+c0001+c1000)/(d-3)<<std::endl;
        std::cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c0110+c0011+c0101+c1100+c1001+c1010)/(d-3)<<std::endl;
        std::cout<<"вероятность выпадания числа с тремя единицами "<<static_cast<double>(c0111+c1011+c1101+c1110)/(d-3)<<std::endl; 
    }


std::ifstream file_posle("file2.txt", std::ios::binary); // Открываем файл в бинарном режиме для чтения

    if (!file_posle.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    // Определяем размер файла
    file_posle.seekg(0, std::ios::end);
    std::streampos fileSize1 = file_posle.tellg();
    file_posle.seekg(0, std::ios::beg);

    // Вычисляем количество байт, необходимых для хранения файла в массиве
    std::vector<unsigned char> buffer1(fileSize1);
    std::cout<<fileSize1<<std::endl;
    // Считываем данные файла в буфер
    file_posle.read(reinterpret_cast<char*>(buffer1.data()), fileSize1);
    file_posle.close(); // Закрываем файл

    // Создаем массив для хранения каждого бита
    std::vector<bool> result1;
    for (size_t i = 0; i < fileSize1; ++i) {
        for (int j = 7; j >= 0; --j) {
            result1.push_back((buffer1[i] >> j) & 1);
        }
    }
    kk=0,c1=0,c0=0,c00=0,c01=0,c10=0,c11=0,c000=0,c001=0,c010=0,c011=0,c100=0,c101=0,c110=0,c111=0;
    c0000=0,c0001=0,c0010=0,c0011=0,c0100=0,c0101=0,c0110=0,c0111=0,c1000=0,c1001=0,c1010=0,c1011=0,c1100=0,c1101=0,c1110=0,c1111=0;
    std::cout<<"РАБОТА С ФАЙЛОМ ПОСЛЕ МАСКИРОВАНИЯ"<<std::endl;
    std::cout<<"введите длину последовательности от 1 до 4 бит: "<<std::endl;
    std::cin>>kk;
    for (int i=0;i<fileSize1;++i){
        //цикл подсчёта всех последовательностей
        if (kk==1){
        
            if (result1[i]==1){
                c1++;
            }
            else{
                c0++;
            }
        }
        if ((kk==2)and (i>0)){
            if ((result1[i]==0) and (result1[i-1]==0)){
                c00++;}
            if ((result1[i]==1) and (result1[i-1]==0)){
                c01++;}
            if ((result1[i]==0) and (result1[i-1]==1)){
                c10++;}
            if ((result1[i]==1) and (result1[i-1]==1)){
                c11++;   
            }
        }
         //если число бит = 3;
        if ((kk==3)and (i>1)){
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==0)){
                c000++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==0)){
                c001++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==0)){
                c010++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==0)){
                c011++;}
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==1)){
                c100++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==1)){
                c101++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==1)){
                c110++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==1)){
                c111++;}
            
        }
        //если число бит = 4;
        if ((kk==4)and (i>2)){
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==0)and (result1[i-3]==0)){
                c0000++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==0)and (result1[i-3]==0)){
                c0001++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==0)and (result1[i-3]==0)){
                c0010++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==0)and (result1[i-3]==0)){
                c0011++;}
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==1)and (result1[i-3]==0)){
                c0100++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==1)and (result1[i-3]==0)){
                c0101++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==1)and (result1[i-3]==0)){
                c0110++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==1)and (result1[i-3]==0)){
                c0111++;}
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==0)and (result1[i-3]==1)){
                c1000++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==0)and (result1[i-3]==1)){
                c1001++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==0)and (result1[i-3]==1)){
                c1010++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==0)and (result1[i-3]==1)){
                c1011++;}
            if ((result1[i]==0)and (result1[i-1]==0)and(result1[i-2]==1)and (result1[i-3]==1)){
                c1100++;}
            if ((result1[i]==1)and (result1[i-1]==0)and(result1[i-2]==1)and (result1[i-3]==1)){
                c1101++;}
            if ((result1[i]==0)and (result1[i-1]==1)and(result1[i-2]==1)and (result1[i-3]==1)){
                c1110++;}
            if ((result1[i]==1)and (result1[i-1]==1)and(result1[i-2]==1)and (result1[i-3]==1)){
                c1111++;}
            
        }

    }
    d=fileSize1;
    if (kk==1){
         //double result = static_cast<double>(c0)/d;
        std::cout<<"последовательность '0' выпадает с вероятностью: "<< static_cast<double>(c0)/d <<std::endl;
        std::cout<<"последовательность '1' выпадает с вероятностью: "<<static_cast<double>(c1)/d<<std::endl;
    }
    if (kk==2){
        std::cout<<"последовательность '00' выпадает с вероятностью: "<<static_cast<double>(c00)/(d-1)<<std::endl;
        std::cout<<"последовательность '01' выпадает с вероятностью: "<<static_cast<double>(c01)/(d-1)<<std::endl;
        std::cout<<"последовательность '10' выпадает с вероятностью: "<<static_cast<double>(c10)/(d-1)<<std::endl;
        std::cout<<"последовательность '11' выпадает с вероятностью: "<<static_cast<double>(c11)/(d-1)<<std::endl;
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c10+c01)/(d-1)<<std::endl;
    }
    if (kk==3){
        std::cout<<"последовательность '000' выпадает с вероятностью: "<<static_cast<double>(c000)/(d-2)<<std::endl;
        std::cout<<"последовательность '001' выпадает с вероятностью: "<<static_cast<double>(c001)/(d-2)<<std::endl;
        std::cout<<"последовательность '010' выпадает с вероятностью: "<<static_cast<double>(c010)/(d-2)<<std::endl;
        std::cout<<"последовательность '011' выпадает с вероятностью: "<<static_cast<double>(c011)/(d-2)<<std::endl;
        std::cout<<"последовательность '100' выпадает с вероятностью: "<<static_cast<double>(c100)/(d-2)<<std::endl;
        std::cout<<"последовательность '101' выпадает с вероятностью: "<<static_cast<double>(c101)/(d-2)<<std::endl;
        std::cout<<"последовательность '110' выпадает с вероятностью: "<<static_cast<double>(c110)/(d-2)<<std::endl;
        std::cout<<"последовательность '111' выпадает с вероятностью: "<<static_cast<double>(c111)/(d-2)<<std::endl;
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c100+c010+c001)/(d-2)<<std::endl;
       std::cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c110+c011+c101)/(d-2)<<std::endl;
    }
    if (kk==4){
        std::cout<<"последовательность '0000' выпадает с вероятностью: "<<static_cast<double>(c0000)/(d-3)<<std::endl;
        std::cout<<"последовательность '0001' выпадает с вероятностью: "<<static_cast<double>(c0001)/(d-3)<<std::endl;
        std::cout<<"последовательность '0010' выпадает с вероятностью: "<<static_cast<double>(c0010)/(d-3)<<std::endl;
        std::cout<<"последовательность '0011' выпадает с вероятностью: "<<static_cast<double>(c0011)/(d-3)<<std::endl;
        std::cout<<"последовательность '0100' выпадает с вероятностью: "<<static_cast<double>(c0100)/(d-3)<<std::endl;
        std::cout<<"последовательность '0101' выпадает с вероятностью: "<<static_cast<double>(c0101)/(d-3)<<std::endl;
        std::cout<<"последовательность '0110' выпадает с вероятностью: "<<static_cast<double>(c0110)/(d-3)<<std::endl;
        std::cout<<"последовательность '0111' выпадает с вероятностью: "<<static_cast<double>(c0111)/(d-3)<<std::endl;
        std::cout<<"последовательность '1000' выпадает с вероятностью: "<<static_cast<double>(c1000)/(d-3)<<std::endl;
        std::cout<<"последовательность '1001' выпадает с вероятностью: "<<static_cast<double>(c1001)/(d-3)<<std::endl;
        std::cout<<"последовательность '1010' выпадает с вероятностью: "<<static_cast<double>(c1010)/(d-3)<<std::endl;
        std::cout<<"последовательность '1011' выпадает с вероятностью: "<<static_cast<double>(c1011)/(d-3)<<std::endl;
        std::cout<<"последовательность '1100' выпадает с вероятностью: "<<static_cast<double>(c1100)/(d-3)<<std::endl;
        std::cout<<"последовательность '1101' выпадает с вероятностью: "<<static_cast<double>(c1101)/(d-3)<<std::endl;
        std::cout<<"последовательность '1110' выпадает с вероятностью: "<<static_cast<double>(c1110)/(d-3)<<std::endl;
        std::cout<<"последовательность '1111' выпадает с вероятностью: "<<static_cast<double>(c1111)/(d-3)<<std::endl; 
        std::cout<<"вероятность выпадания числа с одной единицей "<<static_cast<double>(c0100+c0010+c0001+c1000)/(d-3)<<std::endl;
        std::cout<<"вероятность выпадания числа с двумя единицами "<<static_cast<double>(c0110+c0011+c0101+c1100+c1001+c1010)/(d-3)<<std::endl;
        std::cout<<"вероятность выпадания числа с тремя единицами "<<static_cast<double>(c0111+c1011+c1101+c1110)/(d-3)<<std::endl; 
    }


    return 0;
}