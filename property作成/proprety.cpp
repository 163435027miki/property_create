#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム
#include <windows.h>

#include<time.h>//時間を用いる

#include <direct.h>//フォルダを作成する

void main(){
////////////////初期設定11///////////////////////////////////////////////////////////
	char property_name[128] = "simulation17-0725";
	int Togire[10]={0,1,3,5,7,9,13,17};
	int pixel[10] = { 0,1,3,5,7,9,13,17 };
	char filter_name1[128] = "kernel";
	int kernel_flag = 0;	//1ならkernel，それ以外ならsobel
	int paramerter_kernel[5] = { 3,10,100 };
	int paramerter_sobel[5] = { 3,5,7 };
	int Rm = 3, Rg = 3, Rs = 5, Rc = 100, Cs = 10;	//Rsは0.5を5と入力
	int image_x = 120;
	int image_y = 120;
	int Rvector_create = 0;
	int Rvector_coordinate_x = 59;
	int Rvector_coordinate_y = 60;
	int kernel_size = 31;

	int sd_step = 10;
	int sd_max = 0;

	//char input_image_directory[128]="..\\\\bmp\\\\\Togire\\\\90-17p-17T";	//入力画像
	//sprintf(kenel_directory,"..\\\\simulation17-0203\\8dire_RmRg%dkRs%dkRc%dkCs%dp",Rm,Rs,Rc,Cs);		//kernel

	char input_image_directory[128];	//拡張子不要
	char kenel_directory[128];
	char input_image_sd[128];
	
	int paramerter_number=3;

	for(int z2=1;z2<=7;++z2){	//pixelの++
	for(int z=1;z<=7;++z){		//Togireの++

	sprintf(input_image_directory,"..\\\\bmp\\\\\Togire\\\\15-%dp-%dT", pixel[z2], Togire[z]);

	//実行日時の表示
	time_t now = time(NULL);
    struct tm *pnow = localtime(&now);
	char date[128]="";
	sprintf(date,"%2d/%2d/%2d - %d:%d:%d\n",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	printf(date);

	char date_directory[128];
	char property_atan[128];
	char property_cossim[128];
	char property_conv[128];
	char conv_directory[128];
	char input_directory[128];
	char outputbmp_directory[128];
	char cossim_directory[128];
	char atan_directory[128];

	//フォルダの作成
	//sprintf(date_directory,"..\\property_tiger\\%2d-%02d%02d-%02d%02d%02d\\",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);

	if (kernel_flag == 1) {
		sprintf(date_directory, "..\\property_tiger\\15-%dp-%dT\\", pixel[z2], Togire[z]);
	}
	else {
		sprintf(date_directory, "..\\property_tiger\\15-%dp-%dT_sobel\\", pixel[z2], Togire[z]);
	}

	 if(_mkdir(date_directory)==0){
        printf("フォルダ %s を作成しました\n",date_directory);
    }else{
        printf("フォルダ作成に失敗しました。\n%s\n", date_directory);
    }

	 sprintf(property_conv,"%s",date_directory);


	 FILE *fp_conv,*fp_cossim,*fp_atan;
	 char filename_pro[128];
	 char filenemae_conv[128];
	 char filenemae_cossim[128];
	 char filenemae_atan[128];

		//propertyの作成
	 for(int i=0;i<paramerter_number;++i){

		 //property_conv作成
		 for(int sd=0; sd <=sd_max;sd=sd+ sd_step){

			 if (kernel_flag == 1) {
				 sprintf(filenemae_conv, "%sproperty_%dk_conv_sd%d.txt", property_conv, paramerter_kernel[i], sd);
				 if ((fp_conv = fopen(filenemae_conv, "w")) == NULL) { printf("proterty_convファイルが開けません"); exit(1); }

				 fprintf(fp_conv, "%d,%d,%d,%d,%d,%d,\n", image_x, image_y, Rvector_create, Rvector_coordinate_x, Rvector_coordinate_y, kernel_size);

				 fprintf(fp_conv, "\\\\Rvector\\\\8dire_%dk\n", paramerter_kernel[i]);

				 sprintf(kenel_directory, "..\\\\filter\\\\%s\\\\8dire_RmRg%dkRs0.%dkRc%dkCs%dp", filter_name1, paramerter_kernel[i], Rs, Rc, Cs);
				 //sprintf(kenel_directory, "..\\\\filter\\\\kernel\\\\%d", paramerter[i], paramerter[i]);

				 // fprintf(fp_conv,"%s_sd%d.bmp\n",input_image_directory,j*sd_step);
				 fprintf(fp_conv, "%s.bmp\n", input_image_directory);
				 fprintf(fp_conv, "%s\\\\V(0).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(45).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(90).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(135).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(180).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(225).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(270).txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\V(315).txt\n", kenel_directory);
			
			 } else {

				 kernel_size = paramerter_sobel[i];

				 sprintf(filenemae_conv, "%sproperty_%d×%dsobel_conv_sd%d.txt", property_conv, paramerter_sobel[i], paramerter_sobel[i], sd);
				 if ((fp_conv = fopen(filenemae_conv, "w")) == NULL) { printf("proterty_convファイルが開けません"); exit(1); }
				 fprintf(fp_conv, "%d,%d,%d,%d,%d,%d,\n", image_x, image_y, Rvector_create, Rvector_coordinate_x, Rvector_coordinate_y, kernel_size);

				 sprintf(kenel_directory, "..\\\\filter\\\\%d×%dsobelN", paramerter_sobel[i], paramerter_sobel[i]);

				 fprintf(fp_conv, "\\\\Rvector\\\\%d×%dsobel_under\n", paramerter_sobel[i], paramerter_sobel[i]);

				 // fprintf(fp_conv,"%s%d.bmp\n",input_image_directory,i*10);

				 fprintf(fp_conv, "%s.bmp\n", input_image_directory);
				 fprintf(fp_conv, "%s\\\\sobel0.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel45.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel90.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel135.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel180.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel225.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel270.txt\n", kenel_directory);
				 fprintf(fp_conv, "%s\\\\sobel315.txt\n", kenel_directory);
			 }
			 fclose(fp_conv);
		 }
		  
	 }
	 /*
	 //log作成
	 FILE *fp_log;
	 char filename_log[128];
	 sprintf(filename_log, "..\\property_tiger\\%2d-%02d%02d-%02d%02d%02d\\%s_log.txt",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec,property_name);	//logファイル作成のディレクトリ指定
	 if((fp_log=fopen(filename_log,"w"))==NULL){printf("logファイルが開けません");exit(1);}

	 fprintf(fp_log,"%2d-%02d%02d-%02d%02d%02d\n",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	 fprintf(fp_log,"property_name : %s\n",property_name);
	 fprintf(fp_log,"input_image_directory : %s\n",input_image_directory);
	 fprintf(fp_log,"property_name : %s\n",property_name);
	 fprintf(fp_log,"filter_name : %s , %s\n",filter_name1,filter_name2);
	 fprintf(fp_log,"Rm = %d , Rg = %d , Rs = 0.%d , Rc = %d , Cs = %d\n",Rm,Rg,Rs,Rc,Cs);
	 fprintf(fp_log,"paramerter={%d,%d,%d,%d,%d}",paramerter[0],paramerter[1],paramerter[2],paramerter[3],paramerter[4]);

	 

	 

	 fclose(fp_log);
	printf("ファイル %s を作成しました\n",filename_log);
	*/
	//Sleep(1000);

	}
	}

}
