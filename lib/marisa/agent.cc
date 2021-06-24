#include <new>

#include "marisa/agent.h"
#include "marisa/grimoire/trie.h"

namespace marisa {

Agent::Agent() : query_(), key_(), state_(NULL) {}

Agent::~Agent() {
  delete state_;
}

Agent::Agent(const Agent &other)
    : query_(other.query_),
      key_(other.key_),
      state_(other.has_state() ? new (std::nothrow) grimoire::trie::State(other.state()) : NULL) {}

Agent &Agent::operator=(const Agent &other) {
  query_ = other.query_;
  key_ = other.key_;
  delete state_;
  if (other.has_state()) {
    state_ = new (std::nothrow) grimoire::trie::State(other.state());
  } else {
    state_ = NULL;
  }
  return *this;
}

#if __cplusplus >= 201103L
Agent::Agent(Agent &&other) noexcept
    : query_(other.query_), key_(other.key_), state_(other.state_) {
  other.state_ = NULL;
}

Agent &Agent::operator=(Agent &&other) noexcept {
  query_ = other.query_;
  key_ = other.key_;
  delete state_;
  state_ = other.state_;
  other.state_ = NULL;
  return *this;
}
#endif

void Agent::set_query(const char *str) {
  MARISA_THROW_IF(str == NULL, MARISA_NULL_ERROR);
  if (state_ != NULL) {
    clear_state();
  }
  query_.set_str(str);
}

void Agent::set_query(const char *ptr, std::size_t length) {
  MARISA_THROW_IF((ptr == NULL) && (length != 0), MARISA_NULL_ERROR);
  if (state_ != NULL) {
    clear_state();
  }
  query_.set_str(ptr, length);
}

void Agent::set_query(std::size_t key_id) {
  if (state_ != NULL) {
    clear_state();
  }
  query_.set_id(key_id);
}

void Agent::init_state() {
  MARISA_THROW_IF(state_ != NULL, MARISA_STATE_ERROR);
  delete state_;
  state_ = new (std::nothrow) grimoire::State;
  MARISA_THROW_IF(state_ == NULL, MARISA_MEMORY_ERROR);
}

void Agent::clear() {
  Agent().swap(*this);
}


void Agent::clear_state() {
  delete state_;
  state_ = nullptr;
}

void Agent::swap(Agent &rhs) {
  query_.swap(rhs.query_);
  key_.swap(rhs.key_);
  marisa::swap(state_, rhs.state_);
}

}  // namespace marisa
