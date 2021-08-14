#include "vol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
enum 
{
 DEPART,
 ARRIVEE,
 DATEA,
 DATER,
 CLASSE,
 PRIX,
 COLUMNS
};
void ajouter (vol *v)
{
FILE *f;
f=fopen("vol.bin","ab"); //ouvrir un fichier en mode ajout
if(f!=NULL) //si le fichier est ouvert 
{
fwrite(v,sizeof(vol),1,f);
fclose(f); } //fermeture du fichier
}

void afficher (GtkWidget *liste)
{struct vol v;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
store=NULL;
FILE *f;
store=gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
if (store==NULL)
{
renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes(" Depart ", renderer,"text",DEPART,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes(" Arrivée ", renderer,"text",ARRIVEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes(" Date d'aller", renderer,"text",DATEA,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes("Date de retour", renderer,"text",DATER,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);


renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes("Classe", renderer,"text",CLASSE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);

renderer=gtk_cell_renderer_text_new();
column= gtk_tree_view_column_new_with_attributes("Prix", renderer,"text",PRIX,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW (liste), column);


}
store= gtk_list_store_new (COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_UINT,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("vol.bin","rb"); 
if(f!=NULL) 
{fread (&v, sizeof(vol),1,f);
while (!(feof(f)))
{
fread (&v, sizeof(vol),1,f);

char r1[20];
char r2[20];
char r3[20];
char r4[20];
char r5[20];
char r6[20];
char dt_aller[500];
char dt_retour[500];
dt_aller[0]='\0';dt_retour[0]='\0';
sprintf(r1,"%d",v.aller.jour);
strcat(dt_aller,r1);
strcat(dt_aller,"/");

sprintf(r2,"%d",v.aller.mois);
strcat(dt_aller,r2);
strcat(dt_aller,"/");

sprintf(r3,"%d",v.aller.annee);
strcat(dt_aller,r3);

sprintf(r4,"%d",v.retour.jour);
strcat(dt_retour,r4);
strcat(dt_retour,"/");
sprintf(r5,"%d",v.retour.mois);
strcat(dt_retour,r5);
strcat(dt_retour,"/");
sprintf(r6,"%d",v.retour.annee);
strcat(dt_retour,r6);

gtk_list_store_append(store, &iter);
gtk_list_store_set(store,&iter,DEPART,v.depart,ARRIVEE,v.arrivee,CLASSE,v.classe,DATEA,dt_aller,DATER,dt_retour,PRIX,v.prix, -1);
}

fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL(store));
g_object_unref(store);
}
}
/*********Supp User***************/
void dell_user(char *depart)
{
vol v;
FILE *old;
FILE *new=NULL;
/*****create a temporary file *****/
new=fopen("vol_test.bin","wb");
fclose(new);
/******copy data from old to new *******/
old=fopen("vol.bin","rb");
new=fopen("vol_test.bin","ab");
/**************************/
int i=0;
while(!(feof(old)))
	{i++;
	fread(&v,1,sizeof(vol),old);
	}
fclose(old);
old=fopen("vol.bin","rb");
/******************************/
int j=0;
while(j<i-1)
	{j++;
	fread(&v,1,sizeof(vol),old);
	g_print("Psuedo  : %s\n",v.depart);
	if(strcmp(v.depart,depart))
		{	
		fwrite(&v,sizeof(vol),1,new);
		}
	}
fclose(new);
fclose(old);
remove("vol.bin");//nfas5ou il fichier li9dim
rename("vol_test.bin","vol.bin");//enronomiw il fichier ejdid b esm li9dim bech ye5ou blastou
/*****Na3mlo Actualiser lil liste **************/

}


