#include "red.h"
#include "arp.h"
#include "tcp.h"
unsigned short runo=0,rdos=65535,red=0,constante=257;
pthread_mutex_t mutex;
pthread_t hilo[255];
void *esvir(void *args){
	unsigned short s,f,c,j;
	unsigned char tramaenv[74];
	s=((unsigned short*)args)[0];
	f=((unsigned short*)args)[1];
	pthread_mutex_unlock(&mutex);
	for(c=s;c<f;c++){
		for(j=0;j<3;j++){if(estructura(tramaenv,c,red,j)){break;};}
	}
	pthread_exit(NULL);
}
void inicio(){
	unsigned short h,j,limite[2]={0,runo};
	ctapa=ctapc=0;memset(pa,0,800);memset(pc,0,800);
	pthread_mutex_init(&mutex,NULL);pthread_mutex_init(&mutexpc,NULL);pthread_mutex_init(&mutexpa,NULL);
	if((rdos-runo)<=1024){constante=20;}
	if((rdos-runo)>1024&&(rdos-runo)<=81192){constante=128;}
	for(h=0;h<255&&limite[1]<rdos;h++){
		pthread_mutex_lock(&mutex);
		limite[0]=limite[1];
		limite[1]=(constante*(h+1))+runo;
		if(limite[1]>rdos){limite[1]=rdos;}
		pthread_create(&hilo[h],NULL,esvir,(void *)limite);
	}
	for(j=0;j<=h;j++)
		pthread_join(hilo[j],NULL);
}
void imprimepuertos(){
        unsigned short cta,*p;
	int puerto;
        char infopuerto[100];
        FILE *info;
        if((info=fopen("infopuertos.dat","r"))==NULL)
                {printf("\nerror al abrir el fichero infopuerto.dat");return;}
	for(cta=0;pa[cta]!=0;cta++){printf("\npa[%d]=%d",cta,pa[cta]);}
	for(puerto=0;pc[puerto]!=0;puerto++){printf("\npc[%d]=%d",puerto,pc[puerto]);}
	if(cta>puerto){p=pa;}//mas puertos abiertos
        else{p=pc;}//mas puerto serrados
        for(cta=0;p[cta]!=0;cta++){
                while(!feof(info)){
                        fscanf(info,"%d\t%[a-zA-Z0-9()-/#\t ]\n",&puerto,infopuerto);
                        if(puerto==p[cta])
                                {printf("\npuerto:%d\t%s",puerto,infopuerto);break;}
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
       	printf("\n\nescaneo de puertos tcp ala direccion ");putip(cabr->tuip);
        if((red=compruebared())){
        	estructuraarp(cabr,cabr->tuip,cabr->tumac);}
	inicio();
	imprimepuertos();
        printf("\n");return 0;
}
