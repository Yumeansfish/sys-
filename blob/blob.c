#include "blob.h"
#include <stdio.h>
#include <string.h>

//  All the functions take a pointer to a blob object that represents a potentially large sequence of bytes. The blob structure stores such a sequence within a list of chunks, each storing a subsequence of bytes. Each chunk is stored as an array of bytes in a chunk structure. The blob object then simply consists of a doubly-linked list with sentinel of chunk objects. Notice that the list may be empty (no chunks), which represents an empty blob. Individual chunks may also be empty, when their length is 0.

// count_char(b,c) must return the number of occurrences of character c in blob b.

// copy_to_buffer(b,buf,maxlen) must copy at most maxlen bytes from blob b into the given buffer buf. If the blob contains less than maxlen bytes or exactly maxlen bytes, then all those bytes are copied into the buffer and the return value is the number of bytes actually copied. If the blob contains more than maxlen bytes, then the function must copy the first maxlen bytes in the blob, and the return value must be maxlen+1.

// copy_to_buffer_reverse(b,buf,maxlen) must copy at most maxlen bytes from the blob b into the given buffer buf in reverse order, starting from the end of the content of the blob. The order is reversed in the sense that the last byte of the blob must be copied in the first position in the buffer, then the byte right before the last one in the blob must go to the second position in the buffer, and so on. As for copy_to_buffer, the return value is the number of bytes actually copied, or maxlen+1 if the blob contains more than maxlen bytes.

// Use the blob.tgz test package you find on-line to test your solution. 



unsigned int	count_char(const struct blob *b, char c)
{
    const struct chunk_list* itr = &b->sentinel;
    itr = itr->next;
    if(itr == &b->sentinel)return 0;
    unsigned int count =0;
    while(itr!=&b->sentinel){
        struct chunk* cur_chunk = itr->c;
        if(cur_chunk->length == 0){
            itr = itr->next;
            continue;
        }
        for(int i =0;i<cur_chunk->length;i++){
            if(cur_chunk->data[i]==c)count ++;
        }
        itr = itr->next;
    }
    return count;
}

unsigned int	copy_to_buffer(const struct blob *b, char *buf,
		unsigned int maxlen)
{
   const struct chunk_list *itr = &b->sentinel;
   itr = itr->next;
   if(itr==&b->sentinel)return 0;
   unsigned int count = 0;
    char* write = buf;
   while(itr!=&b->sentinel){
    struct chunk* cur_chunk = itr->c;
    if(cur_chunk->length ==0){
        itr = itr->next;
        continue;
    }
    for(int i =0;i<cur_chunk->length;i++){
        if(count<maxlen){
            *write ++  = cur_chunk->data[i];
            count++;
        }
        else return maxlen+1;
    }
    itr = itr->next;
   }
   return count;
}

unsigned int	copy_to_buffer_reverse(const struct blob *b, char *buf,
		unsigned int maxlen)
{
    const struct chunk_list *itr = &b->sentinel;
    itr = itr->prev;
    if(itr==&b->sentinel)return 0;
    unsigned int count = 0;
    char* write = buf;
    while(itr!=&b->sentinel){
        struct chunk* cur_chunk = itr->c;
        if(cur_chunk->length==0){
            itr = itr->prev;
            continue;
        }
        for(int i =cur_chunk->length-1;i>-1;i--){
            if(count<maxlen){
                *write ++ = cur_chunk->data[i];
                count++;
            }
            else return maxlen+1;
        }
        itr = itr->prev;
    }
    return count;
	
}






// //prev implementation
// struct chunk_list sentinel = b->sentinel;
// 	struct chunk_list *itr = &sentinel;

// 	// move to prev first
// 	itr = itr->prev;
// 	if (itr == &sentinel)
// 		return (0);

// 	char *write = buf;
// 	unsigned int count = 0;
// 	while (itr != &sentinel)
// 	{
// 		struct chunk *cur_chunk = itr->c;
// 		if (cur_chunk->length == 0)
// 		{
// 			itr = itr->prev;
// 			continue ;
// 		}

// 		for (int i = cur_chunk->length; i > 0; i--)
// 		{
// 			if (count < maxlen)
// 			{
// 				*write++ = cur_chunk->data[i];
// 				count++;
// 			}

// 			else if (count >= maxlen)
// 				return (maxlen + 1);
// 		}
// 		itr = itr->prev;
// 	}
// 	return (count);