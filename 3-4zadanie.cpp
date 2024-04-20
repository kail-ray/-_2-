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
            /*if (bits[i]==1){//каждая восьмая единица инвертируется
                h++;
                if (h==8){
                    bits[i]=0;
                    h=0;
                }
            }
*/
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



std::cout<<"ФАЙЛ ДО МАСКИРОВАНИЯ"<<std::endl;
std::ifstream file("file1.txt", std::ios::binary); // Открываем файл в бинарном режиме для чтения

    if (!file.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end); // Переходим к концу файла
    std::streampos fileSize = file.tellg(); // Получаем размер файла
    file.seekg(0, std::ios::beg); // Перемещаем указатель на начало файла

    std::vector<char> buffer(fileSize); // Создаем буфер для считывания файла
    file.read(buffer.data(), fileSize); // Считываем данные файла

    file.close(); // Закрываем файл

    std::vector<int> charCount(256, 0); // Инициализируем счетчики для каждого символа (8 бит)

    for (char c : buffer) {
        for (int i = 0; i < 256; ++i) {
            if (c == static_cast<char>(i)) {
                charCount[i]++;
            }
        }
    }

    // Выводим статистику встречаемости каждого символа
  for (int i = 0; i < 256; ++i) {
    double frequency = static_cast<double>(charCount[i]) / fileSize;
    //char ch = static_cast<char>(i);
    std::cout <<""<<" "<< frequency << std::endl;
}



std::cout<<std::endl<<std::endl<<std::endl;
std::cout<<"ФАЙЛ ПОСЛЕ МАСКИРОВАНИЯ"<<std::endl;

std::ifstream file1("file2.txt", std::ios::binary); // Открываем файл в бинарном режиме для чтения

    if (!file1.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    file1.seekg(0, std::ios::end); // Переходим к концу файла
    std::streampos fileSize1 = file1.tellg(); // Получаем размер файла
    file1.seekg(0, std::ios::beg); // Перемещаем указатель на начало файла

    std::vector<char> buffer1(fileSize1); // Создаем буфер для считывания файла
    file1.read(buffer1.data(), fileSize1); // Считываем данные файла

    file1.close(); // Закрываем файл

    std::vector<int> charCount1(256, 0); // Инициализируем счетчики для каждого символа (8 бит)

    for (char c : buffer1) {
        for (int i = 0; i < 256; ++i) {
            if (c == static_cast<char>(i)) {
                charCount1[i]++;
            }
        }
    }

    // Выводим статистику встречаемости каждого символа
  for (int i = 0; i < 256; ++i) {
    double frequency = static_cast<double>(charCount1[i]) / fileSize1;
    //char ch = static_cast<char>(i);
    std::cout <<""<<" "<< frequency << std::endl;
}

    return 0;
}