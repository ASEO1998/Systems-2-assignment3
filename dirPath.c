/*-------------------------------------------------------------------------*
 *------*
 *---dirPath.c---*
 *------*
 *---    This file defines a program that parses a path into its---*
 *---component entries.---*
 *------*
 *--------------------------------------*
 *------*
 *---Version 1.0Joseph Phillips---*
 *------*
 *-------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINE_LEN 256

struct DirEntryName
{
  char* name_;
  struct DirEntryName* nextPtr_;
};


struct PathName
{
  int isRoot_;
  int isMyHome_;
  int isSomeonesHome_;
  struct DirEntryName* dirEntryNamePtr_;
};


//  PURPOSE:  To return a non-zero value if 'c' is legal in a restricted Unix
//directory entry name, or '0' otherwise.
int isLegalDirEntryChar
(char c
 )
{
  return( isalnum(c) || (c == '-') || (c == '_') || (c == '.') );
}


//  PURPOSE:  To return 'argv[1]' if there is at least one argument on the
//command line according to 'argc'.  Otherwise:
//(1) asks the user for a path,
//(2) enters it into 'textSpace' of length 'textSpaceLen',
//(3) removes the ending '\n' from 'textSpace',
//(4) and returns 'textSpace'.
const char* getPathText(int argc,
		       char*argv[],
		       char* textSpace,
		       int textSpaceLen
		       )
{
  
  textSpace[textSpaceLen];
  if(argc >= 1){
    return (argv[1]);
    //printf("Please type in a path name: ");
    //scanf("%s",textSpace);
    //char * cPtr = strchr(textSpace, '\n');
    //if(cPtr != NULL)
      //*cPtr = '\0';
    //return(textSpace);
    
   }

    else{
      printf("Please type in a path name: ");
      scanf("%s",textSpace);
      char * cPtr = strchr(textSpace, '\n');
      if(cPtr != NULL)
      *cPtr = '\0';
      return(textSpace);
   
    }
  //  YOUR CODE HERE
}


//  PURPOSE:  To create and return a linked list of heap-allocated
//struct DirEntryName instances that represent the path 'linePtr'.
//(1) If 'linePtr' is empty (points to '\0') then returns 'NULL'.
//(2) If 'linePtr' is not empty then it
//    (a) allocates a 'struct DirEntryName' instance from the heap,
//    (b) allocates a C-string to hold the directory entry 'linePtr'
//    points to.
//    (c) allocates a new 'struct DirEntryName' for the next directory
//    entry, etc.
//
//Directory entries are separated by the '/' char.
//If the directory entry is empty (e.g. "//") then it does:
//fprintf(stderr,"Missing directory name!\n");
//exit(EXIT_FAILURE);
//If the directory entry has a character not accepted by
//'isLegalDirEntryChar()' then it does:
//fprintf(stderr,"Illegal character %c in path!\n",*linePtr);
//exit(EXIT_FAILURE);
struct DirEntryName*
parseRestOfPath(const char*  linePtr
		)
{
  //  I.  Application validity check:

  
  if  (linePtr == NULL)
    {
      fprintf(stderr,"NULL ptr to parseRestOfPath()\n");
      exit(EXIT_FAILURE);
    }


  //  II.  Return value:
  //  II.A.  Handle when at end of 'linePtr':
  //  YOUR CODE HERE

  if(*linePtr == '\0'){
    //printf("End reached\n");
    return (NULL);
  }
  
  
  
  //  II.B.  Handle when 'linePtr' points to '/',
  //     and thus a missing directory name:
  //  YOUR CODE HERE
  if(*linePtr == '/'){
    fprintf(stderr,"Missing directory name!\n");
    exit(EXIT_FAILURE);
  }
  
  
  // II.C.  Get entry name:

  const char* entryNamePtr = linePtr;
  //printf("%c\n", *entryNamePtr);
  //printf("%d\n", strlen(entryNamePtr));
  //  II.C.1.  Leave 'entryNamePtr' pointing to the beginning of the entry name,
  //       and advance 'linePtr' until the characters are no longer legal:
  //  YOUR CODE HERE
  int length = 0;
  
  while( *linePtr != '\0'){
    //printf("%s\n",linePtr);
    if(isLegalDirEntryChar(*linePtr) == 0){
      break;
    }
    length ++;
    linePtr++;
    
  }

  //  II.C.2.  If you have stopped because of anything other than '/' or '\0'
  //       then the user gave you an illegal char.  Give error message here:
  //  YOUR CODE HERE
  
    
    if(isLegalDirEntryChar(*linePtr) == 0 && *linePtr != '/' &&  *linePtr != '\0'){
      //printf("Illegal\n");
      fprintf(stderr,"Illegal character %c in path!\n",*linePtr);
      exit(EXIT_FAILURE);
    }
    


  //  II.C.3.  Allocate a new 'struct DirEntryName*' pointer here.
  //       Allocate memory for its name and copy entry name into that mem:
  //  YOUR CODE HERE
    //char* charPtr = (char*)malloc(strlen(entryNamePtr)+1);
    //char* charPtr2 = (char*)malloc(strlen(linePtr)+1);
    char* charPtr3 = (char*)calloc(length + 1,sizeof(char));
    //charPtr3 = (char*)entryNamePtr;
    for(int i = 0; i < length; i++){
      charPtr3[i] = *entryNamePtr;
      entryNamePtr++;
    }
    charPtr3[length + 1] = '\0'; 
    //printf("%s\n",charPtr3);
    
    //printf("Final copy : %s. Length is %d \n", dest,sizeof(dest));
    struct DirEntryName* word = (struct DirEntryName*) malloc(sizeof(struct DirEntryName));
    //word->name_ = (char*)malloc((linePtr - entryNamePtr)+1);
    word->name_ = (char*)malloc(strlen(charPtr3));
    word->name_ = charPtr3;

  //  II.C.4.  If 'linePtr' encountered '/' it should get the value for
  //       'nextPtr_' by recursion.  If it points to '\0' it should set
  //       'nextPtr_' to 'NULL'.
  //  YOUR CODE HERE
    
    if(*linePtr == '/' ){
      //const char* next = linePtr++;
      linePtr++;
      word->nextPtr_ = parseRestOfPath(linePtr);
      }
    else if (*linePtr == '\0'){
     word->nextPtr_ = parseRestOfPath(linePtr); 
      //word->nextPtr_ = NULL;
    }

  //  III.  Finished:
  //  RETURN YOUR 'struct DirEntryName*' POINTER HERE
  //}
  return (word);
}


//  PURPOSE:  To return the address of a heap-allocated 'struct PathName'
//instance that encodes the path given by 'linePtr'.
struct PathName*
getPath(const char* linePtr
	)
{
  //  I.  Application validity check:
  if  (linePtr == NULL)
    {
      fprintf(stderr,"NULL ptr to getPath()!\n");
      exit(EXIT_FAILURE);
    }

  //  II.  Create 'struct PathName' object:
  //  II.A.  Obtain heap memory:
  struct PathName* toReturn = (struct PathName*)
    malloc(sizeof(struct PathName));

  //  II.B.  Initialize flags of '*toReturn':
  toReturn->isRoot_ = 0;
  toReturn->isMyHome_ = 0;
  toReturn->isSomeonesHome_ = 0;

  switch  (*linePtr)
    {
    case '/' :
      toReturn->isRoot_ = 1;
      linePtr++;
      break;

    case '~' :
      linePtr++;

      if  (*linePtr == '\0')
	toReturn->isMyHome_ = 1;
      else
	if  (*linePtr == '/')
	  {
	    toReturn->isMyHome_ = 1;
	    linePtr++;
	  }
	else
	  toReturn->isSomeonesHome_ = 1;

      break;

    case '\0' :
      fprintf(stderr,"Empty path!\n");
      exit(EXIT_FAILURE);
    }

  //  II.B.  Initialize 'dirEntryNamePtr_' of '*toReturn':
  toReturn->dirEntryNamePtr_ = parseRestOfPath(linePtr);

  //  III.  Finished:
  return(toReturn);
}


//  PURPOSE:  To print out the constructed path '*pathNamePtr'.  No return
//value.
void print(struct PathName*
	  pathNamePtr
	  )
{
  //  I.  Application validity check:
  if  (pathNamePtr == NULL)
    {
      fprintf(stderr,"NULL ptr to print()!\n");
      exit(EXIT_FAILURE);
    }

  //  II.  Print path:
  //  II.A.  Print beginning of path:
  int sum = pathNamePtr->isRoot_ +
    pathNamePtr->isMyHome_ +
    pathNamePtr->isSomeonesHome_;

  if  ( (sum < 0) || (sum > 1) )
    {
      fprintf(stderr,"Inconsistent pathname!\n");
      exit(EXIT_FAILURE);
    }

  struct DirEntryName* run = pathNamePtr->dirEntryNamePtr_;

  if  (pathNamePtr->isRoot_)
    printf("Start from the root directory /\n");
  else
    if  (pathNamePtr->isMyHome_)
      printf("Start from your home directory ~\n");
    else
      if  (pathNamePtr->isSomeonesHome_)
	{
	  printf("Start from the home directory of %s\n",run->name_);
	  run  = run->nextPtr_;
	}
      else
	printf("Start from current directory\n");

  //  II.B.  Print rest of path:
  for  ( ;  run != NULL;  run = run->nextPtr_)
    printf("  %s\n",run->name_);

  //  III.  Finished:
}


//  PURPOSE:  To 'free()' the memory of 'pathNamePtr': all DirEntryName
//'name_' and 'nextPtr_' member vars, and the memory of 'pathNamePtr'
//itself.  No return value.
void destroy(struct PathName*
	    pathNamePtr
	    )
{
  //  YOUR CODE HERE
  struct  DirEntryName* freePtr = pathNamePtr->dirEntryNamePtr_;
  struct DirEntryName* tmp;
  //while (pathNamePtr != NULL){
  //free(pathN)
  //}
  while (freePtr != NULL){
    tmp = freePtr;
    
    freePtr = freePtr->nextPtr_;
    free(tmp->name_);
    free(tmp);
  }
  
  free(pathNamePtr);
}


//  PURPOSE:  To do the high level work of this program.  'argc' tells the
//number of command line arguments.  'argv[]' points to the arguments.
//Returns 'EXIT_SUCCESS' to OS on success or 'EXIT_FAILURE' otherwise.
int main(int argc,
	char*argv[]
	)
{
  char textSpace[LINE_LEN];
  const char* linePtr = getPathText(argc,argv,textSpace,LINE_LEN);
  struct PathName* pathPtr = getPath(linePtr);

  print(pathPtr);
  destroy(pathPtr);
  return(EXIT_SUCCESS);
}
