template <typename C, typename... Args>
void push_back(C& c, Args&&... args) {
    (c.push_back(args), ...);
}