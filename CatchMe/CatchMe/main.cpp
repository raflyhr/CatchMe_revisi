/*
 * Catch Me If You Can
 * Game kejar-kejaran antara 'hero' dan 'enemy'
 * hero harus mengejar enemy yang bergerak secara acak
 * bila hero berhasil menangkap enemy, skor akan bertambah
 *
 * Kontrol
 * - ESC			keluar
 * - Panah		pergerakan
 *
 */

#include <iostream> // untuk menampilkan teks (cout)
#include <conio.h>	// untuk input keyboard non-blocking (_kbhit, _getch)
#include <cstdlib>	// untuk fungsi random (rand, srand)
#include <ctime>	// untuk waktu (sebagai seed random)
#include "cursor.h" // file eksternal untuk posisi & warna kursor

using namespace std;
using namespace cur; // agar bisa pakai fungsi gotoxy dan setcolor dari file cursor.h.

int main()
{
	system("title Catch Me If You Can"); // Mengubah judul jendela console menjadi “Catch Me If You Can”.

	// koordinat hero player
	short heroX = 30;
	short heroY = 12;

	// koordinat enemy
	short enemX = 30;
	short enemY = 5;

	// Hero mulai di tengah (30, 12)
	// Enemy mulai di atas (30, 5)
	// Koordinat (x, y) berarti:
	// x → posisi horizontal (kiri–kanan)
	// y → posisi vertikal (atas–bawah)

	// arah pergerakan disimbolkan dengan 4 karakter:
	// U	atas
	// D	bawah
	// L	kiri
	// R	kanan
	char heroDir = ' '; // arah hero
	char enemDir = 'U'; // arah enemy (awal ke atas)

	short tick = 0; // counter perulangan (arah pergantian )
	int score = 0;	// skor

	srand((unsigned int)time(NULL));
	// Digunakan agar fungsi rand() menghasilkan angka berbeda setiap kali game dijalankan (berdasarkan waktu saat ini).

	while (true) // 👉 while(true) berarti game berjalan terus sampai pemain keluar.
	{
		system("cls");
		
		// 👉 system("cls") membersihkan layar agar posisi karakter terlihat berpindah.
		

		// menggambar garis bawah
		 setcolor(10, 0); // awal hijau jadi biru score nya
		gotoxy(1, 29);
		for (int i = 0; i < 60; ++i)
			cout << char(196);
	// setcolor(3, 0) → mengatur warna teks biru (3 = biru muda, 0 = latar hitam).
	// gotoxy(1, 29) → pindah kursor ke posisi baris 29.
	// char(196) → karakter garis horizontal “─” di ASCII.
	// Tujuannya: membuat batas bawah arena game

		//  pergerakan hero player
		if (enemDir == 'U' && enemY > 2)
			enemY--;
		if (enemDir == 'L' && enemX > 2)
			enemX--;
		if (enemDir == 'D' && enemY < 28)
			enemY++;
		if (enemDir == 'R' && enemX < 59)
			enemX++;
			// Jika arah U, kurangi enemY (bergerak ke atas) tapi jangan sampai melewati batas atas (> 2).
			// Begitu juga untuk L, D, R dengan pembatas supaya musuh tidak keluar area (60x30).

		gotoxy(enemX, enemY);
		setcolor(2, 0);
		cout << char(219);
		// char(219) adalah blok penuh (█) — simbol karakter enemy.

		//
		if (heroDir == 'U' && heroY > 1)
			heroY--;
		if (heroDir == 'L' && heroX > 1)
			heroX--;
		if (heroDir == 'D' && heroY < 28)
			heroY++;
		if (heroDir == 'R' && heroX < 59)
			heroX++;
			// Jika arah U, kurangi enemY (bergerak ke atas) tapi jangan sampai melewati batas atas (> 2).

			// Begitu juga untuk L, D, R dengan pembatas supaya musuh tidak keluar area (60x30).

		gotoxy(heroX, heroY);
		setcolor(6, 0);
		cout << char(219);
		cout << char(219);
		cout << char(219);
		cout << char(219);
		cout << char(219);
		
		// char(122) adalah huruf z (z) — simbol karakter player.

		
		// menampilkan 'press ESC to exit
		gotoxy(1, 30);
		setcolor(7, 0);
		cout << "press ";
		setcolor(0, 7);
		cout << " ESC ";
		setcolor(7, 0);
		cout << " to exit";
		// Menampilkan teks “press ESC to exit” di bawah layar.

		// menampilkan score
		gotoxy(50, 30);
		setcolor(3, 0);
		cout << "score: ";
		setcolor(10, 0);
		cout << score << ' ';
		// Menampilkan skor di pojok kanan bawah.

		// mendeteksi apakah posisi hero dan enemy sama
		if (heroX == enemX && heroY == enemY)
		{
			// tambahkan score
			score++;
			Beep(440, 100);

			// reset posisi hero dan enemy
			heroX = 30;
			heroY = 12;
			enemX = 30;
			enemY = 5;

			// reset arah hero dan enemy
			heroDir = ' ';
			enemDir = ' ';
		}

// Kalau posisi hero dan enemy sama, berarti hero berhasil menangkap enemy:
// Skor bertambah.
// Suara “beep” dimainkan.
// Posisi hero dan musuh kembali ke titik awal.

		// mendeteksi input dari keyboard
		// fungsi _kbhit() memungkinkan agar perulangan
		// tetap berjalan tanpa tertahan oleh penekanan tombol
		if (_kbhit())
		{
			char key = _getch();
			if (key == 27)
				break;
			if (key == 72)
				heroDir = 'U';
			if (key == 75)
				heroDir = 'L';
			if (key == 80)
				heroDir = 'D';
			if (key == 77)
				heroDir = 'R';
		}
// _kbhit() → Mengecek apakah ada tombol ditekan.
// _getch() → Mengambil karakter dari keyboard tanpa menunggu Enter.
// Kode angka (ASCII khusus):
// 27 → ESC
// 72 → Panah Atas
// 75 → Panah Kiri
// 80 → Panah Bawah
// 77 → Panah Kanan

		// tiap 5x tick
		// acak arah pergerakan enemy
		tick++;
		if (tick >= 5)
		{
			int rnd = rand() % 12 + 1;
			if (rnd < 4)
				enemDir = 'U';
			else if (rnd < 7)
				enemDir = 'D';
			else if (rnd < 10)
				enemDir = 'L';
			else
				enemDir = 'R';

			tick = 0;
		}
// Setiap 5 kali loop (tick >= 5), arah enemy berubah acak:
// rand() % 12 + 1 menghasilkan angka antara 1–12.
// Berdasarkan angka tersebut, musuh bisa bergerak ke atas/bawah/kiri/kanan secara acak.

		Sleep(200);
		// 👉 Sleep(200) memberi jeda 200 milidetik antar frame (biar game tidak terlalu cepat).
	}

	return 0;
}