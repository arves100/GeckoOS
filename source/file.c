#include <gccore.h>
#include <fat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/dir.h>

#include "sd.h"
#include "gfx.h"
#include "file.h"
#include "menu.h"
#include "file.h"

#define font_y_spacing 22

int numfiles = 0;
int afiles = 0;
u32 filetop = 0;
struct foundfile *filelist = NULL;

//---------------------------------------------------------------------------------
void file_execute(struct foundfile *list, int top, int sel)
//---------------------------------------------------------------------------------
{
	int i;
	
	for( i=0; i<idcount; i++ )
	{
		if(list[i+top].id == file_menu_selected){	// current
			if(list[i+top].type == 0){	// DOL

			}

			if(list[i+top].type == 1){	// ELF

			}

			if(list[i+top].type == 2){	// WAD

			}

			if(list[i+top].type == 3){	// MP3

			}
		}
	}
}

//---------------------------------------------------------------------------------
void menu_showdirlist(struct foundfile *list, int top, int sel)
//---------------------------------------------------------------------------------
{
	int i;
	u32 file_y_screen = 100;

	if(!list){
		return;
	}

	if(!idcount || !sd_found){
		gfx_printf(tex_font1,180,file_y_screen,0xff,"No Files Found");
		goto nofileloop;
	}
	
	if(idcount >= 12){
		idcount = 12;
	}

	for( i=0; i<idcount; i++ )
	{
		//file_menu_selected
		if(list[i+top].id == file_menu_selected){
			gfx_printf(tex_font1,180,file_y_screen,textfade,list[i+top].showname);
		}
		else{
			gfx_printf(tex_font1,180,file_y_screen,0xff,list[i+top].showname);
		}

		file_y_screen += font_y_spacing;
	}

nofileloop:
	file_y_screen += font_y_spacing;

	gfx_printf(tex_font1,180,file_y_screen,0xff,"Press B to return");
}

//---------------------------------------------------------------------------------
void menu_scandir()
//---------------------------------------------------------------------------------
{
	char tempfilename[MAXPATHLEN];

	DIR *pdir;
	struct dirent* fstat = NULL;

	pdir=opendir("sd:/files");

	if( filelist == NULL )
	{
		numfiles = 0;
		afiles = 8;
		filelist = (struct foundfile *)malloc( sizeof( struct foundfile ) * afiles );
	}

	numfiles = 0;
	idcount = 0;

	while ((fstat = readdir(pdir)) != NULL)
	{
		struct stat statbuf;

		if(strcmp(".", fstat->d_name) == 0 || strcmp("..", fstat->d_name) == 0)
			continue;
		
		stat(fstat->d_name, &statbuf);

		// if directory then continue
		if(S_ISDIR(statbuf.st_mode))
			continue;

		if( numfiles == afiles )
		{
			afiles += 4;
			filelist = realloc(filelist, afiles * sizeof( struct foundfile ) );
		}

		strncpy(tempfilename, fstat->d_name, MAXPATHLEN );

		int i = strlen(tempfilename);	// get length of files
		
		if(strcasecmp(&tempfilename[i-4], ".dol") == 0)
		{
			filelist[numfiles].name[MAXPATHLEN-1] = 0;
			strncpy(filelist[numfiles].showname, tempfilename, 40 );
			filelist[numfiles].showname[39] = 0;
			filelist[numfiles].size = statbuf.st_size;
			filelist[numfiles].type = 0;
			filelist[numfiles].id = idcount;
			idcount++;
			numfiles++;
		}

		if(strcasecmp(&tempfilename[i-4], ".elf") == 0)
		{
			filelist[numfiles].name[MAXPATHLEN-1] = 0;
			strncpy(filelist[numfiles].showname, tempfilename, 40 );
			filelist[numfiles].showname[39] = 0;
			filelist[numfiles].size = statbuf.st_size;
			filelist[numfiles].type = 1;
			filelist[numfiles].id = idcount;
			idcount++;
			numfiles++;
		}

		if(strcasecmp(&tempfilename[i-4], ".wad") == 0)
		{
			filelist[numfiles].name[MAXPATHLEN-1] = 0;
			strncpy(filelist[numfiles].showname, tempfilename, 40 );
			filelist[numfiles].showname[39] = 0;
			filelist[numfiles].size = statbuf.st_size;
			filelist[numfiles].type = 2;
			filelist[numfiles].id = idcount;
			idcount++;
			numfiles++;
		}

		if(strcasecmp(&tempfilename[i-4], ".mp3") == 0)
		{
			filelist[numfiles].name[MAXPATHLEN-1] = 0;
			strncpy(filelist[numfiles].showname, tempfilename, 40 );
			filelist[numfiles].showname[39] = 0;
			filelist[numfiles].size = statbuf.st_size;
			filelist[numfiles].type = 3;
			filelist[numfiles].id = idcount;
			idcount++;
			numfiles++;
		}
	}
	closedir( pdir );
}
