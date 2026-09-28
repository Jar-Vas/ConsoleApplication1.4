// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
int char_to_int(char c) {
    return c - 48;
}

int string_to_dec_int(string s) {
    if (s == "-2147483648") return -2147483648;
    int k = 1;
    if (s[0] == '-') {
        k = -1;
        s.erase(0, 1);
    }
    int last = s.length();
    int out_num = 0;
    string nums = "1234567890";
    for (char c1 : s) {
        bool m = 1;
        for (char c2 : nums) {
            if (c1 == c2) {
                m = 0;
            }
        }
        if (m) throw logic_error("invalid number");
    }
    for (int i = last - 1; i >= 0; i--) {
        if (i > last - 10) {
            out_num += char_to_int(s[i]) * (int)pow(10, last - i - 1);
        } //                                                                                147483648;
        else if (i == last - 10 and (char_to_int(s[i]) < 2 or (char_to_int(s[i]) == 2 and out_num < 147483648))) {
            out_num += char_to_int(s[i]) * (int)pow(10, last - i - 1);
        }
        else {
            throw out_of_range("number is too large");
        }
    }
    return out_num * k;
}

const int MAX_SIZE = 1000;

class MyDStack {
private:
    int maxsize = 100;
    int size;
    char* myArr;
public:

    MyDStack() : size(0) {
        myArr = new char[maxsize];
    };

    MyDStack(const MyDStack& other) : size(other.size), maxsize(other.maxsize) {
        if (maxsize > MAX_SIZE) {
            throw out_of_range("max size is " + to_string(MAX_SIZE));
        }
        myArr = new char[maxsize];
        for (int i = 0; i < size; i++) {
            myArr[i] = other.myArr[i];
        }
    };

    MyDStack& operator=(const MyDStack& other) {
        if (this == &other) {
            return *this;
        }

        delete[] myArr;

        size = other.size;
        maxsize = other.maxsize;
        myArr = new char[maxsize];

        for (int i = 0; i < size; i++) {
            myArr[i] = other.myArr[i];
        }

        return *this;
    }

    void grow(double scale) {
        maxsize = (int)(maxsize * scale) + 1;

        if (maxsize > MAX_SIZE) {
            throw out_of_range("max size is " + to_string(MAX_SIZE));
        }
        char* _myArr = new char[maxsize];
        for (int i = 0; i < size; i++) {
            _myArr[i] = myArr[i];
        }
        delete[] myArr;
        myArr = _myArr;
    }

    void add(char element) {
        if (size == maxsize) {
            grow(1.2);
        }
        myArr[size] = element;
        size++;
    }

    bool isEmpty() const {
        return !size;
    }

    bool del() {
        if (isEmpty()) {
            return false;
        }
        size--;
        return true;
    }

    bool isFul() const {
        return (size == maxsize);
    }

    void clear() {
        size = 0;
        delete[] myArr;
    }

    int GetSize() const {
        return size;
    }

    char getLast() const {
        if (isEmpty()) {
            return '\0';
        }
        return myArr[size - 1];
    }

    ~MyDStack() {
        delete[] myArr;
    }
};

int main()
{
    try {
        string snum = "2147483647";
        cout << string_to_dec_int(snum) << endl;
    }
    catch (const exception& e) {
        cout << "error: " << e.what() << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
