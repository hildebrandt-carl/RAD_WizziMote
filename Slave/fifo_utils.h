#include <stdint.h>

/* write a value to the tail of the FIFO queue
 * val is the value to be written
 * returns 0 on success, 1 on error (queue full)
*/
int writeFifo(uint32_t val);

/* read a value from the head of the FIFO queue
 * val is the value that is read
 * returns 0 on success, 1 on error (queue empty)
*/
int readFifo(uint32_t *val);

/* peek the value at the head of the FIFO queue, without removing it
 * val is the value that is read
 * returns 0 on success, 1 on error (queue empty)
*/
int peekFifo(uint32_t *val);

/* empty the FIFO queue
 */
int clearFifo();
