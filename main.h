#include<stdio.h>
#include<string.h>
#define SUCCESS 1
#define FAILURE 0

typedef struct mp3_tag_reader
{
    char *filename;
    char tag[5];
    int size;
    int version;
    FILE *fptr;
}Tagreader;
int read_and_validate(char **argv);

int view_mode(char *filename);
int view_tag(Tagreader *Tag);
int tag(Tagreader *Tag,char *tag,char *name);

int edit_mode(char **argv);
int edit(Tagreader *Tag,char *name);
int check_tag_to_edit(char **argv,Tagreader *Tag);

int skip_cursor_till_the_required_tag(Tagreader *Tag, char *cptr);
void help_menu();


