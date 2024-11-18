#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	char text[100];
	int key,choice;
	printf("enter message:");
	gets(text);
	printf("enter a key:");
	scanf("%d",&key);
	printf("enter choice: 1.encryption 2.decryption:");
	scanf("%d",&choice);
	switch(choice){
     case 1:{
		
	    for(int i=0;text[i]!='\0';i++)
    	{
		if(isalpha(text[i]))
		{
		char base=isupper(text[i])?'A':'a';
		char r=(text[i]-base+key)%26+base;
		text[i]=r;
    	}
		}
		printf("encrypted text:%s",text);
	    break;
	    }
     case 2:{
    	for(int i=0;text[i]!='\0';i++)
	    {
		if(isalpha(text[i]))
		{
		char base=isupper(text[i])?'A':'a';
		char r=(text[i]-base-key)%26+base;
		text[i]=r;
	    }
		}
		printf("decrypted text:%s",text);
		break;
	   }
	 default:
		printf("invalid choice");
	}
	}
	
