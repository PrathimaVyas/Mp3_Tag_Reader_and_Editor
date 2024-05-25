#include"main.h"
#include<stdlib.h>
int edit_mode(char **argv)
{
    Tagreader *Tag;
    Tag -> fptr = fopen(argv[4],"r+");
    if(Tag -> fptr == NULL)
    {
	printf("INFO : Given file is empty\n");
	return FAILURE;
    }
    fseek(Tag->fptr,0,SEEK_SET);
    char buffer[3];
    fread(buffer,sizeof(char),3,Tag->fptr);
    if(strcmp(buffer,"ID3")==0)
    {
	char buffer[2];
	fread(buffer,sizeof(char),2,Tag->fptr);
	if(buffer[0] == 0x03 && buffer[1] == 0x00)
	{
	    fseek(Tag->fptr,10,SEEK_SET);
	    if(check_tag_to_edit(argv,Tag)==SUCCESS);
	    else
		return FAILURE;
	}
	else
	{
	    printf("INFO : Version not matched\n");
	    return FAILURE;
	}

    }
    else
    {
	printf("INFO : Metadata container(ID3) is not matched\n");
	return FAILURE;
    }
}

int check_tag_to_edit(char **argv, Tagreader *Tag)
{

    fread(Tag->tag,sizeof(char),4,Tag->fptr);
    Tag->tag[4]='\0';
    fread(&(Tag->size),sizeof(char),4,Tag->fptr);
    char *cptr = (char *)&(Tag->size);
    fseek(Tag->fptr,3,SEEK_CUR);
    for(int i=0;i<2;i++)
    {
	char temp = cptr[i];
	cptr[i] = cptr[4-i-1];
	cptr[4-i-1] = temp;
    }

    if((strcmp(argv[2],"-t") == 0) && (strcmp(Tag->tag,"TIT2")==0))
    {
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Title changed successfully\n");
	    exit(0);
	}
	else
	{
	    printf("INFO : Failed to change title\n");
	    return FAILURE;
	}
    }

    skip_cursor_till_the_required_tag(Tag,cptr);

    if((strcmp(argv[2],"-a")==0) && (strcmp(Tag->tag,"TPE1")==0))
    {
	printf("TAG matched\n");
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Artist name changed successfully\n");
	    return SUCCESS;
	}
	else
	{
	    printf("INFO : Failed to change artist name\n");
	    return FAILURE;
	}

    }

    skip_cursor_till_the_required_tag(Tag,cptr);

    if((strcmp(argv[2],"-A")==0) && (strcmp(Tag->tag,"TALB")==0))
    {
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Album name changed successfully\n");
	    return SUCCESS;
	}
	else
	{
	    printf("INFO : Failed to change album name\n");
	    return FAILURE;
	}
    }

    skip_cursor_till_the_required_tag(Tag,cptr);

    if((strcmp(argv[2],"-y")==0) && (strcmp(Tag->tag,"TYER")==0))
    {
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Year changed successfully\n");
	    return SUCCESS;
	}
	else
	{
	    printf("INFO : Failed to change album name\n");
	    return FAILURE;
	}
    }

    skip_cursor_till_the_required_tag(Tag,cptr);

    if((strcmp(argv[2],"-m")==0) && (strcmp(Tag->tag,"TCON") == 0))
    {
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Content changed successfully\n");
	    return SUCCESS;
	}
	else
	{
	    printf("INFO : Failed to change album name\n");
	    return FAILURE;
	}
    }

    skip_cursor_till_the_required_tag(Tag,cptr);

    if((strcmp(argv[2],"-c") == 0) && (strcmp(Tag->tag, "COMM") == 0))
    {
	if(edit(Tag,argv[3]) == SUCCESS)
	{
	    printf("Comment changed successfully\n");
	    return SUCCESS;
	}
	else
	{
	    printf("INFO : Failed to change album name\n");
	    return FAILURE;
	}
    }

}

int edit(Tagreader *Tag,char *name)
{
    char duplicate[Tag->size+1];
    strcpy(duplicate,name);
    int i=0;
    printf("Duplicate %s\n",duplicate);
    while(duplicate[i]!= '\0')
    {
	i++;
    }
    for(int j=i;j<=Tag->size;j++)
    {
	duplicate[j] = '\0';
    }

    duplicate[Tag->size] = '\0';
    fwrite(duplicate,sizeof(char),(Tag->size)-1,Tag -> fptr);
    return SUCCESS;
}

int skip_cursor_till_the_required_tag(Tagreader *Tag, char *cptr)
{
    fseek(Tag->fptr,Tag->size-1,SEEK_CUR);
    fread(Tag->tag,sizeof(char),4,Tag->fptr);
    Tag->tag[4] = '\0';
    fread(&(Tag -> size),sizeof(char),4,Tag->fptr);
    cptr = (char *)&(Tag ->size);
    fseek(Tag -> fptr,3,SEEK_CUR);
    for(int i=0;i<2;i++)
    {
	char temp = cptr[i];
	cptr[i] = cptr[4-i-1];
	cptr[4-i-1] = temp;
    }
}
