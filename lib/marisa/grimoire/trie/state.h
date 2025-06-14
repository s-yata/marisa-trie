#ifndef MARISA_GRIMOIRE_TRIE_STATE_H_
#define MARISA_GRIMOIRE_TRIE_STATE_H_

#include <cassert>
#include <vector>

#include "marisa/grimoire/trie/history.h"

namespace marisa::grimoire::trie {

// A search agent has its internal state and the status codes are defined
// below.
enum StatusCode {
  MARISA_READY_TO_ALL,
  MARISA_READY_TO_COMMON_PREFIX_SEARCH,
  MARISA_READY_TO_PREDICTIVE_SEARCH,
  MARISA_END_OF_COMMON_PREFIX_SEARCH,
  MARISA_END_OF_PREDICTIVE_SEARCH,
};

class State {
 public:
  State() = default;

  State(const State &) = default;
  State &operator=(const State &) = default;
  State(State &&) noexcept = default;
  State &operator=(State &&) noexcept = default;

  void set_node_id(uint32_t node_id) {
    node_id_ = node_id;
  }
  void set_query_pos(uint32_t query_pos) {
    query_pos_ = query_pos;
  }
  void set_history_pos(uint32_t history_pos) {
    history_pos_ = history_pos;
  }
  void set_status_code(StatusCode status_code) {
    status_code_ = status_code;
  }

  uint32_t node_id() const {
    return node_id_;
  }
  uint32_t query_pos() const {
    return query_pos_;
  }
  uint32_t history_pos() const {
    return history_pos_;
  }
  StatusCode status_code() const {
    return status_code_;
  }

  const std::vector<char> &key_buf() const {
    return key_buf_;
  }
  const std::vector<History> &history() const {
    return history_;
  }

  std::vector<char> &key_buf() {
    return key_buf_;
  }
  std::vector<History> &history() {
    return history_;
  }

  void reset() {
    status_code_ = MARISA_READY_TO_ALL;
  }

  void lookup_init() {
    node_id_ = 0;
    query_pos_ = 0;
    status_code_ = MARISA_READY_TO_ALL;
  }
  void reverse_lookup_init() {
    key_buf_.resize(0);
    key_buf_.reserve(32);
    status_code_ = MARISA_READY_TO_ALL;
  }
  void common_prefix_search_init() {
    node_id_ = 0;
    query_pos_ = 0;
    status_code_ = MARISA_READY_TO_COMMON_PREFIX_SEARCH;
  }
  void predictive_search_init() {
    key_buf_.resize(0);
    key_buf_.reserve(64);
    history_.resize(0);
    history_.reserve(4);
    node_id_ = 0;
    query_pos_ = 0;
    history_pos_ = 0;
    status_code_ = MARISA_READY_TO_PREDICTIVE_SEARCH;
  }

 private:
  std::vector<char> key_buf_;
  std::vector<History> history_;
  uint32_t node_id_ = 0;
  uint32_t query_pos_ = 0;
  uint32_t history_pos_ = 0;
  StatusCode status_code_ = MARISA_READY_TO_ALL;
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_STATE_H_
