/**
Author: Ichiro Miyasato
Assignment: Programming Assignment 3
Date: 09 July 2024
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include "student_code.h"

int statusno, _initialized;

node_t *_chunklist;
void *_arena_start, *_arena_end;


void print_header(node_t *header){
  //Note: These printf statements may produce a segmentation fault if the buff
  //pointer is incorrect, e.g., if buff points to the start of the arena.
  printf("Header->size: %lu\n", header->size);
  printf("Header->fwd: %p\n", header->fwd);
  printf("Header->bwd: %p\n", header->bwd);
  printf("Header->is_free: %d\n", header->is_free);
}


int init(size_t size) {
  if(size > (size_t) MAX_ARENA_SIZE) {
    return ERR_BAD_ARGUMENTS;
  }


  // Find pagesize and increase allocation to match some multiple a page size
  // Question: Why is it good to match our allocation to the size of the page?
  int pagesize = getpagesize();

  if (pagesize <= 0)
    return ERR_CALL_FAILED;

  //Align to page size
  if( size % pagesize != 0 ) {
    // Calculate how much we need to increase to match the size of a page
    size -= size % pagesize;
    size += pagesize;
  }

  // Open up /dev/zero to zero-init our memory.
  int fd=open("/dev/zero",O_RDWR);
  if (fd == -1) {
    return ERR_SYSCALL_FAILED;
  }
  // Map memory from /dev/zero using mmap()
  _arena_start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  if (_arena_start == MAP_FAILED) {
    return ERR_SYSCALL_FAILED;
  }

  _arena_end = _arena_start + size;
  _initialized = 1;

  _chunklist = _arena_start;
  _chunklist -> size = size - sizeof(node_t);

  //  mmap sets the initial memory value
  // to zero so the fwd pointer of the is already null, but
  // it doesn't hurt to make that clear
  _chunklist -> fwd = NULL;
  _chunklist -> bwd = NULL;
  _chunklist -> is_free = true;

   return size;
}

int destroy() {

  if (_initialized == 0) {
    return ERR_UNINITIALIZED; 
  }

  // Remove arena with munmap()
  if(munmap(_arena_start, _arena_end - _arena_start) == -1) {
    return ERR_SYSCALL_FAILED;
  }

  // Question: Are there memory leaks here?

  // Clean up variables
  _arena_start = NULL;
  _arena_end = NULL;
  _chunklist = NULL;
  _initialized = 0;

  return 0;
}


node_t * find_first_free_chunk(size_t size, node_t* starting_node) {
  node_t* track_node = starting_node;
  while(track_node!= NULL){
  // if the node is free and less than or equal to size, return that node
    if(track_node->size >= size && track_node->is_free){
      return track_node;
    }
  // go on to the next node until you get to an empty node
    track_node = track_node->fwd;
  }

  return NULL;
}

void split_node(node_t* node, size_t size) {
  node_t* next = node->fwd;
  // node will be unfree in any case
  node->is_free = false;
  // If the node is neither the exact right size nor bigger than requested, though too small to split
  if(!(node->size == size) && !(node->size - size < sizeof(node_t))) {
    // If the requested memory does not take up the entire free chunk, we need to
    // to split that chunk and add a new node to the free list.
    node_t* new_node = (node_t*)((char*)node + sizeof(node_t) + size);
    new_node-> size = node->size - size - sizeof(node_t);
    new_node->is_free = true;
    new_node->fwd = next;
    new_node->bwd = node;
    if(next != NULL){
      next->bwd = new_node;
    }
    node->size = size;
    node->fwd = new_node;
  }
}

node_t* get_header(void* ptr) {
  return (void*)ptr - sizeof(node_t);
}

void coalesce_nodes(node_t* front, node_t* back) {
  if (front > back) {
    // Check to make sure they're in the right order
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if (front == back) {
    // Check to make sure they aren't the same node 
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if (front == NULL || back == NULL) {
    // Then one of them is already the end of the list  
    statusno = ERR_BAD_ARGUMENTS;
    return;
  }
  if ( ! (front->is_free && back->is_free)) {
    // Then one of them isn't free 
    statusno = ERR_CALL_FAILED;
    return;
  }

  // We want to do two things: skip over the second node and update size.
  front->size += back->size + sizeof(node_t);
  // complete the linked list forward
  front->fwd = back->fwd;
  // complete the linked list backwards
  if (back->fwd != NULL) {
    back->fwd->bwd = front;
  }
}


void* mem_alloc(size_t size){
  // Check to make sure we are initialized, and if not set statusno and return NULL;
  if(_initialized == 0) {
    statusno = ERR_UNINITIALIZED;
    return NULL;
  }

  // Find a free chunk of memory
  node_t* node = find_first_free_chunk(size, _chunklist);

  // If finding a node returned NULL then we're out of memory
  if (node == NULL) {
    statusno = ERR_OUT_OF_MEMORY;
    return NULL;
  }

  // Split node to be the appropriate size, since there's no guarantee a free node is the right size already
  split_node(node, size);

  //return to point at the memory we just allocated (the "tail" of the node)
  return (void*)((char*)node + sizeof(node_t));
}


void mem_free(void *ptr){
  if (ptr == NULL){
    return;
  }

  if (ptr < _arena_start || ptr > _arena_end){
    // Then the pointer is outside of the arena
    return;
  }

  // Step backward from the pointer to look at the node header
  node_t* back_chunk = get_header(ptr)->bwd;

  // Get the central header
  node_t *chunk = get_header(ptr);
  // Free the memory
  chunk->is_free = true;

  // Get the forward header  
  node_t *next_chunk = chunk->fwd;

  // Coalesce together the chunks if possible
  if (back_chunk != NULL && back_chunk->is_free) {
    coalesce_nodes(back_chunk, chunk);
    chunk = back_chunk;
  }
  if (next_chunk != NULL && next_chunk->is_free) {
    coalesce_nodes(chunk, next_chunk);
  }
}

void insert_into_freelist(node_t* chunk, node_t* _chunklist) {
  // Keep it ordered by address
  node_t* curr_node = _chunklist;
  while (curr_node != NULL && curr_node > chunk ) {
    curr_node = curr_node->fwd;
  }
  
  if (curr_node == NULL) {
    // We're at the very end of the list
    curr_node->fwd->bwd = chunk;
    chunk->fwd = curr_node->fwd->bwd;
    curr_node->fwd = chunk;
    chunk->bwd = curr_node;
  } else {
    // We're in the middle of the list
  }
}
