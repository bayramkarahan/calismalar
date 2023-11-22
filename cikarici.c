#include <sys/types.h>

#include <sys/stat.h>

#include <archive.h>
#include <archive_entry.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<iostream>
using namespace std;


void list_archive(const char * name) {
    struct archive *a;
    struct archive_entry *entry;

    // create new archive struct for the file
    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    // open 7z file
    int r = archive_read_open_filename(a, name, 1024);

    if (r != ARCHIVE_OK) {
        cout << "cannot read file: " << name << endl;
        cout << "read error: " << archive_error_string(a) << endl;
    }

    // looping through entries
    for (;;) {
        int status = archive_read_next_header(a, &entry);

        // if there's no more header
        if (status != ARCHIVE_OK) break;

        // print some status messages to stdout
        string pathname(archive_entry_pathname(entry));
        cout << "working on: " << pathname << endl;

        size_t entry_size = archive_entry_size(entry);

        // load the entry's content
        char * content;
        content = (char*)malloc(entry_size);
        r = archive_read_data(a, content, entry_size);

        // check if archive_read_data was successful
        if (r > 0) {
            cout << "read " << r << " of " << entry_size <<content <<" bytes successfully\n";
            
            // we are interested in .fog file only
            if (pathname.back() == 'g') {
                // do something with the .fog file
            }
        }
        else // usually the error happens here
            if (archive_errno(a) != ARCHIVE_OK) cout << "read error: " << archive_error_string(a) << endl;


        // free the content and clear the entry
        archive_read_data_skip(a);
        free(content);
        archive_entry_clear(entry);

        cout << "-----" << endl;
    }

    // we are done with the current archive, free it
    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        cout << "Failed to free archive object. Error: " << archive_error_string(a) << endl;
        exit(1);
    }
}

/*
static int
copy_data(struct archive *ar, struct archive *aw)
{
printf("selam moruk\n");
  int r;
  const void *buff;
  size_t size;
  off_t offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_OK)
      return (ARCHIVE_OK);
    if (r < ARCHIVE_OK)
      return (r);
    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(aw));
      return (r);
    }
  }
}
*/
static int copy_data(struct archive *ar, struct archive *aw)
{
  int r;
  const void *buff;
  size_t size;
  la_int64_t offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF)
      return (ARCHIVE_OK);
    if (r < ARCHIVE_OK)
      return (r);
    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(aw));
      return (r);
    }
  }
}
/*
static int
extract(const char *filename,const char *destfolder)
{
  struct archive *a;
  struct archive *ext;
  struct archive_entry *entry;
  int flags;
  int r;
char* dest_file;
  /* select which attributes we want to restore. */
/*  flags = ARCHIVE_EXTRACT_TIME;
  flags |= ARCHIVE_EXTRACT_PERM;
  flags |= ARCHIVE_EXTRACT_ACL;
  flags |= ARCHIVE_EXTRACT_FFLAGS;

  a = archive_read_new();
  archive_read_support_format_all(a);
  ext = archive_write_disk_new();
  archive_write_disk_set_options(ext, flags);
  archive_write_disk_set_standard_lookup(ext);
  if ((r = archive_read_open_filename(a, filename, 102400)))
    return 1;
  for (;;) {

    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF)
      break;
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
      return 1;
      std::string destination="/tmp/";
      
    //  asprintf(&dest_file, "%s/%s", destfolder, archive_entry_pathname(entry));
    //archive_entry_set_pathname(entry, dest_file);
   
          
 
      r = archive_write_header(ext, entry);
   
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    else if (archive_entry_size(entry) > 0) {
     // r = copy_data(a, ext);
      if (r < ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(ext));
      if (r < ARCHIVE_WARN)
        return 1;
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    if (r < ARCHIVE_WARN)
      return 1;
  }
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);
  return 0;
}
*/
static void extract(const char *filename,const char *destfolder)
{
  struct archive *a;
  struct archive *ext;
  struct archive_entry *entry;
  int flags;
  int r;
char* dest_file;
  /* Select which attributes we want to restore. */
  flags = ARCHIVE_EXTRACT_TIME;
  flags |= ARCHIVE_EXTRACT_PERM;
  flags |= ARCHIVE_EXTRACT_ACL;
  flags |= ARCHIVE_EXTRACT_FFLAGS;

  a = archive_read_new();
  archive_read_support_format_all(a);
  archive_read_support_compression_all(a);
  ext = archive_write_disk_new();
  archive_write_disk_set_options(ext, flags);
  archive_write_disk_set_standard_lookup(ext);
  if ((r = archive_read_open_filename(a, filename, 10240))){
    exit(1);
  }
  for (;;) {
     // qDebug()<<"for;;";
   
    r = archive_read_next_header(a, &entry);
        asprintf(&dest_file, "%s/%s", destfolder, archive_entry_pathname(entry));
    archive_entry_set_pathname(entry, dest_file);
  
    if (r == ARCHIVE_EOF)
      break;
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN){
      exit(1);
    }
    r = archive_write_header(ext, entry);

    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    else if (archive_entry_size(entry) > 0) {
      r = copy_data(a, ext);
      if (r < ARCHIVE_OK){
        fprintf(stderr, "%s\n", archive_error_string(ext));
      }
      if (r < ARCHIVE_WARN){
        exit(1);                              //A1: Program exits here.
      }
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    if (r < ARCHIVE_WARN){
      exit(1);
    }
  }
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);
  exit(0);
}
int main ( int argc, const char **argv )
{
/*printf(argv[1]);
printf("\n");
printf(argv[2]);
*/
//list_archive(argv[1]);
//return 
  extract (argv[1],argv[2]);;
return 0;
}
