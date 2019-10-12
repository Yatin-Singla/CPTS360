#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <libgen.h>

#define MAX 10000
#define BLKSIZE 4096
FILE * fp, * gp;
char buf[4096];

typedef struct {
    char *name;
    char *value;
} ENTRY;

ENTRY entry[MAX];

void ls_file(char * fname);
void ls_dir(char * dname);

main(int argc, char *argv[]) 
{
  int i, m, n, r, j;
  char cwd[128];

  m = getinputs();    // get user inputs name=value into entry[ ]
  getcwd(cwd, 128);   // get CWD pathname

  printf("Content-type: text/html\n\n");
  printf("<p>pid=%d uid=%d cwd=%s\n", getpid(), getuid(), cwd);

  printf("<H1>Echo Your Inputs</H1>");
  printf("You submitted the following name/value pairs:<p>");
 
  for(i=0; i <= m; i++)
     printf("%s = %s<p>", entry[i].name, entry[i].value);
  printf("<p>");


  /*****************************************************************
   Write YOUR C code here to processs the command
         mkdir dirname
         rmdir dirname
         rm    filename
         cat   filename
         cp    file1 file2
         ls    [dirname] <== ls CWD if no dirname
  *****************************************************************/

// if the command is mkdir
if(!strcmp(entry[0].value, "mkdir"))
{
	// make all the directories	
	for(i = 1; i <= m; i++)
	{
		// if the directory name exists
		if(entry[i].value)
		{
			// make the directory
			r = mkdir(entry[i].value, 0755);
		}
	}
}

// if the command is rmdir
else if(!strcmp(entry[0].value, "rmdir"))
{
	// remove all the directories
	for(i = 1; i <= m; i++)
	{
		// if the directory name exists
		if(entry[i].value)
		{
			// try to remove the directory
			r = rmdir(entry[i].value);
		}
	}
}	

// if the command is rm
else if(!strcmp(entry[0].value, "rm"))
{
	// remove all the files
	for(i = 1; i <= m; i++)
	{	
		// if file name exists
		if(entry[i].value)
		{
			// rm file
			r = unlink(entry[i].value);
		}
	}
}

// if the command is cat
else if(!strcmp(entry[0].value, "cat"))
{
	// remove all the files
	for(i = 1; i <= m; i++)
	{	
		// file number 1
		if(entry[i].value)
		{
			fp = fopen(entry[i].value, "r");
			if (fp == NULL)
			{
				printf("<p><b>Cannot open the file</b></p>");
			}
			else
			{
				printf("<p>");
				while (fgets(buf, 4096, fp))
				{
					printf("%s", buf);
				}
				printf("</p>");
				fclose(fp);
			}
		}
	}
}
// if command is cp
else if(!strcmp(entry[0].value, "cp"))
{
	if (m < 2)
	{
		printf("<p><b>need src and dest</b></p>");
		exit(1);
	}
	// check if both files are different
	if(strcmp(entry[1].value, entry[2].value))
	{
		printf("<p><b>Two files are not the same</b></p>");
		fp = fopen(entry[1].value, "r");
		if (fp == NULL) exit(2);
		gp = fopen(entry[2].value, "w");
		if (gp == NULL) exit(3);
		while (n = fread(buf, 1, BLKSIZE, fp)) 
		{
			fwrite(buf, 1, n, gp);
		}
		fclose(fp);
		fclose(gp);
	}
	else
	{
		printf("<p><b>Src and Dest should be different</b></p>");
	}
}
else if(!strcmp(entry[0].value, "ls"))
{
	struct stat mystat, *sp = &mystat;
	char * filename, path[1024];
	filename = "./";
	if (m > 1) // file is specified
	{
		filename = entry[1].value;
	}
	
	strcpy(path, filename);

	if(path[0] != '/') // filename is relative
	{
		strcpy(path, cwd);
		strcat(path, "/");
		strcat(path, filename);
	}

	if((r = lstat(path, sp) < 0))
	{
		printf("<p><b>No such file</b></p>");
	}	

	if(S_ISDIR(sp->st_mode))
	{
		ls_dir(path);
	}
	else
	{
		ls_file(path);
	}
}

  // create a FORM webpage for user to submit again 
  printf("</title>");
  printf("</head>");
  printf("<body bgcolor=\"#FF0000\" link=\"#330033\" leftmargin=8 topmargin=8");
  printf("<p>------------------ DO IT AGAIN ----------------\n");
  
  printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~singla/cgi-bin/mycgi.bin\">");

  //------ NOTE : CHANGE ACTION to YOUR login name ----------------------------
  //printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~YOURNAME/cgi-bin/mycgi.bin\">");
  
  printf("Enter command : <INPUT NAME=\"command\"> <P>");
  printf("Enter filename1: <INPUT NAME=\"filename1\"> <P>");
  printf("Enter filename2: <INPUT NAME=\"filename2\"> <P>");
  printf("Submit command: <INPUT TYPE=\"submit\" VALUE=\"Click to Submit\"><P>");
  printf("</form>");
  printf("------------------------------------------------<p>");

  printf("</body>");
  printf("</html>");
}

void ls_file(char * fname)
{
	char * t1 = "xwrxwrxwr-------";
	char * t2 = "----------------";
	struct stat fstat, *sp;
	int r, i;
	char ftime[64];
	sp = &fstat;
	
	if((r = lstat(fname, &fstat)) < 0)
	{
		printf("<p><b>Can't stat %s</b></p>", fname);
	}
	printf("<p><b>");
	if ((sp->st_mode & 0xF000) == 0x8000) // if (S_ISREG())
		printf("%c",'-');	
	else if ((sp->st_mode & 0xF000) == 0x4000) // if (S_ISDIR())
		printf("%c",'d');

	for(i = 8; i >= 0; i--)
	{
		if (sp->st_mode & (1 << i)) //print r|w|x
			printf("%c",t1[i]);
		else
			printf("%c", t2[i]); // or print -
	}

	printf("%4d ", sp->st_nlink); // link count
	printf("%4d ", sp->st_gid); // gid
	printf("%4d ", sp->st_uid); // uid
	printf("%8d ", sp->st_size); // size
	// print time
	strcpy(ftime, ctime(&sp->st_ctime)); //print time in calendar form
	ftime[strlen(ftime)-1] = 0; // kill \n at end
	printf("%s ", ftime);
	// print name
	printf("%s", basename(fname)); //print file basename
	printf("</p></b>");
}

void ls_dir(char * dname)
{
	struct dirent * ep;
	char path[1024];
	DIR *dp = opendir(dname);
	while (ep = readdir(dp))
	{
		bzero(path, 1024);
		strcat(path, "./");
		strcat(path, ep->d_name);
		ls_file(path);
	}
}
