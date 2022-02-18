//
//  homework2.h
//  hw2
//
//  Created by Michael Harden on 2/13/22.
//

#ifndef homework2_h
#define homework2_h

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/stat.h>

struct run_flags;
// Function Decleration
void print_dir(DIR* directory, char* current_path, unsigned short tabs, struct run_flags* params);
long long fileSize(const char *filename);

#endif /* homework2_h */
