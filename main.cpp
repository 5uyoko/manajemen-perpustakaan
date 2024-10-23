#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "abc123#";
const char* DB = "mydb";

class Mahasiswa {
private:
 string Id;
public:
Mahasiswa() : Id("") {}

void setId(string id) {
  Id = id;
 }
 
 string getId() {
  return Id;
 }
 
};

class Perpustakaan {
private:
 string Nama;
 int Jumlah;
public:
Perpustakaan() : Nama(""), Jumlah(0) {}

void setNama(string nama) {
  Nama = nama;
}

void setJumlah(int jumlah) {
  Jumlah = jumlah;
}

int getJumlah() {
  return Jumlah;
}
string getNama() {
  return Nama;
}

	
};

void admin(MYSQL* conn, Perpustakaan p, Mahasiswa m){
	bool tutup = false;
	while(!tutup){
	int pilihan;
cout << "1. Tambah Buku." << endl;
 cout << "2. Tambah Mahasiswa." << endl;
 cout << "0. Keluar." << endl;
 cout << "Masukkan Pilihan: ";
 cin >> pilihan;
 
 if(pilihan == 1){
 	system("cls");
string nama;
int jumlah;

cout<<"Nama Buku: ";
cin>>nama;
p.setNama(nama);

cout<<"Masukkan Jumlah: ";
cin>>jumlah;
p.setJumlah(jumlah);

int Jml = p.getJumlah();
stringstream ss;
ss<<Jml;
string Sml = ss.str();

string buku = "INSERT INTO lib (Nama,Jumlah) VALUES('"+p.getNama()+"', '"+Sml+"') ";
if(mysql_query(conn,buku.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Buku Berhasil Ditambahkan"<<endl;
}
 }// if1
 
 else if(pilihan == 2){
 	system("cls");
string id;
 cout << "Masukkan NIM Mahasiswa: ";
 cin >> id;
 m.setId(id);
 
  string st = "INSERT INTO mahasiswa (Id) VALUES('" + m.getId() + "')";
 if (mysql_query(conn, st.c_str())) {
 cout << "Error: " << mysql_error(conn) << endl;
 }
else {
  cout << "Mahasiswa Berhasil Ditambahkan" << endl; 
}
}//if2
else if(pilihan == 0){
	tutup = true;
	cout<<"Sistem ditutup"<<endl;
}
	}//while
Sleep(3000);
}//function

//fungsi tampilan
void tampilkan(MYSQL* conn){
	system("cls");
cout<<"Buku yang Tersedia"<<endl;
cout<<"******************"<<endl;

string tampil = "SELECT * FROM lib";
 if (mysql_query(conn, tampil.c_str())) {
  cout << "Error: " << mysql_error(conn) << endl;
 }
 else{
 	MYSQL_RES* res;
 	res= mysql_store_result(conn);
 	if(res){
 		int num= mysql_num_fields(res);
 	MYSQL_ROW row;
 	while(row=mysql_fetch_row(res)){
 		for(int i=0; i< num; i++){
 			cout<<" "<<row[i];
		 }
		cout<<endl;
	 }
	 mysql_free_result(res);
	 }
 }
}

//fungsi cek buku

int cekBuku(MYSQL* conn, string NamaBuku){
string exist = "SELECT Nama, Jumlah FROM lib WHERE Nama = '" + NamaBuku + "'";
if (mysql_query(conn, exist.c_str())) {
 cout << "Error: " << mysql_error(conn) << endl;
 }
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
	int num = mysql_num_fields(res);
MYSQL_ROW row;
while(row=mysql_fetch_row(res)){
	for(int i=0; i< num; i++){
	if(NamaBuku == row[i]){
	int jumlah = atoi(row[i+1]);
	return jumlah;	
	}
	else{
		cout<<"Buku Tidak Ditemukan."<<endl;
	}
	}
} 
mysql_free_result(res);
}
	
}//else if exist
return 0;
Sleep(5000);
}//function

//fungsi user

void pengguna(MYSQL* conn, Perpustakaan p, Mahasiswa m){
	system("cls");
	tampilkan(conn);
string Sid;
cout<<"Masukkan NIM Anda: ";
cin>>Sid;

string com = "SELECT * FROM mahasiswa WHERE Id = '"+Sid+"'";
 if (mysql_query(conn, com.c_str())) {
   cout << "Error: " << mysql_error(conn) << endl;
 }
 else{
MYSQL_RES* res;
res=mysql_store_result(conn);
if(res){
	int num= mysql_num_rows(res);
	if(num==1){
		cout<<"NIM Mahasiswa Ditemukan."<<endl;
	string NamaBuku;
	cout<<"Masukkan Nama Buku: ";
	cin>>NamaBuku;
	if(cekBuku(conn,NamaBuku) > 0){
		int jumlahBuku = cekBuku(conn,NamaBuku)-1;
		stringstream ss;
		ss<<jumlahBuku;
		string Sml = ss.str();

string upd ="UPDATE lib SET Jumlah ='"+Sml+"' WHERE Nama = '"+NamaBuku+"' ";
if(mysql_query(conn,upd.c_str())){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Buku tersedia. Meminjam Buku...."<<endl;
}
	}
	else{
		cout<<"Buku tidak tersedia."<<endl;
	}
	}
else if(num==0){
	cout<<"Mahasiswa ini Belum Terdaftar."<<endl;
}
}
mysql_free_result(res);
 }	
}

int main() {
	Mahasiswa m;
	Perpustakaan p;

MYSQL* conn;
conn = mysql_init(NULL);

if(!mysql_real_connect(conn,HOST, USER, PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Terhubung ke Database!"<<endl;
}
Sleep(3000);
bool keluar = false;
while(!keluar){
	system("cls");
	int val;
cout << "Selamat Datang di Sistem Manajemen Perpustakaan" << endl;
cout << "**********************************************" << endl;
cout << "1. Administrasi." << endl;
cout << "2. Pengguna." << endl;
cout << "0. Keluar." << endl;
cout<<"Masukkan Pilihan: ";
cin>>val;

if(val==1){
	system("cls");
admin(conn,p,m);	
}//if1 main

else if(val==2){
pengguna(conn,p,m);
Sleep(5000);	
}
else if(val==0){
	keluar = true;
	cout<<"Sampai Jumpa!"<<endl;
	Sleep(3000);
}

}//while
mysql_close(conn);
	return 0;
}

