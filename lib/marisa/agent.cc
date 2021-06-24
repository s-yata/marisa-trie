#include <new>
#include <utility>

#include "marisa/agent.h"
#include "marisa/grimoire/trie.h"
#include "marisa/grimoire/trie/state.h"

namespace marisa {

Agent::Agent() : query_(), key_(), state_() {}

Agent::~Agent() {}

Agent::Agent(const Agent &other)
    : query_(other.query_),
      key_(other.key_),
      state_(other.has_state() ? new (std::nothrow) grimoire::trie::State(other.state()) : NULL) {}

Agent &Agent::operator=(const Agent &other) {
  query_ = other.query_;
  key_ = other.key_;
  state_.reset(other.has_state() ? new (std::nothrow) grimoire::trie::State(other.state()) : NULL);
  return *this;
}

Agent::Agent(Agent &&other) noexcept = default;
Agent &Agent::operator=(Agent &&other) noexcept = default;

void Agent::set_query(const char *str) {
  MARISA_THROW_IF(str == NULL, MARISA_NULL_ERROR);
  if (state_ != nullptr) {
    state_->reset();
  }
  query_.set_str(str);
}

void Agent::set_query(const char *ptr, std::size_t length) {
  MARISA_THROW_IF((ptr == NULL) && (length != 0), MARISA_NULL_ERROR);
  if (state_ != nullptr) {
    state_->reset();
  }
  query_.set_str(ptr, length);
}

void Agent::set_query(std::size_t key_id) {
  if (state_ != nullptr) {
    state_->reset();
  }
  query_.set_id(key_id);
}

void Agent::init_state() {
  MARISA_THROW_IF(state_.get() != NULL, MARISA_STATE_ERROR);
  state_.reset(new (std::nothrow) grimoire::State);
  MARISA_THROW_IF(state_.get() == NULL, MARISA_MEMORY_ERROR);
}

void Agent::clear() {
  Agent().swap(*this);
}

void Agent::swap(Agent &rhs) {
  query_.swap(rhs.query_);
  key_.swap(rhs.key_);
  state_.swap(rhs.state_);
}

}  // namespace marisa
