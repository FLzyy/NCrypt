#include <iostream>
#include <fstream>
#include <random>
#include <sys/stat.h>
#include <direct.h>
#include <string>
using namespace std;

// User Input
int choice;
string file;
int keyinput;
bool Redo = true;
//

void decryptFile(string filePath, int key)
{
    fstream file, tempFile;
    string tempFilePath = "tempde.txt";

    file.open(filePath, ios::in);
    tempFile.open(tempFilePath, ios::out);

    char byte;
    while (file >> noskipws >> byte)
    {
        byte -= key;

        tempFile << byte;
    }

    file.close();
    tempFile.close();

    file.open(filePath, ios::out);
    tempFile.open(tempFilePath, ios::in);

    while (tempFile >> noskipws >> byte)
    {
        file << byte;
    }

    file.close();
    tempFile.close();

    remove(tempFilePath.c_str());
}

int generateKey()
{
    int key;

    random_device rd;
    mt19937 gen(rd());
    fstream keyFile;
    string keyFilePath = "key.txt";
    keyFile.open(keyFilePath, ios::out);

    uniform_int_distribution<> distr(-1215752191, 1215752191);
    keyFile << distr(gen) << endl;

    keyFile.close();
    keyFile.open(keyFilePath, ios::in);
    keyFile >> key;
    keyFile.close();

    return key;
}

void encryptFile(string filePath)
{
    fstream file, tempFile;
    string tempFilePath = "temp.txt";

    file.open(filePath, ios::in);
    tempFile.open(tempFilePath, ios::out);

    char byte;
    int key = generateKey();
    while (file >> noskipws >> byte)
    {
        byte += key;

        tempFile << byte;
    }

    file.close();
    tempFile.close();

    file.open(filePath, ios::out);
    tempFile.open(tempFilePath, ios::in);

    while (tempFile >> noskipws >> byte)
    {
        file << byte;
    }

    file.close();
    tempFile.close();

    remove(tempFilePath.c_str());
}

int main()
{
    while (Redo)
    {
        cout << "NCrypt - My attempt at an Encryptor.\n";
        cout << "Decrypt or Encrypt? (0 or 1): ";
        cin >> choice;

        switch (choice)
        {
        case 0:
        {
            cout << "\nEnter the local file path to your file (eg. ./Data/file.txt): ";
            cin >> file;
            std::ifstream fileA(file);
            if (fileA.is_open())
            {
                cout << "\nEnter the key used to encrypt the file (Integer):";
                cin >> keyinput;
                decryptFile(file, keyinput);
                cout << "\nFinished decrypting your file!\n";
                cout << "Do you want to restart the app (0 to stop, 1 to restart):";
                cin >> Redo;
            }
            else
            {
                cout << "\nAre you sure you entered the correct file path?\n";
                cout << "Do you want to restart the app (0 to stop, 1 to restart):";
                cin >> Redo;
            }

            break;
        }
        case 1:
        {
            cout << "\nEnter the local file path to your file (eg. ./Data/file.txt): ";
            cin >> file;
            std::ifstream fileB(file);
            if (fileB.is_open())
            {
                encryptFile(file);
                cout << "\nFinished encrypting your file!, look for key.txt for your decryption key!\n";
                cout << "Do you want to restart the app (0 to stop, 1 to restart):";
                cin >> Redo;
            }
            break;
        }
        default:
            cout << "\nPlease enter only 0 or 1\n";
            cout << "Do you want to restart the app (0 to stop, 1 to restart):";
            cin >> Redo;
        }
    }
    return 0;
}
