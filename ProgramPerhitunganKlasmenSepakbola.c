/*
Program Perhitungan Klasmen Piala Dunia Sepakbola
Tanggal : 31 Maret 2021
Kelompok 2
Fikri Afif Musyaffa     2006536662
Muhammad Raihan Azhari  2006468320
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//struct data untuk menyimpan data team peserta kompetisi
struct data_team{
	char nama_tim[30]; //variabel nama tim nasional 
	int point; // variabel jumlah poin dari setiap tim
	int gol; //variabel jumlah gol dari setiap tim
	int kebobolan; //variabel jumlah kebobolan dari setiap tim
	int selisih_gol; //variabel selisih dari setiap tim
	int tanding [4]; //array untuk menyimpan rekap pertandingan
	char benua [10]; //variabel asal benua dari setiap tim
};

//struct data untuk menyimpan data statistik kompetisi dari setiap tim dalam kompetisi
struct statistik{
	char nama_tim[30]; 
	int point;
	int gol;
	int kebobolan;
	int selisih_gol;
	int tanding [4];
	char benua [10];
};

//deklarasi fungsi
void menu_awal();
void option();
void display_klasmen(struct data_team team [20][4], int jumlah_group);
void input_timnas(struct data_team team [20][4], int jumlah_group);
void input_pertandingan(struct data_team team [20][4], int group);
void tim_lolos (struct data_team team [20][4], int jumlah_group);
void reset_awal(struct data_team team [20][4], int jumlah_group);
void sorting_klasmen (struct data_team team [20][4], int jumlah_group);
void swap (struct data_team team [20][4], int i, int k, int jumlah_group);
void sorting_statistika(struct statistik statistik [50][4], struct data_team team [20][4], int jumlah_group, int statistik_method);
void statistik_help ();
void swap_statistik (struct statistik statistik [50][4], int k);
void searching_tim(struct data_team team [20][4], int jumlah_group);
void capt_handler_key(char key[30]);
void rules();

int main() {
	
	int condition = 0; //insialisasi ke 0 untuk memastikan variabel benar benar bernilai 0
	int jumlah_group, input_method, i, j, group, meyakinkan, statistik_method;

  //display menu awal untuk penulisan judul program
	menu_awal();
	
  //error handling untuk membatasi maksimum jumlah group yang dapat diinput
	while (condition == 0){
		printf("\n\nMasukan Jumlah Group: ");
		scanf("%d", &jumlah_group);
		if (jumlah_group > 0 && jumlah_group <= 16){
			break;
		}
		else{
			printf("\nJumlah group yang dapat dimasukan 1 - 16");
			printf("\nHarap masukan angka yang benar");
			condition = 0;
		}
	}
	
	
  //condisi di set kembali ke 0 untuk looping selanjutnya
	condition = 0;
	
  //deklarasi struct pada fungsi main
	struct data_team team[20][4];
	struct statistik statistik [50][4];
	
  //reset awal semua data, agar dipastikan benar benar 0
	reset_awal(team, jumlah_group);	

	//loop utama pada program
	while (condition != -1){
		
    //diseplay menu utama pada program utama
		option();
		printf("\n\nMasukkan nomor: ");
		scanf("%d", &condition);
		
    //error handling untuk menu utama, jika tidak ada pada menu maka user diminta untuk menginput nomor baru
		if (condition > 8 || condition < 1){
			if (condition != -1){
				printf("\nHarap masukkan angka yang benar\n");
				system ("pause");
				system("cls");
				continue;
			}	
		}
		
    //switch case condition menu utama
		switch (condition){
			
      //jika user menginput angka 1 maka fungsi input tim nasional akan berjalan
			case 1:
				system("cls");	
				input_timnas(team, jumlah_group);
				system("cls");
				printf("\nTeam berhasil diinput!!");		
				break;

      //jika user menginput angka 2 maka fungsi input skor akan berjalan	
			case 2:
				system("cls");
				printf("\nPilih Group ");
				printf("\nMasukan group sesuai nomor:");
        //display semua group yang ada untuk memudahkan input user
				for (i = 0; i < jumlah_group; i++){
					printf("\n%d. Group: %c", i + 1, i + 65);
				}
        //user diminta memasukan angka untuk memilih group mana yang akan diinput
				printf("\nMasukan angka: ");
				scanf("%d", &group);
        //fungsi input pertandingan berjalan
				input_pertandingan(team, group);
        //program akan mengurutkan team berdasarkan poin, gol, dan selisih gol
				sorting_klasmen(team, jumlah_group);
				system("cls");	
				break;

      //jika angka yang dimasukan 3 maka program akan menampilkan hasil klasmen sementara				
			case 3:
				system("cls");	
				display_klasmen(team, jumlah_group);
				printf("\n\n");
				system ("pause");
				system("cls");
				break;

      //jika angka yang dimasukan 4 maka program akan menampilkan siapa saja yang berhak maju ke babak selanjutnya	
			case 4:
				system("cls");	
				tim_lolos (team, jumlah_group);
				printf("\n");
				system ("pause");
				system("cls");
				break;
			
      //jika angka yang dimasukan 5 maka fungsi searching akan berjalan
			case 5:
				system("cls");	
				searching_tim(team, jumlah_group);
				printf("\n");
				system ("pause");
				system("cls");
				break;
			
      //jika angka yang dimasukan 6, maka akan dijalankan fungsi statistik kompetisi
			case 6:
				system("cls");
        //petunjuk kepada user ingin melihat statistik berdasarkan apa
				statistik_help ();
				printf("\nMasukan angka :");
   				scanf("%d", &statistik_method);
        //sorting statistika sekaligus display statistika berdasarkan input method dari user
   				sorting_statistika(statistik, team, jumlah_group, statistik_method);
   				printf("\n");
   				system ("pause");
   				system("cls");
   				break;

      //jika angka yang dimasukan 7, maka program akan menampilkan peraturan dari pemeringkatan klasmen sepakbola
      		case 7:
      			system("cls");
      			rules();
      			printf("\n");
      			system ("pause");
   				system("cls");
      			break;
		}
	}
	return 0;
}

//tampilan header judul awal
void menu_awal(){
  printf("=================================================");
  printf("\n|                                               |");
  printf("\n|         Selamat Datang Pada Program           |");
  printf("\n|       Perhitungan Klasmen Sepak Bola          |");
  printf("\n|              Piala Dunia 2022                 |");
  printf("\n|                                               |");
  printf("\n=================================================");
}

//display menu option pada program 
void option(){
	printf("\nMenu program :");
	printf("\nMasukan program: ");
	printf("\n1.Input Team Nasional");
	printf("\n2.Input Skor pada setiap Pertandingan");
	printf("\n3.Display Klasmen Sementara");
	printf("\n4.Display Team yang Lolos ke-16 besar");
	printf("\n5.Pencarian Team");
	printf("\n6.Statistik Kompetisi");
    printf("\n7.Lihat aturan kompetisi");
	printf("\n\nTekan tombol -1 untuk keluar: ");	
}

//fungsi untuk menginput nama tim nasional yang ikut dalam kompetisi
void input_timnas(struct data_team team [20][4], int jumlah_group){
	
	printf("\nMasukan nama team:\n");
	
	char temp[30]; //temporary variable untuk menghandle error input spasi
	int i, j; //i dan j variabel looping
	
  //loopiing untuk input nama tim berdasarkan jumlah_group yang diinput user
  //looping berapa banyak group yang akan diinput
	for(i = 0; i < jumlah_group; i++){
    //mencetak nama group dalam alphabet menurut kode ASCII 
		printf("\nGroup %c:\n", i + 65);
    // looping nama group sampai jumlah anggota
    //aturan rata-rata kompetisi sepakbola adalah setiap group berisikan 4 tim saja
		for(j = 0; j < 4; j++){
			printf("Input team: ");
			scanf("%c", &temp); //temporary scanf untuk mencegah enter terlewat pada fungsi scan %[^\n]
      //input nama tim nasional
			scanf("%[^\n]", team[i][j].nama_tim);
			capt_handler_key(team[i][j].nama_tim); //handle huruf kapital sehingga setiap input dituliskan menurut aturan baku
			printf("Asal benua: ");
      //innput asal benua dari tim yang diinput
			scanf("%s", team[i][j].benua);
			scanf("%[^\n]", team[i][j].benua);
			capt_handler_key(team[i][j].benua);
		}
	}
}

//Fungsi untuk menginput skor pertandingan
void input_pertandingan(struct data_team team [20][4], int group){
	
  //i dan j untuk variabel looping
  //variabel num untuk menandakan nomor pertandingan
  //variabel goal1 untuk menyimpan skor (gol) dari team A, goal2 untuk team B
  //status untuk kepentingan error handling sehingga pertandingan yang telah diinput tidak dapat diinput kembali
	int i, j, k, num, match, goal1, goal2, status;
	
	num = 0; //set nilai num ke 0
	status = 0; //set nilai status ke 0
	

	printf("\nNomor untuk setiap pertandingan");
  //group yang akan diinput pertandinganya menggunakan alphabet sesuai ASCII
	printf("\nGroup %c\n", group + 64);
	
  //for loop untuk mendisplay pertandingan
  // for loop menggunakan algoritma kombinasi (dalam pelajaran peluang matematika), sehingga setiap team mendapat team yang berbeda sesuai dengan nomor pertandinganya
	for (i = 3; i >= 1; i--){
		for (j = 2 - (3 - i); j >= 0; j--){
			num++;
			printf("\n%d. %s vs %s", num, team[group - 1][i].nama_tim, team[group - 1][j].nama_tim);
      //jika dalam array tanding telah di detect telah melakukan pertandingan melawan tim yang sama
			if (team[group - 1][i].tanding[j] == 1){
        //maka program akan mendisplay keterangan sudah diinput
				printf("\tSudah anda input");
			}
		}
	}

  //user  diminta untuk memasukan nomor pertandingan sesuai yang telah didisplay pada loop diatas
	printf("\n\nMasukan nomor pertandingan: ");
	scanf("%d", &match);

  //jika variabel match tidak dalam range 1-6 
	if (match < 1 || match > 6){
    //program akan menampilkan pesan kesalahan
		printf("\nNomor yang Anda masukan salah!");
		printf("\nSilahkan masukan nomor 1 - 6\n");
		system ("pause");
		system("cls");
    //maka fungsi akan memanggil fungsinya sendiri (recursive) untuk meminta input data dari user
		input_pertandingan (team, group);
	}
  //jika input no.pertandingan yang dimasukan benar
	else{
		num = 0;  //set angka num ke 0
    //looping program untuk searching input nomor pertandingan oleh user
		for (i = 3; i >= 1 && status != -1; i--){
			for (j = 2 - (3 - i); j >= 0 && status != -1; j--){
				num++;
        //jika nomor petandingan yang diinput user ditemukan
				if (match == num){
          //jika pertandingan tersebut belum ditandingkan maka iff statement akan berjalan
					if (team[group - 1][i].tanding[j] != 1){
						status = -1; //status menjadi -1 untuk mencegah terjadinya input data ganda
            //user diminta untuk menginput skor
						printf("\nInput skor %s: ", team[group - 1][i].nama_tim); 
						scanf("%d", &goal1);
            //penambahan jumlah gol dan kebobolan pada array dalam struct untuk diakumulasikan
						team[group - 1][i].gol += goal1;
						team[group - 1][j].kebobolan += goal1;
						printf("\nInput skor %s: ", team[group - 1][j].nama_tim);
						scanf("%d", &goal2);
						team[group - 1][j].gol += goal2;
						team[group - 1][i].kebobolan += goal2;
						team[group - 1][i].selisih_gol += goal1 - goal2;
						team[group - 1][j].selisih_gol += goal2 - goal1;
            //2 tim yang bertan sudah diset ke 1 menandakan pertandingan tidak dapat diinput kembali
						team[group - 1][i].tanding[j] = 1;
						team[group - 1][j].tanding[i] = 1;
						//Perhitungan point menurut kemenangan, seri, dan kelelahan
            //jika team A menang maka team A mendapat 3 point
						if(goal1 > goal2){
						team[group-1][i].point += 3;
            }
            //jika team B menang maka team B mendapat 3 point
						else if(goal1 < goal2){
							team[group-1][j].point += 3;
			   			}
            //jika team A seri dengan team B maka point kedua team akan seri              
						else if(goal1 == goal2){
		    				team[group-1][i].point += 1;
					   		team[group-1][j].point += 1;
			    		}
						break;
						}
            //jika team telah bertanding satu sama lain
						else if (team[group - 1][i].tanding[j] == 1  && status != -1){
						status = -1;
            //sistem akan mengeluarkan peringatan
						printf("\nSkor pertandingan sudah diinput, harap masukan skor pertandingan lain \n");
						break;
				  		}
				}
			}
		}
	}	
}

//fungsi untuk menampilkan klasmen
void display_klasmen(struct data_team team [20][4], int jumlah_group){
	
	int i, j;
	
  //looping untuk mendisplay klasmen pertandingan
	for (i = 0; i < jumlah_group; i++){
		printf("\n\nGroup: %c", i +65);
		printf("\nNo.\tNama Team\tPoint\tJumlah Gol\tKebobolan\tSelisih Gol\tAsal Benua");
		for(j = 0; j < 4; j++){
			printf("\n%d. \t%s", j + 1, team[i][j].nama_tim);
      //jika string yang diinput kurang dari 8 karakter maka display akan dijorokan kedalam
      //hal ini untuk merapihkan display
			if(strlen(team[i][j].nama_tim) < 8){
				printf("\t");
			}
			printf("\t%d", team[i][j].point);
			printf("\t%d", team[i][j].gol);
			printf("\t\t%d", team[i][j].kebobolan);
			printf("\t\t%d", team[i][j].selisih_gol);
			printf("\t\t%s", team[i][j].benua);			
		}
	}
}


//fungsi reset awal untuk meng 0 kan data sebelum program dimulai
void reset_awal(struct data_team team [20][4], int jumlah_group){
	
	int i, j, k;
	
	for(i = 0; i <= jumlah_group ; i++){
		for(j = 0; j < 4; j++){
			team[i][j].gol = 0;
			team[i][j].kebobolan = 0;
			team[i][j].point = 0;
			team[i][j].selisih_gol = 0;
			for(k = 0; k < 4; k++){
				team[i][j].tanding[k] = 0;
			}
		}
	}
}

//fungsi untuk sorting klasmen 
void sorting_klasmen (struct data_team team [20][4], int jumlah_group){
	
	int i, j, k;
	
  //loop menggunakan bubble sorting
	for(i = 0; i < jumlah_group; i++){
		for (j = 0; j < 4; j++){
			for( k = 0; k < 4; k++){
        //sorting berdasarkan point tertinggi
        // statement (k+1) != 4 untuk mencegah data yag melebihi nomor team dijalankan 
				if (team[i][k].point < team[i][k + 1].point && (k + 1) != 4){
          //pertukaran data struct (sorting)
					swap(team, i, k, jumlah_group);
				}
        //jika point kedua team sama
				else if (team[i][k].point == team[i][k + 1].point && (k + 1) != 4){
          //sorting dilakukan berdasarkan jumlah gol terbanyak
					if (team[i][k].gol < team[i][k + 1].gol && (k + 1) != 4){
						swap(team, i, k, jumlah_group);
				  }
          //jika jumlah gol kedua tim sama
					else if(team[i][k].gol == team[i][k + 1].gol && (k + 1) != 4){
            //sorting dilakukan berdasarkan jumlah kebobolan terkecil
            if (team[i][k].kebobolan > team[i][k + 1].kebobolan && (k + 1) != 4){
						swap(team, i, k, jumlah_group);
						}
					}
				}
			}
		}
	}
}

//fungsi untuk men swap struct data
void swap (struct data_team team [20][4], int i, int k, int jumlah_group){
	
	//team[jumlah_group][k] as temporary struct
	int temp, a;
	
  //swap data array struct 
	team[jumlah_group][k] = team[i][k];
	team[i][k] = team[i][k + 1];
	team[i][k + 1] = team[jumlah_group][k];
	
  //swapping array tanding, karena susunan klub berubah
	for(a = 0; a < 4; a++){
		temp = team[i][a].tanding[k];
		team[i][a].tanding[k] = team[i][a].tanding[k + 1];
		team[i][a].tanding[k + 1] = temp;
	}
}

//statistik kompetisi berdasarkan metode sorting
void sorting_statistika(struct statistik statistik [50][4], struct data_team team [20][4], int jumlah_group, int statistik_method){
	
	int i, j, k; //variabel looping
	
  //set nilai k ke 0
	k = 0;
	
  //masukan data dari struct data team ke data statistik
	for (i = 0; i < jumlah_group; i++){
		for (j = 0; j < 4; j++){
      //jika sorting berdasarkan point tertinggi
			if (statistik_method == 1){
				strcpy(statistik[k][0].nama_tim, team[i][j].nama_tim);
				statistik[k][0].point = team[i][j].point;
				k++;
			}
      //jika sorting berdasarkan gol terbanyak
			else if (statistik_method == 2){
				strcpy(statistik[k][0].nama_tim, team[i][j].nama_tim);
				statistik[k][0].gol = team[i][j].gol;
				k++;
			}
      //jika sorting berdasarkan jumlah kebobolan terkecil
			else if (statistik_method == 3){
				strcpy(statistik[k][0].nama_tim, team[i][j].nama_tim);
				statistik[k][0].kebobolan = team[i][j].kebobolan;
				k++;
			}
       //jika sorting berdasarkan jumlah kebobolan terkecil
			else if (statistik_method == 4){
				strcpy(statistik[k][0].nama_tim, team[i][j].nama_tim);
				strcpy(statistik[k][0].benua, team[i][j].benua);
				k++;
			}
		}
	}
  //sorting data statistik
	for(i = 0; i < k; i++){
		for(j = 0; j < k; j++){
      //sorting statistika berdasarkan point terbanyak
			if (statistik_method == 1 && statistik[j][0].point < statistik[j + 1][0].point){
				swap_statistik (statistik, j);
			}
      //sorting statistika berdasarkan jumlah gol terbanyak
			else if (statistik_method == 2 && statistik[j][0].gol < statistik[j + 1][0].gol){
				swap_statistik (statistik, j);
			}
       //sorting statistika berdasarkan jumlah kebobolan terkecil
			else if (statistik_method == 3 && statistik[j][0].kebobolan < statistik[j + 1][0].kebobolan){
				swap_statistik (statistik, j);
			}
      //sorting pengelompokan benua berdasarkan alphabet ASCII
			else if (statistik_method == 4 && strcmp(statistik[j][0].benua, statistik[j + 1][0].benua) > 0){
				swap_statistik (statistik, j);
			}
		}
	}
  //display nilai statistik yang telah disorting
	for(i = 0; i < k; i++){
    	if (statistik_method == 1){
			printf("\n\n%d. %s", i + 1, statistik[i][0].nama_tim);
			printf("\nJumlah poin: %d", statistik[i][0].point);
		}
		else if (statistik_method == 2){
			printf("\n\n%d. %s", i + 1, statistik[i][0].nama_tim);
			printf("\nJumlah gol: %d", statistik[i][0].gol);
		}
		else if (statistik_method == 3){
			printf("\n\n%d. %s", i + 1, statistik[i][0].nama_tim);
			printf("\nJumlah kebobolan: %d", statistik[i][0].kebobolan);
		}
		else if (statistik_method == 4){
			printf("\n\n%d. %s", i + 1, statistik[i][0].nama_tim);
			printf("\nBenua: %s", statistik[i][0].benua);
		}
	}
}

//fungsi pertukaran struct statistik dalam sorting
void swap_statistik (struct statistik statistik [50][4], int k){
	statistik[45][0] = statistik[k][0];
	statistik[k][0] = statistik[k + 1][0];
	statistik[k + 1][0] = statistik[45][0];
}

//fungsi help manual untuk sorting statistik
void statistik_help (){
	printf("\nMasukan angka untuk statistik berdasarkan");
	printf("\n1. Point terbanyak di kompetisi");
	printf("\n2. Jumlah gol terbanyak di kompetisi");
	printf("\n3. Jumlah kebobolan terbanyak di kompetisi");
	printf("\n4. Sorting negara menurut benuanya");
}

// fungsi untuk menampilkan tim yang lolos ke babak 16 besar
//tim yang lolos dipilih berdasarkan 2 klasmen teratas
void tim_lolos (struct data_team team [20][4], int jumlah_group){
	
	int i, j; //variabel looping
	
	printf("\n\nTeam yang masuk babak 16 besar");

  //looping untuk menampilkan tim yang lolos
	for (i = 0; i < jumlah_group; i++){	
		printf("\n\nGroup: %c", i +65);
		printf("\nNo.\tNama Team\tPoint\tAsal Benua");
		for (j = 0; j < 2; j++){
			printf("\n%d. \t%s", j + 1, team[i][j].nama_tim);
			if(strlen(team[i][j].nama_tim) < 8){
				printf("\t");
			}
			printf("\t%d", team[i][j].point);
			printf("\t%s", team[i][j].benua);
		}
	}
	printf("\n");
}

///fungsi untuk menghandle kesalahan penulisan huruf kapital
//penulisan huruf kapital berdasarkan aturan baku bahasa Indonesia
void capt_handler_key(char key[30]){
	
	int i, j;
	
	for(j = 0; j < 30; j++){			
		if (key[j] == 32){
			if (key[j+1] <= 122 && key[j+1] >= 97){
				j++;
				key[j] -= 32;	
			}
		}
		//huruf kecil diubah menjadi besar sesuai ASCII
		else if(key[0] <= 122 && key[0] >= 97){
			key[0] -= 32;
		}
		//huruf besar diubah menjadi  kecil sesuai ASCII
		else if (key[j] <= 90 && key[j] >= 65 && j != 0 && key[j - 1] != 32){
			key[j] += 32;
		}
	}
}

//fungsi untuk mencari team pada statistik
void searching_tim(struct data_team team [20][4], int jumlah_group){
	
	int i, j, condition;
	char cek[20];
	
  //user diminta untuk menginput data yang ingin dicari
	printf("\nKetik nama team yang kamu ingin cari :");
	scanf("%s", &cek);
	scanf("%[^\n]", &cek);
	capt_handler_key(cek);
	
  condition = 0;
  //looping untuk menampilkan hasil data pencarian
	for (i = 0; i < jumlah_group; i++){
		for (j = 0; j < 4; j++){
      //jika data yang dicari ditemukan
      //display semua data yang dicari user
			if (strcmp(team[i][j].nama_tim, cek) == 0 ){
				printf("\n%s\n", team[i][j].nama_tim);
				printf("\nGol		: %d", team[i][j].gol);
				printf("\nKebobolan	: %d", team[i][j].kebobolan);
				printf("\nSelisih Gol	: %d", team[i][j].selisih_gol);
				printf("\nPoint		: %d", team[i][j].point);
				printf("\nBenua		: %s", team[i][j].benua);
   			printf("\n");
         //jika ditemukan maka kondisi akan bernilai 1
         condition = 1;
         //jika searching ditemukan maka loop akan di break
   			break;
			}
			}
		}
    //jika condition masih bernilai 0 (tim belum ditemukan)
    if (condition == 0){
				printf("\n\nMaaf, Team yang anda cari tidak ada dalam daftar\n");
				printf("\nSilahkan daftarkan team anda terlebih dahulu\n");
	}
}

//display aturan pemeringkatan kompetisi
void rules(){
  printf("\n\nPerturan pemeringkatan klasmen");
  printf("\n1.Point tertinggi diperingkatkan lebih atas");
  printf("\n2. Jika point sama, maka pemeringkatan berdasarkan jumlah gol");
  printf("\n3. Jika jumlah gol sama, maka selisih gol dengan nilai terbesar diperingkatkan lebih atas");
  printf("\n\nMenang = 3 point");
  printf("\nSeri = 1 point");
  printf("\nKalah = 0 point");
}
