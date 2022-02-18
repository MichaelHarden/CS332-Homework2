//
//  homework2.c
//  hw2
//
//  Created by Michael Harden on 2/13/22.
//
//  Demoed Code at lab on 2/18/22
//  I am an Undergrad but still included the -t flag
//

#include "homework2.h"

// run_flags stores all the flags so that they can be referenced during recersive calls
struct run_flags {
    bool flag_S;
    size_t flag_s;
    char* flag_f;
    char flag_t;
};


int main (int argc, char* const argv[]) {
    DIR* parentDir; //initial directory to start
     
    // verify a directory is given
    if (argc < 1) {
        printf ("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }
    // sets flags to default value if they are not provided
    struct run_flags params;
    params.flag_S = false;
    params.flag_s = -1;
    params.flag_f = NULL;
    params.flag_t = 0;

    // puts the flags into the structs
    int option;
    while((option = getopt(argc, argv, "Ss:f:t:")) != -1) {
        switch (option) {
            case 'S':
                params.flag_S = true;
                break;
            case 's':
                params.flag_s = atoi(optarg);
                break;
            case 'f':
                params.flag_f = optarg;
                break;
            case 't':
                params.flag_t = optarg[0];
                break;
            default:
                printf("Error");
                exit(-1);
                
        }
    }
    
    // checks if a path is give. If no path is given then the path is set to the current path
    char* path = ".";
    if (optind < argc) {
        path = argv[argc-1];
    }
    
    // starting directory
    parentDir = opendir(path);
    
    // makes sure that the directory was opened.
    if (parentDir == NULL) {
        printf ("Error opening directory '%s'\n", path);
        exit (-1);
    }
    // calling recurisive function using a function pointer
    void (*ptr_print_dir)(DIR* directory, char* current_path, unsigned short tabs, struct run_flags* params) = print_dir;
    ptr_print_dir(parentDir, path, 0, &params);
    
    closedir (parentDir);
    return 0;
}

/*
 print_dir is a recursive function. It begins by printing everything inside the
 directory provided. Then if a certain item is another directory print_dir is
 called again with that child directory passing into print_dir.
 
 print_dir also checks the flags and verifies that they are provided. If they
 are, then only prints what is allowed via the flags.
 
 parameters:
    directory: the current directory to search
    current_path: the path taken from the starting directory to the current
                    directory inorder to call the next directory
    tabs: the number of \t to insert into the print statement for prettifying
            the output
    params: the struct which holds the flag values.
    dirent: the current dirent to operate on
 */
void print_dir(DIR* directory, char* current_path, unsigned short tabs, struct run_flags* params) {
    struct dirent *dirent;
    
    // loops throught every element contained in dirent
    while((dirent = readdir(directory)) != NULL){
        
        // saves the dirent name
        char* dir_name = dirent->d_name;
        
        // builds the path for recursive reference
        char* path = malloc((strlen(current_path) + strlen(dir_name) + 2) * sizeof(char));
        strcpy(path, current_path);
        strcat(path, "/");
        strcat(path, dir_name);
        
        // stores what is going to need to be printed for the file.
        char* output = (char*)malloc(10*sizeof(char));
        strcpy(output, dir_name);
        
        // check if dirent is a directory.
        if (dirent->d_type == DT_DIR) {
            // if the if flag is not provided it should print it also should
            // print if the f flag is provided but the directory name has contains
            // the substring. This would be two if statements. So, instead i check
            // if not the inverse of these two situations. This allows for only one
            // if statement of the f flag
            
            if (!((params->flag_f) && !(strstr(dir_name, params->flag_f)))) {
                // checks if the t flag is provided. If it is not provided or if
                // it is d then print the directory
                if ((params->flag_t == 'd') || (params->flag_t == 0)) {
                    int i;
                    for(i=0; i < tabs; i++) { printf("\t"); }
                    printf("%s\n", output);
                }
            }
            
            // if dirent is a directory verify that it is not . or ..
            // on those cases do not call print_dir
            if ((strcmp(dir_name, ".") != 0) && (strcmp(dir_name, "..") != 0)) {
                // creates the path from the parent directory to the current directory
                
                DIR* next_dir = opendir(path);
                // verify the next directory is not a null pointer
                if (next_dir != NULL) {
                    //recursively call the next directory
                    print_dir(next_dir, path, tabs+1, params);
                }
            }
        // if dirent is of type file and t flag is not provided
        // or if t flag is set to f then do the following.
        } else if ((params->flag_t == 'f') || (params->flag_t == 0)) {
            
            //function pointer for getting size of a file
            long long (*ptr_fileSize)(const char *filename) = fileSize;
            long long file_size = ptr_fileSize(path);
            
            // check for s flag
            if ((params->flag_s != -1) && (params->flag_s > file_size)) {
                continue;
            }
            // check for S flag if it is provided the add the size to the output
            if (params->flag_S) {
                char* buff = (char*)malloc(sizeof(char)*124);
                sprintf(buff, " %lld", file_size); //ISSUES ON THIS LINE
                strcat(output, buff);
                free(buff);
            }
            // if the f flag is provided and is not a substring then continue
            if ((params->flag_f) && !(strstr(dir_name, params->flag_f))) {
                continue;
            }
            
            int i;
            for(i=0; i < tabs; i++) { printf("\t"); }
            printf("%s\n", output);
        }
        free(output);
    }
}

/*
 returns the file size of a file
 
 file name must be a path to that file from the current directory.
 */
long long fileSize(const char *filename) {
    struct stat sb;

    if (stat(filename, &sb) == 0) {
        return sb.st_size;
    }

    return -1;
}
