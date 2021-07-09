/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aasamaro
 *
 * Created on February 1, 2021, 7:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>


/*
 * 
 */
int main(int argc, char** argv) {

    //List of local variables
    char command[100];
    char exeCmd[100];
    int index = 0;
    bool ampFlag;
    
    char *argPtr[100];
    int argPtrNum = 0;
    int argPtrIndex = 0;
    
    printf("Your command> \n");
    argPtr[argPtrIndex] = &command[0];
    argPtrNum++;
    
    while((command[index] = getchar()) != '\n'){
        
        
        //Check if empty space
        
        if(command[index] == ' '){
            
            //make it NULL
            command[index] = NULL;
            
            //Set next char as pointer address
            argPtrNum++;
            argPtrIndex++;
            argPtr[argPtrIndex] = &command[index + 1];
        }
        
        index++;
    }
    
    //Check to see if ampersand
    
    if(command[index - 1] == '&' && command[index - 2] != ' '){
        ampFlag = true;
    }
    
    //Create new process
    pid_t cpid;
    
    if(fork() == 0){
        printf("A Child Process has been created.\n");
        
        //Execute commands
        index = 0;
        argPtrIndex = 0;
        
        for(argPtrIndex = 0; argPtrIndex < argPtrNum; argPtrIndex++){
            index = 0;
            
            while(*argPtr[argPtrIndex] != NULL){
                exeCmd[index] = *argPtr[argPtrIndex];
                argPtr[argPtrIndex] = argPtr[argPtrIndex + 1];
                
                printf("%c\n", exeCmd[index]);
                index++;
            }
            exeCmd[index] = NULL;
            system(exeCmd);
        }
        
        printf("%s\n", exeCmd);
        printf("%d\n", argPtrNum);
        exit(0);
    } else {
        printf("Parent process is currently waiting.\n");
        
        //Now we wait for child process to terminate
        if(ampFlag == false){
            cpid = wait(NULL);
        }
        
        printf("Parent Process has ended.\n");
    }
    
    return (EXIT_SUCCESS);
}

