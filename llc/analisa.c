#include "red.h"
#include "llc.h"
unsigned char sap[5];
int dsapandssap(unsigned char goi,unsigned char roc)//14 y 15
{
        memset(sap,0,5);//11110000
	if((goi&0x01)==1)
                {printf("\ntrama de grupo");}
        else
                {printf("\ntrama individual");}
        if((roc&0x01)==1)
                {printf("\ntrama de respuesta");}
        else
                {printf("\ntrama de comando");}
	printf("\ndssap and ssap: ");
	switch((roc&0xFE))
	{
		case 0x04:printf("IBM SNA");break;
		case 0x06:printf("IP");break;
		case 0x80:printf("3COM");break;
		case 0xAA:printf("SNAP");break;
		case 0xBC:printf("BANYAN");break;
		case 0xE0:printf("NOVELL");break;
		case 0xFA:printf("LAN MANAGER FE-CLNS");break;
		case 0x42:printf("SPANNING TREE BPDU");break;
		case 0xF0:printf("NETBIOS");break;
	}
        sap[0]=roc>>1;
        sap[1]=goi>>1;
        return roc>>7;
}
int innusu(unsigned char env)//16 
{
//      if((env&0x0))0111|1111
        switch((env&0x03))
        {
                case 0:printf("\ntrama de informacion");return 0;break;
                case 2:printf("\ntrama de informacion");return 2;break;
                case 1:printf("\ntrama de supervicion");return 1;break;
                case 3:printf("\ntrama no numerada");return 3;break;
        }
        return 5;
}
int chekonebyte(unsigned char byteone)
{
        if((byteone&0x10)==16)
        {
                printf("\nrequiere un respuesta inmediata");
                switch((byteone&0xEC))
                {
                        case 0x80:printf("\nset normal response snrm");break;
                        case 0xCC:printf("\nset normal response extended mode snrme");break;
                        case 0x0C:printf("\nset asincronous response sarm");break;
                        case 0x4C:printf("\nset asincronous response extended mode sarme");break;
                        case 0x2C:printf("\nset asincronous balance mode sabm");break;
                        case 0x6C:printf("\nset asincronous balance extended mode sabme");break;
                        case 0x04:printf("\nset inicialitation mode sim");break;
                        case 0x40:printf("\ndisconect dist");break;
                        case 0x20:printf("\nunnumbered poll up");break;
                        case 0x8C:printf("\nreset");break;
                }
        }
        else
        {
		printf("\npoll/final: 0");
                switch((byteone&0xEC))
                {
                        case 0x60:printf("\nunnumbered Acknowledgment UA");break;
                        case 0x0C:printf("\ndisconect mode dm");break;
                        case 0x40:printf("\nrequest disconect rd");break;
                        case 0x01:printf("\nrequest initialitacion mode rim");break;
                        case 0x81:printf("\nframe reject frmr");break;
                }
        }
        switch((byteone&0xEC))
        {
                case 0x00:printf("\nunnumered informacion ui");break;
                case 0xAC:printf("\nexchange identification xid");break;
                case 0xE0:printf("\ntest");break;
        }
        printf("\n");
        return 0;
}
int chektwobytes(unsigned char byteone,unsigned char bytetwo,int opc)//opc 0 informacion 1 supervicion
{
        if(opc)
        {
                switch((byteone&0x0C))
                {
                        case 0:printf("\nreseptor listo (rr)");break;
                        case 4:printf("\nreseptor no listo (rnr)");break;
                        case 8:printf("\nretransmicion (rej)");break;
                        case 12:printf("\nretransmicion selectiva (srej)");break;
                }
        }
        else
       	{
		printf("\nnumero de secuencia de envio: %d",((byteone&0xFC)>>2));
	}
	printf("\npoll/final: %d",(bytetwo&0x01));
/*        if((bytetwo&0x03)==1)
                {printf("\nrequiere una respuesta inmediata");}*/
        printf("\nnumero de secuencia que se espera recivir: %d",((bytetwo&0xFE)>>1));
        printf("\n");
        return 0;
}
void *analisatrama(void *args)
{
	llc *f=cabt;
	int longitud;
	while(1)
	{
		f=cabt;
		while(f!=NULL)
		{
        		printf("\ntrama llc recivida\n\n");
			imprime(f->trama,148);
			memcpy(tumac+0,f->trama+6,6);
                        memcpy(macdes+0,f->trama+0,6);
                        printf("\nmac origen:\t\t");putmac(tumac);
                        printf("\nmac destino:\t\t");putmac(macdes);
                        longitud=(f->trama[12]*256 + f->trama[13] );
                        printf("\nlongitud:\t\t%d",longitud);
                        sap[3]=dsapandssap(f->trama[14],f->trama[15]);
                        //printf("\norigen:\t\t%x",sap[0]);
                        //printf("\ndestino:\t\t%x",sap[1]);
                        sap[4]=innusu(f->trama[16]);
                        if(sap[4]==0||sap[4]==2)
                                chektwobytes(f->trama[16],f->trama[17],0);
                        if(sap[4]==1)
                                chektwobytes(f->trama[16],f->trama[17],1);
                        if(sap[4]==3)
                                chekonebyte(f->trama[16]);
                        while(f->sig==NULL){;}
                        f=f->sig;
                        printf("\n ya ahy otra trama por analisar presione enter porfavor!!");
                        getchar();
                        getchar();
                }
        }
        return("termine de mostrar");
}
			
