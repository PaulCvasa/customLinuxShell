# customLinuxShell_v2

Run using: g++ -o projectPaulCvasa.exe projectPaulCvasa.cpp -lreadline
Then: ./projectPaulCvasa.exe

REQUIREMENTS (that I had to do)
------------
The following commands must be implemented, along with their parameters (see man help pages for information on each):

1. The "nl" command. Parameters that need to be implemented are: -s, -d

2. The "head" command. Parameters that need to be implemented are: -c, -n, -q, -v

3. The "chroot" command. No parameters need to be implemented.

4. Your program must also support pipes in the commands, e.g. > ls -l | grep -e 'tmp' | wc -l (it must work with any type of command!)

5. Your program must also support redirection in the commands, e.g. > ls -l > out.txt (it must work with any type of command!)

6. Your program must support both pipes and redirection in the same command line, e.g. > ls -l | grep -e 'tmp' > out.txt (it must work with any type of command!)
