#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/queue.h>
#include <sys/mman.h>

#define MMAPED 1
#define PREV_USED 2
#define MIN_SIZE 0x18
#define BIG_BLOCK_THRESHOLD (3 * (size_t)getpagesize())
#define BLOCK_ALIGNMENT sizeof(size_t)

#define DEFAULT_CHUNK_SIZE (10 * (size_t)getpagesize())
#define FREE_HEADER_SIZE sizeof(size_t)
#define is_initialized(arena) ((arena).lh_first != NULL)
#define get_chunk(size) mmap(\
    NULL,\
    (size),\
    PROT_READ | PROT_WRITE,\
    MAP_ANONYMOUS | MAP_PRIVATE,\
    0,\
    0\
)

#define make_tag(block) \
    *(((int64_t*)(block)) + get_size((block)->mb_size)/sizeof(size_t)) = (block)->mb_size;

#define mark_mmaped(block) (block)->mb_size |= MMAPED
#define mark_not_mmaped(block) (block)->mb_size &= ~MMAPED

#define mark_prev_used(block) (block)->mb_size |= PREV_USED
#define mark_prev_not_used(block) (block)->mb_size &= ~PREV_USED

#define is_prev_used(block) ((block)->mb_size & PREV_USED)
#define is_mmaped(block) ((block)->mb_size & MMAPED)

#define get_size(sz) ((sz) & (~PREV_USED) & (~MMAPED))


#define aligned_size(size, alignment) ((size) <= MIN_SIZE ?\
    MIN_SIZE :\
    (size) + ((size) % (alignment) ? ((alignment) - (size) % (alignment)) : 0))

#define get_block_at_offset(block, offset) \
    (mem_block_t*)((size_t*)(block) + (offset))

typedef LIST_HEAD(, mem_chunk) arena_t;
typedef struct mem_block
{
    size_t mb_size;
    union {
        LIST_ENTRY(mem_block) mb_node;
        uint64_t mb_data[0];
    };
} mem_block_t;

typedef struct mem_chunk
{
    LIST_ENTRY(mem_chunk) ma_node;
    LIST_HEAD(, mem_block) ma_freeblks;
    int32_t size;
    mem_block_t ma_first[0];
} mem_chunk_t;

arena_t arena;
pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *expand_arena(arena_t *arena, size_t chunk_size)
{
    assert(!(chunk_size % getpagesize()));
    mem_chunk_t *chunk = (mem_chunk_t *)get_chunk(chunk_size);
    chunk->size = chunk_size;
    LIST_INSERT_HEAD(arena, chunk, ma_node);
    LIST_INIT(&chunk->ma_freeblks);
    mem_block_t *first_free = (mem_block_t *)chunk->ma_first;
    LIST_INSERT_HEAD(&chunk->ma_freeblks, first_free, mb_node);
    first_free->mb_size = DEFAULT_CHUNK_SIZE - sizeof(mem_chunk_t) - FREE_HEADER_SIZE;
    make_tag(first_free);
    mark_prev_used(first_free);

    return (void*)chunk;
}

void initialize_arena(arena_t *arena)
{
    LIST_INIT(arena);
    expand_arena(arena, DEFAULT_CHUNK_SIZE);

    
}

void split_free_block(mem_block_t *block, size_t size)
{
    assert(size % BLOCK_ALIGNMENT == 0);
    assert(size >= MIN_SIZE);
    size_t block_size = get_size(block->mb_size);
    assert(block_size >= size);
    mem_block_t *remaining = get_block_at_offset(block, size/sizeof(size_t) + 1);
    if (block_size - size < MIN_SIZE)
    {
        LIST_REMOVE(block, mb_node);
    }
    else
    {
        remaining->mb_size = block_size - size - sizeof(size_t);
        make_tag(remaining);
        LIST_INSERT_AFTER(block, remaining, mb_node);
        LIST_REMOVE(block, mb_node);
        block->mb_size = size;
        mark_prev_used(block);
    }
    mark_prev_used(remaining);
}

