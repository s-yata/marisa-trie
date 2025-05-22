#include "marisa/agent.h"

#include <new>
#include <utility>

#include "marisa/grimoire/trie.h"
#include "marisa/grimoire/trie/state.h"
#include "marisa/key.h"

namespace marisa {
namespace {
void UpdateAgentAfterCopyingState(const grimoire::trie::State &state,
                                  Agent &agent) {
  // Point the agent's key to the newly copied buffer if necessary.
  switch (state.status_code()) {
    case grimoire::trie::MARISA_READY_TO_PREDICTIVE_SEARCH:
    case grimoire::trie::MARISA_END_OF_PREDICTIVE_SEARCH:
      // In states corresponding to predictive_search, the agent's
      // key points into the state key buffer. We need to repoint
      // after copying the state.
      agent.set_key(state.key_buf().begin(), state.key_buf().size());
      break;
    default:
      // In other states, they key is either null, or points to the
      // query, so we do not need to repoint it.
      break;
  }
}
}  // namespace

Agent::Agent() : query_(), key_(), state_() {}

Agent::~Agent() {}

Agent::Agent(const Agent &other)
    : query_(other.query_), key_(other.key_),
      state_(other.has_state() ? new (std::nothrow)
                                     grimoire::trie::State(other.state())
                               : nullptr) {
  if (other.has_state()) {
    MARISA_THROW_IF(state_ == nullptr, MARISA_MEMORY_ERROR);
    UpdateAgentAfterCopyingState(*state_, *this);
  }
}

Agent &Agent::operator=(const Agent &other) {
  query_ = other.query_;
  key_ = other.key_;
  if (other.has_state()) {
    state_.reset(new (std::nothrow) grimoire::trie::State(other.state()));
    MARISA_THROW_IF(state_ == nullptr, MARISA_MEMORY_ERROR);
    UpdateAgentAfterCopyingState(*state_, *this);
  } else {
    state_ = nullptr;
  }
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
