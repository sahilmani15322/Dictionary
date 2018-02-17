#include"bits/stdc++.h"
using namespace std;

FILE *file_ptr;
struct node
{
 char word[20],meaning[100];
 node *left,*right;
};

void showmenu()
{
 printf("+------COMPUTER DICTIONARY------+");
 printf("\n|1.Add a word.                  |");
 printf("\n|2.Find meaning.                |");
 printf("\n|3.Display all.                 |");
 printf("\n|4.Save and Close.              |");
 printf("\n+-------------------------------+");
 printf("\nEnter Choice::");
}

node* maketree(char w[],char m[])
{
 node *p;
 p=new node;
 strcpy(p->word,w);
 strcpy(p->meaning,m);
 p->left=NULL;
 p->right=NULL;
 return p;
}

void addword(node **tree,char word[],char meaning[])
{
	node *p,*q;
	p=q=*tree;
	while(p!=NULL&&strcmp(word,p->word)!=0)
	{
		q=p;
		if(strcmp(word,p->word)<0)
			p=p->left;
		else
			p=p->right;
	}
	
	if(strcmp(word,q->word)==0)
	{
		printf("This word already exists...");
	}
	else if(strcmp(word,q->word)<0)
		q->left=maketree(word,meaning);
	else
		q->right=maketree(word,meaning);
}

void seperateword(char str[],char w[],char m[])
{
	int i,j;
	for(i=0;str[i]!=' ';i++)
		w[i]=str[i];
	w[i++]='\0';	
	for(j=0;str[i]!='\0';i++,j++)
		m[j]=str[i];
	m[j]='\0';
}

node* treefromfile()
{
	node *ptree=NULL;
	char word[20],meaning[100],str[120],*i;
	int flags=0;
	file_ptr=fopen("dictionary.txt","r");
	if(file_ptr==NULL)
		ptree=NULL;
	else
	{
		while(!feof(file_ptr))
		{
			i=fgets(str,120,file_ptr);
			if(i==NULL)
				break;
			seperateword(str,word,meaning);
			if(flags==0)
			{
				ptree=maketree(word,meaning);
				flags=1;
			}
			else
				addword(&ptree,word,meaning);
		}
		
		fclose(file_ptr);
	}
	return ptree;
}

node* bsearch(node *tree,char word[])
{
	node *q;
	q=tree;
	while(q!=NULL)
	{
		if(strcmp(word,q->word)<0)
			q=q->left;
		else if(strcmp(word,q->word)>0)
			q=q->right;
		if(strcmp(word,q->word)==0)
			break;
	}
	return q;
}

void travandwrite(node *tree)
{
	if(tree!=NULL)
	{
		fprintf(file_ptr,"%s %s\n",tree->word,tree->meaning);
		travandwrite(tree->left);
		travandwrite(tree->right);
	}
}

void filefromtree(node *tree)
{
	file_ptr=fopen("dictionary.txt","w");
	if(file_ptr==NULL)
	{
		printf("Cannot open file for writing data!!!");
	}
	else 
	{
		if(tree!=NULL)
		{
			travandwrite(tree);
		}
		fclose(file_ptr);  
	}
}


void displayall(node *tree)
{
 if(tree!=NULL)
 {
  displayall(tree->left);
  printf("%s : %s\n",tree->word,tree->meaning);
  displayall(tree->right);
 }
}
void prog()
{
 system("cls");
 char word[20],meaning[100];
 int menuchoice;
 node *temp;
 temp=treefromfile();
 if(temp==NULL)
 {
	printf("File does not exist or dictionary is empty...");
 }
 while(1)
 {
	  system("cls");
	  showmenu();
	  scanf("%d",&menuchoice);
	  switch(menuchoice)
	  {
		   case 1:
				printf("Enter word ::");
				scanf("%s",word);
				cin.ignore();
				printf("Enter meaning ::" );
				gets(meaning);
				if(temp==NULL)
				temp=maketree(word,meaning);
				else
				addword(&temp,word,meaning);
				break;
				  
		   case 2:
				if(temp==NULL)
				printf("The dictionary is empty...");
				else
				{
					printf("Find Meaning of : ");
					cin.ignore();
					gets(word);
					node *t;
					t=bsearch(temp,word);
					if(t==NULL)
						printf("Word not found...");
					else
					{
					    printf("%s : ",t->word);
					    puts(t->meaning);
					}
				}
				system("pause");
				break;
		   case 3:
				if(temp==NULL)
					printf("Dictionary is Empty!!!");
				else
					displayall(temp);
				system("pause");
				break;
		   case 4:
	   			filefromtree(temp);
			 	exit(1);
			 	break;
		   default:cout<<"Enter Again";
			  	   prog();
				   break;
	  }
 }
}

int main()
{
	prog();
	return 0;
}

