//Thomas Honnell

//ASXIILINES

//for converting tvg to ascii format


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct line
{
  char c;
  int ro;
  char tr;
  int co;
  char tc;
  char l;
  int len;
  char tl;
  char u;
};


int
main(int argc, char* argv[])
{
  FILE *fptr = NULL;


  //read file from arg
  char *filename = argv[1];
  int len=strlen(filename);
  if(len<4)
    exit(0);
  

  //success
  fptr = fopen(filename, "r");
  if(fptr == NULL){
    printf("file open fail");
    exit(0);
  }

  //get columns and rows for format
  char c;
  char r;
  r = fgetc(fptr);
  if(r == EOF)
    exit(0);
  c = fgetc(fptr);
  if(c == EOF)
    exit(0);
  //if there is a space in between this should re get the character
  if(c == ' ')
    c = fgetc(fptr);
  if(c == EOF)
    exit(0);
  //convert to int
  int col;
  int row;
  col = c - '0';
  row = r - '0';
  //col = atoi(c);
  //row = atoi(r);

  //printf("%d",row);
  //printf("%d",col);
  //printf("%c",r);
  //printf("%c",c);
  //printf("\n");

  //make the graph
  char graph[15][15];
  //not sure how to do dynamically because of double list
  //init graph with blank dots
  for(int i=0;i<row;++i){
    for(int k=0;k<col;++k){
      graph[i][k] = '.';
    }
  }


  line commands[15];
  int index=0;
  char temp;
  //this is for recording tvg line commands
  //take each command and fill line structure
  //convert to ints when needed
  while(index<15 && temp!=EOF){
    temp = fgetc(fptr);
    while((temp == ' ' || temp == '\n') && temp!=EOF)
      temp = fgetc(fptr);
    if(temp == EOF){
      printf("first character fail so still good?");
      printf("\n");
      break;
    }
    commands[index].c = temp;
    temp = fgetc(fptr);
    while(temp == ' ' && temp!=EOF)
      temp = fgetc(fptr);
    if(temp == EOF){
      printf("error eof hit unexpected2");
      exit(0);
    }
    commands[index].tr = temp;
    commands[index].ro = commands[index].tr - '0';
    if(temp == '-'){
      temp = fgetc(fptr);
      commands[index].ro = (temp -'0')*-1;
    }
    temp = fgetc(fptr);
    while(temp == ' ' && temp!=EOF)
      temp = fgetc(fptr);
    if(temp == EOF){
      printf("error eof hit unexpected3");
      exit(0);
    }
    commands[index].tc = temp;
    commands[index].co = commands[index].tc - '0';
    if(temp == '-'){
      temp = fgetc(fptr);
      commands[index].co = (temp -'0')*-1;
    }
    temp = fgetc(fptr);
    while(temp == ' ' && temp!=EOF)
      temp = fgetc(fptr);
    if(temp == EOF){
      printf("error eof hit unexpected4");
      exit(0);
    }
    commands[index].l = temp;
    temp = fgetc(fptr);
    while(temp == ' ' && temp!=EOF)
      temp = fgetc(fptr);
    if(temp == EOF){
      //printf("error eof hit unexpected5");
      //testing
    }
    commands[index].tl = temp;
    commands[index].len = commands[index].tl - '0';
    if(temp == '-'){
      printf("cannot have negative length");
      //printf("%d",index);
      //printf("%d",commands[index].len);
      //printf("%c",temp);
      //printf("\n");
      //printf("%c",commands[0].c);
      //printf("%c",commands[0].tr);
      //printf("%d",commands[0].ro);
      //printf("%c",commands[0].tc);
      //printf("%d",commands[0].co);
      //printf("%c",commands[0].l);
      //printf("%c",commands[0].tl);
      //printf("%d",commands[0].len);
      //printf("\n");
      //printf("%c",commands[1].c);
      //printf("%c",commands[1].tr);
      //printf("%d",commands[1].ro);
      //printf("%c",commands[1].tc);
      //printf("%d",commands[1].co);
      //printf("%c",commands[1].l);
      //printf("%c",commands[1].tl);
      //printf("%d",commands[1].len);
      //printf("\n");

      exit(0);
    }
    //for the command for loop purposes
    commands[index].u = 'y';
    
    

    
    ++index;
  }
  //end of getting lines so close file
  fclose(fptr);

  
  for(int i=0;i<15;++i){
    //not yes for used
    if(commands[i].u != 'y')
      break;
    //if(commands[i].ro>=0){
    if(commands[i].l == 'h'){
      for(int j=commands[i].co;j<commands[i].len && j<c;++j){
        graph[commands[i].ro][j] = commands[i].c;
      }
    }
      //not sure if this should work?
      /*
      else if(!strcmp(commands[i].l,"v")){
	for(int j=0;j<commands[i].len;++j){
          graph[j][commands[i].co] = commands[i].c
        }
      }
      */
      //else{
      //printf("error problem1");
      //exit(0);
      //}
    
      //}
      //if(commands[i].co>=0){
      /*
      if(!strcmp(commands[i].l,"h")){
        for(int j=0;j<commands[i].len;++j){
          graph[commands[i].ro][j] = commands[i].c
        }
      }
      */
      //not sure if this should work?
      
    else if(commands[i].l == 'v'){
      for(int j=commands[i].ro;j<commands[i].len && j<r;++j){
        graph[j][commands[i].co] = commands[i].c;
      }
    }
      
    else{
      printf("error problem2");
      exit(0);
    }

      //}

  }
  //end of commands

  //PRINT EVERYTHING
  for(int i=0;i<row;++i){
    for(int k=0;k<col;++k){
      printf("%c",graph[i][k]);
    }
    printf("\n");
  }


  
  exit(0);
}
