# tail_xv6
Implementation of the tail command in the xv6 kernel (coded in C)

Pull an xv6 image using Docker
I used grantbot/xv6
Run your container!

Attach this container to VSCode and you'll see the entire xv6_public directory.
In this, create files tail.c and EXAMPLE.txt

Copy the contents from my repo to these files

In xv6_public/Makefile,
There'll be a parameter called UPROGS
We have to add tail.c to it

After adding, UPROGS in makefile looks like this: 
UPROGS=\
	_cat\
	_echo\
	_forktest\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_stressfs\
	_usertests\
	_wc\
	_zombie\
	_tail\

YOU'RE ALL SET!

Test your tail command by using it as follows:
Running syntax: tail -NUM FILENAME

tail -4 EXAMPLE should give you the last 4 lines of EXAMPLE.txt
tail EXAMPLE should give you the last 10 lines of EXAMPLE.txt (default)

If no file is specified, it'll read the contents of the standard input. 

For example, if we have 
grep the EXAMPLE |tail -2

This should give you the last two lines of EXAMPLE which have the word 'the' present in them! 


