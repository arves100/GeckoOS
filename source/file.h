#ifndef _FILE_H_
#define _FILE_H_
#include <gccore.h>

// powerpc-none-eabi-gcc reported this through warnings. There is an extra one for the null terminatior.
#define MAXPATHLEN 768

//---------------------------------------------------------------------------------
struct foundfile
{
	char name[MAXPATHLEN];
	char showname[40];
	int size;
	int type;	// 0 dol, 1 elf, 2 wad
	int id;
};
//---------------------------------------------------------------------------------
void menu_scandir();
void file_execute(struct foundfile *list, int top, int sel);
//---------------------------------------------------------------------------------
extern int numfiles;
extern int afiles;
extern u32 filetop;
extern struct foundfile *filelist;
//---------------------------------------------------------------------------------

#endif
