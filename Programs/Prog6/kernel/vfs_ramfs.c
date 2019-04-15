#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "fs.h"
#include "vfs.h"
#include "file.h"
#include "stat.h"
#include "vfs_ramfs.h"

struct vfs_ops ramfs_vfs_ops = {
  .stati = ramfs_stati,
  .ilock = ramfs_ilock,
  .iunlock = ramfs_iunlock,
  .iput = ramfs_iput,
  .writei = ramfs_writei,
  .readi = ramfs_readi
};

#define MAX_RAMFILES 20

struct ram {
  int alloc;
  char* fName;
  char* data;
};

struct ramDrive {
  struct spinlock lock;
  struct ram* ramFiles[MAX_RAMFILES];
};

struct ramDrive drive;

void raminit(void)
{
  initlock(&drive.lock, "ram");
}

struct vfile* ramfs_create(char *path, short type, short major, short minor)
{
  struct ram* ip;
  for(int i = 0; i < MAX_RAMFILES; i++)
  {
    ip = drive.ramFiles[i];
    if(ip->alloc == 0)
    {
      ip->fName = path;
      ip->alloc = 1;
      ip->data = kalloc();
      break;
    }
  }

  return vfile_alloc(ip, &ramfs_vfs_ops);
}

void ramfs_stati(struct vfile *vfile, struct stat *st)
{
  st->type = 3;
  st->dev = 0;
  st->ino = 0;
  st->nlink = 0;
  st->size = sizeof(vfile->fsp);
}

void ramfs_ilock(struct vfile* vfile)
{
  // DON'T NEED TO DO
}

void ramfs_iunlock(struct vfile* vfile)
{
  // DON'T NEED TO DO
}

void ramfs_iput(struct vfile* vfile) 
{
  // DON'T NEED TO DO
}

int ramfs_writei(struct vfile* vfile, char *src, uint off, uint n)
{
  struct ram* writeTo = (struct ram*)vfile->fsp;
  memmove(&writeTo->data[off], src, n);
  return 0;
}

int ramfs_readi(struct vfile* vfile, char *src, uint off, uint n)
{
  struct ram* readFrom = (struct ram*)vfile->fsp;
  memmove(&readFrom->data[off], src, n);
  return 0;
}


