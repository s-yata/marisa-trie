#include <new>

#include "marisa/agent.h"
#include "marisa/grimoire/trie.h"

namespace marisa {

Agent::Agent() : query_(), key_(), state_() {} 

Agent::~Agent() {}

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