void *mymalloc(size_t size)
{
    if(size == 0)
        return NULL;
    size = aligned_size(size, BLOCK_ALIGNMENT);
    if(size >= BIG_BLOCK_THRESHOLD)
    {
        mem_block_t *block = get_chunk(size + sizeof(mem_block_t));
        block->mb_size = size;
        mark_mmaped(block);
        mark_prev_used(block);
        return block->mb_data;
    }

    if (!is_initialized(arena))
        initialize_arena(&arena);


    mem_chunk_t *chunk;
    LIST_FOREACH(chunk, &arena, ma_node)
    {
        mem_block_t *block;
        LIST_FOREACH(block, &arena.lh_first->ma_freeblks, mb_node)
        {
            size_t block_size = get_size(block->mb_size);
            if(block_size >= size)
            {
                split_free_block(block, size);
                return block->mb_data;
            }
        }
    }

    // no free space found, need new chunk
    chunk = expand_arena(&arena, DEFAULT_CHUNK_SIZE);
    mem_block_t *block = chunk->ma_first;
    split_free_block(block, size);
    return block->mb_data;

}

void myfree(void *data)
{
    if(!data)
        return;

    mem_block_t *block = (mem_block_t*)((int64_t*)data - 1);
    size_t size = get_size(block->mb_size);
    if(is_mmaped(block))
    {
        munmap(block, aligned_size(size, getpagesize()));
        return;
    }

    mem_block_t *next_adj_block = get_block_at_offset(block, size/sizeof(size_t) + 1);
    size_t next_size = get_size(next_adj_block->mb_size);
    mem_block_t *nextnext_adj_block = get_block_at_offset(
        next_adj_block, 
        next_size/sizeof(size_t) + 1
    );

    // TODO add some asserts
    assert(is_prev_used(next_adj_block));

    bool on_list = false;
    bool coalesced = false;
    // try to coalesce prev
    if(!is_prev_used(block))
    {
        size_t prev_size = *((size_t*)block - 1);
        mem_block_t *prev_block = get_block_at_offset(
            block, 
            -(int64_t)prev_size/sizeof(int64_t) - 1
        );
        prev_block->mb_size += size + sizeof(size_t);
        make_tag(prev_block);
        block = prev_block;
        mark_prev_not_used(next_adj_block);
        on_list = true;
        coalesced = true;
    }

    // try to coalesce next
    if(!is_prev_used(nextnext_adj_block))
    {
        block->mb_size += next_size + sizeof(size_t);
        if(!on_list)
            LIST_INSERT_BEFORE(next_adj_block, block, mb_node);
        LIST_REMOVE(next_adj_block, mb_node);
        make_tag(block);
        coalesced = true;
    }

    if(coalesced)
        return;

    mark_prev_not_used(next_adj_block);
    mem_chunk_t *chunk;
    LIST_FOREACH(chunk, &arena, ma_node)
    {
        size_t low = (size_t)chunk;
        size_t high = low + chunk->size;
        size_t blk = (size_t)block;
        if(low <= blk && blk < high)
        {
            if(LIST_EMPTY(&chunk->ma_freeblks))
            {
                LIST_INSERT_HEAD(
                    &chunk->ma_freeblks,
                    block,
                    mb_node
                );
                return;
            }

            mem_block_t *block_it;
            LIST_FOREACH(block_it, &chunk->ma_freeblks, mb_node)
            {
                if(blk < (size_t)block_it)
                {
                    LIST_INSERT_BEFORE(block_it, block, mb_node);
                    return;
                }
            }

            // should not be there
            assert(false);
        }
    }

}

void *malloc(size_t size)
{
    pthread_mutex_lock(&malloc_mutex);
    // fprintf(stderr, "malloc(%lu)\n", size);
    void *ret = mymalloc(size);
    pthread_mutex_unlock(&malloc_mutex);
    return ret;
}

void free(void *data)
{
    pthread_mutex_lock(&malloc_mutex);
    // fprintf(stderr, "free(%p)\n", data);
    myfree(data);
    pthread_mutex_unlock(&malloc_mutex);
}


// int main(void)
// {
//     char *x = (char*)mymalloc(0x8);
//     scanf("%8s", x);
//     char *y = mymalloc(0x10);
//     scanf("%16s", x);
//     char *z = mymalloc(0x18);
//     scanf("%24s", x);

//     myfree(x);
//     myfree(y);
//     myfree(z);



//     // mymalloc(20);

//     return 0;
// }