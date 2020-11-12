#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>


int moveFile(const char* srcPath, const char* destPath){
    return !rename(srcPath, destPath);
}

int main (int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm local;
    localtime_r(&t, &local);
    
    char *dirname;
    DIR *dirp;
    struct dirent *p;
    struct stat    s;
    int retval;
    int counter = 0;
    char mkd = "./out";
    char new[20] = "img000.dng";
    char *dirent ="dirent.h";
    char *exe = "RenameTool.exe";
    char *c = "test.c";
    char *tool = "RenameTool.c";
    char *bc = "RenameTool.c.bc";
    char *check;
    char file[20] = "img000.dng";
    char fileNew[20] = "./out/img000.dng";
    char directry[20] = "./out/";
    char newdirectry[20] = "../out/";
    char time[20] = "t";
    
    sprintf(time, "%04d", local.tm_sec);
    sprintf(new,"img000_%s.dng", time);
    sprintf(file, "img000_%s.dng", time);
    sprintf(fileNew, "./out/img000_%s.dng", time);
    
    if (argc != 2) {
        dirname = ".";
    } else {
        dirname = argv[1];
    }

    if ((dirp = opendir(dirname)) == NULL) {
        fprintf(stderr, "Can't open directory %s\n", dirname);
        return -1;
    }
    
	mkdir("out", S_IRWXU | S_IRWXG | S_IRWXO);
    
    while ((p = readdir(dirp)) != NULL) {
        retval = stat(p->d_name, &s);
        if (retval != 0) {
            fprintf(stderr, "Can't stat %s\n", p->d_name);
            return -1;
        }
    
        check = p->d_name;  
        
        if (strcmp(check, dirent)!= 0 & strcmp(check, exe)!= 0 & strcmp(check, c)!= 0 & strcmp(check, tool)!=0 & strcmp(check, bc)!=0 ){
            if ((s.st_mode & S_IFMT) == S_IFREG) {
                printf("Filename %10s Size %10ld\n", p->d_name, s.st_size);

            	if ( rename(p->d_name, new) == 0 ) {
                	printf("%s has renamed to %s\n", p->d_name, new);
                	counter = counter + 1;
                	printf("%d\n",counter);
                	printf("%s\n",new);
                	
                	strcpy(file,new);
                	printf("%s\n",file);
                	sprintf(fileNew,"./out/%s",new);
                	printf("move to %s\n",fileNew);
                	
            	if (moveFile( new, fileNew)) {
        			sprintf(new, "img%03d_%s.dng", counter, time);
        			puts("Moved\n");
    			}else{
        			puts("Faild to move\n");
    			}
                  
                
                } else {
                fprintf(stderr, "faild to rename %s\n", p->d_name);
                }

            }
        }
    }

    if (closedir(dirp) != 0) {
        fprintf(stderr, "Can't close directory %s\n", dirname);
        return -1;
    }

    printf("\n");
    
    if( rename( directry, newdirectry ) == 0 ){
    	printf( "%s has moved to %s\n", directry, newdirectry );
  	}else{
    	printf( "faild to move the directry\n" );
  	}
       
    printf("end");
    return 0;
}

