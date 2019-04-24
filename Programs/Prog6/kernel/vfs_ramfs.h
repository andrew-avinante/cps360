#ifndef VFS_RAM_H
#define VFS_RAM_H

#define MAX_RAMFILES 20
#define PATH_SIZE 14
#define MEMORY_SIZE 64

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


struct dataBlock {
  char* data;
  int alloc;
};

struct ram {
  int alloc;
  char fName[PATH_SIZE];
  struct dataBlock dataBlocks[MEMORY_SIZE % 4];
};


struct ramDrive {
  struct spinlock *lock;
  struct ram ramFiles[MAX_RAMFILES];
};


#endif


// #include "types.h"
// #include "defs.h"
// #include "spinlock.h"
// #include "fs.h"
// #include "vfs.h"
// #include "file.h"
// #include "stat.h"
// #include "vfs_ramfs.h"

// struct vfs_ops ramfs_vfs_ops = {
//   .stati = ramfs_stati,
//   .ilock = ramfs_ilock,
//   .iunlock = ramfs_iunlock,
//   .iput = ramfs_iput,
//   .writei = ramfs_writei,
//   .readi = ramfs_readi
// };

// void raminit(void)
// {
//   initlock(drive.lock, "ram");
// }

// struct vfile* ramfs_create(char *path, short type, short major, short minor)
// {
//   for(int i = 0; i < MAX_RAMFILES; i++)
//   {
//     if(drive.ramFiles[i].alloc == 0)
//     {
//       memmove(drive.ramFiles[i].fName, path, 14);
//       drive.ramFiles[i].alloc = 1;
//       drive.ramFiles[i].data[0] = kalloc();
//       memset(drive.ramFiles[i].data[0], 0, 4096);
//       memset(drive.ramFiles[i].data[0], 1, 1);
//       struct vfile *vf = vfile_alloc(&drive.ramFiles[i], &ramfs_vfs_ops);
//       vf->type = 2;
//       return vf;
//     }
//   }
//   return vfile_alloc(NULL, &ramfs_vfs_ops);
// }

// void ramfs_stati(struct vfile *vfile, struct stat *st)
// {
//   st->type = 2;
//   st->dev = 0;
//   st->ino = 0;
//   st->nlink = 0;
//   st->size = 1;
// }

// void ramfs_ilock(struct vfile* vfile)
// {
//   // DON'T NEED TO DO
// }

// void ramfs_iunlock(struct vfile* vfile)
// {
//   // DON'T NEED TO DO
// }

// void ramfs_iput(struct vfile* vfile) 
// {
//   // DON'T NEED TO DO
// }

// int ramfs_writei(struct vfile* vfile, char *src, uint off, uint n)
// {
//  struct ram* writeTo = (struct ram*)vfile->fsp;
//  if(writeTo->data[(off + 1) / 2][0] != 1)
//  {
//   writeTo->data[(off + 1) / 2] = kalloc();
//   memset(writeTo->data[(off + 1) / 2], 0, 4096);
//   memmove(&writeTo->data[(off + 1) / 2][0], (char*)1, 1);
//  }
//   cprintf("%d %d %d\n", off, (off + 1) / 3, ((off ) % 3 + 1) %);

//   memmove(&writeTo->data[(off + 1) / 2][(off + 1) / 2 + 1], src, n);
//   // cprintf("%s", writeTo->data[(off + 1) / 2][(off + 1) / 2 + 1]);
//   return 1;
// }

// int ramfs_readi(struct vfile* vfile, char *src, uint off, uint n)
// {
//    struct ram* readFrom = (struct ram*)vfile->fsp;
//   memmove(src, &readFrom->data[(off + 1) / 2][off / 2 + 1], n);
//   if(readFrom->data[(off + 1) / 2][off / 2 + 1] != 0)
//   {
//     return 1;
//   }
//   else
//   {
//     return 0;
//   }

// }


