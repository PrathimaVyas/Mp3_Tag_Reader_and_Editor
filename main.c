#include"main.h"
#include<stdlib.h>
int main(int argc,char **argv)
{
    if(argc >5)
    {
	printf("ERROR : INVALID ARGUMENTS IN CLA\n");
	return 0;
    }
    else if(argc == 1)
    {
	printf("------------------------------------------------------\n");
	printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE: \nTo view please pass like : ./a.out -v mp3filename\n");
	printf("To edit please pass like : ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------\n");
	return 0;
    }
    else
    {
	if(read_and_validate(argv) == SUCCESS)	
	{
	    printf("VAlidation successful\n");
	    return SUCCESS;
	}
	else
	{
	    return FAILURE;
	}
    }
}


int read_and_validate(char **argv)
{
    if(strcmp(argv[1],"-v") == 0)
    {
	printf("View mode selected\n");
	if(view_mode(argv[2])==SUCCESS)
	   exit(0);    // return SUCCESS is giving segmentation fault so exit the program
	else
	    return FAILURE;
    }
    else if(strcmp(argv[1],"-e") == 0)
    {
	printf("Edit mode selected\n");
	 if(edit_mode(argv) == SUCCESS) //pass the option to edit and then filename
	     exit(0);
	 else
	     return FAILURE;
    }
    else if(strcmp(argv[1],"--help") == 0)
    {
	help_menu();
    }
    else
    {
	printf("Invalid option in argv[1]\n");
    }
}



void help_menu()
{
    printf("----------------------------HELP MENU-----------------------------\n");
    printf("1. -v --> to view the mp3 file contents\n");
    printf("2. -e --> to edit the mp3 file contents\n\t");
    printf("2.1  -t -> to edit song title\n\t");
    printf("2.2  -a -> to edit artist name\n\t");
    printf("2.3  -A -> to edit album name\n\t");
    printf("2.4  -y -> to edit year\n\t");
    printf("2.5  -m -> to edit content\n\t");
    printf("2.6  -c -> to edit comment\n");
    printf("------------------------------------------------------------------\n");
}

