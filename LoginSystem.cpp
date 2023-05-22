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

    if (data.is_open())
    {
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
    }
    else
    {
        cout << "File tidak dapat dibuka!" nL;
    }
    if (status == 1)
    {
        data.open("database.txt", ios::app);
        if (data.is_open())
        {
            data << NIM + " " + namaPengguna + " " + password nL;
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
            string currentNIM, currentUser, currentPassword;

            str >> currentNIM >> currentUser >> currentPassword;
            if (NIM == currentNIM)
            {
                check = true;
                if (password == currentPassword)
                {
                    cout << "Selamat datang " << currentUser nL;
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
    }
    else
    {
        cout << "File tidak bisa dibuka!" nL;
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
