/* test_ehht_resize.c: test for a simple OO hashtable
   Copyright (C) 2016, 2017, 2018 Eric Herman <eric@freesa.org>

   This work is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or (at
   your option) any later version.

   This work is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

	https://www.gnu.org/licenses/lgpl-3.0.txt
	https://www.gnu.org/licenses/gpl-3.0.txt
*/
#include "test-ehht.h"

int test_ehht_resize()
{
	int failures = 0;
	struct ehht_s *table;
	size_t i, x, items_written, num_buckets, big_bucket1, big_bucket2;
	size_t report[10];
	char buf[24];

	num_buckets = 4;
	table = ehht_new(num_buckets, NULL, NULL, NULL, NULL);

	if (table == NULL) {
		return ++failures;
	}

	failures += check_unsigned_int_m(table->num_buckets(table), num_buckets,
					 "init num_buckets");

	x = num_buckets;
	for (i = 0; i < x; ++i) {
		sprintf(buf, "_%lu_", (unsigned long)i);
		table->put(table, buf, strlen(buf), NULL);
	}

	items_written = ehht_distribution_report(table, report, 10);
	failures += check_unsigned_int_m(items_written, num_buckets,
					 "first items_written");
	big_bucket1 = 0;
	for (i = 0; i < items_written; ++i) {
		if (report[i] > big_bucket1) {
			big_bucket1 = report[i];
		}
	}

	num_buckets *= 2;
	table->resize(table, num_buckets);

	items_written = ehht_distribution_report(table, report, 10);
	failures +=
	    check_unsigned_int_m(items_written, table->size(table),
				 "second items_written");

	big_bucket2 = 0;
	for (i = 0; i < items_written; ++i) {
		if (report[i] > big_bucket1) {
			big_bucket2 = report[i];
		}
	}

	sprintf(buf, "max1: %lu, max2: %lu", (unsigned long)big_bucket1,
		(unsigned long)big_bucket2);
	failures += check_unsigned_int_m((big_bucket2 <= big_bucket1), 1, buf);

	for (i = 0; i < x; ++i) {
		sprintf(buf, "_%lu_", (unsigned long)i);
		failures +=
		    check_size_t_m(table->has_key(table, buf, strlen(buf)), 1,
				   buf);
	}

	ehht_free(table);
	return failures;
}

TEST_EHHT_MAIN(test_ehht_resize())
