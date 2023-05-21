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
    cout << "####### Registrasi #######" nL;
    cout << "Silakan masukkan data Anda" nL;
    cout << "Nim : ";
    cin >> NIM;
    cout << "Nama : ";
    cin >> namaPengguna;
    cout << "Kata sandi : ";
    cin >> password;

    data.open("database.txt", ios::in);

    while (getline(data, currentData))
    {
        istringstream str(currentData);
        string currentNIM, currentUser, currentPassword;

        str >> currentNIM >> currentUser >> currentPassword;
        if (NIM == currentNIM)
        {
            cout << "Akun sudah terdaftar!" nL;
            status = 0;
            break;
        }
    }
    data.close();
    if (status == 1)
    {
        data.open("database.txt", ios::app);
        data << NIM + " " + namaPengguna + " " + password nL;
        data.close();
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
    vector<vector<string>> listData;

    cout << "####### Login #######" nL;
    cout << "Masukkan NIM : ";
    cin >> NIM;
    cout << "password : ";
    do
    {
        c = getch();
        switch (c)
        {
        case 0:
            getch();
            break;
        case 13:
            cout nL;
            break;
        case 8:
            if (password.length() > 0)
            {
                password.erase(password.end() - 1);
                cout << c << ' ' << c;
            }
            break;

        default:
            password += c;
            cout << "*";
            break;
        }
    } while (c != 13);

    int status = 0;
    while (getline(data, currentData))
    {
        istringstream str(currentData);
        string currentNIM, currentUser, currentPassword;

        str >> currentNIM >> currentUser >> currentPassword;
        listData.push_back({currentNIM, currentUser, currentPassword});
    }

    for (int i = 0; i < listData.size(); i++)
    {
        if (NIM == listData[i][0])
        {
            check = true;
            if (password == listData[i][2])
            {
                cout << "Selamat datang " << listData[i][1] nL;
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
