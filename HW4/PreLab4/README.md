
                  CS360 LAB #4 PRE-WORK

================= PART 1: CGI PROGRAMMING: ==============================

1. YOUR WEBSITE at cs360.eecs.wsu.edu
   Each of you has a user account on the Linux machine cs360.eecs.wsu.edu
        login name = YOUR last name     (lower case only)
        password   = YOUR WSU ID number (no leading 0)

2. Access YOUR website by

        http://cs360.eecs.wsu.edu/~YOURNAME
       
        ------------------------------------
        |    Welcome to YOUR Website       |
        |       ------------------         |
        |       | YOUR PICTURE   |         |
        |       ------------------         |
        | Input command  :  BOX            | 
        | Input filename1:  BOX            |
        | Input filename2:  BOX            | 
        | Submit command :  Submit BOX     |
        ------------------------------------

3. You will NOT like your current picture. 
   REQUIRED WORK: login to your account by
                  ssh YOURNAME@cs360.eecs.wsu.edu
                  Change it to YOUR pretty picture.
NOTE: in order for us to know you better, please use a REAL picture of you.

4. When you click the Submit BOX, it submits the strings you entered to the
   httpd (Apache) server on the cs360.eecs.wsu.edu machine, directing it to 
   execute
             ~kcw/cgi-bin/mycgi.bin 
 
  which echos YOUR inputs and shows another input-submit window again.

5. login to your account. As of now, YOUR home directory contains:
 
        public_html --- index.html 
               |
            cgi-bin ---- mycgi.c util.o

5-1. Modify YOUR public_html/index.html file: CHANGE the line

< FORM METHOD="POST" ACTION="http://cs360.eecs.wsu.edu/~kcw/cgi-bin/mycgi.bin" >

TO

< FORM METHOD="POST" ACTION="http://cs360.eecs.wsu.edu/~YOURNAME/cgi-bin/mycgi.bin" >

5-2. Go to YOUR cgi-bin/ directory. Change the line in mycgi.c file

 printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~kcw/cgi-bin/mycgi.bin\">"); 

TO

 printf("<FORM METHOD=\"POST\" ACTION=\"http://cs360.eecs.wsu.edu/~YOURNAME/cgi-bin/mycgi.bin\">");

Then run
     cc -o mycgi.bin mycgi.c util.o   # generate YOUR OWN mycgi executable.
     chmod u+s mycgi.bin              # chmod mycgi to a SETUID executable

6. Access YOUR webpage again. Enter command and filenames. Then, Submit.
   It should execute YOUR mycgi program in YOUR cgi-bin/ directory.


======================= REQUIREMENTS ===============================


MODIFY mycgi.c to do the following commands:
                          # int r;
     mkdir dirname        # r = mkdir(dirname, 0755);
     rmdir dirname        # r = rmdir(dirname);
     rm    filename       # r = unlink(dilename);
     cat   filename       # cat program in Eaxmple 9.1
     cp    file1 file2    # cp program  in Example 9.2
     ls    [directory]    # ls program  in Example 8.6.7

NOTE: YOUR mycgi.bin program is executed by an Apache process (uid=80). 
In order for the Apache process to write to YOUR directories, you MUST change 
YOUR mycgi.bin to a setuid program by
                    chmod u+s mycgi
When a process executes a setuid program, it temporarily assumes the uid of the
program owner, allowing it to write to the owner's directories.


====================== PART 2  ==================================

1. Download the server.c and client.c files from ~samples/LAB4.
   cc and run the programs. Modify the programs to do the following:

          client: sends 2 numbers to server, 
          server: returns the SUM of the 2 numbers.


HAVE FUN !!