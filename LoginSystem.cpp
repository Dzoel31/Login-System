#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>
#include <vector>

#define nL << endl
using namespace std;

void daftar()
{
    system("cls");
    string namaPengguna, NIM, password, currentData;
    int status = 1;
    fstream data;
    vector<vector<string>> dataAccount;
    cout << "####### Registrasi #######" nL;
    cout << "Silakan masukkan data Anda" nL;
    cout << "Nim : ";
    cin >> NIM;
    fflush(stdin);
    cout << "Nama : ";
    getline(cin, namaPengguna);
    cout << "Kata sandi : ";
    cin >> password;

    data.open("database.txt", ios::in);

    while (getline(data, currentData))
    {
        istringstream str(currentData);
        string strSplit;
        vector<string> temp;
        while (getline(str, strSplit, ','))
        {
            temp.push_back(strSplit);
        }
        dataAccount.push_back(temp);
    }
    data.close();
    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (NIM == dataAccount[i][0])
        {
            cout << "Akun sudah terdaftar!" nL;
            status = 0;
            break;
        }
    }

    if (status == 1)
    {
        data.open("database.txt", ios::app);
        if (data.is_open())
        {
            data << NIM + "," + namaPengguna + "," + password nL;
            data.close();
        }
        else
        {
            cout << "File tidak dapat dibuka!" nL;
        }
    }
}

void login()
{
    system("cls");
    string NIM, currentData, password;
    char c;
    int j;
    bool check = true;
    ifstream data("database.txt");
    vector<vector<string>> dataAccount;

    cout << "####### Login #######" nL;
    cout << "Masukkan NIM : ";
    cin >> NIM;
    cout << "password : ";
    cin >> password;

    if (data.is_open())
    {
        while (getline(data, currentData))
        {
            istringstream str(currentData);
            string strSplit;

            vector<string> temp;
            while (getline(str, strSplit, ','))
            {
                temp.push_back(strSplit);
            }
            dataAccount.push_back(temp);
        }
    }
    else
    {
        cout << "File tidak bisa dibuka!" nL;
    }

    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (NIM == dataAccount[i][0])
        {
            check = true;
            if (password == dataAccount[i][2])
            {
                cout << "Selamat datang " << dataAccount[i][1] nL;
            }
            else
            {
                cout << "password salah!" nL;
            }
            break;
        }
        else
        {
            check = false;
        }
    }

    if (check == false)
    {
        cout << "Akun belum terdaftar!" nL;
    }

    data.close();
}
int main()
{
    int pilihMenu;
    char ulang;
    do
    {
        system("cls");
        cout << "==========" nL;
        cout << "[1] Daftar" nL;
        cout << "[2] Login" nL;
        cout << "[0] keluar" nL;
        cout << "Pilih menu : ";
        cin >> pilihMenu;
        switch (pilihMenu)
        {
        case 1:
            daftar();
            break;
        case 2:
            login();
            break;
        case 0:
            cout << "Exit program...";
            exit(1);
            break;
        default:
            cout << "Tidak ada menu yang sesuai!" nL;
            cout << "Enter untuk mengulang!";
            break;
        }
        cout << "Ingin melanjutkan proses? (y/t) : ";
        cin >> ulang;
    } while (ulang != 't');

    return 0;
}
