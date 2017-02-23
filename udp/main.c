#include "red.h"
#include "arp.h"
#include "udp.h"
unsigned short runo=0,rdos=65535,red=0,constante=257;
pthread_mutex_t mutex;
pthread_t hilo[255];
void *esvir(void *args){
	unsigned short s,f,c,j;
	unsigned char tramaenv[74];
	s=((unsigned short*)args)[0];
	f=((unsigned short*)args)[1];
	pthread_mutex_unlock(&mutex);
//	printf("\ninicio=%d\tfinal=%d",s,f);
	for(c=s;c<f;c++){
		for(j=0;j<3;j++){if(estructura(tramaenv,c,red,j)){break;};}
//		estructura(tramaenv,c,red);
//		envia(tramaenv);
//		recive(c);
	}
	pthread_exit(NULL);
}
void inicio(){
	if((fa=fopen("open.dat","a+"))==NULL){printf("\nerror al crear documento puerto abiertos");return;}
	if((fc=fopen("cerrado.dat","a+"))==NULL){printf("\nerror al crear documento puerto cerrado");return;}
	unsigned short h,j,limite[2]={0,runo};//100-500
	pthread_mutex_init(&mutex,NULL);
	if((rdos-runo)<=1024){constante=50;}
	if((rdos-runo)>1024&&(rdos-runo)<=81192){constante=128;}
	for(h=0;h<255&&limite[1]<rdos;h++){
		pthread_mutex_lock(&mutex);
		limite[0]=limite[1];
		limite[1]=(constante*(h+1))+runo;
		if(limite[1]>rdos){limite[1]=rdos;}
		pthread_create(&hilo[h],NULL,esvir,(void *)limite);
//		printf("\nruno=%d\trdos=%d",runo,rdos);
//		printf("\nh=%d",h);
	}
	for(j=0;j<=h;j++)
		pthread_join(hilo[j],NULL);
}
void imprimepuertos(){
        int numpuerto,puerto;
        char infopuerto[100];
        FILE *info,*auxfile;
        if((info=fopen("infopuertos.dat","r"))==NULL)
                {printf("\nerror al abrir el fichero infopuerto.dat");return;}
        if(cerrado>=((rdos-runo)/2)){auxfile=fa;}
        else{auxfile=fc;}
        rewind(auxfile);
        while(!feof(auxfile)){
                fscanf(auxfile,"%d\n",&puerto);
                while(!feof(info)){
                        fscanf(info,"%d\t%[a-zA-Z0-9()-/#\t ]\n",&numpuerto,infopuerto);
                        if(puerto==numpuerto)
                                {printf("\npuerto:%d\t%s",numpuerto,infopuerto);break;}
                }
                rewind(info);
        }
        fclose(info);
}
int main(int ari,char **arc){
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        cabr=datosred(arc[1],paquete);
        parametros(ari,arc,&runo,&rdos);
        putdatos();
       	printf("\n\nescaneo de puertos upd ala direccion ");putip(cabr->tuip);
        if((red=compruebared())){
        	estructuraarp(cabr,cabr->tuip,cabr->tumac);}
	inicio();
	imprimepuertos();
	fclose(fa);fclose(fc);
        printf("\n");return 0;
}
