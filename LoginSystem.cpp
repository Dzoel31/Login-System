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
    while (getline(data, currentData))
    {
        subString = currentData.substr(1, (currentData.length() - 2));
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

bool validatePassword(string password)
{
    bool hasNumber, hasUpper, hasLower;
    hasNumber = hasUpper = hasLower = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (islower(password[i]))
        {
            hasLower = true;
        }
        if (isupper(password[i]))
        {
            hasUpper = true;
        }
        if (isdigit(password[i]))
        {
            hasNumber = true;
        }
    }
    if ((hasLower || hasUpper) && hasNumber)
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
    string namaPengguna, NIM, password, confirmPassword;
    bool check = true;
    fstream data;
    vector<vector<string>> dataAccount = readData();
    cout << "####### Registrasi #######" nL;
    cout << "Silakan masukkan data Anda" nL;
    cout << "Nim : ";
    cin >> NIM;
    fflush(stdin);
    cout << "Nama : ";
    getline(cin, namaPengguna);
    cout << "Password : ";
    cin >> password;

    if (NIM.length() == 10)
    {
        if (namaPengguna.length() <= 20)
        {
            if (password.length() >= 8)
            {
                if (validatePassword(password))
                {
                    cout << "Konfirmasi password : ";
                    cin >> confirmPassword;
                    for (int i = 0; i < dataAccount.size(); i++)
                    {
                        if (NIM == dataAccount[i][0])
                        {
                            cout << "NIM akun tidak dapat digunakan!" nL;
                            check = false;
                            break;
                        }
                    }

                    if (check)
                    {
                        if (password == confirmPassword)
                        {
                            data.open("kelas_B.txt", ios::app);
                            if (data.is_open())
                            {
                                data << "#" + NIM + ";" + namaPengguna + ";" + password + "#" nL;
                                cout << "Akun berhasil didaftarkan!" nL;
                                data.close();
                            }
                            else
                            {
                                cout << "File tidak dapat dibuka!" nL;
                            }
                        }
                        else
                        {
                            cout << "password tidak sesuai!" nL;
                        }
                    }
                }
                else
                {
                    cout << "Password harus terdiri dari campuran huruf besar, huruf kecil dan angka!" nL;
                    cin.get();
                    cin.ignore();
                    daftar();
                }
            }
            else
            {
                cout << "Panjang password minimal 8 karakter!" nL;
            }
        }
        else
        {
            cout << "Panjang nama tidak boleh lebih dari 20 karakter!" nL;
        }
    }
    else
    {
        cout << "Panjang NIM harus 10 karakter!" nL;
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
    fstream data;
    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (dataAccount[i][0] == NIM)
        {
            dataAccount.erase(dataAccount.begin() + i);

            dataAccount.insert(dataAccount.begin() + i, {"*"});
        }
    }
    data.open("kelas_B.txt", ios::out);
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
        data << "#" << endl;
    }
    data.close();
}

void updateData(string NIM)
{
    system("cls");
    vector<vector<string>> dataAccount = readData();
    fstream data;
    string newPassword, validatePassword;
    for (int i = 0; i < dataAccount.size(); i++)
    {
        if (dataAccount[i][0] == NIM)
        {
            cout << "Password lama anda : " << dataAccount[i][2] nL;
            cout << "Password baru anda : ";
            cin >> newPassword;
            cout << "Masukkan kembali password anda : ";
            cin >> validatePassword;
            while (newPassword != validatePassword)
            {
                cout << "Password salah!\nTekan enter untuk mengulang!\n";
                cin.get();
                cin.ignore();
                system("cls");
                cout << "Password lama anda : " << dataAccount[i][2] nL;
                cout << "Password baru anda : ";
                cin >> newPassword;
                cout << "Masukkan kembali password anda : ";
                cin >> validatePassword;
            }
            dataAccount[i][2] = newPassword;
        }
    }
    data.open("kelas_B.txt", ios::out);
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
        data << "#" << endl;
    }
    data.close();
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
        cout << "[3] Delete" nL;
        cout << "[4] Update" nL;
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
            cout << "Masukkan NIM akun yang akan dihapus : ";
            cin >> NIM;
            deleteData(NIM);
            cout << "Data " + NIM + " berhasil dihapus!" nL;
            break;
        case 4:
            cout << "Masukkan NIM akun yang akan diupdate : ";
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
