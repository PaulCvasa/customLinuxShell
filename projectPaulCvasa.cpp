#include <iostream>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fstream>
#include <fcntl.h>

using namespace std;

int searchPipes(string command, vector<string> pipedCommands[])
{
    stringstream ss(command);
    string comm;
    int p=-1;
    while(getline(ss, comm, '|'))
    {
        pipedCommands->push_back(comm.c_str());
        p++;
    }
    return p;
}

void nl(string command)
{
    string argument;
    string command_plus_arguments[15];
    istringstream ss(command);
    int k=0;
    while(ss>>argument)
    {
        command_plus_arguments[k] = argument;
        k++;
    }
    if(k==2)
    {
        ifstream input(command_plus_arguments[1]);
        int l=1;
        while(getline(input, argument))
        {
            cout<<"    "<<l<<"  "<<argument<<"\n";
            l++;
        }
        input.close();
        return;
    }
    if(command_plus_arguments[1].find("-s")!=string::npos)
    {
        int l=1;
        for(int i=3;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            command_plus_arguments[2].erase(remove(command_plus_arguments[2].begin(), command_plus_arguments[2].end(), '\"'), command_plus_arguments[2].end());
            while(getline(input, argument))
            {
                cout<<"    "<<l<<command_plus_arguments[2]<<argument<<"\n";
                l++;
            }
            input.close();
        }
        return;
    }
    if(command_plus_arguments[1].find("-d")!=string::npos)
    {
        int l=1,ok=1;
        for(int i=3;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            while(getline(input, argument))
            {
                if(command_plus_arguments[2].find(argument)!=string::npos)
                {
                    ok=0;
                    cout<<"\n";
                    continue;
                }
                if(ok)
                    cout<<"     "<<l<<" "<<argument<<"\n";
                else
                    cout<<"       "<<argument<<"\n";
               l++;
            }
            input.close();
        }
        return;
    }
    if(k>2)
    {
        int l=1;
        for(int i=1;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            while(getline(input, argument))
            {
                cout<<"    "<<l<<"  "<<argument<<"\n";
                l++;
            }
            input.close();
        }
        return;
    }
}

void head(string command)
{
    string argument;
    string command_plus_arguments[15];
    istringstream ss(command);
    int k=0;
    while(ss>>argument)
    {
        command_plus_arguments[k] = argument;
        k++;
    }

    if(k==2)
    {
        ifstream input(command_plus_arguments[1]);
        int l=1;
        while(getline(input, argument) && l<=10)
        {
            cout<<argument<<"\n";
            l++;
        }
        input.close();
        return;
    }
    if(command_plus_arguments[1].find("-c")!=string::npos)
    {
        for(int i=3;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            char c;
            int bytes, count=0;
            stringstream toInt(command_plus_arguments[2]);
            toInt>>bytes;
            if(k>4)
            {
                cout<<"==> "<<command_plus_arguments[i]<<" <==\n";
            }
            while(input.get(c) && bytes!=count)
            {
                cout<<c;
                count++;
            }
            cout<<"\n";
            input.close();
        }
        return;
    }
    if(command_plus_arguments[1].find("-n")!=string::npos)
    {
        for(int i=3;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            int l=1, n=0;
            stringstream toInt(command_plus_arguments[2]);
            toInt>>n;
            if(k>4)
                cout<<"==> "<<command_plus_arguments[i]<<" <==\n";
            if(n>=0)
            {
                while(getline(input, argument) && l<=n)
                {
                    cout<<argument<<"\n";
                    l++;
                }
            }
            if(n<0)
            {
                n = abs(n);
                vector<string> lines;
                while(getline(input, argument))
                {
                    lines.push_back(argument);
                }
                for(int i=0;i<lines.size()-n;i++)
                    cout<<lines[i]<<"\n";
            }
            input.close();
        }
        return;
    }
    if(k>2 && (command_plus_arguments[1].find("-q")!=string::npos))
    {
        for(int i=2;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            int l=1;
            while(getline(input, argument) && l<=10)
            {
                cout<<argument<<"\n";
                l++;
            }
            input.close();
        }
        return;
    }
    if(command_plus_arguments[1].find("-v")!=string::npos)
    {
        for(int i=2;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            int l=1;
            cout<<"==> "<<command_plus_arguments[i]<<" <==\n";
            while(getline(input, argument) && l<=10)
            {
                cout<<argument<<"\n";
                l++;
            }
            cout<<"\n";
            input.close();
        }
        return;
    }
    if(k>2)
    {
        for(int i=1;i<k;i++)
        {
            ifstream input(command_plus_arguments[i]);
            int l=1;
            cout<<"==> "<<command_plus_arguments[i]<<" <==\n";
            while(getline(input, argument) && l<=10)
            {
                cout<<argument<<"\n";
                l++;
            }
            cout<<"\n";
            input.close();
        }
        return;
    }
}
void ch_root(string command)
{
    string argument;
    string command_plus_arguments[15];
    istringstream ss(command);
    int k=0;
    while(ss>>argument)
    {
        command_plus_arguments[k] = argument;
        k++;
    }

    chdir(command_plus_arguments[1].c_str());
    if(chroot(command_plus_arguments[1].c_str()))
    {
        perror("chroot");
        return;
    }
}
int customCommands(string command)
{
    if(!command.compare("exit"))
        return 0;
    else if(command.find("nl")!=string::npos)
    {
        nl(command);
        return 1;
    }
    else if(command.find("head")!=string::npos)
    {
        head(command);
        return 1;
    }
    else if(command.find("chroot")!=string::npos)
    {
        ch_root(command);
        return 1;
    }
    return -1;
}

