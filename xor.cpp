#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <bitset>
#include <conio.h>
#include <windows.h>
using namespace std;

string SZYFROWANIE(string,string);

int main()
{
//INICIALIZATION OF FILE
    fstream plik;
    plik.open("data_encrypted.txt", ios::in | ios::binary);
    if( plik.good() != true ){
    cout << "Access to file is prohibited!" << endl;
    }

//VARIABLES
    bool IsEncrypted;
    string klucz,temp,start;

//CLEAN FILE AND LOAD CONTENT
    plik.seekg(0, ios::end);
    int length = plik.tellg();
    plik.seekg(0, ios::beg);
    char* content = new char[length];
    plik.read(content,length);

//CHANGE CONTENT TO STRING
    for(int i=0;i<length;i++) temp += content[i];

//IS FILE ENCRYPTED #1
    start=temp.substr(0,7);
    if(start=="XXIOIXX") IsEncrypted=false;
    else IsEncrypted=true;


//CLEAN FILE
    plik.close();



////////////////////////  MAIN LOOP  //////////////////////////////////////////////////////////////
bool petla=1;
while(petla)
{


//KEY
    cout<<"Type key: ";
    cin>>klucz;
plik.open("data_encrypted.txt", ios::trunc | ios::out | ios::binary);

//ENCRYPTION
temp=SZYFROWANIE(temp,klucz);

start=temp.substr(0,7);
 if((start!="XXIOIXX")&&(IsEncrypted==true))
 {
     temp=SZYFROWANIE(temp,klucz);
     cout<<"Wrong password! Try again."<<endl;
     _getch();
 }
    else petla=false;
    system("cls");

    //WRITE TO FILE
    plik.write(temp.data(),temp.size());
    plik.close();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
return 0;
}




//ENCRYPTION/DECRYPTION
string SZYFROWANIE(string temp, string klucz)
{
    for(int i=0;i<temp.length();i++)
    {
        temp[i]^=klucz[i%klucz.length()];
    }
    return temp;
}
