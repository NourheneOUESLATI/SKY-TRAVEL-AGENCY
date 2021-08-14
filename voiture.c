
#include<stdlib.h>
#include<stdio.h>
#include <gtk/gtk.h>
#include <string.h>

#include"Admin.h"
#include"Users.h"
#include "support.h"
#include "callbacks.h"
#include "voiture.h"
Voiture get_voiture_info(GtkWidget *objet_graphique)
{
Voiture voiture;
GtkWidget *input;
//Get ajout_marque
input = lookup_widget(objet_graphique, "entry_ajout_marque") ;
strcpy(voiture.Marque,gtk_entry_get_text(GTK_ENTRY(input)));

//Get ajout_matricule
input = lookup_widget(objet_graphique, "entry_ajout_matricule") ;
strcpy(voiture.Matricule,gtk_entry_get_text(GTK_ENTRY(input)));

//Get ajout_date
input = lookup_widget(objet_graphique, "entry_ajout_date") ;
strcpy(voiture.Date,gtk_entry_get_text(GTK_ENTRY(input)));

//Get ajout_prix
input = lookup_widget(objet_graphique, "entry_ajout_prix") ;
strcpy(voiture.Prix,gtk_entry_get_text(GTK_ENTRY(input)));
//Get ajout_Lieu
input = lookup_widget(objet_graphique, "entry_ajout_lieu_voiture") ;
strcpy(voiture.Lieu,gtk_entry_get_text(GTK_ENTRY(input)));

//Get ajout_telephone
input = lookup_widget(objet_graphique, "entry_ajout_telephone") ;
strcpy(voiture.Tel,gtk_entry_get_text(GTK_ENTRY(input)));

return voiture;

}

////////////////////////////////
void save_voiture (Voiture v)
{
FILE *f;
f=fopen("voiture.bin","ab");
if(f!=NULL)
{
fwrite(&v,sizeof(Voiture),1,f);
}
fclose(f);
}
/////////////////////////////////

enum
{	
	c_MATRICULE,
	c_LIEU,
	c_MARQUE,
	c_PRIX,
        c_DATE,
	c_TEL,
	c_COLUMNS
};
////////////////////////////////////////


void afficher_voiture(GtkWidget *liste)
{

 GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter    iter;
	GtkListStore *store;

  store=gtk_tree_view_get_model(liste);
  if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("Voiture", renderer, "text",c_MATRICULE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Lieu", renderer, "text",c_LIEU, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Marque", renderer, "text",c_MARQUE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Prix", renderer, "text",c_PRIX, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
        renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Date", renderer, "text",c_DATE, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Telephone", renderer, "text",c_TEL, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		
	}
store=gtk_list_store_new (c_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

struct Voiture X;
FILE *f;
/******************************************************/
f=fopen("Voiture.bin","rb");
int i=0;
while(!(feof(f)))
{
fread(&X,1,sizeof(X),f);
i++;
}
fclose(f);
/***********************/
enum
{	
	c_MATRICULE,
	c_LIEU,
	c_MARQUE,
	c_PRIX,
        c_DATE,
	c_TEL,
	c_COLUMNS
};
/***************************/

f=fopen("Voiture.bin","rb");

if(f!=NULL)
	{
	int j=0;
	while(j<i-1)
		{
		fread(&X,1,sizeof(X),f);
		g_print("\nTel : %s",X.Tel);
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter,c_MATRICULE , X.Matricule, c_LIEU, X.Lieu, c_MARQUE, X.Marque,c_PRIX,X.Prix ,c_TEL,X.Tel, -1); j++;
		}
	fclose(f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste),  GTK_TREE_MODEL (store));
        g_object_unref (store);
	}





}
void supp_voiture (Voiture Selected_Voiture)
{
struct Voiture v;
FILE *f=NULL;
FILE *d;
f=fopen("Voiture.bin","rb");
d=fopen("Voituretmp.bin","wb");
fclose(d);
d=fopen("Voituretmp.bin","ab");
if(f!=NULL);
{
while(!(feof(f)))	

	{
	fread(&v,1,sizeof(Voiture),f);
	if((strcmp(v.Matricule,Selected_Voiture.Matricule)!=0)&&(strcmp(v.Tel,Selected_Voiture.Tel)!=0)&&(strcmp(v.Lieu,Selected_Voiture.Lieu))!=0)
	{
	fwrite(&v,sizeof(Voiture),1,d);
	}
	}
fclose(d);
fclose(f);
}
remove("/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Voiture.bin");
rename("/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Voituretmp.bin","/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Voiture.bin");
}