void runExecvp(char* c_args[])
{
    if(fork() ==0)
    {
        if(execvp(c_args[0], c_args)<0)
            cout<<"Error: Incorrect command.";
        exit(0);
    }
    else
    {
        wait(0);
    }
}

void runCommands_notImplemented(string command)
{
    string argument;
    string command_plus_arguments[15];
    istringstream ss(command);
    int k=0;
    while(ss>>argument)
    {
        command_plus_arguments[k] = argument;
        k++;
    }
    char* c_args[k];
    for(int i=0;i<k;i++)
        c_args[i] = const_cast<char*>(command_plus_arguments[i].c_str());
    c_args[k] = NULL;
    
    runExecvp(c_args);
}

void redirect(string output, string command)
{
    int defaultSTDOUT = dup(STDOUT_FILENO);
    int file = open(output.c_str(), O_CREAT | O_WRONLY);
    dup2(file, STDOUT_FILENO);
    if(customCommands(command)==-1)
        runCommands_notImplemented(command);
    dup2(defaultSTDOUT, STDOUT_FILENO);
    close(defaultSTDOUT);
}

int searchRedirect(string &command, string &output)
{
    stringstream ss(command);
    int r=-1;
    while(getline(ss, output, '>'))
    {
        if(r==0)
        {
            command=command.substr(0, command.find(">", 0));
            redirect(output, command);
            cout<<"\nOUTPUT: "<<output;
        }
        //cout<<"\nEdited command: "<<command;
        r++;
    }
    return r;
}

int main()
{
    int run=1;
    string command;
    string output;
    
    while(run)
    {
        cout<<"\n"<<get_current_dir_name()<< "$ ";
        command = readline("");
        add_history(command.c_str());
        vector<string> pipedCommands[15];
        if(searchPipes(command, pipedCommands))
        {
            for(int i=0; i<pipedCommands->size(); i++)
            {
                if(searchRedirect(pipedCommands->at(i), output))
                {
                    cout<<"\nRedirect found !";
                }
                else
                {
                    run = customCommands(pipedCommands->at(i));
                    if(run == -1)
                    {
                        //cout<<"\nThis was not an implemented command, so it will be ran using Linux's implementation.. \n";
                        runCommands_notImplemented(pipedCommands->at(i));
                    }
                }
                
            }
        }
        else
        {
            if(searchRedirect(command, output))
            {
                cout<<"\n redirect found!";
            }
            else
            {
                run = customCommands(command);
                if(run == -1)
                {
                    //cout<<"\nThis was not an implemented command, so it will be ran using Linux's implementation.. \n";
                    runCommands_notImplemented(command);
                }
            }
            
        }
        
    }
    return 0;
}