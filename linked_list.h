#pragma once
#include <stddef.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

Node *insert_at(Node **head, size_t n, Node *node);

size_t list_len(Node *head);

Node *node_at(Node *head, size_t n);

void *delete_at(Node **head, size_t n);

Node *tail(Node *head);
