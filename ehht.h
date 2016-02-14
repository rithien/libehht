/* ehht.h */
#ifndef EHHT_H
#define EHHT_H

/* a simple hash-table */

#include <stddef.h>		/* size_t */

typedef unsigned int (*ehht_hash_func) (const char *str, size_t str_len);

/* if hash_func is NULL, a hashing function will be provided */
struct ehht_s *ehht_new(size_t num_buckets, ehht_hash_func hash_func);

void ehht_free(struct ehht_s *table);

void *ehht_get(struct ehht_s *table, const char *key, size_t key_len);

/* returns the previous value or NULL */
void *ehht_put(struct ehht_s *table, const char *key, size_t key_len,
	       void *val);

/* returns the previous value or NULL */
void *ehht_remove(struct ehht_s *table, const char *key, size_t key_len);

size_t ehht_size(struct ehht_s *table);

void ehht_clear(struct ehht_s *table);

typedef void (*ehht_iterator) (const char *each_key, size_t each_key_len,
			       void *each_val, void *context);

void ehht_foreach_element(struct ehht_s *table, ehht_iterator func,
			  void *context);

/* returns the number of characters written to "buf"
   (excluding the null byte terminator) */
size_t ehht_to_string(struct ehht_s *table, char *buf, size_t buf_len);

/* reports each of the bucket sizes
   sizes_len should be equal to or greater than num_buckets of ehht_new
   returns the number of size_t values written */
size_t ehht_distribution_report(struct ehht_s *table, size_t *sizes,
				size_t sizes_len);

#endif /* EHHT_H */
