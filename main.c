#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"

typedef char Data[TRACK_TITLE_SIZE];

Node *playlist = NULL;

char *remove_newline_if_exists(char *line) {
  if (line == NULL) {
    return NULL;
  }

  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }

  return line;
}

Node **load_file(const char *filename, Node **list) {

  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  char line[TRACK_TITLE_SIZE];

  while (fgets(line, sizeof(line), f) != NULL) {
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
      perror("malloc");
      fclose(f);
      exit(EXIT_FAILURE);
    }
    new_node->next = NULL;

    Data *data = (Data *)malloc(sizeof(Data));
    if (!data) {
      perror("malloc");
      free(new_node);
      fclose(f);
      exit(EXIT_FAILURE);
    }

    strncpy(*data, line, TRACK_TITLE_SIZE);
    (*data)[TRACK_TITLE_SIZE - 1] = '\0';

    new_node->data = data;

    if (*list == NULL) {
      *list = new_node;
    } else {
      Node *t = tail(*list);
      t->next = new_node;
    }
  }

  fclose(f);
  return list;
}

void save_file(const char *filename, Node *list) {

  FILE *f = fopen(filename, "w");
  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  Node *current = list;

  while (current != NULL) {
    fprintf(f, "%s\n", (char *)current->data);
    current = current->next;
  }

  fclose(f);
}

void print_tracks(const Node *const playlist_head) {
  const Node *current = playlist_head;
  for (size_t i = 1; current; i++, current = current->next) {
    printf("%2zu: %s\n", i, (char *)current->data);
  }
}

static void free_playlist(Node **head) {
  if (head == NULL) {
    return;
  }

  while (*head != NULL) {
    void *data = delete_at(head, 0);
    free(data);
  }
}

int main(void) {
  load_file(PLAYLIST_IN_PATH, &playlist);
  print_tracks(playlist);

  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  Node *new_node = (Node *)malloc(sizeof(Node));
  if (!new_node) {
    perror("malloc");
    free_playlist(&playlist);
    exit(EXIT_FAILURE);
  }
  new_node->next = NULL;

  Data *data = (Data *)malloc(sizeof(Data));
  if (!data) {
    perror("malloc");
    free(new_node);
    free_playlist(&playlist);
    exit(EXIT_FAILURE);
  }

  strncpy(*data, "Tarkan - Ş1mar1k 💋", TRACK_TITLE_SIZE);
  (*data)[TRACK_TITLE_SIZE - 1] = '\0';

  new_node->data = data;

  if (insert_at(&playlist, 3, new_node) == NULL) {

    fprintf(stderr, "Failed to insert new track into playlist.\n");
    free(data);
    free(new_node);
    free_playlist(&playlist);
    exit(EXIT_FAILURE);
  }

  save_file(PLAYLIST_OUT_PATH, playlist);

  free_playlist(&playlist);

  return 0;
}
