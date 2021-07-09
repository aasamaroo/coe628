/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aasamaro
 *
 * Created on February 15, 2021, 1:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * 
 */

//How lines will be read
char* readLine(){
    
    int pos = 0;
    char *buffer = malloc(sizeof(char)*100);
    int c;
    
    while(1){
        c = getchar();
        
        //Put arguments in a String
        if(c == EOF || c == '\n'){
            buffer[pos]='\0';
            return buffer;
        }else{
            buffer[pos] = c;
        }
        pos++;
    }
}

char **splitArguments(char *line, char *deli){
    
    int size = 100;
    int index = 0;
    
    char **tokens = malloc(size*sizeof(char*));
    char *token;
    token = strtok(line, deli);
    
    while(token != NULL){
        tokens[index] = token;
        index++;
        token = strtok(NULL, deli);
    }
    tokens[index] = NULL;
    return tokens;
}



void pipingCommands(char *line){
    
    char **args1, **args2, *line1, *line2;
    line1 = malloc(sizeof(char*)*100);
    line2 = malloc(sizeof(char*)*100);
    int i = 0;
    int j = 0;
    int myPipe[2];
    
    while(line[i] != '|'){
        line1[i] = line[i];
        i++;        
    }
    
    line1[i] = (char)'\0';
    i++;
    
    while(line[i] != '\0'){
        line2[j] = line[i];
        i++;
        j++;
    }
    
    line2[j] = '\0';
    
    args1 = splitArguments(line1, " ");
    args2 = splitArguments(line2, " ");
    
    pipe(myPipe);
    
    if(fork() == 0){
        dup2(myPipe[1], STDOUT_FILENO);
        close(myPipe[0]);
        execvp(args1[0], args1);
    }else{
        dup2(myPipe[0], STDIN_FILENO);
        close(myPipe[1]);
        execvp(args2[0], args2);
    }
}


int main(int argc, char** argv) {

    char *line;
    
    while(1){
        printf("Command>");
        line = readLine();
        pipingCommands(line);
    }
    
    
    
    return (EXIT_SUCCESS);
}

