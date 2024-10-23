# Sistem Manajemen Perpustakaan

Sistem Manajemen Perpustakaan adalah aplikasi berbasis C++ yang memungkinkan pengguna untuk mengelola data buku dan mahasiswa serta meminjam buku dari perpustakaan. Aplikasi ini terhubung dengan database MySQL untuk menyimpan dan mengambil data buku serta mahasiswa.

## Fitur

- **Administrasi:**
  - Menambah buku baru ke dalam database.
  - Menambah mahasiswa baru ke dalam database.
  
- **Pengguna:**
  - Menampilkan daftar buku yang tersedia di perpustakaan.
  - Meminjam buku yang tersedia berdasarkan ID mahasiswa.

## Persyaratan Sistem

- **Software:**
  - MySQL Server
  - MySQL Connector C++
  - Windows (untuk penggunaan fungsi `Sleep()` dan `system("cls")`)

- **Library yang dibutuhkan:**
  - MySQL
  - MySQL Error
  - Windows.h (untuk fungsi `Sleep` dan `system`)

## Struktur Program

- **Kelas `Mahasiswa`:** Menyimpan data ID mahasiswa.
- **Kelas `Perpustakaan`:** Menyimpan data buku dan jumlah yang tersedia.
- **Fungsi `admin()`:** Mengelola penambahan buku dan mahasiswa ke database.
- **Fungsi `pengguna()`:** Mengelola proses peminjaman buku oleh mahasiswa.
- **Fungsi `tampilkan()`:** Menampilkan daftar buku yang tersedia di perpustakaan.

## Pengembangan Lebih Lanjut

Fitur tambahan yang dapat dikembangkan:
- Fitur pengembalian buku.
- Sistem pelacakan riwayat peminjaman.
- Implementasi antarmuka grafis pengguna (GUI).
