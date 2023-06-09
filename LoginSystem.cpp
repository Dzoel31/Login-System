#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define nL << endl
using namespace std;

auto readData()
{
    ifstream data("kelas_B.txt");
    vector<vector<string>> dataAccount;
    string currentData, subString, strSplit;
    if (!data.is_open())
    {
        return dataAccount;
    }
    else
    {
        while (getline(data, currentData))
        {
            subString = currentData.substr(1, (currentData.length() - 1));
            istringstream strEdit(subString);
            vector<string> temp;
            while (getline(strEdit, strSplit, ';'))
            {
                temp.push_back(strSplit);
            }
            dataAccount.push_back(temp);
        }
        data.close();
        return dataAccount;
    }
}

void writeData(vector<vector<string>> dataAccount)
{
    ofstream data("kelas_B.txt");
    for (auto baris : dataAccount)
    {
        data << "#";
        for (int i = 0; i < baris.size(); i++)
        {
            data << baris[i];
            if (i != baris.size() - 1)
            {
                data << ";";
            }
        }
        data nL;
    }
    data.close();
}
bool validatePassword(string NIM, string password)
{
    bool hasNumber, hasUpper, match;
    hasNumber = hasUpper = match = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (isupper(password[i]) && i < 2)
        {
            hasUpper = true;
        }
        if (isdigit(password[i]) && i > 2)
        {
            hasNumber = true;
        }
    }
    if (hasUpper && hasNumber && (NIM == password.substr(2, password.length() - 1)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void daftar()
{
    system("cls");
    string namaPengguna, NIM, password;
    bool check = true;
    fstream data;
    vector<vector<string>> dataAccount = readData();
    cout << "####### Registrasi #######" nL;
    cout << "Silakan masukkan data Anda" nL;
    cout << "Nim : ";
    cin >> NIM;
    cin.ignore();
    cout << "Nama : ";
    getline(cin, namaPengguna);
    cout << "Password : ";
    cin >> password;

    if (NIM.length() == 10)
    {
        if (namaPengguna.length() <= 20)
        {
            if (password.length() == 12)
            {
                if (validatePassword(NIM, password))
                {
                    for (int i = 0; i < dataAccount.size(); i++)
                    {
                        if (NIM == dataAccount[i][0] || password == dataAccount[i][2])
                        {
                            cout << "NIM atau password tidak dapat digunakan!" nL;
                            check = false;
                            break;
                        }
                    }

                    if (check)
                    {
                        data.open("kelas_B.txt", ios::app);
                        if (data.is_open())
                        {
                            data << "#" + NIM + ";" + namaPengguna + ";" + password nL;
                            cout << "Akun berhasil didaftarkan!" nL;
                            data.close();
                        }
                        else
                        {
                            cout << "File tidak dapat dibuka!" nL;
                        }
                    }
                }
                else
                {
                    cout << "Password harus terdiri dari 2 huruf kapital dan diikuti oleh NIM anda!" nL;
                    check = false;
                }
            }
            else
            {
                cout << "Panjang password minimal 12 karakter!" nL;
                check = false;
            }
        }
        else
        {
            cout << "Panjang nama tidak boleh lebih dari 20 karakter!" nL;
            check = false;
        }
    }
    else
    {
        cout << "Panjang NIM harus 10 karakter!" nL;
        check = false;
    }
    if (!check)
    {
        cin.get();
        cin.ignore();
        daftar();
    }
}

void login()
{
    system("cls");
    string NIM, currentData, password;
    char c;
    int j;
    bool check = true;
    vector<vector<string>> dataAccount = readData();

    cout << "####### Login #######" nL;
    cout << "Masukkan NIM : ";
    cin >> NIM;
    cout << "password : ";
    cin >> password;

    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (NIM == dataAccount[i][0])
        {
            check = true;
            if (password == dataAccount[i][2])
            {
                system("cls");
                cout << "Selamat datang" nL;
                cout << "NIM : " << dataAccount[i][0] nL;
                cout << "Nama : " << dataAccount[i][1] nL;
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
}

void deleteData(string NIM)
{
    system("cls");
    vector<vector<string>> dataAccount = readData();
    bool unRegistered = true;
    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (dataAccount[i][0] == NIM)
        {
            unRegistered = false;
            dataAccount.erase(dataAccount.begin() + i);
        }
    }
    if (unRegistered)
    {
        cout << "Akun belum terdaftar!" nL;
    }
    else
    {
        cout << "Data " + NIM + " berhasil dihapus!" nL;
        writeData(dataAccount);
    }
}

void updateData(string NIM)
{
    system("cls");
    vector<vector<string>> dataAccount = readData();
    string newPassword;
    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (dataAccount[i][0] == NIM)
        {
            cout << "Password lama anda : " << dataAccount[i][2] nL;
            cout << "Password baru anda : ";
            cin >> newPassword;
            if (newPassword == dataAccount[i][2])
            {
                cout << "Password lama dan baru anda sama, tidak terjadi perubahan!" nL;
            }
            else
            {

                while (!validatePassword(NIM, newPassword))
                {
                    cout << "Password harus terdiri dari 2 huruf kapital dan diikuti oleh NIM Anda!\nTekan enter untuk mengulang!\n";
                    cin.get();
                    cin.ignore();
                    system("cls");
                    cout << "Password lama anda : " << dataAccount[i][2] nL;
                    cout << "Password baru anda : ";
                    cin >> newPassword;
                }
                dataAccount[i][2] = newPassword;
                cout << "Password anda berhasil diubah!" nL;
            }
        }
    }
    writeData(dataAccount);
}

void lihatData()
{
    system("cls");
    ifstream data("kelas_B.txt");
    string currentData;
    while (getline(data, currentData))
    {
        cout << currentData nL;
    }
}

int main()
{
    int pilihMenu;
    char ulang;
    string NIM;
    do
    {
        system("cls");
        cout << "==========" nL;
        cout << "[1] Regis" nL;
        cout << "[2] Login" nL;
        cout << "[3] Lihat Data" nL;
        cout << "[4] Delete" nL;
        cout << "[5] Update" nL;
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
        case 3:
            lihatData();
            break;
        case 4:
            cout << "Masukkan NIM akun yang akan dihapus : ";
            cin >> NIM;
            deleteData(NIM);
            break;
        case 5:
            cout << "Masukkan NIM akun : ";
            cin >> NIM;
            updateData(NIM);
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
        cout << "\nIngin melanjutkan proses? (y/t) : ";
        cin >> ulang;
    } while (ulang != 't');

    return 0;
}
