// list.inl
// Included at the bottom of list.h — do not include directly.

namespace dstr {

  // ── Node ────────────────────────────────────────────────────────────────────

  template <typename T>
  List<T>::Node::Node(const T& value, int level)
    : data(value), forward(level + 1, nullptr) {}


  // ── Lifecycle ────────────────────────────────────────────────────────────────

  template <typename T>
  List<T>::List() : currentLevel_(0), size_(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    head_ = new Node(T{}, MAX_LEVEL);
  }

  template <typename T>
  List<T>::~List() {
    Node* cur = head_;
    while (cur) {
      Node* next = cur->forward[0];
      delete cur;
      cur = next;
    }
  }


  // ── Internal helpers ─────────────────────────────────────────────────────────

  template <typename T>
  int List<T>::randomLevel() {
    int level = 0;
    while (level < MAX_LEVEL &&
           (static_cast<float>(std::rand()) / RAND_MAX) < PROB)
      ++level;
    return level;
  }

  template <typename T>
  std::vector<typename List<T>::Node*> List<T>::findUpdate(const T& value) {
    std::vector<Node*> update(MAX_LEVEL + 1, nullptr);
    Node* cur = head_;
    for (int i = currentLevel_; i >= 0; --i) {
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
      update[i] = cur;
    }
    return update;
  }


  // ── Public operations ────────────────────────────────────────────────────────

  template <typename T>
  void List<T>::insert(const T& value) {
    auto update = findUpdate(value);
    Node* candidate = update[0]->forward[0];
    if (candidate && candidate->data == value)
      return; // duplicate

    int newLevel = randomLevel();
    if (newLevel > currentLevel_) {
      for (int i = currentLevel_ + 1; i <= newLevel; ++i)
        update[i] = head_;
      currentLevel_ = newLevel;
    }

    Node* newNode = new Node(value, newLevel);
    for (int i = 0; i <= newLevel; ++i) {
      newNode->forward[i]   = update[i]->forward[i];
      update[i]->forward[i] = newNode;
    }
    ++size_;
  }

  template <typename T>
  void List<T>::display() const {
    Node* cur = head_->forward[0];
    while (cur) {
      std::cout << cur->data << "\n";
      cur = cur->forward[0];
    }
  }

  template <typename T>
  void List<T>::search(const T& value) const {
    Node* cur = head_;
    for (int i = currentLevel_; i >= 0; --i)
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
    cur = cur->forward[0];
    if (cur && cur->data == value)
      std::cout << "Found: " << cur->data << "\n";
    else
      std::cout << "Not found\n";
  }

  template <typename T>
  const T* List<T>::find(const T& value) const {
    Node* cur = head_;
    for (int i = currentLevel_; i >= 0; --i)
      while (cur->forward[i] && cur->forward[i]->data < value)
        cur = cur->forward[i];
    cur = cur->forward[0];
    if (cur && cur->data == value)
      return &cur->data;
    return nullptr;
  }

  template <typename T>
  bool List<T>::remove(const T& value) {
    auto update = findUpdate(value);
    Node* target = update[0]->forward[0];
    if (!target || target->data != value)
      return false;
    for (int i = 0; i <= currentLevel_; ++i) {
      if (update[i]->forward[i] != target) break;
      update[i]->forward[i] = target->forward[i];
    }
    delete target;
    --size_;
    while (currentLevel_ > 0 && !head_->forward[currentLevel_])
      --currentLevel_;
    return true;
  }

  template <typename T>
  void List<T>::sort() {}  // always sorted on insert

  template <typename T>
  bool List<T>::empty() const {
    return size_ == 0;
  }

  template <typename T>
  int List<T>::size() const {
    return size_;
  }

  template <typename T>
  template <typename Visitor>
  void List<T>::for_each(Visitor fn) const {
    Node* cur = head_->forward[0];
    while (cur) {
      fn(cur->data);
      cur = cur->forward[0];
    }
  }

} // namespace dstr
