/* UWindsor CS POTW 2017
 * Week 4 - The Blackboard API
 * Adam Vandolder
 * github.com/avandolder */

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Course
{
    typedef std::shared_ptr<Course> Ptr;

    bool has_parents() { return !parents.empty(); }
    void add_parent(Ptr c) { parents.insert(c); }
    void remove_parent(Ptr c) { parents.erase(c); }
    void add_child(Ptr c) { children.insert(c); }
    auto& get_children() { return children; }

private:
    std::unordered_set<Ptr> children; // Courses that require this one.
    std::unordered_set<Ptr> parents; // Courses this one requires.
};

auto can_graduate(auto& courses, int required)
{
    std::vector<Course::Ptr> satisfied; // Keep track of courses for which the
                                        // requirements have been satisfied.
    int taken = 0; // Keep track of the number of courses that can be taken.

    // Find courses with no requirements.
    for (auto c : courses)
        if (!c.second->has_parents())
            satisfied.push_back(c.second);

    while (!satisfied.empty())
    {
        // Get the top course from the satisfied list.
        auto parent = satisfied.back();
        satisfied.pop_back();

        // Increase the amount of courses taken, returning if surpasses or
        // equals the required amount.
        if (++taken >= required)
            return true;

        for (auto c : parent->get_children())
        {
            c->remove_parent(parent);

            // If c's has no more prerequisites, add it to satisfied.
            if (!c->has_parents())
                satisfied.push_back(c);
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    std::unordered_map<int, Course::Ptr> courses;

    int c, n;
    std::cin >> c >> n;

    for (int i = 0; i < n; i++)
    {
        int parent, child;
        std::cin >> parent >> child;

        // If either of the courses don't already exist, create them.
        if (courses.find(parent) == courses.end())
            courses[parent] = std::make_shared<Course>();
        if (courses.find(child) == courses.end())
            courses[child] = std::make_shared<Course>();

        courses[child]->add_parent(courses[parent]);
        courses[parent]->add_child(courses[child]);
    }

    std::cout << (can_graduate(courses, c) ? "Good" : "Bad") << std::endl;

    return 0;
}
