/**
 * set_tests.c
 * Este programa contém uma bateria de testes para validar as implementações
 * presentes no ficheiro set.c
 * 
 * 
 * outubro de 2018
 * Build : gcc -Wall -std=c99 -o set_tests set_tests.c set.c tests/unity.c 
 * Execute : set_tests
 *---------------------------------------------------------------------------*/

#include "tests/tests.h"
#include "set.h"


// auxiliary functions

void sort_set(Set s) {
	int ss = set_cardinality(s);
	
	for(int i=ss; i > 0; --i) {
		for(int j =1; j < i; j++) {
			if (s[j] > s[j+1]) {
				int temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		}
	}
	
}

// is member tests

void test_not_a_member_of_an_empty_set() {
	Set empty = { }; 
	TEST_ASSERT_FALSE(set_is_member(empty, 3));
}

void test_is_a_member_of_set() {
	Set s1 = { 4, 23, 2, 45, 4 };
	
	TEST_ASSERT_TRUE(set_is_member(s1, 4));
}

void test_is_not_a_member_of_set() {
	Set s1 = { 4, 23, 2, 45, 55 };
	TEST_ASSERT_FALSE(set_is_member(s1, 4));
}


// intersection tests

void test_empty_intersection() {
	Set s1 = { 3, 2, 5, 7};
	Set s2 = { 3, 3, 1, 4};
	Set sr;
	
	set_intersection(s1, s2, sr);
	TEST_ASSERT_TRUE(set_cardinality(sr) ==0);
}

void test_empty_set_intersection_with_other_is_empty() {
	Set empty = { }; 
	Set s1 = { 5, 23, 2, 45, 4, 89 };
	Set result;
	
	set_intersection(s1, empty, result);
	TEST_ASSERT_EQUAL_INT_ARRAY(empty, result, 1);
}		

void test_set_intersection_with_empty_is_empty() {
	Set empty = { }; 
	Set s1 = { 5, 23, 2, 45, 4, 89 };
	Set result;
	
	set_intersection(empty, s1, result);
	TEST_ASSERT_EQUAL_INT_ARRAY(empty, result, 1);
}	

void test_set_intersection_equal_sets() {
	Set s1 = { 4, 23, 2, 45, 4 };
	Set s2 = { 4, 23, 2, 45, 4 };
	Set result;
	
	set_intersection(s2, s1, result);
	
	TEST_ASSERT_EQUAL_INT(set_cardinality(s1), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(s1+1, result+1, set_cardinality(s1));
}	

void test_empty_intersection_between_non_empty_sets() {
	Set s1 = { 4, 23, 2, 45, 4 };
	Set s2 = { 7, 3, 7, 44, 8, 9, 11, 1 };
	Set result;
	
	set_intersection(s2, s1, result);
	
	TEST_ASSERT_EQUAL_INT(0, set_cardinality(result));

}		
		
//union tests

void test_union_with_non_empty_and_empty_set() {
	Set empty = { }; 
	Set result;
	Set s1 = { 6, 23, 2, 45, 4, 11, 3 };
	
	set_union(s1, empty, result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(s1), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(s1+1, result+1, set_cardinality(s1));
}

void test_union_with_empty_and_non_empty_set() {
	Set empty = { }; 
	Set result;
	Set s1 = { 6, 23, 2, 45, 4, 11, 3 };
	
	set_union(empty, s1, result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(s1), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(s1+1, result+1, set_cardinality(s1));
	
}

void test_union_with_equals_sets() {
 
	Set result;
	Set s1 = { 6, 23, 2, 45, 4, 11, 3 };
	
	set_union(s1, s1, result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(s1), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(s1+1, result+1, set_cardinality(s1));
}

void test_union_with_exclusive_sets() {
	Set result;
	Set s1 = { 6, 23, 2, 45, 4, 11, 3 };
	Set s2 = { 3, 99, 101, 1024 };
	Set expected = { 9, 2, 3, 4, 11, 23, 45,  99, 101, 1024 };
	TEST_ASSERT_TRUE(set_union(s1, s2, result));
	
	sort_set(result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(expected), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(expected+1, result+1, set_cardinality(result));
	
}

// difference tests

void test_difference_between_empty_and_non_empty_set() {
	Set empty = { }; 
	Set s1 = { 4, 23, 2, 45, 4 };
	Set result;
	
	set_difference(empty, s1, result);
	TEST_ASSERT_TRUE(set_cardinality(result) == 0);
	
}

void test_difference_between_non_empty_and_empty_set() {
	Set empty = { }; 
	Set s1 = { 4, 23, 2, 45, 4 };
	Set result;
	
	set_difference(s1, empty, result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(s1), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(s1+1, result+1, set_cardinality(result));	
}


void test_difference_between_equal_sets() {
	Set s1 = { 4, 23, 2, 45, 4 };
	Set s2 = { 4, 23, 2, 45, 4 };
	Set result;
	
	set_difference(s1, s2, result);
	TEST_ASSERT_TRUE(set_cardinality(result) == 0);
}

void test_difference_between_different_sets() {
	Set s1 = { 4, 43, 2, 45, 4 };
	Set s2 = { 4, 23, 2, 45, 4 };
	Set result;
	Set expected = { 1, 43};
	
	set_difference(s1, s2, result);
	TEST_ASSERT_EQUAL_INT(set_cardinality(expected), set_cardinality(result));
	TEST_ASSERT_EQUAL_INT_ARRAY(result+1, expected+1, set_cardinality(result));	
}

// test_valid_sets

void test_empty_set_is_valid() {
	
	Set empty = { }; 
	TEST_ASSERT_TRUE(set_is_valid(empty));
}

void test_set_is_valid() {
	Set s1 = { 4, 43, 2, 45, 4 };
	TEST_ASSERT_TRUE(set_is_valid(s1));
}

void test_set_invalid_with_wrong_size() {
	Set s1 = { -1, 43, 2, 45, 4 };
	Set s2 = { 257, 43, 2, 45, 4 };
	TEST_ASSERT_FALSE(set_is_valid(s1));
	TEST_ASSERT_FALSE(set_is_valid(s2));
}

void test_set_invalid_with_duplicates() {
	Set s1 = { 5, 43, 2, 45, 4, 2 };
	 
	TEST_ASSERT_FALSE(set_is_valid(s1));
 
}


// contains tests

void test_set_contains_empty_set() {
	Set empty = { };
	Set s1 = { 3, 3, 1, 4};

	
	TEST_ASSERT_TRUE(set_contains(s1, empty));
}

void test_set_contains_same_set() {
	Set s1 = { 4, 43, 2, 45, 4 };
 
	TEST_ASSERT_TRUE(set_contains(s1, s1));
}

void test_set_contains_other_set() {
	Set s1 = { 4, 43, 2, 45, 4 };
	Set s2 = { 3,  2, 4, 43 };
 
	TEST_ASSERT_TRUE(set_contains(s1, s2));
}

void test_set_not_contains_other_set() {
	Set s1 = { 4, 43, 2, 45, 4 };
	Set s2 = { 5,  2, 4, 43, 45, 1 };
 
	TEST_ASSERT_FALSE(set_contains(s1, s2));
}

int main() {
	BEGIN_TESTS();

	// is member tests
	RUN_TEST(test_not_a_member_of_an_empty_set);
	RUN_TEST(test_is_a_member_of_set);
	RUN_TEST(test_is_not_a_member_of_set);
	
	// intersection tests
	RUN_TEST(test_empty_intersection);
	RUN_TEST(test_empty_set_intersection_with_other_is_empty);
	RUN_TEST(test_set_intersection_with_empty_is_empty);
	RUN_TEST(test_set_intersection_equal_sets);
	RUN_TEST(test_empty_intersection_between_non_empty_sets);
	
	//union tests
	RUN_TEST(test_union_with_non_empty_and_empty_set);
	RUN_TEST(test_union_with_empty_and_non_empty_set);
	RUN_TEST(test_union_with_equals_sets);
	RUN_TEST(test_union_with_exclusive_sets);
	
	// difference tests
	RUN_TEST(test_difference_between_empty_and_non_empty_set);
	RUN_TEST(test_difference_between_non_empty_and_empty_set);
	RUN_TEST(test_difference_between_equal_sets);
	RUN_TEST(test_difference_between_different_sets);
 
	// valid_sets tests
	RUN_TEST(test_empty_set_is_valid);
	RUN_TEST(test_set_is_valid);
	RUN_TEST(test_set_invalid_with_wrong_size);
	RUN_TEST(test_set_invalid_with_duplicates);

	// contains tests
	RUN_TEST(test_set_contains_empty_set);
	RUN_TEST(test_set_contains_same_set);
	RUN_TEST(test_set_contains_other_set);
	RUN_TEST(test_set_not_contains_other_set);
 

	
	END_TESTS();
	return 0;
}
	


