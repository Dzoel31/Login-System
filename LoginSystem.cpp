#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>

#define nL << endl
#define ENTER 13
#define TAB 9
#define BACKSPACE 8

using namespace std;

void daftar()
{
    string namaPengguna, NIM, password, currentData;
    int status = 1;
    fstream data;
    cout << "Silakan masukkan data Anda" nL;
    cout << "Nama : ";
    cin >> namaPengguna;
    fflush(stdin);
    cout << "Kata sandi : ";
    cin >> password;
    fflush(stdin);

    data.open("database.txt", ios::in);

    while (getline(data, currentData))
    {
        istringstream str(currentData);
        string currentNIM, currentUser, currentPassword;

        str >> currentUser >> currentPassword;
        if (namaPengguna == currentUser)
        {
            cout << "Akun sudah terdaftar!" nL;
            status = 0;
            break;
        }
    }
    data.close();
    if (status == 1)
    {
        ofstream data;
        data.open("database.txt", ios::app);
        data << namaPengguna + " " + password nL;
        data.close();
    }
}

void login()
{
    string pengguna, currentData, password;
    char c;
    int j;
    ifstream data("database.txt");

    cout << "====Login====" nL;
    cout << "Masukkan nama : ";
    cin >> pengguna;
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
        string currentUser, currentPassword;

        str >> currentUser >> currentPassword;

        if (pengguna == currentUser && password == currentPassword)
        {
            cout << "Berhasil login" nL;
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        cout << "Gagal login" nL;
        cout << "Cek username dan password anda" nL;
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
        cout << "Ingin melanjutkan proses? (y/t)";
        cin >> ulang;
    } while (ulang != 't');

    return 0;
}
