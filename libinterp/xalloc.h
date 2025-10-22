#ifdef LINUX_386
#include <sys/mman.h>
#include <unistd.h>

static void* xalloc(int s)
{
	s += sizeof(int); /* For storing the size */
	void *r = mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (r != MAP_FAILED) {
		/* Use first byte to store the size */
		int *r2 = r;
		*r2 = s;
		++r2;
		r = r2;
		return r;
	}
	return 0;
}

static void* xallocz(int s)
{
	return xalloc(s);
}

static void xfree(void *p)
{
	if (p == NULL)
		return;
	int *p2 = p;
	--p;
	p = p2;
	munmap(p, *p2);
}

static void xactivate(void *p)
{
	int *p2 = p;
	--p2;
	p = p2;
	mprotect(p, *p2, PROT_READ | PROT_EXEC);
}
#else
#define xalloc(s) malloc(s)
#define xallocz(s) mallocz(s, 0)
#define xfree(p) free(p)
#define xactivate(p) {}
#endif /* LINUX_386 */
