#ifndef MARISA_GRIMOIRE_TRIE_STATE_HISTORY_H_
#define MARISA_GRIMOIRE_TRIE_STATE_HISTORY_H_

#include <cassert>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class History {
 public:
  History() = default;

  void set_node_id(uint32_t node_id) {
    node_id_ = node_id;
  }
  void set_louds_pos(uint32_t louds_pos) {
    louds_pos_ = louds_pos;
  }
  void set_key_pos(uint32_t key_pos) {
    key_pos_ = key_pos;
  }
  void set_link_id(uint32_t link_id) {
    link_id_ = link_id;
  }
  void set_key_id(uint32_t key_id) {
    key_id_ = key_id;
  }

  uint32_t node_id() const {
    return node_id_;
  }
  uint32_t louds_pos() const {
    return louds_pos_;
  }
  uint32_t key_pos() const {
    return key_pos_;
  }
  uint32_t link_id() const {
    return link_id_;
  }
  uint32_t key_id() const {
    return key_id_;
  }

 private:
  uint32_t node_id_ = 0;
  uint32_t louds_pos_ = 0;
  uint32_t key_pos_ = 0;
  uint32_t link_id_ = MARISA_INVALID_LINK_ID;
  uint32_t key_id_ = MARISA_INVALID_KEY_ID;
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_STATE_HISTORY_H_
