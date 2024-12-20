#include "../src/dinamic_list/dinamic_list.h"
#include "./suite_runner/suite_runner.h"
#include "test_helpers.h"
#include <stdio.h>
#include <string.h>

void test_create_list() {
  List *li = create_list();
  ASSERT(*li == NULL, "create_list() create a empty linked list, where the "
                      "first instance is a NULL value.");
}

void test_is_empty() {
  List *li = create_list();

  ASSERT(is_empty(li), "is_empty() returns a true value if the list is empty.");
}

void test_append_to_start() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};

  append_to_start(li, st1);
  append_to_start(li, st2);

  Elem *head = *li;

  struct student data1 = head->data;
  struct student data2 = head->next->data;

  ASSERT(data1.id == 2 && strcmp(data1.name, "st2") == 0 && data2.id == 1 &&
             strcmp(data2.name, "st1") == 0,
         "append_to_start() insert a value at the beggining of the list.");
}

void test_append_to_end() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};

  append_to_start(li, st1);
  append_to_start(li, st3);
  append_to_end(li, st2);

  Elem *head = *li;
  struct student data = head->next->next->data;

  ASSERT(data.id == 2 && strcmp(data.name, "st2") == 0,
         "append_to_end() insert a value to the end of the linked list.");
}

void test_append_sorting() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st3", 10.0, 10.0};
  struct student st4 = {4, "st4", 10.0, 10.0};
  struct student st5 = {5, "st5", 10.0, 10.0};
  struct student st6 = {6, "st6", 10.0, 10.0};

  append_sorting(li, st2);
  append_sorting(li, st5);
  append_sorting(li, st1);
  append_sorting(li, st6);
  append_sorting(li, st4);
  append_sorting(li, st3);

  Elem *head = *li;

  int counter = 0;
  while (head != NULL) {
    counter++;
    head = head->next;
  }

  ASSERT(counter == 6,
         "append_sorting() insert an item in the list sorting by student id.");
}

void test_list_length() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};

  append_to_start(li, st1);
  append_to_start(li, st3);
  append_to_end(li, st2);

  ASSERT(list_length(li) == 3,
         "list_lenght() returns the current length of the list.");
}

void test_length_of_an_empty_list() {
  List *li = create_list();
  ASSERT(list_length(li) == 0, "should return 0 when the list is empty.");
}

void test_remove_from_start() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_start(li, st1);
  append_to_start(li, st2);
  append_to_start(li, st3);

  remove_from_start(li);

  Elem *head = *li;

  ASSERT(head->data.id == 2, "remove_from_start() should remove an item from "
                             "the beggining of the linked list.");
}

void test_remove_from_end() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st1);
  append_to_end(li, st2);
  append_to_end(li, st3);

  remove_from_end(li);
  remove_from_end(li);

  Elem *head = *li;

  ASSERT(head->data.id == 1 && head->next == NULL,
         "remove_from_end() should remove an item from the "
         "end of list and relocate the NULL value.");
}

void test_remove_by_id_middle() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st1);
  append_to_end(li, st2);
  append_to_end(li, st3);

  remove_by_id(li, 2);

  Elem *head = *li;

  ASSERT(head->data.id == 1 && head->next->data.id == 3 && list_length(li) == 2,
         "remove_by_id() should remove an item by its id and relocate the "
         "previous element and the next element.");
}

void test_remove_by_id_beg() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st1);
  append_to_end(li, st2);
  append_to_end(li, st3);

  remove_by_id(li, 1);

  Elem *head = *li;

  ASSERT(head->data.id == 2 && head->next->data.id == 3 && list_length(li) == 2,
         "remove_by_id() testing removing a item from the beggining.");
}

void test_remove_by_id_end() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st1);
  append_to_end(li, st2);
  append_to_end(li, st3);

  remove_by_id(li, 3);

  Elem *head = *li;

  ASSERT(head->data.id == 1 && head->next->data.id == 2 && list_length(li) == 2,
         "remove_by_id() testing removind a item from the end.");
}

void test_get_item_by_index() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st1);
  append_to_end(li, st2);
  append_to_end(li, st3);

  struct student st;

  int result = get_element_by_index(li, &st, 1);

  ASSERT((result == 1 && st.id == 2),
         "get_element_by_index() should return 1 for a succes get.");
}

void test_get_item_by_index_empty_list() {
  List *li = create_list();

  struct student st;

  int result = get_element_by_index(li, &st, 1);

  ASSERT((result == -1), "should return -1 when the list is empty.");
}

void test_get_item_by_index_empty_in_a_null_list() {
  List *li = NULL;

  struct student st;

  int result = get_element_by_index(li, &st, 1);

  ASSERT((result == 0), "should return 0 when the list is NULL.");
}

void test_get_item_by_id() {
  List *li = create_list();
  struct student st1 = {1, "st1", 10.0, 10.0};
  struct student st2 = {2, "st2", 10.0, 10.0};
  struct student st3 = {3, "st1", 10.0, 10.0};

  append_to_end(li, st2);
  append_to_end(li, st3);
  append_to_end(li, st1);

  struct student st;

  int result = get_element_by_id(li, &st, 1);

  ASSERT((result == 1 && st.id == 1), "get_element_by_id() should return the "
                                      "instance of studnt based on its id.");
}

void test_get_item_by_id_empty_list() {
  List *li = create_list();

  struct student st;

  int result = get_element_by_id(li, &st, 1);

  ASSERT((result == 0), "should return 0 when the list is empty.");
}

void test_get_item_by_id_empty_in_a_null_list() {
  List *li = NULL;

  struct student st;

  int result = get_element_by_id(li, &st, 1);

  ASSERT((result == -1), "should return -1 when the list is NULL.");
}
int main() {
  func tests[] = {
      test_create_list,
      test_is_empty,
      test_append_to_start,
      test_append_to_end,
      test_append_sorting,
      test_list_length,
      test_length_of_an_empty_list,
      test_remove_from_start,
      test_remove_from_end,
      test_remove_by_id_middle,
      test_remove_by_id_beg,
      test_remove_by_id_end,
      test_get_item_by_index,
      test_get_item_by_index_empty_list,
      test_get_item_by_index_empty_in_a_null_list,
      test_get_item_by_id,
      test_get_item_by_id_empty_list,
      test_get_item_by_id_empty_in_a_null_list,
  };

  int amount_of_tests = sizeof(tests) / sizeof(tests[0]);

  run(tests, amount_of_tests, "Dinamic List");
  return 0;
}
