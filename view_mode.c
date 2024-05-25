#include"main.h"
int view_mode(char *filename)
{
    Tagreader *Tag;
    if(strstr(filename,".mp3") != NULL)
    {
	Tag -> filename = filename ; //storing the mp3 file in the structure filename
	Tag -> fptr = fopen(filename,"r");
	if(Tag -> fptr != NULL)
	{
	    char buffer[3];

	    fseek(Tag -> fptr,0,SEEK_SET);
	    fread(buffer,sizeof(char),3,Tag -> fptr);
	    if(strcmp(buffer,"ID3") == 0)  //check whether it is ID3 or not
	    {
		unsigned char buffer[2];
		fread(buffer,sizeof(char),2,Tag -> fptr); //check for the version which means fetch next 2 bytes of data
		if(buffer[0] == 0x03 && buffer[1] == 0x00)
		{
		    fseek(Tag -> fptr,10,SEEK_SET); //to view the tag we have to skip the header , here header is 10 bytes so skip first 10 bytes of data in audio file
		    if(view_tag(Tag) == SUCCESS) //check the tags after the header
		    {
			return SUCCESS;
		    }
		    else
		    {
			printf("FAilure\n");
			return FAILURE;
		    }

		}
		else
		{
		    printf("Version is not matched\n");
		    return FAILURE;
		}
	    }
	    else
	    {
		printf("Meta data container(ID3) is not matched\n");
		return FAILURE;
	    }

	}
	else
	{
	    printf("Given file is empty\n");
	    return FAILURE;
	}
    }
    else
    {
	printf("Given file is not mp3 file\n");
	return FAILURE;
    }
}


int view_tag(Tagreader *Tag)
{
    printf("------------------------SELECTED VIEW DETAILS----------------------\n\n");
    printf("-------------------------------------------------------------------\n");
    printf("---------------MP3 TAG EDITOR and VIEWER FOR ID3V2-----------------\n");
    if(tag(Tag,"TIT2","TITLE") == SUCCESS)
    {
	if(tag(Tag,"TPE1","ARTIST") == SUCCESS)
	{
	    if(tag(Tag,"TALB","ALBUM") == SUCCESS)
	    {
		if(tag(Tag,"TYER","YEAR") == SUCCESS)
		{
		    if(tag(Tag,"TCON","CONTENT") == SUCCESS)
		    {
			if(tag(Tag,"COMM","COMMENT") == SUCCESS)
			{
			    printf("-------------------------------------------------------------------\n");
			    printf("-------------------DETAILS DISPLAYED SUCCESSFULLY------------------\n\n");
			    return SUCCESS;
			}
			else
			{
			    printf("INFO : Failed to display the comments\n");
			    return FAILURE;
			}
		    }
		    else
		    {
			printf("INFO : Failed to display the content\n");
			return FAILURE;
		    }
		}
		else
		{
		    printf("INFO : Failed to display the year\n");
		    return FAILURE;
		}
	    }
	    else
	    {
		printf("INFO : Failed to display the album name\n");
		return FAILURE;
	    }
	}
	else
	{
	    printf("INFO : Failed to display the artise name\n");
	    return FAILURE;
	}
    }
    else
    {
	printf("INFO : Failed to display the title\n");
	return FAILURE;
    }
}

int tag(Tagreader *Tag,char *tag,char *name)
{
    fread(Tag -> tag,sizeof(char),4,Tag -> fptr);
    Tag ->tag[4] = '\0';	
    if(strcmp(Tag -> tag,tag) == 0)
    {
	fread(&(Tag -> size),sizeof(char),4,Tag -> fptr);

	char *cptr = (char *)&(Tag ->size);
	for(int i=0;i<2;i++)
	{
	    char temp = cptr[i];
	    cptr[i] = cptr[4-i-1];
	    cptr[4-i-1] = temp;
	}
	fseek(Tag ->fptr,3,SEEK_CUR); //move the cursor 2 times because to skip the flag
	char buffer[Tag -> size + 1]; //to store the title need to add 1 extra byte for null character
	fread(buffer,sizeof(char),(Tag->size)-1,Tag -> fptr);

	if(strcmp(name,"YEAR")==0)   //only for year last character is garbage value so i directly took the null for the year
	    buffer[4] = '\0';

	buffer[Tag ->size-1] = '\0';

	printf("%-12s : %s		\n",name,buffer);

	return SUCCESS;
    }
    return FAILURE;
}

