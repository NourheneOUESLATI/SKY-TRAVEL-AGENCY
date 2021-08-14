#include<stdlib.h>
#include<stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "hotel.h"
#include"Admin.h"
#include"Users.h"
#include "support.h"
#include "callbacks.h"
Hotel get_hotel_info(GtkWidget *objet_graphique)
{
Hotel hotel;
GtkWidget *input;
//Get Nom Hotel
input = lookup_widget(objet_graphique, "entry_ajout_nom_hotel") ;
strcpy(hotel.Nom,gtk_entry_get_text(GTK_ENTRY(input)));

//Get Lieu Hotel
input = lookup_widget(objet_graphique, "entry_ajout_lieu_hotel") ;
strcpy(hotel.Lieu,gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_simple_1pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_hotel_ch_simple_1_personne") ;
hotel.Prix_ch_simple_1pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_double_1pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_chamb_double_1_personne") ;
hotel.Prix_ch_double_1pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_double_2pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_cham_double_2_personnes") ;
hotel.Prix_ch_double_2pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_Triple_1pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_cham_1_personne") ;
hotel.Prix_ch_Triple_1pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_Triple_2pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_cham_triple_2_personnes") ;
hotel.Prix_ch_Triple_2pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_ch_Triple_3pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_cham_triple_3_personnes") ;
hotel.Prix_ch_Triple_3pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_sweat_1pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_sweat_1_personne") ;
hotel.Prix_sweat_1pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_sweat_2pers Hotel
input = lookup_widget(objet_graphique, "entry_prix_sweat_2_personnes") ;
hotel.Prix_sweat_2pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));

//Get Prix_sweat_3pers Hotel
input = lookup_widget(objet_graphique, "entry_sweat_3_personnes") ;
hotel.Prix_sweat_3pers=atoi(gtk_entry_get_text(GTK_ENTRY(input)));
//Get Categorie Hotel

input = lookup_widget(objet_graphique, "entry_Cat_hotel") ;
g_print("look up ok");
strcpy(hotel.Categorie,gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
g_print("strcpy ok");

//Get TEl Hotel
input = lookup_widget(objet_graphique, "entry_ajout_telephone_hotel") ;
strcpy(hotel.Tel,gtk_entry_get_text(GTK_ENTRY(input)));

return hotel;

}
void save_hotel(Hotel H)
{
FILE *f;
f=fopen("Hotel.bin","ab");
if(f!=NULL)
{
fwrite(&H,sizeof(Hotel),1,f);
}
fclose(f);
}


enum
{	
	c_NOM_HOTEL,
	c_LIEU,
	c_CAT,
	c_PRIX,
	c_TEL,
	c_COLUMNS
};


void afficher_hotel(GtkWidget *liste)
{

 GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter    iter;
	GtkListStore *store;

  store=gtk_tree_view_get_model(liste);
  if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Hotel", renderer, "text",c_NOM_HOTEL, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Lieu", renderer, "text",c_LIEU, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);
	
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Categorie", renderer, "text",c_CAT, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Prix", renderer, "text",c_PRIX, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes(" Telephone", renderer, "text",c_TEL, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste), column);

		
	}

store=gtk_list_store_new (c_COLUMNS, G_TYPE_STRING,  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

struct Hotel X;
FILE *f;
/******************************************************/
f=fopen("Hotel.bin","rb");
int i=0;
while(!(feof(f)))
{
fread(&X,1,sizeof(X),f);
i++;
}
fclose(f);
/************************************enum
{	
	c_NOM_HOTEL,
	c_LIEU,
	c_CAT,
	c_PRIX,
	c_TEL,
	c_COLUMNS
};**********/
f=fopen("Hotel.bin","rb");

if(f!=NULL)
	{
	int j=0;
	while(j<i-1)
		{
		fread(&X,1,sizeof(X),f);
		
		
		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter, c_NOM_HOTEL, X.Nom, c_LIEU, X.Lieu, c_CAT, X.Categorie,c_PRIX,i_to_a(X.Prix_ch_simple_1pers),c_TEL,X.Tel, -1); j++;
		}
	fclose(f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste),  GTK_TREE_MODEL (store));
        g_object_unref (store);
	}




}
void supp_hotel(Hotel Selected_Hotel)
{
struct Hotel H;
FILE *f=NULL;
FILE *d;
f=fopen("Hotel.bin","rb");
d=fopen("Hoteltmp.bin","wb");
fclose(d);
d=fopen("Hoteltmp.bin","ab");
if(f!=NULL);
{
while(!(feof(f)))	

	{
	fread(&H,1,sizeof(Hotel),f);
	if((strcmp(H.Nom,Selected_Hotel.Nom)!=0)&&(strcmp(H.Tel,Selected_Hotel.Tel)!=0)&&(strcmp(H.Lieu,Selected_Hotel.Lieu))!=0)
	{
	fwrite(&H,sizeof(Hotel),1,d);
	}
	}
fclose(d);
fclose(f);
}
remove("/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Hotel.bin");
rename("/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Hoteltmp.bin","/home/bouzayen/Desktop/Skytraveltodo/SkyTravel/src/Hotel.bin");
}
void set_hotel_info(GtkWidget *objet_graphique,Hotel hotel)
{char  str[20];

GtkWidget *input;
//set Nom Hotel
input = lookup_widget(objet_graphique, "entry_modif_nom_hotel") ;
gtk_entry_set_text(GTK_ENTRY(input),hotel.Nom);
//Get Lieu Hotel
input = lookup_widget(objet_graphique, "entry_modif_lieu_hotel") ;
gtk_entry_set_text(GTK_ENTRY(input),hotel.Lieu);

//set Prix_ch_simple_1pers Hotelentry_modif_prix_chamb_double_1_personne
input = lookup_widget(objet_graphique, "entry_modif_prix_chamb_simple_1_personne") ;
sprintf(str,"%d",hotel.Prix_ch_simple_1pers);
g_print("%s|%d",str,hotel.Prix_ch_simple_1pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);

//set Prix_ch_double_1pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_chamb_modif_double_1_personne") ;
sprintf(str,"%d", hotel.Prix_ch_double_1pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set Prix_ch_double_2pers Hotelentry_modif_prix_chamb_modif_double_1_personne
input = lookup_widget(objet_graphique, "entry_modif_prix_cham_double_2_personnes") ;
sprintf(str,"%d", hotel.Prix_ch_double_2pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set Prix_ch_Triple_1pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_cham_1_personne") ;
sprintf(str,"%d", hotel.Prix_ch_Triple_1pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set Prix_ch_Triple_2pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_cham_triple_2_personnes") ;
sprintf(str,"%d", hotel.Prix_ch_Triple_2pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set Prix_ch_Triple_3pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_cham_triple_3_personnes") ;
sprintf(str,"%d", hotel.Prix_ch_Triple_3pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set Prix_sweat_1pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_sweat_1_personne") ;
sprintf(str,"%d", hotel.Prix_sweat_1pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//Get Prix_sweat_2pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_prix_sweat_2_personnes") ;
sprintf(str,"%d", hotel.Prix_sweat_2pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//Get Prix_sweat_3pers Hotel
input = lookup_widget(objet_graphique, "entry_modif_sweat_3_personnes") ;
sprintf(str,"%d", hotel.Prix_sweat_3pers);
gtk_entry_set_text((GTK_ENTRY(input)),str);
//set TEl Hotel
input = lookup_widget(objet_graphique, "entry_modif_telephone_hotel") ;
gtk_entry_set_text((GTK_ENTRY(input)),hotel.Tel);


}






























