#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH_OF_ITEM_ID 30
#define LENGTH_OF_ITEM_DESCRIPTION 80
#define DATA_FILE "item_details.dat"

struct item_details
{
	char item_id[LENGTH_OF_ITEM_ID];
	char item_description[LENGTH_OF_ITEM_DESCRIPTION];
	int item_price;
}items;

struct node
{
	struct item_details item_data;
	struct node *next;

}*head, *new_node, *current, *temp, *current2,*current3;

FILE *fp_data_file;
char item_id[LENGTH_OF_ITEM_ID];
int delete_value = 0;

struct node *get_record_address();

void show_data_as_in_file();
void sort();
void show_menu();
void free_nodes();
void update_item_price();
void update_item_description();
void load_data();
void create_record();
void show_data();
void update_record();
void save_record();
void delete_record();
void search_record();

void  show_menu()
{
	int user_choice;


	printf("----------------------------Item Details----------------------------------\n");
	printf("1)Create new record\n2)Show all records\n3)Update a record\n4)Search a record\n5)Delete a record\n6)sort records\n7)Exit");
	printf("\nEnter your choice: ");
	scanf("%d", &user_choice);

	switch(user_choice)
	{
		case 1 : create_record();
		         break;
      case 2 : show_data();
    	         break;
      case 3 : update_record();
         	   break;
      case 4:  search_record();
    	         break;
      case 5 : delete_record();
    	         break;
      case 6 : sort();
      	      break;
      case 7:  fclose(fp_data_file);
               exit(0);

	   default :printf("Enter valid choice...\n");

	}

}

void load_data()
{
	  	fp_data_file = fopen(DATA_FILE, "r");

 while(fread(&items, sizeof(struct item_details), 1, fp_data_file ))
 {
   // printf("%s\n", items.item_id);
 	new_node = malloc(sizeof(struct node));
 	new_node-> item_data = items;
 	// printf("%s\n", new_node->item_data.item_id);
 	new_node -> next = NULL;

 	if(head == NULL)
 	{
 		head = current = new_node;
 		printf("%s\n", head->item_data.item_id);


 	}

 	else
 	{
 		current -> next = new_node;
 		current = new_node;
 	}
 }

}
void create_record()
{
	
	printf("\nEnter item id: ");
	scanf("%s", items.item_id);
	// printf("id:%s", items.item_id);

	printf("\nEnter item description: ");
	scanf(" %[^\n]s", items.item_description);
	// printf("item_description:%s",items.item_description);


	printf("\nEnter item price: ");
	scanf("%d", &items.item_price);
	// printf("item price:%d",items.item_price);


	new_node = malloc(sizeof(struct node));
	new_node -> item_data = items;
	new_node -> next = NULL;

	if(head == NULL)
	{
		head = current = new_node;
	}
	else if(head -> next == NULL)
	{
       head -> next = new_node;
       current = new_node;
	}
	else
	 {
		for(current = head; current != NULL; current = current -> next)
		{
	          if(current ->next == NULL)
	          {
	          	current ->next = new_node;
	          	current = new_node;

	          }
		}

    }
   save_record();
}

void save_record()
{
   fp_data_file = fopen(DATA_FILE, "w");
   for(current = head; current != NULL; current = current -> next)
   {

   		fwrite(&(current -> item_data), sizeof(struct item_details), 1, fp_data_file);

   }
   fclose(fp_data_file);

}

void show_data()
{
	// load_data();

	printf("\n-----------------------item details-------------------------\n");
	 if(head == NULL)
	{
		printf("\n No data is present in the nodes to show.\n");
	}
	else
	{


		for(current = head; current != NULL; current = current -> next)
		{

			printf("\nItem id: %s", current ->item_data.item_id);
			printf("\nItem description of item id %s: %s",  current ->item_data.item_id, current -> item_data.item_description);
			printf("\nItem price of item id %s: %d",  current ->item_data.item_id, current -> item_data.item_price);
		   printf("\n------------------------------------------------\n");
		}
	}
         
}

void free_nodes()
{
	temp = head;
	while(temp != NULL)
	{
      head = head -> next;
      free(temp);
      temp = head;

	}

}
void get_item_id()
{
	printf("Enter item_id to search: ");
	scanf("%s", item_id);     
}

struct node *get_record_address()
{
	get_item_id();
	   if(head == NULL)
	{
		return NULL;
	}
	else
	{


		for(current = head; current != NULL; current = current -> next)
		{
			if(delete_value == 1)
			{ 
		      
		     	  if(!(strcmp(current->item_data.item_id, item_id)))
		     	  {   
	               return current;
		     	  }
		     	  else
		     	  {	if(current -> next != NULL)
		     	      {

			       		 if(!(strcmp(current -> next ->item_data.item_id, item_id)))
			        		{
			         	return current;
			        		}

		     	      }
		     	  }

		     

			}
			else
			{

				if(!(strcmp(current->item_data.item_id, item_id)))
				{
					return current;
				}
			}	
			
		}
	}
	return NULL;
}


void search_record()
{
	// load_data();
	current = get_recordpostion();

  if(current != NULL)
   {

		printf("\nItem id: %s", current ->item_data.item_id);
		printf("\nItem description of item id %s: %s", item_id, current -> item_data.item_description);
		printf("\nItem price of item id %s: %d\n", item_id, current -> item_data.item_price);
   }

	else
	{
			printf("%s id is not found\n", item_id);
	}
	
}

void update_record()
{
	// load_data();
	current = get_recordpostion();
	int user_choice;

	if(current !=NULL)
	{

		printf("\nEnter your choice to update details \n1)update item description\n2)update item price");
		scanf("%d", &user_choice);

		switch(user_choice)
		{
		  	case 1:  update_item_description();
				      break;
		   case 2:  update_item_price();
		    	      break;
		   case 3:  update_item_description();
		    	      update_item_price();
		    	      break;
		   default: printf("\nEnter valid choice...\n");
		}

	
	}
   else
	{
			printf("%s id is not found.\n", item_id);
	}
	
save_record();


}

void update_item_description()
{
	printf("\nEnter new description for %s id: ", current -> item_data.item_id);
	scanf(" %[^\n]s", current -> item_data.item_description);
	printf("\n%s id's description is updated...\n", item_id);

}


void update_item_price()
{
	printf("\nEnter new price for %s: ", current ->item_data.item_id);
	scanf(" %d", &(current -> item_data.item_price));
	printf("\n%s id's price is updated...\n", item_id);
}

void delete_record()
{

	delete_value = 1;
	current = get_recordpostion();
    
	if(current != NULL)
	{
      if(current == head)
      {

      	head = head -> next;
			current -> next = NULL;
			free(current);
      }
      else 
      {

			current2 = current -> next;
			current -> next = current2 -> next;
			current2 ->next = NULL;
			free(current2);

      }
      printf("\n%s id is successfully deleted\n", item_id);
	}
   else
   {
   	printf("\n%s id is not found\n", item_id);
   }
   save_record();

}

void sort()
{
		
		current3 = malloc(sizeof(struct node));


	for(current = head; current != NULL; current = current -> next)

	{
		for(current2 = head; current2->next != NULL; current2 = current2 -> next)
		{
	  				               
			if(strcmp(current2->item_data.item_id , current2->next->item_data.item_id) > 0)
			{
						 				            
				current3 -> item_data = current2->item_data;
				current2 -> item_data = current2->next -> item_data;
				current2 -> next -> item_data = current3 -> item_data;
            
			}
		}
	}
   show_data();
   free_nodes();
   load_data();		
}


void main()
{  
  

	load_data();

	 while(1)
	{

		show_menu();

	}

}