#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム

#include<time.h>//時間を用いる

#include <direct.h>//フォルダを作成する

void main(){

	//シミュレーションの条件指定
	char property_name[128]="simulation17-0616_sin_usui-4";
	char input_image_directory[128]="..\\\\bmp\\\\circle\\\\3-3波_usui_11.4";	//拡張子不要
	char filter_name1[128]="simulation17-0203";
	char filter_name2[128]="0203";

	int paramerter_number=3;
	int paramerter[5]={3,10,100};
	int sd_step=10;
	char kenel_directory[128];
	int Rm=3,Rg=3,Rs=5,Rc=100,Cs=10;	//Rsは0.5を5と入力
	//sprintf(kenel_directory,"..\\フィルタ\\simulation17-0203\\8dire_RmRg%dkRs%dkRc%dkCs%dp",Rm,Rs,Rc,Cs);
	char input_image_sd[128];

	int image_x = 256;
	int image_y = 256;
	int Rvector_create = 0;
	int Rvector_coordinate_x =59;
	int Rvector_coordinate_y =60;
	int kernel_size = 31;

	

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
	sprintf(date_directory,"..\\property_tiger\\%2d-%02d%02d-%02d%02d%02d\\",pnow->tm_year+1900,pnow->tm_mon + 1,pnow->tm_mday,pnow->tm_hour,pnow->tm_min,pnow->tm_sec);
	 if(_mkdir(date_directory)==0){
        printf("フォルダ %s を作成しました\n",date_directory);
    }else{
        printf("フォルダ作成に失敗しました。\n");
    }

	 sprintf(property_atan,"%sproperty_atan\\",date_directory);
	 sprintf(property_cossim,"%sproperty_cos-sim\\",date_directory);
	 sprintf(property_conv,"%sproperty_conv\\",date_directory);
	 sprintf(conv_directory,"%sconv\\",date_directory);
	 sprintf(input_directory,"%sinput_image\\",date_directory);
	 sprintf(cossim_directory,"%cos-sim\\",date_directory);
	 sprintf(atan_directory,"%satan\\",date_directory);

	 _mkdir(property_atan);
	 _mkdir(property_cossim);
	 _mkdir(property_conv);
	 _mkdir(conv_directory);
	 _mkdir(input_directory);
	 mkdir(cossim_directory);
	 _mkdir(atan_directory);


	 FILE *fp_conv,*fp_cossim,*fp_atan;
	 char filename_pro[128];
	 char filenemae_conv[128];
	  char filenemae_cossim[128];
	    char filenemae_atan[128];

		//propertyの作成
	 for(int i=0;i<paramerter_number;++i){

		 //property_conv作成
		 for(int j=0;j<6;++j){
			 sprintf(filenemae_conv,"%sproperty_%dk_conv_sd%d.txt",property_conv,paramerter[i],j*sd_step);
			 if((fp_conv=fopen(filenemae_conv,"w"))==NULL){printf("proterty_convファイルが開けません");exit(1);}

			 sprintf(kenel_directory,"..\\\\フィルタ\\\\%s\\\\8dire_RmRg%dkRs0.%dkRc%dkCs%dp",filter_name1,paramerter[i],Rs,Rc,Cs);
			 fprintf(fp_conv,"%d,%d,%d,%d,%d,%d,\n",image_x,image_y,Rvector_create,Rvector_coordinate_x,Rvector_coordinate_y,kernel_size);
			 fprintf(fp_conv,"\\\\Rvector\\\\8dire_%dk\n",paramerter[i]);
			 fprintf(fp_conv,"%s_sd%d.bmp\n",input_image_directory,j*sd_step);
			 fprintf(fp_conv,"%s\\\\V(0).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(45).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(90).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(135).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(180).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(225).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(270).txt\n",kenel_directory);
			 fprintf(fp_conv,"%s\\\\V(315).txt\n",kenel_directory);

			 fclose(fp_conv);
		 }

		 //property_cossim作成
		 sprintf(filenemae_cossim,"%sproperty_%dk.txt",property_cossim,paramerter[i]);
		 if((fp_cossim=fopen(filenemae_cossim,"w"))==NULL){printf("proterty_cossimファイルが開けません");exit(1);}

		 fprintf(fp_cossim,"%d,8,8,8,0,\n",image_x);
		 fprintf(fp_cossim,"..\\\\Rvector\\\\%s\\\\8dire_%dk_%s\n",filter_name1,paramerter[i],filter_name2);
		 for(int j=0;j<6;++j)fprintf(fp_cossim,"..\\\\inputdate\\\\%s\\\\%dk_conv_sd%d\n",property_name,paramerter[i],j*sd_step);
		  fclose(fp_cossim);


		 //property_atan作成
		  sprintf(filenemae_atan,"%sproperty_%dk.txt",property_atan,paramerter[i]);
		  if((fp_atan=fopen(filenemae_atan,"w"))==NULL){printf("proterty_atanファイルが開けません");exit(1);}
		  fprintf(fp_atan,"%d,\n",image_x);
		  for(int j=0;j<6;++j)fprintf(fp_atan,"..\\\\inputdate\\\\%s\\\\%dk_conv_sd%d\n",property_name,paramerter[i],j*sd_step);
		  fclose(fp_atan);

		  
	 }

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

}
