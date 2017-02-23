#include "red.h"//97CE094DF5 infinitum89130E
#include "llc.h"
int tam=0,tr;
char bufw[7];
FILE *tramarec;
int insertat(unsigned char *tramallcrec,int tamtr,int df)
{
        if((nvo=(llc *)malloc(sizeof(llc)))==NULL)
		{printf("\nse a agotado la memoria");exit(-1);}
        for(tr=0;tr<tamtr;tr++)
        {
                nvo->trama[tr]=*(tramallcrec+tr);
		sprintf(bufw,"%.2x ",*(tramallcrec+tr));
		write(df,bufw,3*sizeof(char));
		write(df," ",sizeof(char));
                if(tr==tamtr-1)
                {
			write(df,"\n;\n",3*(sizeof(char)));
                        nvo->sig=NULL;
                        if(cabt==NULL)
                                cabt=nvo;
                        else
                        {for(p=cabt;p->sig!=NULL;p=p->sig){;}p->sig=nvo;}
                        continue;
                }
                if(!((tr+1)%16))
                        {
				write(df,"\n",sizeof(char));
			continue;}
        }
        return 0;
}
void *resivellc(void *args)
{
      	if(!((int)args))//sero para solo LLC.TXT
	{sleep(1000000000);}
        unsigned char tramallcrec[tamarp],macf[6]={0x00,0x00,0xe8,0x15,0xbb,0x75};
	int df=open("trec.dat",O_CREAT|O_WRONLY,0777);
        while(1)
        {
                tam=recvfrom(cabr->paquete,tramallcrec,tamarp,0,NULL,0);
                if(tam==-1)
                        {perror("\nError al recibir trama");}
                else
                {
                        if((tramallcrec[12]*256 + tramallcrec[13] ) <= 1500)
                        {
                                if(!((int)args))//sero para solo LLC.TXT
                                {
                                        if(!memcmp(tramallcrec+0,macf+0,6)||!memcmp(tramallcrec+6,macf+0,6))
                                                {insertat(tramallcrec,tam,df);}
                                }
                                else//uno para recivir de la red
                                	{insertat(tramallcrec,tam,df);}
                        }
                }
        }
	close(df);
        return ("ya termine");
}
int imprime(unsigned char *trama,int lim)
{
        int t;
        for(t=0;t<lim;t++)
        {
                printf("%.2x ",*(trama+t));
                if(!((t+1)%16))
                        printf("\n");
        }
        printf("\n\nsiguiente trama\n");
        return 0;
}
void enviallc(unsigned char *tramallcenv,int tamtr)
{
        int tam;
        struct sockaddr_ll nic;
        memset(&nic, 0x00, sizeof(nic));
        nic.sll_family = AF_PACKET;
        nic.sll_protocol = htons(ETH_P_ALL);
        nic.sll_ifindex = cabr->indice;
        tam = sendto(cabr->paquete,tramallcenv,tamtr, 0, (struct sockaddr *)&nic, sizeof(struct sockaddr_ll));
        if(tam == -1)
                perror("\nError al enviar\n\n");
}
void *fichero(void *args)
{
	unsigned char tramallcenv[tamarp],trampa[6];
	FILE *tramas=fopen((char *)args,"r");
	char aux[3],chek;
	aux[2]=';';
	int cf=0,jf=0;
	int df=open("trec.dat",O_CREAT|O_WRONLY,0777);
	if(tramas!=NULL)
	{
		while(!feof(tramas))
                {
                        chek=fgetc(tramas);
                        if(chek==';')
                                {
					memcpy(trampa+0,tramallcenv+0,6);
			;		memcpy(tramallcenv+0,tramallcenv+6,6);
					memcpy(tramallcenv+6,trampa+0,6);
					insertat(tramallcenv,jf,df);enviallc(tramallcenv,jf);jf=-1;usleep(500000);
				}
                        if(chek==' '||chek=='\n')
                                {sscanf(aux,"%x;",(unsigned int*)&tramallcenv[jf]);cf=0;jf++;continue;}
                        aux[cf]=chek;
                        cf++;
                }
		
	}
	else
		printf("\nerror al abrir %s",(char *)args);
	fclose(tramas);
	return ("termine dei enviar");
}
