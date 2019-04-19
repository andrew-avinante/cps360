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

void raminit(void)
{
  initlock(drive.lock, "ram");
}

struct vfile* ramfs_create(char *path, short type, short major, short minor)
{
  for(int i = 0; i < MAX_RAMFILES; i++)
  {
    if(drive.ramFiles[i].alloc == 0)
    {
      cprintf("%d\n", i);
      memmove(drive.ramFiles[i].fName, path, 14);
      drive.ramFiles[i].alloc = 1;
      drive.ramFiles[i].data = kalloc();
      memset(drive.ramFiles[i].data, 0, 4096);
      return vfile_alloc(&drive.ramFiles[i], &ramfs_vfs_ops);
    }
  }
  return vfile_alloc(NULL, &ramfs_vfs_ops);
}

void ramfs_stati(struct vfile *vfile, struct stat *st)
{
  st->type = 2;
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
  return 1;
}

int ramfs_readi(struct vfile* vfile, char *src, uint off, uint n)
{
   struct ram* readFrom = (struct ram*)vfile->fsp;
  memmove(src, &readFrom->data[off], n);
  if(readFrom->data[off] != 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}


