#include "linked_list.h"
#include <stdlib.h>

static Node *prev_node_at(Node *head, size_t n) {
  Node *current = head;
  Node *prev = NULL;
  size_t i = 0;

  if (n == 0 || head == NULL) {
    return NULL;
  }

  while (current != NULL && i < n) {
    prev = current;
    current = current->next;
    ++i;
  }

  if (i != n) {
    return NULL; // index out of range
  }

  return prev;
}

Node *insert_at(Node **head, size_t n, Node *node) {
  if (head == NULL || node == NULL) {
    return NULL;
  }

  // Ensure node->next is defined before insertion
  node->next = NULL;

  // Insert at head (index 0) or into an empty list
  if (n == 0 || *head == NULL) {
    node->next = *head;
    *head = node;
    return node;
  }

  Node *prev_node = prev_node_at(*head, n);
  if (prev_node == NULL) {
    // Index out of range
    return NULL;
  }

  node->next = prev_node->next;
  prev_node->next = node;

  return node;
}

size_t list_len(Node *head) {
  size_t len = 0;
  Node *current = head;

  while (current != NULL) {
    ++len;
    current = current->next;
  }

  return len;
}

Node *node_at(Node *head, size_t n) {
  Node *current = head;
  size_t i = 0;

  while (current != NULL && i < n) {
    current = current->next;
    ++i;
  }

  return current; // NULL if out of range
}

void *delete_at(Node **head, size_t n) {
  if (head == NULL || *head == NULL) {
    return NULL;
  }

  Node *current = *head;
  void *data = NULL;

  // Deleting the head node
  if (n == 0) {
    *head = current->next;
    data = current->data;
    free(current);
    return data;
  }

  // Deleting a non-head node
  Node *prev = prev_node_at(*head, n);
  if (prev == NULL || prev->next == NULL) {
    // Index out of range
    return NULL;
  }

  Node *node_to_be_deleted = prev->next;
  prev->next = node_to_be_deleted->next;

  data = node_to_be_deleted->data;
  free(node_to_be_deleted);

  return data;
}

Node *tail(Node *head) {
  if (head == NULL) {
    return NULL;
  }

  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  return current;
}
