#ifndef VFS_RAM_H
#define VFS_RAM_H

#define MAX_RAMFILES 20
#define PATH_SIZE 14

extern struct vfs_ops ramfs_vfs_ops;

void raminit();
struct ramDrive drive;

struct vfile* ramfs_create(char *, short, short, short);
void ramfs_stati(struct vfile *, struct stat *st);
void ramfs_ilock(struct vfile*);
void ramfs_iunlock(struct vfile*);
void ramfs_iput(struct vfile*);
int ramfs_writei(struct vfile*, char *src, uint off, uint n);
int ramfs_readi(struct vfile*, char *src, uint off, uint n);

struct ram {
  int alloc;
  char fName[PATH_SIZE];
  char* data;
};


struct ramDrive {
  struct spinlock *lock;
  struct ram ramFiles[MAX_RAMFILES];
};

#endif