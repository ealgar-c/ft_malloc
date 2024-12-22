# ft_malloc
This project is about implementing a dynamic memory allocation mechanism.

### ALLOWED FUNCTIONS:

#### mmap()



``` plaintext

void *mmap(void addr[.length], size_t length, int prot, int flags, int fd, off_t offset);


nmap creates a new mapping in the virtual address space of the calling process.

addr -> Specifies the starting address for the new mapping. If addr is NULL, the kernel chooses the page-aligned address at which the new mapping will be created. If addr is NOT NULL, it uses it as a hint about where to place the mapping

length -> Specifies the length of the mapping (must be greater than 0)

prot -> Indicates the desired memory protection for the mapping

flags -> Some extra flags

fd && offset -> You can map something from a file descriptor starting at offset


RETURN VALUE: In case of success, this function returns a pointer to the mapped area. In case of error, the value MAP_FAILED ((void *) -1) is returned. 
```

#### munmap()

``` plaintext

int munmap(void addr[.length], size_t length);



munmap deletes the mappings forthe specified address range. 


RETURN VALUE: On success, munmap() returns 0; in case of error, it returns -1.

```

#### getpagesize()

```plaintext

int get_agesize(void);


This function returns the number of bytes in a memory page. Being "page" a fixed-length memory block.

RETURN VALUE: The nuber of bytes in a memory page
```

#### getrlimit()

```plaintext

int getrlimit(int resource, struct rlimit *rlim);


The getrlimit() system call get resource limits.  Each resource has an associated soft and hard limit, as defined by the rlimit structure.

RETURN VALUE: On success, getrlimit() returns 0; in case of error, it returns -1.
```


### PROJECT LOGIC:
The main part of the understanding of the project is the logic used behind the zones and blocks.
A new zone is created when there is no zone yet, or when the actual zones created has no space to accomodate the requested memory size.
In general words, zones are contiguous regions of memory (we ensure this calling mmap) that will be subdivided in different blocks (allocations)

The blocks inside a zone are the different allocations stored in a zone.

it is important to keep in mind two things: the space we have to reserve for the metadata of the structures of the zones and blocks and the possibility
of having memory freed, meaning that we have to ensure each time that we are searching for the best block for the request and not just creating a new one.